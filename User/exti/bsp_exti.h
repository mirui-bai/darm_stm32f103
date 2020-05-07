#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

#include "stm32f10x.h"


///* 定义KEY连结的GPIO端口， 用户只需修改下面的代码即可改变控制KEY引脚 */
////KEY1
//#define KEY_1_GPIO_PORT		GPIOA						/* GPIO端口 */
//#define KEY_1_GPIO_CLK		RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
//#define KEY_1_GPIO_PIN		GPIO_Pin_0					/* 连结到SCL时钟线的GPIO */


////KEY2
//#define KEY_2_GPIO_PORT		GPIOC						/* GPIO端口 */
//#define KEY_2_GPIO_CLK		RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
//#define KEY_2_GPIO_PIN		GPIO_Pin_13					/* 连结到SCL时钟线的GPIO */


#define KEY1_INT_GPIO_PORT         GPIOA
#define KEY1_INT_GPIO_CLK          (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define KEY1_INT_GPIO_PIN          GPIO_Pin_0
#define KEY1_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOA
#define KEY1_INT_EXTI_PINSOURCE    GPIO_PinSource0
#define KEY1_INT_EXTI_LINE         EXTI_Line0
#define KEY1_INT_EXTI_IRQ          EXTI0_IRQn

#define KEY1_IRQHandler            EXTI0_IRQHandler


#define KEY2_INT_GPIO_PORT         GPIOC
#define KEY2_INT_GPIO_CLK          (RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO)
#define KEY2_INT_GPIO_PIN          GPIO_Pin_13
#define KEY2_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOC
#define KEY2_INT_EXTI_PINSOURCE    GPIO_PinSource13
#define KEY2_INT_EXTI_LINE         EXTI_Line13
#define KEY2_INT_EXTI_IRQ          EXTI15_10_IRQn

#define KEY2_IRQHandler            EXTI15_10_IRQHandler


static void NVIC_Config(void);
void EXIT_Key_Config(void);

#endif /* __BSP_EXTI_H */



