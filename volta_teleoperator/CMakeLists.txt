cmake_minimum_required(VERSION 2.8.3)
project(volta_teleoperator)

find_package(catkin REQUIRED COMPONENTS
  teleop_twist_joy
  teleop_twist_keyboard
  sensor_msgs
  geometry_msgs
  volta_msgs
  actionlib_msgs
)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    joy_teleop
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)

add_library(volta_joy_teleop src/joy_teleop.cpp)
add_dependencies(volta_joy_teleop volta_teleoperator_gencpp)
add_executable(volta_joy_teleop_node src/joy_teleop_node.cpp)
target_link_libraries(volta_joy_teleop_node volta_joy_teleop ${catkin_LIBRARIES})

add_executable(ackermann_joy_teleop src/ackermann_joy_teleop.cpp)
target_link_libraries(ackermann_joy_teleop ${catkin_LIBRARIES})
