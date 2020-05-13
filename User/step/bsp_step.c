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


/*******************************************************************************
* 函 数 名					: Steps_DIR_Init
* 函数功能					: 步进DIR端口初始化
* 输    入					: 
* 输    出					: 无
*******************************************************************************/
void GPIO_DIR_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* 开启相应的 Px时钟 */
	RCC_APB2PeriphClockCmd( STEP_1_DIR_GPIO_CLK |\
													STEP_2_DIR_GPIO_CLK |\
													STEP_3_DIR_GPIO_CLK, ENABLE);
	/* step 初始DIR GPIO口模式  速度 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* step_1 初始DIR GPIO口  */
	GPIO_InitStructure.GPIO_Pin = STEP_1_DIR_GPIO_PIN;
	GPIO_Init(STEP_1_DIR_GPIO_PORT, &GPIO_InitStructure);

	/* step_2 初始DIR GPIO口  */
	GPIO_InitStructure.GPIO_Pin = STEP_2_DIR_GPIO_PIN;
	GPIO_Init(STEP_2_DIR_GPIO_PORT, &GPIO_InitStructure);

	/* step_3 初始DIR GPIO口  */
	GPIO_InitStructure.GPIO_Pin = STEP_3_DIR_GPIO_PIN;
	GPIO_Init(STEP_3_DIR_GPIO_PORT, &GPIO_InitStructure);

//	/* step_4 初始DIR GPIO口  */
//	GPIO_InitStructure.GPIO_Pin = STEP_4_DIR_GPIO_PIN;
//	GPIO_Init(STEP_4_DIR_GPIO_PORT, &GPIO_InitStructure);

	//根据设定参数初始化
	GPIO_SetBits(STEP_1_DIR_GPIO_PORT,STEP_1_DIR_GPIO_PIN); 
	GPIO_SetBits(STEP_2_DIR_GPIO_PORT,STEP_2_DIR_GPIO_PIN);
	GPIO_SetBits(STEP_3_DIR_GPIO_PORT,STEP_3_DIR_GPIO_PIN);
//	GPIO_SetBits(STEP_4_DIR_GPIO_PORT,STEP_4_DIR_GPIO_PIN);
}


/*******************************************************************************
* 函 数 名					: Steps_EN_Init
* 函数功能					: 步进使能EN端口初始化
* 输    入					: 无
* 输    出					: 无
*******************************************************************************/
//void Steps_EN_Init(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;

//	/* 开启相应的 Px时钟 */
//	RCC_APB2PeriphClockCmd( STEP_1_DIR_GPIO_CLK , ENABLE);
//	/* step 初始DIR GPIO口模式  速度 */
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

//	/* step_1 初始DIR GPIO口  */
//	GPIO_InitStructure.GPIO_Pin = STEP_1_DIR_GPIO_PIN;
//	GPIO_Init(STEP_1_DIR_GPIO_PORT, &GPIO_InitStructure);


//	//根据设定参数初始化
//	GPIO_SetBits(STEP_1_DIR_GPIO_PORT,STEP_1_DIR_GPIO_PIN); 

//}

/*******************************************************************************
* 函 数 名					: GPIO_LIMIT_Init
* 函数功能					: 限位开关端口初始化
* 输    入					: 无
* 输    出					: 无
*******************************************************************************/
void GPIO_LIMIT_Init(void)
{

}


/*******************************************************************************
* 函 数 名					: Steps_STPE_Init
* 函数功能					: 步进step端口初始化
* 输    入					: 无
* 输    出					: 无
*******************************************************************************/
void GPIO_STPE_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd( STEP_1_STEP_GPIO_CLK |\
													STEP_2_STEP_GPIO_CLK |\
													STEP_3_STEP_GPIO_CLK, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟

  // RCC_APB2PeriphClockCmd( STEP_4_STEP_GPIO_CLK, ENABLE);
    
	//STEP_GPIO_REMAP_FUN();	// 端口重定义

	//设置该引脚为复用输出功能,输出TIMx的PWM脉冲波形
	/* step 初始STEP GPIO口 模式速度 */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/* step_1 初始STEP GPIO口*/
	GPIO_InitStructure.GPIO_Pin = STEP_1_STEP_GPIO_PIN;
	GPIO_Init(STEP_1_STEP_GPIO_PORT, &GPIO_InitStructure);

	 /* step_2 初始STEP GPIO口  */
	GPIO_InitStructure.GPIO_Pin = STEP_2_STEP_GPIO_PIN;
	GPIO_Init(STEP_2_STEP_GPIO_PORT, &GPIO_InitStructure);

	/* step_3 初始STEP GPIO口  */
	GPIO_InitStructure.GPIO_Pin = STEP_3_STEP_GPIO_PIN;
	GPIO_Init(STEP_3_STEP_GPIO_PORT, &GPIO_InitStructure);

	//	/* step_4 初始STEP GPIO口  */
	//	GPIO_InitStructure.GPIO_Pin = STEP_4_STEP_GPIO_PIN;
	//	GPIO_Init(STEP_4_STEP_GPIO_PORT, &GPIO_InitStructure);
  
}


 /*******************************************************************************
 * 函 数 名					: Step_x_TIMx_Init
 * 函数功能					: STEP_x 对应的时钟TIMx初始化等
 * 输    入					: STEP_x_TIM_CLK (TIM时钟), STEP_x_TIMx (定时器x), STEP_x_TIM_CHANNEL (通道1，2，3，4)
 * 输    出					: 无
 *******************************************************************************/
 void Step_x_TIMx_Init(uint32_t STEP_x_TIM_CLK,TIM_TypeDef* STEP_x_TIMx, uint16_t STEP_x_TIM_CHANNEL)
 {
 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	TIM_OCInitTypeDef  TIM_OCInitStructure;

  RCC_APB1PeriphClockCmd(STEP_x_TIM_CLK, ENABLE);    //使能定时器4时钟

  TIM_TimeBaseStructure.TIM_Period = STEP_TIM_ARR(STEP_INIT_F,STEP_INIT_PSC); //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
  TIM_TimeBaseStructure.TIM_Prescaler = STEP_INIT_PSC; //设置用来作为TIMx时钟频率除数的预分频值 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
  TIM_TimeBaseInit(STEP_x_TIMx, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	

   //初始化TIMx Channel_x PWM模式     
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
   //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //关闭比较输出使能
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
  //TIM_OCInitStructure.TIM_Pulse =(STEP_TIM_ARR(STEP_INIT_F,STEP_INIT_PSC) + 1)*STEP_DUTY_CYCLE/100;

  
  if (STEP_x_TIM_CHANNEL == TIM_Channel_1)  
  {	
  	TIM_OC1Init(STEP_x_TIMx, &TIM_OCInitStructure);	//根据T指定的参数初始化外设TIMx OC1;
   		// 这里设置了TIM_Pulse值，设置待装入捕获比较寄存器的脉冲值
 		TIM_OC1PreloadConfig(STEP_x_TIMx, TIM_OCPreload_Enable); //使能TIMx在CCR2上的预装载寄存器
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

  TIM_CCxCmd(STEP_x_TIMx,STEP_x_TIM_CHANNEL,TIM_CCx_Disable);//关闭TIMx通道1
  
  TIM_Cmd(STEP_x_TIMx, DISABLE);  //先不使能TIMx 
}


/*******************************************************************************
* 函 数 名					: Step_x_TIMER_Init
* 函数功能					: 计时定时器初始化
* 输    入					:	可输入（TIM 2~7）初始化 ，定时器用来计时，溢出产生中断关闭PWM(TIM234)
* 输    出					: 无
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
* 函 数 名					: Steps_TIMs_Init
* 函数功能					: 多个通用定时器初始化
* 输    入					:	无
* 输    出					: 无
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


void Steps_Init(void)
{
	stepper_1_t.step_speed = 100;
	stepper_2_t.step_speed = 100;
	stepper_3_t.step_speed = 100;
	stepper_1_t.step_dir = 1;
	stepper_2_t.step_dir = 1;
	stepper_3_t.step_dir = 1;
}

/*******************************************************************************
* 函 数 名					: Steps_Config
* 函数功能					: 步进电机初始化（端口，时钟等等）
* 输    入					:	无
* 输    出					: 无
*******************************************************************************/
void Steps_Config(void)
{
	GPIO_DIR_Init();
	GPIO_STPE_Init();
	Steps_TIMs_Init();
	Steps_Init();
}

/*******************************************************************************
* 函 数 名					: TIM5_IRQHandler
* 函数功能					: 步进电机初始化（端口，时钟等等）
* 输    入					:	无
* 输    出					: 无
*******************************************************************************/
void TIM5_IRQHandler(void)
{
	if ((TIM5->SR & 0x0001) != 0)                 // 检查中断标志
	{
		TIM5->SR &= ~(1<<0);                        // 中断标志复位
		TIM5->CNT = 0;															//计数复位
		NVIC_DisableIRQ(TIM5_IRQn);
    // 关闭PWM输出
    Step_x_stop(STEP_1_TIMx, STEP_1_TIM_CHANNEL);
		step_busy_1 = false;
	}
}

void TIM6_IRQHandler(void)
{
	if ((TIM6->SR & 0x0001) != 0)                 // 检查中断标志
	{
		TIM6->SR &= ~(1<<0);                        // 中断标志复位
		TIM6->CNT = 0;															//计数复位
		NVIC_DisableIRQ(TIM6_IRQn);
    // 关闭PWM输出
    Step_x_stop(STEP_1_TIMx, STEP_1_TIM_CHANNEL);
		step_busy_2 = false;
	}
}

void TIM7_IRQHandler(void)
{
	if ((TIM7->SR & 0x0001) != 0)                 // 检查中断标志
	{
		TIM7->SR &= ~(1<<0);                        // 中断标志复位
		TIM7->CNT = 0;															//计数复位
		NVIC_DisableIRQ(TIM7_IRQn);
    // 关闭PWM输出
    Step_x_stop(STEP_1_TIMx, STEP_1_TIM_CHANNEL);
    step_busy_3 = false;
	}
}



 /*******************************************************************************
 * 函 数 名					: Step_go
 * 函数功能					: 步进电机前进
 * 输    入					:	无
 * 输    出					: 无
 *******************************************************************************/
void Step_go(void)
{
	if (step_busy_1) { return;}
	step_busy_1 = true;
	if (stepper_1_t.step_dir == FORWARD) { STEP_1_FORWARD; }
	else { STEP_1_BACK; }
	Step_PWM_SET(stepper_1_t.step_speed, STEP_1_TIMx, STEP_1_TIM_CHANNEL);
	CalculateSet_Delay_TIME(stepper_1_t.step_speed, stepper_1_t.n_step, TIM5 );
	
  TIM5->EGR = TIM_PSCReloadMode_Immediate;
	Step_PWM_OUT( STEP_1_TIMx, STEP_1_TIM_CHANNEL);
  TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
  stepper_1_t.use_status = true;
}

/*******************************************************************************
* 函 数 名					: Step_PWM_SET
* 函数功能					: 步进PWM输出参数设置
* 输    入					: 无
* 输    出					: 无
*******************************************************************************/
void Step_PWM_SET(int f, TIM_TypeDef* STEP_x_TIMx, uint16_t STEP_x_TIM_CHANNEL)
{
	int arr;
	arr =	STEP_TIM_ARR(f,STEP_INIT_PSC);
	TIM_SetAutoreload(STEP_x_TIMx, arr);
	if 			( STEP_x_TIM_CHANNEL == TIM_Channel_1 )	{TIM_SetCompare1(STEP_x_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));}
	else if ( STEP_x_TIM_CHANNEL == TIM_Channel_2 )	{TIM_SetCompare2(STEP_x_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));}
	else if ( STEP_x_TIM_CHANNEL == TIM_Channel_3 )	{TIM_SetCompare3(STEP_x_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));}	
	else if ( STEP_x_TIM_CHANNEL == TIM_Channel_4 )	{TIM_SetCompare4(STEP_x_TIMx, STEP_TIM_CCR(STEP_DUTY_CYCLE,arr));}

}

/*******************************************************************************
* 函 数 名					: Step_PWM_OUT
* 函数功能					: 步进PWM端口输出PWM
* 输    入					: 无
* 输    出					: 无
*******************************************************************************/
void Step_PWM_OUT( TIM_TypeDef* STEP_x_TIMx, uint16_t STEP_x_TIM_CHANNEL)
{
	TIM_CCxCmd(STEP_x_TIMx,STEP_x_TIM_CHANNEL,TIM_CCx_Enable);//开启TIMx通道
	TIM_Cmd(STEP_x_TIMx, ENABLE);//必须放在最后使能
}

/*******************************************************************************
* 函 数 名					: CalculateSet_Delay_TIME
* 函数功能					: 计时，溢出关闭PWM， 用来输出指定数量脉冲
* 输    入					: 无
* 输    出					: 无
*******************************************************************************/
void CalculateSet_Delay_TIME(int f, uint16_t n_step, TIM_TypeDef* TIMER_TIMx )
{
	if (n_step > 100) return;
	// 根据频率大小设置定时器预分频,并计算设置定时时间 相关公式ARR = (sys_clk * n_step) / (psc * f)
	if (f > 10000) 
	{	
		TIMER_TIMx->PSC = 71;
		
		TIMER_TIMx->ARR	=(int)((1000000 * n_step)/f);
	}	
	else if (f >1000)	
	{
		TIMER_TIMx->PSC = 719;
		TIMER_TIMx->ARR	=(int)((100000 * n_step)/f);
	}
	else if (f >100)	
	{
		TIMER_TIMx->PSC = 3599;
		TIMER_TIMx->ARR	=(int)((20000 * n_step)/f);
	}
}


 /*******************************************************************************
 * 函 数 名					: Step_x_run
 * 函数功能					: 步进电机x 以固定频率f运动
 * 输    入					:	无
 * 输    出					: 无
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

	TIM_CCxCmd(STEP_x_TIMx,STEP_x_TIM_CHANNEL,TIM_CCx_Enable);//开启TIMx通道

	TIM_Cmd(STEP_x_TIMx, ENABLE);//必须放在最后使能
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
// * 函 数 名					: Step_x_stop
// * 函数功能					: 步进电机x停止
// * 输    入					:	无
// * 输    出					: 无
// *******************************************************************************/
void Step_x_stop(TIM_TypeDef* STEP_x_TIMx, uint16_t STEP_x_TIM_CHANNEL)
{
	TIM_CCxCmd(STEP_x_TIMx,STEP_x_TIM_CHANNEL,TIM_CCx_Enable);//关闭TIMx通道
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
* 函 数 名					: Steps_run
* 函数功能					: 步进电机以同速率运动
* 输    入					:	无
* 输    出					: 无
*******************************************************************************/
void Steps_run(int f)
{	
	Step_1_run(f);
	Step_2_run(f);
	Step_3_run(f);
	// Step_4_run(f);
}


/*******************************************************************************
* 函 数 名					: Steps_stop
* 函数功能					: 步进电机同时停止
* 输    入					:	无
* 输    出					: 无
*******************************************************************************/
void Steps_stop(void)
{
	Step_1_stop();
	Step_2_stop();
	Step_3_stop();
	// Step_4_stop();
}


