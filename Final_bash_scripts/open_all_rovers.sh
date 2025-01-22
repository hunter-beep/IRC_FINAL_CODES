#!/bin/bash

# Open tabs 1, 2, 3 in the same terminal window
gnome-terminal --tab -- bash -c "./run_rover_1.bash > /dev/null 2>&1; exec bash"
sleep 2
gnome-terminal --tab -- bash -c "./run_rover_2.bash > /dev/null 2>&1; exec bash"
sleep 2
gnome-terminal -- bash -c "./run_rover_3.bash > /dev/null 2>&1; exec bash"
sleep 2

# Open 4th and 5th in separate terminal windows
gnome-terminal -- bash -c "./run_rover_4.bash > /dev/null 2>&1; exec bash"
sleep 2
gnome-terminal -- bash -c "./run_rover_5.bash > /dev/null 2>&1; exec bash"
sleep 2
gnome-terminal -- bash -c "./run_rover_6.bash > /dev/null 2>&1; exec bash"
sleep 2

# Open tabs 6 and 7 in the same terminal window
gnome-terminal --tab -- bash -c "./run_rover_7.bash > /dev/null 2>&1; exec bash"
sleep 2
gnome-terminal --tab -- bash -c "./run_rover_8.bash > /dev/null 2>&1; exec bash"
sleep 2

# Open 8, 9, and 10 in the same windows
for i in {9..13}
do
    gnome-terminal --tab -- bash -c "./run_rover_$i.bash > /dev/null 2>&1; exec bash"
    sleep 2
done
