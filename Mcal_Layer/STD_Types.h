/* 
 * File:   STD_Types.h
 * Author: Dell
 *
 * Created on January 23, 2025, 5:21 PM
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H

/************************************************ Includes */
#include "STD_libraries.h"



/************************************************ Data Type Declarations */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;

typedef uint8 Std_ReturnType;

/************************************************ Macro Function Declarations */

/************************************************ Macro Declarations */

#define E_OK         (Std_ReturnType)0x01
#define E_NOT_OK     (Std_ReturnType)0x00

#define ZERO 0

#endif	/* STD_TYPES_H */

