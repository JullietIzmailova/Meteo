#include "config.h"
#include "LCDActuator.h"
#include "src/libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.h"

/*
byte drop[8] = {
    0b00100,
    0b01010,
    0b10001,
    0b10001,
    0b10001,
    0b01110,
    0b00000,
    0b00000};
//lcd.createChar(0, drop);
lcd.write(byte(0));
  lcd.print(char(223));
*/


LiquidCrystal_I2C *lcd = nullptr;

bool LCD_Setup()
{
    lcd = new LiquidCrystal_I2C(LCD_PORT, LCD_COLS, LCD_ROWS); //port = 0x27 for PCF8574T and PCF8574AT for 0x3F, 16 cols, 2 raws
    lcd->init();
    return true;
}

void LCD_Clear()
{
    lcd->clear();
}

void LCD_Set_Light(bool light)
{
    if (light)
    {
        lcd->backlight();
    }
    else
    {
        lcd->noBacklight();
    }
}

void LCD_Print_Line1(String text)
{
    lcd->setCursor(0, 0);
    lcd->print(text);
}

void LCD_Print_Line2(String text)
{
    lcd->setCursor(0, 1);
    lcd->print(text);
}

void LCD_Print_Line3(String text)
{
    lcd->setCursor(0, 2);
    lcd->print(text);
}

void LCD_Print_Line4(String text)
{
    lcd->setCursor(0, 3);
    lcd->print(text);
}