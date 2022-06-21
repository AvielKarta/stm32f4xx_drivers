/*
 * stm32f4xx_spi_drivers.c
 *
 *  Created on: 14 ביוני 2022
 *      Author: avielk
 */

#include "stm32f407xx.h"


/******************************************************
				1.GPIO CLK control
*******************************************************/

void spi_clk_control(SPI_Handle_t* spi_handle,uint8_t enable)
{

	if (enable)
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

/******************************************************
				2.SPI
*******************************************************/

void spi_init(SPI_Handle_t* spi_handle)
{
	uint32_t temp = 0;

	temp |= (spi_handle->spi_pin_config.CPHA)<<CR1_BIT0_CPHA;
	temp |= (spi_handle->spi_pin_config.CPOL)<<CR1_BIT1_CPOL;
	temp |= (spi_handle->spi_pin_config.MSTR)<<CR1_BIT2_MSTR;
	temp |= (spi_handle->spi_pin_config.BR)<<CR1_BIT3_BR0;
	temp |= ENABLE<<CR1_BIT6_LSB;
	temp |= (spi_handle->spi_pin_config.DFF)<<CR1_BIT7_DFF;
	temp |= (spi_handle->spi_pin_config.SSM)<<CR1_BIT9_SSM;

	if (spi_handle->spi_pin_config.BUS == SPI_HALF_DUPLEX)
	{
		/*Half duplex - BIDIMODE bit should be enabled*/
		temp |= SPI_BIDI_MODE<<CR1_BIT15_BIDIMODE;
	}
	else
	{
		/*Full duplex - BIDIMODE bit should be reset*/
		temp |= SPI_UNIDI_MODE<<CR1_BIT15_BIDIMODE;
		if (spi_handle->spi_pin_config.BUS == SPI_SIMPLEX_RX_ONLY)
		{
			/*Simplex RX only - RXONLY bit should be enabled*/
			temp |= ENABLE<<CR1_BIT10_RXONLY;
		}
	}
	spi_handle->p_spi_x->SPI_CR1 = temp;
}

/******************************************************
				3.3.SPI send/receive functions
*******************************************************/

void spi_send(SPI_RegDef_t* p_spi_x,uint8_t *pTxbuffer, uint32_t len)
{
	while(len > 0)
	{
		if (((p_spi_x->SPI_SR)&(1<<SR_BIT1_TXE)) != 0)
		/*If TX buffer is empty*/
		{
			if (((p_spi_x->SPI_CR1)&(1<<CR1_BIT7_DFF)) == SPI_DFF_8_BIT)
			/*If Frame format is 8 bit*/
			{
				p_spi_x->SPI_DR |= *pTxbuffer;
				pTxbuffer++;
				len--;
			}
			else
			/*If Frame format is 16 bit*/
			{
				p_spi_x->SPI_DR =  *((uint16_t*)pTxbuffer);
				len = len-2;
				(uint16_t*)pTxbuffer++;
				/*
				p_spi_x->SPI_DR |= *pTxbuffer;
				pTxbuffer++;
				uint16_t temp = *pTxbuffer;
				p_spi_x->SPI_DR |= (temp<<8);
				pTxbuffer++;
				*/
			}
		}
	}
}
void spi_recieve()
{

}






