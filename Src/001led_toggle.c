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

	int i = 0;
	GPIO_Handle_t green_led;
	GPIO_Handle_t orange_led;
	GPIO_Handle_t red_led;
	GPIO_Handle_t blue_led;

	define_led(&green_led, GPIOD, 12, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	define_led(&orange_led, GPIOD, 13, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	define_led(&red_led, GPIOD, 14, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	define_led(&blue_led, GPIOD, 15, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);



	GPIO_CLKCtrl(GPIOD,ENABLE);

	GPIO_Init(&green_led);
	GPIO_Init(&orange_led);
	GPIO_Init(&red_led);
	GPIO_Init(&blue_led);

	while(1)
	{
		GPIO_TogglePin(GPIOD, 12+(++i)%4);
		delay();

	}
	return 0;
}
