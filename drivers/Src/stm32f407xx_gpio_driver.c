/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: Jan 4, 2020
 *      Author: karta
 */
# include "stm32f407xx.h"

//1.Clock control
void GPIO_CLKCtrl(GPIO_RegDef_t *pGPIOx,uint8_t EnOrDi)
{
	if (EnOrDi == ENABLE)
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

	}

}

//2.Initialize and deInitialize
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp=0;

	/* 1.Configure GPIO pin mode - each pin has 2 dedicated bits in the GPIO mode register
	hence the value is shifted with multiplication  of 2 relative to pin #. */
	if (pGPIOHandle->GPIO_PinCfng.PinMode <= GPIO_MODE_ANALOG)
	{
		//non interrupt mode
		temp = (pGPIOHandle->GPIO_PinCfng.PinMode << (2* pGPIOHandle->GPIO_PinCfng.PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinCfng.PinNumber); //Clear the 2 bits
		pGPIOHandle->pGPIOx->MODER |= temp;// Write to the 2 bits
		temp= 0;
	}
	else
	{
		//Interrupt mode

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


	/*
	if (pGPIOHandle->GPIO_PinCfng.PinNumber > 8)
	{
		temp = (pGPIOHandle->GPIO_PinCfng.PinAltFunc << (4 * pGPIOHandle->GPIO_PinCfng.PinNumber));
		pGPIOHandle->pGPIOx->AFRH |= temp;
		temp= 0;
	}
	else
	{
		temp = (pGPIOHandle->GPIO_PinCfng.PinAltFunc << (4 *pGPIOHandle->GPIO_PinCfng.PinNumber));
		pGPIOHandle->pGPIOx->AFRL |= temp;
		temp= 0;
	}
	*/








}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
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

//3.Data read\write
uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >>PinNumber) & 0x00000001); // shift n-th bit on the LSB and masking the rest
	return value;
}
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR; // returns the entire register
	return value;
}
void GPIO_WriteToPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value)
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
void GPIO_WriteToPort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
	pGPIOx->ODR = value;
}
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t pin_number)
{
	pGPIOx->ODR ^= (1 << pin_number); //changing previous pin state
}

//4.LedController
void define_led(GPIO_Handle_t *GpioLed, GPIO_RegDef_t* gpio, int pin_number, int output_mode, int speed, int push_pull,int pull_up_down)
{
	GpioLed->pGPIOx = gpio;
	GpioLed->GPIO_PinCfng.PinNumber = pin_number;
	GpioLed->GPIO_PinCfng.PinMode = output_mode;
	GpioLed->GPIO_PinCfng.PinSpeed = speed;
	GpioLed->GPIO_PinCfng.PinOType = push_pull;
	GpioLed->GPIO_PinCfng.PinPuPdCtrl = pull_up_down;


}


