#include <ros/ros.h>
#include <thread>
#include <rosbag/bag.h>
#include <rosbag/view.h>

#include <std_msgs/Int32.h>
#include <std_msgs/String.h>

void write() {
  rosbag::Bag bag;
  bag.open("test.bag", rosbag::bagmode::Write);

  std_msgs::String str;
  str.data = std::string("foo");

  std_msgs::Int32 i;
  i.data = 42;

  bag.write("chatter", ros::Time::now(), str);
  bag.write("numbers", ros::Time::now(), i);

  bag.close();
}

void read() {
  rosbag::Bag bag;
  bag.open("test.bag", rosbag::bagmode::Read);

  std::vector<std::string> topics;
  topics.push_back(std::string("chatter"));
  topics.push_back(std::string("numbers"));

  rosbag::View view(bag, rosbag::TopicQuery(topics));

  for(rosbag::MessageInstance const m: view)
  {
    std_msgs::String::ConstPtr s = m.instantiate<std_msgs::String>();
    if (s != NULL)
      std::cout << s->data << std::endl;

    std_msgs::Int32::ConstPtr i = m.instantiate<std_msgs::Int32>();
    if (i != NULL)
      std::cout << i->data << std::endl;
  }
  bag.close();
}

int main( int argc, char** argv ) {

  // 없으면 ros::Time::now() 사용할때 에러가 발생한다.
  ros::Time::init();

  write();
  read();

  return 0;
}
