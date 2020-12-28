cmake_minimum_required(VERSION 2.8.3)
project(volta_msgs)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  std_msgs
)

add_message_files(
  DIRECTORY msg
  FILES
  RPM.msg
  Diagnostics.msg
  Table.msg
  BMS.msg
  )

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
)

