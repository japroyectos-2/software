/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-01-24, 14:21, # CodeGen: 0
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
#include "TI1.h"
#include "AS1.h"
#include "AD1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/* PARA ENVIAR UN BLOQUE POR SERIAL

unsigned int Enviados = 8;

typedef union{
	unsigned char u8[8];
	unsigned int u16;
}AMPLITUD;

volatile AMPLITUD bloque; 

*/


//	PARA EL POTENCIOMETRO

unsigned int envioS = 2;
unsigned int envioP = 5;
 
typedef union{
	unsigned char u8[3];
	unsigned int u16;
}AMPLITUD1;

volatile AMPLITUD1 ADC1, ADC2, Aux; 

unsigned char env[5];

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  dato = esperar;
  	//  dato = enviar;                          // PARA ENVIAR UN CARACTER O UN BLOQUE POR SERIAL
  	/* PARA ENVIAR UN BLOQUE POR SERIAL
  	bloque.u8[0]=0x4A;
  	bloque.u8[1]=0x65;
  	bloque.u8[2]=0x63;
  	bloque.u8[3]=0x6B;
  	bloque.u8[4]=0x73;
  	bloque.u8[5]=0x6F;  
  	bloque.u8[6]=0x6E;
  	bloque.u8[7]=0x20; */
  
  for(;;){
	  
	  //   	PARA EL POTENCIOMETRO 	  
	  		switch (dato){
	  		    		
	  			case esperar:
	  				break;
	  		    			
	  		  	case medir:
	  		  		AD1_Measure(TRUE);
	  		  		AD1_GetValue16(&Aux.u16);
	  		  		Aux.u16 = Aux.u16 >> 4;
	  		  		ADC1.u16 = Aux.u16 & 0x7F;
	  		  		ADC2.u16 = Aux.u16 >> 7;
	  		  		ADC2.u16 = ADC2.u16 & 0x1F;
	  		  		env[0] = 0xF2;
	  		  		env[1] = ADC2.u16;
	  		  		env[2] = ADC1.u16;
	  		  		/*env[3] = 0x00;
	  		  		env[4] = 0x00;*/
	  		  		dato = enviar;

	  		  	case enviar:
	  		  		//AS1_SendBlock(&Aux.u8,2,&envioS);   // Mandar valor sin protocolo
	  		  		AS1_SendBlock(&env,3,&envioP);    // Mandar valor con protocolo
	  		  		dato = esperar;
	  		  		  
	  		  	default:
	  		  		break;
	  		    	
	  		}  
	  		  
	  /* PARA ENVIAR UN CARACTER Y UN BLOQUE POR SERIAL
	  		switch (dato) {
	  			case enviar:
	  		    	//AS1_SendChar(0x42);       // PARA ENVIAR UN CARACTER POR SERIAL
	  		  		AS1_SendBlock(&bloque.u8,8,&Enviados);  // PARA ENVIAR UN BLOQUE POR SERIAL
	  		  		dato=esperar;
	  		  		  
	  		case esperar:
	  		  	break;

	  		}*/
	  
  }
  
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
