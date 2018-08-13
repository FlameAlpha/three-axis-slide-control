#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "user.h"
#include "stdio.h"	
#include "math.h"

extern int X_TIM_1;
extern int Y_TIM_2;
extern int Z_TIM_3;

typedef enum {false = 0,true = 1} bool;

extern void Step_Count_Control(int num,int Step_num);
extern void Step_Control(int num,bool Enable);
#endif

