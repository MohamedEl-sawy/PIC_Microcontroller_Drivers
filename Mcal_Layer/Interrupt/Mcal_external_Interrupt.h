/* 
 * File:   Mcal_rexternal_Interrupt.h
 * Author: Dell
 *
 * Created on March 4, 2025, 11:41 PM
 */

#ifndef MCAL_REXTERNAL_INTERRUPT_H
#define	MCAL_REXTERNAL_INTERRUPT_H

#include "Mcal_Interrupt-Confiq.h"


// *********************************************** Macro Functions Declarations
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
// This roution clears the interrupt enable for the external interrupt INT0
#define EXT_INT0_INterruptDisable()  (INTCONbits.INT0E = 0)
// This roution sets the interrupt enable for the external interrupt INT0
#define EXT_INT0_INterruptEnable()  (INTCONbits.INT0E = 1)
// This roution clear the interrupt flag for the external interrupt INT0
#define EXT_INT0_InterruptFlagClear()   (INTCONbits.INT0F = 0)
// This roution set the interrupt glag for the external interrupt INT0
#define EXT_INT0_InterruptFlagSet()   (INTCONbits.INT0F = 1)
// This routine set the edge detect of the extern interrupt to negative edge
#define EXT_INT0_RisingEdgeSet()    (INTCON2bits.INTEDG0 = 1)
// This routine set the edge detect of the extern interrupt to positive edge
#define EXT_INT0_FallingEdgeSet()    (INTCON2bits.INTEDG0 = 0)


// This routine clears the interrupt enable for the external interrupt, INT1
#define EXT_INT1_InterruptDisable()         (INTCON3bits.INT1IE = 0)
// This routine sets the interrupt enable for the external interrupt, INT1
#define EXT_INT1_InterruptEnable()          (INTCON3bits.INT1IE = 1)
// This routine clears the interrupt flag for the external interrupt, INT1
#define EXT_INT1_InterruptFlagClear()       (INTCON3bits.INT1IF = 0)
// This routine set the edge detect of the extern interrupt to negative edge
#define EXT_INT1_RisingEdgeSet()            (INTCON2bits.INTEDG1 = 1)
// This routine set the edge detect of the extern interrupt to positive edge
#define EXT_INT1_FallingEdgeSet()           (INTCON2bits.INTEDG1 = 0)


// This routine clears the interrupt enable for the external interrupt, INT2
#define EXT_INT2_InterruptDisable()         (INTCON3bits.INT2IE = 0)
// This routine sets the interrupt enable for the external interrupt, INT2
#define EXT_INT2_InterruptEnable()          (INTCON3bits.INT2IE = 1)
// This routine clears the interrupt flag for the external interrupt, INT2
#define EXT_INT2_InterruptFlagClear()       (INTCON3bits.INT2IF = 0)
// This routine set the edge detect of the extern interrupt to negative edge
#define EXT_INT2_RisingEdgeSet()            (INTCON2bits.INTEDG2 = 1)
// This routine set the edge detect of the extern interrupt to positive edge
#define EXT_INT2_FallingEdgeSet()           (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
// This routine set the INT1 External Interrupt Priority to be High priority
#define EXT_INT1_HighPrioritySet()           (INTCON3bits.INT1IP = 1)
// This routine set the INT1 External Interrupt Priority to be Low priority
#define EXT_INT1_LowPrioritySet()            (INTCON3bits.INT1IP = 0)
// This routine set the INT2 External Interrupt Priority to be High priority
#define EXT_INT2_HighPrioritySet()           (INTCON3bits.INT2IP = 1)
// This routine set the INT2 External Interrupt Priority to be Low priority
#define EXT_INT2_LowPrioritySet()            (INTCON3bits.INT2IP = 0)
#endif


#endif


#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt disable for the external interrupt, RBx */
#define EXT_RBx_InterruptDisable()         (INTCONbits.RBIE = 0)
/* This routine sets the interrupt enable for the external interrupt, RBx */
#define EXT_RBx_InterruptEnable()          (INTCONbits.RBIE = 1)
/* This routine clears the interrupt flag for the external interrupt, RBx */
#define EXT_RBx_InterruptFlagClear()       (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This routine set the RBx External Interrupt Priority to be High priority */
#define EXT_RBx_Priority_High()            (INTCON2bits.RBIP = 1)
/* This routine set the RBx External Interrupt Priority to be Low priority */
#define EXT_RBx_Priority_Low()             (INTCON2bits.RBIP = 0)
#endif

#endif

// *********************************************** Data Type Declarations
typedef void (*InterruptHandler)(void);

typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE
}interrupt_INTx_edge;

typedef enum{
    INTERRUPT_EXTERNAL_INT0 =  0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2        
}interrupt_INTx_src;

typedef struct{
    void (* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src source;
    interrupt_priority_cfg priority;
}interrupt_intx_t;

typedef struct{
    void (* EXT_InterruptHandler_HIGH)(void);
    void (* EXT_InterruptHandler_LOW)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
}interrupt_RBx_t;

// *********************************************** SoftWare Interfaces Declarations
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType interrupt_intx_init(const interrupt_intx_t *int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType interrupt_intx_Deinit(const interrupt_intx_t *int_obj);

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType interrupt_RBx_init(const interrupt_RBx_t *int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType interrupt_RBx_Deinit(const interrupt_RBx_t *int_obj);



#endif	/* MCAL_REXTERNAL_INTERRUPT_H */

