#ifndef DEFINE_H_INCLUDED
  #define DEFINE_H_INCLUDED
  //#define DEBUG
  #define SLEEPING
  #define NB_BATTERY_READ 20
  #define MAX_VOLT 3.3
  #define MIN_VOLT 2.7
  #define MAX_RVOLT 3.27

  #define MAXCOUNT 6500

  #define battery 6
  #define button1 9
  #define button2 10
  //#define button3 11

  #define in1 20
  #define in2 21
  #define out1 12

  #define MAGIC_VALUE 56 // bytes
  #define AD_MAGIC_VALUE 0x0 // bytes
  #define AD_CURRENT_POS 0x1 // bytes
  #define AD_DOWN 0x2  // bytes
  #define AD_UP 0x3  // bytes
  #define AD_IDLE 0x4  // bytes
  #define AD_CURRENT_COUNT 0x05 //  dword 4 bytes
  #define AD_TARGET_COUNT 0x09  // dword 4 bytes

  #define MAGIG_VALUE_EEP 56 // word
  #define AD_MAGIG_VALUE_EEP 64
  #define AD_CURRENT_POS_SAVED 65
  #define AD_CURRENT_COUNT_SAVED 66

  #define UP         0
  #define DOWN       1
  #define STOP       2
  #define INT_ZEROX  3
  #define INT_INT0   4
  #define WAIT       5
  #define GO_SLEEP   6
  
  #define TIME_OUT_VAL 100
  

  extern BYTE currentPosition;
  extern dword currentCount;
  extern int pressed1,pressed2,pressed3;
  extern BYTE up,down,idle,action,newVal;
  extern dword targetCount;
  extern word paramValue;
  extern word timeOutVal;
#endif
