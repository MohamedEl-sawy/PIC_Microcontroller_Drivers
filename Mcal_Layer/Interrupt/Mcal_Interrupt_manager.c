/* 
 * File:   Mcal_Inerrupt_manager.c
 * Author: Dell
 *
 * Created on March 4, 2025, 11:41 PM
 */

#include "Mcal_Inerrupt_manager.h"

static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;


#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    void __interrupt() INterruptManagerHIGH(void)
    {
        /* ============ INTx External On Change Interrupt Start ============ */
        if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
            INT0_ISR(); /* External Interrupt 0 */
        }
        else{ /* Nothing */ }
        if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
            INT2_ISR(); /* External Interrupt 1 */
        }
        else{ /* Nothing */ }
        if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
            INT2_ISR(); /* External Interrupt 2 */
        }
        else{ /* Nothing */ }
        /* ============ INTx External Interrupt End ============ */
        
        /* ============ PortB External On Change Interrupt Start ============ */
        if ((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF))
        {
            if (PORTBbits.RB4 == GPIO_HIGH && RB4_Flag)
            {
                RB4_Flag = 0;
                RB4_ISR(0);
            }
            else if (PORTBbits.RB4 == GPIO_LOW && !RB4_Flag)
            {
                RB4_Flag = 1;
                RB4_ISR(1);
            }
            
            if (PORTBbits.RB5 == GPIO_HIGH && RB5_Flag)
            {
                RB5_Flag = 0;
                RB5_ISR(0);
            }
            else if (PORTBbits.RB5 == GPIO_LOW && !RB5_Flag)
            {
                RB5_Flag = 1;
                RB5_ISR(1);
            }
            
            if (PORTBbits.RB6 == GPIO_HIGH && RB6_Flag)
            {
                RB6_Flag = 0;
                RB6_ISR(0);
            }
            else if (PORTBbits.RB6 == GPIO_LOW && !RB6_Flag)
            {
                RB6_Flag = 1;
                RB6_ISR(1);
            }
            
            if (PORTBbits.RB7 == GPIO_HIGH && RB7_Flag)
            {
                RB7_Flag = 0;
                RB7_ISR(0);
            }
            else if (PORTBbits.RB7 == GPIO_LOW && !RB7_Flag)
            {
                RB7_Flag = 1;
                RB7_ISR(1);
            }
        }

        /* ============ PortB External On Change Interrupt End ============ */
        
        if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF)){
            ADC_ISR();
        }
        else{ /* Nothing */ }
        
        
        if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF)){
//            MSSP_I2C_ISR();
        }
        else{ /* Nothing */ }
        if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF)){
//            MSSP_I2C_BC_ISR();
        }
        else{ /* Nothing */ }
        if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF)){
            MSSP_SPI_ISR();
        }
        else{ /* Nothing */ }
    }

void __interrupt(low_priority) INterruptManagerLOW(void)
{
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCUR == INTCON3bits.INT1F)){
        INT1_ISR();
    }
    else{ /* Nothing */ }
}
#else

void __interrupt() InterruptManager(void)
{
    /* ============ INTx External On Change Interrupt Start ============ */
    if(INTERRUPT_ENABLE == INTCONbits.INT0IE && INTERRUPT_OCCUR == INTCONbits.INT0IF )
    {
        INT0_ISR(); /* External Interrupt 0 */
    }
    else{/* Nothing */}
    
    if(INTERRUPT_ENABLE == INTCON3bits.INT1E && INTERRUPT_OCCUR == INTCON3bits.INT1F )
    {
        INT1_ISR(); /* External Interrupt 1 */
    }
    else{/* Nothing */}
    
    if(INTERRUPT_ENABLE == INTCON3bits.INT2E && INTERRUPT_OCCUR == INTCON3bits.INT2F )
    {
        INT2_ISR(); /* External Interrupt 2 */
    }
    else{/* Nothing */}
    
    /* ============ INTx External Interrupt End ============ */
    
    /* ============ PortB External On Change Interrupt Start ============ */
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB4 == GPIO_HIGH) && (RB4_Flag == 1)){
        RB4_Flag = 0;
        RB4_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB4 == GPIO_LOW) && (RB4_Flag == 0)){
        RB4_Flag = 1;
        RB4_ISR(1);
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB5 == GPIO_HIGH) && (RB5_Flag == 1)){
        RB5_Flag = 0;
        RB5_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB5 == GPIO_LOW) && (RB5_Flag == 0)){
        RB5_Flag = 1;
        RB5_ISR(1);
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB6 == GPIO_HIGH) && (RB6_Flag == 1)){
        RB6_Flag = 0;
        RB6_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB6 == GPIO_LOW) && (RB6_Flag == 0)){
        RB6_Flag = 1;
        RB6_ISR(1);
    }
    else{ /* Nothing */ }
    
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB7 == GPIO_HIGH) && (RB7_Flag == 1)){
        RB7_Flag = 0;
        RB7_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (PORTBbits.RB7 == GPIO_LOW) && (RB7_Flag == 0)){
        RB7_Flag = 1;
        RB7_ISR(1);
    }
    else{ /* Nothing */ }
    
    /* ============ PortB External On Change Interrupt End ============ */
    
    
    
}

#endif