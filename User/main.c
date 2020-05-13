#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_systick.h"
#include "bsp_step.h"
#include "bsp_usart.h"

//extern uint8_t step_busy_1;
//extern uint8_t step_busy_2;
//extern uint8_t step_busy_3;
uint8_t step_busy_1;
uint8_t step_busy_2;
uint8_t step_busy_3;

// static void Show_Message(void);

void Delay(uint32_t count)
{
	for(;count!=0;count--);
}


#define delay1 Delay(0xFF)

int main(void)
{
//	char ch;
//	int f;
	int speed_upgrade;
	// ODR 低电平亮 高电平灭
	// led init
	LED_GPIO_Config();
	
	/* 中断init */
	EXIT_Key_Config();
	
	/* arr=999 ,不分频psc=71  PWM频率=(72000000 / (psc + 1)) / (arr + 1) */
	Steps_Config();
//	Steps_run(STEP_INIT_F,STEP_INIT_F,STEP_INIT_F,STEP_INIT_F);

  
  /* 初始化RGB彩灯 */
  LED_GPIO_Config();
  
  /* 初始化USART 配置模式为 115200 8-N-1 */
  // USART_Config();
	
  /* 打印指令输入提示信息 */
  // Show_Message();
	
	speed_upgrade = 1;

	// printf("%d", STEP_TIM_ARR(STEP_INIT_F,STEP_INIT_PSC));
	// f = STEP_INIT_F;
  // Steps_run(f);

  while(1)
	{
    /* 获取字符指令 */
    // ch=getchar();
    // printf("接收到字符：%c\n",ch);

  
    if (step_busy_1 == false)	
    {

    	if (stepper_1_t.step_speed < 100)	
    	{
    		stepper_1_t.step_speed = 100;}
    	if (stepper_1_t.step_speed < 1000) 	{stepper_1_t.n_step = 1;}
    	else if (stepper_1_t.step_speed < 10000)		{stepper_1_t.n_step = 2;}
    	else if (stepper_1_t.step_speed < 20000)		{stepper_1_t.n_step = 4;}
    	stepper_1_t.step_speed += speed_upgrade;
    	if (stepper_1_t.step_dir) {stepper_1_t.step_counts += stepper_1_t.n_step;}
    	else {stepper_1_t.step_counts -= stepper_1_t.n_step;}
    	Step_go();
    	if (stepper_1_t.step_counts > 6000 )	{speed_upgrade = - speed_upgrade;}
    	if ((stepper_1_t.step_speed < 500) & (stepper_1_t.step_counts == 0)) 
    	{
    		stepper_1_t.step_dir = BACK;
    		speed_upgrade = - speed_upgrade;
    	}
    }

//    switch(ch)
//    {
//      case 'r':
//        Steps_run(f);
//      break;
//      case 's':
//        Steps_stop();
//			break;
//      case '1':
//        Steps_stop();
//			break;
//      case '0':
//        Steps_stop();
//			break;
//			
//			case '+':
//				f += 10;
//        Steps_run(f);
//      break;
//	    case '-':
//				f -= 10;
//				Steps_run(f);
//			break;
//      default:
//        /* 如果不是指定指令字符，打印提示信息 */
//        Show_Message();
//        break;      
//    }
//		//printf("当前频率：%d\n",f);
		}	
}


/**
  * @brief  打印指令输入提示信息
  * @param  无
  * @retval 无
  */
//static void Show_Message(void)
//{
//  printf("\r\n   这是一个通过串口通信指令控制42步进电机实验 \n");
//  printf("使用  USART  参数为：%d “r”“s” \n",DEBUG_USART_BAUDRATE);
//  printf("开发板接到指令后控制步进电机状态，指令对应如下：\n");
//  printf("   指令   ------ 动停正反加减速 \n");
//  printf("     r    ------    动 \n");
//  printf("     s    ------    停 \n");
//	printf("     1    ------    正 \n");
//  printf("     0    ------    反 \n");
//	printf("     +    ------    加速 \n");
//  printf("     -    ------    减速 \n");
//}


