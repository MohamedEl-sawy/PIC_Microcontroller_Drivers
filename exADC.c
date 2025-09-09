/* 
 * File:   App.c
 * Author: Mohamed Fawzy
 *
 * Created on January 23, 2025, 5:12 PM
 */

#include "App.h"



ADC_Confiq_t adc_1 = {
    .ADC_InterruptHandler = NULL,
    .acquisition_time = ADC_12_TAD,
    .channel_select = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLED
};

uint16 adc_res_1 = 0, adc_res_2 = 0, adc_res_3 = 0, adc_res_4 = 0;
int main() {
    Std_ReturnType ret = E_NOT_OK;
    ret = ADC_Init(&adc_1);
    
    while(1)
    {
        ret = ADC_GetConversion_Blocking(&adc_1, ADC_CHANNEL_AN0, &adc_res_1);
//        ret = ADC_GetConversion_Blocking(&adc_2, ADC_CHANNEL_AN1, &adc_res_2);
//        ret = ADC_GetConversion_Blocking(&adc_3, ADC_CHANNEL_AN2, &adc_res_3);
//        ret = ADC_GetConversion_Blocking(&adc_4, ADC_CHANNEL_AN3, &adc_res_4);
    }
    
    return (EXIT_SUCCESS);
}




                                                    