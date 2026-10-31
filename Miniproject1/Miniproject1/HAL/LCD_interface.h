/******************************************************************************
 * @file        : LCD_interface.h
 * @author      : Ahmed Diaa Lashin
 * @brief       : 16x2 LCD Driver Interface (4-Bit Mode)
 * @target      : ATmega32
 * @organization: AZEX'S Embedded Team
 ******************************************************************************/

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define LCD_DATA_PORT   DIO_PORTA
#define LCD_CTRL_PORT   DIO_PORTA

#define LCD_RS_PIN      DIO_PIN1
#define LCD_EN_PIN      DIO_PIN2

void LCD_voidInit(void);
void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidSendChar(u8 Copy_u8Data);
void LCD_voidSendString(const char* Copy_pcString);
void LCD_voidClear(void);
void LCD_voidGoToXY(u8 Copy_u8Line, u8 Copy_u8Column);

#endif /* LCD_INTERFACE_H_ */