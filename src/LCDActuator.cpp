#include "config.h"
#include "log.h"
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

byte Lock[] = {
  B01110,
  B10001,
  B10001,
  B11111,
  B11011,
  B11011,
  B11111,
  B00000
};

byte Block4x3[] = {
  B11110,
  B11110,
  B11110,  
  B00000,
  B00000,
  B00000,
  B00000,
  B00000        
};

byte Block5x2[] = {
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};

byte Block5x3Down[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,        
  B11111,
  B11111,
  B11111
};

byte Block4x8[] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110
};

byte Block4x3Down[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,        
  B11110,
  B11110,
  B11110
};



LiquidCrystal_I2C *lcd = nullptr;

void LCD_Print_Chars()
{
       

    lcd->createChar(0, Block4x3);
    lcd->createChar(1, Block5x2);
    lcd->createChar(2, Block5x3Down);
    lcd->createChar(3, Block4x8);
    lcd->createChar(4, Block4x3Down);

//first line 
    lcd->setCursor(0, 0);
    lcd->write(byte(0));

    lcd->setCursor(1, 0);
    lcd->write(byte(1));

    lcd->setCursor(2, 0);
    lcd->write(byte(3));
//secont line     
    lcd->setCursor(0, 1);
    lcd->write(byte(3));

    lcd->setCursor(1, 1);
    lcd->write(byte(2));

    lcd->setCursor(2, 1);
    lcd->write(byte(4));

       /*
       for (int i=0; i <80; i++)
       {
            lcd->createChar(i, Lock);

       }
       lcd->clear();
       for (int i=0; i <80; i++)
       {

            lcd->write(byte(i));
       }
       */

}

bool LCD_Setup()
{
    lcd = new LiquidCrystal_I2C(LCD_PORT, LCD_COLS, LCD_ROWS); //port = 0x27 for PCF8574T and PCF8574AT for 0x3F, 16 cols, 2 raws
    lcd->init();
    Log("LCD setup complete");
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

void LCD_Print_Right(String text)
{
    if (text.length() == 0)
    {
        return;
    }
    if (text.length() < 20)
    {
        String empty = "";
        for (unsigned int i=0; i < 20 - text.length(); i++)
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
        for (unsigned int i=0; i < (20 - text.length()) / 2; i++)
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