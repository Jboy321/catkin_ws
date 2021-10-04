<!--
 * @Author: Zhoushenshen
 * @Date: 2021-09-26 23:01:01
 * @LastEditors: Zhoushenshen
 * @LastEditTime: 2021-09-30 00:50:45
 * @Description: 
 * @Company: xxxxxx
 * @Email: zhoushenshen@todo.com
-->
1、直接使用ros::spin和ros::spinOnce()并不会给回调函数创建单独线程，此时只是阻塞主线程，去执行全局队列上的收到的消息的回调函数，示例如下：
发布器publisher代码：
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <iostream>
#include <thread>
#include <mutex>

static std::mutex cout_mutex;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_minimal_publisher");
    ros::NodeHandle nh;
    ros::Publisher my_publisher_object = nh.advertise<std_msgs::Float64>("topic1", 1);

    std_msgs::Float64 input_float;
    input_float.data = 0.0;
    ros::Rate naptime(1.0);

    while (ros::ok())
    {
        my_publisher_object.publish(input_float);
        input_float.data += 0.1;
        naptime.sleep();
    }
}
订阅器subscriber代码：
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <iostream>
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

int main(int argc, char **argv)
{
    ros::init(argc, argv, "my_minimal_subscriber");
    ros::NodeHandle n;
    ros::Subscriber my_subscriber_object1 = n.subscribe("topic1", 1, MyCallback1);
    ros::Subscriber my_subscriber_object2 = n.subscribe("topic1", 1, MyCallback2);
    ros::Subscriber my_subscriber_object3 = n.subscribe("topic1", 1, MyCallback3);

    ros::Rate rate(1.0);

    std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
    //或者直接使用ros::spin();
    while (ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
    }
}
上述代码运行结果：
Main thread id is 139797149267840
Callback1 received value is 0.1
Callback1 thread is 139797149267840
Callback2 received value is 0.1
Callback2 thread is 139797149267840
Callback3 received value is 0.1
Callback3 thread is 139797149267840
Callback1 received value is 0.2
Callback1 thread is 139797149267840
Callback2 received value is 0.2
Callback2 thread is 139797149267840
Callback3 received value is 0.2
Callback3 thread is 139797149267840
Callback1 received value is 0.3
Callback1 thread is 139797149267840
Callback2 received value is 0.3
Callback2 thread is 139797149267840
Callback3 received value is 0.3
Callback3 thread is 139797149267840
从结果中可以看到，回调函数的线程和主线程是一个，并没有创建新线程，同时当有多个subscriber订阅同一个topic时，每一帧消息都会处触发当前所有的subscriber的回调函数。
2、使用ROS多线程ros::MultiThreadedSpinner,可以指定创建的线程数，不指定的话，默认取硬件最大并发线程，示例如下：
发布器publisher代码同上
订阅器subscriber代码：
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <iostream>
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

    ros::MultiThreadedSpinner ms(6);    //或者不指定线程数，使用默认最大硬件并发线程数： ros::MultiThreadedSpinner ms;
    std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
    ms.spin();      //也可以这样写ros::spin(ms);
}
上述代码运行结果：
Main thread id is 139685730576256
Callback1 received value is 0.1
Callback1 thread is 139685338797824
Callback3 received value is 0.1
Callback3 thread is 139685221365504
Callback4 received value is 0.1
Callback4 thread is 139685578131200
Callback5 received value is 0.1
Callback5 thread is 139685569738496
Callback2 received value is 0.1
Callback2 thread is 139685355583232
Callback6 received value is 0.1
Callback6 thread is 139685347190528
从结果中可以看到，主线程之外额外创建了6个线程，正好spin给每个subscriber都分配了一个线程，那如果只给了3个线程，怎么样呢，结果如下所示：
Main thread id is 140079605458816
Callback1 received value is 0.1
Callback1 thread is 140079453013760
Callback4 received value is 0.1
Callback4 thread is 140079453013760
Callback5 received value is 0.1
Callback5 thread is 140079453013760
Callback6 received value is 0.1
Callback6 thread is 140079453013760
Callback3 received value is 0.1
Callback3 thread is 140079444621056
Callback2 received value is 0.1
Callback2 thread is 140079436228352
Callback1 received value is 0.2
Callback1 thread is 140079453013760
Callback2 received value is 0.2
Callback2 thread is 140079444621056
Callback3 received value is 0.2
Callback3 thread is 140079436228352
Callback4 received value is 0.2
Callback4 thread is 140079453013760
Callback5 received value is 0.2
Callback5 thread is 140079444621056
Callback6 received value is 0.2
Callback6 thread is 140079436228352
从结果上看，线程的分配并不是依次分配的，看起来随机的，具体规律得去看源码。
3、使用ROS多线程ros::AsyncSpinner，AsyncSpinner必须指定要创建的线程数
发布器publisher代码同上
订阅器subscriber代码：
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


    ros::AsyncSpinner as(6);    //必须指定线程数
    std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
    as.start();
    ros::waitForShutdown();     //必须有阻塞等待的地方，不然程序直接结果
}
上述代码运行结果：
Main thread id is 140218784503680
Callback4 received value is 0.1
Callback4 thread is 140218623665920
Callback5 received value is 0.1
Callback5 thread is 140218632058624
Callback2 received value is 0.1
Callback2 thread is 140218615273216
Callback6 received value is 0.1
Callback6 thread is 140218267072256
Callback3 received value is 0.1
Callback3 thread is 140218132854528
Callback1 received value is 0.1
Callback1 thread is 140218258679552
从结果上和MultiThreadedSpinner一样，给各个subscriber都分配了一个线程，MultiThreadedSpinner类似创建一个thread,然后需要调用join方法(ros::spin)去阻塞执行子线程任务，而AsyncSpinner类似创建一个thread后直接调用detach方法，如果主线不wait的话就直接结束程序了，AsyncSpinner更好用一些，拥有start和stop方法，出作用域也会自动结束。
4、使用ROS的定时器ros::Timer
只需要发布器publisher代码：
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
    ros::Timer timer2 = nh.createTimer(ros::Duration(1.0), [&](const ros::TimerEvent& event){
        std::lock_guard<std::mutex> locker(cout_mutex);
        std::cout << "TimerCallback2 thread id is " << std::this_thread::get_id() << std::endl;
    });     //也可以使用lambda表达式

    std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;

    ros::spin();    //没有spin或者spinOnce就不会执行定时器了
}
上述代码运行结果：
Main thread id is 139752454231936
TimerCallback1 thread id is 139752454231936
TimerCallback2 thread id is 139752454231936
同样的，不使用ROS多线程方法的话，也不会创建新的线程，使用MultiThreadedSpinner或者AsyncSpinner才会创建新的线程，如下所示的代码修改：
int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_minimal_publisher");
    ros::NodeHandle nh;
    ros::Publisher my_publisher_object = nh.advertise<std_msgs::Float64>("topic1", 1);

    std_msgs::Float64 input_float;
    input_float.data = 0.0;
    ros::Rate naptime(1.0);

    ros::Timer timer1 = nh.createTimer(ros::Duration(1.0), TimerCallback1);
    ros::Timer timer2 = nh.createTimer(ros::Duration(1.0), [&](const ros::TimerEvent& event){
        std::lock_guard<std::mutex> locker(cout_mutex);
        std::cout << "TimerCallback2 thread id is " << std::this_thread::get_id() << std::endl;
    });     //也可以使用lambda表达式

    ros::AsyncSpinner as(2);
    std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
    as.start();
    ros::waitForShutdown();
}
运行结果为
Main thread id is 140041949087616
TimerCallback1 thread id is 140041779857152
TimerCallback2 thread id is 140041788249856

5、发现个Publisher的小技巧，ros::Publisher使用NodeHandle的advertise函数返回值赋值时，这个advertise是有三个参数的，第三个参数为默认参数bool latch = false，默认为false，当一个Subscriber和Publisher连接上时，Publisher发布的上一个消息不会保存，就会丢掉一个消息，平常不留意的现象，示例代码如下：
发布器Publisher代码：
#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Int32.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_minimal_publisher");
    ros::NodeHandle nh;
    ros::Publisher easy_pub1 = nh.advertise<std_msgs::Int32>("easy_topic1", 1);

    ros::Rate naptime(1.0);

    std_msgs::Int32 output;
    output.data = 1;

    while (ros::ok())
    {
        easy_pub1.publish(output);
        std::cout << output.data << std::endl;
        output.data++;
        naptime.sleep();
    }
}
订阅器Subscriber代码：
#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Int32.h>

void MyCallback1(const std_msgs::Int32& message)
{
    std::cout << "Callback1 received value is " << message.data << std::endl;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "my_minimal_subscriber");
    ros::NodeHandle n;
    ros::Subscriber easy_subscriber1 = n.subscribe("easy_topic1", 1, MyCallback1);
    ros::spin();
}
上述代码运行结果(Subscriber):
Callback1 received value is 2
Callback1 received value is 3
Callback1 received value is 4
Callback1 received value is 5
Callback1 received value is 6
发现回调函数收到的第一个消息为2，并不是1，因为1被丢掉了，我们把Publisher中easy_pub1改成下面这样的
ros::Publisher easy_pub1 = nh.advertise<std_msgs::Int32>("easy_topic1", 1， true);
运行结果为：
Callback1 received value is 1
Callback1 received value is 2
Callback1 received value is 3
Callback1 received value is 4
Callback1 received value is 5
丢掉的1又能收到了。

6、ROS多线程的陷阱
（1）试验一个例子，假设我们在某个订阅器绑定的Callback函数中进行了阻塞操作，比如是延时操作，那么如果此时我们使用了ROS多线程，会不会消息队列上不会阻塞，直接拿新的的线程来处理新接收到的消息，试验结果跟设想完全不一样，当前订阅器完全阻塞了，多线程对这种情况并没有起到作用，所以ROS的多线程绑定的是全局队列，并不是订阅器，根据全局队列来分配线程，具体的某一个订阅器并不能分配线程，代码示例如下：
发布器Publisher代码：
#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Int32.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_minimal_publisher");
    ros::NodeHandle nh;
    ros::Publisher easy_pub1 = nh.advertise<std_msgs::Int32>("easy_topic1", 1, true);

    ros::Rate naptime(1.0);

    std_msgs::Int32 output;
    output.data = 1;

    while (ros::ok())
    {
        easy_pub1.publish(output);
        std::cout << output.data << std::endl;
        output.data++;
        naptime.sleep();
    }
}
订阅器Subscriber代码：
#include <iostream>
#include <thread>
#include <chrono>
#include <ros/ros.h>
#include <std_msgs/Int32.h>

void MyCallback1(const std_msgs::Int32& message)
{
    std::cout << "Callback1 received value is " << message.data << std::endl;
    std::cout << "Callback1 thread is " << std::this_thread::get_id() << std::endl;
    std::cout << "Callback1 time is " << ros::Time::now().toSec() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "my_minimal_subscriber");
    ros::NodeHandle n;
    ros::Subscriber easy_subscriber1 = n.subscribe("easy_topic1", 5, MyCallback1);
    
    ros::AsyncSpinner as(6);    //必须指定线程数

    std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
    std::cout.precision(10);
    std::cout << "Main thread time is " << ros::Time::now().toSec() << std::endl;

    as.start();
    ros::waitForShutdown();
}
上述代码运行结果为:
Main thread id is 139698770474880
Main thread time is 1632932847
Callback1 received value is 1
Callback1 thread is 139698525673216
Callback1 time is 1632932849
Callback1 received value is 2
Callback1 thread is 139698525673216
Callback1 time is 1632932854
可以看到，回调函数的第二次响应时间和第一次相差了5s，此时，ROS多线程失去了作用；
（2）增加第二个不阻塞的回调函数，情况会如何呢？具体代码如下：
发布器Publisher代码：
int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_minimal_publisher");
    ros::NodeHandle nh;
    ros::Publisher easy_pub1 = nh.advertise<std_msgs::Int32>("easy_topic1", 1, true);
    ros::Publisher easy_pub2 = nh.advertise<std_msgs::Int32>("easy_topic2", 1, true);

    ros::Rate naptime(1.0);

    std_msgs::Int32 output;
    output.data = 1;

    while (ros::ok())
    {
        easy_pub1.publish(output);
        easy_pub2.publish(output);
        std::cout << output.data << std::endl;
        output.data++;
        naptime.sleep();
    }
}
订阅器Subscriber代码：
void MyCallback1(const std_msgs::Int32& message)
{
    std::cout << "Callback1 received value is " << message.data << std::endl;
    std::cout << "Callback1 thread is " << std::this_thread::get_id() << std::endl;
    std::cout << "Callback1 time is " << ros::Time::now().toSec() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

void MyCallback2(const std_msgs::Int32& message)
{
    std::cout << "Callback2 received value is " << message.data << std::endl;
    std::cout << "Callback2 thread is " << std::this_thread::get_id() << std::endl;
    std::cout << "Callback2 time is " << ros::Time::now().toSec() << std::endl;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "my_minimal_subscriber");
    ros::NodeHandle n;
    ros::Subscriber easy_subscriber1 = n.subscribe("easy_topic1", 5, MyCallback1);
    ros::Subscriber easy_subscriber2 = n.subscribe("easy_topic2", 1, MyCallback2);
    
    ros::AsyncSpinner as(6);    //必须指定线程数

    std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
    std::cout.precision(10);
    std::cout << "Main thread time is " << ros::Time::now().toSec() << std::endl;

    as.start();
    ros::waitForShutdown();
}
上述代码运行结果为：
Main thread id is 140218075957120
Main thread time is 1632933150
Callback1 received value is 1
Callback1 thread is 140217839240960
Callback1 time is 1632933152
Callback2 received value is 1
Callback2 thread is 140217814062848
Callback2 time is 1632933152
Callback2 received value is 2
Callback2 thread is 140217856026368
Callback2 time is 1632933153
Callback2 received value is 3
Callback2 thread is 140217856026368
Callback2 time is 1632933154
Callback2 received value is 4
Callback2 thread is 140217856026368
Callback2 time is 1632933155
Callback1 received value is 2
Callback1 thread is 140217839240960
Callback1 time is 1632933157
明显的Callback1收到延时5秒的影响，而Callback2没有受到影响；
总而言之，就是这种多线程使用方法不能解决某一个订阅器对应的回调函数的阻塞问题，只能解决多个订阅器时，某个订阅器的回调函数阻塞却并不会影响别的订阅器。
另外还可以注意一个现象，单线程时，两个回调函数，一个延时5s，一个正常，那么延时5s结束后，会先执行另一个被阻塞没被执行的回调函数吗？答案是的，那么再下一次呢，就不是的，我们来理下时间线，刚开始接受消息先执行了Callback1，阻塞5s，第6s执行Callback2(假设不耗费时间)，执行完立即又执行Callback1，阻塞5s（6+5=11），接下来还是执行Callback1(6+5+5=16),之后才执行Callback2，两次Callback2执行之间差了10s，细思起来很有意思。

7、封装一个可以解决在6中讨论的ROS多线程阻塞问题的Subscriber