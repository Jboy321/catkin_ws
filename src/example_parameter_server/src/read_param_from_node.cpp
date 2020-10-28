#include <ros/ros.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "param_reader");
    ros::NodeHandle n;

    double P_gain, I_gain, D_gain;

    if (n.getParam("/joint1_gains/p", P_gain))
    {
        ROS_INFO("proportional gain P set to %f", P_gain);
    }
    else
    {
        ROS_WARN("could not find parameter value /joint1_gains/p on parameter server!");
    }
    if (n.getParam("/joint1_gains/i", I_gain))
    {
        ROS_INFO("proportional gain I set to %f", I_gain);
    }
    else
    {
        ROS_WARN("could not find parameter value /joint1_gains/i on parameter server!");
    }
    if (n.getParam("/joint1_gains/d", D_gain))
    {
        ROS_INFO("proportional gain D set to %f", D_gain);
    }
    else
    {
        ROS_WARN("could not find parameter value /joint1_gains/d on parameter server!");
    }
    
}