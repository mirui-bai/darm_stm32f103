#include "bsp_exti.h"

 

static void NVIC_Config(void)
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	/*����NIVC���ȼ���һ */	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/* Key1 �������ȼ� */
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Key2 �������ȼ� */
	NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
	NVIC_Init(&NVIC_InitStructure);

}

void EXIT_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	 /* �����ж����ȼ� */
	NVIC_Config();
	/* ����KEY1��KEY2 �� GPIO ʱ�� */
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK, ENABLE);	
	RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLK, ENABLE);
	
/*--------------------------KEY1����-----------------------------*/
	/* KEY1 ��ʼIO�� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	/* ѡ��ģʽ ��������*/
	GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;	/* ѡ������ */
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);


	/* KEY1 EXTI ѡ���ź�Դ*/
	GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE,KEY1_INT_EXTI_PINSOURCE);
	EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;
	/* KEY1 EXTI�����ж�ģʽ*/	
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		/* KEY1 EXTI ���������ش��� */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	/* KEY1 EXTIʹ�� */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
/*--------------------------KEY1����-----------------------------*/
	/* KEY2 ��ʼIO�� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	/* ѡ��ģʽ ��������*/
	GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
	GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);
	
	/* KEY2 EXTI ѡ���ź�Դ*/
	GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE,KEY2_INT_EXTI_PINSOURCE);
	EXTI_InitStructure.EXTI_Line =  KEY2_INT_EXTI_LINE;
	

	/* KEY2 EXTI�����ж�ģʽ*/	
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* KEY2 EXTI ���������ش��� */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	/* KEY2 EXTIʹ�� */
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

