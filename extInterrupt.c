/* 
 * File:   App.c
 * Author: Mohamed Fawzy
 *
 * Created on January 23, 2025, 5:11 PM
 */

#include "./App.h"
#include "Ecu_Layer/Char_Lcd/Char_Lcd.h"

 Std_ReturnType ret = E_NOT_OK;
 

led_t led1 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW,
};

led_t led2 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .led_status = GPIO_LOW,
};

led_t led3 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .led_status = GPIO_LOW,
};

// Interrupt Flags
volatile uint8_t int0_flag = 0;
volatile uint8_t int1_flag = 0;
volatile uint8_t int2_flag = 0;


// Interrupt Service Routines (ISRs)
void int0_App_ISR() {
    int0_flag = 1;  // Set flag for INT0
    __delay_ms(250);
}

void int1_App_ISR() {
    int1_flag = 1;  // Set flag for INT1
    __delay_ms(250);
}

void int2_App_ISR() {
    int2_flag = 1;  // Set flag for INT2
    __delay_ms(250);
}


interrupt_intx_t int0_obj ={
    .EXT_InterruptHandler = int0_App_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT0,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN0,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_intx_t int1_obj ={
    .EXT_InterruptHandler = int1_App_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_LOW_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT1,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN1,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_intx_t int2_obj ={
    .EXT_InterruptHandler = int2_App_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT2,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN2,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};



int main()
{
    // Initialize LEDs
    if ((led_initialize(&led1) == E_OK) &&
        (led_initialize(&led2) == E_OK) &&
        (led_initialize(&led3) == E_OK))
    {
        // Initialize interrupts
        if ((interrupt_intx_init(&int0_obj) != E_OK) ||
            (interrupt_intx_init(&int1_obj) != E_OK) ||
            (interrupt_intx_init(&int2_obj) != E_OK))
        {
            while (1); // Stop execution if interrupts fail
        }
    }
    else
    {
        while (1); // Stop execution if LED initialization fails
    }

    while (1)
    {
        // Handle INT0 (LED1 toggle)
        if (int0_flag) {
            int0_flag = 0;  // Clear flag
            led_turn_toggle(&led1);
            __delay_ms(250);
        }
        
        // Handle INT1 (LED2 blinking)
        if (int1_flag) {
            int1_flag = 0;  // Clear flag
            led_turn_toggle(&led2);
            __delay_ms(250);
        }
        
        // Handle INT2 (LED3 toggling separately)
        if (int2_flag) {
            int2_flag = 0;  // Clear flag
            led_turn_toggle(&led3);
            __delay_ms(250);
        }
    }
    
    return (EXIT_SUCCESS);
}