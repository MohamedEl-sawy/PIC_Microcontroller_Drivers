/* 
 * File:   Char_Lcd.c
 * Author: Mohamed Fawzy
 *
 * Created on January 24, 2025, 4:46 PM
 */

#include "Char_Lcd.h"


static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 ROW, uint8 col);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 ROW, uint8 col);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 col);
/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    uint8 lcd_data_pins_counter = ZERO;
    
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(lcd_data_pins_counter=ZERO; lcd_data_pins_counter<4; lcd_data_pins_counter++){
            ret = gpio_pin_intialize(&(lcd->lcd_data[lcd_data_pins_counter]));
        }
        // LCD initialization commands
        __delay_ms(20);  // Wait for LCD power stabilization
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE); // Function set: 8-bit, 2 lines
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
         // Clear display and configure settings
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80); // Move cursor to the beginning
    }
    return ret;
}


/**
 * 
 * @param lcd
 * @param command
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
        /* Write Logic (0) to the "Register Select" Pin to select the "Instruction Register"  */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        /* Send the Command through the (4-Pins" Data lines */
        ret = lcd_send_4bits( lcd , command >> 4);
        /* Send the Enable Signal on the "E" Pin */
        ret = lcd_4bit_send_enable_signal(lcd);
        /* Send the Command through the (4-Pins" Data lines */
        ret = lcd_send_4bits( lcd , command );
        /* Send the Enable Signal on the "E" Pin */
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd Pointer to the LCD configurations
 * @param data The data that we need to send to the LCD
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data)
{
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
        /* Write Logic (1) to the "Register Select" Pin to select the "Data Register"  */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        /* Send the Data through the (4-Pins" Data lines */
        ret = lcd_send_4bits( lcd , data >> 4);
        /* Send the Enable Signal on the "E" Pin */
        ret = lcd_4bit_send_enable_signal(lcd);
        /* Send the Data through the (4-Pins" Data lines */
        ret = lcd_send_4bits( lcd , data );
         /* Send the Enable Signal on the "E" Pin */
        ret = lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    return ret;

}

/**
 * 
 * @param lcd
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        while (*str){
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret = E_OK;
    
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd, row, column);
        while (*str){
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 char_lcd = ZERO;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
        for(char_lcd = 0; char_lcd <= 7; char_lcd++)
        {
            ret = lcd_4bit_send_char_data(lcd,_chr[char_lcd]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}


/*!********************************************************************************************************/
/*!*********************************************************************************************LCD 8 BITS*/
/*!********************************************************************************************************/


/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    uint8 l_data_pins_counter = ZERO;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{    
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(l_data_pins_counter=ZERO; l_data_pins_counter<8; l_data_pins_counter++){
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        // LCD initialization commands
        __delay_ms(20);  // Wait for LCD power stabilization
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE); // Function set: 8-bit, 2 lines
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
         // Clear display and configure settings
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, 0x80); // Move cursor to the beginning
    }
    return ret;
}


/**
 * 
 * @param lcd
 * @param command
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    uint8 lcd_pins_counter = ZERO;
    
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
        /* Write Logic (0) to the "Register Select" Pin to select the "Instruction Register"  */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for (lcd_pins_counter = ZERO ; lcd_pins_counter <8 ; ++lcd_pins_counter)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[lcd_pins_counter]) , (command >> lcd_pins_counter) & 0x01);
        }
         /* Send the Enable Signal on the "E" Pin */
        ret = lcd_8bit_send_enable_signal(lcd);
    }
    return ret;
}


/**
 * 
 * @param lcd
 * @param data
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    uint8 lcd_pin_counter = ZERO;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }
    else{
        /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
        /* Write Logic (1) to the "Register Select" Pin to select the "Data Register"  */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        /*Sent the data through the (8-pins Data Line */
        for(lcd_pin_counter = ZERO ; lcd_pin_counter <8 ; lcd_pin_counter++){
            ret = gpio_pin_write_logic (&(lcd->lcd_data[lcd_pin_counter]) , (data>>lcd_pin_counter) & 0x01);
        }
        /* Send Enable Signal on the E pin */
        lcd_4bit_send_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret = E_OK;

    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = lcd_8bit_set_cursor(lcd,  row, column );
        ret = lcd_8bit_send_char_data (lcd,data);
        
    }
    return ret;
}


/**
 * 
 * @param lcd
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;

    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        while (*str){
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
        
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret = E_OK;

    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = lcd_8bit_set_cursor(lcd,  row, column );
        while (*str){
            ret = lcd_8bit_send_char_data(lcd, *str++);
            
        }
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 char_lcd = ZERO;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
        for(char_lcd = 0; char_lcd <= 7; char_lcd++)
        {
            ret = lcd_8bit_send_char_data(lcd,_chr[char_lcd]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;
}


/*!********************************************************************************************************/
/*!********************************************************************************************************/

/**
 * 
 * @param lcd
 * @param _data_command
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *lcd, uint8 _data_command){
    Std_ReturnType ret = E_OK;
    
    ret = gpio_pin_write_logic(&(lcd->lcd_data[0]) , (_data_command >> 0) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[1]) , (_data_command >> 1) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[2]) , (_data_command >> 2) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[3]) , (_data_command >> 3) & (uint8)0x01);
        
    return ret;
}

/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType lcd_4bit_send_enable_signal(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_HIGH);
    __delay_us(500); // Reduce to 500 microseconds
    ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_LOW);
    return ret;
}

/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType lcd_8bit_send_enable_signal(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_HIGH);
    __delay_us(500); // Reduce to 500 microseconds
    ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_LOW);
    return ret;
}

/**
 * 
 * @param lcd Pointer to the LCD configuration parameters defined by the user
 * @param row Which row you need to print your character
 * @param coulmn Which column you need to print your character
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 col){
    Std_ReturnType ret = E_OK;
    col--;
    switch(row)
    {
        case ROW1 :
            ret = lcd_8bit_send_command(lcd , (0x80 + col));
            break;
        case ROW2 :
            ret = lcd_8bit_send_command(lcd , (0xc0 + col));
            break;
        case ROW3 : 
            ret = lcd_8bit_send_command(lcd , (0x94 + col));
            break;
        case ROW4 : 
            ret = lcd_8bit_send_command(lcd , (0xd4 + col));
            break;
        default: ;
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 col){
    Std_ReturnType ret = E_OK;
    col--;
    switch(row)
    {
        case ROW1 :
            ret = lcd_4bit_send_command(lcd , (0x80 + col));
            break;
        case ROW2 :
            ret = lcd_4bit_send_command(lcd , (0xc0 + col));
            break;
        case ROW3 : 
            ret = lcd_4bit_send_command(lcd , (0x94 + col));
            break;
        case ROW4 : 
            ret = lcd_4bit_send_command(lcd , (0xd4 + col));
            break;
        default: ;
    }
    return ret;
}