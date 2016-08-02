
/* 
 * Blinky: Switch the MCU to high(ish) speed and blink the LED attached 
 * to port B, bit 3
*/


#include "stm32l011.h"

void delay(int);

void delay(int dly)
{
  while( dly--);
}

void initClockPLL()
{
    // Use the PLL as a clock source - HSI16 = PLL input clock
// This is potentially a dangerous function as it could
// result in a system with an invalid clock signal - result: a stuck system
        // Set the PLL up
        // First ensure PLL is disabled
        RCC_CR &= ~BIT24;
        RCC_CR |= BIT0; // turn on HSI16 (16MHz clock)
        while ((RCC_CR & BIT2)==0); // wait for HSI to be ready
        // now set up the PLL
        // Assuming a 16MHz input want to achieve a 32MHz core clock
        // Must divide by two at least then multiply back up by 4
        RCC_CFGR &=~(BIT23+BIT21+BIT20+BIT19);
        RCC_CFGR |= (BIT23+BIT22+BIT18);
        // and turn the PLL back on again
        RCC_CR |= BIT24;     
        while ((RCC_CR & BIT25)==0); // wait for PLL to be ready
        // set PLL as system clock source 
        RCC_CFGR |= BIT0+BIT1;
}
void initClockHSI16()
{
    // Use the HSI16 clock as the system clock - allows operation down to 1.5V
        RCC_CR &= ~BIT24;
        RCC_CR |= BIT0; // turn on HSI16 (16MHz clock)
        while ((RCC_CR & BIT2)==0); // wait for HSI to be ready
        // set HSI16 as system clock source 
        RCC_CFGR |= BIT0;
}
void configPins()
{
	// Enable PORTB where LED is connected
	RCC_IOPENR |= BIT1;
	GPIOB_MODER |= BIT6; // make bit3  an output
	GPIOB_MODER &= ~BIT7; // make bit3  an output
}	

int main()
{
	initClockHSI16();
	configPins(); 
	
	while(1)
	{
		GPIOB_ODR |= BIT3;
		delay(200000);
		GPIOB_ODR &= ~BIT3;
		delay(200000);
	} 
	return 0;
}








