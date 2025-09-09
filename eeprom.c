/* 
 * File:   App.c
 * Author: Mohamed Fawzy
 *
 * Created on January 23, 2025, 5:12 PM
 */

#include "App.h"
//led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
//led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};
//
//button_t btn1 = {
//    .button_pin.port = PORTB_INDEX, .button_pin.pin = GPIO_PIN0, .button_pin.direction = GPIO_DIRECTION_INPUT, .button_pin.logic = GPIO_LOW,
//    .button_connection = BUTTON_ACTIVE_HIGH, .button_state =BUTTON_RELEASED
//};


//led_t led3 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN2, .led_status = GPIO_LOW};
//
//void Int0_APP_ISR(void){
//    led_turn_toggle(&led1);
//}
//void Int1_APP_ISR(void)

//led_t led1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOW};
//led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOW};
//led_t led3 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN2, .led_status = GPIO_LOW};
//
//void Int0_APP_ISR(void){
//    led_turn_toggle(&led1);
//}
//void Int1_APP_ISR(void){
//    led_turn_toggle(&led2);
//}
//void Int2_APP_ISR(void){
//    led_turn_toggle(&led3);
//}

//interrupt_intx_t int0_obj = {
//  .EXT_InterruptHandler =  Int0_APP_ISR,
//  .edge = INTERRUPT_RISING_EDGE,
//  .priority = INTERRUPT_HIGH_PRIORITY,
//  .source = INTERRUPT_EXTERNAL_INT0,
//  .mcu_pin.port = PORTB_INDEX,
//  .mcu_pin.pin = GPIO_PIN0,
//  .mcu_pin.direction = GPIO_DIRECTION_INPUT
//};
//
//
//interrupt_intx_t int1_obj = {
//  .EXT_InterruptHandler =  Int1_APP_ISR,
//  .edge = INTERRUPT_FALLING_EDGE,
//  .priority = INTERRUPT_HIGH_PRIORITY,
//  .source = INTERRUPT_EXTERNAL_INT1,
//  .mcu_pin.port = PORTB_INDEX,
//  .mcu_pin.pin = GPIO_PIN1,
//  .mcu_pin.direction = GPIO_DIRECTION_INPUT
//};
//
//interrupt_intx_t int2_obj = {
//  .EXT_InterruptHandler =  Int2_APP_ISR,
//  .edge = INTERRUPT_RISING_EDGE,
//  .priority = INTERRUPT_HIGH_PRIORITY,
//  .source = INTERRUPT_EXTERNAL_INT2,
//  .mcu_pin.port = PORTB_INDEX,
//  .mcu_pin.pin = GPIO_PIN2,
//  .mcu_pin.direction = GPIO_DIRECTION_INPUT
//};
//volatile uint8 Program_Selected = 0;
//volatile uint8 btn_stat = 0;
//
//void toggle_leds(void) {
//    if (Program_Selected == 0) {
//        led_turn_on(&led1);
//        led_turn_off(&led2);
//    } else {
//        led_turn_off(&led1);
//        led_turn_on(&led2);
//    }
//}
//
//uint8 eepromVal = 0, eepromred;

int main() {     
    Std_ReturnType ret = E_NOT_OK;
////    application_intialize();
//    ret = interrupt_intx_init(&int0_obj);
//    ret = interrupt_intx_init(&int1_obj);
//    ret = interrupt_intx_init(&int2_obj);
//    ret = led_initialize(&led1);
//    ret = led_initialize(&led2);
//    ret = button_initialize(&btn1);
//    ret = led_initialize(&led2);
//    ret = led_initialize(&led3);
    
//    ret = led_initialize(&led1);
//    ret = led_initialize(&led2);
//    ret = button_initialize(&btn1);
//    
    // Read the last stored state from EEPROM
//    ret = Data_EEPROM_ReadByte(0x3FF, &Program_Selected);
//    if (Program_Selected > 1) {
//        Program_Selected = 0;
//    }
//    toggle_leds(); // Apply the initial state
    
//    while(1) {
////        ret = button_read_state(&btn1, &btn_stat);
//        
//        if(BUTTON_PRESSED == btn_stat) {
//            Program_Selected ^= 1; // Toggle between 0 and 1
//            
//            // Store the selected program state in EEPROM
//            ret = Data_EEPROM_WriteByte(0x3FF, Program_Selected);
//            __delay_ms(300); // Debounce delay
//            
//            toggle_leds(); // Apply the new state
//        }
//    }
        
//        ret = Data_EEPROM_WriteByte(0x3FF, eepromVal++);
//        __delay_ms(1000);
//        ret = Data_EEPROM_ReadByte(0x3FF, &eepromred);
//        if(5 == eepromred)
//        {
//            
//            led_turn_on(&led1);
//            __delay_ms(1000);
//        }
//        else
//        {
//            led_turn_off(&led1);
//        }
//    }
    
    return (EXIT_SUCCESS);
}




                                                    