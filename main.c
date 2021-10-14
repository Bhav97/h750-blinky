#include <stdint.h>

#include "stm32h750xx.h"
#include "stm32h7xx_hal.h"

#define LED_PORT GPIOE
#define LED_PIN GPIO_PIN_3

void HardFault_Handler(void)
{
	__asm("bkpt #0");
	while(1)
	{
		;
	}
}

void SysTick_Handler(void)
{
	HAL_IncTick();
}

int main(void)
{
	SCB_EnableICache();
	SCB_EnableDCache();
	HAL_Init();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitTypeDef InitStruct = {0};
	InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	InitStruct.Pin = LED_PIN;
	InitStruct.Pull = GPIO_PULLUP;
	InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(LED_PORT, &InitStruct);
	while(1)
	{
		HAL_Delay(100);
		HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
	}
}
