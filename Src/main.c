/*
 * 		main.c
 *      Author:  Aviel karta
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

	GPIO_Handle_t irq_pin;

	gpio_configure_pin(&green_led, GPIOD, 12, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	gpio_configure_pin(&orange_led, GPIOD, 13, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	gpio_configure_pin(&red_led, GPIOD, 14, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	gpio_configure_pin(&blue_led, GPIOD, 15, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);
	gpio_configure_pin(&button, GPIOA, 0, GPIO_MODE_IN, GPIO_SPPED_FAST, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);

	gpio_configure_pin(&irq_pin, GPIOA, 12, GPIO_MODE_IRQ_FT, GPIO_SPPED_FAST, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD);


	/*Enable the LED in open drain configuration (low current, low LED intensity)*/
//	configure_gpio_pin(&green_led, GPIOD, 12, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_OD, GPIO_PU);
//	configure_gpio_pin(&orange_led, GPIOD, 13, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_OD, GPIO_PU);
//	configure_gpio_pin(&red_led, GPIOD, 14, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_OD, GPIO_PU);
//	configure_gpio_pin(&blue_led, GPIOD, 15, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_OD, GPIO_PU);

	GPIO_CLKCtrl(GPIOD,ENABLE);
	GPIO_CLKCtrl(GPIOA,ENABLE);

	gpio_init(&green_led);
	gpio_init(&orange_led);
	gpio_init(&red_led);
	gpio_init(&blue_led);
	gpio_init(&button);
	gpio_init(&irq_pin);

	void EXTI0_IRQHandler(void)
	{
		gpio_irq_handler(0);
	}
	
	while(1)
	{
		if (gpio_read_pin(GPIOA, 0) == ENABLE)
		{
			delay();
			gpio_toggle_pin(GPIOD, 12+(++cnt)%4);
		}
	}
	return 0;
}
