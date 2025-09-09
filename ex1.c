/* 
 * File:   App.c
 * Author: Mohamed Fawzy
 *
 * Created on January 23, 2025, 5:11 PM
 */

#include "./App.h"
#include "Ecu_Layer/Char_Lcd/Char_Lcd.h"

chr_lcd_4bit_t lcd_1 ={
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
};
chr_lcd_8bit_t led_2 ={
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN6,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN7,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    
    .lcd_data[0].port =PORTD_INDEX,
    .lcd_data[0].pin = GPIO_PIN0,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    
    .lcd_data[1].port =PORTD_INDEX,
    .lcd_data[1].pin = GPIO_PIN1,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    
    .lcd_data[2].port =PORTD_INDEX,
    .lcd_data[2].pin = GPIO_PIN2,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    
    .lcd_data[3].port =PORTD_INDEX,
    .lcd_data[3].pin = GPIO_PIN3,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
    
    .lcd_data[4].port =PORTD_INDEX,
    .lcd_data[4].pin = GPIO_PIN4,
    .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[4].logic = GPIO_LOW,
    
    .lcd_data[5].port =PORTD_INDEX,
    .lcd_data[5].pin = GPIO_PIN5,
    .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[5].logic = GPIO_LOW,
    
    .lcd_data[6].port =PORTD_INDEX,
    .lcd_data[6].pin = GPIO_PIN6,
    .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[6].logic = GPIO_LOW,
    
    .lcd_data[7].port =PORTD_INDEX,
    .lcd_data[7].pin = GPIO_PIN7,
    .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[7].logic = GPIO_LOW,
};

uint8 l_Counter = ZERO;
void welcome_Massege()
{
    for(l_Counter=1; l_Counter<=2; l_Counter++)
    {
        lcd_4bit_send_string_pos( &lcd_1,1,5,"Hello All");
        lcd_4bit_send_string_pos( &lcd_1,2,3,"Embedded Diploma");
        __delay_ms(500);
        lcd_4bit_send_command(&lcd_1,_LCD_CLEAR);
        __delay_ms(100);
    }
}

void loading()
{
    lcd_8bit_send_string_pos(&led_2, 1,1,"Loading");
    uint8 counter = ZERO;
    for(counter =8; counter<=15;counter++)
    {
        lcd_8bit_send_string_pos(&led_2,1,counter,".");
        __delay_ms(50);
    }
    lcd_8bit_send_string_pos(&led_2, 1,8,"        ");
}

uint8 customChar[8] = {
  0x00,
  0x1B,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x0E,
  0x04 
};
void main();

int main() {
    Std_ReturnType ret = E_NOT_OK;
   ret = lcd_8bit_intialize(&(led_2));  
    ret = lcd_4bit_intialize(&(lcd_1));
   welcome_Massege();
    
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 10, "Doaa");
    ret = lcd_4bit_send_custom_char(&lcd_1,2,15, customChar,1 );
    
    while(1)
    {
//        loading();   
//        for(l_Counter= 5; l_Counter<7; l_Counter++)
//        {
//            ret = lcd_4bit_send_string_pos( &lcd_1,1,l_Counter,"Doaa Ismail");
//            __delay_ms(250);
//            ret = lcd_4bit_send_string_pos( &lcd_1,1,l_Counter," ");
//        }
//        ret = lcd_4bit_send_string_pos( &lcd_1,1,5,"            ");
//        
//        
//        for(l_Counter= 7; l_Counter>=5; --l_Counter)
//        {
//            ret = lcd_4bit_send_string_pos( &lcd_1,1,l_Counter,"Doaa Ismail");
//            __delay_ms(250);
//            ret = lcd_4bit_send_string_pos( &lcd_1,1,l_Counter+11," ");
//        }
//        ret = lcd_4bit_send_string_pos( &lcd_1,1,5,"            ");
        
    
    }

    
    
//    ret = lcd_4bit_send_command(&lcd_1,_LCD_DISPLAY_SHIFT_RIGHT );
//    __delay_ms(250);
//    ret = lcd_4bit_send_command(&lcd_1,_LCD_DISPLAY_SHIFT_RIGHT );
//    __delay_ms(250);
//    
//    ret = lcd_4bit_send_command(&lcd_1,_LCD_DISPLAY_SHIFT_LEFT );
//    __delay_ms(250);
//    ret = lcd_4bit_send_command(&lcd_1,_LCD_DISPLAY_SHIFT_LEFT );
//    __delay_ms(250);

    
    return (EXIT_SUCCESS);
}

//!11111111111111111111111111111111111111111111111111111111


/* 
 * File:   App.c
 * Author: Mohamed Fawzy
 *
 * Created on January 23, 2025, 5:11 PM
 */

#include "./App.h"
#include "Ecu_Layer/Char_Lcd/Char_Lcd.h"


uint8 valueKeypad_1 = ZERO;
chr_lcd_4bit_t lcd_1 ={
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
};

uint8 CupCoffee[] = {
  0x00,
  0x00,
  0x00,
  0x0F,
  0x17,
  0x0F,
  0x00,
  0x00
};

keypad_t Keypad_1= {
    .keypad_row_pins[0].port = PORTD_INDEX,
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic = GPIO_LOW,
    
    .keypad_row_pins[1].port = PORTD_INDEX,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic = GPIO_LOW,
    
    .keypad_row_pins[2].port = PORTD_INDEX,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic = GPIO_LOW,
    
    .keypad_row_pins[3].port = PORTD_INDEX,
    .keypad_row_pins[3].pin = GPIO_PIN3,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic = GPIO_LOW,
    
    .keypad_columns_pins[0].port = PORTD_INDEX,
    .keypad_columns_pins[0].pin = GPIO_PIN4,
    .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[0].logic = GPIO_LOW,
    
    .keypad_columns_pins[1].port = PORTD_INDEX,
    .keypad_columns_pins[1].pin = GPIO_PIN5,
    .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[1].logic = GPIO_LOW,
    
    .keypad_columns_pins[2].port = PORTD_INDEX,
    .keypad_columns_pins[2].pin = GPIO_PIN6,
    .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[2].logic = GPIO_LOW,
    
    .keypad_columns_pins[3].port = PORTD_INDEX,
    .keypad_columns_pins[3].pin = GPIO_PIN7,
    .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[3].logic = GPIO_LOW,

};


pin_config_t wa1={
    .port = PORTC_INDEX,
    .pin = GPIO_PIN6,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW,
};

pin_config_t wa2={
    .port = PORTC_INDEX,
    .pin = GPIO_PIN7,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW,
};

uint8 l_Counter = ZERO;
void welcome_Massege()
{
    for(l_Counter = 1; l_Counter<=2;l_Counter++)
    {
        lcd_4bit_send_string_pos( &(lcd_1),1,4,"Have a Nice Day");
        lcd_4bit_send_string_pos( &(lcd_1),2,2,"Get a Cup of Coffee ");
        lcd_4bit_send_string_pos( &(lcd_1),3,5,"press Start");
        lcd_4bit_send_custom_char(&(lcd_1),4, 10,CupCoffee,1 );
    }
}

void Menu()
{
    lcd_4bit_send_string_pos( &(lcd_1),1,1,"1-Cup Without Sugar");
    lcd_4bit_send_string_pos( &(lcd_1),2,1,"2-Cup with Sugar");
    lcd_4bit_send_string_pos( &(lcd_1),3,1,"3-Cup with Milk");
    lcd_4bit_send_string_pos( &(lcd_1),4,2,"Choose Cup Coffe");
    lcd_4bit_send_custom_char(&(lcd_1),4,17,CupCoffee,1);
//    while(1);
}
void CupWithoutSugar()
{
    gpio_pin_write_logic(&(wa2), GPIO_HIGH);
    __delay_ms(1000);
    gpio_pin_write_logic(&(wa2), GPIO_LOW);
}
int main() {
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_intialize(&(lcd_1));
    ret = keypad_initialize(&(Keypad_1));
    ret = gpio_pin_direction_intialize(&wa1);
    ret = gpio_pin_direction_intialize(&wa2);
    ret = keypad_get_value(&(Keypad_1), &valueKeypad_1);
    welcome_Massege();
    
    if(valueKeypad_1 == '#')
    {
      Menu();
        if(valueKeypad_1=='1')
        {   
            CupWithoutSugar();
        }
    }
    return (EXIT_SUCCESS);
}
