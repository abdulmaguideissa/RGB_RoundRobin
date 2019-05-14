;/*****************************************************************************/
; OSasm.s: low-level OS commands, written in assembly                       */
; Runs on LM4F120/TM4C123/MSP432
; Lab 4 starter file
; March 25, 2016

;


        AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8

        EXTERN  runPtr            ; currently running thread
        EXPORT  RTOS_start
        EXPORT  SysTick_Handler
        IMPORT  RTOS_scheduler

	; ****** OS CONTEXT SWITCHER *******
SysTick_Handler                ; 1) Saves R0-R3, R12, LR, PC, PSR automatically (by CPU)
    CPSID   I                  ; 2) Prevent interrupt during switching
	PUSH    {R4-R11}           ; 3) Save remaining registers manually (by user)
    LDR     R0, =runPtr        ; 4) R0 = runPtr, pointer to old thread 
	LDR     R1, [R0]           ;    R1 = runPtr
	STR     SP, [R1]           ; 5) Save SP into TCB
	PUSH    {R0, LR}
	BL      RTOS_scheduler     ; Branch to Scheduler written in c
	POP     {R0, LR}           ; 
	LDR     R1, [R0]           ; 6) R1 = runPtr, new thread
	LDR     SP, [R1]		   ; 7) new thread SP; SP = runPtr->sp;
	POP     {R4-R11}		   ; 8) restore regs r4-11
    CPSIE   I                  ; 9) tasks run with interrupts enabled
    BX      LR                 ; 10) restore R0-R3, R12, LR, PC, PSR

	 ; ****** OS DISPATCHER *******
RTOS_start                      
    CPSID   I                  ; 1) DISABLE interrupts
	LDR  	R0, =runPtr        ; currently running thread
	LDR     R2, [R0]		   ; R2 = value of runPtr
	LDR     SP, [R2]		   ; new thread SP; SP = runPtr->stackPointer
	POP     {R4-R11}		   ; restore regs r4-11
	POP     {R0-R3}			   ; restore regs r0-3
	POP     {R12}
	ADD     SP, SP, #4		   ; discard LR from initial stack
	POP     {LR}			   ; start location
	ADD     SP, SP, #4		   ; discard PSR
    CPSIE   I                  ; Enable interrupts at processor level
    BX      LR                 ; start first thread 

    ALIGN
    END
