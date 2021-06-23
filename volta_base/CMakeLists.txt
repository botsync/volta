cmake_minimum_required(VERSION 3.0.2)
project(volta_base)

add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
)

catkin_package()

set_directory_properties(PROPERTIES COMPILE_OPTIONS "-std=c++14;")

install(
  DIRECTORY launch config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
