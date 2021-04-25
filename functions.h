#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
void setShadeToTarget(BYTE newValue);
int isButtonPressed(int button);
int countToPosition(dword count);
dword positionToCount(BYTE pos);
void setShadeToTarget(BYTE newValue);
void intButtonPressed();
int my_battery_handler();
void SaveCFGParam(byte param, word value);
word LoadCFGParam(byte param);
void buttonPressed();
void resetTimeOut();
void checkTimeOut();
#endif
