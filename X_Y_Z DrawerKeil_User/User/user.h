#ifndef __USER_H__
#define __USER_H__

#include "main.h"

extern void Init_NVIC_PriorityGroupConfig(void);
extern void USART_Init_Config(int bound);
extern void LED_Config(void); 
extern void PWM_TIM_Init(u16 arr,u16 psc);
extern void Motor_Config(void);
extern void TIM_Init(void);
extern void Travel_Switch_Config(void);
extern void PWM_Define_Init(void);
#endif
