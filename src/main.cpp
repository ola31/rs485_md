//#include "ros/ros.h"
//#include "std_msgs/String.h"

#include "main.hpp"
#include "com.hpp"

int vel_array[] = {1,0,90,1,0,80,0};
Communication Com;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rs485_md_node");
  ros::NodeHandle nh;

  int result1, result2;
  InitSerial();

  ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    std_msgs::String msg;
    msg.data = "hello world";
    result2 = PutMdData(207, 7, vel_array);

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
