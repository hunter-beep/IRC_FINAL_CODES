#!/bin/bash


# Set ROS environment variables
export ROS_MASTER_URI=http://192.168.1.60:11311
export ROS_IP=192.168.1.64

# Navigate to the joystick directory
cd ~/joystick_new_science || { echo "Directory ~/joystick does not exist. Exiting."; exit 1; }

# Clean and build the workspace
rm -rf build
catkin_make

# Source the workspace setup
source devel/setup.bash

# Launch the teleop node
roslaunch teleop_twist_joy teleop.launch

