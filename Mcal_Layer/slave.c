//#include "../App.h"

//SPI_Config spi_slave = {
//    .spi_mode = SPI_SLAVE_SS_ENABLE,  // Set Slave mode with SS enabled
//};
////
//int _main() {
//    uint8 received_data;
//    
//    // Initialize SPI in Slave Mode
//    SPI_Init(&spi_slave);
//    
//    while (1) {
//        // Read data from Master
//        SPI_Read_Byte(&spi_slave, &received_data);
//        
//        // Send acknowledgment back
//        SPI_Send_Byte(&spi_slave, received_data + 1);
//    }
//}
