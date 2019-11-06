#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <thread>
#include <math.h>
#include <stdio.h>

#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>


void sendTF(const std::string name, const double x, const double y, const double theta){
  static tf::TransformBroadcaster br;

  printf("%s %f %f %f\n", name.c_str(), x, y, theta);

  tf::Transform transform;
  transform.setOrigin( tf::Vector3(x, y, 0.0) );
  tf::Quaternion q;
  q.setRPY(0, 0, theta);
  transform.setRotation(q);

  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", name));
}

void makeCloud(){
  /*
  // create point cloud object
  pcl::PointCloud<pcl::PointXYZ> myCloud;

  // fill cloud with random points
  for (int v=0; v<1000; ++v)
  {
    pcl::PointXYZ newPoint;
    newPoint.x = (rand() * 100.0) / RAND_MAX;
    newPoint.y = (rand() * 100.0) / RAND_MAX;
    newPoint.z = (rand() * 100.0) / RAND_MAX;
    myCloud.points.push_back(newPoint);
  }
  */
}

// http://docs.ros.org/jade/api/sensor_msgs/html/main_8cpp_source.html
sensor_msgs::PointCloud2 makeCloud2() {
  // Create a dummy PointCloud2
  sensor_msgs::PointCloud2 cloud_msg_1;

  int n_points = 4;
  cloud_msg_1.height = n_points;
  cloud_msg_1.width = 1;
  sensor_msgs::PointCloud2Modifier modifier(cloud_msg_1);
  modifier.setPointCloud2FieldsByString(2, "xyz", "rgb");

  // Fill 1 by hand
  float point_data_raw[] = {0.5, 0.0, 0.0, 1.0, 0.0, 0.0, 1.5, 0.0, 0.0, 2.0, 0.0, 0.0};
  std::vector<float> point_data(point_data_raw, point_data_raw + 3*n_points);

  // colors in RGB order
  uint8_t color_data_raw[] = {40, 80, 120, 160, 200, 240, 20, 40, 60, 80, 100, 120};
  std::vector<uint8_t> color_data(color_data_raw, color_data_raw + 3*n_points);

  float *data = reinterpret_cast<float*>(&cloud_msg_1.data.front());
  for(size_t n=0, i=0; n<n_points; ++n) {
    for(; i<3*(n+1); ++i)
      *(data++) = point_data[i];

    // Add an extra float of padding
    ++data;
    uint8_t *bgr = reinterpret_cast<uint8_t*>(data++);

    // add the colors in order BGRA like PCL
    size_t j_max = 2;
    for(size_t j = 0; j <= j_max; ++j)
      *(bgr++) = color_data[3*n+(j_max - j)];

    // Add 3 extra floats of padding
    data += 3;
  }
  return cloud_msg_1;
}


int main( int argc, char** argv ) {
  ros::init(argc, argv, "tf_second");

  std::thread myThread(
    []() {
      static double angle = 0;
      do {
        sendTF("/turtle1", cos(angle), sin(angle), angle + M_PI / 2);
        angle += 0.1;
        ros::Duration(1.0).sleep();
      } while (true);
    });

  std::thread myThread2 = std::thread(
    []() {
      ros::NodeHandle nh;
      ros::Publisher pub = nh.advertise<sensor_msgs::PointCloud2> ("output", 1);

      do {
        sensor_msgs::PointCloud2 cloud = makeCloud2();
        // header.frame_id를 설정한다.
        cloud.header.frame_id = "/turtle1";
        pub.publish(cloud);
        //ros::spin();
        std::cout << "publish" << std::endl;
        ros::Duration(1.0).sleep();
      }while(true);

    });

  if (myThread.joinable() == true)
    myThread.join();
  if (myThread2.joinable() == true)
    myThread2.join();

  return 0;
}
