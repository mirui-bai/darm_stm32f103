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
	// ODR �͵�ƽ�� �ߵ�ƽ��
	// led init
	LED_GPIO_Config();
	
	/* �ж�init */
	EXIT_Key_Config();
	
	/* arr=999 ,����Ƶpsc=71  PWMƵ��=(72000000 / (psc + 1)) / (arr + 1) */
	Steps_Config();
//	Steps_run(STEP_INIT_F,STEP_INIT_F,STEP_INIT_F,STEP_INIT_F);

  
  /* ��ʼ��RGB�ʵ� */
  LED_GPIO_Config();
  
  /* ��ʼ��USART ����ģʽΪ 115200 8-N-1 */
  // USART_Config();
	
  /* ��ӡָ��������ʾ��Ϣ */
  // Show_Message();
	
	speed_upgrade = 1;

	// printf("%d", STEP_TIM_ARR(STEP_INIT_F,STEP_INIT_PSC));
	// f = STEP_INIT_F;
  // Steps_run(f);

  while(1)
	{
    /* ��ȡ�ַ�ָ�� */
    // ch=getchar();
    // printf("���յ��ַ���%c\n",ch);

  
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
//        /* �������ָ��ָ���ַ�����ӡ��ʾ��Ϣ */
//        Show_Message();
//        break;      
//    }
//		//printf("��ǰƵ�ʣ�%d\n",f);
		}	
}


/**
  * @brief  ��ӡָ��������ʾ��Ϣ
  * @param  ��
  * @retval ��
  */
//static void Show_Message(void)
//{
//  printf("\r\n   ����һ��ͨ������ͨ��ָ�����42�������ʵ�� \n");
//  printf("ʹ��  USART  ����Ϊ��%d ��r����s�� \n",DEBUG_USART_BAUDRATE);
//  printf("������ӵ�ָ�����Ʋ������״̬��ָ���Ӧ���£�\n");
//  printf("   ָ��   ------ ��ͣ�����Ӽ��� \n");
//  printf("     r    ------    �� \n");
//  printf("     s    ------    ͣ \n");
//	printf("     1    ------    �� \n");
//  printf("     0    ------    �� \n");
//	printf("     +    ------    ���� \n");
//  printf("     -    ------    ���� \n");
//}


