#ifndef INC_STM32F407XX_UART_DRIVER_H_
#define INC_STM32F407XX_UART_DRIVER_H_

#include "stm32f407xx.h"

/******************************************************
						1.UART structures
*******************************************************/
/******************************************************
				1.1.UART pin configuration structure
*******************************************************/
typedef struct
{
	uint8_t 	mode;						/*RX/TX/Both*/
	uint32_t 	baud_rate;					/**/
	uint8_t 	stop_bit_amount;			/*1,1.5,2*/
	uint8_t 	word_length;				/*8 or 9*/
	uint8_t 	parity;						/*Data Frame format*/
	uint8_t 	hw_flow_control;			/*slave select management*/

}UartConfig_t;

/******************************************************
				1.2. UART handler structure
*******************************************************/
typedef struct
{
	UartRegisters_t* 		p_uart_x;		/*Base address of the UARTx base address*/
	UartConfig_t 			uart_config;	/**/
}UartHandler_t;



/******************************************************
				2. UART functions
*******************************************************/
void uart_clk_control(UartHandler_t* uart_handler, uint8_t enable);
void uart_configure_pin(UartHandler_t* uart, UartRegisters_t* uart_x, uint8_t mode, uint32_t baud_rate, uint8_t stop_bit_amount, uint8_t word_length, uint8_t parity, uint8_t hw_flow_control);
void uart_init(UartHandler_t* uart_handler);
void uart_set_baud_rate(UartHandler_t* uart_handler, uint32_t baud_rate, uint32_t clock_frequency);

/******************************************************
				3. UART registers bit positions
*******************************************************/
/******************************************************
				3.1 status register bit positions
*******************************************************/

#define     SR_BIT0_PE                  0   // Parity Error
#define     SR_BIT1_FE                  1   // Framing Error
#define     SR_BIT2_NE                  2   // Noise Error Flag
#define     SR_BIT3_ORE                 3   // Overrun Error
#define     SR_BIT4_IDLE                4   // IDLE Line Detected
#define     SR_BIT5_RXNE                5   // Read Data Register Not Empty
#define     SR_BIT6_TC                  6   // Transmission Complete
#define     SR_BIT7_TXE                 7   // Transmit Data Register Empty
#define     SR_BIT8_LBD                 8   // LIN Break Detection Flag
#define     SR_BIT9_CTS                 9   // CTS Flag

/******************************************************
				3.2.Data register bit positions
*******************************************************/
#define     DR_MASK_DATA                0x1FF // 9-bit Data Mask (Bits 0-8)

/******************************************************
				3.3.Baud rate register bit positions
*******************************************************/
#define     BRR_BIT0_DIV_FRACTION       0   // Fraction of USARTDIV (Bits 0-3)
#define     BRR_BIT4_DIV_MANTISSA       4   // Mantissa of USARTDIV (Bits 4-15)
/******************************************************
				3.4.Control register 1 bit positions
*******************************************************/
#define     USART_CR1_BIT0_SBK                0   // Send Break
#define     USART_CR1_BIT1_RWU                1   // Receiver Wakeup
#define     USART_CR1_BIT2_RE                 2   // Receiver Enable
#define     USART_CR1_BIT3_TE                 3   // Transmitter Enable
#define     USART_CR1_BIT4_IDLEIE             4   // IDLE Interrupt Enable
#define     USART_CR1_BIT5_RXNEIE             5   // RXNE Interrupt Enable
#define     USART_CR1_BIT6_TCIE               6   // Transmission Complete Interrupt Enable
#define     USART_CR1_BIT7_TXEIE              7   // TXE Interrupt Enable
#define     USART_CR1_BIT8_PEIE               8   // PE Interrupt Enable
#define     USART_CR1_BIT9_PS                 9   // Parity Selection
#define     USART_CR1_BIT10_PCE               10  // Parity Control Enable
#define     USART_CR1_BIT11_WAKE              11  // Wakeup Method
#define     USART_CR1_BIT12_M                 12  // Word Length
#define     USART_CR1_BIT13_UE                13  // USART Enable
#define     USART_CR1_BIT15_OVER8             15  // Oversampling Mode
/******************************************************
				3.5.Control register 2 bit positions
*******************************************************/
#define     USART_CR2_BIT0_ADD                0   // Address of the USART node (Bits 0-3)
#define     USART_CR2_BIT5_LBDL               5   // LIN Break Detection Length
#define     USART_CR2_BIT6_LBDIE              6   // LIN Break Detection Interrupt Enable
#define     USART_CR2_BIT8_LBCL               8   // Last Bit Clock Pulse
#define    	USART_CR2_BIT9_CPHA               9   // Clock Phase
#define     USART_CR2_BIT10_CPOL              10  // Clock Polarity
#define     USART_CR2_BIT11_CLKEN             11  // Clock Enable
#define     USART_CR2_BIT12_STOP              12  // STOP bits (Bits 12-13)
#define     USART_CR2_BIT14_LINEN             14  // LIN Mode Enable
/******************************************************
				3.6.Control register 3 bit positions
*******************************************************/
#define     USART_CR3_BIT0_EIE                0   // Error Interrupt Enable
#define     USART_CR3_BIT1_IREN               1   // IrDA Mode Enable
#define     USART_CR3_BIT2_IRLP               2   // IrDA Low-Power
#define     USSART_CR3_BIT3_HDSEL              3   // Half-Duplex Selection
#define     USART_CR3_BIT4_NACK               4   // Smartcard NACK Enable
#define     USART_CR3_BIT5_SCEN               5   // Smartcard Mode Enable
#define     USART_CR3_BIT6_DMAT               6   // DMA Enable Transmitter
#define     USART_CR3_BIT7_DMAR               7   // DMA Enable Receiver
#define     USART_CR3_BIT8_RTSE               8   // RTS Enable
#define     USART_CR3_BIT9_CTSE               9   // CTS Enable
#define     USART_CR3_BIT10_CTSIE             10  // CTS Interrupt Enable
#define     USART_CR3_BIT11_ONEBIT            11  // One sample bit method enable
/******************************************************
				3.7.status register bit positions
*******************************************************/
#define     USART_GTPR_BIT0_PSC               0   // Prescaler value (Bits 0-7)
#define     USART_GTPR_BIT8_GT                8   // Guard time value (Bits 8-15)

/******************************************************
				4.UartConfig_t options
*******************************************************/


#define 	USART_MODE_ONLY_RX 			0
#define 	USART_MODE_ONLY_TX		 	1
#define 	USART_MODE_TX_RX 			2

#define 	USART_BR_9600 				0
#define 	USART_BR_115200 			1

#define 	USART_SB_1		 			0
#define 	USART_SB_0_5		 		1
#define 	USART_SB_2				 	2
#define 	USART_SB_1_5	 			3

#define 	USART_8_BIT				 	0
#define 	USART_9_BIT		 			1

#define 	USART_PARITY_DIS			0
#define 	USART_PARITY_EVEN			1
#define 	USART_PARITY_ODD			2

#define 	USART_HW_FLOW_CTRL_CTS			0
#define 	USART_HW_FLOW_CTRL_RTS			1
#define 	USART_HW_FLOW_CTRL_CTS_RTS		2


#endif /* INC_STM32F407XX_UART_DRIVER_H_ */
