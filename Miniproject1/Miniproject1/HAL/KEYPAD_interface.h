/******************************************************************************
 * @file        : KEYPAD_interface.h
 * @author      : Ahmed Diaa Lashin
 * @brief       : 4x4 Matrix Keypad Driver Interface
 * @target      : ATmega32
 * @organization: AZEX'S Embedded Team
 ******************************************************************************/

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#define KPD_PORT            DIO_PORTC
#define KPD_NO_PRESSED_KEY  0xFF

void KEYPAD_voidInit(void);
u8   KEYPAD_u8GetPressedKey(void);

#endif /* KEYPAD_INTERFACE_H_ */