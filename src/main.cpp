#include "main.hpp"
#include "robot.hpp"

ROBOT robot;

//int vel_array[] = {1,(1000>>8)&0xff,1000&0xff,1,(1000>>8)&0xff,1000&0xff,0};//{1,0,90,1,0,80,0};
//int vel_array[] = {1,100&0xff,(100>>8)&0xff,1,(1>>8)&0xff,1&0xff,0};//{1,0,90,1,0,80,0};

double linear_x = 0.0;
double angular_z = 0.0;

void cmd_velCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
   linear_x = msg->linear.x;
   angular_z = msg->angular.z;
   //robot.go_cmd_vel(linear_x,angular_z);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "rs485_md_node");
  ros::NodeHandle nh;

  int result1, result2;
  robot.InitSerial();

  robot.set_baudrate_57600();

  //ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);
  ros::Subscriber sub = nh.subscribe("/cmd_vel", 1000, cmd_velCallback);

  ros::Rate loop_rate(120);
  while (ros::ok())
  {
    //result2 = robot.PutMdData(207, 7, vel_array);
    //robot.go_rpm(1000, 1000);
    //robot.go_cmd_vel();
    robot.go_cmd_vel(linear_x,angular_z);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
