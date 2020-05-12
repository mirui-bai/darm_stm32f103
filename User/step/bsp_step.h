#ifndef __BSP_STEP_H
#define __BSP_STEP_H

#include "stm32f10x.h"

/********************定时器选择通道选择************************/

#define 	STEP_1_TIMx  								TIM2
#define		STEP_1_TIM_CLK							RCC_APB1Periph_TIM2

#define 	STEP_2_TIMx  								TIM3
#define		STEP_2_TIM_CLK							RCC_APB1Periph_TIM3

#define 	STEP_3_TIMx  								TIM4
#define		STEP_3_TIM_CLK							RCC_APB1Periph_TIM4

// TIM( 5 、 6 、 7)用来计时
#define		TIMER_CLK										(RCC_APB1Periph_TIM5 | RCC_APB1Periph_TIM6 | RCC_APB1Periph_TIM7 )

#define		STEP_1_TIM_CHANNEL					TIM_Channel_4
#define		STEP_2_TIM_CHANNEL					TIM_Channel_1
#define		STEP_3_TIM_CHANNEL					TIM_Channel_1

// #define 		STEP_4_TIMx  								TIM5
// #define		STEP_4_TIM_CLK							RCC_APB1Periph_TIM5
// #define		STEP_4_TIM_CHANNEL					TIM_Channel_1


/******************STEP 初始参数 **********************/
// 定时器TIMx频率 -> 电机速度
#define		STEP_INIT_F								100		// 100 Hz
#define		STEP_INIT_PSC							71		//72预分频
#define		STEP_DUTY_CYCLE						50		//50%

#define		STEP_TIM_ARR(f,psc)						(int)((SystemCoreClock / ((psc + 1) * f)) -1)
#define		STEP_TIM_CCR(duty_cycle,arr)	(int)(duty_cycle*(arr + 1)/100)

#define		FORWARD					1
#define		BACK						0

#define		STEP_1_FORWARD						GPIO_SetBits(STEP_1_DIR_GPIO_PORT,STEP_1_DIR_GPIO_PIN); 
#define		STEP_1_BACK								GPIO_ResetBits(STEP_1_DIR_GPIO_PORT,STEP_1_DIR_GPIO_PIN);


////使能脚 和led 绿灯共用GPIO引脚，方便观察，后期改掉
//#define		STEP_EN_GPIO_PORT					GPIOB
//#define		STEP_EN_GPIO_PIN					GPIO_Pin_0


//引脚重映射
//#define   STEP_GPIO_REMAP_FUN() 		GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);

/******************* STEP 1 ****************************/

#define STEP_1_STEP_GPIO_PORT				GPIOA
#define STEP_1_STEP_GPIO_CLK				(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define STEP_1_STEP_GPIO_PIN				GPIO_Pin_3

#define STEP_1_DIR_GPIO_PORT				GPIOC
#define STEP_1_DIR_GPIO_CLK					(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO)
#define STEP_1_DIR_GPIO_PIN					GPIO_Pin_8


/******************* STEP 2 ****************************/

#define STEP_2_STEP_GPIO_PORT				GPIOA
#define STEP_2_STEP_GPIO_CLK				(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define STEP_2_STEP_GPIO_PIN				GPIO_Pin_6

#define STEP_2_DIR_GPIO_PORT				GPIOC
#define STEP_2_DIR_GPIO_CLK					(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO)
#define STEP_2_DIR_GPIO_PIN					GPIO_Pin_9


/******************* STEP 3 ****************************/

#define STEP_3_STEP_GPIO_PORT				GPIOB
#define STEP_3_STEP_GPIO_CLK				(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define STEP_3_STEP_GPIO_PIN				GPIO_Pin_6

#define STEP_3_DIR_GPIO_PORT				GPIOC
#define STEP_3_DIR_GPIO_CLK					(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO)
#define STEP_3_DIR_GPIO_PIN					GPIO_Pin_10


/******************* STEP 4 ****************************/

// #define STEP_4_STEP_GPIO_PORT			GPIOB
// #define STEP_4_STEP_GPIO_CLK				(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
// #define STEP_4_STEP_GPIO_PIN				GPIO_Pin_9


// #define STEP_4_DIR_GPIO_PORT				GPIOC
// #define STEP_4_DIR_GPIO_CLK				(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO)
// #define STEP_4_DIR_GPIO_PIN				GPIO_Pin_11


void Steps_DIR_Init(void);
void Steps_STPE_Init(void);
void Step_x_TIMx_Init(uint32_t STEP_x_TIM_CLK,TIM_TypeDef* STEP_x_TIMx, uint16_t STEP_x_TIM_CHANNEL);
void Step_x_TIMER_Init(TIM_TypeDef* TIMER ,u16 Period, u16 Prescaler, u8 PP);
void Steps_TIMs_Init(void);

void TIM5_IRQHandler(void);
void TIM6_IRQHandler(void);
void TIM7_IRQHandler(void);

void Steps_Config(void);
void Step_x_run(int f, TIM_TypeDef* STEP_x_TIMx, uint16_t STEP_x_TIM_CHANNEL);
void Step_1_run(int f);
void Step_2_run(int f);
void Step_3_run(int f);
// void Step_4_run(int f);
void Steps_run(int f);

void Step_x_stop(TIM_TypeDef* STEP_x_TIMx, uint16_t STEP_x_TIM_CHANNEL);
void Step_1_stop(void);
void Step_2_stop(void);
void Step_3_stop(void);
// void Step_4_stop(void);
void Steps_stop(void);


#endif /*__BSP_STEP_H*/


