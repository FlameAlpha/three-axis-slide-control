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

//play signals
    bool play_square=false;
    bool play_circle=false;
    bool get_sure=true;
    
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
    if(Tr_Sw_Enable_1==true){
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)==RESET) {
    TR_SW_1=true; 
    //printf("S%d%d%d%d%d%d",TR_SW_1,TR_SW_2,TR_SW_3,TR_SW_4,TR_SW_5,TR_SW_6);
    Z_TIM_3=0;     
    if(TR_SW_Var_1==false)printf("p%dx%dy%dz",X_TIM_1,Y_TIM_2,Z_TIM_3);
    if((TR_SW_Var_1==false)||(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_9)==SET)) 
    GPIO_ResetBits(GPIOC,GPIO_Pin_2); 
    TR_SW_Var_1=true;
    }
    else {TR_SW_1=false; TR_SW_Var_1=false;}
    
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)==RESET) {
    TR_SW_2=true; 
    Z_MAX=Z_TIM_3; //get_sure=true;
    //printf("S%d%d%d%d%d%d",TR_SW_1,TR_SW_2,TR_SW_3,TR_SW_4,TR_SW_5,TR_SW_6);
    if((TR_SW_Var_2==false)||(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_9)==RESET)) 
    GPIO_ResetBits(GPIOC,GPIO_Pin_2); 
    TR_SW_Var_2=true;
    }
    else {TR_SW_2=false; TR_SW_Var_2=false;}
    }
    if(Tr_Sw_Enable_2==true){
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)==RESET) { 
    TR_SW_3=true;  
    //printf("S%d%d%d%d%d%d",TR_SW_1,TR_SW_2,TR_SW_3,TR_SW_4,TR_SW_5,TR_SW_6);
    Y_TIM_2=3096;
    Y_MAX=Y_TIM_2;    //get_sure=true;
    if((TR_SW_Var_3==false)||(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_8)==RESET))
    GPIO_ResetBits(GPIOC,GPIO_Pin_1); 
    TR_SW_Var_3=true;
    }
    else {TR_SW_3=false; TR_SW_Var_3=false;}
    
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)==RESET) { 
    TR_SW_4=true; 
    //printf("S%d%d%d%d%d%d",TR_SW_1,TR_SW_2,TR_SW_3,TR_SW_4,TR_SW_5,TR_SW_6);
    Y_TIM_2=0;
    if(TR_SW_Var_4==false)printf("p%dx%dy%dz",X_TIM_1,Y_TIM_2,Z_TIM_3);        
    if((TR_SW_Var_4==false)||(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_8)==SET)) 
    GPIO_ResetBits(GPIOC,GPIO_Pin_1); 
    TR_SW_Var_4=true;
    }
    else {TR_SW_4=false; TR_SW_Var_4=false;}
    }
    if(Tr_Sw_Enable_3==true){
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)==RESET) { 
    TR_SW_5=true; 
    //printf("S%d%d%d%d%d%d",TR_SW_1,TR_SW_2,TR_SW_3,TR_SW_4,TR_SW_5,TR_SW_6);
    X_TIM_1=0;    
    if(TR_SW_Var_5==false)printf("p%dx%dy%dz",X_TIM_1,Y_TIM_2,Z_TIM_3);        
    if((TR_SW_Var_5==false)||(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_7)==SET)) 
    GPIO_ResetBits(GPIOC,GPIO_Pin_0); 
    TR_SW_Var_5=true;
    }
    else {TR_SW_5=false; TR_SW_Var_5=false;}
    
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)==RESET) { 
    TR_SW_6=true; 
    //printf("S%d%d%d%d%d%d",TR_SW_1,TR_SW_2,TR_SW_3,TR_SW_4,TR_SW_5,TR_SW_6);
    X_TIM_1=2583;
    X_MAX=X_TIM_1; //get_sure=true;
    if((TR_SW_Var_6==false)||(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_7)==RESET)) 
    GPIO_ResetBits(GPIOC,GPIO_Pin_0); 
    TR_SW_Var_6=true;}
    else {TR_SW_6=false; TR_SW_Var_6=false;}
    }
}

void Postion_Init()
{
    //210
    GPIO_SetBits(GPIOB,GPIO_Pin_9);
    GPIO_SetBits(GPIOC,GPIO_Pin_2); 
    //110
    GPIO_SetBits(GPIOB,GPIO_Pin_8);
    GPIO_SetBits(GPIOC,GPIO_Pin_1);     
    //010
    GPIO_SetBits(GPIOB,GPIO_Pin_7); 
    GPIO_SetBits(GPIOC,GPIO_Pin_0);

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
    GPIO_SetBits(GPIOC,GPIO_Pin_0);
    GPIO_SetBits(GPIOC,GPIO_Pin_1);
    GPIO_SetBits(GPIOC,GPIO_Pin_2);
}


void MoveToPostion()
{
    //A0 0 D12 1 B0 2
//    TIM_SetCompare1(TIM4,200);	//D12
//    TIM_SetCompare1(TIM2,200);	//A0
//    TIM_SetCompare3(TIM3,200);    //B0
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
int main(void)
{ 
	Init_NVIC_PriorityGroupConfig();
	USART_Init_Config(115200);
    PWM_TIM_Init(400,72);
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
        
        if(get_sure==true)  {   printf("g%dx%dy%dz",X_MAX,Z_MAX,Y_MAX); get_sure=false; }
        Travel_switch_control();   
	}
}



