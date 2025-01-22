#!/bin/bash


# Set ROS environment variables
export ROS_MASTER_URI=http://192.168.1.60:11311
export ROS_IP=192.168.1.64
rostopic echo /sensors_data
