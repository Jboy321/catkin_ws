#include <ros/ros.h>
#include <std_msgs/Float64.h>

#include <iostream>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_minimal_publisher");
    ros::NodeHandle nh;
    ros::Publisher my_publisher_object = nh.advertise<std_msgs::Float64>("topic1", 1);

    std_msgs::Float64 input_float;
    input_float.data = 0.0;
    ros::Rate naptime(1.0);

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

    int i = 0;

    while (ros::ok())
    {
        if (i < 11)
        {
            my_publisher_object.publish(input_float);
            i++;
            input_float.data += 0.1;
            naptime.sleep();
        }
        else
        {
            i = 0;
            input_float.data = 0.0;         
            
        }
        
    }

}
