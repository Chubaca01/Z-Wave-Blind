#include "arduino.h"
#include "debug.h"
#include "define.h"
#include "initval.h"
#include "command.h"
#include "functions.h"

void adjustUp(int pause){
int valSave;
    valSave = currentCount;
    if(currentCount ==0)
      currentCount = 100;
    upBlind();
    delay(pause);
    if (valSave == 0)
      currentCount = 0;
    stopBlind();
}

void upBlind()
  {
    if (currentCount >= MAXCOUNT)
      currentCount += OFFSET;
    digitalWrite(LED_BUILTIN, HIGH);
    down = 0;
    up = 1;
    idle = 0;
    //DebugPrintln("Blinds up");
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(out1,HIGH);
    action = WAIT;
  }

void downBlind()
  {
    down = 1;
    up = 0;
    idle = 0;
    digitalWrite(LED_BUILTIN, HIGH);
    //DebugPrintln("Blinds down");
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(out1,HIGH);
    action = WAIT;
  }

void stopBlind()
  {
    digitalWrite(out1,LOW);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,HIGH);

    digitalWrite(LED_BUILTIN, LOW);
    currentPosition = countToPosition(currentCount);
    SaveCFGParam(AD_CURRENT_POS_SAVED, currentPosition);
    SaveCFGParam(AD_CURRENT_COUNT_SAVED, currentCount);
    DebugPrintln("Blinds stop");
    DebugPrint("Current Count:");
    DebugValPrintln(currentCount);
    DebugPrint("Current Position:");
    DebugValPrintln(currentPosition);
    down = 0;
    up = 0;
    idle = 1;
    zunoSendReport(1);
    action = GO_SLEEP;
  }

  int readBattery(){
    int val = 0;
    int i;
    for( i=0; i< NB_BATTERY_READ ; i++)
      val += analogRead(battery);
    val/= NB_BATTERY_READ;
    return val;
  }

  void goToSleep(){
    writeNvRamValues();
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(out1,LOW);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,HIGH);
  }
