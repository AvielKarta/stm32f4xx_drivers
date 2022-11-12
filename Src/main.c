/*
 * 		main.c
 *      Author:  Aviel karta
 */

#include "stm32f407xx.h"
#include <string.h>


void delay1(int timeout)
{
	for(uint32_t i = 0 ; i < timeout ; i ++);
}

void gpio_driver_function1(GPIO_Handle_t green_led)
{

	gpio_configure_pin(&green_led, GPIOD, 12, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 0);
	gpio_init(&green_led);

}

int main(void)
{
	GPIO_Handle_t green_led;
	gpio_driver_function1(green_led);
	while(1)
	{
		gpio_toggle_pin(GPIOD, 12);
		delay1(700000);
	}



return 0;
}



