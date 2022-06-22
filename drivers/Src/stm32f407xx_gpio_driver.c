/*
 * 		stm32f407xx_gpio_driver.c
 *      Author:  Aviel karta
 */
# include "stm32f407xx.h"

/******************************************************
				1.GPIO CLK control
*******************************************************/
void gpio_clk_control(GPIO_RegDef_t *pGPIOx,uint8_t enable)
{
	if (enable)
	{
		if (pGPIOx == GPIOA)
		{
			GPIOA_CLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_CLK_EN();
		}
		else if (pGPIOx == GPIOC)
		{
			GPIOC_CLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_CLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_CLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_CLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_CLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_CLK_EN();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_CLK_EN();
		}

	}

	else
	{
		if (pGPIOx == GPIOA)
		{
			GPIOA_CLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_CLK_DI();
		}
		else if (pGPIOx == GPIOC)
		{
			GPIOC_CLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_CLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_CLK_DI();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_CLK_DI();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_CLK_DI();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_CLK_DI();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_CLK_DI();
		}

	}

}

/******************************************************
				2.GPIO initializations
*******************************************************/
void gpio_init(GPIO_Handle_t *pGPIOHandle)
{

	gpio_clk_control(pGPIOHandle->pGPIOx, ENABLE);/*Initializes the clock control*/
	uint32_t temp=0;

	/* 1.Configure GPIO pin mode - each pin has 2 dedicated bits in the GPIO mode register
	hence the value is shifted with multiplication  of 2 relative to pin #. */

	//1.1.Non interrupt mode
	if (pGPIOHandle->GPIO_PinCfng.PinMode <= GPIO_MODE_ANALOG)
	{

		temp = (pGPIOHandle->GPIO_PinCfng.PinMode << (2* pGPIOHandle->GPIO_PinCfng.PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinCfng.PinNumber); //Clear the 2 bits
		pGPIOHandle->pGPIOx->MODER |= temp;// Write to the 2 bits
		temp= 0;
	}

	//1.2.Interrupt mode
	else
	{
		// Enable the Interrupt mask register
		EXTI->IMR |=   (1 << pGPIOHandle->GPIO_PinCfng.PinNumber);

		if (pGPIOHandle->GPIO_PinCfng.PinMode == GPIO_MODE_IRQ_FT)
		{	// Enable only the rising trigger selection register
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinCfng.PinNumber);
			EXTI->FTSR|=   (1 << pGPIOHandle->GPIO_PinCfng.PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinCfng.PinMode == GPIO_MODE_IRQ_RT)
		{
			//Enable only falling trigger selection register
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinCfng.PinNumber);
			EXTI->RTSR|=   (1 << pGPIOHandle->GPIO_PinCfng.PinNumber);
		}
		else if (pGPIOHandle->GPIO_PinCfng.PinMode == GPIO_MODE_IRQ_RFT)
		{
			//Enable both falling and rising trigger selection register
			EXTI->RTSR|=   (1 << pGPIOHandle->GPIO_PinCfng.PinNumber);
			EXTI->FTSR|=   (1 << pGPIOHandle->GPIO_PinCfng.PinNumber);
		}
		//Select the SYSCFG register

		uint32_t value = 0;
		if (pGPIOHandle->pGPIOx == GPIOA)
			value = 0;
		else if (pGPIOHandle->pGPIOx == GPIOB)
			value = 1;
		else if (pGPIOHandle->pGPIOx == GPIOC)
			value = 2;
		else if (pGPIOHandle->pGPIOx == GPIOD)
			value = 3;
		else if (pGPIOHandle->pGPIOx == GPIOE)
			value = 4;
		else if (pGPIOHandle->pGPIOx == GPIOF)
			value = 5;
		else if (pGPIOHandle->pGPIOx == GPIOG)
			value = 6;
		else if (pGPIOHandle->pGPIOx == GPIOH)
			value = 7;
		else if (pGPIOHandle->pGPIOx == GPIOI)
			value = 8;

		SYSCFG_CLK_EN();
		uint32_t exticr_reg = pGPIOHandle->GPIO_PinCfng.PinNumber/4;
		uint32_t exticr_position = pGPIOHandle->GPIO_PinCfng.PinNumber%4;
		SYSCFG->EXTICR[exticr_reg ] &= ~(value<<4*exticr_position);
		SYSCFG->EXTICR[exticr_reg ] |= value<<4*exticr_position;

	}

	/*2. Configure GPIO pin speed - each pin has 2 dedicated bits in the GPIO mode register
	hence the value is shifted as multiplication  of 2 relative to pin # */
	temp = (pGPIOHandle->GPIO_PinCfng.PinSpeed << (2* pGPIOHandle->GPIO_PinCfng.PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinCfng.PinNumber)); //Clear the 2 bits
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;// Write to the 2 bits
	temp= 0;

	/*3. Configure GPIO pin pull up\pull down register - each pin has 2 dedicated bits
	in the GPIO mode register hence the value is shifted with as multiplication of 2 relative to pin # */
	temp = (pGPIOHandle->GPIO_PinCfng.PinPuPdCtrl << (2* pGPIOHandle->GPIO_PinCfng.PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << ( 2* pGPIOHandle->GPIO_PinCfng.PinNumber)); //Clear the 2 bits
	pGPIOHandle->pGPIOx->PUPDR |= temp;// Write to the 2 bits
	temp= 0;

	/*4. Configure GPIO pin output type register - each pin has 1 dedicated bits
	 in the GPIO output type register hence the value is shifted relative to pin #. */
	temp = (pGPIOHandle->GPIO_PinCfng.PinOType << (pGPIOHandle->GPIO_PinCfng.PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinCfng.PinNumber); //Clear the 2 bits
	pGPIOHandle->pGPIOx->OTYPER |= temp;// Write to the bit
	temp= 0;

	/*5. Configure GPIO pin alternate functionality register - each pin has 4 dedicated bits
	 in it hence the value is shifted as multiplication of 4 relative to pin #. */
	if (pGPIOHandle->GPIO_PinCfng.PinMode == GPIO_MODE_ALTFN)
	{
		uint8_t temp1,temp2;
		temp1 = pGPIOHandle->GPIO_PinCfng.PinNumber / 8  ;
		temp2 = pGPIOHandle->GPIO_PinCfng.PinNumber % 8 ;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinCfng.PinAltFunc << (4 * temp2)); //write to the 4 bits
		temp1 = temp2 = 0;
	}


}
void gpio_deinit(GPIO_RegDef_t *pGPIOx)
{
	if (pGPIOx == GPIOA)
	{
		GPIOA_RST();
	}
	else if(pGPIOx == GPIOB)
	{
		GPIOB_RST();
	}
	else if (pGPIOx == GPIOC)
	{
		GPIOC_RST();
	}
	else if(pGPIOx == GPIOD)
	{
		GPIOD_RST();
	}
	else if(pGPIOx == GPIOE)
	{
		GPIOE_RST();
	}
	else if(pGPIOx == GPIOF)
	{
		GPIOF_RST();
	}
	else if(pGPIOx == GPIOG)
	{
		GPIOG_RST();
	}
	else if(pGPIOx == GPIOH)
	{
		GPIOH_RST();
	}
	else if(pGPIOx == GPIOI)
	{
		GPIOI_RST();
	}
}
void gpio_configure_pin(GPIO_Handle_t *gpio_x_pin, GPIO_RegDef_t* gpio, int pin_number, int output_mode, int pin_speed, int pin_out_mode,int internal_resistor, int alternate_function)
{
	gpio_x_pin->pGPIOx = gpio;
	gpio_x_pin->GPIO_PinCfng.PinNumber = pin_number;
	gpio_x_pin->GPIO_PinCfng.PinMode = output_mode;
	gpio_x_pin->GPIO_PinCfng.PinSpeed = pin_speed;
	gpio_x_pin->GPIO_PinCfng.PinOType = pin_out_mode;
	gpio_x_pin->GPIO_PinCfng.PinPuPdCtrl = internal_resistor;
	gpio_x_pin->GPIO_PinCfng.PinAltFunc = alternate_function;
}

/******************************************************
				3.GPIO read/write functions
*******************************************************/
uint8_t gpio_read_pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)

{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >>PinNumber) & 0x00000001); // shift n-th bit on the LSB and masking the rest
	return value;
}
uint16_t gpio_read_port(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR; // returns the entire register
	return value;
}
void gpio_write_to_pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value)
{
	if (value == ENABLE)
	{
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
	/*
	pGPIOx->ODR &= ~ (0x1 << PinNumber);
	pGPIOx->ODR |= (value << PinNumber);
	 */


}
void gpio_write_to_port(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
	pGPIOx->ODR = value;
}
void gpio_toggle_pin(GPIO_RegDef_t *pGPIOx, uint8_t pin_number)
{
	pGPIOx->ODR ^= (1 << pin_number); //changing previous pin state
}

/******************************************************
				4.GPIO Interrupt request functions
*******************************************************/
void gpio_irq_set(uint8_t IRQNumber)
{
	if (IRQNumber < 32)
		{*NVIC_ISER0 |= (1<<IRQNumber);}
	else if ((IRQNumber > 32)&&(IRQNumber < 64))
		{*NVIC_ISER1 |= (1<<IRQNumber%32); }
	else if ((IRQNumber > 64)&&(IRQNumber < 96))
		{*NVIC_ISER2 |= (1<<IRQNumber%32); }
}
void gpio_irq_clear(uint8_t IRQNumber)

{
	if (IRQNumber < 32)
		{*NVIC_ICER0 |= (1<<IRQNumber); }
	else if ((IRQNumber > 32)&&(IRQNumber < 64))
		{*NVIC_ICER1 |= (1<<IRQNumber%32); }
	else if ((IRQNumber > 64)&&(IRQNumber < 96))
		{*NVIC_ICER2 |= (1<<IRQNumber%32); }
}
void gpio_irq_priority(uint8_t IRQNumber, uint8_t IRQPriority)
{
	uint8_t iprx = IRQNumber/4;
	uint8_t	iprx_section = IRQNumber%4;
	uint8_t shift_amount = (8 * iprx_section) + (8 - PRIORITY_NOT_IMPLEMENTED_BITS);
	*(NVIC_IPR_BASE + iprx) |= (IRQPriority << iprx_section) << (shift_amount);

}
void gpio_irq_handler(uint8_t PinNumber)
{
	//Clear the pending register pin
	if(EXTI->PR & (1 << PinNumber))
	{
		EXTI->PR |= (1 << PinNumber);
	}
}
