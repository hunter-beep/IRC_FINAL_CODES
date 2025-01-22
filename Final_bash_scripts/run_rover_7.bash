#!/bin/bash
set -m
trap "kill -- -$$" SIGHUP
# SSH into the remote machine and run the commands
sshpass -p "mars140420" ssh -C -X orinmars@192.168.1.60 "bash --login -c '
export ROS_MASTER_URI=http://192.168.1.60:11311;
export ROS_IP=192.168.1.60;
pkill zed2i.launch
cd ~/zed_ws;
source devel/setup.bash;
roslaunch zed_wrapper zed2i.launch'"
wait


