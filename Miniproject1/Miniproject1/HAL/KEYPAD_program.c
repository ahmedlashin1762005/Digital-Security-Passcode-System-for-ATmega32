/******************************************************************************
 * @file        : KEYPAD_program.c
 * @author      : Ahmed Diaa Lashin
 * @brief       : 4x4 Matrix Keypad Driver Implementation
 * @target      : ATmega32
 * @organization: AZEX'S Embedded Team
 ******************************************************************************/

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "KEYPAD_interface.h"
#include <util/delay.h>

const u8 KPD_u8Buttons[4][4] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'C', '0', '=', '+'}
};

void KEYPAD_voidInit(void) {
    DIO_voidSetPinDirection(KPD_PORT, DIO_PIN0, DIO_PIN_INPUT);
    DIO_voidSetPinDirection(KPD_PORT, DIO_PIN1, DIO_PIN_INPUT);
    DIO_voidSetPinDirection(KPD_PORT, DIO_PIN2, DIO_PIN_INPUT);
    DIO_voidSetPinDirection(KPD_PORT, DIO_PIN3, DIO_PIN_INPUT);

    DIO_voidSetPinValue(KPD_PORT, DIO_PIN0, DIO_PIN_HIGH);
    DIO_voidSetPinValue(KPD_PORT, DIO_PIN1, DIO_PIN_HIGH);
    DIO_voidSetPinValue(KPD_PORT, DIO_PIN2, DIO_PIN_HIGH);
    DIO_voidSetPinValue(KPD_PORT, DIO_PIN3, DIO_PIN_HIGH);

    DIO_voidSetPinDirection(KPD_PORT, DIO_PIN4, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(KPD_PORT, DIO_PIN5, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(KPD_PORT, DIO_PIN6, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(KPD_PORT, DIO_PIN7, DIO_PIN_OUTPUT);

    DIO_voidSetPinValue(KPD_PORT, DIO_PIN4, DIO_PIN_HIGH);
    DIO_voidSetPinValue(KPD_PORT, DIO_PIN5, DIO_PIN_HIGH);
    DIO_voidSetPinValue(KPD_PORT, DIO_PIN6, DIO_PIN_HIGH);
    DIO_voidSetPinValue(KPD_PORT, DIO_PIN7, DIO_PIN_HIGH);
}

u8 KEYPAD_u8GetPressedKey(void) {
    u8 Local_u8PressedKey = KPD_NO_PRESSED_KEY;
    u8 Local_u8ColIdx, Local_u8RowIdx, Local_u8PinState;

    for (Local_u8ColIdx = 0; Local_u8ColIdx < 4; Local_u8ColIdx++) {
        DIO_voidSetPinValue(KPD_PORT, Local_u8ColIdx + 4, DIO_PIN_LOW);

        for (Local_u8RowIdx = 0; Local_u8RowIdx < 4; Local_u8RowIdx++) {
            Local_u8PinState = DIO_u8GetPinValue(KPD_PORT, Local_u8RowIdx);
            if (Local_u8PinState == DIO_PIN_LOW) {
                Local_u8PressedKey = KPD_u8Buttons[Local_u8RowIdx][Local_u8ColIdx];
                while (DIO_u8GetPinValue(KPD_PORT, Local_u8RowIdx) == DIO_PIN_LOW);
                _delay_ms(10);
            }
        }
        DIO_voidSetPinValue(KPD_PORT, Local_u8ColIdx + 4, DIO_PIN_HIGH);
    }
    return Local_u8PressedKey;
}