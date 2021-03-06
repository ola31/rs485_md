#include "com.hpp"
#include "main.hpp"

serial::Serial ser;
//typedef unsigned char  BYTE;
//typedef unsigned short WORD;
//typedef unsigned int   DWORD;
//Communication Com;
//Initialize serial communication in ROS
int InitSerial(void)
{
    try
    {
        ser.setPort("/dev/ttyUSB0");
        ser.setBaudrate(57600);
        serial::Timeout to = serial::Timeout::simpleTimeout(1667); //1667 when baud is 57600, 0.6ms
        ser.setTimeout(to);                                        //2857 when baud is 115200, 0.35ms
        ser.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }
    if(ser.isOpen())
        ROS_INFO_STREAM("Serial Port initialized");
    else
        return -1;
}


//for sending the data
int PutMdData(BYTE byPID, BYTE byDataSize, int nArray[]){

  IByte iData;
  BYTE byPidDataSize;  //, byDataSize;
  BYTE i, j;

  static BYTE byTempDataSum;

  for(j = 0; j <MAX_PACKET_SIZE; j++){       //MAX_PACKET_SIZE = 26
    Com.bySndBuf[j] = 0;
  }

  Com.bySndBuf[0] = 184;  //RMID = 184
  Com.bySndBuf[1] = 172;  //IDPC = 172
  Com.bySndBuf[2] = 1;    //ID of MD_motor_driver = 1
  Com.bySndBuf[3] = byPID;  //PID
  Com.bySndBuf[4] = byDataSize;  //data_number

  byPidDataSize = byDataSize+6;   //PIDDataSize(total size) = Datasize + Header(2) + ID(1) + PID(1) + data_number(1) + checksum(1)

  for(i=0;i<byDataSize;i++){
    Com.bySndBuf[5+i]=nArray[i];
  }

  for(i = 0; i < (byPidDataSize-1); i++){
    byTempDataSum += Com.bySndBuf[i];
  }

  Com.bySndBuf[byPidDataSize-1] = ~(byTempDataSum) + 1; //check sum

  ser.write(Com.bySndBuf, byPidDataSize);  //Serial write

}
