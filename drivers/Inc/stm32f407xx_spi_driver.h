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
				1.1.SPI CPHA MODES (CPHA BIT)
*******************************************************/
#define 	SPI_CLK_IDLE_1		1		/*CLK is 1 when idle*/
#define 	SPI_CLK_IDLE_0		0		/*CLK is 0 when idle*/

/******************************************************
				1.2.SPI CPOL MODES (CPOL BIT)
*******************************************************/
#define 	SPI_CLK_PHASE_1		1		/*The first clock transition is the first data capture edge*/
#define 	SPI_CLK_PHASE_0		0		/*The second clock transition is the first data capture edge*/

/******************************************************
				1.3.SPI MASTR MODES (CPOL BIT)
*******************************************************/
#define 	SPI_MASTER		1
#define 	SPI_SLAVE		0

/******************************************************
				1.4.SPI BR - baud rate modes (BR[0:2] BITS)
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
				1.5.SPI LSB FIRST (LSB FIRST BIT)
*******************************************************/
#define 	SPI_MSB_FIRST				0
#define 	SPI_LSB_FIRST				1

/******************************************************
				1.6.SPI Data frame format (DFF BIT)
*******************************************************/
#define 	SPI_DFF_8_BIT				0
#define 	SPI_DFF_16_BIT				1

/******************************************************
				1.7.SPI Slave Select Management (SSM BIT)
*******************************************************/
#define 	SPI_SSM_DIS				0
#define 	SPI_SSM_EN				1

/******************************************************
				1.8.SPI Internal Slave Select (SSI BIT 8)
*******************************************************/
#define 	SPI_SSI_DIS				0
#define 	SPI_SSI_EN				1

/******************************************************
				1.9.SPI BUS configuration
*******************************************************/
#define 	SPI_FULL_DUPLEX				1			/**/
#define 	SPI_HALF_DUPLEX				2			/**/
#define 	SPI_SIMPLEX_RX_ONLY			3			/**/

/******************************************************
				1.10.SPI Bidirectional data mode enable (BIDIMODE BIT)
*******************************************************/
#define 	SPI_UNIDI_MODE				0			/*2-line unidirectional data mode selected*/
#define 	SPI_BIDI_MODE				1			/*1-line bidirectional data mode selected*/

/******************************************************
				1.11.SPI Bidirectional output enable (BIDIOE BIT)
*******************************************************/
#define 	SPI_BIDI_OUT_DIS		0			/*Output disabled (receive-only mode)*/
#define 	SPI_BIDI_OUT_EN			1			/*Output enabled (transmit-only mode)*/

/******************************************************
				1.12.SPI Control register 1 bit fields macros
*******************************************************/
#define 	CR1_BIT0_CPHA				0
#define 	CR1_BIT1_CPOL				1
#define 	CR1_BIT2_MSTR				2
#define 	CR1_BIT3_BR0				3
#define 	CR1_BIT4_BR1				4
#define 	CR1_BIT5_BR2				5
#define 	CR1_BIT6_SPE				6
#define 	CR1_BIT7_LSB				7
#define 	CR1_BIT8_SSI				8
#define 	CR1_BIT9_SSM				9
#define 	CR1_BIT10_RXONLY			10
#define 	CR1_BIT11_DFF				11
#define 	CR1_BIT12_CRCNEXT			12
#define 	CR1_BIT13_CRCEN				13
#define 	CR1_BIT14_BIDIOE			14
#define 	CR1_BIT15_BIDIMODE			15

/******************************************************
				1.13.SPI Control register 2 bit fields macros
*******************************************************/
#define 	CR2_BIT0_RXDMAEN			0
#define 	CR2_BIT1_TXDMAEN			1
#define 	CR2_BIT2_SSOE				2
#define 	CR2_BIT4_FRF				4
#define 	CR2_BIT5_ERRIE				5
#define 	CR2_BIT6_RXNEIE				6
#define 	CR2_BIT7_TXEIE				7

/******************************************************
				1.14.SPI Status register bit fields macros
*******************************************************/
#define 	SR_BIT0_RXNE				0
#define 	SR_BIT1_TXE					1
#define 	SR_BIT2_CHSIDE				2
#define 	SR_BIT3_UDR					3
#define 	SR_BIT4_MODF				4
#define 	SR_BIT5_OVR					5
#define 	SR_BIT6_BSY					6
#define 	SR_BIT7_FRE					7

/******************************************************
				1.15.SPI RECIEVE BUFFER STATUS
*******************************************************/
#define 	RX_BUFFER_EMPTY				0
#define 	RX_BUFFER_NOT_EMPTY			1


/******************************************************
				1.16.SPI TRANSMIT BUFFER STATUS
*******************************************************/
#define 	TX_BUFFER_NOT_EMPTY			0
#define 	TX_BUFFER_EMPTY				1



#define SPI_SR_RXNE						0
#define SPI_SR_TXE				 		1
#define SPI_SR_CHSIDE				 	2
#define SPI_SR_UDR					 	3
#define SPI_SR_CRCERR				 	4
#define SPI_SR_MODF					 	5
#define SPI_SR_OVR					 	6
#define SPI_SR_BSY					 	7
#define SPI_SR_FRE					 	8

#define FLAG_RESET          0
#define FLAG_SET 			1


#define SPI_TXE_FLAG    ( 1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG   ( 1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG   ( 1 << SPI_SR_BSY)

/******************************************************
				2.SPI structure definitions
*******************************************************/

/******************************************************
				2.1.SPI pin configuration structure
*******************************************************/
typedef struct
{
	uint8_t 	CPHA;			/*Clock phase*/
	uint8_t 	CPOL;			/*Clock  polarity*/
	uint8_t 	MSTR;			/*Master selection*/
	uint8_t 	BR;				/*Baud rate control*/
	uint8_t 	DFF;			/*Data Frame format*/
	uint8_t 	SSM;			/*slave select management*/
	uint8_t 	SSI;			/*internal slave select*/
	uint8_t 	BUS;			/*Bus communication method Full/Half duplex/simplex */
}SPI_Config_t;

/******************************************************
				2.2.SPI handler structure
*******************************************************/
typedef struct
{
	SPI_RegDef_t 		*p_spi_x;		/*Base address of the SPIx base address*/
	SPI_Config_t 		spi_config;	/**/
}SPI_Handle_t;



/*******************************************************************************************
				3.API supported by this driver
********************************************************************************************/


/******************************************************
				3.1.SPI CLK control
*******************************************************/

/* Enables the bus clock of SPIx based on its location (which bus).
 * Arguments:
 * ==============
 *  		spi_handle:	Structure contains all relevant data regard to SPI peripheral instance.
*/
void spi_clk_control(SPI_Handle_t* spi_handle,uint8_t EnOrDi);

/******************************************************
				3.2.SPI initializations
*******************************************************/

void spi_configure_pin(SPI_Handle_t* spi, SPI_RegDef_t* spi_x, int cpha, int cpol, int master, int baudrate, int ssm, int ssi, int dff, int bus_cfg);
/* Initializes all relevant bits in SPI registers (mainly in control register 1 SPI_CR1) based on user initialization in main
 * Arguments:
 * ==============
 *  		spi_handle:	pointer to structure contains all relevant data regard to SPI peripheral instance.
 */
void spi_init(SPI_Handle_t* spi_handle);
/* Enable/Disable the SPI peripheral since configuring parameters is not recommended while peripheral is enabled
 * Arguments:
 * ==============
 *  		spi_handle:	pointer to structure contains all relevant data regard to SPI peripheral instance.
 *  		enable	  : enable or disable the peripheral
 */
void spi_enable(SPI_RegDef_t *p_spi_x, uint8_t enable);
/* Set the SSI bit in order to avoid the MODEF fault handler
 * Arguments:
 * ==============
 *  		spi_handle:	pointer to structure contains all relevant data regard to SPI peripheral instance.
 *  		enable	  : enable or disable the peripheral
 */void spi_ssi_enable(SPI_RegDef_t *p_spi_x, uint8_t enable);

/******************************************************
				3.3.SPI send/receive functions
*******************************************************/

/* Sends data frames (8 or 16 bit) to SPI_DR (data register), each frame is sent to SPI_DR.
 * Next frame will be sent once TX buffer is empty (indication via SPI_SR (status register) TXE bit) function terminates once all frames sent(len).
 * Arguments:
 * ==============
 * 				p_spi_x   :	SPI registers structure
 *  			*pTxbuffer:	pointer to data frames
 *  			len 	  :	number of data frames
 */
void spi_send(SPI_RegDef_t* p_spi_x,uint8_t *pTxbuffer, uint32_t len);
/* Sends data frames (8 or 16 bit) to SPI_DR (data register), each frame is sent to SPI_DR.
 * Next frame will be sent once TX buffer is empty (indication via SPI_SR (status register) TXE bit) function terminates once all frames sent(len).
 * Arguments:
 * ==============
 * 				p_spi_x   :	SPI registers structure
 *  			*pRxbuffer:	pointer to stored data frames
 *  			len 	  :	number of data frames
 */
void spi_recieve(SPI_RegDef_t* p_spi_x,uint8_t *pRxbuffer, uint32_t len);

#endif /* INC_STM32F4XX_SPI_DRIVERS_H_ */
