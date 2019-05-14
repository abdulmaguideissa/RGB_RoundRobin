/** @file
    gpio.c
   
  * @brief description
    MCAL
    implementation of the functions that define a GPIO

  * @author
    Abdulmaguid Eissa

  * @date
     April 22, 2019

  *	@COPYRIGHT NOTICE
  *
  *
  *
* */

#include <stdint.h>

#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "port.h"
#include "main.h"



// ************* GPIO_init **************
// PORTF 
void
GPIO_PF_init(void) {
	volatile uint32_t delay;

	GPIO_CLOCK_R   |= GPIO_PF_CLK_EN;
	delay           = GPIO_CLOCK_R;
	GPIO_PF_CTRL_R &= ~GPIO_PF_CTRL_SET;
	GPIO_PF_ALTF_R &= ~GPIO_PORTF_PIN1;
	GPIO_PF_ALGF_R &= ~GPIO_PORTF_PIN1;
	GPIO_PF_DIR_R  |= GPIO_PORTF_PIN1;
	GPIO_PF_DEN_R  |= GPIO_PORTF_PIN1;
}


// ************* GPIO_set_bit **************
void
GPIO_PF_set_bit(uint8_t port_bit) {
	GPIO_PF_DATA_R |= port_bit;
}


// ************* GPIO_clear_bit **************
void
GPIO_PF_clear_bit(uint8_t port_bit) {
	GPIO_PF_DATA_R &= ~port_bit;
}


// ************* GPIO_toggle_bit **************
void
GPIO_PF_toggle_bit(uint8_t port_bit) {
	GPIO_PF_DATA_R ^= port_bit;
}



// ************* end of file *************
