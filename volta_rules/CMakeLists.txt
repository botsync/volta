cmake_minimum_required(VERSION 2.8.3)
project(volta_rules)

find_package(catkin REQUIRED COMPONENTS

)

catkin_package(
  CATKIN_DEPENDS
)

install(PROGRAMS
        create_udev_rules
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

catkin_install_python(PROGRAMS sensor_read.py
        DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(FILES
        udev_rules.rules
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)