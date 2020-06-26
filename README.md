#Neobotix simulation mmo-500

source /opt/ros/dashing/setup.bash

source ~/neobotix_ws/devel/setup.bash

roslaunch neo_simulation simulation.launch

roslaunch neo_simulation mmo_500_amcl.launch

roslaunch neo_simulation mmo_500_move_base.launch
