/* 
 * File:   ADC.c
 * Author: Dell
 *
 * Created on March 14, 2025, 1:17 AM
 */
#include "ADC.h"

#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*ADC_InterruptHandler)(void) = NULL;
#endif

static inline void ADC_input_channel_port_confiq(ADC_channel_select_t channel);
static inline void select_result_format(const ADC_Confiq_t *adc);
static inline void configure_voltage_reference(const ADC_Confiq_t *adc);

/**
 * @Summary Initializes the ADC
 * @Description This routine initializes the ADC.
 *              This routine must be called before any other ADC routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Init(const ADC_Confiq_t *adc)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
        // Disable the ADC
        ADC_CONVERTER_DISABLE();
        //Configure the acquisition time
        ADCON2bits.ACQT = adc->acquisition_time;
        //Configure the conversion clock
        ADCON2bits.ADCS = adc->conversion_clock;
        //Configure the default channel 
        ADCON0bits.CHS = adc->channel_select;
        ADC_input_channel_port_confiq(adc->channel_select);
        //Configure the interrupt
        #if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        if(INTERRUPT_HIGH_PRIORITY == adc->priority){ 
            INTERRUPT_GlobalInterruptHighEnable();
            ADC_HighPrioritySet(); 
        }
        else if(INTERRUPT_LOW_PRIORITY == adc->priority){ 
            INTERRUPT_GlobalInterruptLowEnable();
            ADC_LowPrioritySet(); 
        }
        else{ /* Nothing */ }
        #endif
        ADC_InterruptHandler = adc->ADC_InterruptHandler;
        #endif
        //Configure the result format 
        select_result_format(adc);
        //Configure the voltage reference
        configure_voltage_reference(adc);
        //Enable the ADC
        ADC_CONVERTER_ENABLE();
        
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary De-Initializes the ADC
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_DeInit(const ADC_Confiq_t *adc)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
        // Disable the ADC
        ADC_CONVERTER_DISABLE();
        // Disable the interrupt
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            ADC_InterruptDisable();
        #endif
    }
    return ret;
}

/**
 * @Summary Allows selection of a channel for conversion
 * @Description This routine is used to select desired channel for conversion.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_SelectChannel(const ADC_Confiq_t *adc, ADC_channel_select_t channel)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
        //Configure the default channel 
        ADCON0bits.CHS = channel;
        ADC_input_channel_port_confiq(channel);
        
        
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary Starts conversion
 * @Description This routine is used to start conversion of desired channel.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_Startconversion(const ADC_Confiq_t *adc)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
        ADC_START_CONVERSION();
        ret = E_OK;
    }
    return ret;
}
/**
 * @Summary Returns true when the conversion is completed otherwise false.
 * @Description This routine is used to determine if conversion is completed.
 *              When conversion is complete routine returns true. It returns false otherwise.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 *                ADC_StartConversion() should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_status The conversion status
 *          true  - If conversion is complete
 *          false - If conversion is not completed
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_IsConversionDone(const ADC_Confiq_t *adc, uint8 *conversion_status)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == adc || NULL == conversion_status){
        ret = E_NOT_OK;
    }
    else{
        *conversion_status = (ADCON0bits.GO_nDONE);
        ret = E_OK;
    }
    return ret;
}
/**
 * @Summary Returns the ADC conversion value.
 * @Description This routine is used to get the analog to digital converted value.
 *              This routine gets converted values from the channel specified.
 * @Preconditions   This routine returns the conversion value only after the conversion is complete.
 *                  Completion status can be checked using ADC_IsConversionDone() routine.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversionResult(const ADC_Confiq_t *adc, ADC_result_t *conversion_result)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == adc || NULL == conversion_result){
        ret = E_NOT_OK;
    }
    else{
        if(ADC_RESULT_RIGHT == adc->result_format){
            *conversion_result = (ADC_result_t)((ADRESH << 8 ) +ADRESL);
        }
        else if(ADC_RESULT_LEFT == adc->result_format){
            *conversion_result = (ADC_result_t)(((ADRESH << 8 ) +ADRESL) >> 6) ;
        }
        else{
            *conversion_result = (ADC_result_t)((ADRESH << 8 ) +ADRESL);
        }
        ret = E_OK;
    }
    return ret;
}
/**
 * @Summary Returns the ADC conversion value, also allows selection of a channel for conversion.
 * @Description This routine is used to select desired channel for conversion.
 *              This routine is get the analog to digital converted value.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_GetConversion_Blocking(const ADC_Confiq_t *adc, ADC_channel_select_t channel, ADC_result_t *conversion_result)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == adc || NULL == conversion_result){
        ret = E_NOT_OK;
    }
    else{
        // select the A/D channel
        ret = ADC_SelectChannel(adc, channel);
        // Start the conversion
        ret = ADC_Startconversion(adc);
        // Check if conversion is completed
        while(ADCON0bits.GO_nDONE);
        ret = ADC_GetConversionResult(adc, conversion_result);
    }
    return ret;
}
/**
 * 
 * @param adc
 * @param channel
 * @return 
 */
Std_ReturnType ADC_StartConversion_Interrupt(const ADC_Confiq_t *adc, ADC_channel_select_t channel)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
        ADC_InterruptFlagClear();
        /* select the A/D channel */
        ret = ADC_SelectChannel(adc, channel);
        /* Start the conversion */
        ret = ADC_Startconversion(adc);
        ret = E_OK;
    }
    return ret;
}


static inline void ADC_input_channel_port_confiq(ADC_channel_select_t channel)
{
    switch(channel)
    {
        case ADC_CHANNEL_AN0 : 
            SET_BIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_AN1 : 
            SET_BIT(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_CHANNEL_AN2 : 
            SET_BIT(TRISA, _TRISA_RA2_POSN);
            break;
        case ADC_CHANNEL_AN3 : 
            SET_BIT(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_AN4 : 
            SET_BIT(TRISA, _TRISA_RA5_POSN);
            break;
        case ADC_CHANNEL_AN5 : 
            SET_BIT(TRISA, _TRISE_RE0_POSN);
            break;
        case ADC_CHANNEL_AN6 : 
            SET_BIT(TRISA, _TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_AN7 : 
            SET_BIT(TRISA, _TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_AN8 : 
            SET_BIT(TRISA, _TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_AN9 : 
            SET_BIT(TRISA, _TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_AN10 : 
            SET_BIT(TRISA, _TRISB_RB1_POSN);
            break;
        case ADC_CHANNEL_AN11 : 
            SET_BIT(TRISA, _TRISB_RB4_POSN);
            break;
        case ADC_CHANNEL_AN12 : 
            SET_BIT(TRISA, _TRISB_RB0_POSN);
            break;  
        default : /* Nothing */;

            
        
    }
}

static inline void select_result_format(const ADC_Confiq_t * adc)
{
    if(ADC_RESULT_RIGHT == adc->result_format){
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if(ADC_RESULT_LEFT == adc->result_format){
        ADC_RESULT_LEFT_FORMAT();
    }
    else{
        ADC_RESULT_RIGHT_FORMAT();
    }
}


static inline void configure_voltage_reference(const ADC_Confiq_t *adc)
{
    if(ADC_VOLTAGE_REFERENCE_ENABLED == adc ->voltage_reference){
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
    else if(ADC_VOLTAGE_REFERENCE_DISABLED == adc->voltage_reference){
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    else{
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
}


void ADC_ISR(void){
    ADC_InterruptFlagClear();
    if(ADC_InterruptHandler){
        ADC_InterruptHandler();
    }
}