#ifndef __BSP_STEP_H
#define __BSP_STEP_H

#include "stm32f10x.h"

/********************定时器通道**************************/

#define 	STEP_TIMx  								TIM4
#define		STEP_TIM_CLK							RCC_APB1Periph_TIM4


/******************STEP 初始参数 **********************/
// 定时器TIMx频率 -> 电机速度
#define		STEP_INIT_F								100		// 100 Hz
#define		STEP_INIT_PSC							71		//72预分频
#define		STEP_DUTY_CYCLE						50		//50%

#define		STEP_TIM_ARR(f,psc)						(int)((SystemCoreClock / ((psc + 1) * f)) -1)
#define		STEP_TIM_CCR(duty_cycle,arr)	(int)(duty_cycle*(arr + 1)/100)

////使能脚 和led 绿灯共用GPIO引脚，方便观察，后期改掉
//#define		STEP_EN_GPIO_PORT					GPIOB
//#define		STEP_EN_GPIO_PIN					GPIO_Pin_0



//引脚重映射
#define   STEP_GPIO_REMAP_FUN() 		GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);

/******************* STEP 1 ****************************/

#define STEP1_STEP_GPIO_PORT				GPIOB
#define STEP1_STEP_GPIO_CLK					(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define STEP1_STEP_GPIO_PIN					GPIO_Pin_6

#define STEP1_DIR_GPIO_PORT					GPIOB
#define STEP1_DIR_GPIO_CLK					(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define STEP1_DIR_GPIO_PIN					GPIO_Pin_5


/******************* STEP 2 ****************************/

#define STEP2_STEP_GPIO_PORT				GPIOB
#define STEP2_STEP_GPIO_CLK					(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define STEP2_STEP_GPIO_PIN					GPIO_Pin_7

#define STEP2_DIR_GPIO_PORT					GPIOA
#define STEP2_DIR_GPIO_CLK					(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define STEP2_DIR_GPIO_PIN					GPIO_Pin_8


/******************* STEP 3 ****************************/

#define STEP3_STEP_GPIO_PORT				GPIOB
#define STEP3_STEP_GPIO_CLK					(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define STEP3_STEP_GPIO_PIN					GPIO_Pin_8

#define STEP3_DIR_GPIO_PORT					GPIOC
#define STEP3_DIR_GPIO_CLK					(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO)
#define STEP3_DIR_GPIO_PIN					GPIO_Pin_6


/******************* STEP 4 ****************************/

#define STEP4_STEP_GPIO_PORT				GPIOB
#define STEP4_STEP_GPIO_CLK					(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define STEP4_STEP_GPIO_PIN					GPIO_Pin_9


#define STEP4_DIR_GPIO_PORT					GPIOC
#define STEP4_DIR_GPIO_CLK					(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO)
#define STEP4_DIR_GPIO_PIN					GPIO_Pin_7


void Steps_DIR_Init(void);
void Steps_STPE_Init(void);
void Steps_TIM_Init(void);
void Steps_Config(void);
void Steps_run(int f);
void Steps_stop(void);


#endif /*__BSP_STEP_H*/


