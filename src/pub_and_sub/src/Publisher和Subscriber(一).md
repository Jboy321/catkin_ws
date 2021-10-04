<!--
 * @Author: Zhoushenshen
 * @Date: 2021-10-02 21:08:54
 * @LastEditors: Zhoushenshen
 * @LastEditTime: 2021-10-02 22:24:56
 * @Description: 
 * @Company: xxxxxx
 * @Email: zhoushenshen@todo.com
-->
1、Publisher
下面写一个最简单的publisher(发布器)，我们让发布器发布从1开始递增的整数，频率为1Hz，代码如下：
#include <iostream>
#include <thread>
#include <chrono>

#include <ros/ros.h>
#include <std_msgs/Int32.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "easy_publisher");
    ros::NodeHandle nh;

    ros::Publisher easy_pub = nh.advertise<std_msgs::Int32>("topic1", 1);

    std_msgs::Int32 output;
    output.data = 1;

    while (ros::ok())
    {
        easy_pub.publish(output);
        ++output.data;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
运行上面的publisher代码，使用rostopic echo /topic1查看输出的消息，输出如下：
data: 2
---
data: 3
---
data: 4
---
data: 5
---
data: 6
---
我们发现程序里并未使用ros::spinOnce()，这说明Publisher的机制对spin机制没有依赖性，因为很多的例子中都用了ros::spinOnce()，可能会导致误解，认为Publisher也需要搭配ros::spin()或者ros::spinOnce()使用，两者并不存在依赖关系。
同时我们发现接收到的第一个消息是2，并不是1，这就是advertise()的一个使用陷阱，advertise()包含了第三个参数:bool latch = false，此参数为默认参数，默认为false，意思是与一个订阅器连接上后，不会保留上一次的数据，我们把这个默认参数显式传递true，同时使用ros::Rate来间隔循环，具体代码如下:
int main(int argc, char** argv)
{
    ros::init(argc, argv, "easy_publisher");
    ros::NodeHandle nh;

    ros::Publisher easy_pub = nh.advertise<std_msgs::Int32>("topic1", 1, true);

    std_msgs::Int32 output;
    output.data = 1;

    ros::Rate naptime(1.0);
    while (ros::ok())
    {
        easy_pub.publish(output);
        ++output.data;
        naptime.sleep();
    }
}
运行上述代码后使用rostopic echo查看，结果如下:
data: 1
---
data: 2
---
data: 3
---
data: 4
---
data: 5
---
当然，如果发布的频率较高，我们仍然会漏掉初始数据，这就对subscriber的队列的size有要求，后续再讨论。
实际上，当每次调用publish()接口时，会往Publisher Queue(发布器队列)插入一次数据，与此同时，会有一个额外的线程publisher thread负责去队列中取出数据并发送，具体流程如下图所示：
xxxxxxx
需要注意的是，每个publisher都会有一个自己的队列，这个队列的size就是advertise()的第二个参数，那么问题来了，如果我调用publish()的频率比Publisher Thread处理的频率高，那么就会有数据被冲掉，我们可以把循环间隔naptime.sleep()去掉，队列的size保持为1，运行后使用rostopic echo查看结果为:
data: 515539
---
data: 515552
---
data: 515553
---
data: 515581
---
data: 515582
---
data: 515608
---
data: 515609
---
data: 515629
---
可以观察到，发送的数据有丢失的情况，当然我们可以通过多线程的方式来优化，至于ros的多线程我们放在在subscriber中做详细讨论。
2、Subscriber
