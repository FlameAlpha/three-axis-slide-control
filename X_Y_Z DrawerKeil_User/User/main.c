/**
  ******************************************************************************
  * @file    main.c
  * @author  Flame
  * @version 3.0
  * @date    07/06/2017
  * @brief   Main program body.

  ******************************************************************************


Includes ------------------------------------------------------------------*/
#include "main.h"
//
extern int PWM_Count_0;
extern int PWM_Count_1;
extern int PWM_Count_2;
//play signals
    bool play_square=false;
    bool play_circle=false;
    bool get_sure=true;
//Move Enable
    bool Motor_0_Enable;
    bool Motor_1_Enable;
    bool Motor_2_Enable;
//Move true
    bool Front_Rear_true;
    bool Up_Down_true;
    bool Right_Left_true;
    
// Max variable
    int X_MAX;
    int Y_MAX;
    int Z_MAX;

//Travel Switch variable

    bool TR_SW_1;
    bool TR_SW_2;
    bool TR_SW_3;
    bool TR_SW_4;
    bool TR_SW_5;
    bool TR_SW_6;

//Travel Switch count variable
    
    bool TR_SW_Var_1;
    bool TR_SW_Var_2;
    bool TR_SW_Var_3;
    bool TR_SW_Var_4;
    bool TR_SW_Var_5;
    bool TR_SW_Var_6;
    
    bool Tr_Sw_Enable_1=false;
    bool Tr_Sw_Enable_2=false;
    bool Tr_Sw_Enable_3=false;
    
//TIM variable
extern int X_TIM_1;
extern int Y_TIM_2;
extern int Z_TIM_3;

//Postion
int X_P=0;
int Y_P=0;
int Z_P=0;
int x=4000,y=0;
int R=4000;
bool Move_true=false;
//重定义fputc函数
int fputc(int ch, FILE *f)
{      
	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART1->DR = (u8) ch; 
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕            
	return ch;
}

void Travel_switch_control()
{
    int x=10;
    static int delay_0=0,delay_1=0,delay_2=0,delay_3=0,delay_4=0,delay_5=0;
    if(Tr_Sw_Enable_1==true){
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==RESET) {
    TR_SW_1=true; 
    Z_TIM_3=0;   
    if(TR_SW_Var_4==false)printf("p%dx%dy%dz",X_TIM_1,Y_TIM_2,Z_TIM_3); 
    if((TR_SW_Var_1==false)||(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_9)==SET)) 
    delay_0++; 
    if(delay_0>x){
    Motor_2_Enable=false;
    delay_0=0;
    }
    TR_SW_Var_1=true;
    }
    else {TR_SW_1=false; TR_SW_Var_1=false;delay_0=0;}
    
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==RESET) {
    TR_SW_2=true; 
    if((TR_SW_Var_2==false)||(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_9)==RESET)) 
     delay_1++; 
    if(delay_1>x){
    Motor_2_Enable=false;
    delay_1=0;
    }    
    TR_SW_Var_2=true;
    }
    else {TR_SW_2=false; TR_SW_Var_2=false;delay_1=0;}
    }
    if(Tr_Sw_Enable_2==true){
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)==RESET) { 
    TR_SW_3=true;   
    if((TR_SW_Var_3==false)||(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_8)==RESET))
     delay_2++; 
    if(delay_2>x){
    Motor_1_Enable=false;
    delay_2=0;
    }   
    TR_SW_Var_3=true;
    }
    else {TR_SW_3=false; TR_SW_Var_3=false;delay_2=0;}
    
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)==RESET) { 
    TR_SW_4=true; 
    Y_TIM_2=0;
    if(TR_SW_Var_4==false)printf("p%dx%dy%dz",X_TIM_1,Y_TIM_2,Z_TIM_3);        
    if((TR_SW_Var_4==false)||(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_8)==SET)) 
     delay_3++; 
    if(delay_3>x){
    Motor_1_Enable=false;
    delay_3=0;
    }
    TR_SW_Var_4=true;
    }
    else {TR_SW_4=false; TR_SW_Var_4=false;delay_3=0;}
    }
    if(Tr_Sw_Enable_3==true){
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)==RESET) { 
    TR_SW_5=true; 
    X_TIM_1=0;    
    if(TR_SW_Var_5==false)printf("p%dx%dy%dz",X_TIM_1,Y_TIM_2,Z_TIM_3);        
    if((TR_SW_Var_5==false)||(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_7)==SET)) 
     delay_4++; 
    if(delay_4>x){
    Motor_0_Enable=false;
    delay_4=0;
    }
    TR_SW_Var_5=true;
    }
    else {TR_SW_5=false; TR_SW_Var_5=false;delay_4=0;}
    
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)==RESET) { 
    TR_SW_6=true; 
    if((TR_SW_Var_6==false)||(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_7)==RESET)) 
    delay_5++; 
    if(delay_5>x){
    Motor_0_Enable=false;
    delay_5=0;
    }
    TR_SW_Var_6=true;}
    else {TR_SW_6=false; TR_SW_Var_6=false; delay_5=0;}
    }
}

void Postion_Init()
{
    //210
    GPIO_SetBits(GPIOB,GPIO_Pin_9);
    //110
    GPIO_SetBits(GPIOB,GPIO_Pin_8);   
    //010
    GPIO_SetBits(GPIOB,GPIO_Pin_7); 
    
    Motor_2_Enable=true;
    Motor_0_Enable=true;
    Motor_1_Enable=true;
    
    X_TIM_1=0;
    Y_TIM_2=0;
    Z_TIM_3=0;
    
    TIM_Cmd(TIM1,ENABLE);
    TIM_Cmd(TIM7,ENABLE);
    TIM_Cmd(TIM6,ENABLE);
}


void Play_Square()
{
    if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)==RESET)&&(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)==RESET))
    {
         GPIO_SetBits(GPIOB,GPIO_Pin_7);
    }
    if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)==RESET)&&(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)==RESET))
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_8);
    }
    if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)==RESET)&&(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)==RESET))
    {
         GPIO_ResetBits(GPIOB,GPIO_Pin_7);
    }
    if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)==RESET)&&(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)==RESET))
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_8);
    }
    if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==RESET)){       
        GPIO_ResetBits(GPIOB,GPIO_Pin_9);
        
    }
    if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==RESET))
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_9);
    }
    Motor_2_Enable=true;
    Motor_0_Enable=true;
    Motor_1_Enable=true;
}


void MoveToPostion()
{

    if(X_P>X_TIM_1) { 
    GPIO_ResetBits(GPIOB,GPIO_Pin_7); 
    GPIO_SetBits(GPIOC,GPIO_Pin_0); 
    }
    if(X_P<X_TIM_1) { 
    GPIO_SetBits(GPIOB,GPIO_Pin_7); 
    GPIO_SetBits(GPIOC,GPIO_Pin_0); 
    }
    if(X_P==X_TIM_1) { 
    GPIO_ResetBits(GPIOC,GPIO_Pin_0);     
    }  
    
    if(Y_P>Y_TIM_2) { 
    GPIO_ResetBits(GPIOB,GPIO_Pin_8); 
    GPIO_SetBits(GPIOC,GPIO_Pin_1); 
    }
    if(Y_P<Y_TIM_2) { 
    GPIO_SetBits(GPIOB,GPIO_Pin_8); 
    GPIO_SetBits(GPIOC,GPIO_Pin_1); 
    }
    if(Y_P==Y_TIM_2) { 
    GPIO_ResetBits(GPIOC,GPIO_Pin_1); 
    }
    
    if((Y_P==Y_TIM_2)&&(X_P==X_TIM_1)){
    Move_true=false;    
    }   
}

void Motor_Enable_Control()
{
    if(Motor_0_Enable==true) GPIO_SetBits(GPIOC,GPIO_Pin_0); 
    else GPIO_ResetBits(GPIOC,GPIO_Pin_0); 
    if(Motor_1_Enable==true) GPIO_SetBits(GPIOC,GPIO_Pin_1); 
    else GPIO_ResetBits(GPIOC,GPIO_Pin_1); 
    if(Motor_2_Enable==true) GPIO_SetBits(GPIOC,GPIO_Pin_2); 
    else GPIO_ResetBits(GPIOC,GPIO_Pin_2); 
}
int abs_user(int x)
{
    if(x<0) return -x;
    else return x; 
}
void Play_Circle()
{
    int x2,y2;
    static int case_n = 1;
    int error1,error2,error3;
    if(play_circle)
    {
    if((PWM_Count_0==0)&&(PWM_Count_2==0)){ 
    switch(case_n){
        case 1:            
            x2=x-1;
            y2=y+1;
        
            GPIO_ResetBits(GPIOB,GPIO_Pin_7); 
            GPIO_ResetBits(GPIOB,GPIO_Pin_9); 
            
            if(x==0) case_n = 2;          
            
            break;
        case 2:            
            x2=x-1;
            y2=y-1;

            GPIO_ResetBits(GPIOB,GPIO_Pin_7); 
            GPIO_SetBits(GPIOB,GPIO_Pin_9); 
                        
            if(y==0) case_n = 3;             
            
            break;
        case 3: 
            x2=x+1;
            y2=y-1;
        
            GPIO_SetBits(GPIOB,GPIO_Pin_7); 
            GPIO_SetBits(GPIOB,GPIO_Pin_9); 
            if(x==0) case_n=4; 
            break;
        case 4:
            x2=x+1;
            y2=y+1;
           
            GPIO_SetBits(GPIOB,GPIO_Pin_7); 
            GPIO_ResetBits(GPIOB,GPIO_Pin_9); 
            if(y==0) case_n=1; 
            break;
        }
            error1=abs_user(x2*x2+y*y-R*R);
            error2=abs_user(x*x+y2*y2-R*R);
            error3=abs_user(x2*x2+y2*y2-R*R);

            if((error1<=error3)&&(error1<=error2)) { Step_Count_Control(0,1); x=x2; y=y; }
            if((error2<=error1)&&(error2<=error3)) { Step_Count_Control(2,1); x=x; y=y2; }
            if((error3<=error1)&&(error3<=error2)) { Step_Count_Control(0,1); Step_Count_Control(2,1); x=x2; y=y2; }
            
            Motor_2_Enable=true;
            Motor_0_Enable=true; 
        }
    }
        else
        {
            x=R;y=0;
            case_n=1;
        }
}
int main(void)
{ 
	Init_NVIC_PriorityGroupConfig();
	USART_Init_Config(115200);
    PWM_Define_Init();
    TIM_Init();
    LED_Config();
    Travel_Switch_Config();
    Motor_Config();   
    Postion_Init();  
	while(1)
	{	
        if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==RESET)
        Tr_Sw_Enable_1=true;
        if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)==RESET)
        Tr_Sw_Enable_2=true;
        if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)==RESET)
        Tr_Sw_Enable_3=true;
        
        if(play_square==true) Play_Square();
        
        if(Move_true==true) MoveToPostion();
        
        Play_Circle();
        
        Travel_switch_control();   
        
        Motor_Enable_Control();
	}
}



