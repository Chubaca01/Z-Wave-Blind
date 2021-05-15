  #include "EEPROM.h"
#include "define.h"
#include "initval.h"
#include "debug.h"
#include "command.h"
#include "functions.h"

ZUNO_SETUP_CHANNELS(ZUNO_BLINDS(getterFunction, setterFunction));
//ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_ALWAYS_AWAKE);
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_FREQUENTLY_AWAKE);
ZUNO_SETUP_BATTERY_HANDLER(my_battery_handler);
ZUNO_SETUP_ISR_ZEROX(motorRotationCount_handler);
ZUNO_SETUP_ISR_INT0(intButtonPressed);

BYTE currentPosition;
dword currentCount;
int pressed1,pressed2,pressed3;
BYTE up,down,idle,action,newVal,readNvRam;
dword targetCount;
word paramValue;
word timeOutVal;

void setup() {
byte n;
  initInputOutput();
  DebugInit();
  resetTimeOut();
  NZRAM.get(AD_MAGIC_VALUE, &n, 1);
  if (n != MAGIC_VALUE){  // just boot
    DebugPrintln("Just Boot ...");
    n = MAGIC_VALUE;
    NZRAM.put(AD_MAGIC_VALUE, &n, 1);
    InitVariables();
    measureBattery();
    zunoSendReport(1);
    action = WAIT;
  }
  else{
    DebugPrintln("Just not Boot ...");
    readNvRamValues();
    action = WAIT;
  }

//DebugPrintln("1");
}
void checkMotorlocation(){
    if ((currentCount == 0) && (up==1))
    {
      //stopBlind();
      action = STOP;
      currentCount=0;
    }
    else if ((currentCount >= targetCount)&&(down==1))
    {
      action = STOP;
    }
    else if ((currentCount <= targetCount)&&(up==1))
    {
      action = STOP;
    }
}

void stateCommand()
{
  switch(action){
    case UP:
      upBlind();
      break;
    case DOWN:
      downBlind();
      break;
    case STOP:
      stopBlind();
      break;
    case INT_ZEROX:
      break;
    case INT_INT0:
      adjustUp(ADJUST);
      break;
    case WAIT:
      checkTimeOut();
      break;
    case GO_SLEEP:
      goToSleep();
      zunoSendDeviceToSleep();
      break;
    default:
      checkTimeOut();
      break;
  }
}

void loop() {
  buttonPressed();
#ifdef SLEEPING
  stateCommand();
#else
  delay(20);
#endif
}

BYTE getterFunction() {
  resetTimeOut();
  currentPosition = countToPosition(currentCount);
  DebugValPrintln(currentCount);
  return currentPosition;
}

void setterFunction(BYTE newValue) {
unsigned int target;
  digitalWrite(LED_BUILTIN, HIGH);
  newVal= newValue;
  setShadeToTarget(newVal);
  resetTimeOut();
}

int my_battery_handler() {
  resetTimeOut();
  int percent;
  percent = measureBattery();
  return(percent);
}


void motorRotationCount_handler()
  {
    resetTimeOut();
    if (down)
      currentCount++;
    else if ((up) && (currentCount != 0))
      currentCount --;
    checkMotorlocation();
  }

void intButtonPressed(){
   //pressed3 = true;
   action = INT_INT0;
}


void SaveCFGParam(byte param, word value){
  zunoSaveCFGParam(param,value);
}

word LoadCFGParam(byte param){
word value;
  value = zunoLoadCFGParam(param);
  return value;
}


//--------------------------- debug function ----------------------------
void DebugInit(){
  #ifdef DEBUG
      Serial.begin(115200);
      delay(2000);
  #endif
  //DebugPrintln("--- Start Serial Monitor SEND_RCVE ---");
}

void DebugPrint(char *sValue) {
   #ifdef DEBUG
    Serial.print(sValue);
   #endif
}

void DebugValPrint(int value) {
  #ifdef DEBUG
   Serial.print(value);
  #endif
}

void DebugValPrintln(int value) {
  #ifdef DEBUG
   Serial.println(value);
  #endif
}

void DebugPrintln(char *sValue) {
  #ifdef DEBUG
    Serial.println(sValue);
  #endif
}
