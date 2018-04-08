/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : PE_Const.h
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Component   : PE_Const
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-04-07, 16:05, # CodeGen: 0
**     Abstract    :
**         This component "PE_Const" contains internal definitions
**         of the constants.
**     Settings    :
**     Contents    :
**         No public methods
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file PE_Const.h
** @version 01.00
** @brief
**         This component "PE_Const" contains internal definitions
**         of the constants.
*/         
/*!
**  @addtogroup PE_Const_module PE_Const module documentation
**  @{
*/         

#ifndef __PE_Const_H
#define __PE_Const_H

/* Constants for detecting running mode */
#define HIGH_SPEED        0x00U        /* High speed */
#define LOW_SPEED         0x01U        /* Low speed */
#define SLOW_SPEED        0x02U        /* Slow speed */

/* Reset cause constants */
#define RSTSRC_POR        0x80U        /* Power-on reset        */
#define RSTSRC_PIN        0x40U        /* External reset bit    */
#define RSTSRC_COP        0x20U        /* COP reset             */
#define RSTSRC_ILOP       0x10U        /* Illegal opcode reset  */
#define RSTSRC_ILAD       0x08U        /* Illegal address reset */
#define RSTSRC_MODRST     0x04U        /* Normal Monitor Mode Entry Reset*/
#define RSTSRC_MENRST     0x04U        /* Forced Monitor Mode Entry Reset*/
#define RSTSRC_LVI        0x02U        /* Low voltage inhibit reset */

#endif /* _PE_Const_H */
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
