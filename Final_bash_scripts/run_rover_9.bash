#!/bin/bash

# Use sshpass to provide the password and SSH into the remote machine with X11 forwarding

export ROS_MASTER_URI=http://192.168.1.60:11311
export ROS_IP=192.168.1.64
rqt_image_view /zed2i/zed_node/rgb_raw/image_raw_color/compressed

