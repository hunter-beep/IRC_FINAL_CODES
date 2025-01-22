#!/bin/bash

sshpass -p "mars140420" ssh -C -t orinmars@192.168.1.60 "bash --login -c '
source /opt/ros/noetic/setup.bash;
export ROS_MASTER_URI=http://192.168.1.60:11311;
export ROS_IP=192.168.1.60;
killall -f roscore
sleep 2
roscore'"


