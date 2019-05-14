/** @file 
    rtos.h
    
  * @brief description
    OS serivce abstraction layer (APIs). 
    providing an abstraction layer to access the RTOS functions and 
	threads block control
	RTOS specific functions prototypes.
	Semaphores prototypes.
	FIFO prototypes.
	Implementation of each of these declarations lies in separate source file.

  * @author
    Abdulmaguid Eissa

  * @date
    May 9, 2019

  *	@COPYRIGHT NOTICE 
    (2019) AE
  *
  *
* */


#ifndef RTOS_H
#define RTOS_H


// ************ Thread Block Control type definition ************ 
// contains:
//	stack pointer field
//	blocked thread field
//  sleep thread field
//  linked field for the next thread
typedef struct tcb {
	uint32_t * sp;                      // Stack pointer
	int32_t  * blocked;
	uint32_t   sleep;
	struct tcb * next_thread;           
}tcb_t;
extern tcb_t * runPtr;

// ************* Enumeration for threads **************
// contains decriptive numbers for the running threads, which 
// in this case are three threads
typedef enum threads {
	THREAD0,
	THREAD1,
	THREAD2
}thread_t;

// ************* Enumeration for FIFO **************
typedef enum fifo_status {
	EMPTY,
	NONE = 0,
	NOT_FULL = 0,
	ERR_FULL = -1
}fifo_status_t;

// ************* Enumeration for semaphore **************
typedef enum mutex_status {
	BUSY,
	AVIALABLE
}sema_status_t;

// ************* RTOS_init **************
// brief description:  initialization of the RTOS 
// inputs:           none
// outputs:          none
// NOTES:  depends on the hardware architecture which run on.
//         remember to initialize the system clock source to the fastest mode.
void
RTOS_init(void);


// ************* RTOS_add_threads_3 **************
// brief description:  inserting 3 three threads to be executed concurrently.
// inputs:   three function pointers to three threads
// outputs:  none
// NOTES:    each threads should be void return and void inputs.
void
RTOS_add_threads_3(void(*thread0)(void), 
	               void(*thread1)(void),
				   void(*thread2)(void));

// ************* RTOS_launch **************
// brief description:  RTOS dispatcher
// inputs:   time slice for tasks/clocks to be loaded to SysTick. 
// outputs:  none
// NOTES:
void
RTOS_launch(uint32_t system_tick);

// ************* RTOS_scheduler **************
// brief description:  RTOS scheduler algorithm to run tasks
// inputs:    none
// outputs:   none
// NOTES:    look at all threads in TCB and run the non-sleeping
//           and non-blocked threads.
void
RTOS_scheduler(void);

// ************* RTOS_thread_suspend **************
// brief description:  RTOS suspend thread cooperatively.
// inputs:  none. 
// outputs: none.
// NOTES:   called by as assigned thread when it is blocked for resource.
void
RTOS_thread_suspend(void);

// ************* RTOS_thread_sleep **************
// brief description:  RTOS sleep thread.
// inputs:  sleep time. 
// outputs: none.
// NOTES:   placing thread into dormant state.
//          call thread suspend function after putting 
//          a thread into sleep.
void
RTOS_thread_sleep(uint8_t sleep_time);

// ************* RTOS_semaphore_init **************
// brief description:  RTOS semaphore initialization.
// inputs:  pointer to semaphore,
//          value of semaphore
// outputs: none.
// NOTES:  implementaion follows nonbinary semaphore.   
//         block thread if its value less than 0.
void
RTOS_semaphore_init(int32_t *semaPtr, int8_t value);

// ************* RTOS_semaphore_wait **************
// brief description:  RTOS semaphore wait (pend) thread.
// inputs:  pointer to semaphore.
// outputs: none.
// NOTES:  implementaion follows nonbinary semaphore. 
//         block thread if its value less than 0.
void
RTOS_semaphore_wait(int32_t *semaPtr);

// ************* RTOS_semaphore_signal **************
// brief description:  RTOS semaphore signal (post) thread.
// inputs:  pointer to semaphore.
// outputs: none.
// NOTES:  implementaion follows nonbinary semaphore. 
//         wakeup blocked thread if appropriate.
void
RTOS_semaphore_signal(int32_t * semaPtr);

// ************* RTOS_fifo_init **************
// brief description:  appending new value to FIFO buffer.
// inputs:  none.
// outputs: none.
// NOTES:   implemenation follows event trigger tasks, data will be 
//          lost if not consumed synchronously.
void
RTOS_fifo_init(void);

// ************* RTOS_fifo_put **************
// brief description:  appending new value to FIFO buffer.
// inputs:  pointer to data to be appended.
// outputs: 0 if successful data retrieving, -1 if not.
// NOTES:   implemenation follows event trigger tasks, data will be 
//          lost if not consumed synchronously.
int8_t
RTOS_fifo_put(uint32_t fifoData);

// ************* RTOS_fifo_get **************
// brief description:  appending new value to FIFO buffer.
// inputs:  none
// outputs: data to be retrieved..
// NOTES:  
uint32_t 
RTOS_fifo_get(void);

#endif  // ************* RTOS_H *************

        // ************* end of file *************
