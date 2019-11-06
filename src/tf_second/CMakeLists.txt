cmake_minimum_required(VERSION 2.8.3)
project(tf_second)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  tf
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(tf_second src/main.cpp)
target_link_libraries(tf_second ${catkin_LIBRARIES})
