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
#define enable1 { TIM_SetCompare1(TIM4,200); TIM_1_Enable=true;}
#define enable2 { TIM_SetCompare3(TIM3,200); TIM_6_Enable=true;}
#define enable3 { TIM_SetCompare1(TIM4,200); TIM_SetCompare3(TIM3,200); TIM_1_Enable=true; TIM_6_Enable=true;}
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
int x=2000,y=0;
extern bool Move_true;
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
    static int delay_x=0;
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
        if((GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_0)==Bit_SET)&&(TR_SW_5!=true)&&(TR_SW_6!=true))
        if(TIM_1_Enable){
        if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_7)==Bit_RESET) X_TIM_1++;
        else X_TIM_1--;
        delay_x++;
            if(delay_x>=50)
            {
                printf("p%dx%dy%dz",X_TIM_1,Y_TIM_2,Z_TIM_3);
                delay_x=0;
            }
        }
	}
}
void TIM7_IRQHandler()
{
    static int delay_y=0;
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update);
        if((GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_1)==Bit_SET)&&(TR_SW_4!=true)&&(TR_SW_3!=true))
        if(TIM_7_Enable){
        if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_8)==Bit_RESET) Y_TIM_2++;
        else Y_TIM_2--;
        delay_y++;
            if(delay_y>=50)
            {
                printf("p%dx%dy%dz",X_TIM_1,Y_TIM_2,Z_TIM_3);
                delay_y=0;
            }
        }      
	}
}

void TIM6_IRQHandler()
{
    static int delay_z=0;
   	if(TIM_GetITStatus(TIM6,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
        if((GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_2)==Bit_SET)&&(TR_SW_1!=true)&&(TR_SW_2!=true))
        if(TIM_6_Enable){
        if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_9)==Bit_RESET) Z_TIM_3++;
        else Z_TIM_3--;         
        delay_z++;
            if(delay_z>=50)
            {
                printf("p%dx%dy%dz",X_TIM_1,Y_TIM_2,Z_TIM_3);
                delay_z=0;
            }
        }
	} 
}
int abs_user(int x)
{
    if(x<0) return -x;
    else return x; 
}
void TIM8_UP_IRQHandler()
{
    static int delay=0;
    int x2,y2;
    static int case_n = 1;
    int error1,error2,error3;
	if(TIM_GetITStatus(TIM8,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM8,TIM_IT_Update);
        delay++;
        if(delay>=50)
        {
            printf("S%d%d%d%d%d%d",TR_SW_1,TR_SW_2,TR_SW_3,TR_SW_4,TR_SW_5,TR_SW_6);
            delay=0;
        }
        if(play_circle)
        {
        GPIO_ResetBits(GPIOC,GPIO_Pin_0);
        GPIO_ResetBits(GPIOC,GPIO_Pin_2);
        TIM_SetCompare1(TIM4,400); 
        TIM_SetCompare3(TIM3,400);
        TIM_6_Enable=false;
        TIM_1_Enable=false;    
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
            error1=abs_user(x2*x2+y*y-2000*2000);
            error2=abs_user(x*x+y2*y2-2000*2000);
            error3=abs_user(x2*x2+y2*y2-2000*2000);

            if((error1<=error3)&&(error1<=error2)) { enable1; x=x2; y=y; }
            if((error2<=error1)&&(error2<=error3)) { enable2; x=x; y=y2; }
            if((error3<=error1)&&(error3<=error2)) { enable3; x=x2; y=y2; }
            
            GPIO_SetBits(GPIOC,GPIO_Pin_0);
            GPIO_SetBits(GPIOC,GPIO_Pin_2); 
        }
        else
        {
            TIM_SetCompare1(TIM4,200); 
            TIM_SetCompare3(TIM3,200);
            TIM_6_Enable=true;
            TIM_1_Enable=true; 
            x=2000;y=0;
            case_n=1;
        }
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

void USART3_IRQHandler()
{ 
}

void USART1_IRQHandler(void)
{
    u8 Res;
	static int n=0;
    int p_x,p_y;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
        USART_SendData(USART1,Res);	//读取接收到的数据
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
                    if(set_char[2]=='0') { GPIO_ResetBits(GPIOC,GPIO_Pin_0); play_square=false; Move_true=false;}
                        else { GPIO_SetBits(GPIOC,GPIO_Pin_0);}
                break;
                case '1': 
                    if(set_char[1]=='0') { if(TR_SW_3!=true) GPIO_ResetBits(GPIOB,GPIO_Pin_8); } 
                        else { if(TR_SW_4!=true) GPIO_SetBits(GPIOB,GPIO_Pin_8); } 
                    if(set_char[2]=='0') { GPIO_ResetBits(GPIOC,GPIO_Pin_1); play_square=false; Move_true=false;}
                        else { GPIO_SetBits(GPIOC,GPIO_Pin_1);}
                break;
                case '2': 
                    if(set_char[1]=='0') { if(TR_SW_2!=true) GPIO_ResetBits(GPIOB,GPIO_Pin_9); }
                        else { if(TR_SW_1!=true) GPIO_SetBits(GPIOB,GPIO_Pin_9);}
                    if(set_char[2]=='0') { GPIO_ResetBits(GPIOC,GPIO_Pin_2); play_square=false; Move_true=false;}
                        else { GPIO_SetBits(GPIOC,GPIO_Pin_2); }
                break;
                        
                case '5': 
                    if(set_char[1]=='0') { play_square = false; GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);}
                        else { play_square = true; GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);}
                    if(set_char[2]=='0') { }
                        else {  }
                break; 
                case '6': 
                    if(set_char[1]=='0') { play_circle = false; x=2000;y=0; GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_2);}
                        else { play_circle = true; x=2000;y=0;}
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

