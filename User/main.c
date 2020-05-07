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
	// ODR �͵�ƽ�� �ߵ�ƽ��
	// led init
	LED_GPIO_Config();
	
	/* �ж�init */
	EXIT_Key_Config();
	
	/* arr=999 ,����Ƶpsc=71  PWMƵ��=(72000000 / (psc + 1)) / (arr + 1) */
	Steps_Config();
	Steps_run(STEP_INIT_F);

  
  /* ��ʼ��RGB�ʵ� */
  LED_GPIO_Config();
  
  /* ��ʼ��USART ����ģʽΪ 115200 8-N-1 */
  USART_Config();
	
  /* ��ӡָ��������ʾ��Ϣ */
  Show_Message();
	f = STEP_INIT_F;
  while(1)
	{	
    /* ��ȡ�ַ�ָ�� */
    ch=getchar();
    printf("���յ��ַ���%c\n",ch);

    
    /* �����ַ�ָ�����RGB�ʵ���ɫ */

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
        /* �������ָ��ָ���ַ�����ӡ��ʾ��Ϣ */
        Show_Message();
        break;      
    }
		printf("��ǰƵ�ʣ�%d\n",f);
	}	
}


/**
  * @brief  ��ӡָ��������ʾ��Ϣ
  * @param  ��
  * @retval ��
  */
static void Show_Message(void)
{
  printf("\r\n   ����һ��ͨ������ͨ��ָ�����42�������ʵ�� \n");
  printf("ʹ��  USART  ����Ϊ��%d ��r����s�� \n",DEBUG_USART_BAUDRATE);
  printf("������ӵ�ָ�����Ʋ������״̬��ָ���Ӧ���£�\n");
  printf("   ָ��   ------ ��ͣ�����Ӽ��� \n");
  printf("     r    ------    �� \n");
  printf("     s    ------    ͣ \n");
	printf("     1    ------    �� \n");
  printf("     0    ------    �� \n");
	printf("     +    ------    ���� \n");
  printf("     -    ------    ���� \n");
}


