/*
 * 		main.c
 *      Author:  Aviel karta
 */

#include "stm32f407xx.h"
#include <string.h>

static int timeout = 2.5*M;

void delay(int timeout)
{
	for(uint32_t i = 0 ; i < timeout ; i ++);
}

void gpio_driver_function(void)
{
	GPIO_Handle_t green_led, orange_led, red_led, blue_led, irq_pin;

	gpio_configure_pin(&green_led, GPIOD, 12, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 0);
	gpio_configure_pin(&orange_led, GPIOD, 13, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 0);
	gpio_configure_pin(&red_led, GPIOD, 14, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 0);
	gpio_configure_pin(&blue_led, GPIOD, 15, GPIO_MODE_OUT, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 0);
	gpio_configure_pin(&irq_pin, GPIOA, 0, GPIO_MODE_IRQ_RT, GPIO_SPPED_FAST, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 0);		/*Configures GPIOA_0 pin the work in interrupt mode*/

	gpio_init(&green_led);
	gpio_init(&orange_led);
	gpio_init(&red_led);
	gpio_init(&blue_led);
	gpio_init(&irq_pin);

	/*Enable and configure interrupt line 0*/
	gpio_irq_set(EXTI0);
	gpio_irq_priority(EXTI0, 15);


}
void spi_driver_function(void)
{


	GPIO_Handle_t spi_pins;
	gpio_configure_pin(&spi_pins, GPIOB, 12, GPIO_MODE_ALTFN, GPIO_SPPED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 5);/*Enables NSS*/
	spi_pins.GPIO_PinCfng.PinNumber = 13; /*Enables SCLK*/
	gpio_init(&spi_pins);
	spi_pins.GPIO_PinCfng.PinNumber = 14;/*Enables MISO*/
	gpio_init(&spi_pins);
	spi_pins.GPIO_PinCfng.PinNumber = 15;/*Enables MOSI*/
	gpio_init(&spi_pins);


	SPI_Handle_t spi2_handler;
	spi_configure_pin(&spi2_handler, SPI2, SPI_CLK_PHASE_0, SPI_CLK_IDLE_0, SPI_MASTER, SPI_BR_CLK_DIV_256, SPI_SSM_EN, SPI_DFF_16_BIT, SPI_FULL_DUPLEX);/*Configures parameters for SPI2*/
	spi_init(&spi2_handler);
	spi_ssi_enable(SPI2, ENABLE);
	spi_enable(SPI2, ENABLE);
}

int main(void)
{

	//TX STM code
	char spi_tx_data[] = "blue";
	gpio_driver_function();
	spi_driver_function();


	while(1)
	{
		delay(timeout);
		spi_send(SPI2, (uint8_t*)spi_tx_data, strlen(spi_tx_data));
	}


	//RX STM code
	char spi_rx_data[strlen(spi_tx_data)];
	gpio_driver_function();
	spi_driver_function();


	while(1)
	{
		delay(timeout);
		spi_recieve(SPI2, (uint8_t*)spi_rx_data, strlen(spi_tx_data));
		if (!strcmp(spi_rx_data, "blue"))
		{
		gpio_write_to_pin(GPIOD, 15, ENABLE);
		}

	}


	return 0;
}

void EXTI0_IRQHandler(void)
	{
	if (timeout == 2.5*M)
		timeout = 100*K;
	else
		timeout = 2.5*M;
	gpio_irq_handler(0);
	}

