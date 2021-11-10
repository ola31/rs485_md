//#ifndef COM_H
//#define COM_H



#define MAX_PACKET_SIZE     26
#define MAX_DATA_SIZE       21

#include "main.hpp"
//#include <serial/serial.h>

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned int   DWORD;

typedef struct {
    BYTE bySndBuf[MAX_PACKET_SIZE];
    BYTE byRcvBuf[MAX_PACKET_SIZE];
    BYTE byPacketSize;
    BYTE byPacketNum;
    BYTE byIn, byStep;
    BYTE byChkSend;
    BYTE byChkRcv;
    BYTE fgInIdleLine, fgPacketOK, fgComComple;
    BYTE byTotalRcvDataNum;
    BYTE fgChk;
    BYTE byChkSum, byMaxDataNum, byDataNum;

    //int nIDPC, nIDMDUI, nIDMDT, nRMID;
    //int nDiameter, nBaudrate, nWheelLength, nGearRatio, fgDirSign;
    //short sSetDia, sSetWheelLen, sSetGear;
    int nCmdSpeed, nCmdAngSpeed;

    short sTempVoltIn, sSumVolt ,sVoltIn;
    BYTE byPlatStatus, bEmerSW, bBusy, bBumper1, bBumper2, bBumper3, bBumper4;
    BYTE byDocStatus, bDocComple, bChargeState, bCharComple, bIr1, bIr2, bIr3, bRccState;

    BYTE byUS1, byUS2, byUS3, byUS4;

    BYTE fgResetOdometry, fgControlstate, fgResetAngle;

    int fgSndOK, nCntDelaySnd;

    long lPosi[2], lTempPosi[2];
    short sTheta, sTempTheta, sExTheta;

    long lMoving[3][3];

    short sMotorRPM[2];
    long lMotorPosi[2];

    WORD sCurrent[2];

    BYTE byStatus[2];
    BYTE fgAlarm[2], fgCtrlFail[2], fgOverVolt[2], fgOverTemp[2];
    BYTE fgOverLoad[2], fgHallFail[2], fgInvVel[2], fgStall[2];

    BYTE byChkComError;
    BYTE fgComDataChk;

    BYTE byCntVoltAver;

    int nHallType, nMaxRPM, nAngResol;
    double dTheta;

    int nSlowstart, nSlowdown;
    BYTE fgInitsetting;

    BYTE fgResetAlarm;

}Communication;
//Communication Com;


class COM{

private:
  Communication Com;

public:
  int InitSerial(void);
  int PutMdData(BYTE byPID, BYTE byDataSize, int nArray[]);
  void ReadMdData(BYTE* rx_array,BYTE *byBufNumber);

};

typedef struct {
    BYTE byLow;
    BYTE byHigh;
}IByte;


//#endif // COM_H
