#include "robot.hpp"

#define GearHead_Ratio 50

#define ROBOT_WHEEL_DIA 0.2 //m
#define ROBOT_WHEEL_SEP 1.0 //m

#define Left_Wheel_num 1  // mot1
#define PI 3.141592


void ROBOT::set_baudrate_57600(void){
  int Data[2]={0xaa,5};
  BYTE PID = 135;
  PutMdData(PID,2,Data);

}

BYTE ROBOT::h_Byte(short data){
  return data>>8 & 0xff;
}
BYTE ROBOT::l_Byte(short data){
  return data & 0xff;
}

/***********************************************************
 * 1바이트 D4,D5,D6,D7 데이터를 받아 원 데이터인 4바이트 정수를 만듬
 ***********************************************************/
int ROBOT::Byte2Int32(BYTE d4, BYTE d5, BYTE d6, BYTE d7)
{
  return ((int)d4 | (int)d5<<8 | (int)d6<<16 | (int)d7<<24);
}


void ROBOT::go_rpm(short mot1_rpm, short mot2_rpm){

  BYTE PID = 207; //PID_PNT_VEL_CMD

  int D1 = 1;  //mot1 enable
  int D2 = l_Byte(mot1_rpm);
  int D3 = h_Byte(mot1_rpm);
  int D4 = 1;  //mot1 enable
  int D5 = l_Byte(mot2_rpm);
  int D6 = h_Byte(mot2_rpm);
  int D7 = 2; //

  int Data[7] = {D1,D2,D3,D4,D5,D6,D7};
  PutMdData(PID,7,Data);

 // ROS_INFO("go_rpm");

 // ROS_INFO("D2 : %d, D3 : %d / D5 : %d, D6 : %d",D2,D3,D5,D6);


}

short pre_r_rpm = -1;
short pre_l_rpm = -1;

void ROBOT::go_cmd_vel(double linear_x, double angular_z){

  short R_wheel_RPM = -1*(short)(GearHead_Ratio*30.0*((2*linear_x) + (ROBOT_WHEEL_SEP*angular_z))/(ROBOT_WHEEL_DIA*PI));
  short L_wheel_RPM = (short)(GearHead_Ratio*30.0*((2*linear_x) - (ROBOT_WHEEL_SEP*angular_z))/(ROBOT_WHEEL_DIA*PI));

  //if(pre_l_rpm !=L_wheel_RPM || pre_r_rpm !=R_wheel_RPM){
    //ROS_INFO("r_rpm : %d l_rpm : %d",R_wheel_RPM,L_wheel_RPM);

  if(Left_Wheel_num ==1){
    go_rpm(L_wheel_RPM,R_wheel_RPM);
  }
  else{
    go_rpm(R_wheel_RPM,L_wheel_RPM);
  }

//  }

  pre_r_rpm = R_wheel_RPM;
  pre_l_rpm = L_wheel_RPM;

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

void ROBOT::get_position(int *mot1_posi, int *mot2_posi){
  BYTE rx_data[250];
  BYTE byBufNumber;
  ReadMdData(rx_data, &byBufNumber);

  int checksum =0;
  BYTE data_num = 0;
  BYTE DATA[19]={0};
  //ROS_INFO("%d",byBufNumber);
  int i=0;
  //ROS_INFO("1");
  while(i<byBufNumber){

    if(rx_data[i]==172 && rx_data[i+1]==183){
      //ROS_INFO("2");

    for(int j=i;j<i+18;j++){
      DATA[j-i]=rx_data[j+5];
    }
    //ROS_INFO("%d",rx_data[i+3]);
   // ROS_INFO("4");
    for(int k=i;k<=(i+24);k++){
      //ROS_INFO("6");
      checksum+=rx_data[k];
    }
    //ROS_INFO("5");
    if(1==checksum){
      ROS_WARN("communication_error");
      checksum = 0;
    }
    else{
      *mot1_posi = Byte2Int32(DATA[5],DATA[6],DATA[7],DATA[8]);
      //ROS_INFO("%d %d %d %d",DATA[5],DATA[6],DATA[7],DATA[8]);
      *mot2_posi = Byte2Int32(DATA[14],DATA[15],DATA[16],DATA[17]);
      //ROS_INFO("%d %d %d %d",DATA[14],DATA[15],DATA[16],DATA[17]);
    }
    }
    i++;
  }
  //ROS_INFO("3");


}

