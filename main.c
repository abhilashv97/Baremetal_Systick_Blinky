#include <stdint.h>


#define LED_PIN 5
volatile int counter = 0;

volatile uint32_t *AHB2ENR = (volatile uint32_t *)(0x40021000 + 0x4c); 
volatile uint32_t *GPIOA_MODER = (volatile uint32_t *)(0x48000000 + 0x00);
volatile uint32_t *GPIOA_ODR = (volatile uint32_t *)(0x48000000 + 0x14);

volatile uint32_t *STK_CTRL = (volatile uint32_t *)(0xE000E010);
volatile uint32_t *STK_LOAD = (volatile uint32_t *)(0xE000E014);
volatile uint32_t *STK_VAL = (volatile uint32_t *)(0xE000E018);
volatile uint32_t *STK_CALIB = (volatile uint32_t *)(0xE000E01C);

void delay(volatile uint32_t count) {
    while(count--) {
        __asm__("nop");
    }
}
 void systick_handler()
 {
      *GPIOA_ODR ^= (1 << LED_PIN); // Turn on LED (assuming active high)
 }

int main(void) {
	
    *AHB2ENR = *AHB2ENR | (0x01 << 0); // TO set only the GPIOA enable bit i.e bit 0.
    
    delay(1000000); // Delay
    
    *GPIOA_MODER = *GPIOA_MODER & (~(0x3 << (LED_PIN * 2))); //Reset the port
    *GPIOA_MODER = *GPIOA_MODER | (0x01 << (LED_PIN * 2)); // Configuring pin 5 "General purpose output mode" 

    *STK_CTRL |= 0x00; 
    *STK_LOAD |= 0x0FFFFF; 
    *STK_CTRL |= 0x07; 

    while(1);

}
