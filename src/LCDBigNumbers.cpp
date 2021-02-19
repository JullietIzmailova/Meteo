#include "LCDBigNumbers.h"
#include "src/libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.h"


//BlockXxY[]
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

byte Block5x2UpDown[] = {
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

byte Block5x2Up[] = {
  B11111,
  B11111,
  B00000,  
  B00000,
  B00000,
  B00000,
  B00000,
  B00000        
};


bool LCDBigNumber_Setup()
{
    
    LiquidCrystal_I2C * lcd = LCD_Get_LCDPointer();
    if (lcd == nullptr)
    {
        return false;
    }
    
    lcd->createChar(0, Block4x3);
    lcd->createChar(1, Block5x2UpDown);
    lcd->createChar(2, Block5x3Down);
    lcd->createChar(3, Block4x8);
    lcd->createChar(4, Block4x3Down);
    lcd->createChar(5, Block5x2Up);
   
    return true;

}

void Print_Number_2_h2(int column, int row)
{
    LiquidCrystal_I2C * lcd = LCD_Get_LCDPointer();
//first line 
    lcd->setCursor(column, row);
    lcd->write(byte(0));

    lcd->setCursor(column+1, row);
    lcd->write(byte(1));

    lcd->setCursor(column+2, row);
    lcd->write(byte(3));
//secont line     
    lcd->setCursor(column, row + 1);
    lcd->write(byte(3));

    lcd->setCursor(column+1, row + 1);
    lcd->write(byte(2));

    lcd->setCursor(column+2, row + 1);
    lcd->write(byte(4));
}

void Print_Number_3_h2(int column, int row)
{
    LiquidCrystal_I2C * lcd = LCD_Get_LCDPointer();
//first line 
    lcd->setCursor(column, row);
    lcd->write(byte(0));

    lcd->setCursor(column+1, row);
    lcd->write(byte(1));

    lcd->setCursor(column+2, row);
    lcd->write(byte(3));
//secont line     
    lcd->setCursor(column, row + 1);
    lcd->write(byte(4));

    lcd->setCursor(column+1, row + 1);
    lcd->write(byte(2));

    lcd->setCursor(column+2, row + 1);
    lcd->write(byte(3));
}

void Print_Number_6_h2(int column, int row)
{
    LiquidCrystal_I2C * lcd = LCD_Get_LCDPointer();
//first line 
    lcd->setCursor(column, row);
    lcd->write(byte(3));

    lcd->setCursor(column+1, row);
    lcd->write(byte(5));

    lcd->setCursor(column+2, row);
    lcd->write(byte(0));
//secont line     
    lcd->setCursor(column, row + 1);
    lcd->write(byte(3));

    lcd->setCursor(column+1, row + 1);
    lcd->write(byte(1));

    lcd->setCursor(column+2, row + 1);
    lcd->write(byte(3));
}

void LCDBigNumber_Print_Height2_Right(int row, String number)
{
    Print_Number_3_h2(0, row);
    Print_Number_2_h2(3, row);
    Print_Number_6_h2(6, row);
    

}

void LCDBigNumber_Print_Height2_Center(int line, String number)
{
    
}

void LCDBigNumber_Print_Height2_Left(int line, String number)
{
    
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

