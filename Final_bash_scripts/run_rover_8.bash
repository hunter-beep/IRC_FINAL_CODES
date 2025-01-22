#!/bin/bash


# Use sshpass to provide the password and SSH into the remote machine with X11 forwarding
sshpass -p "mars140420" ssh -C -X orinmars@192.168.1.60 "bash --login -c '
export ROS_MASTER_URI=http://192.168.1.60:11311;
export ROS_IP=192.168.1.60;
cd ~/dual_webcam/src/dual_webcam/launch;
pkill -f dual_webcam.launch
sleep 2
./la.sh'"


