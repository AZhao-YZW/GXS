/***********************************************************************************

***********************************************************************************/
#ifndef _ARM_H
#define _ARM_H

#include "sys.h"
#include "servo.h"

extern u8 text1_flag;
extern u8 text2_flag;


/* ϵͳ���� */
void Servo_Scan(void);
void Arm_Action(void);
void Arm_ActConfig(void);
/* �û����� */
void Arm_ActChoose(u8 choose);

	
#endif


