/*** 
 * @Author: Zhoushenshen
 * @Date: 2021-05-02 14:17:03
 * @LastEditors: Zhoushenshen
 * @LastEditTime: 2021-09-25 22:44:21
 * @Description: 
 * @Company: idriverplus
 * @Email: zhoushenshen@idriverplus.com
 */
#include <ros/ros.h>
#include <std_msgs/Float64.h>

#include <iostream>
#include <thread>
#include <mutex>

static std::mutex cout_mutex;

void TimerCallback1(const ros::TimerEvent& event)
{
    std::lock_guard<std::mutex> locker(cout_mutex);
    std::cout << "TimerCallback1 thread id is " << std::this_thread::get_id() << std::endl;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_minimal_publisher");
    ros::NodeHandle nh;
    ros::Publisher my_publisher_object = nh.advertise<std_msgs::Float64>("topic1", 1);

    std_msgs::Float64 input_float;
    input_float.data = 0.0;
    ros::Rate naptime(1.0);

    ros::Timer timer1 = nh.createTimer(ros::Duration(1.0), TimerCallback1);
    ros::Timer timer2 = nh.createTimer(ros::Duration(1.0), TimerCallback1);

    int i = 0;

    ros::MultiThreadedSpinner ms(2);
    ros::AsyncSpinner as(2);
    std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
    as.start();

    while (ros::ok())
    {
        naptime.sleep();
    }
    // while (ros::ok())
    // {
    //     std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
    //     //ros::spin(ms);
    //     // my_publisher_object.publish(input_float);
    //     // i++;
    //     // input_float.data += 0.1;
    //     // naptime.sleep();
    // }

    //下面一段代码说明个问题，if中用data1作判断能正常打印到0.9，而用input_float来做判断时竟然能打印到1。
    //没搞明白之前，判断或循环里用自定义的局部变量，不要用ROS的变量类型
   
    // float data1 = 0.0;

    // while(1)
    // {
    //     if (data1 < 1)
    //     {
            
    //         data1 += 0.1;
    //         input_float.data += 0.1;
    //         // my_publisher_object.publish(input_float);
    //         std::cout << "data1:" << data1 << std::endl;
    //         std::cout << "input_float:" << input_float.data << std::endl;
    //         sleep(1);
    //     }
    //     else
    //     {
    //         break;
    //     }    
    // }
    ///犯了致命错误，一般不会拿浮点数做循环判断，因为浮点数没法精确表示0.1/0.01这些，误差原因会导致可能多循环一次
    ///此列中如果用float32数来判断就不会出现多循环一次的问题，所以以后只能拿整数做循环判断。

    

}
