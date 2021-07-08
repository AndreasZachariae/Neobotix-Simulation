/** *******************************************************
 * PeTRA - University of Applied Sciences Karlsruhe
 * Module : ROS1-Node "StopBridge"
 * Purpose : Converts topic "Stop" to "move_base/cancel"
 *
 * @author Andreas Zachariae
 * @since 1.0.0 (2020.08.26)
 *********************************************************/
#include <iostream>
#include <ros/ros.h>

#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>
#include <actionlib_msgs/GoalID.h>
#include <move_base_msgs/MoveBaseActionResult.h>
#include <move_base_msgs/MoveBaseActionFeedback.h>
#include <geometry_msgs/PoseStamped.h>

class StopBridge
{
public:
    StopBridge(ros::NodeHandle n);

private:
    ros::NodeHandle handle_;
    ros::Publisher action_cancel_pub_ = handle_.advertise<actionlib_msgs::GoalID>("move_base/cancel", 1000);
    ros::Publisher result_status_pub_ = handle_.advertise<std_msgs::UInt8>("nav/result_status", 1000);
    ros::Publisher current_position_pub_ = handle_.advertise<geometry_msgs::PoseStamped>("nav/current_position", 1000);
    ros::Subscriber stop_sub_ = handle_.subscribe("Stop", 1000, &StopBridge::stop_callback_, this);
    ros::Subscriber action_result_sub_ = handle_.subscribe("move_base/result", 1000, &StopBridge::action_result_callback_, this);
    ros::Subscriber action_feedback_sub_ = handle_.subscribe("move_base/feedback", 1000, &StopBridge::action_feedback_callback_, this);

    void stop_callback_(const std_msgs::Empty::ConstPtr &msg);
    void action_result_callback_(const move_base_msgs::MoveBaseActionResult::ConstPtr &msg);
    void action_feedback_callback_(const move_base_msgs::MoveBaseActionFeedback::ConstPtr &msg);
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

    action_cancel_pub_.publish(cancel);
}

void StopBridge::action_result_callback_(const move_base_msgs::MoveBaseActionResult::ConstPtr &msg)
{
    ROS_INFO("Navigation action result recieved, publishing nav/result_status");

    std_msgs::UInt8 status;
    status.data = msg->status.status;

    result_status_pub_.publish(status);
}

void StopBridge::action_feedback_callback_(const move_base_msgs::MoveBaseActionFeedback::ConstPtr &msg)
{
    (void)msg;

    // ROS_INFO("Navigation action feedback recieved, publishing nav/current_position");

    geometry_msgs::PoseStamped current_position;
    current_position = msg->feedback.base_position;

    current_position_pub_.publish(current_position);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "stop_bridge");

    ros::NodeHandle n;

    StopBridge sb = StopBridge(n);

    ros::spin();

    return 0;
}