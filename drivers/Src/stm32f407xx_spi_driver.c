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
void spi_configure_pin(SPI_Handle_t* spi, SPI_RegDef_t* spi_x, int cpha, int cpol, int master, int baudrate, int ssm, int ssi, int dff, int bus_cfg)
{

	spi->p_spi_x = spi_x;
	spi->spi_config.CPHA = cpha;
	spi->spi_config.CPOL = cpol;
	spi->spi_config.MSTR = master;
	spi->spi_config.BR = baudrate;
	spi->spi_config.SSM = ssm;
	spi->spi_config.SSI = ssi;
	spi->spi_config.DFF = dff;
	spi->spi_config.BUS = bus_cfg;

}
void spi_init(SPI_Handle_t* spi_handle)
{
	spi_clk_control(spi_handle, ENABLE);

	uint32_t temp = 0;
	temp |= (spi_handle->spi_config.CPHA)<<CR1_BIT0_CPHA;
	temp |= (spi_handle->spi_config.CPOL)<<CR1_BIT1_CPOL;
	temp |= (spi_handle->spi_config.MSTR)<<CR1_BIT2_MSTR;
	temp |= (spi_handle->spi_config.BR)<<CR1_BIT3_BR0;
	temp |= DISABLE<<CR1_BIT7_LSB;
	temp |= (spi_handle->spi_config.DFF)<<CR1_BIT11_DFF;
	temp |= (spi_handle->spi_config.SSM)<<CR1_BIT9_SSM;

	if (spi_handle->spi_config.BUS == SPI_HALF_DUPLEX)
	{
		/*Half duplex - BIDIMODE bit should be enabled*/
		temp |= ENABLE<<CR1_BIT15_BIDIMODE;
	}
	else
	{
		/*Full duplex - BIDIMODE bit should be reset*/
		temp &= ~(ENABLE<<CR1_BIT15_BIDIMODE);
		if (spi_handle->spi_config.BUS == SPI_SIMPLEX_RX_ONLY)
		{
			/*Simplex RX only - RXONLY bit should be enabled*/
			temp |= ENABLE<<CR1_BIT10_RXONLY;
		}
	}
	spi_handle->p_spi_x->SPI_CR1 = temp;

}
void spi_enable(SPI_RegDef_t *p_spi_x, uint8_t enable)
{
	p_spi_x->SPI_CR1 &= ~(1<<CR1_BIT6_SPE);
	p_spi_x->SPI_CR1 |= (enable<<CR1_BIT6_SPE);

}
void spi_ssi_enable(SPI_RegDef_t *p_spi_x, uint8_t enable)
{
	p_spi_x->SPI_CR1 &= ~(1<<CR1_BIT8_SSI);
	p_spi_x->SPI_CR1 |= (enable<<CR1_BIT8_SSI);

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
			if (((p_spi_x->SPI_CR1)&(1<<CR1_BIT11_DFF)) == SPI_DFF_8_BIT)
			/*If Frame format is 8 bit*/
			{
				p_spi_x->SPI_DR = *pTxbuffer;
				pTxbuffer++;
				len--;
			}
			else
			/*If Frame format is 16 bit*/
			{
				p_spi_x->SPI_DR = *((uint16_t*)pTxbuffer);
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
void spi_recieve(SPI_RegDef_t* p_spi_x,uint8_t *pRxbuffer, uint32_t len)
{
	while(len > 0)
		{
			if (((p_spi_x->SPI_SR)&(1<<SR_BIT0_RXNE)) != 0)
			/*If RX buffer get the data from the shift register*/
			{
				if (((p_spi_x->SPI_CR1)&(1<<CR1_BIT11_DFF)) == SPI_DFF_8_BIT)
				/*If Frame format is 8 bit*/
				{
					*pRxbuffer |= p_spi_x->SPI_DR;
					pRxbuffer++;
					len--;
				}
				else
				/*If Frame format is 16 bit*/
				{
					*((uint16_t*)pRxbuffer) |= p_spi_x->SPI_DR;
					len = len-2;
					(uint16_t*)pRxbuffer++;

				}
			}
		}

}






