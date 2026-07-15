#include "stm32f407xx.h"



int main(void)
/*
 * */
{
	//define USART GPIO

	GPIO_Handle_t uart4_tx, uart4_rx;
	gpio_configure_pin(&uart4_tx, GPIOA, 0, GPIO_MODE_ALTFN, GPIO_SPEED_MEDIUM, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 0);
	gpio_configure_pin(&uart4_rx, GPIOA, 1, GPIO_MODE_ALTFN, GPIO_SPEED_MEDIUM, GPIO_OUT_MODE_OD, GPIO_PU, 0);
	gpio_init(&uart4_tx);
	gpio_init(&uart4_rx);

//	uart_configure_pin();


    return 0;
}
