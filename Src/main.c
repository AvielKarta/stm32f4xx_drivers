/*
 * 001led_toggle.c
 *
 *  Created on: Jan 4, 2020
 *      Author: admin
 */

#include "stm32f407xx.h"


void delay(void)
{
	for(uint32_t i = 0 ; i < 500000 ; i ++);
}


int main(void)
{

	int cnt = 0;
	GPIO_Handle_t green_led;
	GPIO_Handle_t orange_led;
	GPIO_Handle_t red_led;
	GPIO_Handle_t blue_led;
	GPIO_Handle_t button;

	configure_gpio_pin(&green_led, GPIOD, 12, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	configure_gpio_pin(&orange_led, GPIOD, 13, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	configure_gpio_pin(&red_led, GPIOD, 14, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	configure_gpio_pin(&blue_led, GPIOD, 15, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	configure_gpio_pin(&button, GPIOA, 0, GPIO_MODE_IN, GPIO_SPPED_FAST, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);


	/*Enable the LED in open drain configuration (low current, low LED intensity)*/
//	configure_gpio_pin(&green_led, GPIOD, 12, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_OD, GPIO_PU);
//	configure_gpio_pin(&orange_led, GPIOD, 13, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_OD, GPIO_PU);
//  configure_gpio_pin(&red_led, GPIOD, 14, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_OD, GPIO_PU);
//	configure_gpio_pin(&blue_led, GPIOD, 15, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_OD, GPIO_PU);

	GPIO_CLKCtrl(GPIOD,ENABLE);
	GPIO_CLKCtrl(GPIOA,ENABLE);

	GPIO_Init(&green_led);
	GPIO_Init(&orange_led);
	GPIO_Init(&red_led);
	GPIO_Init(&blue_led);
	GPIO_Init(&button);

	
	while(1)
	{
		if (GPIO_ReadPin(GPIOA, 0) == ENABLE)
		{
			delay();
			GPIO_TogglePin(GPIOD, 12+(++cnt)%4);
		}
	}
	return 0;
}
