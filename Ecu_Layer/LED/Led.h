/* 
 * File:   Led.h
 * Author: Mohamed Fawzy
 *
 * Created on January 23, 2025, 5:12 PM
 */
#ifndef LED_H
#define	LED_H


/************************************************ Includes */
#include "../../Mcal_Layer/GPIO/GPIO.h"
/************************************************ Data Type Declarations */
typedef enum{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct{
    uint8 port_name : 4;
    uint8 pin : 3;
    uint8 led_status : 1;
}led_t;

/************************************************ Function Declarations  */
Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_turn_toggle(const led_t *led);



#endif	/* LED_H */

