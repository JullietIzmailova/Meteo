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


#include "LCDBigNumbers.h"
#include "src/libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.h"


/****** Block numbers bar ************************************/

byte bar0[8] = 
{
        B11100,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11100
};
byte bar1[8] =
{
        B00111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B00111
};
byte bar2[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar3[8] =
{
        B11110,
        B11100,
        B00000,
        B00000,
        B00000,
        B00000,
        B11000,
        B11100
};
byte bar4[8] =
{
        B01111,
        B00111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00011,
        B00111
};
byte bar5[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
byte bar6[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00111,
        B01111
};
byte bar7[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};

/****** END Block numbers bar ************************************/

bool LCDBigNumber_Setup()
{

    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    if (lcd == nullptr)
    {
        return false;
    }


    lcd->createChar(0, bar0);
    lcd->createChar(1, bar1);
    lcd->createChar(2, bar2);
    lcd->createChar(3, bar3);
    lcd->createChar(4, bar4);
    lcd->createChar(5, bar5);
    lcd->createChar(6, bar6);
    lcd->createChar(7, bar7);


    return true;
}

void Print_Number_0_h2(int column, int row)
{
    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    //first line
    lcd->setCursor(column, row);
    lcd->write(byte(1));

    lcd->setCursor(column + 1, row);
    lcd->write(byte(7));

    lcd->setCursor(column + 2, row);
    lcd->write(byte(0));
    //secont line
    lcd->setCursor(column, row + 1);
    lcd->write(byte(1));

    lcd->setCursor(column + 1, row + 1);
    lcd->write(byte(5));

    lcd->setCursor(column + 2, row + 1);
    lcd->write(byte(0));
}

void Print_Number_1_h2(int column, int row)
{
    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    //first line
    lcd->setCursor(column, row);
    lcd->write(byte(32));

    lcd->setCursor(column + 1, row);
    lcd->write(byte(32));

    lcd->setCursor(column + 2, row);
    lcd->write(byte(0));

    //secont line
    lcd->setCursor(column, row + 1);
    lcd->write(byte(32));

    lcd->setCursor(column+1, row + 1);
    lcd->write(byte(32));

    lcd->setCursor(column+2, row+1);
    lcd->write(byte(0));
}

void Print_Number_2_h2(int column, int row)
{
    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    //first line
    lcd->setCursor(column, row);
    lcd->write(byte(4));

    lcd->setCursor(column + 1, row);
    lcd->write(byte(2));

    lcd->setCursor(column + 2, row);
    lcd->write(byte(0));
    //secont line
    lcd->setCursor(column, row + 1);
    lcd->write(byte(1));

    lcd->setCursor(column + 1, row + 1);
    lcd->write(byte(5));

    lcd->setCursor(column + 2, row + 1);
    lcd->write(byte(5));
}

void Print_Number_3_h2(int column, int row)
{
    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    //first line
    lcd->setCursor(column, row);
    lcd->write(byte(4));

    lcd->setCursor(column + 1, row);
    lcd->write(byte(2));

    lcd->setCursor(column + 2, row);
    lcd->write(byte(0));
    //secont line
    lcd->setCursor(column, row + 1);
    lcd->write(byte(6));

    lcd->setCursor(column + 1, row + 1);
    lcd->write(byte(5));

    lcd->setCursor(column + 2, row + 1);
    lcd->write(byte(0));
}

void Print_Number_4_h2(int column, int row)
{
    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    //first line
    lcd->setCursor(column, row);
    lcd->write(byte(1));

    lcd->setCursor(column + 1, row);
    lcd->write(byte(5));

    lcd->setCursor(column + 2, row);
    lcd->write(byte(0));
    //secont line
    lcd->setCursor(column, row + 1);
    lcd->write(byte(32));

    lcd->setCursor(column + 1, row + 1);
    lcd->write(byte(32));

    lcd->setCursor(column + 2, row + 1);
    lcd->write(byte(0));
}

void Print_Number_5_h2(int column, int row)
{
    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    //first line
    lcd->setCursor(column, row);
    lcd->write(byte(1));

    lcd->setCursor(column + 1, row);
    lcd->write(byte(2));

    lcd->setCursor(column + 2, row);
    lcd->write(byte(3));
    //secont line
    lcd->setCursor(column, row + 1);
    lcd->write(byte(6));

    lcd->setCursor(column + 1, row + 1);
    lcd->write(byte(5));

    lcd->setCursor(column + 2, row + 1);
    lcd->write(byte(0));
}

void Print_Number_6_h2(int column, int row)
{
    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    //first line
    lcd->setCursor(column, row);
    lcd->write(byte(1));

    lcd->setCursor(column + 1, row);
    lcd->write(byte(2));

    lcd->setCursor(column + 2, row);
    lcd->write(byte(3));
    //secont line
    lcd->setCursor(column, row + 1);
    lcd->write(byte(1));

    lcd->setCursor(column + 1, row + 1);
    lcd->write(byte(5));

    lcd->setCursor(column + 2, row + 1);
    lcd->write(byte(0));
}

void Print_Number_7_h2(int column, int row)  // 
{
    LiquidCrystal_I2C * lcd = LCD_Get_LCDPointer();
//first line 
    lcd->setCursor(column, row);
    lcd->write(byte(1));

    lcd->setCursor(column+1, row);
    lcd->write(byte(7));

    lcd->setCursor(column+2, row);
    lcd->write(byte(0));
//secont line     
    lcd->setCursor(column, row + 1);
    lcd->write(byte(32));

    lcd->setCursor(column+1, row + 1);
    lcd->write(byte(32));

    lcd->setCursor(column+2, row+1);
    lcd->write(byte(0));
}

void Print_Number_8_h2(int column, int row)
{
    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    //first line
    lcd->setCursor(column, row);
    lcd->write(byte(1));

    lcd->setCursor(column + 1, row);
    lcd->write(byte(2));

    lcd->setCursor(column + 2, row);
    lcd->write(byte(0));
    //secont line
    lcd->setCursor(column, row + 1);
    lcd->write(byte(1));

    lcd->setCursor(column + 1, row + 1);
    lcd->write(byte(5));

    lcd->setCursor(column + 2, row + 1);
    lcd->write(byte(0));
}

void Print_Number_9_h2(int column, int row)
{
    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    //first line
    lcd->setCursor(column, row);
    lcd->write(byte(1));

    lcd->setCursor(column + 1, row);
    lcd->write(byte(2));

    lcd->setCursor(column + 2, row);
    lcd->write(byte(0));
    //secont line
    lcd->setCursor(column, row + 1);
    lcd->write(byte(6));

    lcd->setCursor(column + 1, row + 1);
    lcd->write(byte(5));

    lcd->setCursor(column + 2, row + 1);
    lcd->write(byte(0));
}

void Print_Symbol_Colon_h2(int column, int row)
{
    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    //first line
    lcd->setCursor(column, row);
    lcd->write(byte(5));

    //secont line
    lcd->setCursor(column, row + 1);
    lcd->write(byte(5));
}

void LCDBigNumber_Print_Height2_Offset(int row, int offset, String number)
{
    int start = offset;
    for (int i=0; i < number.length(); i++)
    {
        if (number[i] == '0')
        {
          Print_Number_0_h2(start, row);        
          start+=3;
        }
        else 
        if (number[i] == '1')
        {
          Print_Number_1_h2(start, row);        
          start+=3;
        }
        else 
        if (number[i] == '2')
        {
          Print_Number_2_h2(start, row);        
          start+=3;
        }
        else 
        if (number[i] == '3')
        {
          Print_Number_3_h2(start, row);        
          start+=3;
        }
        else 
        if (number[i] == '4')
        {
          Print_Number_4_h2(start, row);        
          start+=3;
        }
        else 
        if (number[i] == '5')
        {
          Print_Number_5_h2(start, row);        
          start+=3;
        }
        else 
        if (number[i] == '6')
        {
          Print_Number_6_h2(start, row);        
          start+=3;
        }
        else 
        if (number[i] == '7')
        {
          Print_Number_7_h2(start, row);        
          start+=3;
        }
        else 
        if (number[i] == '8')
        {
          Print_Number_8_h2(start, row);        
          start+=3;
        }
        else 
        if (number[i] == '9')
        {
          Print_Number_9_h2(start, row);        
          start+=3;
        }
        else 
        if (number[i] == '0')
        {
          Print_Number_0_h2(start, row);        
          start+=3;
        }
        else 
        if (number[i] == ':')
        {
          Print_Symbol_Colon_h2(start, row);        
          start++;
        }
        else 
        if (number[i] == '.')
        {
          Print_Symbol_Colon_h2(start, row);        
          start++;
        }

/*
        if (number[i] == '%')
        {
          Print_Symbol_Colon_h2(start, row);        
          start++;
        }
*/
    }
}

void LCDBigNumber_Print_Height2_Right(int row, String number)
{
  int size = 20 - number.length() * 3;
  LCDBigNumber_Print_Height2_Offset(row, size, number);
}

void LCDBigNumber_Print_Height2_Center(int row, String number)
{
  int size = 10 - (number.length() * 3 / 2);
  LCDBigNumber_Print_Height2_Offset(row, size, number);
}

void LCDBigNumber_Print_Height2_Left(int row, String number)
{  
  LCDBigNumber_Print_Height2_Offset(row, 0, number);
}

void LCDBigNumber_Print_Height4_Right(String number)
{
}

void LCDBigNumber_Print_Height4_Center(String number)
{
}

void LCDBigNumber_Print_Height4_Left(String number)
{
}
