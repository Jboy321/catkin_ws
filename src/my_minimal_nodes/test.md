/*** 
 * @Author: Zhoushenshen
 * @Date: 2021-09-28 20:27:10
 * @LastEditors: Zhoushenshen
 * @LastEditTime: 2021-09-28 20:45:00
 * @Description: 
 * @Company: xxxxxx
 * @Email: zhoushenshen@todo.com
 */
#include <iostream>

#include <ros/ros.h>
#include <std_msgs/Int32.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "test_pub");
    ros::NodeHandle nh;

    ros::Publisher easy_pub = nh.advertise<std_msgs::Int32>("easy_topic", 1);
    ros::Publisher easy_pub2 = nh.advertise<std_msgs::Int32>("easy_topic2", 1);

    ros::Rate naptime(1.0);
    std_msgs::Int32 output;
    output.data = 1;

    while (ros::ok())
    {
        easy_pub.publish(output);
        easy_pub2.publish(output);
        std::cout << output.data << std::endl;
        output.data++;
        naptime.sleep();
    }
    
}



/*** 
 * @Author: Zhoushenshen
 * @Date: 2021-02-04 17:21:12
 * @LastEditors: Zhoushenshen
 * @LastEditTime: 2021-09-28 20:52:22
 * @Description:
 * @Company: idriverplus
 * @Email: zhoushenshen@idriverplus.com
 */
#include "monitor.h"

#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <functional>
#include <type_traits>

#include <ros/ros.h>
#include <ros/master.h>
#include <std_msgs/Int8.h>
#include <diagnosis/FaultServiceMsg.h>
#include <std_msgs/Int32.h>

bool CheckROSNodeState(const std::string& node, std::string&uri) {
    XmlRpc::XmlRpcValue args, result, payload;
    args[0] = ros::this_node::getName();
    args[1] = node;
    if (!ros::master::execute("lookupNode", args, result, payload, true)) {
        std::cout << "Failed!" << std::endl;
        return false;
    }
    std::cout << "----------LookupedNode----------" << std::endl;
    uri = std::string(payload);
    //std::cout << bool(result) << std::endl;
    std::cout << node << ":" << std::string(payload) << std::endl;
    return true;
}

void EasyCallback(const std_msgs::Int32& msg)
{
    std::cout << "Receive1 value: " << msg.data << std::endl;
    std::cout << "This callback1 thread is " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

void EasyCallback2(const std_msgs::Int32& msg)
{
    std::cout << "Receive2 value: " << msg.data << std::endl;
    std::cout << "This callback2 thread is " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "test");
    ros::NodeHandle nh;
    ros::Subscriber easy_subscriber = nh.subscribe("easy_topic", 10, EasyCallback);
    ros::Subscriber easy_subscriber2 = nh.subscribe("easy_topic2", 1, EasyCallback2);
    ros::Subscriber easy_subscriber3 = nh.subscribe("easy_topic2", 1, EasyCallback2);
    // ros::Rate rate(1.0);

    // ros::ServiceClient fault_client = nh.serviceClient<::diagnosis::FaultServiceMsg>("/diagnosis/fault_service");
    // ::diagnosis::FaultServiceMsg srv;
    // srv.request.cmd = 0;

    // while (ros::ok())
    // {
    //     auto time1 = ros::Time::now();
    //     fault_client.call(srv);
    //     std::cout << (ros::Time::now() - time1).toSec() << std::endl;

    //     rate.sleep();
    // }
    


    // std::string node_name, node_uri;

    // while (std::getline(std::cin, node_name))
    // {
    //     if (node_name != "exit")
    //     {
    //         std::cout << std::boolalpha << CheckROSNodeState(node_name, node_uri) << std::endl;
    //     }
    //     else
    //     {
    //         exit(0);
    //     }
    // }

    // auto pmonitor = std::move(avos::diagnosis::Monitor::Instance());
    // pmonitor->Init("planning", avos::diagnosis::Monitor::InitParam::fault);
    // ros::Rate rate(1);
    // while (ros::ok())
    // {
    //     pmonitor->DirectFaultTrigger(
    //         PLANNING_ALGORITHM_8_ERROR,
    //         "current loc is in collision!",
    //         avos::diagnosis::SignalFunctor<bool>(true)
    //     );
    //     rate.sleep();
    // }

    // std::thread thread1([&](){
    //     ros::Timer timer1 = nh.createTimer(ros::Duration(1.0), [&](const ros::TimerEvent& event){
    //         std::cout << 123 << std::endl;
    //         std::cout << "timer thread id is " << std::this_thread::get_id() << std::endl;
    //     });

    //     ros::waitForShutdown();
    // });
    // thread1.detach();

    // ros::MultiThreadedSpinner ms(5);
    std::cout << "Main thread id is " << std::this_thread::get_id() << std::endl;
    // ms.spin();  //ros::spin(ms);
    ros::AsyncSpinner as(5);
    as.start();
    ros::waitForShutdown();
    // pmonitor->Init("shared_memory_manager", avos::diagnosis::Monitor::InitParam::both);
    // int duration = 100;
    // std::cout << (*pmonitor)[0x0020];
    // (*pmonitor)[0x0020].fault_code = 0x0020;
    // (*pmonitor)[0x0020].fault_flag = true;
    // (*pmonitor)[0x0020].SetFaultNodeName("localization");
    // (*pmonitor)[0x0020].SetFaultMessage("fuck bitch!");
    // std::cout << (*pmonitor)[0x0020];
    // std::cout << "请输入心跳周期(ms)，退出输入111" << std::endl;
    // while (std::cin >> duration)
    // {
    //     if (duration == 111) exit(0);
    //     ros::Rate rate(1000/duration);
    //     int i = 0;
    //     while (ros::ok())
    //     {
    //         pmonitor->HeartbeatStart();
    //         rate.sleep();
    //         i++;
    //         if (i > (5 * 1000 / duration))
    //         {
    //             std::cout << "请输入心跳周期(ms)，退出输入111" << std::endl;
    //             break;
    //         }
    //     }
    // }

    // int num = 0;

    // while (num < 10)
    // {
    //     pmonitor->HeartbeatStart();
        
    //     //std::cout << "123\n";

    //     // for (int i = 0; i < 3; i++) {
	// 	// 	pmonitor->SetFaultInfo(base + i, "error " + std::to_string(i));
	// 	// }
    //     pmonitor->SetFaultInfo(0x1026, "fuck");
    //     pmonitor->SetFaultInfo(0x2026, "fuck");
    //     pmonitor->SetFaultInfo(0x602b, "fuck");
    //     pmonitor->SetFaultInfo(0x8403, "fuck");
    //     pmonitor->SetFaultInfo(0x905f, "fuck");

    //     num++;

    //     usleep(1000 * 850);
    // }

    // pmonitor->ResetFaultInfo(0x1026);
    // pmonitor->ResetFaultInfo(0x2026);
    // pmonitor->ResetFaultInfo(0x602b);
    // pmonitor->ResetFaultInfo(0x8403);
    // pmonitor->ResetFaultInfo(0x905f);

    // std::string str;
    // while(std::getline(std::cin, str))
    // {
    //     if (str == "set")
    //     {
    //         while (std::getline(std::cin, str))
    //         {
    //             pmonitor->SetFaultInfo("canbus", std::stoi(str, nullptr, 16), "fuck");
    //             break;
    //         }
    //     }
    //     else if (str == "reset")
    //     {
    //         while (std::getline(std::cin, str))
    //         {
    //             pmonitor->ResetFaultInfo(std::stoi(str, nullptr, 16));
    //             break;
    //         }
    //     }
    // }


}

// void PubTopic1(ros::Publisher pub)
// {
//     ros::Rate naptime(1);
//     while (ros::ok())
//     {
//         std_msgs::Int8 input;
//         input.data = 1;
//         pub.publish(input);

//         naptime.sleep();
//     }
// }

// void PubTopic2(ros::Publisher pub)
// {
//     ros::Rate naptime(2);

//     while (ros::ok())
//     {
//         std_msgs::Int8 input;
//         input.data = 1;
//         pub.publish(input);

//         naptime.sleep();
//     }
// }

// int main(int argc, char** argv)
// {
//     ros::init(argc, argv, "my_minimal_publisher");
//     ros::NodeHandle nh;
//     ros::Publisher my_pub1 = nh.advertise<std_msgs::Int8>("topic1", 1);
//     ros::Publisher my_pub2 = nh.advertise<std_msgs::Int8>("topic2", 1);

//     ros::Publisher testpub = my_pub1;
//     std::thread thread1(PubTopic1, std::ref(my_pub1));
//     thread1.detach();
//     std::thread thread2(PubTopic2, std::move(my_pub2));
//     thread2.detach();

//     while (ros::ok())
//     {
        
//     }

// }

// template<class... A>
// void Print(A... arg)
// {
// 	//assert(false);
// }
 
// void Print(int a1, int a2, int a3, int a4, int a5, int a6)
// {
// 	std::cout << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << std::endl;
// }
 
// template<class... A>
// int Vaargs(A... args)
// {
// 	int size = sizeof...(A);
 
// 	switch (size) {
// 	case 0: Print(99, 99, 99, 99, 99, 99);
// 		break;
// 	case 1: Print(99, 99, args..., 99, 99, 99);
// 		break;
// 	case 2: Print(99, 99, args..., 99, 99);
// 		break;
// 	case 3: Print(args..., 99, 99, 99);
// 		break;
// 	case 4: Print(99, args..., 99);
// 		break;
// 	case 5: Print(99, args...);
// 		break;
// 	case 6: Print(args...);
// 		break;
// 	default:
// 		Print(0, 0, 0, 0, 0, 0);
// 	}
 
// 	return size;
// }

// int test_variable_arguments_sizeof_1()
// {
// 	Vaargs();
// 	Vaargs(1);
// 	Vaargs(1, 2);
// 	Vaargs(1, 2, 3);
// 	Vaargs(1, 2, 3, 4);
// 	Vaargs(1, 2, 3, 4, 5);
// 	Vaargs(1, 2, 3, 4, 5, 6);
// 	Vaargs(1, 2, 3, 4, 5, 6, 7);
 
// 	return 0;
// }

// int main()
// {
//     test_variable_arguments_sizeof_1();
// }
// void syszuxPrint(){std::cout<< 123 <<", "<<std::endl;}
// template<typename T>
// void syszuxPrint(T arg){std::cout<<arg<<", "<<std::endl;}

// template<typename T, typename... Ts>
// void syszuxPrint(T arg1, Ts... arg_left){
//     std::cout<<arg1<<", ";
//     syszuxPrint(arg_left...);
// }

// int main(int argc, char** argv)
// {
//     syszuxPrint(719,7030,"civilnet");
// }

// template<typename T1, typename T2, typename T3>
// void JudgeHandler(T1 signal, T2 handler1, T3 handler2)
// {
//     if (signal() == true)
//     {
//         handler1();
//     }
//     else
//     {
//         handler2();
//     }
// }

// template<typename T>
// struct SignalFunctor
// {
//     SignalFunctor(T t)
//     :value()
//     {

//     }

//     T value;

//     std::function<bool()> operator()()
//     {
//         return [m_var=value]{ return static_cast<bool>(m_var); };
//     }

// };

// template<typename T>
// bool SignalHandler(T t)
// {
//     return static_cast<bool>(t());
// }


// template<typename T, typename... Args>
// bool SignalHandler(T t, Args... args)
// {
//     std::cout << "args..." << std::endl;
    
//     return static_cast<bool>(t()) && SignalHandler(args...);
// }

// int main()
// {
//     //auto pt =  SignalFunctor<int>()();
//     //std::cout << std::boolalpha << pt << std::endl;
//     SignalHandler(SignalFunctor<int>(1), SignalFunctor<int>(2), SignalFunctor<int>(3));
// }

// int main()
// {
//     auto pmonitor = std::move(avos::diagnosis::Monitor::Instance());
//     // pmonitor->FaultHandle(
//     //     avos::diagnosis::
//     // )
//     pmonitor->DirectFaultTrigger(
//         0x0020,
//         "fuck!",
//         std::bind(avos::diagnosis::HardwareJudgeSignal<int>,1,1),
//         std::bind(avos::diagnosis::HardwareJudgeSignal<int>,2,2),
//         std::bind(avos::diagnosis::HardwareJudgeSignal<int>,3,3)
//     );
//     std::cout << 123 << std::endl;
    
// }




 hardware_sub_option_ = ros::SubscribeOptions::create<canbus_msgs::CanRecieve>("tpbusinessfb", 1, boost::bind(&HardwareDiagnosis::CallbackHardwareFault, this, _1), ros::VoidPtr(), &hardware_fault_queue_);
    hardware_subscriber_ = nh_.subscribe(hardware_sub_option_);


