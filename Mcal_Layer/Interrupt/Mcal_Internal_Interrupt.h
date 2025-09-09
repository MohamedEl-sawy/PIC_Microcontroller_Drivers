/* 
 * File:   Mcal_Inernal_Interrupt.h
 * Author: Dell
 *
 * Created on March 4, 2025, 11:39 PM
 */

#ifndef MCAL_INERNAL_INTERRUPT_H
#define	MCAL_INERNAL_INTERRUPT_H

#include "Mcal_Interrupt-Confiq.h"

// ********************************************************* Macro Functions Declarations 

#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the ADC Module */
#define ADC_InterruptDisable()         (PIE1bits.ADIE = 0)
/* This routine sets the interrupt enable for the ADC Module */
#define ADC_InterruptEnable()          (PIE1bits.ADIE = 1)
/* This routine clears the interrupt flag for the ADC Module */
#define ADC_InterruptFlagClear()       (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the ADC Module Interrupt Priority to be High priority */
#define ADC_HighPrioritySet()          (IPR1bits.ADIP = 1)
/* This routine set the ADC Module Interrupt Priority to be Low priority */
#define ADC_LowPrioritySet()           (IPR1bits.ADIP = 0)
#endif
#endif


#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the MSSP I2C Module */
#define MSSP_I2C_InterruptDisable()         (PIE1bits.SSPIE = 0)
#define MSSP_I2C_BUS_COL_InterruptDisable() (PIE2bits.BCLIE = 0)
/* This routine sets the interrupt enable for the MSSP I2C Module */
#define MSSP_I2C_InterruptEnable()          (PIE1bits.SSPIE = 1)
#define MSSP_I2C_BUS_COL_InterruptEnable()  (PIE2bits.BCLIE = 1)
/* This routine clears the interrupt flag for the MSSP I2C Module */
#define MSSP_I2C_InterruptFlagClear()         (PIR1bits.SSPIF = 0)
#define MSSP_I2C_BUS_COL_InterruptFlagClear() (PIR2bits.BCLIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the MSSP I2C Module Interrupt Priority to be High priority */
#define MSSP_I2C_HighPrioritySet()          (IPR1bits.SSPIP = 1)
#define MSSP_I2C_BUS_COL_HighPrioritySet()  (IPR2bits.BCLIP = 1)
/* This routine set the MSSP I2C Module Interrupt Priority to be Low priority */
#define MSSP_I2C_LowPrioritySet()           (IPR1bits.SSPIP = 0)
#define MSSP_I2C_BUS_COL_LowPrioritySet()   (IPR2bits.BCLIP = 0)
#endif
#endif


#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the SPI Module */
#define MSSP_SPI_InterruptDisable()         (PIE1bits.SSPIE = 0)
/* This routine sets the interrupt enable for the SPI Module */
#define MSSP_SPI_InterruptEnable()          (PIE1bits.SSPIE = 1)
/* This routine clears the interrupt flag for the SPI Module */
#define MSSP_SPI_InterruptFlagClear()       (PIR1bits.SSPIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the SPI Module Interrupt Priority to be High priority */
#define MSSP_SPI_HighPrioritySet()          (IPR1bits.SSPIP = 1)
/* This routine set the SPI Module Interrupt Priority to be Low priority */
#define MSSP_SPI_LowPrioritySet()           (IPR1bits.SSPIP = 0)
#endif
#endif

#endif	/* MCAL_INERNAL_INTERRUPT_H */

