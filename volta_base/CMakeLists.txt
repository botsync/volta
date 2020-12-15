cmake_minimum_required(VERSION 2.8.3)
project(volta_base)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
)

catkin_package()

set_directory_properties(PROPERTIES COMPILE_OPTIONS "-std=c++11;")

install(
  DIRECTORY launch config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
