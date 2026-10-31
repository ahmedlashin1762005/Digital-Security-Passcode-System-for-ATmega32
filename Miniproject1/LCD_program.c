/******************************************************************************
 * @file        : LCD_program.c
 * @author      : Ahmed Diaa Lashin
 * @brief       : 16x2 LCD Driver Implementation (4-Bit Mode)
 * @target      : ATmega32
 * @organization: AZEX'S Embedded Team
 ******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include <util/delay.h>

static void LCD_voidSendNibble(u8 Copy_u8Nibble) {
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN4, GET_BIT(Copy_u8Nibble, 0));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN5, GET_BIT(Copy_u8Nibble, 1));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN6, GET_BIT(Copy_u8Nibble, 2));
    DIO_voidSetPinValue(LCD_DATA_PORT, DIO_PIN7, GET_BIT(Copy_u8Nibble, 3));

    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, DIO_PIN_HIGH);
    _delay_ms(2);
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, DIO_PIN_LOW);
}

void LCD_voidSendCommand(u8 Copy_u8Command) {
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, DIO_PIN_LOW);
    LCD_voidSendNibble(Copy_u8Command >> 4);
    LCD_voidSendNibble(Copy_u8Command & 0x0F);
}

void LCD_voidSendChar(u8 Copy_u8Data) {
    DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, DIO_PIN_HIGH);
    LCD_voidSendNibble(Copy_u8Data >> 4);
    LCD_voidSendNibble(Copy_u8Data & 0x0F);
}

void LCD_voidInit(void) {
    DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_EN_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_DATA_PORT, DIO_PIN4, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_DATA_PORT, DIO_PIN5, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_DATA_PORT, DIO_PIN6, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_DATA_PORT, DIO_PIN7, DIO_PIN_OUTPUT);

    _delay_ms(40);
    LCD_voidSendCommand(0x02);
    LCD_voidSendCommand(0x28);
    LCD_voidSendCommand(0x0C);
    LCD_voidSendCommand(0x01);
    _delay_ms(2);
}

void LCD_voidSendString(const char* Copy_pcString) {
    u8 i = 0;
    while (Copy_pcString[i] != '\0') {
        LCD_voidSendChar(Copy_pcString[i]);
        i++;
    }
}

void LCD_voidClear(void) {
    LCD_voidSendCommand(0x01);
    _delay_ms(2);
}

void LCD_voidGoToXY(u8 Copy_u8Line, u8 Copy_u8Column) {
    u8 Local_u8Address = 0;
    if (Copy_u8Line == 0) {
        Local_u8Address = Copy_u8Column;
    } else if (Copy_u8Line == 1) {
        Local_u8Address = 0x40 + Copy_u8Column;
    }
    LCD_voidSendCommand(0x80 | Local_u8Address);
}