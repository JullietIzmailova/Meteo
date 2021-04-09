/* ----------------------------------------------------------------------------
Ready IoT Solution - OWLOS Meteo
Copyright 2020, 2021 by:
- Julliet Izmailova
- Vitalii Glushchenko (cehoweek@gmail.com)
- Denys Melnychuk (meldenvar@gmail.com)
- Denis Kirin (deniskirinacs@gmail.com)
- Serhii Lehkii (sergey@light.kiev.ua)

This file is part of Ready IoT Solution - OWLOS

OWLOS is free software : you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

OWLOS is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with OWLOS. If not, see < https://www.gnu.org/licenses/>.

GitHub: https://github.com/KirinDenis/Meteo

(Этот файл — часть Ready IoT Solution - OWLOS.

OWLOS - свободная программа: вы можете перераспространять ее и/или изменять
ее на условиях Стандартной общественной лицензии GNU в том виде, в каком она
была опубликована Фондом свободного программного обеспечения; версии 3
лицензии, любой более поздней версии.

OWLOS распространяется в надежде, что она будет полезной, но БЕЗО ВСЯКИХ
ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА или ПРИГОДНОСТИ ДЛЯ
ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ.
Подробнее см.в Стандартной общественной лицензии GNU.

Вы должны были получить копию Стандартной общественной лицензии GNU вместе с
этой программой. Если это не так, см. <https://www.gnu.org/licenses/>.)
--------------------------------------------------------------------------------------*/

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

    for (uint8_t i=0; i < (n-s.length()); i++ )
    {
       s = '0' + s;
    }

    lcd->print(s);
}
