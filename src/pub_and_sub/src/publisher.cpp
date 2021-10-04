/*** 
 * @Author: Zhoushenshen
 * @Date: 2021-10-02 21:07:38
 * @LastEditors: Zhoushenshen
 * @LastEditTime: 2021-10-02 22:18:55
 * @Description: 
 * @Company: xxxxxx
 * @Email: zhoushenshen@todo.com
 */
#include <iostream>
#include <thread>
#include <chrono>

#include <ros/ros.h>
#include <std_msgs/Int32.h>

// int main(int argc, char** argv)
// {
//     ros::init(argc, argv, "easy_publisher");
//     ros::NodeHandle nh;

//     ros::Publisher easy_pub = nh.advertise<std_msgs::Int32>("topic1", 1);

//     std_msgs::Int32 output;
//     output.data = 1;

//     while (ros::ok())
//     {
//         easy_pub.publish(output);
//         ++output.data;
//         std::this_thread::sleep_for(std::chrono::seconds(1));
//     }
// }

int main(int argc, char** argv)
{
    ros::init(argc, argv, "easy_publisher");
    ros::NodeHandle nh;

    ros::Publisher easy_pub = nh.advertise<std_msgs::Int32>("topic1", 1, true);

    std_msgs::Int32 output;
    output.data = 1;

    ros::Rate naptime(1000.0);
    while (ros::ok())
    {
        easy_pub.publish(output);
        ++output.data;
        //naptime.sleep();
    }
}