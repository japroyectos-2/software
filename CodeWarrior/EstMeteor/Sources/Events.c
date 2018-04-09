/* ###################################################################
**     Filename    : Events.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-04-07, 16:05, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
int countPWM = 0, countT1 = 0, countTime1 = 0, countTime2 = 0, signal = 0;
int pwm1Error, pwm2Error, pwm3Error, pwm4Error;

//volatile AMPLITUD1 ADC1, ADC2, Aux, time2, time1, timeAux1, timeAux2; 

/*
** ===================================================================
**     Event       :  TI2_OnInterrupt (module Events)
**
**     Component   :  TI2 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI2_OnInterrupt(void)
{
  /* Write your code here ... */
	countPWM++;
		
	if(countPWM==1){
		pwm1Error = PWM1_Enable(); 
		pwm3Error = PWM3_Enable();
	}
	if(countPWM==2){
		pwm1Error = PWM1_Disable();
		pwm3Error = PWM3_Disable();
		signal = 1;
		//Cap1_Enable();
		//Cap1_GetCaptureValue(&timeAux1.u16);
		//Cap1_Reset();
		//if(timeAux1.u16 != 0){
		//if((timeAux1 > 1200) && (timeAux1 < 1800)){
		//	time1.u16 = timeAux1.u16;
		//}
	}
	if(countPWM==10){
		//Cap1_Disable();
		pwm2Error = PWM2_Enable();
		pwm4Error = PWM4_Enable();
	}
	if(countPWM==11){
		pwm2Error = PWM2_Disable();
		pwm4Error = PWM4_Disable();
		signal = 2;
		//Cap2_Enable();
		//Cap2_GetCaptureValue(&timeAux2.u16);
		//Cap2_Reset();
		//if(timeAux2.u16 != 0){
		//if((timeAux2 > 1200) && (timeAux2 < 1800)){
		//	time2.u16 = timeAux2.u16;
		//}
	}
	if(countPWM==18){
		//Cap2_Disable();
		countPWM = 0;
	}	
}

/*
** ===================================================================
**     Event       :  AS1_OnError (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnRxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnTxChar (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnFullRxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnFullRxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AS1_OnFreeTxBuf (module Events)
**
**     Component   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after the last character in output
**         buffer is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void  AS1_OnFreeTxBuf(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1_OnInterrupt(void)
{
  /* Write your code here ... */
	countT1++;
	
	if(signal == 1){
		countTime1++;
		if(!Bit1_GetVal()){
			time1.u16 = countTime1;
			countTime1 = 0;
			signal = 0;
		}
	}
	if(signal == 2){
		countTime2++;
		if(!Bit2_GetVal()){
			time2.u16 = countTime2;
			countTime2 = 0;
			signal = 0;
		}
	}
	if(countT1 == 50){
		if(dato==esperar){
			dato=medir;
			countT1 = 0;
		} 		
	}
}

/* END Events */

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
