cmake_minimum_required(VERSION 2.8.3)
project(volta_description)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

install(
  DIRECTORY launch meshes rviz_params urdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
