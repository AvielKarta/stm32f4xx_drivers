/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: Jan 4, 2020
 *      Author: Aviel karta
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_


#include "stm32f407xx.h"
#include <stdint.h>


/******************************************************
				@0.GPIO pin possible modes
*******************************************************/
#define 	GPIO_MODE_IN		0			/*GPIO Input mode*/
#define 	GPIO_MODE_OUT		1			/*GPIO Output mode*/
#define 	GPIO_MODE_ALTFN		2			/*GPIO Output ALternate functionality mode*/
#define 	GPIO_MODE_ANALOG	3			/*GPIO Output analog mode*/

//Interrupt modes
#define 	GPIO_MODE_IN_FT		4			/*GPIO Input mode - falling edge*/
#define 	GPIO_MODE_IN_RT		5			/*GPIO Input mode - rising edge*/
#define	 	GPIO_MODE_IN_RFT	6			/*GPIO Input mode - rise fall edge*/

/******************************************************
				@1.GPIO pin output modes
*******************************************************/
#define 	GPIO_OUT_MODE_PP		0		/*GPIO output mode - Push pull edge*/
#define 	GPIO_OUT_MODE_OD		1		/*GPIO output mode - Open drain*/

/******************************************************
				@2.GPIO pin speed modes
*******************************************************/
#define 	GPIO_SPPED_LOW			0
#define 	GPIO_SPPED_MEDIUM		1
#define 	GPIO_SPPED_FAST			2
#define 	GPIO_SPPED_HIGH			3

/******************************************************
				@3.GPIO pin pull up/down  modes
*******************************************************/
#define 	GPIO_DIS_PUPD			0
#define 	GPIO_PU					1
#define 	GPIO_PD					2


typedef struct
{
	uint8_t 	PinNumber;		/*Contains Pin number*/
	uint8_t 	PinMode;		/*Configures Pin Mode, possible values are @0.GPIO pin possible modes */
	uint8_t 	PinSpeed;		/*Configures Pin Speed, possible values are,@2.GPIO pin speed modes */
	uint8_t 	PinPuPdCtrl;	/*Configures Pin pull up/down modes, possible values are @3.GPIO pin pull up/down modes*/
	uint8_t 	PinOType;		/*Configures Pin output mode, possible vales are@1.GPIO pin output modes */
	uint8_t 	PinAltFunc;		/*Configures Pin */
}GPIO_PinConfig_t;

typedef struct
{
	GPIO_RegDef_t 		*pGPIOx;		/*Base address of the GPIO that the pin belongs to*/
	GPIO_PinConfig_t 	GPIO_PinCfng;	/**/
}GPIO_Handle_t;

/*******************************************************************************************
				API's supported by this driver
********************************************************************************************/
//1.Clock control
void GPIO_CLKCtrl(GPIO_RegDef_t *pGPIOx,uint8_t EnOrDi);

//2.Initialize and deInitialize
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

//3.Data read\write
uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value);
void GPIO_WriteToPort(GPIO_RegDef_t *pGPIOx, uint16_t value);
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t pin_number);

//4.Interrupt handling
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi);
void GPIO_IRQHandle(uint8_t PinNumber);

//4.GPIO control
void configure_gpio_pin(GPIO_Handle_t *GpioLed, GPIO_RegDef_t* gpio, int pin_number, int output_mode, int pin_speed, int pin_out_mode,int internal_resistor_state);

#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */





