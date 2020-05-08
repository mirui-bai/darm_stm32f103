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


/*******************************************************************************
* �� �� ��					: Steps_DIR_Init
* ��������					: ����DIR�˿ڳ�ʼ��
* ��    ��					: 
* ��    ��					: ��
*******************************************************************************/
void Steps_DIR_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* ������Ӧ�� Pxʱ�� */
	RCC_APB2PeriphClockCmd( STEP_1_DIR_GPIO_CLK |\
													STEP_2_DIR_GPIO_CLK |\
													STEP_3_DIR_GPIO_CLK, ENABLE);
	/* step ��ʼDIR GPIO��ģʽ  �ٶ� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* step_1 ��ʼDIR GPIO��  */
	GPIO_InitStructure.GPIO_Pin = STEP_1_DIR_GPIO_PIN;
	GPIO_Init(STEP_1_DIR_GPIO_PORT, &GPIO_InitStructure);

	/* step_2 ��ʼDIR GPIO��  */
	GPIO_InitStructure.GPIO_Pin = STEP_2_DIR_GPIO_PIN;
	GPIO_Init(STEP_2_DIR_GPIO_PORT, &GPIO_InitStructure);

	/* step_3 ��ʼDIR GPIO��  */
	GPIO_InitStructure.GPIO_Pin = STEP_3_DIR_GPIO_PIN;
	GPIO_Init(STEP_3_DIR_GPIO_PORT, &GPIO_InitStructure);

//	/* step_4 ��ʼDIR GPIO��  */
//	GPIO_InitStructure.GPIO_Pin = STEP_4_DIR_GPIO_PIN;
//	GPIO_Init(STEP_4_DIR_GPIO_PORT, &GPIO_InitStructure);

	//�����趨������ʼ��
	GPIO_SetBits(STEP_1_DIR_GPIO_PORT,STEP_1_DIR_GPIO_PIN); 
	GPIO_SetBits(STEP_2_DIR_GPIO_PORT,STEP_2_DIR_GPIO_PIN);
	GPIO_SetBits(STEP_3_DIR_GPIO_PORT,STEP_3_DIR_GPIO_PIN);
//	GPIO_SetBits(STEP_4_DIR_GPIO_PORT,STEP_4_DIR_GPIO_PIN);
}


/*******************************************************************************
* �� �� ��					: Steps_EN_Init
* ��������					: ����ʹ��EN�˿ڳ�ʼ��
* ��    ��					: ��
* ��    ��					: ��
*******************************************************************************/
//void Steps_EN_Init(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;

//	/* ������Ӧ�� Pxʱ�� */
//	RCC_APB2PeriphClockCmd( STEP_1_DIR_GPIO_CLK , ENABLE);
//	/* step ��ʼDIR GPIO��ģʽ  �ٶ� */
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

//	/* step_1 ��ʼDIR GPIO��  */
//	GPIO_InitStructure.GPIO_Pin = STEP_1_DIR_GPIO_PIN;
//	GPIO_Init(STEP_1_DIR_GPIO_PORT, &GPIO_InitStructure);


//	//�����趨������ʼ��
//	GPIO_SetBits(STEP_1_DIR_GPIO_PORT,STEP_1_DIR_GPIO_PIN); 

//}


/*******************************************************************************
* �� �� ��					: Steps_STPE_Init
* ��������					: ����step�˿ڳ�ʼ��
* ��    ��					: ��
* ��    ��					: ��
*******************************************************************************/
void Steps_STPE_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd( STEP_1_STEP_GPIO_CLK |\
													STEP_2_STEP_GPIO_CLK |\
													STEP_3_STEP_GPIO_CLK, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��

  // RCC_APB2PeriphClockCmd( STEP_4_STEP_GPIO_CLK, ENABLE);
    
	//STEP_GPIO_REMAP_FUN();	// �˿��ض���

	//���ø�����Ϊ�����������,���TIMx��PWM���岨��
	/* step ��ʼSTEP GPIO�� ģʽ�ٶ� */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* step_1 ��ʼSTEP GPIO��*/
	GPIO_InitStructure.GPIO_Pin = STEP_1_STEP_GPIO_PIN;
	GPIO_Init(STEP_1_STEP_GPIO_PORT, &GPIO_InitStructure);

	 /* step_2 ��ʼSTEP GPIO��  */
	GPIO_InitStructure.GPIO_Pin = STEP_2_STEP_GPIO_PIN;
	GPIO_Init(STEP_2_STEP_GPIO_PORT, &GPIO_InitStructure);

	/* step_3 ��ʼSTEP GPIO��  */
	GPIO_InitStructure.GPIO_Pin = STEP_3_STEP_GPIO_PIN;
	GPIO_Init(STEP_3_STEP_GPIO_PORT, &GPIO_InitStructure);

	//	/* step_4 ��ʼSTEP GPIO��  */
	//	GPIO_InitStructure.GPIO_Pin = STEP_4_STEP_GPIO_PIN;
	//	GPIO_Init(STEP_4_STEP_GPIO_PORT, &GPIO_InitStructure);
  
}


 /*******************************************************************************
 * �� �� ��					: Step_x_TIMx_Init
 * ��������					: STEP_x ��Ӧ��ʱ��TIMx��ʼ����
 * ��    ��					: STEP_x_TIM_CLK (TIMʱ��), STEP_x_TIMx (��ʱ��x), STEP_x_TIM_CHANNEL (ͨ��1��2��3��4)
 * ��    ��					: ��
 *******************************************************************************/
 void Step_x_TIMx_Init(uint32_t STEP_x_TIM_CLK,TIM_TypeDef* STEP_x_TIMx, uint16_t STEP_x_TIM_CHANNEL)
 {
 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   TIM_OCInitTypeDef  TIM_OCInitStructure;

   RCC_APB1PeriphClockCmd(STEP_x_TIM_CLK, ENABLE);    //ʹ�ܶ�ʱ��4ʱ��

  	//��ʼ��TIMx
   TIM_TimeBaseStructure.TIM_Period = STEP_TIM_ARR(STEP_INIT_F,STEP_INIT_PSC); //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
   TIM_TimeBaseStructure.TIM_Prescaler = STEP_INIT_PSC; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
   TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
   TIM_TimeBaseInit(STEP_x_TIMx, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	

   //��ʼ��TIMx Channel_x PWMģʽ     
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
   //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�رձȽ����ʹ��
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
   //TIM_OCInitStructure.TIM_Pulse =(STEP_TIM_ARR(STEP_INIT_F,STEP_INIT_PSC) + 1)*STEP_DUTY_CYCLE/100;

  
   if (STEP_x_TIM_CHANNEL == TIM_Channel_1)  
   {	
   	TIM_OC1Init(STEP_x_TIMx, &TIM_OCInitStructure);	//����Tָ���Ĳ�����ʼ������TIMx OC1;
   		// ����������TIM_Pulseֵ�����ô�װ�벶��ȽϼĴ���������ֵ
 		TIM_OC1PreloadConfig(STEP_x_TIMx, TIM_OCPreload_Enable); //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
 	}  
   else if (STEP_x_TIM_CHANNEL == TIM_Channel_2)	
   {
   	TIM_OC2Init(STEP_x_TIMx, &TIM_OCInitStructure);	
  	TIM_OC2PreloadConfig(STEP_x_TIMx, TIM_OCPreload_Enable); 
   }
   else if (STEP_x_TIM_CHANNEL == TIM_Channel_3) 
   {
   	TIM_OC3Init(STEP_x_TIMx, &TIM_OCInitStructure);	
   	TIM_OC3PreloadConfig(STEP_x_TIMx, TIM_OCPreload_Enable); 
   }
   else if (STEP_x_TIM_CHANNEL == TIM_Channel_4)	
   {	
   	TIM_OC4Init(STEP_x_TIMx, &TIM_OCInitStructure);
   	TIM_OC4PreloadConfig(STEP_x_TIMx, TIM_OCPreload_Enable); 
   }

   TIM_CCxCmd(STEP_x_TIMx,STEP_x_TIM_CHANNEL,TIM_CCx_Disable);//�ر�TIMxͨ��1
  
   TIM_Cmd(STEP_x_TIMx, DISABLE);  //�Ȳ�ʹ��TIMx 
 }



// void TIM2_Init(void)
// {
// 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//   TIM_OCInitTypeDef  TIM_OCInitStructure;

//   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    //ʹ�ܶ�ʱ��4ʱ��

//  	//��ʼ��TIMx
//   TIM_TimeBaseStructure.TIM_Period = 9999; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//   TIM_TimeBaseStructure.TIM_Prescaler = 71; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
//   TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
//   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//   TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	

//   //��ʼ��TIMx Channel_x PWMģʽ     
//   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
//   //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�رձȽ����ʹ��
//   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
//   //TIM_OCInitStructure.TIM_Pulse =(STEP_TIM_ARR(STEP_INIT_F,STEP_INIT_PSC) + 1)*STEP_DUTY_CYCLE/100;

  

// 	TIM_OC4Init(TIM2, &TIM_OCInitStructure);	//����Tָ���Ĳ�����ʼ������TIMx OC1;
// 		// ����������TIM_Pulseֵ�����ô�װ�벶��ȽϼĴ���������ֵ
// 	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���


//   TIM_CCxCmd(TIM2,TIM_Channel_4,TIM_CCx_Disable);//�ر�TIMxͨ��1
  
//   TIM_Cmd(TIM2, DISABLE);  //�Ȳ�ʹ��TIMx 
// }




/*******************************************************************************
* �� �� ��					: Steps_TIMs_Init
* ��������					: ���ͨ�ö�ʱ����ʼ��
* ��    ��					:	��
* ��    ��					: ��
*******************************************************************************/
void Steps_TIMs_Init(void)
{
	Step_x_TIMx_Init(STEP_1_TIM_CLK, STEP_1_TIMx, STEP_1_TIM_CHANNEL);
	Step_x_TIMx_Init(STEP_2_TIM_CLK, STEP_2_TIMx, STEP_2_TIM_CHANNEL);
	Step_x_TIMx_Init(STEP_3_TIM_CLK, STEP_3_TIMx, STEP_3_TIM_CHANNEL);

}


/*******************************************************************************
* �� �� ��					: Steps_Config
* ��������					: ���������ʼ�����˿ڣ�ʱ�ӵȵȣ�
* ��    ��					:	��
* ��    ��					: ��
*******************************************************************************/
void Steps_Config(void)
{
	Steps_DIR_Init();
	Steps_STPE_Init();
	Steps_TIMs_Init();

}


 /*******************************************************************************
 * �� �� ��					: Step_x_run
 * ��������					: �������x �Թ̶�Ƶ��f�˶�
 * ��    ��					:	��
 * ��    ��					: ��
 *******************************************************************************/
//  void Step_1_run(int f)
//  {	
//  	int arr;
//  	arr =	STEP_TIM_ARR(f,STEP_INIT_PSC);
//  	TIM_SetAutoreload(TIM2, arr);
//  	TIM_SetCompare4(TIM2, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));

//  	TIM_CCxCmd(TIM2,TIM_Channel_4,TIM_CCx_Enable);//����TIMxͨ��

//  	TIM_Cmd(TIM2, ENABLE);//����������ʹ��
//  }


// void Step_2_run(int f)
// {	
// 	int arr;
// 	arr =	STEP_TIM_ARR(f,STEP_INIT_PSC);
// 	TIM_SetAutoreload(TIM3, arr);
// 	TIM_SetCompare1(TIM3, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));

// 	TIM_CCxCmd(TIM3,TIM_Channel_1,TIM_CCx_Enable);//����TIMxͨ��

// 	TIM_Cmd(TIM3, ENABLE);//����������ʹ��
// }
void Step_x_run(int f, TIM_TypeDef* STEP_x_TIMx, uint16_t STEP_x_TIM_CHANNEL)
{
	int arr;
	arr =	STEP_TIM_ARR(f,STEP_INIT_PSC);
	TIM_SetAutoreload(STEP_x_TIMx, arr);
	TIM_SetCompare1(STEP_x_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));

	TIM_CCxCmd(STEP_x_TIMx,STEP_x_TIM_CHANNEL,TIM_CCx_Enable);//����TIMxͨ��

	TIM_Cmd(STEP_x_TIMx, ENABLE);//����������ʹ��
}

void Step_1_run(int f)
{	
	Step_x_run(f, STEP_1_TIMx, STEP_1_TIM_CHANNEL);
}

void Step_2_run(int f)
{	
	Step_x_run(f, STEP_2_TIMx, STEP_2_TIM_CHANNEL);
}

void Step_3_run(int f)
{	
	Step_x_run(f, STEP_3_TIMx, STEP_3_TIM_CHANNEL);
}

// void Step_4_run(int f)
// {	
// 	Step_x_run(f, STEP_4_TIMx, STEP_4_TIM_CHANNEL);
// }

// void Step_2_run(int f)
// {	
// 	int arr;
// 	arr =	STEP_TIM_ARR(f,STEP_INIT_PSC);
// 	TIM_SetAutoreload(STEP_2_TIMx, arr);
// 	TIM_SetCompare1(STEP_2_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));

// 	TIM_CCxCmd(STEP_2_TIMx,STEP_2_TIM_CHANNEL,TIM_CCx_Enable);//����TIMxͨ��

// 	TIM_Cmd(STEP_2_TIMx, ENABLE);//����������ʹ��
// }


// void Step_3_run(int f)
// {	
// 	int arr;
// 	arr =	STEP_TIM_ARR(f,STEP_INIT_PSC);
// 	TIM_SetAutoreload(STEP_3_TIMx, arr);
// 	TIM_SetCompare1(STEP_3_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));

// 	TIM_CCxCmd(STEP_3_TIMx,STEP_3_TIM_CHANNEL,TIM_CCx_Enable);//����TIMxͨ��

// 	TIM_Cmd(STEP_3_TIMx, ENABLE);//����������ʹ��
// }


// void Step_4_run(int f)
// {	
// 	int arr;
// 	arr =	STEP_TIM_ARR(f,STEP_INIT_PSC);
// 	TIM_SetAutoreload(STEP_4_TIMx, arr);
// 	TIM_SetCompare1(STEP_4_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));

// 	TIM_CCxCmd(STEP_4_TIMx,STEP_4_TIM_CHANNEL,TIM_CCx_Enable);//����TIMxͨ��

// 	TIM_Cmd(STEP_4_TIMx, ENABLE);//����������ʹ��
// }



// /*******************************************************************************
// * �� �� ��					: Step_x_stop
// * ��������					: �������xֹͣ
// * ��    ��					:	��
// * ��    ��					: ��
// *******************************************************************************/
void Step_x_stop(TIM_TypeDef* STEP_x_TIMx, uint16_t STEP_x_TIM_CHANNEL)
{

	if 			(STEP_x_TIM_CHANNEL == TIM_Channel_1) {TIM_SetCompare1(STEP_x_TIMx, 0);}
  else if (STEP_x_TIM_CHANNEL == TIM_Channel_2)	{TIM_SetCompare2(STEP_x_TIMx, 0);}
  else if (STEP_x_TIM_CHANNEL == TIM_Channel_3)	{TIM_SetCompare3(STEP_x_TIMx, 0);}
  else if (STEP_x_TIM_CHANNEL == TIM_Channel_4)	{TIM_SetCompare4(STEP_x_TIMx, 0);}
	TIM_CCxCmd(STEP_x_TIMx,STEP_x_TIM_CHANNEL,TIM_CCx_Enable);//�ر�TIMxͨ��
	TIM_Cmd(STEP_x_TIMx, DISABLE);
}

void Step_1_stop(void)
{
	Step_x_stop(STEP_1_TIMx, STEP_1_TIM_CHANNEL);
}

void Step_2_stop(void)
{
	Step_x_stop(STEP_2_TIMx, STEP_2_TIM_CHANNEL);
}

void Step_3_stop(void)
{
	Step_x_stop(STEP_3_TIMx, STEP_3_TIM_CHANNEL);
}

// void Step_4_stop(void)
// {
// 	Step_x_stop(STEP_4_TIMx, STEP_4_TIM_CHANNEL);
// }


// void Step_2_stop(void)
// {
// 	if (STEP_2_TIM_CHANNEL == TIM_Channel_1)  {TIM_SetCompare1(STEP_2_TIMx, 0);}
//   if (STEP_2_TIM_CHANNEL == TIM_Channel_2)	{TIM_SetCompare2(STEP_2_TIMx, 0);}
//   if (STEP_2_TIM_CHANNEL == TIM_Channel_3)	{TIM_SetCompare3(STEP_2_TIMx, 0);}
//   if (STEP_2_TIM_CHANNEL == TIM_Channel_4)	{TIM_SetCompare4(STEP_2_TIMx, 0);}
// 	TIM_CCxCmd(STEP_2_TIMx,STEP_2_TIM_CHANNEL,TIM_CCx_Enable);//�ر�TIMxͨ��
// 	TIM_Cmd(STEP_2_TIMx, DISABLE);
// }

// void Step_3_stop(void)
// {	
// 	if (STEP_3_TIM_CHANNEL == TIM_Channel_1)  {TIM_SetCompare1(STEP_3_TIMx, 0);}
//   if (STEP_3_TIM_CHANNEL == TIM_Channel_2)	{TIM_SetCompare2(STEP_3_TIMx, 0);}
//   if (STEP_3_TIM_CHANNEL == TIM_Channel_3)	{TIM_SetCompare3(STEP_3_TIMx, 0);}
//   if (STEP_3_TIM_CHANNEL == TIM_Channel_4)	{TIM_SetCompare4(STEP_3_TIMx, 0);}
// 	TIM_CCxCmd(STEP_3_TIMx,STEP_3_TIM_CHANNEL,TIM_CCx_Enable);//�ر�TIMxͨ��
// 	TIM_Cmd(STEP_3_TIMx, DISABLE);
// }

// void Step_4_stop(void)
// {
// 	if (STEP_4_TIM_CHANNEL == TIM_Channel_1)  {TIM_SetCompare1(STEP_4_TIMx, 0);}
//   if (STEP_4_TIM_CHANNEL == TIM_Channel_2)	{TIM_SetCompare2(STEP_4_TIMx, 0);}
//   if (STEP_4_TIM_CHANNEL == TIM_Channel_3)	{TIM_SetCompare3(STEP_4_TIMx, 0);}
//   if (STEP_4_TIM_CHANNEL == TIM_Channel_4)	{TIM_SetCompare4(STEP_4_TIMx, 0);}
// 	TIM_CCxCmd(STEP_4_TIMx,STEP_4_TIM_CHANNEL,TIM_CCx_Enable);//�ر�TIMxͨ��
// 	TIM_Cmd(STEP_4_TIMx, DISABLE);
// }


/*******************************************************************************
* �� �� ��					: Steps_run
* ��������					: ���������ͬ�����˶�
* ��    ��					:	��
* ��    ��					: ��
*******************************************************************************/
void Steps_run(int f)
{	
	Step_1_run(f);
	Step_2_run(f * 2);
	Step_3_run(f * 3);
	// Step_4_run(f);
}


/*******************************************************************************
* �� �� ��					: Steps_stop
* ��������					: �������ͬʱֹͣ
* ��    ��					:	��
* ��    ��					: ��
*******************************************************************************/
void Steps_stop(void)
{
	Step_1_stop();
	Step_2_stop();
	Step_3_stop();
	// Step_4_stop();
}


