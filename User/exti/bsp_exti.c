#include "bsp_exti.h"

 

static void NVIC_Config(void)
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	/*配置NIVC优先级组一 */	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/* Key1 配置优先级 */
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Key2 配置优先级 */
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
	NVIC_Init(&NVIC_InitStructure);

}

void EXIT_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	 /* 配置中断优先级 */
	NVIC_Config();
	/* 开启KEY1、KEY2 的 GPIO 时钟 */
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK, ENABLE);	
	RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLK, ENABLE);
	
/*--------------------------KEY1配置-----------------------------*/
	/* KEY1 初始IO口 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	/* 选择模式 浮空输入*/
	GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;	/* 选择引脚 */
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);


	/* KEY1 EXTI 选择信号源*/
	GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE,KEY1_INT_EXTI_PINSOURCE);
	EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;
	/* KEY1 EXTI设置中断模式*/	
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		/* KEY1 EXTI 设置上升沿触发 */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	/* KEY1 EXTI使能 */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
/*--------------------------KEY1配置-----------------------------*/
	/* KEY2 初始IO口 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	/* 选择模式 浮空输入*/
	GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
	GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);
	
	/* KEY2 EXTI 选择信号源*/
	GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE,KEY2_INT_EXTI_PINSOURCE);
	EXTI_InitStructure.EXTI_Line =  KEY2_INT_EXTI_LINE;
	

	/* KEY2 EXTI设置中断模式*/	
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* KEY2 EXTI 设置上升沿触发 */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	/* KEY2 EXTI使能 */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

