/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Cap2.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Component   : Capture
**     Version     : Component 02.223, Driver 01.30, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-04-09, 12:35, # CodeGen: 21
**     Abstract    :
**         This component "Capture" simply implements the capture function
**         of timer. The counter counts the same way as in free run mode. On
**         the selected edge of the input signal (on the input pin), the current
**         content of the counter register is written into the capture
**         register and the OnCapture event is called.
**     Settings    :
**             Timer capture encapsulation : Capture
**
**         Timer
**             Timer                   : TPM1
**             Counter shared          : Yes
**
**         High speed mode
**             Prescaler               : divide-by-16
**           Maximal time for capture register
**             Xtal ticks              : 2048
**             microseconds            : 62500
**             milliseconds            : 62
**             seconds (real)          : 0.0625
**             Hz                      : 16
**           One tick of timer is
**             microseconds            : 0.953674
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Capture                : TPM1C2V   [$004C]
**              Counter                : TPM1CNT   [$0041]
**              Mode                   : TPM1SC    [$0040]
**              Run                    : TPM1SC    [$0040]
**              Prescaler              : TPM1SC    [$0040]
**
**         Used input pin              : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       48            |  PTA6_TPM1CH2_ADP8
**             ----------------------------------------------------
**
**         Port name                   : PTA
**         Bit number (in port)        : 6
**         Bit mask of the port        : $0040
**
**         Signal edge/level           : rising
**         Pull option                 : off
**
**     Contents    :
**         Enable          - byte Cap2_Enable(void);
**         Disable         - byte Cap2_Disable(void);
**         Reset           - byte Cap2_Reset(void);
**         GetCaptureValue - byte Cap2_GetCaptureValue(Cap2_TCapturedValue *Value);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file Cap2.c
** @version 01.30
** @brief
**         This component "Capture" simply implements the capture function
**         of timer. The counter counts the same way as in free run mode. On
**         the selected edge of the input signal (on the input pin), the current
**         content of the counter register is written into the capture
**         register and the OnCapture event is called.
*/         
/*!
**  @addtogroup Cap2_module Cap2 module documentation
**  @{
*/         

/* MODULE Cap2. */

#include "Cap2.h"


static bool EnUser;                    /* Enable/Disable device by user */
volatile word Cap2_CntrState;          /* Content of counter */


/*
** ===================================================================
**     Method      :  Cap2_Enable (component Capture)
**     Description :
**         This method enables the component - it starts the capture.
**         Events may be generated (<DisableEvent>/<EnableEvent>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte Cap2_Enable(void)
{
  Cap2_CntrState = TPM1CNT;            /* Load content of counter register to variable CntrState */
  if (!EnUser) {                       /* Is the device disabled by user? */
    EnUser = TRUE;                     /* If yes then set the flag "device enabled" */
    /* TPM1C2SC: CH2F=0,CH2IE=0,MS2B=0,MS2A=0,ELS2B=0,ELS2A=1,??=0,??=0 */
    setReg8(TPM1C2SC, 0x04U);          /* Enable capture function */ 
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  Cap2_Disable (component Capture)
**     Description :
**         This method disables the component - it stops the capture.
**         No events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte Cap2_Disable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    EnUser = FALSE;                    /* If yes then set the flag "device disabled" */
    /* TPM1C2SC: CH2F=0,CH2IE=0,MS2B=0,MS2A=0,ELS2B=0,ELS2A=0,??=0,??=0 */
    setReg8(TPM1C2SC, 0x00U);          /* Disable capture function */ 
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  Cap2_Reset (component Capture)
**     Description :
**         This method resets the counter register (see implementation
**         note in <General Info>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte Cap2_Reset(word *Value)

**  This method is implemented as a macro. See Cap2.h file.  **
*/

/*
** ===================================================================
**     Method      :  Cap2_GetCaptureValue (component Capture)
**     Description :
**         This method gets the last value captured by enabled timer.
**         Note: one tick of timer is
**               0.953674 us in high speed mode
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Value           - A pointer to the content of the
**                           capture register
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte Cap2_GetCaptureValue(Cap2_TCapturedValue *Value)

**  This method is implemented as a macro. See Cap2.h file.  **
*/

/*
** ===================================================================
**     Method      :  Cap2_Init (component Capture)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void Cap2_Init(void)
{
  /* TPM1C2V: BIT15=0,BIT14=0,BIT13=0,BIT12=0,BIT11=0,BIT10=0,BIT9=0,BIT8=0,BIT7=0,BIT6=0,BIT5=0,BIT4=0,BIT3=0,BIT2=0,BIT1=0,BIT0=0 */
  setReg16(TPM1C2V, 0x00U);            /* Clear capture register */ 
  Cap2_CntrState = 0x00U;              /* Clear variable */
  EnUser = TRUE;                       /* Enable device */
  /* TPM1C2SC: CH2F=0,CH2IE=0,MS2B=0,MS2A=0,ELS2B=0,ELS2A=1,??=0,??=0 */
  setReg8(TPM1C2SC, 0x04U);            /* Enable capture function */ 
}


/* END Cap2. */

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
