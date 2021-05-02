#include <creating_a_ros_library/example_ros_class.h>

//前导和构造函数
ExampleRosClass::ExampleRosClass(ros::NodeHandle* nodehandle):nh_(*nodehandle)
{
    ROS_INFO("in class constructor of ExampleRosClass");
    //初始化成员函数
    initializeSubscribers();
    initializePublishers();
    initializeServices();

    //初始化变量
    val_to_remember_ = 0.0;
}

//助手成员函数
//初始化订阅器
void ExampleRosClass::initializeSubscribers()
{
    ROS_INFO("Initializing Subscribers");
    minimal_subscriber_ = nh_.subscribe("example_class_input_topic", 1, &ExampleRosClass::subscriberCallback, this);
    //keyword "this" is required to refer to the current instance of ExampleRosClass
    //add more subscribers here, as needed
}
// 初始化服务器
void ExampleRosClass::initializeServices()
{
    ROS_INFO("Initializing Services");
    minimal_service_ = nh_.advertiseService("example_minimal_service", &ExampleRosClass::serviceCallback, this);
    //add more services here ,as needed

}
//初始化发布器
void ExampleRosClass::initializePublishers()
{
    ROS_INFO("Initializing Publishers");
    minimal_publisher_ = nh_.advertise<std_msgs::Float32>("example_class_input_topic", 1, true);
    //add more publishers, as needed
}

//回调函数
void ExampleRosClass::subscriberCallback(const std_msgs::Float32& message_holder)
{
    val_from_subscriber_ = message_holder.data;
    ROS_INFO("myCallback activated: received value %f", val_from_subscriber_);
    std_msgs::Float32 output_msg;
    val_to_remember_ += val_from_subscriber_;
    output_msg.data = val_to_remember_;
    ros::Rate naptime(2.0);
    minimal_publisher_.publish(output_msg);
    naptime.sleep();
}

bool ExampleRosClass::serviceCallback(std_srvs::TriggerRequest& request, std_srvs::TriggerResponse& response)
{
    ROS_INFO("service callback activated");
    response.success = true;
    response.message = "Here is a response string";
    return true;
}