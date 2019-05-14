/** @file 
    main.h
    
  * @brief description
    A header file that contains common used values through project, gathered in one file
	for clarity, maintainability and for a value not to be confused with another value 
	or a definition.
	It also includes the registers values of the used devices/periphrals.
   
  * @author
    Abdulmaguid Eissa.

  * @date
    April 19, 2019

  *	@COPYRIGHT NOTICE
    (2019)
  *
  *
  *
* */


#ifndef MAIN__H
	#define MAIN__H


// *********************************************************
// ************************* GPIO **************************
// *********************************************************
// NOTE: Macros naming convension is according to the GPIO usge.
  // PORTE FOR ADC
#define PORTE_CLOCK_EN          (0x10)
#define PORTE_ANLG_MOD          (0x04)
#define PORTE_DIO_EN            (0x04)
#define PORTE_OUT_DIR           (0x04)
#define PORTE_ADC_SETUP         (0x04)
#define PORTE_CTRL_CLR          (0xFFFF00FF)
#define PORTE_ADC_EN            (0x00003300)
#define PORTE_ADC_OD            (0x08)


  // POTRF FOR LED
#define GPIO_PORTF_PIN1         (0x02)
#define GPIO_PORTF_PIN2         (0x04)
#define GPIO_PORTF_PIN3         (0x08)
#define GPIO_PF_CLK_EN          (0x00000020)
#define GPIO_PF_CTRL_SET        (0x000000F0)




// *********************************************************
// ************************* ADC ***************************
// *********************************************************
// ADC assigned registers values, including ADC periphral
// values and its GPIO values.
#define SYSTEM_CLOCK            (80000000)
#define ADC_MODULE0_EN          (0x00000001)
#define ADC_SS3_HIPRI           (0x0123)
#define ADC_ACTSS_EN            (0x0008)
#define ADC_SW_TRG              (0xF000)
#define ADC_SSMUX3_SIS          (0x000F)
#define ADC_IE0_END0            (0x0006)
#define ADC_SS3_INIT            (0x0008)
#define ADC_SS3_IS              (0x08)
#define ADC_SSIACK3             (0x0008)
#define DATA_BYTE               (0xFF)
#define MAXTRIES                (5)



// *********************************************************
// ************************ LED ****************************
// *********************************************************
#define LED_BLUE                (GPIO_PORTF_PIN1)
#define LED_GREEN               (GPIO_PORTF_PIN2)
#define LED_RED                 (GPIO_PORTF_PIN3)


#endif  // ************* MAIN__H *************

        // ************* end of file *************
