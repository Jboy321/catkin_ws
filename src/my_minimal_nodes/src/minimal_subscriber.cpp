/*** 
 * @Author: Zhoushenshen
 * @Date: 2021-05-02 14:17:03
 * @LastEditors: Zhoushenshen
 * @LastEditTime: 2021-09-25 22:24:38
 * @Description: 
 * @Company: idriverplus
 * @Email: zhoushenshen@idriverplus.com
 */
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <thread>
#include <mutex>

static std::mutex cout_mutex;
void MyCallback1(const std_msgs::Float64& message)
{
    std::lock_guard<std::mutex> locker(cout_mutex);
    //ROS_INFO("Callback1 received value is :%f", message.data);
    std::cout << "Callback1 received value is " << message.data << std::endl;
    std::cout << "Callback1 thread is " << std::this_thread::get_id() << std::endl;
}

void MyCallback2(const std_msgs::Float64& message)
{
    std::lock_guard<std::mutex> locker(cout_mutex);
    //ROS_INFO("Callback2 received value is :%f", message.data);
    std::cout << "Callback2 received value is " << message.data << std::endl;
    std::cout << "Callback2 thread is " << std::this_thread::get_id() << std::endl;
}

void MyCallback3(const std_msgs::Float64& message)
{
    std::lock_guard<std::mutex> locker(cout_mutex);
    //ROS_INFO("Callback3 received value is :%f", message.data);
    std::cout << "Callback3 received value is " << message.data << std::endl;
    std::cout << "Callback3 thread is " << std::this_thread::get_id() << std::endl;
}

void MyCallback4(const std_msgs::Float64& message)
{
    std::lock_guard<std::mutex> locker(cout_mutex);
    //ROS_INFO("Callback3 received value is :%f", message.data);
    std::cout << "Callback4 received value is " << message.data << std::endl;
    std::cout << "Callback4 thread is " << std::this_thread::get_id() << std::endl;
}

void MyCallback5(const std_msgs::Float64& message)
{
    std::lock_guard<std::mutex> locker(cout_mutex);
    //ROS_INFO("Callback3 received value is :%f", message.data);
    std::cout << "Callback5 received value is " << message.data << std::endl;
    std::cout << "Callback5 thread is " << std::this_thread::get_id() << std::endl;
}

void MyCallback6(const std_msgs::Float64& message)
{
    std::lock_guard<std::mutex> locker(cout_mutex);
    //ROS_INFO("Callback3 received value is :%f", message.data);
    std::cout << "Callback6 received value is " << message.data << std::endl;
    std::cout << "Callback6 thread is " << std::this_thread::get_id() << std::endl;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "my_minimal_subscriber");
    ros::NodeHandle n;
    ros::Subscriber my_subscriber_object1 = n.subscribe("topic1", 1, MyCallback1);
    ros::Subscriber my_subscriber_object2 = n.subscribe("topic1", 1, MyCallback2);
    ros::Subscriber my_subscriber_object3 = n.subscribe("topic1", 1, MyCallback3);
    ros::Subscriber my_subscriber_object4 = n.subscribe("topic1", 1, MyCallback4);
    ros::Subscriber my_subscriber_object5 = n.subscribe("topic1", 1, MyCallback5);
    ros::Subscriber my_subscriber_object6 = n.subscribe("topic1", 1, MyCallback6);
    ros::Rate rate(1.0);

    ros::MultiThreadedSpinner s(2);
    
    while (ros::ok())
    {
        std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
        std::cout << "====================" << std::endl;
        ros::spin(s);
    }
    //ros::spin();
    return 0;
}