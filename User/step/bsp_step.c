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


typedef int bool;

typedef struct {
	uint16_t	counter_xyz;
	uint16_t	n_step;			//����
	uint16_t	step_speed;		//Ƶ��
	bool	step_dir;

	uint16_t	timer_psc
	uint16_t	step_counts;
} stepper_t;

static stepper_t stepper_1_t;
static stepper_t stepper_2_t;
static stepper_t stepper_3_t;



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


/*******************************************************************************
* �� �� ��					: Step_x_TIMER_Init
* ��������					: ��ʱ��ʱ����ʼ��
* ��    ��					:	�����루TIM 2~7����ʼ�� ����ʱ��������ʱ����������жϹر�PWM(TIM234)
* ��    ��					: ��
*******************************************************************************/
void Step_x_TIMER_Init(TIM_TypeDef* TIMER ,u16 Period, u16 Prescaler, u8 PP)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(TIMER_CLK, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = Period - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler - 1;

	if (TIMER != TIM6 |TIMER !=TIM7 )
	{
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;}
	
	TIM_TimeBaseInit(TIMER, &TIM_TimeBaseStructure);

	TIM_ClearITPendingBit(TIMER, TIM_IT_Update);
	TIM_ITConfig(TIMER, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIMER, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	if (TIMER == TIM2) { NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; }
	else if (TIMER == TIM3) { NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; }
	else if (TIMER == TIM4) { NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; }
	else if (TIMER == TIM5) { NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; }
	else if (TIMER == TIM6) { NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn; }
	else if (TIMER == TIM7) { NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; }

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PP;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	
	NVIC_DisableIRQ(TIM2_IRQn);
	if (TIMER == TIM2) { NVIC_DisableIRQ(TIM2_IRQn); }
	else if (TIMER == TIM3) { NVIC_DisableIRQ(TIM3_IRQn); }
	else if (TIMER == TIM4) { NVIC_DisableIRQ(TIM4_IRQn); }
	else if (TIMER == TIM5) { NVIC_DisableIRQ(TIM5_IRQn); }
	else if (TIMER == TIM6) { NVIC_DisableIRQ(TIM6_IRQn); }
	else if (TIMER == TIM7) { NVIC_DisableIRQ(TIM7_IRQn); }
}


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
	Step_x_TIMER_Init(TIM5, 1, 1, 1);
	Step_x_TIMER_Init(TIM6, 1, 1, 1);
	Step_x_TIMER_Init(TIM7, 1, 1, 1);
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
* �� �� ��					: TIM5_IRQHandler
* ��������					: ���������ʼ�����˿ڣ�ʱ�ӵȵȣ�
* ��    ��					:	��
* ��    ��					: ��
*******************************************************************************/
void TIM5_IRQHandler(void)
{
	if ((TIM5->SR & 0x0001) != 0)                 // ����жϱ�־
	{
		TIM5->SR &= ~(1<<0);                        // �жϱ�־��λ
		TIM5->CNT = 0;															//������λ
		NVIC_DisableIRQ(TIM5_IRQn);
    // �ر�PWM���
    Step_x_stop(STEP_1_TIMx, STEP_1_TIM_CHANNEL);
		// GPIO_Write(STEP_PORT, (GPIO_ReadOutputData(STEP_PORT) & ~STEP_MASK) | (step_port_invert_mask & STEP_MASK));
	}
}

void TIM6_IRQHandler(void)
{
	if ((TIM6->SR & 0x0001) != 0)                 // ����жϱ�־
	{
		TIM6->SR &= ~(1<<0);                        // �жϱ�־��λ
		TIM6->CNT = 0;															//������λ
		NVIC_DisableIRQ(TIM6_IRQn);
    // �ر�PWM���
    Step_x_stop(STEP_1_TIMx, STEP_1_TIM_CHANNEL);
	}
}

void TIM7_IRQHandler(void)
{
	if ((TIM7->SR & 0x0001) != 0)                 // ����жϱ�־
	{
		TIM7->SR &= ~(1<<0);                        // �жϱ�־��λ
		TIM7->CNT = 0;															//������λ
		NVIC_DisableIRQ(TIM7_IRQn);
    // �ر�PWM���
    Step_x_stop(STEP_1_TIMx, STEP_1_TIM_CHANNEL);
	}
}



 /*******************************************************************************
 * �� �� ��					: Step_go
 * ��������					: �������
 * ��    ��					:	��
 * ��    ��					: ��
 *******************************************************************************/
void Step_go(void)
{

	if (stepper_1_t.step_dir == FORWARD) STEP_1_FORWARD;
	else STEP_1_BACK;



}





void Step_PWM_SET()
{


}


 /*******************************************************************************
 * �� �� ��					: Step_x_run
 * ��������					: �������x �Թ̶�Ƶ��f�˶�
 * ��    ��					:	��
 * ��    ��					: ��
 *******************************************************************************/
void Step_x_run(int f, TIM_TypeDef* STEP_x_TIMx, uint16_t STEP_x_TIM_CHANNEL)
{
	int arr;
	arr =	STEP_TIM_ARR(f,STEP_INIT_PSC);
	TIM_SetAutoreload(STEP_x_TIMx, arr);
	if 			( STEP_x_TIM_CHANNEL == TIM_Channel_1 )	{TIM_SetCompare1(STEP_x_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));}
	else if ( STEP_x_TIM_CHANNEL == TIM_Channel_2 )	{TIM_SetCompare2(STEP_x_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));}
	else if ( STEP_x_TIM_CHANNEL == TIM_Channel_3 )	{TIM_SetCompare3(STEP_x_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));}	
	else if ( STEP_x_TIM_CHANNEL == TIM_Channel_4 )	{TIM_SetCompare4(STEP_x_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));}

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


// /*******************************************************************************
// * �� �� ��					: Step_x_stop
// * ��������					: �������xֹͣ
// * ��    ��					:	��
// * ��    ��					: ��
// *******************************************************************************/
void Step_x_stop(TIM_TypeDef* STEP_x_TIMx, uint16_t STEP_x_TIM_CHANNEL)
{

	// if 			(STEP_x_TIM_CHANNEL == TIM_Channel_1) {TIM_SetCompare1(STEP_x_TIMx, 0);}
 //  else if (STEP_x_TIM_CHANNEL == TIM_Channel_2)	{TIM_SetCompare2(STEP_x_TIMx, 0);}
 //  else if (STEP_x_TIM_CHANNEL == TIM_Channel_3)	{TIM_SetCompare3(STEP_x_TIMx, 0);}
 //  else if (STEP_x_TIM_CHANNEL == TIM_Channel_4)	{TIM_SetCompare4(STEP_x_TIMx, 0);}
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



/*******************************************************************************
* �� �� ��					: Steps_run
* ��������					: ���������ͬ�����˶�
* ��    ��					:	��
* ��    ��					: ��
*******************************************************************************/
void Steps_run(int f)
{	
	Step_1_run(f);
	Step_2_run(f);
	Step_3_run(f);
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


