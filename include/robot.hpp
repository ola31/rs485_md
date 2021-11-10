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
  void get_position(int *mot1_posi, int *mot2_posi);
  void DATA_REQ(BYTE REQ_PID);
  void REQ_main_data(void);
  void set_baudrate_57600(void);
  int Byte2Int32(BYTE d4, BYTE d5, BYTE d6, BYTE d7);


};







#endif // ROBOT_HPP
