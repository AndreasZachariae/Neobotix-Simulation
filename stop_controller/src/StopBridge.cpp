#include <ros/ros.h>

#include <std_msgs/Empty.h>
#include <actionlib_msgs/GoalID.h>

class StopBridge
{
private:
    ros::NodeHandle handle_;
    ros::Publisher cancel_action_pub_ = handle_.advertise<actionlib_msgs::GoalID>("move_base/cancel", 1000);
    ros::Subscriber stop_sub_ = handle_.subscribe("Stop", 1000, &StopBridge::stop_callback_, this);

    void stop_callback_(const std_msgs::Empty::ConstPtr &msg);

public:
    StopBridge(ros::NodeHandle n);

};

StopBridge::StopBridge(ros::NodeHandle n) : handle_(n)
{
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