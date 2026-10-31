/******************************************************************************
 * @file        : main.c
 * @author      : Ahmed Diaa Lashin
 * @brief       : Digital Security Passcode System Main Application
 * @target      : ATmega32
 * @organization: AZEX'S Embedded Team
 ******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include <util/delay.h>
#include <string.h>

#define PASSCODE_LENGTH  4
const char MASTER_PASSCODE[PASSCODE_LENGTH + 1] = "1234";

int main(void) {
    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN0, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN1, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN2, DIO_PIN_OUTPUT);

    DIO_voidSetPinValue(DIO_PORTB, DIO_PIN0, DIO_PIN_LOW);
    DIO_voidSetPinValue(DIO_PORTB, DIO_PIN1, DIO_PIN_LOW);
    DIO_voidSetPinValue(DIO_PORTB, DIO_PIN2, DIO_PIN_LOW);

    LCD_voidInit();
    KEYPAD_voidInit();

    u8 key;
    char user_input[PASSCODE_LENGTH + 1] = {0};
    u8 input_idx = 0;
    u8 failed_attempts = 0;

    LCD_voidSendString("Enter Passcode:");
    LCD_voidGoToXY(1, 0);

    while (1) {
        key = KEYPAD_u8GetPressedKey();

        if (key != KPD_NO_PRESSED_KEY) {
            if (key == 'C') {
                input_idx = 0;
                memset(user_input, 0, sizeof(user_input));
                LCD_voidClear();
                LCD_voidSendString("Enter Passcode:");
                LCD_voidGoToXY(1, 0);
            }
            else if (input_idx < PASSCODE_LENGTH && key >= '0' && key <= '9') {
                user_input[input_idx++] = key;
                LCD_voidSendChar('*');

                if (input_idx == PASSCODE_LENGTH) {
                    _delay_ms(300);
                    LCD_voidClear();

                    if (strcmp(user_input, MASTER_PASSCODE) == 0) {
                        LCD_voidSendString("ACCESS GRANTED!");
                        DIO_voidSetPinValue(DIO_PORTB, DIO_PIN0, DIO_PIN_HIGH);
                        _delay_ms(3000);
                        DIO_voidSetPinValue(DIO_PORTB, DIO_PIN0, DIO_PIN_LOW);
                        failed_attempts = 0;
                    } else {
                        failed_attempts++;
                        LCD_voidSendString("ACCESS DENIED!");
                        DIO_voidSetPinValue(DIO_PORTB, DIO_PIN1, DIO_PIN_HIGH);
                        _delay_ms(2000);
                        DIO_voidSetPinValue(DIO_PORTB, DIO_PIN1, DIO_PIN_LOW);

                        if (failed_attempts >= 3) {
                            LCD_voidClear();
                            LCD_voidSendString("SYSTEM LOCKED!");
                            DIO_voidSetPinValue(DIO_PORTB, DIO_PIN2, DIO_PIN_HIGH);
                            _delay_ms(10000);
                            DIO_voidSetPinValue(DIO_PORTB, DIO_PIN2, DIO_PIN_LOW);
                            failed_attempts = 0;
                        }
                    }

                    input_idx = 0;
                    memset(user_input, 0, sizeof(user_input));
                    LCD_voidClear();
                    LCD_voidSendString("Enter Passcode:");
                    LCD_voidGoToXY(1, 0);
                }
            }
        }
    }
    return 0;
}