/*
 * 		stm32f407xx.h
 *      Author:  Aviel karta
 */


#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_



#include <stdint.h>


/*=================================================================================================================================================================================
																					STM side
=================================================================================================================================================================================*/


/******************************************************
				0.Generic Macros
*******************************************************/
#define __vo 									volatile

#define ENABLE									1
#define DISABLE									0
#define SET										1
#define RST										0
#define PRIORITY_NOT_IMPLEMENTED_BITS			4
#define K										1000
#define M										1000000

/******************************************************
				1.Memory base addresses
*******************************************************/

#define 	FLASH_BASE		 		0x80000000U
#define 	SRAM1_BASE 				0x20000000U
#define 	SRAM2_BASE 				0x2001C000U
#define     ROM_BASE				0x1FFF0000U
#define 	SRAM					SRAM1_BASE

/******************************************************
				2.Bus domains base addresses
*******************************************************/

#define 	APB1_BUS_BASE			0x40000000U
#define 	APB2_BUS_BASE			0x40010000U
#define 	AHB1_BUS_BASE			0x40020000U
#define 	AHB2_BUS_BASE			0x50000000U

/******************************************************
				3. Bus peripherals addresses
*******************************************************/
/*3.1 AHB1 peripherals addresses
------------------------------------------------------
3.1.1 GPIO
------------------------------------------------------
3.1.1.1 GPIO addresses
------------------------------------------------------*/

#define 	GPIOA_BASE				(AHB1_BUS_BASE + 0x000)
#define 	GPIOB_BASE				(AHB1_BUS_BASE + 0x400)
#define 	GPIOC_BASE				(AHB1_BUS_BASE + 0x800)
#define 	GPIOD_BASE				(AHB1_BUS_BASE + 0xC00)
#define 	GPIOE_BASE				(AHB1_BUS_BASE + 0x1000)
#define 	GPIOF_BASE				(AHB1_BUS_BASE + 0x1400)
#define 	GPIOG_BASE				(AHB1_BUS_BASE + 0x1800)
#define 	GPIOH_BASE				(AHB1_BUS_BASE + 0x1C00)
#define 	GPIOI_BASE				(AHB1_BUS_BASE + 0x2000)
#define 	RCC_BASE				(AHB1_BUS_BASE + 0x3800)
#define 	RCC						((RCC_RegDef_t*) RCC_BASE)
#define 	EXTI					((EXTI_RegDef_t*) EXTI_BASE)
#define 	SYSCFG					((SYSCFG_RegDef_t*) SYSCFG_BASE)
/*------------------------------------------------------
3.1.1.2 GPIO addresses casted to the GPIO registers structure
------------------------------------------------------*/

#define 	GPIOA					((GPIO_RegDef_t*) GPIOA_BASE)
#define 	GPIOB					((GPIO_RegDef_t*) GPIOB_BASE)
#define 	GPIOC					((GPIO_RegDef_t*) GPIOC_BASE)
#define 	GPIOD					((GPIO_RegDef_t*) GPIOD_BASE)
#define 	GPIOE					((GPIO_RegDef_t*) GPIOE_BASE)
#define 	GPIOF					((GPIO_RegDef_t*) GPIOF_BASE)
#define 	GPIOG					((GPIO_RegDef_t*) GPIOG_BASE)
#define 	GPIOH					((GPIO_RegDef_t*) GPIOH_BASE)
#define 	GPIOI					((GPIO_RegDef_t*) GPIOI_BASE)

/*------------------------------------------------------
3.1.2 RCC
------------------------------------------------------
3.1.2.1 RCC addresses
------------------------------------------------------*/



/*------------------------------------------------------
3.1.1.2 RCC addresses casted to the RCC registers structure
------------------------------------------------------*/



/*----------------------------------------------------
3.2 AHB2 peripherals addresses
------------------------------------------------------*/

/*----------------------------------------------------
3.3 APB1 peripherals addresses
------------------------------------------------------
3.3.1 I2C addresses
------------------------------------------------------*/

#define 	I2C1_BASE				(APB1_BUS_BASE + 0x5400)
#define 	I2C2_BASE				(APB1_BUS_BASE + 0x5800)
#define 	I2C3_BASE				(APB1_BUS_BASE + 0x5C00)

/*----------------------------------------------------
3.3.2 SPI addresses
------------------------------------------------------*/

#define 	SPI2_BASE				(APB1_BUS_BASE + 0x3800)
#define 	SPI3_BASE				(APB1_BUS_BASE + 0x3C00)
/*----------------------------------------------------
3.3.3 U/SART addresses
------------------------------------------------------*/

#define 	USART2_BASE				(AHB1_BUS_BASE + 0x4400)
#define 	USART3_BASE				(AHB1_BUS_BASE + 0x4800)
#define 	UART4_BASE				(AHB1_BUS_BASE + 0x4C00)
#define 	UART5_BASE				(AHB1_BUS_BASE + 0x5000)

/*----------------------------------------------------
3.4 APB2 peripherals addresses
------------------------------------------------------*/

#define 	EXTI_BASE				(APB2_BUS_BASE + 0x3C00)
#define 	SPI1_BASE				(APB2_BUS_BASE + 0x3000)
#define 	SPI4_BASE				(APB2_BUS_BASE + 0x3400)
#define 	SYSCFG_BASE				(APB2_BUS_BASE + 0x3800)
#define 	USART1_BASE				(APB2_BUS_BASE + 0x1000)
#define 	USART6_BASE				(APB2_BUS_BASE + 0x1400)

/*******************************************************************************************
				4. Peripheral registers structures and pointers macros and initializations
********************************************************************************************/
/*----------------------------------------------------
4.1 AHB1 peripherals
------------------------------------------------------*/
/*----------------------------------------------------
4.1.1.1 GPIO - registers
------------------------------------------------------*/

typedef struct
{
	__vo uint32_t MODER;		/*Port MODE register					Address offset: 0x00 */
	__vo uint32_t OTYPER;		/*Output type register					Address offset: 0x04 */
	__vo uint32_t OSPEEDR;		/*Output speed register					Address offset: 0x08 */
	__vo uint32_t PUPDR;		/*Output pull up\down register			Address offset: 0x0C */
	__vo uint32_t IDR;			/*Input data register					Address offset: 0x10 */
	__vo uint32_t ODR;			/*Output data type register				Address offset: 0x14 */
	__vo uint32_t BSRR;			/*Bit set/reset  register				Address offset: 0x18 */
	__vo uint32_t LCKR;			/*Lock configuration register			Address offset: 0x1C */
	__vo uint32_t AFR[2];		/*Alternate functionality Low register	Address offset: 0x20 */
								/*Alternate functionality High register Address offset: 0x24 */
	//uint_32_t AFR[2];			/*Alternate functionality register		Address offset: 0x24 */

}GPIO_RegDef_t;

/*----------------------------------------------------
4.1.1.2 GPIO - CLK Enables\Disable
------------------------------------------------------*/

#define GPIOA_CLK_EN()			(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_CLK_EN()			(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_CLK_EN()			(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_CLK_EN()			(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_CLK_EN()			(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_CLK_EN()			(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_CLK_EN()			(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_CLK_EN()			(RCC->AHB1ENR |= (1 << 7))
#define GPIOI_CLK_EN()			(RCC->AHB1ENR |= (1 << 8))

#define GPIOA_CLK_DI()			(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_CLK_DI()			(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_CLK_DI()			(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_CLK_DI()			(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_CLK_DI()			(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_CLK_DI()			(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_CLK_DI()			(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_CLK_DI()			(RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_CLK_DI()			(RCC->AHB1ENR &= ~(1 << 8))

/*----------------------------------------------------
4.1.1.2 GPIO - Reset GPIO registers
------------------------------------------------------*/
//These macros sets and resets the correspond bit in the GPIO
//reset register.

#define GPIOA_RST()			do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0));}while(0)
#define GPIOB_RST()			do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1));}while(0)
#define GPIOC_RST()			do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2));}while(0)
#define GPIOD_RST()			do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3));}while(0)
#define GPIOE_RST()			do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4));}while(0)
#define GPIOF_RST()			do{ (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5));}while(0)
#define GPIOG_RST()			do{ (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6));}while(0)
#define GPIOH_RST()			do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7));}while(0)
#define GPIOI_RST()			do{ (RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~(1 << 8));}while(0)


/*----------------------------------------------------
4.1.2.1 RCC registers
------------------------------------------------------*/

typedef struct
{
	__vo uint32_t CR;			/*								Address offset: 0x00 */
	__vo uint32_t PLLCFG;		/*								Address offset: 0x04 */
	__vo uint32_t CFGR;			/*								Address offset: 0x08 */
	__vo uint32_t CIR;			/*								Address offset: 0x0C */
	__vo uint32_t AHB1RSTR;		/*								Address offset: 0x10 */
	__vo uint32_t AHB2RSTR;		/*								Address offset: 0x14 */
	__vo uint32_t AHB3RSTR;		/*								Address offset: 0x18 */
	__vo uint32_t RESERVED_0;	/*								Address offset: 0x1C */
	__vo uint32_t APB1RSTR;		/*								Address offset: 0x20 */
	__vo uint32_t APB2RSTR;		/*								Address offset: 0x24 */
	__vo uint32_t RESERVED_1;	/*								Address offset: 0x28 */
	__vo uint32_t RESERVED_2;	/*								Address offset: 0x2C */
	__vo uint32_t AHB1ENR;		/*								Address offset: 0x30 */
	__vo uint32_t AHB2ENR;		/*								Address offset: 0x34 */
	__vo uint32_t AHB3ENR;		/*								Address offset: 0x38 */
	__vo uint32_t RESERVED_3;	/*								Address offset: 0x3C */
	__vo uint32_t APB1ENR;		/*								Address offset: 0x40 */
	__vo uint32_t APB2ENR;		/*								Address offset: 0x44 */
	__vo uint32_t RESERVED_4;	/*								Address offset: 0x48 */
	__vo uint32_t RESERVED_5;	/*								Address offset: 0x4C */
	__vo uint32_t AHB1LPENR;	/*								Address offset: 0x50 */
	__vo uint32_t AHB2LPENR;	/*								Address offset: 0x54 */
	__vo uint32_t AHB3LPENR;	/*								Address offset: 0x58 */
	__vo uint32_t RESERVED_6;	/*								Address offset: 0x5C */
	__vo uint32_t APB1LPENR;	/*								Address offset: 0x60 */
	__vo uint32_t APB2LPENR;	/*								Address offset: 0X64 */
	__vo uint32_t RESERVED_7;	/*								Address offset: 0x68 */
	__vo uint32_t RESERVED_8;	/*								Address offset: 0x6C */
	__vo uint32_t BDCR;			/*								Address offset: 0x70 */
	__vo uint32_t CSR;			/*								Address offset: 0x74 */
	__vo uint32_t RESERVED_9[2];/*							Address offset: 0x78+0x7c */
	__vo uint32_t SSCGR;		/*								Address offset: 0x80 */
	__vo uint32_t PLLI2SCFGR;	/*								Address offset: 0x84 */


}RCC_RegDef_t;

/*----------------------------------------------------
4.2 AHB2 peripherals
------------------------------------------------------*/

/*----------------------------------------------------
4.2.1 SYSCFG registers
------------------------------------------------------*/
typedef struct{

	__vo uint32_t MEMRMP;			/*memory remap register						Address offset: 0x00 */
	__vo uint32_t PMC;				/*peripheral mode configuration register	Address offset: 0x04 */
	__vo uint32_t EXTICR[4];		/*external interrupt configuration 1-4		Address offset: 0x08-0x14 */
	     uint32_t RESERVED1;												  /*Address offset: 0x18 */
	     uint32_t RESERVED2;												  /*Address offset: 0x1c */
	__vo uint32_t CMPCR;			/*Compensation cell control register	Address offset: 0x20 */
		uint32_t RESERVED3;												      /*Address offset: 0x24 */
		uint32_t RESERVED4;												      /*Address offset: 0x28 */
	__vo uint32_t CFGR;

}SYSCFG_RegDef_t;

/*----------------------------------------------------
4.2.2 EXTI registers
------------------------------------------------------*/

typedef struct{

	__vo uint32_t IMR;			/*Interrupt mask register				Address offset: 0x00 */
	__vo uint32_t EMR;			/*Event mask register					Address offset: 0x04 */
	__vo uint32_t RTSR;			/*Rising trigger selection register		Address offset: 0x08 */
	__vo uint32_t FTSR;			/*Falling trigger selection register	Address offset: 0x0C */
	__vo uint32_t SWIER;		/*Software interrupt event register		Address offset: 0x10 */
	__vo uint32_t PR;			/*Pending register					 	Address offset: 0x14 */

}EXTI_RegDef_t;

/*----------------------------------------------------
4.3 APB1 peripherals
------------------------------------------------------*/


/*----------------------------------------------------
4.3.1.1 SPI - Registers structures
------------------------------------------------------*/


typedef struct{

	__vo uint32_t SPI_CR1;			/*SPI control register 1				Address offset: 0x00 */
	__vo uint32_t SPI_CR2;			/*SPI control register 2				Address offset: 0x04 */
	__vo uint32_t SPI_SR;			/*SPI status register 					Address offset: 0x08 */
	__vo uint32_t SPI_DR;			/*SPI data register						Address offset: 0x0C */
	__vo uint32_t SPI_CRCPR;		/*SPI CRC polynomial register			Address offset: 0x10 */
	__vo uint32_t SPI_RXCRCR;		/*SPI RX CRC register Pending register	Address offset: 0x14 */
	__vo uint32_t SPI_TXCRCR;		/*SPI RX CRC register Pending register	Address offset: 0x18 */
	__vo uint32_t SPI_I2SCFGR;		/*SPI_I2S configuration register		Address offset: 0x1C */
	__vo uint32_t SPI_I2SPR;		/*SPI_I2S pending register				Address offset: 0x20 */
}SPI_RegDef_t;




#define 	SPI1					((SPI_RegDef_t*) SPI1_BASE)
#define 	SPI2					((SPI_RegDef_t*) SPI2_BASE)
#define 	SPI3					((SPI_RegDef_t*) SPI3_BASE)
#define 	SPI4					((SPI_RegDef_t*) SPI4_BASE)

/*----------------------------------------------------
4.3.2.1 SPI - CLK Enables\Disable
------------------------------------------------------*/

#define SPI2_CLK_EN()			(RCC->APB1ENR |= (1 << 14))
#define SPI3_CLK_EN()			(RCC->APB1ENR |= (1 << 15))

#define SPI2_CLK_DI()			(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_CLK_DI()			(RCC->APB1ENR &= ~(1 << 15))

/*----------------------------------------------------
4.3.2.2 U\SART - CLK Enables\Disable
------------------------------------------------------*/

#define USART2_CLK_EN()			(RCC->APB1ENR |= (1 << 17))
#define USART3_CLK_EN()			(RCC->APB1ENR |= (1 << 18))
#define UART4_CLK_EN()			(RCC->APB1ENR |= (1 << 19))
#define UART5_CLK_EN()			(RCC->APB1ENR |= (1 << 20))

#define USART2_CLK_DI()			(RCC->APB1ENR &= ~(1 << 17))
#define USART3_CLK_DI()			(RCC->APB1ENR &= ~(1 << 18))
#define UART4_CLK_DI()			(RCC->APB1ENR &= ~(1 << 19))
#define UART5_CLK_DI()			(RCC->APB1ENR &= ~(1 << 20))

/*----------------------------------------------------
4.3.2.3 I2C - CLK Enables\Disable
------------------------------------------------------*/

#define I2C1_CLK_EN()			(RCC->APB1ENR |= (1 << 21))
#define I2C2_CLK_EN()			(RCC->APB1ENR |= (1 << 22))
#define I2C3_CLK_EN()			(RCC->APB1ENR |= (1 << 23))

#define I2C1_CLK_DI()			(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_CLK_DI()			(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_CLK_DI()			(RCC->APB1ENR &= ~(1 << 23))

/*----------------------------------------------------
4.4 APB2 peripherals
------------------------------------------------------*/
/*----------------------------------------------------
4.4.1.1 U\SART - CLK Enables\Disable
------------------------------------------------------*/

#define USART1_CLK_EN()			(RCC->APB2ENR |= (1 << 4))
#define USART6_CLK_EN()			(RCC->APB2ENR |= (1 << 5))

#define USART1_CLK_DI()			(RCC->APB2ENR &= ~(1 << 4))
#define USART6_CLK_DI()			(RCC->APB2ENR &= ~(1 << 5))

/*----------------------------------------------------
4.4.1.2 SPI - CLK Enables\Disable
------------------------------------------------------*/

#define SPI1_CLK_EN()			(RCC->APB2ENR |= (1 << 12))
#define SPI4_CLK_EN()			(RCC->APB2ENR |= (1 << 13))

#define SPI1_CLK_DI()			(RCC->APB2ENR &= ~(1 << 12))
#define SPI4_CLK_DI()			(RCC->APB2ENR &= ~(1 << 13))

/*----------------------------------------------------
4.4.1.3 SYSCFG - CLK Enables\Disable
------------------------------------------------------*/
#define SYSCFG_CLK_EN()			(RCC->APB2ENR |= (1 << 14))
#define SYSCFG_CLK_DI()			(RCC->APB2ENR &= ~(1 << 14))



/*******************************************************************************************
				5. IRQ (RM0090 Rev 17 p376/1747)
********************************************************************************************/

#define EXTI0 			6 					 /*Address 0x0000 0058*/
#define EXTI1 			7 					 /*Address 0x0000 005C*/
#define EXTI2 			8 					 /*Address 0x0000 0060*/
#define EXTI3 			9 					 /*Address 0x0000 0064*/
#define EXTI4 			10 					 /*Address 0x0000 0068*/
#define EXTI9_5 		23 					 /*Address 0x0000 009c*/
#define EXTI10_15 		40 					 /*Address 0x0000 00e0*/



/*=================================================================================================================================================================================
																					ARM CORTEX M4(CPU) side
=================================================================================================================================================================================*/

/******************************************************
				IRQ enable\clear registers
*******************************************************/


#define 	NVIC_ISER0 		((__vo uint32_t*)0xE000E100)
#define 	NVIC_ISER1 		((__vo uint32_t*)0xE000E104)
#define 	NVIC_ISER2 		((__vo uint32_t*)0xE000E108)


#define 	NVIC_ICER0 		((__vo uint32_t*)0xE000E180)
#define 	NVIC_ICER1 		((__vo uint32_t*)0xE000E184)
#define 	NVIC_ICER2 		((__vo uint32_t*)0xE000E188)

/******************************************************
				IRQ priority registers
*******************************************************/

#define 	NVIC_IPR_BASE		((__vo uint32_t*)0xE000E400)








#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"


#endif /* INC_STM32F407XX_H_ */


