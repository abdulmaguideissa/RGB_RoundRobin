/** @file
    rtos.c
    
 
  * @brief description
    OS serivce layer implementation

  * @author
    Abdulmaguid Eissa

  * @date
    May 9, 2019
  
  *	@COPYRIGHT NOTICE
  *
  *
  *
* */

#include <stdint.h>

#include "rtos.h"
#include "pll.h"
#include "systick.h"

// External functions
void EnableInterrupts(void);
void DisableInterrupts(void);
void RTOS_start(void);
int32_t StartCritical(void);
void EndCritical(int32_t status);

// data types declarations
tcb_t * runPtr = NULL;

// macro definitions
#define NUMTHREADS       (3)                 // maximum number of threads
#define STACKSIZE        (100)                // number of 32-bit words in stack per thread
#define T_BIT            (0x01000000)         // thumb bit in Process Stack Pointer PSR
#define R14              (0x14141414)         // for debugging
#define R12              (0x12121212)
#define R11              (0x11111111)
#define R10              (0x10101010)
#define R9               (0x09090909)
#define R8               (0x08080808)
#define R7               (0x07070707)
#define R6               (0x06060606)
#define R5               (0x05050505)
#define R4               (0x04040404)
#define R3               (0x03030303)
#define R2               (0x02020202)
#define R1               (0x01010101)
#define R0               (0x00000000)


// static data declarations
tcb_t static    tcbs[NUMTHREADS];
uint32_t static stacks[NUMTHREADS][STACKSIZE];


// private functions declarations 
// ************* Set_initial_stack **************
// inputs:  stack index to be initialized
// outputs: none
void static
Set_initial_stack(uint8_t stack_index);

// ************* RTOS_init **************
void
RTOS_init(void) {
	uint8_t thread;

	DisableInterrupts();
	PLL_Init();

	for (thread = THREAD0; thread < NUMTHREADS; thread++) {
		tcbs[thread].sp          = NULL;
		tcbs[thread].blocked     = NULL;
		tcbs[thread].sleep       = 0;
		tcbs[thread].next_thread = NULL;
	}
}


// ************* RTOS_add_threads_3 **************
void
RTOS_add_threads_3(void(*thread0)(void),
	void(*thread1)(void),
	void(*thread2)(void)) 
{
	int32_t status;
	uint8_t thread;

	status = StartCritical();
	tcbs[THREAD0].next_thread = &tcbs[THREAD1];   // linking tasks circularly 
	tcbs[THREAD1].next_thread = &tcbs[THREAD2];
	tcbs[THREAD2].next_thread = &tcbs[THREAD0];

	for (thread = THREAD0; thread < NUMTHREADS; thread++) {
		Set_initial_stack(thread);
	}

	stacks[THREAD0][STACKSIZE - 2] = (int32_t)(thread0);   // PC of each threads points to its function/task
	stacks[THREAD1][STACKSIZE - 2] = (int32_t)(thread1);
	stacks[THREAD2][STACKSIZE - 2] = (int32_t)(thread2);

	runPtr = &tcbs[THREAD0];  // initial task to be ran.
	EndCritical(status);
}


// ************* RTOS_launch **************
// OS dispatcher
void
RTOS_launch(uint32_t system_tick) {
	Systick_rtos_init(system_tick);
	RTOS_start();
}


// ************* RTOS_scheduler **************
// OS scheduler
// Round Robin algortihm based scheduler.
void
RTOS_scheduler(void) {
	tcb_t * tPtr = runPtr;
	do
	{
		tPtr = tPtr->next_thread;
	} while (tPtr != runPtr &&
		     tPtr->blocked == 0 &&
			 tPtr->sleep == 0);
	//runPtr = runPtr->next_thread;
}


// ************* RTOS_thread_suspend **************
// triggering the SysTick to switch for the next thread,
// suspending the current thread from running further time.
void
RTOS_thread_suspend(void) {
	SysTick_trigger();
}


// ************* RTOS_thread_sleep **************
void
RTOS_thread_sleep(uint8_t sleep_time) {
	runPtr->sleep = sleep_time;
	RTOS_thread_suspend();
}


// private functions definitions
// ************* Set_initial_stack **************
void static
Set_initial_stack(uint8_t stack_index) {
	tcbs[stack_index].sp = &stacks[stack_index][STACKSIZE - 16];   // set SP of each thread to its position in stacks

	stacks[stack_index][STACKSIZE - 1]  = T_BIT;
	stacks[stack_index][STACKSIZE - 3]  = R14;
	stacks[stack_index][STACKSIZE - 4]  = R12;
	stacks[stack_index][STACKSIZE - 5]  = R3;
	stacks[stack_index][STACKSIZE - 6]  = R2;
	stacks[stack_index][STACKSIZE - 7]  = R1;
	stacks[stack_index][STACKSIZE - 8]  = R0;
	stacks[stack_index][STACKSIZE - 9]  = R11;
	stacks[stack_index][STACKSIZE - 10] = R10;
	stacks[stack_index][STACKSIZE - 11] = R9;
	stacks[stack_index][STACKSIZE - 12] = R8;
	stacks[stack_index][STACKSIZE - 13] = R7;
	stacks[stack_index][STACKSIZE - 14] = R6;
	stacks[stack_index][STACKSIZE - 15] = R5;
	stacks[stack_index][STACKSIZE - 16] = R4;
}







// ************* end of file *************
