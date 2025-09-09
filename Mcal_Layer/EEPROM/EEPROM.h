/* 
 * File:   EEPROM.h
 * Author: Dell
 *
 * Created on March 11, 2025, 3:32 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include ".../../pic18f4620.h"
#include "../STD_Types.h"
#include "../../Mcal_Layer/Interrupt/Mcal_Internal_Interrupt.h"
 

#define ACCESS_EEPROM_PROGRAM_MEMORY 0
#define ACCESS_FLASH_EEPROM_MEMORY   1

#define ALLOW_WRITE_CYCLES_FLASH_EEPROM 1
#define INITIATE_DATA_EEPROM_WRITE_ERASE 1
#define INHIBTS_WRITE_CYCLES_FLASH_EEPROM  0
#define INITIATE_DATA_EEPROM_READ  1

/**
 * 
 * @param BADD
 * @param BDATA
 * @return 
 */
Std_ReturnType Data_EEPROM_WriteByte (uint16 BADD, uint8 BDATA);
/**
 * 
 * @param BADD
 * @param BDARA
 * @return 
 */
Std_ReturnType Data_EEPROM_ReadByte (uint16 BADD, uint8 *BDARA);


#endif	/* EEPROM_H */