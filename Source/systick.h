/*SysTick.h
 *Header file for the system clock to initiate a proper and precise time delay.
 *7/3/2017
 *Author: Abdulmaguid
*/
/*-----------------------------------*/
#ifndef __SysTick_H__
#define __SysTick_H__


//1)initialization. 
void SysTick_init(uint32_t period);

// rtos specific intializations
void
Systick_rtos_init(uint32_t system_tick);

// systick triggering for rtos thread suspending
void
SysTick_trigger(void);

//2)Loading the reload register by proper count value
void SysTick_wait_10ms(uint32_t delay);


//3)Create the required delay
void SysTick_wait(uint32_t delay);




#endif
