#include "stm32f407xx.h"


void prepare_gpio(GPIO_Handle_t *green_led, GPIO_Handle_t *orange_led, GPIO_Handle_t *red_led, GPIO_Handle_t *blue_led)
{
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
/*
 * Define the pre-scaler to 42000, and ARR to 2000 such that for 16M CLK TIM6 will interrupt
 * (42K*2K)/16M = 5.25[s]
 * */
{
	TMR6_CLK_EN();
	TMR6->TIMx_PSC = 41999;
	TMR6->TIMx_ARR = 1999;
	TMR6->TIMx_DIER |= (1 << 0);
	*NVIC_ISER1 |= (1 << 22);
	TMR6->TIMx_CR1 |= (1 << 0);

	GPIO_Handle_t green_led, orange_led, red_led, blue_led;
	prepare_gpio(&green_led, &orange_led, &red_led, &blue_led);

    while(1)
    {

    }

    return 0;
}


void TIM6_DAC_IRQHandler(void) {

    // 1. Check if the Update Interrupt Flag (UIF) is set in the Status Register (SR)
    if (TMR6->TIMx_SR & (1 << 0)) {

        // 2. Clear the UIF flag by writing 0 to bit 0
        TMR6->TIMx_SR &= ~(1 << 0);

        gpio_toggle_pin(GPIOD, 12);
        gpio_toggle_pin(GPIOD, 13);
        gpio_toggle_pin(GPIOD, 14);
        gpio_toggle_pin(GPIOD, 15);
    }
}
