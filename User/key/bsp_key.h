#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f10x.h"



/* 定义KEY连结的GPIO端口， 用户只需修改下面的代码即可改变控制KEY引脚 */
//KEY1
#define KEY_1_GPIO_PORT		GPIOA						/* GPIO端口 */
#define KEY_1_GPIO_CLK		RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define KEY_1_GPIO_PIN		GPIO_Pin_0					/* 连结到SCL时钟线的GPIO */

//KEY2
#define KEY_2_GPIO_PORT		GPIOC						/* GPIO端口 */
#define KEY_2_GPIO_CLK		RCC_APB2Periph_GPIOC		/* GPIO端口时钟 */
#define KEY_2_GPIO_PIN		GPIO_Pin_13					/* 连结到SCL时钟线的GPIO */



/* 定义KEY 按下 为高点平 松开为低电平 */
#define KEY_ON 1
#define KEY_OFF 0




void KEY_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);


#endif /*__BSP_KEY_H*/
