#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <thread>


void poseCallback(const std::string turtle_name, const double x, const double y, const double theta){
  static tf::TransformBroadcaster br;

  tf::Transform transform;
  transform.setOrigin( tf::Vector3(x, y, 0.0) );
  tf::Quaternion q;
  q.setRPY(0, 0, theta);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name));
}

int main( int argc, char** argv ) {
  ros::init(argc, argv, "tf_first");

  std::thread myThread(
    []() {
      //std::cout << ros::Time::now() << std::endl;
      for (int i = 0; i < 10; i++) {
        poseCallback("/turtle1", i, 0, 0);
        poseCallback("/turtle2", 2*i, 0, 0);
        ros::Duration(1.0).sleep();
      }
    });

  std::thread myThread2 = std::thread(
    []() {
      tf::TransformListener listener;
      tf::StampedTransform transform;
      try{
        ros::Duration(3.0).sleep();
        ros::Time past = ros::Time::now() - ros::Duration(0.5);
        listener.waitForTransform("/turtle2", "/turtle1", past, ros::Duration(3.0));

        listener.lookupTransform("/turtle2", "/turtle1",
                                 past, transform);

        std::cout << transform.getOrigin().getX() << std::endl;
      }
      catch (tf::TransformException ex){
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();
      }
    });

  if (myThread.joinable() == true)
    myThread.join();

  if (myThread2.joinable() == true)
    myThread2.join();

  return 0;
}
