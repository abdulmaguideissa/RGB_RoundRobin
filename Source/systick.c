/*Functions definitions of Systick header file */

/*------------------------------*/
#include <stdint.h>

#include "systick.h"
#include "tm4c123gh6pm.h"

#define SYSTICK_CLK_CORE      (0x00000004)      // clock core 
#define SYSTICK_INT_ARM       (0x00000002)      // interrupt arming
#define SYSTICK_CTRL_EN       (0x00000001)      // systick register enable
#define SYSTICK_TRIGGER       (0x04000000)
#define SYSTICK_PRI7          ((NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0xE0000000)
#define NVIC_ST_INT_CTRL      (*((volatile uint32_t *)0xE000ED04))


//4)----------- system clock -----------
void SysTick_init(uint32_t period){
	NVIC_ST_CTRL_R = 0;              //disable systick during setup
	NVIC_ST_CTRL_R = 0x00000005;     //enable core clock.
	NVIC_ST_RELOAD_R = period - 1;                                         //3) set the reload Reg with coressponding value to 40 Hz
	NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_R & 0x00FFFFFF;                        //4) set the sysTick priority.
	NVIC_ST_CTRL_R = 0x00000007;                                         //5) set counter, interrupt and clock bits
}

// ************** Systick_rtos_init *************
void
Systick_rtos_init(uint32_t system_tick) {
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = SYSTICK_PRI7;
	NVIC_ST_RELOAD_R = system_tick;
	NVIC_ST_CTRL_R = (SYSTICK_INT_ARM | SYSTICK_CLK_CORE | SYSTICK_CTRL_EN);
}

// ************** SysTick_trigger ***************
void 
SysTick_trigger(void) {
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_INT_CTRL = SYSTICK_TRIGGER;
}


// ************** SysTick_wait **************
void SysTick_wait(uint32_t delay){
	NVIC_ST_RELOAD_R = delay - 1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&0x00010000) == 0){
	}  //wait for the count flag to be 0
}

// ************* SysTick_wait_10ms **************
//800000*12.5ns = 10ms 
//12.5ns = 1 / 80*10^6 Hz
void SysTick_wait_10ms(uint32_t delay){
	uint32_t i;
	for(i=0; i < delay; i++){
		SysTick_wait(800000); //wait 10ms
	}
}
