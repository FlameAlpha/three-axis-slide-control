/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "main.h"

int test;
u8 set_char[10]={'0','0','0','0','0','0','0','0','0','0'};
extern bool get_sure;
//TIM variable

    int X_TIM_1=0;
    int Y_TIM_2=0;
    int Z_TIM_3=0;
//TIM Enable
    bool TIM_1_Enable=true;
    bool TIM_6_Enable=true;
    bool TIM_7_Enable=true;

//Move Enable
extern bool Motor_0_Enable;
extern bool Motor_1_Enable;
extern bool Motor_2_Enable;

//Travel Switch variable

    extern bool TR_SW_1;
    extern bool TR_SW_2;
    extern bool TR_SW_3;
    extern bool TR_SW_4;
    extern bool TR_SW_5;
    extern bool TR_SW_6;

    extern bool play_square;
    extern bool play_circle;
    
extern int X_P;
extern int Y_P;
extern int Z_P;

//int x=2000,y=0;
extern bool Move_true;

bool PWM_Enable_0=true;
bool PWM_Enable_1=true;
bool PWM_Enable_2=true;

int PWM_Count_0;
int PWM_Count_1;
int PWM_Count_2;

int period_0=0,period_1=0,period_2=0;
extern int R;
extern int x;
extern int y;
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}


void EXTI9_5_IRQHandler (void)
{ 
}
void TIM1_UP_IRQHandler()
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);       
        if(period_0 < 5) {
            GPIO_SetBits(GPIOA,GPIO_Pin_0);
        }
        else{
            GPIO_ResetBits(GPIOA,GPIO_Pin_0);
        }
        if(period_1 < 5) {
            GPIO_SetBits(GPIOD,GPIO_Pin_12);
        }
        else{
            GPIO_ResetBits(GPIOD,GPIO_Pin_12);
        }
        if(period_2 < 5) {
            GPIO_SetBits(GPIOB,GPIO_Pin_0);
        }
        else{
            GPIO_ResetBits(GPIOB,GPIO_Pin_0);
        }
        
        if((PWM_Enable_0==true)||(PWM_Count_0>0)) {
            period_0++;
        }
        if((PWM_Enable_1==true)||(PWM_Count_1>0)) {
            period_1++;
            
        }
        if((PWM_Enable_2==true)||(PWM_Count_2>0)) {
            period_2++;
        }
        if(Motor_0_Enable==true)
        if(period_0>=10) {
            PWM_Count_0--;
            if(PWM_Count_0<=0) PWM_Count_0=0;
            period_0=0;
            if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)!=RESET)&&(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)!=RESET)) {
                if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==RESET) X_TIM_1++;
                else X_TIM_1--;
            }
        }
        if(Motor_1_Enable==true)
        if(period_1>=10) {
            period_1=0;
            PWM_Count_1--;
            if(PWM_Count_1<=0) PWM_Count_1=0;
            if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)!=RESET)&&(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)!=RESET)) 
            {
                if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==RESET) Y_TIM_2++;
                else Y_TIM_2--;
            }
        }
        if(Motor_2_Enable==true)
        if(period_2>=10) {
            period_2=0;
            PWM_Count_2--;
            if(PWM_Count_2<=0) PWM_Count_2=0;
            if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)!=RESET)&&(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)!=RESET)) {
            if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==RESET) Z_TIM_3++;
                else Z_TIM_3--;
            }
        }
	}
}
void Step_Control(int num,bool Enable)
{
    switch(num)
    {
        case 0:PWM_Enable_0=Enable; break;
        case 1:PWM_Enable_1=Enable; break;
        case 2:PWM_Enable_2=Enable; break;
        default: break;
    }
}
void Step_Count_Control(int num,int Step_num)
{
    switch(num)
    {
        case 0: PWM_Enable_0=false; PWM_Count_0=Step_num; period_0 =0; break;
        case 1: PWM_Enable_1=false; PWM_Count_1=Step_num; period_1 =0; break;
        case 2: PWM_Enable_2=false; PWM_Count_2=Step_num; period_2 =0; break;
        default: break;
    }
}

void TIM8_UP_IRQHandler()
{
    static int delay=0;
	if(TIM_GetITStatus(TIM8,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM8,TIM_IT_Update);
        delay++;
        if(delay%70==0)
        {
            printf("S%d%d%d%d%d%d",TR_SW_1,TR_SW_2,TR_SW_3,TR_SW_4,TR_SW_5,TR_SW_6);
        }
        if(delay%50==0)
        {
            printf("p%dx%dy%dz",X_TIM_1,Y_TIM_2,Z_TIM_3);
        }
        if(delay>=50*70)  delay=0;
    }
}
int chartoint(unsigned char a)
{
	switch(a)
	{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case '+': return 11;
		case '-': return 12;
	}
	return 10;
}

void USART1_IRQHandler(void)
{
    u8 Res;int count;
	static int n=0;
    int p_x,p_y;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
        //USART_SendData(USART1,Res);	//读取接收到的数据
		if(Res!='#'){			
			set_char[n]=Res;
			n++;
            if(n>9) n=9;
		}
		if(Res=='#')
		{	            
            switch(set_char[0]){
                case '0': 
                    if(set_char[1]=='0') { if(TR_SW_6!=true) GPIO_ResetBits(GPIOB,GPIO_Pin_7); }
                        else { if(TR_SW_5!=true) GPIO_SetBits(GPIOB,GPIO_Pin_7); }
                    if(set_char[2]=='0') { Motor_0_Enable=false; Step_Control(0,false);play_square=false; Move_true=false;}
                        else {Motor_0_Enable=true;Step_Control(0,true);}
                break;
                case '1': 
                    if(set_char[1]=='0') { if(TR_SW_3!=true) GPIO_ResetBits(GPIOB,GPIO_Pin_8); } 
                        else { if(TR_SW_4!=true) GPIO_SetBits(GPIOB,GPIO_Pin_8); } 
                    if(set_char[2]=='0') { Motor_1_Enable=false; Step_Control(1,false);play_square=false; Move_true=false;}
                        else { Motor_1_Enable=true;Step_Control(1,true);}
                break;
                case '2': 
                    if(set_char[1]=='0') { if(TR_SW_2!=true) GPIO_ResetBits(GPIOB,GPIO_Pin_9); }
                        else { if(TR_SW_1!=true) GPIO_SetBits(GPIOB,GPIO_Pin_9);}
                    if(set_char[2]=='0') { Motor_2_Enable=false; Step_Control(2,false);play_square=false; Move_true=false;}
                        else { Motor_2_Enable=true; Step_Control(2,true);}
                break;
                        
                case '5': 
                    if(set_char[1]=='0') { 
                        play_square = false; 
                        Motor_2_Enable=false;
                        Motor_0_Enable=false;
                        Motor_1_Enable=false;}
                        else { play_square = true; 
                        Motor_2_Enable=true;
                        Motor_0_Enable=true;
                        Motor_1_Enable=true;
                        }
                    if(set_char[2]=='0') { }
                        else {  }
                break; 
                case '6': 
                    if(set_char[1]=='0') { 
                    play_circle = false; 
                    x=R;y=0; 
                    Motor_2_Enable=false;
                    Motor_0_Enable=false;
                    Step_Control(0,true);
                    Step_Control(1,true);
                    Step_Control(2,true);
                    }
                    else { play_circle = true; x=R;y=0;}
                    if(set_char[2]=='0') { }
                        else {  }
                break;                                   
                case 'p': 
                    p_x=chartoint(set_char[1])*1000+chartoint(set_char[2])*100+chartoint(set_char[3])*10+chartoint(set_char[4]);
                    p_y=chartoint(set_char[5])*1000+chartoint(set_char[6])*100+chartoint(set_char[7])*10+chartoint(set_char[8]);
                    X_P=p_x;
                    Y_P=p_y;
                    Move_true=true;
                break;
                case 'g':
                    get_sure=true;
                case 'm':
                    //count=chartoint(set_char[1])*1000+chartoint(set_char[2])*100+chartoint(set_char[3])*10+chartoint(set_char[4]);
                    GPIO_ResetBits(GPIOB,GPIO_Pin_7);
                    Motor_0_Enable=true;                    
                    Step_Count_Control(0,12);
                break; 
                
                }
                
            n=0;            
        } 
    }
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

