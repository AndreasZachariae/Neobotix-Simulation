# Neobotix simulation mmo-500

source /opt/ros/dashing/setup.bash

source ~/neobotix_ws/devel/setup.bash

roslaunch neo_simulation simulation.launch

roslaunch neo_simulation mmo_500_amcl.launch

roslaunch neo_simulation mmo_500_move_base.launch

# ROS1/2 bridge

source /opt/ros/melodic/setup.bash

source /opt/ros/dashing/setup.bash 

export ROS_MASTER_URI=http://localhost:11311

ros2 run ros1_bridge dynamic_bridge
