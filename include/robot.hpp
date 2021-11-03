#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "com.hpp"

class ROBOT : public COM
{
private:
public:
  BYTE h_Byte(short data);
  BYTE l_Byte(short data);

  void go_rpm(short mot1_rpm, short mot2_rpm);
  void go_cmd_vel(double linear_x, double angular_z);
  void get_position(BYTE mot1_posi, BYTE mot2_posi);
  void DATA_REQ(BYTE REQ_PID);
  void REQ_main_data(void);
  void set_baudrate_57600(void);

};







#endif // ROBOT_HPP
