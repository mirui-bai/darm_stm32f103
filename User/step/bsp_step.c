/**
  ******************************************************************************
  * @file    bsp_step.c
  * @author  bai
  * @version V1.0
  * @date    2020.4.28
  * @brief   步进电机应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者 STM32 开发板 （vet6）
  *
  ******************************************************************************
  */


#include "bsp_step.h"

//#include "delay.h"


//方向脚初始化
void Steps_DIR_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* 开启相应的 Px时钟 */
	RCC_APB2PeriphClockCmd( STEP1_DIR_GPIO_CLK |\
													STEP2_DIR_GPIO_CLK |\
													STEP3_DIR_GPIO_CLK |\
													STEP4_DIR_GPIO_CLK , ENABLE);
	/* step 初始DIR GPIO口模式  速度 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* step1 初始DIR GPIO口  */
	GPIO_InitStructure.GPIO_Pin = STEP1_DIR_GPIO_PIN;
	GPIO_Init(STEP1_DIR_GPIO_PORT, &GPIO_InitStructure);

	/* step2 初始DIR GPIO口  */
	GPIO_InitStructure.GPIO_Pin = STEP2_DIR_GPIO_PIN;
	GPIO_Init(STEP2_DIR_GPIO_PORT, &GPIO_InitStructure);

	/* step3 初始DIR GPIO口  */
	GPIO_InitStructure.GPIO_Pin = STEP3_DIR_GPIO_PIN;
	GPIO_Init(STEP3_DIR_GPIO_PORT, &GPIO_InitStructure);

	/* step4 初始DIR GPIO口  */
	GPIO_InitStructure.GPIO_Pin = STEP4_DIR_GPIO_PIN;
	GPIO_Init(STEP4_DIR_GPIO_PORT, &GPIO_InitStructure);

	//根据设定参数初始化
	GPIO_SetBits(STEP1_DIR_GPIO_PORT,STEP1_DIR_GPIO_PIN); 
	GPIO_SetBits(STEP2_DIR_GPIO_PORT,STEP2_DIR_GPIO_PIN);
	GPIO_SetBits(STEP3_DIR_GPIO_PORT,STEP3_DIR_GPIO_PIN);
	GPIO_SetBits(STEP4_DIR_GPIO_PORT,STEP4_DIR_GPIO_PIN);
}

////使能脚初始化
//void Steps_EN_Init(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;

//	/* 开启相应的 Px时钟 */
//	RCC_APB2PeriphClockCmd( STEP1_DIR_GPIO_CLK , ENABLE);
//	/* step 初始DIR GPIO口模式  速度 */
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

//	/* step1 初始DIR GPIO口  */
//	GPIO_InitStructure.GPIO_Pin = STEP1_DIR_GPIO_PIN;
//	GPIO_Init(STEP1_DIR_GPIO_PORT, &GPIO_InitStructure);


//	//根据设定参数初始化
//	GPIO_SetBits(STEP1_DIR_GPIO_PORT,STEP1_DIR_GPIO_PIN); 

//}


//steps引脚初始化
void Steps_STPE_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd( STEP1_STEP_GPIO_CLK |\
													STEP2_STEP_GPIO_CLK |\
													STEP3_STEP_GPIO_CLK |\
													STEP4_STEP_GPIO_CLK, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    
	//STEP_GPIO_REMAP_FUN();


	//设置该引脚为复用输出功能,输出TIMx的PWM脉冲波形
	/* step 初始STEP GPIO口 模式速度 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* step1 初始STEP GPIO口*/
	GPIO_InitStructure.GPIO_Pin = STEP1_STEP_GPIO_PIN;
	GPIO_Init(STEP1_STEP_GPIO_PORT, &GPIO_InitStructure);

	 /* step2 初始STEP GPIO口  */
	GPIO_InitStructure.GPIO_Pin = STEP2_STEP_GPIO_PIN;
	GPIO_Init(STEP2_STEP_GPIO_PORT, &GPIO_InitStructure);

	/* step3 初始STEP GPIO口  */
	GPIO_InitStructure.GPIO_Pin = STEP3_STEP_GPIO_PIN;
	GPIO_Init(STEP3_STEP_GPIO_PORT, &GPIO_InitStructure);

	/* step4 初始STEP GPIO口  */
	GPIO_InitStructure.GPIO_Pin = STEP4_STEP_GPIO_PIN;
	GPIO_Init(STEP4_STEP_GPIO_PORT, &GPIO_InitStructure);

    
  //！！！！！配置完复用功能后，此时输出为低电平，似乎难以修改

}


//TIMx初始化 
void Steps_TIM_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  RCC_APB1PeriphClockCmd(STEP_TIM_CLK, ENABLE);    //使能定时器4时钟
		
	//#define		STEP_INIT_FREQ						500
	//#define		STEP_INIT_PSC							71

 	//初始化TIMx
  TIM_TimeBaseStructure.TIM_Period = STEP_TIM_ARR(STEP_INIT_F,STEP_INIT_PSC); //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
  TIM_TimeBaseStructure.TIM_Prescaler = STEP_INIT_PSC; //设置用来作为TIMx时钟频率除数的预分频值 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
  TIM_TimeBaseInit(STEP_TIMx, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

  //初始化TIMx Channel_1234 PWM模式     
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
  //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //关闭比较输出使能
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
  
  TIM_OC1Init(STEP_TIMx, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIMx OC1
  //TIM_OC1PreloadConfig(STEP_TIMx, TIM_OCPreload_Enable);  //使能TIMx在CCR1上的预装载寄存器
  
  TIM_OC2Init(STEP_TIMx, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIMx OC2
  //TIM_OC2PreloadConfig(STEP_TIMx, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
  
  TIM_OC3Init(STEP_TIMx, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIMx OC3
  //TIM_OC3PreloadConfig(STEP_TIMx, TIM_OCPreload_Enable);  //使能TIMx在CCR3上的预装载寄存器
  
  TIM_OC4Init(STEP_TIMx, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIMx OC4
  //TIM_OC4PreloadConfig(STEP_TIMx, TIM_OCPreload_Enable);  //使能TIMx在CCR4上的预装载寄存器

  TIM_CCxCmd(STEP_TIMx,TIM_Channel_1,TIM_CCx_Disable);//关闭TIMx通道1
  TIM_CCxCmd(STEP_TIMx,TIM_Channel_2,TIM_CCx_Disable);//关闭TIMx通道2
  TIM_CCxCmd(STEP_TIMx,TIM_Channel_3,TIM_CCx_Disable);//关闭TIMx通道3
  TIM_CCxCmd(STEP_TIMx,TIM_Channel_4,TIM_CCx_Disable);//关闭TIMx通道4
  
  TIM_Cmd(STEP_TIMx, DISABLE);  //先不使能TIMx 
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
	
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_1,TIM_CCx_Enable);//开启TIMx通道1
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_2,TIM_CCx_Enable);//开启TIMx通道2
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_3,TIM_CCx_Enable);//开启TIMx通道3
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_4,TIM_CCx_Enable);//开启TIMx通道4
	TIM_Cmd(STEP_TIMx, ENABLE);//必须放在最后使能
	
}

void Steps_stop(void)
{
	TIM_SetCompare2(STEP_TIMx, 0);
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_1,TIM_CCx_Enable);//关闭TIMx通道1
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_2,TIM_CCx_Enable);//关闭TIMx通道2
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_3,TIM_CCx_Enable);//关闭TIMx通道3
	TIM_CCxCmd(STEP_TIMx,TIM_Channel_4,TIM_CCx_Enable);//关闭TIMx通道4
	TIM_Cmd(STEP_TIMx, DISABLE);

}


