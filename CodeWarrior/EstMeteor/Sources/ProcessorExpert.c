/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-04-07, 16:05, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AS1.h"
#include "TI2.h"
#include "PWM1.h"
#include "PWM3.h"
#include "PWM2.h"
#include "PWM4.h"
#include "Bit1.h"
#include "Bit2.h"
#include "FC1.h"
#include "Bit3.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

//unsigned int envioS = 2;
unsigned int envioP = 5;
 
typedef union{
	unsigned char u8[3];
	unsigned int u16;
}AMPLITUD1;

volatile AMPLITUD1 ADC1, ADC2, ADC3, ADC4; 
//volatile AMPLITUD2 time1, time2, timeAux1, timeAux2;
unsigned int time1, time2, timea, timeb, timeAux, echo1=0, echo2=0;

unsigned char env[5];

//int time1 = 0, time2 = 0, timeAux1 = 0, timeAux2 = 0;

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  dato = esperar;
  
  for(;;){
	  
	  switch (dato){
	    	  		    		
	  	  case esperar:
	  		  break;
	  		  
	  	  case ultrasonido1:
	  		do{
	  			  		  while(echo1 == 0){
	  			  			  echo1 = Bit1_GetVal();
	  			  		  }
	  			  		  FC1_GetCounterValue(&timea);
	  			  		  while(echo1 == 1){
	  			  			  echo1 = Bit1_GetVal();
	  			  		  }
	  			  		  FC1_GetCounterValue(&timeb);
	  			  		  }while((timeb-timea)<100);
	  			  		  time1=timea;
	  			  		  Bit3_NegVal();
	  		 /* while(echo1 == 0){
	  			  echo1 = Bit1_GetVal();
	  		  }*/
	  		  echo1 = 0;
	  		  //FC1_GetCounterValue(&time1);
	  		  FC1_Disable();
	  		  FC1_Reset();
	  		  dato = esperar;
	  		  
	  	  case ultrasonido2:
	  		  do{
	  		  while(echo2 == 0){
	  			  echo2 = Bit2_GetVal();
	  		  }
	  		  FC1_GetCounterValue(&timea);
	  		  while(echo2 == 1){
	  			  echo2 = Bit2_GetVal();
	  		  }
	  		  FC1_GetCounterValue(&timeb);
	  		  }while((timeb-timea)<100);
	  		  time2=timea;
	  		  
	  		  echo2 = 0;
	  		  //FC1_GetCounterValue(&time2);
	  		  FC1_Disable();
	  		  FC1_Reset();
	  		  dato = esperar;
	  		
	  	  case medir:
	    	    		
	  		  //time1 = time1 >> 4;
	  		  /*ADC1.u16 = time1; //& 0x7F;
	  		  ADC2.u16 = time1 >> 7;
	  		  ADC2.u16 = ADC2.u16 & 0x1F;*/
	  		  
	  		  ADC1.u16 = time1&0x00FF;
	  		  ADC2.u16 = time1 >> 8;
	  		  ADC2.u16 = ADC2.u16 & 0x00FF;
	  		  ADC3.u16 = time2&0x00FF;
	   		  ADC4.u16 = time2 >> 8;
	   		  ADC4.u16 = ADC4.u16 & 0x00FF;
	  			    	  
	      	  /*time2 = time2 >> 4;
	      	  ADC3.u16 = time2 & 0x7F;
	      	  ADC4.u16 = time2 >> 7;
	      	  ADC4.u16 = ADC4.u16 & 0x1F;*/
	  			    	  
	  	   	  /*AD1_Measure(TRUE);
	  	  	  AD1_GetValue16(&Aux.u16);
	  	   	  Aux.u16 = Aux.u16 >> 4;
	  	   	  ADC5.u16 = Aux.u16 & 0x7F;
	  		  ADC6.u16 = Aux.u16 >> 7;
	  	 	  ADC6.u16 = ADC6.u16 & 0x1F;*/
	  			    	  
	  	   	  env[0] = 0xF2;
	      	  env[1] = ADC2.u16;
	  		  env[2] = ADC1.u16;
	  	   	  env[3] = ADC4.u16;
	      	  env[4] = ADC3.u16;
	  		  /*env[5] = ADC6.u16;
	  		  env[6] = ADC5.u16;*/
	    	  //AS1_SendBlock(&Aux.u8,2,&envioS);   // Mandar valor sin protocolo
	    	  AS1_SendBlock(&env,5,&envioP);    // Mandar valor con protocolo
	    	  dato = esperar;
	    	  
	    	  		  		  
	      default:
	    	  break;
	    	  		    	
	  }  
	  
  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
