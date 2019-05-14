/** @file 
    gpio.h
    
  * @brief description
    APIs to interface GPIO function definitions

  * @author
    Abdulmaguid Eissa

  * @date
    April 22, 2019

  *	@COPYRIGHT NOTICE 
  *
  *
  *
* */


#ifndef GPIO__H
#define GPIO__H

// ************* GPIO_init **************
// brief description: initializing a GPIO.
// inputs:   none
// outputs:  none
// NOTES:
void
GPIO_PF_init(void);

// ************* GPIO_set_bit **************
// brief description: setting a bit in a GPIO.
// inputs:   bit number in hex
// outputs:  none
// NOTES:
void
GPIO_PF_set_bit(uint8_t port_bit);

// ************* GPIO_clear_bit **************
// brief description: clearing a bit in a GPIO.
// inputs:   bit number in hex
// outputs:  none
// NOTES:
void
GPIO_PF_clear_bit(uint8_t port_bit);

// ************* GPIO_toggle_bit **************
// brief description: toggling a bit in a GPIO.
// inputs:   bit number in hex
// outputs:  none
// NOTES:
void
GPIO_PF_toggle_bit(uint8_t port_bit);


#endif  // ************* GPIO__H *************

        // ************* end of file *************
