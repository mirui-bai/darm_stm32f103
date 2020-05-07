/**
  ******************************************************************************
  * @file    bsp_step.c
  * @author  bai
  * @version V1.0
  * @date    2020.4.28
  * @brief   �������Ӧ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ ��vet6��
  *
  ******************************************************************************
  */


#include "bsp_step.h"

//#include "delay.h"


//����ų�ʼ��
void Steps_DIR_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* ������Ӧ�� Pxʱ�� */
	RCC_APB2PeriphClockCmd( STEP1_DIR_GPIO_CLK |\
													STEP2_DIR_GPIO_CLK |\
													STEP3_DIR_GPIO_CLK |\
													STEP4_DIR_GPIO_CLK , ENABLE);
	/* step ��ʼDIR GPIO��ģʽ  �ٶ� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* step1 ��ʼDIR GPIO��  */
	GPIO_InitStructure.GPIO_Pin = STEP1_DIR_GPIO_PIN;
	GPIO_Init(STEP1_DIR_GPIO_PORT, &GPIO_InitStructure);

	/* step2 ��ʼDIR GPIO��  */
	GPIO_InitStructure.GPIO_Pin = STEP2_DIR_GPIO_PIN;
	GPIO_Init(STEP2_DIR_GPIO_PORT, &GPIO_InitStructure);

	/* step3 ��ʼDIR GPIO��  */
	GPIO_InitStructure.GPIO_Pin = STEP3_DIR_GPIO_PIN;
	GPIO_Init(STEP3_DIR_GPIO_PORT, &GPIO_InitStructure);

	/* step4 ��ʼDIR GPIO��  */
	GPIO_InitStructure.GPIO_Pin = STEP4_DIR_GPIO_PIN;
	GPIO_Init(STEP4_DIR_GPIO_PORT, &GPIO_InitStructure);

	//�����趨������ʼ��
	GPIO_SetBits(STEP1_DIR_GPIO_PORT,STEP1_DIR_GPIO_PIN); 
	GPIO_SetBits(STEP2_DIR_GPIO_PORT,STEP2_DIR_GPIO_PIN);
	GPIO_SetBits(STEP3_DIR_GPIO_PORT,STEP3_DIR_GPIO_PIN);
	GPIO_SetBits(STEP4_DIR_GPIO_PORT,STEP4_DIR_GPIO_PIN);
}

////ʹ�ܽų�ʼ��
//void Steps_EN_Init(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;

//	/* ������Ӧ�� Pxʱ�� */
//	RCC_APB2PeriphClockCmd( STEP1_DIR_GPIO_CLK , ENABLE);
//	/* step ��ʼDIR GPIO��ģʽ  �ٶ� */
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

//	/* step1 ��ʼDIR GPIO��  */
//	GPIO_InitStructure.GPIO_Pin = STEP1_DIR_GPIO_PIN;
//	GPIO_Init(STEP1_DIR_GPIO_PORT, &GPIO_InitStructure);


//	//�����趨������ʼ��
//	GPIO_SetBits(STEP1_DIR_GPIO_PORT,STEP1_DIR_GPIO_PIN); 

//}


//steps���ų�ʼ��
void Steps_STPE_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd( STEP1_STEP_GPIO_CLK |\
													STEP2_STEP_GPIO_CLK |\
													STEP3_STEP_GPIO_CLK |\
													STEP4_STEP_GPIO_CLK, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    
	//STEP_GPIO_REMAP_FUN();


	//���ø�����Ϊ�����������,���TIMx��PWM���岨��
	/* step ��ʼSTEP GPIO�� ģʽ�ٶ� */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* step1 ��ʼSTEP GPIO��*/
	GPIO_InitStructure.GPIO_Pin = STEP1_STEP_GPIO_PIN;
	GPIO_Init(STEP1_STEP_GPIO_PORT, &GPIO_InitStructure);

	 /* step2 ��ʼSTEP GPIO��  */
	GPIO_InitStructure.GPIO_Pin = STEP2_STEP_GPIO_PIN;
	GPIO_Init(STEP2_STEP_GPIO_PORT, &GPIO_InitStructure);

	/* step3 ��ʼSTEP GPIO��  */
	GPIO_InitStructure.GPIO_Pin = STEP3_STEP_GPIO_PIN;
	GPIO_Init(STEP3_STEP_GPIO_PORT, &GPIO_InitStructure);

	/* step4 ��ʼSTEP GPIO��  */
	GPIO_InitStructure.GPIO_Pin = STEP4_STEP_GPIO_PIN;
	GPIO_Init(STEP4_STEP_GPIO_PORT, &GPIO_InitStructure);

    
  //���������������긴�ù��ܺ󣬴�ʱ���Ϊ�͵�ƽ���ƺ������޸�

}


//TIMx��ʼ�� 
void Steps_TIM_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  RCC_APB1PeriphClockCmd(STEP_TIM_CLK, ENABLE);    //ʹ�ܶ�ʱ��4ʱ��
		
	//#define		STEP_INIT_FREQ						500
	//#define		STEP_INIT_PSC							71

 	//��ʼ��TIMx
  TIM_TimeBaseStructure.TIM_Period = STEP_TIM_ARR(STEP_INIT_F,STEP_INIT_PSC); //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
  TIM_TimeBaseStructure.TIM_Prescaler = STEP_INIT_PSC; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
  TIM_TimeBaseInit(STEP_TIMx, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

  //��ʼ��TIMx Channel_1234 PWMģʽ     
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
  //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�رձȽ����ʹ��
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
  
  TIM_OC1Init(STEP_TIMx, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIMx OC1
  //TIM_OC1PreloadConfig(STEP_TIMx, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
  
  TIM_OC2Init(STEP_TIMx, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIMx OC2
  //TIM_OC2PreloadConfig(STEP_TIMx, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
  
  TIM_OC3Init(STEP_TIMx, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIMx OC3
  //TIM_OC3PreloadConfig(STEP_TIMx, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR3�ϵ�Ԥװ�ؼĴ���
  
  TIM_OC4Init(STEP_TIMx, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIMx OC4
  //TIM_OC4PreloadConfig(STEP_TIMx, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR4�ϵ�Ԥװ�ؼĴ���

  TIM_CCxCmd(STEP_TIMx,TIM_Channel_1,TIM_CCx_Disable);//�ر�TIMxͨ��1
  TIM_CCxCmd(STEP_TIMx,TIM_Channel_2,TIM_CCx_Disable);//�ر�TIMxͨ��2
  TIM_CCxCmd(STEP_TIMx,TIM_Channel_3,TIM_CCx_Disable);//�ر�TIMxͨ��3
  TIM_CCxCmd(STEP_TIMx,TIM_Channel_4,TIM_CCx_Disable);//�ر�TIMxͨ��4
  
  TIM_Cmd(STEP_TIMx, DISABLE);  //�Ȳ�ʹ��TIMx 
}


void Steps_Config(void)
{
	Steps_DIR_Init();
	Steps_STPE_Init();
	Steps_TIM_Init();

}

void Steps_run(int f)
{	
	int arr;
	arr =	STEP_TIM_ARR(f,STEP_INIT_PSC);
	TIM_SetAutoreload(STEP_TIMx, arr);
	TIM_SetCompare1(STEP_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));	// 50% = 500/(arr + 1) * 100%
	TIM_SetCompare2(STEP_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));
	TIM_SetCompare3(STEP_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));
	TIM_SetCompare4(STEP_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));
	
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_1,TIM_CCx_Enable);//����TIMxͨ��1
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_2,TIM_CCx_Enable);//����TIMxͨ��2
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_3,TIM_CCx_Enable);//����TIMxͨ��3
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_4,TIM_CCx_Enable);//����TIMxͨ��4
	TIM_Cmd(STEP_TIMx, ENABLE);//����������ʹ��
	
}

void Steps_stop(void)
{
	TIM_SetCompare2(STEP_TIMx, 0);
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_1,TIM_CCx_Enable);//�ر�TIMxͨ��1
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_2,TIM_CCx_Enable);//�ر�TIMxͨ��2
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_3,TIM_CCx_Enable);//�ر�TIMxͨ��3
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_4,TIM_CCx_Enable);//�ر�TIMxͨ��4
	TIM_Cmd(STEP_TIMx, DISABLE);

}


