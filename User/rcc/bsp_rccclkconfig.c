/* bsp : board support packge �弶֧�ְ� */
#include "bsp_rccclkconfig.h"


void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
	ErrorStatus HSEStatus;
	/* HSE */
	RCC_HSEConfig(RCC_HSE_ON);
	
	HSEStatus = RCC_WaitForHSEStartUp();
	
	if(	HSEStatus == SUCCESS)
	{
		/* ʹ��Ԥȡָ */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config( RCC_HCLK_Div1);
		
		/* ����PLLCLK = HSE * RCC_PLLMl_x */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_x);
		
		/* ʹ��PLL */
		RCC_PLLCmd(ENABLE);
		
		/* �ȴ�PLL�ȶ� */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		/* ѡ��ϵͳʱ�� */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

		while(RCC_GetSYSCLKSource() != 0x08);
		
		
	}
	else
	{
	/* ���HSE����ʧ�ܣ������Լ������� */
	}
	

}


void HSI_SetSysClk(uint32_t RCC_PLLMul_x)
{
	__IO uint32_t HSIStatus = 0;
	
	/* �ѼĴ�����λ�ɸ�λֵ */
	RCC_DeInit();
	
	/* ʹ�� HSI */

	RCC_HSICmd(ENABLE);
	
	HSIStatus = RCC->CR & RCC_CR_HSIRDY;
	
	if(	HSIStatus == SUCCESS)
	{
		/* ʹ��Ԥȡָ */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		FLASH_SetLatency(FLASH_Latency_2);
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config( RCC_HCLK_Div1);
		
		/* ����PLLCLK = HSI * RCC_PLLMl_x */
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_x);
		
		/* ʹ��PLL */
		RCC_PLLCmd(ENABLE);
		
		/* �ȴ�PLL�ȶ� */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		/* ѡ��ϵͳʱ�� */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

		while(RCC_GetSYSCLKSource() != 0x00);
		
		
	}
	else
	{
		/* ���HSI����ʧ�ܣ������Լ������� */
	}
	

}

