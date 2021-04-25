#include "ArduinoCAPI.h"
#include "EEPROM.h"
#include "debug.h"
#include "define.h"
#include "initval.h"
#include "functions.h"

void InitVariables(){
  currentCount = 0;
  targetCount = 0;
  down = 0;
  up = 0;
  idle = 1;
  currentPosition = 100;
  paramValue = LoadCFGParam(AD_MAGIG_VALUE_EEP);
  if (paramValue != MAGIG_VALUE_EEP){ // first time run
    SaveCFGParam(AD_MAGIG_VALUE_EEP, MAGIG_VALUE_EEP);
    SaveCFGParam(AD_CURRENT_POS_SAVED, currentPosition);
    SaveCFGParam(AD_CURRENT_COUNT_SAVED, currentCount);
  }
  else{
    currentPosition = LoadCFGParam(AD_CURRENT_POS_SAVED);
    currentCount = LoadCFGParam(AD_CURRENT_COUNT_SAVED);
  }
}

void initInputOutput(){
  #ifndef SLEEPING
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
  #endif
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(out1, OUTPUT);
  
  digitalWrite(out1,LOW);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,HIGH);
  
  pinMode(LED_BUILTIN, OUTPUT);
  

  zunoExtIntMode(ZUNO_EXT_ZEROX, RISING);
  zunoExtIntMode(ZUNO_EXT_INT0, RISING);
}

void printVar(){
     DebugPrint("CurrentPosition ");
     DebugValPrintln(currentPosition);
     DebugPrint("CurrentCount ");
     DebugValPrintln(currentCount);
     DebugPrint("TargetCount ");
     DebugValPrintln(targetCount);
     DebugPrint("Down");
     DebugValPrintln(down);
     DebugPrint("up");
     DebugValPrintln(up);
     DebugPrint("idle");
     DebugValPrintln(idle);
}
void readNvRamValues(){
     NZRAM.get(AD_CURRENT_COUNT, &currentCount, 4);
     NZRAM.get(AD_TARGET_COUNT, &targetCount, 4);
     NZRAM.get(AD_CURRENT_POS, &currentPosition, 1);
     NZRAM.get(AD_DOWN, &down, 1);
     NZRAM.get(AD_UP, &up, 1);
     NZRAM.get(AD_IDLE, &idle, 1);
     DebugPrintln("ReadNVRAM ");
     printVar();
}

void writeNvRamValues(){
     NZRAM.put(AD_CURRENT_COUNT, &currentCount, 4);
     NZRAM.put(AD_TARGET_COUNT, &targetCount, 4);
     NZRAM.put(AD_CURRENT_POS, &currentPosition, 1);
     NZRAM.put(AD_DOWN, &down, 1);
     NZRAM.put(AD_UP, &up, 1);
     NZRAM.put(AD_IDLE, &idle, 1);
     DebugPrintln("WriteNVRAM ");
     printVar();
}
