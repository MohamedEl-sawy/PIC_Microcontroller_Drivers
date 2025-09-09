/* 
 * File:   DC_Motor.h
 * Author: Mohamed Fawzy
 *
 * Created on January 24, 2025, 12:36 AM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

/* ********************************************* Includes */

#include "../../Mcal_Layer/GPIO/GPIO.h"
/* ********************************************* Macro Declarations */
#define DC_MOTOR_ON_STATUS  0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

#define DC_MOTOR_PIN1 0x00U
#define DC_MOTOR_PIN2 0x01U

/* ********************************************* Data Type Declarations */
typedef struct{
    pin_config_t dc_motor_pin[2];
}dc_motor_t;


/* ********************************************* Software Interfaces Declarations */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);


#endif	/* DC_MOTOR_H */

