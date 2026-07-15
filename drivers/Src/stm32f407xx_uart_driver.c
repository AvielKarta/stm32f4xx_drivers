#include "stm32f407xx.h"
#include "stm32f407xx_uart_driver.h"

/******************************************************
				1.UART/USART CLK control
*******************************************************/

void uart_clk_control(UartHandler_t* uart_handler, uint8_t enable)
{

	if (enable)
	{
		if (uart_handler->p_uart_x == USART1)
		{
			USART1_CLK_EN();
		}
		else if (uart_handler->p_uart_x == USART2)
		{
			USART2_CLK_EN();
		}
		else if (uart_handler->p_uart_x == USART3)
		{
			USART3_CLK_EN();
		}
		else if (uart_handler->p_uart_x == UART4)
		{
			UART4_CLK_EN();
		}
		else if (uart_handler->p_uart_x == UART5)
		{
			UART5_CLK_EN();
		}
		else if (uart_handler->p_uart_x == USART6)
		{
			USART6_CLK_EN();
		}

	}
	else
	{
		if (uart_handler->p_uart_x == USART1)
		{
			USART1_CLK_DI();
		}
		else if (uart_handler->p_uart_x == USART2)
		{
			USART2_CLK_DI();
		}
		else if (uart_handler->p_uart_x == USART3)
		{
			USART3_CLK_DI();
		}
		else if (uart_handler->p_uart_x == UART4)
		{
			UART4_CLK_DI();
		}
		else if (uart_handler->p_uart_x == UART5)
		{
			UART5_CLK_DI();
		}
		else if (uart_handler->p_uart_x == USART6)
		{
			USART6_CLK_DI();
		}

	}


}

/******************************************************
				2.UART
*******************************************************/

void uart_configure_pin(UartHandler_t* uart, UartRegisters_t* uart_x, uint8_t mode, uint32_t baud_rate, uint8_t stop_bit_amount, uint8_t word_length, uint8_t parity, uint8_t hw_flow_control)
{
	uart->p_uart_x = uart_x;
	uart->uart_config.mode = mode;
	uart->uart_config.baud_rate = baud_rate;
	uart->uart_config.stop_bit_amount = stop_bit_amount;
	uart->uart_config.word_length = word_length;
	uart->uart_config.parity = parity;
	uart->uart_config.hw_flow_control = hw_flow_control;
}

void uart_init(UartHandler_t* uart_handler)
{

	uart_clk_control(uart_handler, ENABLE);
	uint32_t temp = 0;
	temp |= ENABLE << USART_CR1_BIT13_UE; //enable UART

	/*configure CR1*/

	/*define mode*/
	if (uart_handler->uart_config.mode == USART_MODE_ONLY_RX)
	{
		temp |= ENABLE << USART_CR1_BIT2_RE;
	}
	else if (uart_handler->uart_config.mode == USART_MODE_ONLY_TX)
	{
		temp |= ENABLE << USART_CR1_BIT3_TE;
	}
	else if (uart_handler->uart_config.mode == USART_MODE_ONLY_TX)
	{
		temp |= (ENABLE << USART_CR1_BIT3_TE) | (ENABLE << USART_CR1_BIT2_RE);
	}
	/*define word length*/
	if (uart_handler->uart_config.word_length == USART_8_BIT)
	{
		temp &= ~(ENABLE << USART_CR1_BIT12_M);
	}
	else
	{
		temp |= ENABLE << USART_CR1_BIT12_M;
	}
	/*define parity*/
	if (uart_handler->uart_config.parity == USART_PARITY_DIS)
	    {
	        temp &= ~(ENABLE << USART_CR1_BIT10_PCE);
	    }
	    else
	    {
	        temp |= (ENABLE << USART_CR1_BIT10_PCE);

	        if (uart_handler->uart_config.parity == USART_PARITY_ODD)
	        {
	            temp |= (ENABLE << USART_CR1_BIT9_PS);
	        }
	        else // USART_PARITY_EVEN
	        {
	            temp &= ~(ENABLE << USART_CR1_BIT9_PS);
	        }
	    }
	uart_handler->p_uart_x->UART_CR1 = temp;

	/*configure CR2*/
	/*define bit amount*/
	temp = 0;
	if (uart_handler->uart_config.stop_bit_amount == USART_SB_0_5)
	    {
	        temp |= (1 << USART_CR2_BIT12_STOP); // 01
	    }
	    else if (uart_handler->uart_config.stop_bit_amount == USART_SB_2)
	    {
	        temp |= (2 << USART_CR2_BIT12_STOP); // 10
	    }
	    else if (uart_handler->uart_config.stop_bit_amount == USART_SB_1_5)
	    {
	        temp |= (3 << USART_CR2_BIT12_STOP); // 11
	    }
	uart_handler->p_uart_x->UART_CR2 = temp;

	/*configure CR3*/
	temp = 0;
	/*define hw_flow_control*/
	if (uart_handler->uart_config.hw_flow_control == USART_HW_FLOW_CTRL_CTS)
	{
		temp |= ENABLE << USART_CR3_BIT9_CTSE;
	}
	else if (uart_handler->uart_config.hw_flow_control == USART_HW_FLOW_CTRL_RTS)
	{
		temp |= ENABLE << USART_CR3_BIT8_RTSE;
	}
	else if(uart_handler->uart_config.hw_flow_control == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		temp |= (ENABLE << USART_CR3_BIT9_CTSE) | (ENABLE << USART_CR3_BIT8_RTSE);
	}
	uart_handler->p_uart_x->UART_CR3 = temp;
	uart_set_baud_rate(uart_handler, uart_handler->uart_config.baud_rate, 16000000);
}

void uart_set_baud_rate(UartHandler_t* uart_handler, uint32_t baud_rate, uint32_t clock_frequency)
{
    uint32_t usartdiv, mantissa, fraction, temp = 0;



    usartdiv = (clock_frequency * 25) / (4 * baud_rate);
    mantissa = usartdiv / 100;
    fraction = (((usartdiv - (mantissa * 100)) * 16) + 50) / 100;
    if (fraction >= 16)
    {
        mantissa += 1;
        fraction = 0;
    }
    temp |= (mantissa << 4);
    temp |= (fraction & 0xF);

    uart_handler->p_uart_x->UART_BRR = temp;

}




