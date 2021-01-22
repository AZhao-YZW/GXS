#ifndef _ARMDEBUG_H
#define _ARMDEBUG_H

#include "sys.h"

/* 用户调用 */
//用这4个
void Arm_DebugConfig(u16 depwmWidth1, u16 depwmWidth2, u16 depwmWidth3, u16 depwmWidth4, u16 depwmWidth5, u16 depwmWidth6);
void Arm_DebugConfig2(u16 deperiod1,   u16 deperiod2,   u16 deperiod3,   u16 deperiod4,   u16 deperiod5,   u16 deperiod6, 
											u16 depwmWidth1, u16 depwmWidth2, u16 depwmWidth3, u16 depwmWidth4, u16 depwmWidth5, u16 depwmWidth6);
void Servo_UsmartMoveConfig(u8 num, u16 period, u16 pwmWidth);
void Servo_UsmartDebugConfig(u8 num, int tranPwm);


void Servo_UsmartPrintStatus(u8 num, const char *configName);
void Arm_UsmartPrintStatus(const char *configName);


#endif

