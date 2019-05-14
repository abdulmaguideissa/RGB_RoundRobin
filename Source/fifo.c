/** @file
    fifo.c
 
  * @brief description
    implementation of FIFO prototypes in rtos.h APIs.
	event thread based implementaion, lost data will be flagged and skipped

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

#define FIFO_SIZE     (100)


uint8_t static  put_index;
uint8_t static  get_index;
uint32_t static fifo[FIFO_SIZE];
int8_t static   current_size_sema;   // fifo size semaphore
uint32_t static lost_data;           // to be checked for data losses counts

// ************* RTOS_fifo_init **************
void
RTOS_fifo_init(void) {
	put_index = 0;
	get_index = 0;
	RTOS_semaphore_init(&current_size_sema, EMPTY);
	lost_data = NONE;
}

// ************* RTOS_fifo_put **************
int8_t
RTOS_fifo_put(uint32_t fifo_data) {
	if (current_size_sema == FIFO_SIZE) {
		lost_data++;
		return (ERR_FULL);
	}
	else {
		fifo[put_index] = fifo_data;
		put_index = (put_index + 1) % FIFO_SIZE;
		RTOS_semaphore_signal(&current_size_sema);
		return (NOT_FULL);
	}
}

// ************* RTOS_fifo_get **************
uint32_t
RTOS_fifo_get(void) {
	uint32_t fifo_data;

	RTOS_semaphore_wait(&current_size_sema);
	fifo_data = fifo[get_index];
	get_index = (get_index + 1) % FIFO_SIZE;
	return (fifo_data);
}





// ************* end of file *************
