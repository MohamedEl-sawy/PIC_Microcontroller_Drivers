/*
 * 
 * File:   Keypad.h
 * Author: Mohamed Fawzy
 *
 * Created on January 24, 2025, 1:15 AM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

/* ************************************************** Includes */

#include "../../Mcal_Layer/GPIO/GPIO.h"
/* ************************************************** Macro Declarations */

#define ECU_KEYPAD_ROWS    4
#define ECU_KEYPAD_COLUMNS 4
/* ************************************************** Data Type Declarations */

typedef struct{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;


/* ************************************************** Software Interfaces Declarations */

Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);

#endif	/* KEYPAD_H */