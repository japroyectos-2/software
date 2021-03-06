/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : FC1.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Component   : FreeCntr
**     Version     : Component 01.118, Driver 01.13, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-04-09, 16:04, # CodeGen: 35
**     Abstract    :
**         This device "FreeCntr" implements a free running counter for
**         time measurement.
**     Settings    :
**         Timer name                  : TPM1 (16-bit)
**         Compare name                : TPM10
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 16777216 Hz
**           Period
**             Xtal ticks              : 128
**             microseconds            : 3906
**             milliseconds            : 4
**             seconds (real)          : 0.003906190395
**             Hz                      : 256
**           Frequency of counting (Bus clock / prescaler)
**             Hz                      : 16777216
**
**         Initialization:
**              Timer                  : Enabled
**
**         Timer registers
**              Counter                : TPM1CNT   [$0041]
**              Mode                   : TPM1SC    [$0040]
**              Run                    : TPM1SC    [$0040]
**              Prescaler              : TPM1SC    [$0040]
**              Compare                : TPM1C0V   [$0046]
**
**         User handling procedure     : not specified
**     Contents    :
**         Enable          - byte FC1_Enable(void);
**         Disable         - byte FC1_Disable(void);
**         Reset           - byte FC1_Reset(void);
**         GetCounterValue - byte FC1_GetCounterValue(FC1_TTimerValue *Value);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file FC1.c
** @version 01.13
** @brief
**         This device "FreeCntr" implements a free running counter for
**         time measurement.
*/         
/*!
**  @addtogroup FC1_module FC1 module documentation
**  @{
*/         

/* MODULE FC1. */

#include "FC1.h"

static bool EnUser;                    /* Enable/Disable device by user */

/*** Internal macros and method prototypes ***/

/*
** ===================================================================
**     Method      :  SetCV (component FreeCntr)
**
**     Description :
**         The method computes and sets compare/modulo/reload value for 
**         time measuring.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#define FC1_SetCV(_Val) ( \
  TPM1C0V = (FC1_TTimerValue)(_Val) )

/*
** ===================================================================
**     Method      :  HWEnDi (component FreeCntr)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void);

/*** End of Internal methods declarations ***/


/*
** ===================================================================
**     Method      :  HWEnDi (component FreeCntr)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void)
{
  if (EnUser) {
    TPM1SC |= 0x08U;                   /* Run counter (set CLKSB:CLKSA) */
  } else {
    /* TPM1SC: CLKSB=0,CLKSA=0 */
    clrReg8Bits(TPM1SC, 0x18U);        /* Stop counter (CLKSB:CLKSA = 00) */ 
  }
}

/*
** ===================================================================
**     Method      :  FC1_Enable (component FreeCntr)
*/
/*!
**     @brief
**         This method enables the component, i.e. timer is enabled and
**         the internal clocks are counted. The method usually also
**         reset the counter (if it is supported by HW). 
**         The method is not available if the counter is shared.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/
byte FC1_Enable(void)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    EnUser = TRUE;                     /* If yes then set the flag "device enabled" */
    HWEnDi();                          /* Enable the device */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  FC1_Disable (component FreeCntr)
*/
/*!
**     @brief
**         This method disables the component, i.e. timer is disabled
**         and the internal clocks are stopped. Last counter value is
**         usually preserved in the counter (if it is supported by HW).
**         The method is not available if the counter is shared.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/
byte FC1_Disable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    EnUser = FALSE;                    /* If yes then set the flag "device disabled" */
    HWEnDi();                          /* Disable the device */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  FC1_Reset (component FreeCntr)
*/
/*!
**     @brief
**         This method resets the timer-counter (sets to zero for
**         up-counting HW or to appropriate value for down-counting HW).
**         The method is available only if the counter register can be
**         set by software and the counter is not shared.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/
/*
byte FC1_Reset(word *Value)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  FC1_GetCounterValue (component FreeCntr)
*/
/*!
**     @brief
**         This method returns a content of the counter.
**     @param
**         Value           - Pointer to returned value.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/
/*
byte FC1_GetCounterValue(FC1_TTimerValue *Value)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  FC1_Init (component FreeCntr)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void FC1_Init(void)
{
  /* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
  setReg8(TPM1SC, 0x00U);              /* Stop HW; disable overflow interrupt and set prescaler to 0 */ 
  /* TPM1MOD: BIT15=0,BIT14=0,BIT13=0,BIT12=0,BIT11=0,BIT10=0,BIT9=0,BIT8=0,BIT7=0,BIT6=0,BIT5=0,BIT4=0,BIT3=0,BIT2=0,BIT1=0,BIT0=0 */
  setReg16(TPM1MOD, 0x00U);            /* Clear modulo register: e.g. set free-running mode */ 
  /* TPM1C0SC: CH0F=0,CH0IE=0,MS0B=0,MS0A=1,ELS0B=0,ELS0A=0,??=0,??=0 */
  setReg8(TPM1C0SC, 0x10U);            /* Set output compare mode and disable compare interrupt */ 
  EnUser = TRUE;                       /* Enable device */
  FC1_SetCV(0xFFFFU);                  /* Initialize appropriate value to the compare/modulo/reload register */
  clrSetReg8Bits(TPM1SC, 0x07U, 0x00U); /* Set prescaler */
  HWEnDi();
}

/* END FC1. */

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
