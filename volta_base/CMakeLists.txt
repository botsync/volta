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
  um7
  imu_transformer
  imu_filter_madgwick
  laser_filters
  controller_manager
  diagnostic_updater
  robot_pose_publisher
  volta_msgs
)

catkin_package(
INCLUDE_DIRS
CATKIN_DEPENDS hardware_interface volta_msgs roscpp sensor_msgs
DEPENDS Boost )

include_directories(include ${Boost_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})
set_directory_properties(PROPERTIES COMPILE_OPTIONS "-std=c++11;")


install(
  DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
