/* 
 * File:   App.c
 * Author: Mohamed Fawzy
 *
 * Created on January 23, 2025, 5:12 PM
 */

#include "App.h"

    
SPI_Config  spi_master = {
    .spi_mode = SPI_MASTER_FOSC_DIV16, // Set Master mode with Fosc/16
    
};
int main() {
    Std_ReturnType ret = E_NOT_OK;
    uint8 received_data;
    // Initialize SPI in Master Mode
    SPI_Init(&spi_master);
    while (1) {
        // Send a byte
        SPI_Send_Byte(&spi_master, 0x55);
        
        // Read a byte (if applicable)
        SPI_Read_Byte(&spi_master, &received_data);
    }
    
    
    return (EXIT_SUCCESS);
}




                                                    