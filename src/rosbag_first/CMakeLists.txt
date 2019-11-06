cmake_minimum_required(VERSION 2.8.3)
project(rosbag_first)

add_compile_options(-std=c++17)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  rosbag
  roscpp
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES rosbag_first
#  CATKIN_DEPENDS rosbag roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(rosbag_first src/main.cpp)
target_link_libraries(rosbag_first ${catkin_LIBRARIES})
