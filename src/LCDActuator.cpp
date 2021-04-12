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

//I2C LCD driver based on OWLOS\src\libraries\LiquidCrystal_I2C\LiquidCrystal_I2C.cpp by https://gitlab.com/tandembyte/liquidcrystal_i2c
//
//Известные I2C адрес для разных типов PCF8574хх чипов (если перемычки не соединенны)
//порт 0x27 для PCF8574T
//порт 0x3F для PCF8574AT
//если вам известны адреса для других типов - передайте их нам
//https://raspberrypi.stackexchange.com/questions/39773/how-can-i-use-multiple-lcd-with-connected-via-i2c-on-same-raspberry-project
//A0 | A1 | A2 | 8574 | 8574A
//----+----+----+------+-------
//  L |  L |  L | 0x20 | 0x38
//  L |  L |  H | 0x21 | 0x39
//  L |  H |  L | 0x22 | 0x3A
//  L |  H |  H | 0x23 | 0x3B
//  H |  L |  L | 0x24 | 0x3C
//  H |  L |  H | 0x25 | 0x3D
//  H |  H |  L | 0x26 | 0x3E
//  H |  H |  H | 0x27 | 0x3F
//
//Хорошая лекция по I2C шине:
//https://www.youtube.com/watch?v=_4KD29qnhNM
//WiKi:
//https://ru.wikipedia.org/wiki/I%C2%B2C
//https://ru.wikipedia.org/wiki/%D0%96%D0%B8%D0%B4%D0%BA%D0%BE%D0%BA%D1%80%D0%B8%D1%81%D1%82%D0%B0%D0%BB%D0%BB%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B9_%D0%B4%D0%B8%D1%81%D0%BF%D0%BB%D0%B5%D0%B9
//контроллер LCD
//https://ru.wikipedia.org/wiki/HD44780

//примечание: драйвер LCD требует I2C адрес подчиненного устройства на шине. Для совместимости с общей архитектурой драйверов - I2C адрес представлен внешне в роли
//пина. Что делает возможность управления адресом из PinService.

#include "config.h"
#include "log.h"
#include "LCDActuator.h"
#include "src/libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.h"

LiquidCrystal_I2C *lcd;

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

    for (uint8_t i = 0; i < (n - s.length()); i++)
    {
        s = '0' + s;
    }

    lcd->print(s);
}
