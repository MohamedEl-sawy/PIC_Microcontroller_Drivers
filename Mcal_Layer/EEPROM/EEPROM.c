/* 
 * File:   EEPROM.h
 * Author: Dell
 *
 * Created on March 11, 2025, 3:32 AM
 */

#include "EEPROM.h"



/**
 * @Summary Writes a data byte to Data EEPROM
 * @Description This routine writes a data byte to given Data EEPROM location
 * @Preconditions None
 * @param bAdd - Data EEPROM location to which data to be written
 * @param bData - Data to be written to Data EEPROM location
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @Example ret = Data_EEPROM_WriteByte(0x3ff, 0);
 */

Std_ReturnType Data_EEPROM_WriteByte (uint16 BADD, uint8 BDATA)
{
    Std_ReturnType  ret = E_NOT_OK;
    /* Read the Interrupt Status "Enabled or Disabled" */
    uint8 Global_Interrupt_Stat = INTCONbits.GIE; // read Stat general interrupt enable pin
    /* Update the Address Registers */
    EEADRH = (uint8)((BADD>>8)&0x03); // High Register byte
    EEADR = (uint8) (BADD & 0xff);   // low register byte
    /* Update the Data Register */
    EEDATA = BDATA;
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS  = ACCESS_FLASH_EEPROM_MEMORY;
    /* Allows write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    /* Disable all interrupts "General Interrupt" */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    /* Wait for write to complete */
    while(EECON1bits.WR);
    /* Inhibits write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = INHIBTS_WRITE_CYCLES_FLASH_EEPROM;
    /* Restore the Interrupt Status "Enabled or Disabled" */
    INTCONbits.GIE = Global_Interrupt_Stat;
    return ret;
}
 
 
/**
 * 
 * @param BADD
 * @param BDARA
 * @return 
 */
Std_ReturnType Data_EEPROM_ReadByte (uint16 BADD, uint8 *BDARA)
{
    Std_ReturnType  ret = E_NOT_OK;
    if(NULL == BDARA)
    {
        ret = E_NOT_OK;
    }
    
    else
    {
        /* Update the Address Registers */
        EEADRH = (uint8)((BADD>>8)&0x03); // High Register byte
        EEADR = (uint8) (BADD & 0xff);   // low register byte
        /* Select Access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS  = ACCESS_FLASH_EEPROM_MEMORY;
        /* Initiates a data EEPROM read cycle */
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        NOP(); /* NOPs may be required for latency at high frequencies */
        NOP(); /* NOPs may be required for latency at high frequencies */
        /* Return data */
        *BDARA = EEDATA;
        ret = E_OK;
    }
    return ret;
}