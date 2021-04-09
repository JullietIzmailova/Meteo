#include "config.h"
#include "log.h"
#include "LCDActuator.h"
#include "src/libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.h"

LiquidCrystal_I2C *lcd;
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

byte Lock[] = {
    B01110,
    B10001,
    B10001,
    B11111,
    B11011,
    B11011,
    B11111,
    B00000};

//LiquidCrystal_I2C *lcd = nullptr;

bool LCD_Setup()
{
    lcd = new LiquidCrystal_I2C(LCD_PORT, LCD_COLS, LCD_ROWS); //port = 0x27 for PCF8574T and PCF8574AT for 0x3F, 16 cols, 2 raws
    lcd->init();
    Log("LCD setup complete");
    return true;
}

LiquidCrystal_I2C *LCD_Get_LCDPointer()
{
    return lcd;
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

void LCD_Print_Right(String text)
{
    if (text.length() == 0)
    {
        return;
    }
    if (text.length() < 20)
    {
        String empty = "";
        for (unsigned int i = 0; i < 20 - text.length(); i++)
        {
            empty += " ";
        }
        text = text + empty;
    }
    lcd->print(text);
}

void LCD_Print_Center(String text)
{
    if (text.length() == 0)
    {
        return;
    }

    if (text.length() < 20)
    {
        String empty = "";
        for (unsigned int i = 0; i < (20 - text.length()) / 2; i++)
        {
            empty += " ";
        }
        text = empty + text + empty;
    }
    lcd->print(text);
}

void LCD_Print_Line1(String text)
{
    lcd->setCursor(0, 0);
    LCD_Print_Right(text);
}

void LCD_Print_Line2(String text)
{
    lcd->setCursor(0, 1);
    LCD_Print_Right(text);
}

void LCD_Print_Line3(String text)
{
    lcd->setCursor(0, 2);
    LCD_Print_Right(text);
}

void LCD_Print_Line4(String text)
{
    lcd->setCursor(0, 3);
    LCD_Print_Right(text);
}

void LCD_Print_CenterLine1(String text)
{
    lcd->setCursor(0, 0);
    LCD_Print_Center(text);
}

void LCD_Print_CenterLine2(String text)
{
    lcd->setCursor(0, 1);
    LCD_Print_Center(text);
}

void LCD_Print_CenterLine3(String text)
{
    lcd->setCursor(0, 2);
    LCD_Print_Center(text);
}

void LCD_Print_CenterLine4(String text)
{
    lcd->setCursor(0, 3);
    LCD_Print_Center(text);
}

void LCD_Print_Text(int column, int row, String text)
{
    lcd->setCursor(column, row);
    lcd->print(text);
}

void LCD_Print_Number(int column, int row, unsigned n, int base)
{
    lcd->setCursor(column, row);

    String s = String(base);

    for (int i=0; i < (n-s.length()); i++ )
    {
       s = '0' + s;
    }

    lcd->print(s);
}
