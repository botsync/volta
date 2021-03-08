# Volta
Version:1.1.0
ROS packages used to to run volta with hardware

* volta_base - Package contains files to connect to the robot and run the sensor driver.
* volta_control - Control configuration required for ROS control.
* volta_description - Volta Robot description (URDF files).
* volta_localization - Sensor fusion of wheel odometry and IMU data using the robot localization package.
* volta_msgs - contains ROS messages specific to volta such as the power board messages,..etc
* volta_navigation - Contains files required for running gmapping, amcl and move_base ROS packages.
* volta_teleoperation - Control the robot using keyboard or Joystick.
* volta_rules - Contains rules that ensures the USB peripherals are binded correctly

## Steps to Launch Volta :

### 1. Mapping an environment with Volta
* Launch the move_base node by running:   
```
$ roslaunch volta_base bringup.launch   
```
* Launch the sensors node by running:    
```
$ roslaunch volta_base sensors.launch   
```
* To perform the mapping, launch the navigation package by running   
```
$ roslaunch volta_navigation navigation.launch gmapping:=true  
```
* Launch the rviz visualization tool by running:   
```
$ rosrun rviz rviz  
```
You can then open the volta configured rviz environment by opening the volta rviz config file, located under volta_navigation->rviz_config->navigation.rviz, from the rviz tool

* In order to control the robot, launch the teleoperation node by running:     
```
$ roslaunch volta_teleoperator teleoperator.launch keyboard:=true
```

* Once the mapping of the entire environment is completed, the map can be saved by running:     
```
$ rosrun map_server map_saver –f <filename>
```

### 3. Navigation with Volta
* Launch the move_base node by running:   
```
$ roslaunch volta_base bringup.launch   
```
* Launch the sensors node by running:    
```
$ roslaunch volta_base bringup.launch   
```
* To perform the Autonomous navigation, launch the navigation package by running   
```
$ roslaunch volta_navigation navigation.launch  
```
* Launch the rviz visualization tool by running:   
```
$ rosrun rviz rviz  
```
You can then open the volta configured rviz environment by opening the volta rviz config file, located under volta_navigation->rviz_config->navigation.rviz, from the rviz tool

Use the 2D Nav Goal tool in the top toolbar to select a navigation goal in the visualizer. Ensure that the nav goal is given in a mapped section of the map
