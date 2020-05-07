/* bsp : board support packge 板级支持包 */
#include "bsp_rccclkconfig.h"


void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
	ErrorStatus HSEStatus;
	/* HSE */
	RCC_HSEConfig(RCC_HSE_ON);
	
	HSEStatus = RCC_WaitForHSEStartUp();
	
	if(	HSEStatus == SUCCESS)
	{
		/* 使能预取指 */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config( RCC_HCLK_Div1);
		
		/* 配置PLLCLK = HSE * RCC_PLLMl_x */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_x);
		
		/* 使能PLL */
		RCC_PLLCmd(ENABLE);
		
		/* 等待PLL稳定 */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		/* 选择系统时钟 */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

		while(RCC_GetSYSCLKSource() != 0x08);
		
		
	}
	else
	{
	/* 如果HSE启动失败，可以自己添加添加 */
	}
	

}


void HSI_SetSysClk(uint32_t RCC_PLLMul_x)
{
	__IO uint32_t HSIStatus = 0;
	
	/* 把寄存器复位成复位值 */
	RCC_DeInit();
	
	/* 使能 HSI */

	RCC_HSICmd(ENABLE);
	
	HSIStatus = RCC->CR & RCC_CR_HSIRDY;
	
	if(	HSIStatus == SUCCESS)
	{
		/* 使能预取指 */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config( RCC_HCLK_Div1);
		
		/* 配置PLLCLK = HSI * RCC_PLLMl_x */
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_x);
		
		/* 使能PLL */
		RCC_PLLCmd(ENABLE);
		
		/* 等待PLL稳定 */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		/* 选择系统时钟 */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

		while(RCC_GetSYSCLKSource() != 0x00);
		
		
	}
	else
	{
		/* 如果HSI启动失败，可以自己添加添加 */
	}
	

}

