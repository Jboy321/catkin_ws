/*** 
 * @Author: Zhoushenshen
 * @Date: 2021-05-02 14:17:03
 * @LastEditors: Zhoushenshen
 * @LastEditTime: 2021-09-30 00:40:17
 * @Description: 
 * @Company: xxxxxx
 * @Email: zhoushenshen@todo.com
 */

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <iostream>
#include <thread>
#include <mutex>

static std::mutex cout_mutex;
void MyCallback1(const std_msgs::Int32& message)
{
    // std::lock_guard<std::mutex> locker(cout_mutex);
    // //ROS_INFO("Callback1 received value is :%f", message.data);
    // std::cout << "Callback1 received value is " << message.data << std::endl;
    // std::cout << "Callback1 thread is " << std::this_thread::get_id() << std::endl;

    std::cout << "Callback1 received value is " << message.data << std::endl;
    std::cout << "Callback1 thread is " << std::this_thread::get_id() << std::endl;
    std::cout << "Callback1 time is " << ros::Time::now().toSec() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

void MyCallback2(const std_msgs::Int32& message)
{
    // std::lock_guard<std::mutex> locker(cout_mutex);
    // //ROS_INFO("Callback2 received value is :%f", message.data);
    // std::cout << "Callback2 received value is " << message.data << std::endl;
    // std::cout << "Callback2 thread is " << std::this_thread::get_id() << std::endl;

    std::cout << "Callback2 received value is " << message.data << std::endl;
    std::cout << "Callback2 thread is " << std::this_thread::get_id() << std::endl;
    std::cout << "Callback2 time is " << ros::Time::now().toSec() << std::endl;
    // std::this_thread::sleep_for(std::chrono::seconds(10));
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
    // ros::Subscriber my_subscriber_object1 = n.subscribe("topic1", 1, MyCallback1);
    // ros::Subscriber my_subscriber_object2 = n.subscribe("topic1", 1, MyCallback2);
    // ros::Subscriber my_subscriber_object3 = n.subscribe("topic1", 1, MyCallback3);
    // ros::Subscriber my_subscriber_object4 = n.subscribe("topic1", 1, MyCallback4);
    // ros::Subscriber my_subscriber_object5 = n.subscribe("topic1", 1, MyCallback5);
    // ros::Subscriber my_subscriber_object6 = n.subscribe("topic1", 1, MyCallback6);

    ros::Subscriber easy_subscriber1 = n.subscribe("easy_topic1", 1, MyCallback1);
    ros::Subscriber easy_subscriber2 = n.subscribe("easy_topic2", 1, MyCallback2);
    
    // ros::Rate rate(1.0);

    // ros::MultiThreadedSpinner ms(6);   //或者不指定线程数，使用默认最大硬件并发线程数： ros::MultiThreadedSpinner ms;
    // std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
    // ms.spin();  //ros::spin(ms);
    // ros::AsyncSpinner as(6);    //必须指定线程数
    // std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
    // std::cout.precision(10);
    // std::cout << "Main thread time is " << ros::Time::now().toSec() << std::endl;

    // as.start();
    // ros::waitForShutdown();
    ros::spin();
    // while (ros::ok())
    // {
        
    //     // std::cout << "====================" << std::endl;
    //     // ros::spin(s);
    //     ros::spinOnce();
    //     rate.sleep();
    // }
    
    return 0;
}