#include "stm32f407xx.h"

#define US 1000
#define MS 1000*US
int ext_timeout = MS;

volatile uint8_t button_pressed = 0;
volatile uint32_t last_interrupt_time = 0;
// A crude estimate loop counter variable if you don't have a millisecond timer set up yet:
volatile uint32_t software_millis = 0;

void delay1(int timeout)
{
    for(int i = 0 ; i < timeout ; i ++);
}

// FIX: Changed parameters to pointers (GPIO_Handle_t*)
void gpio_driver_function1(GPIO_Handle_t *green_led, GPIO_Handle_t *orange_led, GPIO_Handle_t *red_led, GPIO_Handle_t *blue_led)
{
    // FIX: Removed the '&' because green_led, orange_led, etc. are already pointers now
    gpio_configure_pin(green_led, GPIOD, 12, GPIO_MODE_OUT, GPIO_SPEED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 0);
    gpio_init(green_led);

    gpio_configure_pin(orange_led, GPIOD, 13, GPIO_MODE_OUT, GPIO_SPEED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 0);
    gpio_init(orange_led);

    gpio_configure_pin(red_led, GPIOD, 14, GPIO_MODE_OUT, GPIO_SPEED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 0);
    gpio_init(red_led);

    gpio_configure_pin(blue_led, GPIOD, 15, GPIO_MODE_OUT, GPIO_SPEED_LOW, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 0);
    gpio_init(blue_led);
}



int main(void)
{
	TMR6_CLK_EN();
	TMR6->TIMx_PSC = 41999;
	TMR6->TIMx_ARR = 1999;
	TMR6->TIMx_DIER |= (1 << 0);
	*NVIC_ISER1 |= (1 << 22);
	GPIO_Handle_t green_led, orange_led, red_led, blue_led;
	gpio_driver_function1(&green_led, &orange_led, &red_led, &blue_led);

//	GPIO_Handle_t green_led, orange_led, red_led, blue_led, irq_pin;

    // FIX: Pass the addresses (&) of the handles into the function
//    gpio_driver_function1(&green_led, &orange_led, &red_led, &blue_led);

    // This part is correct because you are explicitly passing the address here
//    gpio_configure_pin(&irq_pin, GPIOA, 0, GPIO_MODE_IRQ_RT, GPIO_SPEED_FAST, GPIO_OUT_MODE_PP, GPIO_DIS_PUPD, 0);
//    gpio_init(&irq_pin);

//    gpio_irq_set(EXTI0);
//    gpio_irq_priority(EXTI0, 15);
	TMR6->TIMx_CR1 |= (1 << 0);
    while(1)
    {
//        gpio_toggle_pin(GPIOD, 12);
//        delay1(ext_timeout);
//        gpio_toggle_pin(GPIOD, 13);
//        delay1(ext_timeout);
//        gpio_toggle_pin(GPIOD, 14);
//        delay1(ext_timeout);
//        gpio_toggle_pin(GPIOD, 15);
//        delay1(ext_timeout);
    }

    return 0;
}

//void EXTI0_IRQHandler(void)
//{
//    // 1. Clear the pending register flag in hardware
//    gpio_irq_handler(0); // Pin 0
//    if (ext_timeout < 10000)
//    {
//    	ext_timeout = MS;
//    }
//    else
//    {
//    	ext_timeout = ext_timeout/2;
//    }
//
//}

void TIM6_DAC_IRQHandler(void) {

    // 1. Check if the Update Interrupt Flag (UIF) is set in the Status Register (SR)
    if (TMR6->TIMx_SR & (1 << 0)) {

        // 2. Clear the UIF flag by writing 0 to bit 0
        TMR6->TIMx_SR &= ~(1 << 0);

        gpio_toggle_pin(GPIOD, 12);
    }
}
