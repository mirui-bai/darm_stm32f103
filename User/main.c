#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_systick.h"
#include "bsp_step.h"
#include "bsp_usart.h"

static void Show_Message(void);

void Delay(uint32_t count)
{
	for(;count!=0;count--);
}


#define delay1 Delay(0x0F)

int main(void)
{
	char ch;
	int f;
	// ODR 低电平亮 高电平灭
	// led init
	LED_GPIO_Config();
	
	/* 中断init */
	EXIT_Key_Config();
	
	/* arr=999 ,不分频psc=71  PWM频率=(72000000 / (psc + 1)) / (arr + 1) */
	Steps_Config();
	Steps_run(STEP_INIT_F);

  
  /* 初始化RGB彩灯 */
  LED_GPIO_Config();
  
  /* 初始化USART 配置模式为 115200 8-N-1 */
  USART_Config();
	
  /* 打印指令输入提示信息 */
  Show_Message();
	f = STEP_INIT_F;
  while(1)
	{	
    /* 获取字符指令 */
    ch=getchar();
    printf("接收到字符：%c\n",ch);

    
    /* 根据字符指令控制RGB彩灯颜色 */

    switch(ch)
    {
      case 'r':
        Steps_run(f);
      break;
      case 's':
        Steps_stop();
			break;
      case '1':
        Steps_stop();
			break;
      case '0':
        Steps_stop();
			break;
			
			case '+':
				f += 10;
        Steps_run(f);
      break;
	    case '-':
				f -= 10;
				Steps_run(f);
			break;
      default:
        /* 如果不是指定指令字符，打印提示信息 */
        Show_Message();
        break;      
    }
		printf("当前频率：%d\n",f);
	}	
}


/**
  * @brief  打印指令输入提示信息
  * @param  无
  * @retval 无
  */
static void Show_Message(void)
{
  printf("\r\n   这是一个通过串口通信指令控制42步进电机实验 \n");
  printf("使用  USART  参数为：%d “r”“s” \n",DEBUG_USART_BAUDRATE);
  printf("开发板接到指令后控制步进电机状态，指令对应如下：\n");
  printf("   指令   ------ 动停正反加减速 \n");
  printf("     r    ------    动 \n");
  printf("     s    ------    停 \n");
	printf("     1    ------    正 \n");
  printf("     0    ------    反 \n");
	printf("     +    ------    加速 \n");
  printf("     -    ------    减速 \n");
}


