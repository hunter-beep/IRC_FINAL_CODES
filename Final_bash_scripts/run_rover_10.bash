#!/bin/bash


export ROS_MASTER_URI=http://192.168.1.60:11311
export ROS_IP=192.168.1.64
rqt_image_view /usb_cam_0/image_raw/compressed

