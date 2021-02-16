#include <Arduino.h>

bool LCD_Setup();

void LCD_Clear();

void LCD_Set_Light(bool light);

void LCD_Print_Line1(String text);
void LCD_Print_Line2(String text);
void LCD_Print_Line3(String text);
void LCD_Print_Line4(String text);

void LCD_Print_CenterLine1(String text);
void LCD_Print_CenterLine2(String text);
void LCD_Print_CenterLine3(String text);
void LCD_Print_CenterLine4(String text);
