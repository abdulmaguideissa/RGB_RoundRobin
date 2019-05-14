/** @file
    ledtasks.c
    
 
  * @brief description
    HAL
    implementation of LED OS tasks using the MCAL of PORTF GPIO.
  
  * @author
    Abdulmaguid Eissa
  
  * @date
    May 4, 2019

  *	@COPYRIGHT NOTICE
  *
  *
  *
* */



#include "ledtasks.h"
#include "main.h"
#include "gpio.h"


// ************* LED_green_set_task **************
void
LED_green_set_task(void) {
	for (;;) {
		GPIO_PF_set_bit(LED_GREEN);
		GPIO_PF_clear_bit(LED_BLUE | LED_RED);
	}
}



// ************* LED_blue_set_task **************
void
LED_blue_set_task(void) {
	for (;;) {
		GPIO_PF_set_bit(LED_BLUE);
		GPIO_PF_clear_bit(LED_GREEN | LED_RED);
	}
}



// ************* LED_red_set_task **************
void
LED_red_set_task(void) {
	for (;;) {
		GPIO_PF_set_bit(LED_RED);
		GPIO_PF_clear_bit(LED_BLUE | LED_GREEN);
	}
}

// ************* end of file *************
