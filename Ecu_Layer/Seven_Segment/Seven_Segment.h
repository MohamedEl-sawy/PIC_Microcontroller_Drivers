/* 
 * File:   Seven_Segment.h
 * Author: Mohamed Fawzy 
 *
 * Created on January 24, 2025, 3:29 PM
 */

#ifndef SEVEN_SEGMENT_H
#define	SEVEN_SEGMENT_H

/************************************************ Includes*/
#include "../../Mcal_Layer/GPIO/GPIO.h"

/* ************************************************ Macro Declarations */
#define SEGEMENT_PIN0 0
#define SEGEMENT_PIN1 1
#define SEGEMENT_PIN2 2
#define SEGEMENT_PIN3 3 

/* ************************************************ Data Type Declarations */
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;

/* ************************************************ Function Declarations */
Std_ReturnType seven_segement_intialize(const segment_t *seg);
Std_ReturnType seven_segement_write_number(const segment_t *seg, uint8 number);




#endif	/* SEVEN_SEGMENT_H */

