
// System
#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>

// ROS
#include <ros/ros.h>
#include <ros/package.h>

// Local
#include <service_first/Add.h>


bool add(service_first::Add::Request &req,
                               service_first::Add::Response &res) {
  res.result = req.a + req.b;
  std::cout << req.a << " + " << req.b << " = " << res.result << std::endl;
  return true;                          
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "add_srv_node");
  ros::NodeHandle nh;
  
  ros::ServiceServer service = nh.advertiseService("add", add);
  
  ROS_INFO("add service up and running.");
  ros::spin();
  
  return EXIT_SUCCESS;
}