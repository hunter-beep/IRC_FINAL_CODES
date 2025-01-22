#!/bin/bash


export ROS_MASTER_URI=http://192.168.1.60:11311;
export ROS_IP=192.168.1.64;
cd ~/joystick_final_steer;
rm -rf build;
catkin_make;
source devel/setup.bash;
rosrun teleop_twist_joy explore



