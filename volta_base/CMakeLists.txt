cmake_minimum_required(VERSION 2.8.3)
project(volta_base)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  rosserial_python
  sensor_msgs
  std_msgs
  tf
  controller_manager
  hardware_interface
  diagnostic_updater
  diff_drive_controller
  robot_pose_publisher
)

catkin_package(
)
include_directories(${catkin_INCLUDE_DIRS})
set_directory_properties(PROPERTIES COMPILE_OPTIONS "-std=c++11;")
