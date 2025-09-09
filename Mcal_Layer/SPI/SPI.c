/* 
 * File:   SPI.c
 * Author: Dell
 *
 * Created on March 24, 2025, 1:41 AM
 */

#include "SPI.h"

#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*SPI_InterruptHandler)(void) = NULL;
#endif
    
static void MSSP_SPI_Interrupt_Init(const SPI_Config *Config);
static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(const SPI_Config *Config);
static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *Config);

/**
 * Initializes the SPI module with the given configuration.
 * @param Config : Pointer to SPI_Config structure containing SPI settings.
 * @return : E_OK if successful, E_NOT_OK otherwise.
 */
Std_ReturnType SPI_Init(const SPI_Config *Config)
{
    Std_ReturnType ret = E_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
        /* MSSP SPI Mode Select */
        SSPCON1bits.SSPM = Config->spi_mode;
        /* GPIO PIN Configurations */
        if(Config->spi_mode == SPI_MASTER_FOSC_DIV16 || Config->spi_mode == SPI_MASTER_FOSC_DIV64 ||
            Config->spi_mode == SPI_MASTER_FOSC_TMR2 || Config->spi_mode == SPI_MASTER_FOSC_DIV4){
            MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(Config);
        }else if(Config->spi_mode == SPI_SLAVE_SS_ENABLE || Config->spi_mode == SPI_SLAVE_SS_DISABLE){
            MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(Config);
        }
        /* Clock Polarity Select */
        SSPCON1bits.CKP = Config->spi_config.ClockPolarity;
        /* SPI Sample Select */
        SSPSTATbits.SMP = Config->spi_config.SampleSelect;
        /* SPI Clock Select */
        SSPSTATbits.CKE = Config->spi_config.ClockSelect;
        /* MSSP SPI Interrupt Configurations*/
        MSSP_SPI_Interrupt_Init(Config);
        /* Interrupt Configurations */        
        #if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            MSSP_SPI_InterruptDisable();
        #endif
    }
    return ret;
}

/**
 * De-initializes the SPI module by disabling it.
 * @param Config : Pointer to SPI_Config structure.
 * @return : E_OK if successful, E_NOT_OK otherwise.
 */
Std_ReturnType SPI_DeInit(const SPI_Config *Config){
    Std_ReturnType ret = E_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
        /* Interrupt Configurations */        
        #if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            MSSP_SPI_InterruptDisable();
        #endif
    }
    return ret;
}


/**
 * Sends a single byte over SPI and waits for transmission to complete.
 * @param Config : Pointer to SPI_Config structure.
 * @param _data : Byte to send.
 * @return : E_OK if successful, E_NOT_OK otherwise.
 */
Std_ReturnType SPI_Send_Byte(const SPI_Config *Config, const uint8 data){
    Std_ReturnType ret = E_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        SSPBUF = data;
        while (!SSPSTATbits.BF); /* Wait until transmission is complete */
        PIR1bits.SSPIF = 0;
    }
    return ret;
}


/**
 * Reads a single byte received over SPI.
 * @param Config : Pointer to SPI_Config structure.
 * @param _data : Pointer to store the received byte.
 * @return : E_OK if successful, E_NOT_OK otherwise.
 */
Std_ReturnType SPI_Read_Byte(const SPI_Config *Config, uint8 *_data){
    Std_ReturnType ret = E_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        while (!SSPSTATbits.BF); /* Wait for data reception */
        *_data= SSPBUF;
    }
    return ret;
}

/**
 * Configures GPIO pins for SPI Master Mode.
 * @param Config :Pointer to SPI_Config structure.                                      
 * @param _data
 * @return 
 */
Std_ReturnType SPI_Send_Byte_NonBlocking(const SPI_Config *Config, const uint8 _data){
    Std_ReturnType ret = E_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        
    }
    return ret;
}


Std_ReturnType SPI_Read_Byte_NonBlocking(const SPI_Config *Config, uint8 *_data){
    Std_ReturnType ret = E_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        
    }
    return ret;
}

void MSSP_SPI_ISR(void){
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_SPI_InterruptFlagClear();
    if(SPI_InterruptHandler){
        SPI_InterruptHandler();
    }
#endif
}

static void MSSP_SPI_Interrupt_Init(const SPI_Config *Config){
    Std_ReturnType ret = E_NOT_OK;
    if (NULL != Config) {
        
    }
}
/**
 * Configures GPIO pins for SPI Master Mode.
 * @param Config :Pointer to SPI_Config structure.                                      
 * 
 */
static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(const SPI_Config *Config){
    Std_ReturnType ret = E_NOT_OK;
    if (NULL != Config) {
        pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
        pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_INPUT};
        pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_OUTPUT};
        
        ret = gpio_pin_intialize(&SPI_SDO);
        ret = gpio_pin_intialize(&SPI_SDI);
        ret = gpio_pin_intialize(&SPI_CLK);
    
    }
}

/**
 * Configures GPIO pins for SPI Slave Mode.
 * @param Config
 */
static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *Config){
    Std_ReturnType ret = E_NOT_OK;
    if (NULL != Config) {
        pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
        pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_INPUT};
        pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRECTION_INPUT};
        pin_config_t SPI_SS  = {.port = PORTA_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_INPUT};
        
        ret = gpio_pin_intialize(&SPI_SDO);
        ret = gpio_pin_intialize(&SPI_SDI);
        ret = gpio_pin_intialize(&SPI_CLK);
        ret = gpio_pin_intialize(&SPI_SS);
    }
}

