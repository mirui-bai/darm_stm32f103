#include "bsp_systick.h"


void SysTick_Delay_us( __IO uint32_t us)
{	
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000000);
	for(i=0; i<us; i++)
	{
		
		/* 	当计数器的值减小到 0 的时候
				CRTL 寄存器的位 16 会置 1
				当置 1 时，读取该位会清 0 */
			while(!((SysTick->CALIB) & (1<<16)));
	}
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}



void SysTick_Delay_ms(__IO uint32_t ms)
{	
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000);
	for(i=0; i<ms; i++)
	{
		
		/* 	当计数器的值减小到 0 的时候
				CRTL 寄存器的位 16 会置 1
				当置 1 时，读取该位会清 0 */
			while(!((SysTick->CTRL) & (1<<16)));
	}
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}

