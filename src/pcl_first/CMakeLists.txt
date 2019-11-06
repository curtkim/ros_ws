cmake_minimum_required(VERSION 2.8.3)
project(pcl_first)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS
  pcl_conversions
  pcl_ros
  rosbag
  roscpp
  std_msgs
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(pcl_first src/pcl_point_cloud2.cpp)
target_link_libraries(pcl_first ${catkin_LIBRARIES})

add_executable(pcl_point_cloud_t src/pcl_point_cloud_t.cpp)
target_link_libraries(pcl_point_cloud_t ${catkin_LIBRARIES})

add_executable(downsample src/downsample.cpp)
target_link_libraries(downsample ${catkin_LIBRARIES})

#configure_file(<input> <output> COPYONLY)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/table_scene_lms400.pcd DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
