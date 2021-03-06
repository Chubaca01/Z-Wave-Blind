#include "arduino.h"
#include "debug.h"
#include "define.h"
#include "initval.h"
#include "command.h"
#include "functions.h"

void setShadeToTarget(BYTE newValue){
  if (newValue == 99)
    newValue = 100;
  if (newValue > currentPosition)
  {
    targetCount = positionToCount(newValue);
    action = UP;
  }
  else if (newValue < currentPosition)
  {
    targetCount = positionToCount(newValue);
    action = DOWN;
  }
  else
    action = WAIT;
}


int isButtonPressed(int button){
  int val;
  val = digitalRead(button);
  if (val == LOW) {
    while (val == LOW){
      val = digitalRead(button);
      delay(20);
    }
    return 1;
  }
  else
    return 0;
}


void buttonPressed(){
#ifndef SLEEPING
  if(isButtonPressed(button1))
      pressed1 = true;
  if(isButtonPressed(button2))
      pressed2 = true;
  if (pressed1 == true)
    {
      targetCount= MAXCOUNT;
      downBlind();
      pressed1 = false;
    }
  if (pressed2 == true)
    {
      targetCount= 0;
      upBlind();
      pressed2 = false;
    }
#endif
  if(isButtonPressed(button3))
      pressed3 = true;
  if (pressed3 == true)
    {
      targetCount= 0;
      upBlind();
      pressed3 = false;
    }
 }

dword positionToCount(BYTE pos){
dword val;
dword ct;
int percent;
  percent = 100 - pos;
  val = MAXCOUNT;
  val *= percent;
  val /= 100;
  ct = val;
  return ct;
}

int countToPosition(dword ct){
int pos;
dword percent;
   percent = ct*100;
   percent /= MAXCOUNT;
   pos = 100 - (int) percent;
   if (pos > 100)
    pos = 100;
   else if (pos < 0)
    pos = 0;
   return pos;
}

void resetTimeOut()
{
  timeOutVal = TIME_OUT_VAL;
}

void checkTimeOut()
{
  //delay(TIME_OUT_DELAY);
  delayMicroseconds(TIME_OUT_DELAY);
  timeOutVal -= 1;
  if (timeOutVal <= 0)
  {
    if (up == 1) // stuck up
    {
      currentCount = 0;
      targetCount = 0;
      down = 0;
      up = 0;
      idle = 1;
      currentPosition = 100;
    }
    action = GO_SLEEP;
  }
}

int measureBattery(){
  float value;
  int percent;
  resetTimeOut();
  value = MAX_VOLT*readBattery();
  value /= 1023;
  value = (MAX_RVOLT - value)*100;
  value /= (MAX_RVOLT - MIN_VOLT);
  percent = 100 - value;
  if (percent > 100)
    percent = 100;
  DebugPrint("Battery Value %: ");
  DebugValPrintln(percent);
  return percent;
}
