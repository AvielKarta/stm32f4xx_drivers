/*
 * stm32f4xx_spi_drivers.c
 *
 *  Created on: 14 ביוני 2022
 *      Author: avielk
 */

#include "stm32f407xx.h"

void spi_clk_control(SPI_Handle_t* spi_handle,uint8_t EnOrDi)
{
	if (EnOrDi == ENABLE)
	{
		if (spi_handle->p_spi_x == SPI1)
		{
			SPI1_CLK_EN();
		}
		else if (spi_handle->p_spi_x == SPI2)
		{
			SPI2_CLK_EN();
		}
		else if (spi_handle->p_spi_x == SPI3)
		{
			SPI3_CLK_EN();
		}
		else if (spi_handle->p_spi_x == SPI4)
		{
			SPI4_CLK_EN();
		}

	}
	else
	{
		if (spi_handle->p_spi_x == SPI1)
			{
				SPI1_CLK_DI();
			}
			else if (spi_handle->p_spi_x == SPI2)
			{
				SPI2_CLK_DI();
			}
			else if (spi_handle->p_spi_x == SPI3)
			{
				SPI3_CLK_DI();
			}
			else if (spi_handle->p_spi_x == SPI4)
			{
				SPI4_CLK_DI();
			}
	}


}

void spi_init(SPI_Handle_t* spi_handle)
{
	uint32_t temp = 0;
	temp |= (spi_handle->spi_pin_config.CPHA);
	temp |= (spi_handle->spi_pin_config.CPOL)<<1;
	temp |= (spi_handle->spi_pin_config.MSTR)<<2;
	temp |= (spi_handle->spi_pin_config.BR)<<3;
	temp |= ENABLE<<6;
	temp |= (spi_handle->spi_pin_config.DFF)<<7;
	temp |= (spi_handle->spi_pin_config.SSM)<<9;

	spi_handle->p_spi_x->SPI_CR1 |= temp;

}


void spi_send()
{

}
void spi_recieve()
{

}






