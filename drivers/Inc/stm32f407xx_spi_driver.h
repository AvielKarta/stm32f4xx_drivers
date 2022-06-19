/*
 * stm32f4xx_spi_drivers.h
 *
 *  Created on: 14 ביוני 2022
 *      Author: avielk
 */

#ifndef INC_STM32F4XX_SPI_DRIVERS_H_
#define INC_STM32F4XX_SPI_DRIVERS_H_

#include "stm32f407xx.h"
#include <stdint.h>



/******************************************************
						1.MACROS
*******************************************************/

/******************************************************
				1.1.SPI CPHA MODES
*******************************************************/
#define 	CLK_IDLE_1		1		/*CLK is 1 when idle*/
#define 	CLK_IDLE_0		0		/*CLK is 0 when idle*/

/******************************************************
				1.2.SPI CPOL MODES
*******************************************************/
#define 	CLK_PHASE_1		1		/*The first clock transition is the first data capture edge*/
#define 	CLK_PHASE_0		0		/*The second clock transition is the first data capture edge*/

/******************************************************
				1.3.SPI MASTR MODES
*******************************************************/
#define 	SPI_MASTER		1
#define 	SPI_SLAVE		0


/******************************************************
				1.4.SPI BR (baudrate) modes
*******************************************************/
#define 	SPI_BR_CLK_DIV_2		0		/*configure fPCLK/2*/
#define 	SPI_BR_CLK_DIV_4		1		/*configure fPCLK/4*/
#define 	SPI_BR_CLK_DIV_8		2		/*configure fPCLK/8*/
#define 	SPI_BR_CLK_DIV_16		3		/*configure fPCLK/16*/
#define 	SPI_BR_CLK_DIV_32		4		/*configure fPCLK/32*/
#define 	SPI_BR_CLK_DIV_64		5		/*configure fPCLK/64*/
#define 	SPI_BR_CLK_DIV_128		6		/*configure fPCLK/182*/
#define 	SPI_BR_CLK_DIV_256		7		/*configure fPCLK/256*/

/******************************************************
				1.5.SPI Frame format
*******************************************************/
#define 	MSB_FIRST				0
#define 	LSB_FIRST				1

/******************************************************
				1.6.SPI SSM (Slave Select Management)
*******************************************************/
#define 	SSM_DIS				0
#define 	SSM_EN				1



/******************************************************
				2.SPI structure definitions
*******************************************************/

/******************************************************
				2.1.SPI pin configuration structure
*******************************************************/
typedef struct
{
	uint8_t 	CPHA;			/*Clock phase*/
	uint8_t 	CPOL;			/*Clock polarity*/
	uint8_t 	MSTR;			/*Master selection*/
	uint8_t 	BR;				/*Baud rate control*/
	uint8_t 	DFF;			/*Data Frame format*/
	uint8_t 	SSM;			/**/
}SPI_PinConfig_t;

/******************************************************
				2.2.SPI handler structure
*******************************************************/
typedef struct
{
	SPI_RegDef_t 		*p_spi_x;		/*Base address of the GPIO that the pin belongs to*/
	SPI_PinConfig_t 	spi_pin_config;	/**/
}SPI_Handle_t;



/*******************************************************************************************
				3.API supported by this driver
********************************************************************************************/

/******************************************************
				3.1.SPI CLK control
*******************************************************/
void spi_clk_control(SPI_Handle_t* spi_handle,uint8_t EnOrDi);

/******************************************************
				3.1.SPI de/init
*******************************************************/
void spi_init(SPI_Handle_t* spi_handle);
void spi_irq_set(uint8_t IRQNumber);
void spi_irq_clear(uint8_t IRQNumber);
void spi_irq_priority(uint8_t IRQNumber, uint8_t IRQPriority);
void spi_irq_handler(uint8_t PinNumber);

/******************************************************
				3.3.SPI send/receive functions
*******************************************************/
void spi_send_data(SPI_Handle_t* spi_handle);
void spi_receive_data(SPI_Handle_t* spi_handle);

#endif /* INC_STM32F4XX_SPI_DRIVERS_H_ */
