/** *******************************************************
 * PeTRA - University of Applied Sciences Karlsruhe
 * Module : ROS1-Node "StopBridge"
 * Purpose : Converts topic "Stop" to "move_base/cancel"
 *
 * @author Moritz Weisenböhler
 * @author Andreas Zachariae
 * @since 1.0.0 (2020.08.26)
 *********************************************************/
#include <ros/ros.h>

#include <std_msgs/Empty.h>
#include <actionlib_msgs/GoalID.h>

class StopBridge
{
public:
    StopBridge(ros::NodeHandle n);

private:
    ros::NodeHandle handle_;
    ros::Publisher cancel_action_pub_ = handle_.advertise<actionlib_msgs::GoalID>("move_base/cancel", 1000);
    ros::Subscriber stop_sub_ = handle_.subscribe("Stop", 1000, &StopBridge::stop_callback_, this);

    void stop_callback_(const std_msgs::Empty::ConstPtr &msg);
};

StopBridge::StopBridge(ros::NodeHandle n) : handle_(n)
{
    ROS_INFO("StopBridge active, bridging /Stop to /move_base/cancel");
}

void StopBridge::stop_callback_(const std_msgs::Empty::ConstPtr &msg)
{
    (void)msg;

    ROS_INFO("Stop recieved, publishing move_base/cancel");

    actionlib_msgs::GoalID cancel;

    cancel_action_pub_.publish(cancel);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "stop_bridge");

    ros::NodeHandle n;

    StopBridge sb = StopBridge(n);

    ros::spin();

    return 0;
}