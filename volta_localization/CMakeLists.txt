cmake_minimum_required(VERSION 2.8.3)
project(volta_localization)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  robot_localization
)

catkin_package(
)

install(
  DIRECTORY config launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
