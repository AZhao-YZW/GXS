#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

//#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
//#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1
//#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP) 
#define KEY0 PEin(4)
#define KEY1 PEin(3)
#define WK_UP PAin(0)

//按键按下
#define KEY0_PRES 1
#define KEY1_PRES 2
#define WKUP_PRES 3

void KEY_Init(void);
u8 KEY_Scan(u8 mode);

#endif

