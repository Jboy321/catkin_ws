#include <ros/ros.h>
#include <custom_msgs/VecOfDoubles.h>

void myCallback(const custom_msgs::VecOfDoubles& message_holder)
{
    std::vector <double> vec_of_doubles = message_holder.dbl_vec;//can copy contents of message to a C++ vector like this
    int nvals = vec_of_doubles.size();//ask the vector how long it is
    for (int i=0; i<nvals; i++)
    {
        ROS_INFO("vec[%d] = %f", i ,vec_of_doubles[i]); //print put all the values
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "vector_subscriber");
    ros::NodeHandle nh;
    ros::Subscriber my_subscriber_object = nh.subscribe("vec_topic", 1, myCallback);
    ros::spin();
    return 0;
}