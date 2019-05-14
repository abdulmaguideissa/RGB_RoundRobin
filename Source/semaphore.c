/** @file
    semaphore.c
   
  * @brief description
    implementation of semaphore APIs 
	semaphore initialization
	semaphore signal 
	semaphore wait
  
  * @author
    Abdulmaguid Eissa
  
  * @date
    May 14, 2019
  
  *	@COPYRIGHT NOTICE
    (2019) AE
  *
  *
  *
* */

#include <stdint.h>

#include "rtos.h"

// External functions
void EnableInterrupts(void);
void DisableInterrupts(void);

// ************* RTOS_semaphore_init **************
void
RTOS_semaphore_init(int32_t *semaPtr, int8_t value) {
	DisableInterrupts();
	*semaPtr = value;
	EnableInterrupts();
}

// ************* RTOS_semaphore_wait **************
// Pending resource
void
RTOS_semaphore_wait(int32_t *semaPtr) {
	DisableInterrupts();
	(*semaPtr)--;

	if ((*semaPtr) < 0) {
		runPtr->blocked = semaPtr;
		EnableInterrupts();
		RTOS_thread_suspend();
	}
	EnableInterrupts();
}

// ************* RTOS_semaphore_signal **************
// Posting resource
void
RTOS_semaphore_signal(int32_t * semaPtr) {
	tcb_t * ptr;

	DisableInterrupts();
	(*semaPtr++);

	if ((*semaPtr) < 0) {            
		ptr = runPtr->next_thread;
		while (ptr->blocked != semaPtr) {   // thread still blocked
			ptr = ptr->next_thread;
		}
		*(ptr->blocked) = 0;  // Wakeup this thread
	}
	EnableInterrupts();
}


// ************* end of file *************
