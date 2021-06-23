cmake_minimum_required(VERSION 3.0.2)
project(volta_localization)

add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  robot_localization
)

catkin_package(
)

install(
  DIRECTORY config launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
