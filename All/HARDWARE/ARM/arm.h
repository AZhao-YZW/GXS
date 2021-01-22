/***********************************************************************************

***********************************************************************************/
#ifndef _ARM_H
#define _ARM_H

#include "sys.h"
#include "servo.h"

extern u8 text1_flag;
extern u8 text2_flag;


/* 系统调用 */
void Servo_Scan(void);
void Arm_Action(void);
void Arm_ActConfig(void);
/* 用户调用 */
void Arm_ActChoose(u8 choose);

	
#endif


