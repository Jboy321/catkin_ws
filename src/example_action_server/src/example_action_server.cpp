#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include "example_action_server/demoAction.h"

static int g_count = 0;
static bool g_count_failure = false;

class ExampleActionServer
{
private:
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<example_action_server::demoAction> as_;
    example_action_server::demoGoal goal_;
    example_action_server::demoResult result_;
    example_action_server::demoFeedback feedback_;

public:
    ExampleActionServer()
    : as_(nh_, "example_action", boost::bind(&ExampleActionServer::executeCB, this, _1), false)
    {
        ROS_INFO("in constructor of ExampleActionServer...");
        as_.start();
    }

    ~ExampleActionServer()
    {

    }

    void executeCB(const actionlib::SimpleActionServer<example_action_server::demoAction>::GoalConstPtr& goal)
    {
        ROS_INFO("123");
        g_count++;
        result_.output = g_count;
        result_.goal_stamp = goal->input;

        if (g_count != goal->input)
        {
            ROS_WARN("hey--mismatch!");
            ROS_INFO("g_count = %d; goal_stamp = %d", g_count, result_.goal_stamp);
            g_count_failure = true;
            ROS_WARN("informing client of aborted goal");
            as_.setAborted(result_);
        }
        else
        {
            as_.setSucceeded(result_);
        }
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "demo_action_server_node");

    ROS_INFO("instantiating the demo action server: ");

    ExampleActionServer as_object;
    
    ROS_INFO("going into spin");

    // while(!g_count_failure)
    // {
    //     ros::spinOnce();
    // } //这种写法不好，首先是启动服务器后会因为一直调用spinOnce导致占用大量资源，二是终端上无法退出程序，只能去资源管理器上关闭进程

    if (g_count_failure)
    {
        return 0;
    }
    ros::spin();

    // do
    // {
    //     ros::spinOnce();
    // }
    // while(!g_count_failure);

}