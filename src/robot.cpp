#include "robot.hpp"

#define GearHead_Ratio 50

#define ROBOT_WHEEL_DIA 0.2 //m
#define ROBOT_WHEEL_SEP 1.0 //m

#define Left_Wheel_num 1  // mot1
#define PI 3.141592


void set_baudrate_57600(void){
  int Data[2]={170,4};
  BYTE PID = 135;
  //PutMdData(PID,2,Data);

}

BYTE ROBOT::h_Byte(short data){
  return data>>8 & 0xff;
}
BYTE ROBOT::l_Byte(short data){
  return data & 0xff;
}

void ROBOT::go_rpm(short mot1_rpm, short mot2_rpm){

  BYTE PID = 207; //PID_PNT_VEL_CMD

  int D1 = 1;  //mot1 enable
  int D2 = l_Byte(mot1_rpm);
  int D3 = h_Byte(mot1_rpm);
  int D4 = 1;  //mot1 enable
  int D5 = l_Byte(mot2_rpm);
  int D6 = h_Byte(mot2_rpm);
  int D7 = 0; //

  int Data[7] = {D1,D2,D3,D4,D5,D6,D7};
  PutMdData(PID,7,Data);

 // ROS_INFO("D2 : %d, D3 : %d / D5 : %d, D6 : %d",D2,D3,D5,D6);


}

short pre_r_rpm = 0;
short pre_l_rpm = 0;

void ROBOT::go_cmd_vel(double linear_x, double angular_z){

  short R_wheel_RPM = -1*(short)(GearHead_Ratio*30.0*((2*linear_x) + (ROBOT_WHEEL_SEP*angular_z))/(ROBOT_WHEEL_DIA*PI));
  short L_wheel_RPM = (short)(GearHead_Ratio*30.0*((2*linear_x) - (ROBOT_WHEEL_SEP*angular_z))/(ROBOT_WHEEL_DIA*PI));

  if(pre_l_rpm !=L_wheel_RPM && pre_r_rpm !=R_wheel_RPM){

  if(Left_Wheel_num ==1)
    go_rpm(L_wheel_RPM,R_wheel_RPM);
  else
    go_rpm(R_wheel_RPM,L_wheel_RPM);
  }

}

void ROBOT::DATA_REQ(BYTE REQ_PID){

  BYTE PID = 4;
  int Data[1] = {REQ_PID};
  PutMdData(PID,1,Data);

}

void ROBOT::REQ_main_data(void){
  BYTE PID = 210;//PID_PNT_MAIN_DATA;
  DATA_REQ(PID);
}
/*
void get_position(BYTE mot1_posi, BYTE mot2_posi){
  BYTE rx_data[250];
  BYTE byBufNumber;
  ReadMdData(rx_data, &byBufNumber);

  BYTE checksum =0;
  BYTE data_num = 0;
  BYTE DATA[19]={0};

  int i=0;
  while(i<byBufNumber){
    if(rx_data[i]==172 && rx_data[i+1]=184){

    for(int j=0;j<18;j++){
      DATA[j]=rx_data[j+5];
    }
    for(i;i<i+23;i++){
      checksum+=rx_data;
    }
    if(rx_data[i]!=checksum){
      printf("communication_error");
    }



    }
    i++;
  }

}
*/
