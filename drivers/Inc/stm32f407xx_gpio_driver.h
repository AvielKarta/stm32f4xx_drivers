/*
 * 		stm32f407xx_gpio_driver.h
 *      Author:  Aviel karta
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_


#include "stm32f407xx.h"
#include <stdint.h>



/******************************************************
						1.MACROS
*******************************************************/

/******************************************************
				1.1.GPIO pin possible modes
*******************************************************/
#define 	GPIO_MODE_IN		0			/*GPIO Input mode*/
#define 	GPIO_MODE_OUT		1			/*GPIO Output mode*/
#define 	GPIO_MODE_ALTFN		2			/*GPIO Output ALternate functionality mode*/
#define 	GPIO_MODE_ANALOG	3			/*GPIO Output analog mode*/

//Interrupt modes
#define 	GPIO_MODE_IRQ_FT	4			/*GPIO Input mode - falling edge*/
#define 	GPIO_MODE_IRQ_RT	5			/*GPIO Input mode - rising edge*/
#define	 	GPIO_MODE_IRQ_RFT	6			/*GPIO Input mode - rise fall edge*/

/******************************************************
				1.2.GPIO pin output modes
*******************************************************/
#define 	GPIO_OUT_MODE_PP		0		/*GPIO output mode - Push pull edge*/
#define 	GPIO_OUT_MODE_OD		1		/*GPIO output mode - Open drain*/

/******************************************************
				1.3.GPIO pin speed modes
*******************************************************/
#define 	GPIO_SPPED_LOW			0
#define 	GPIO_SPPED_MEDIUM		1
#define 	GPIO_SPPED_FAST			2
#define 	GPIO_SPPED_HIGH			3

/******************************************************
				1.4.GPIO pin pull up/down  modes
*******************************************************/
#define 	GPIO_DIS_PUPD			0
#define 	GPIO_PU					1
#define 	GPIO_PD					2



/******************************************************
				2.GPIO structure definitions
*******************************************************/

/******************************************************
				2.1.GPIO pin configuration structure
*******************************************************/
typedef struct
{
	uint8_t 	PinNumber;		/*Contains Pin number*/
	uint8_t 	PinMode;		/*Configures Pin Mode, possible values are @0.GPIO pin possible modes */
	uint8_t 	PinSpeed;		/*Configures Pin Speed, possible values are,@2.GPIO pin speed modes */
	uint8_t 	PinPuPdCtrl;	/*Configures Pin pull up/down modes, possible values are @3.GPIO pin pull up/down modes*/
	uint8_t 	PinOType;		/*Configures Pin output mode, possible vales are@1.GPIO pin output modes */
	uint8_t 	PinAltFunc;		/*Configures the alternate functionality Pin */
}GPIO_PinConfig_t;

/******************************************************
				2.1.GPIO pin configuration structure
*******************************************************/
typedef struct
{
	GPIO_RegDef_t 		*pGPIOx;		/*Base address of the GPIO that the pin belongs to*/
	GPIO_PinConfig_t 	GPIO_PinCfng;	/**/
}GPIO_Handle_t;

/*******************************************************************************************
				3.API supported by this driver
********************************************************************************************/

/******************************************************
				3.1.GPIO CLK control
*******************************************************/

/* Enables the bus clock of GPIOx on AHB1.
 * Arguments:
 * ==============
 * 		 	*pGPIOx 	:	pointer to structure address, contains all relevant data regard to GPIOx peripheral.
 *	 		enable		:	enable or disable the GPIOx CLK.*/
void gpio_clk_control(GPIO_RegDef_t *pGPIOx,uint8_t EnOrDi);

/******************************************************
				3.2.GPIO initializations
*******************************************************/

/* Configures a GPIO pin parameters based on user input			.
 * Arguments:
 * ==============
 * 			*gpio_x_pin				 : pointer to the GPIO_Handle_t structure of the selected pin
 * 			gpio					 : which gpio the pin belongs to
 * 			pin_number				 : pin number
 * 			output_mode			 	 : output_mode
 * 			pin_speed				 : output_mode
 * 			pin_out_mode			 : pin_out_mode
 * 			internal_resistor_state  : internal_resistor_state
 */
void gpio_configure_pin(GPIO_Handle_t *gpio_x_pin, GPIO_RegDef_t* gpio, int pin_number, int output_mode, int pin_speed, int pin_out_mode,int internal_resistor_state, int alternate_function);
/* Initializes all relevant registers (MODE, SPEED, OTYPE etc.. in GPIO_RegDef_t) for the given configured pin
 * based on the pGPIOHandle->GPIO_PinCfn parameters given by user
 * Arguments:
 * ==============
 * 			 *pGPIOHandle 	:	pointer to structure contains all relevant data regard to GPIOx peripheral.
 */
void gpio_init(GPIO_Handle_t *pGPIOHandle);
/* Resets all pins in the selected GPIO back to default				.
 * Arguments:
 * ==============
 *  		*pGPIOx 	:	pointer to structure address, contains all relevant data regard to GPIOx peripheral.
 */
void gpio_deinit(GPIO_RegDef_t *pGPIOx);

/******************************************************
				3.3.GPIO read\write functions
*******************************************************/

/* Reads data from GPIO single pin
 * Arguments:
 * ==============
 *  		*pGPIOx 	:	pointer to structure address, contains all relevant data regard to GPIOx peripheral.
 *  		PinNumber	:	pin number to read the data from.
 */
uint8_t gpio_read_pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
/* Reads data from GPIO entire port
 * Arguments:
 * ==============
 *  		*pGPIOx 	:	pointer to structure address, contains all relevant data regard to GPIOx peripheral.
 *
 */
uint16_t gpio_read_port(GPIO_RegDef_t *pGPIOx);
/* Writes data to GPIO single pin
 * Arguments:
 * ==============
 *  		*pGPIOx 	:	pointer to structure address, contains all relevant data regard to GPIOx peripheral.
 *  		PinNumber	:	pin number to read the data from.
 *  		value		:	value to be written
 */
void gpio_write_to_pin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value);
/* Reads data from GPIO single pin
 * Arguments:
 * ==============
 *  		*pGPIOx 	:	pointer to structure address, contains all relevant data regard to GPIOx peripheral.
 *  		PinNumber	:	pin number to read the data from.
 *  		value		:	value to be written to the entire port.
 */
void gpio_write_to_port(GPIO_RegDef_t *pGPIOx, uint16_t value);
/* Toggles single pin value
 * Arguments:
 * ==============
 *  		*pGPIOx 	:	pointer to structure address, contains all relevant data regard to GPIOx peripheral.
 *  		PinNumber	:	toggled pin number.
 */
void gpio_toggle_pin(GPIO_RegDef_t *pGPIOx, uint8_t pin_number);

/******************************************************
				3.4.GPIO Interrupt request functions
*******************************************************/

/* Sets the IRO number in the appropriate NVIC_ISERx register
 * Arguments:
 * ==============
 *  		IRQNumber 	:	interrupt number as listed in NVIC table (table 61 RM0090 Rev 17, P.372/1747)
 */
void gpio_irq_set(uint8_t IRQNumber);
/* Clears the IRO number in the appropriate NVIC_ICERx register
 * Arguments:
 * ==============
 *  		IRQNumber 	:	interrupt number as listed in NVIC table (table 61 RM0090 Rev 17, P.372/1747)
 */
void gpio_irq_clear(uint8_t IRQNumber);
/* Sets the IRO priority in the appropriate NVIC_ISERx register
 * Arguments:
 * ==============
 *  		IRQNumber 	:	interrupt number as listed in NVIC table (table 61 RM0090 Rev 17, P.372/1747)
 *  		IRQPriority :   interrupt priority
 */
void gpio_irq_priority(uint8_t IRQNumber, uint8_t IRQPriority);
/* Handles the interrupt, can perform additional tasks but currently clears the correspond bit in the pending register
 * Arguments:
 * ==============
 *  		PinNumber	:	pin number to be cleared
 *
 */
void gpio_irq_handler(uint8_t PinNumber);

#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */





