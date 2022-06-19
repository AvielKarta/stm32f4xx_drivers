/*
 * 		main.c
 *      Author:  Aviel karta
 */

#include "stm32f407xx.h"


void delay(int timeout)
{
	for(uint32_t i = 0 ; i < timeout ; i ++);
}


static int timeout = 2500000;

int main(void)
{
	int cnt = 0;

	GPIO_Handle_t green_led;
	GPIO_Handle_t orange_led;
	GPIO_Handle_t red_led;
	GPIO_Handle_t blue_led;
	//GPIO_Handle_t button;
	GPIO_Handle_t irq_pin;

	gpio_configure_pin(&green_led, GPIOD, 12, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	gpio_configure_pin(&orange_led, GPIOD, 13, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	gpio_configure_pin(&red_led, GPIOD, 14, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	gpio_configure_pin(&blue_led, GPIOD, 15, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);

	/*Configure the LED's to run in open drain with pull up resistor (40K), this will cause LED to work in low luminosity mode*/

	 /*
	configure_gpio_pin(&green_led, GPIOD, 12, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_OD, GPIO_PU);
	configure_gpio_pin(&orange_led, GPIOD, 13, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_OD, GPIO_PU);
	configure_gpio_pin(&red_led, GPIOD, 14, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_OD, GPIO_PU);
	configure_gpio_pin(&blue_led, GPIOD, 15, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_OD, GPIO_PU);
	*/

	//gpio_configure_pin(&button, GPIOA, 0, GPIO_MODE_IN, GPIO_SPPED_FAST, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);

	/*Configures GPIOA_0 pin the work in interrupt mode*/
	gpio_configure_pin(&irq_pin, GPIOA, 0, GPIO_MODE_IRQ_RT, GPIO_SPPED_FAST, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	//gpio_configure_pin(&irq_pin, GPIOD, 5, GPIO_MODE_IRQ_FT, GPIO_SPPED_FAST, GPIO_OUT_MODE_PP, GPIO_PU);

	/*Enables the GPIO CLK*/
	GPIO_CLKCtrl(GPIOD,ENABLE);
	GPIO_CLKCtrl(GPIOA,ENABLE);


	gpio_init(&green_led);
	gpio_init(&orange_led);
	gpio_init(&red_led);
	gpio_init(&blue_led);
	gpio_init(&irq_pin);
	//gpio_init(&button);

	gpio_irq_set(EXTI0);
	gpio_irq_priority(EXTI0, 15);
	gpio_write_to_pin(GPIOD, 15, ENABLE);

	while(1)
	{
		delay(timeout);
		gpio_toggle_pin(GPIOD, 12+(cnt++)%4);

	}

	return 0;
}

void EXTI0_IRQHandler(void)
	{
		if (timeout < 200000)
		{
			timeout = 1000000;
		}
		else
		{
			timeout-=100000;
		}
		gpio_irq_handler(0);
	}

