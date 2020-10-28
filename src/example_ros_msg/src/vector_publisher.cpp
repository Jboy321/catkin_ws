#include <ros/ros.h>
#include <custom_msgs/VecOfDoubles.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "vector_publisher");
    ros::NodeHandle nh;
    ros::Publisher my_publisher_object = nh.advertise<custom_msgs::VecOfDoubles>("vec_topic", 1);
    
    custom_msgs::VecOfDoubles vec_msg;
    double counter = 0;
    ros::Rate naptime(1.0);
    
    vec_msg.dbl_vec.resize(3); //manually resize it to hold 3 doubles
    //after setting the size, one can access elements of this array conventionally, e.g.
    vec_msg.dbl_vec[0] = 1.414;
    vec_msg.dbl_vec[1] = 2.71828;
    vec_msg.dbl_vec[2] = 3.1416;

    //Alternatively, one can use the vector member function push_back() to append data to an existing array, e.g.
    vec_msg.dbl_vec.push_back(counter);
    while(ros::ok())
    {
        counter +=1.0;
        vec_msg.dbl_vec.push_back(counter);
        my_publisher_object.publish(vec_msg);
        naptime.sleep();
    }
}