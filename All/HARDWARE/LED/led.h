#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define LED0 PBout(5)
#define LED1 PEout(5)

void LED_Init(void);
void LED1_Toggle(void);
void LED2_Toggle(void);

#endif

