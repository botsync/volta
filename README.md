# Volta

# To Do

- [ ] ROS Control Test on physical robot
- [ ] Odometry Test on Physical Robot
- [ ] PID control tuning
- [ ] IMU Test
- [ ] LIDAR Test
- [ ] Camera Test
- [ ] Configure On Board PC
- [ ] Localization Test
- [ ] Mapping Test
- [ ] Update Instructions in README.md
- [ ] Create  base package for public repo
- [ ] Code Review (Nikhil Venkatesh)
- [ ] Publish Public Repo (Nikhil Venkatesh)

## Optimization

- [ ] Contoller and Interface Board Update - reduce number of wires, add programming switch, add DB9 connector
- [ ] Change serial library for latency reduction

# Running the Simulation

## Bringing up the simulation
1. To run in Simulation, launch the gazebo node first using
```roslaunch volta_description gazebo.launch```
2. Followed by:
```roslaunch volta_description simulation.launch```
3. Open Rviz and use the config file at volta_navigation/rviz_config/navigation.rviz to visualize.

By default a map of the simulation environment has been built and stored for convenience sake. 

## Mapping the environment 
To change the environment in the simulation, update the argument in the gazebo.launch file with the exact path to the world file.

You will need to run mapping. You can simply use the argument in one_robot.launch to turn gmapping true.
```roslaunch volta_description one_robot.launch gmapping:=true```

To visualize the map updations, use rviz and open this config volta_navigation/rviz_config/navigation.rviz.

To save the map, run ```rosrun map_server map_saver```

# Running Online

## Bringing up the robot
1. ```roslaunch volta_base volta_bringup.launch```
2. ```roslaunch volta_base volta_base.launch```

These two commands will bringup the robot for teleoperation and start the odometry filter as well. In order to visualize the robot, use rviz.

## Mapping an Environment
1. ```roslaunch volta_navigation navigation.launch gmapping:=true```

This command should start mapping the environment. To visualize the map, use rviz. Open the configuration, volta_navigation/rviz_config/navigation.rviz.

Once the mapping process is completed, save the map by running the following command.
1. ```rosrun map_server map_saver```

## Running Navigation
Before you can navigate without gmapping running, you will need to have a saved map. 
Edit the map file argument with the path to the exact map file.

1. ```roslaunch volta_navigation navigation.launch```

To visualize the navigation, use rviz. Open the configuration, volta_navigation/rviz_config/navigation.rviz.
