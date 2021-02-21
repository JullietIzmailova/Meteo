#include "LCDBigNumbers.h"
#include "src/libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.h"


/****** Block numbers bar ************************************/

/*
struct CharSymbol
{
  

}

*/

byte FontBlocks1[8][8] = 
{
        (B11100,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11100),

        (B00111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B00111),

        (B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111),

        (B11110,
        B11100,
        B00000,
        B00000,
        B00000,
        B00000,
        B11000,
        B11100),

        (B01111,
        B00111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00011,
        B00111),

        (B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111),

        (B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00111,
        B01111),

        (B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000)

};

int * Char_Number_Ptr;

#define CHAR_TABLE_SIZE 16

int Char_Numbers[6][CHAR_TABLE_SIZE]=
{
  (1,7,0,1,5,0),
  (32,32,0,32,32,0),
  (4,2,0,1,5,5),
  (4,2,0,6,5,0),
  (1,5,0,32,32,0),
  (1,2,3,6,5,0),
  (1,2,3,1,5,0),
  (1,7,0,32,32,0),
  (1,2,0,1,5,0),
  (1,2,0,6,5,0)
// (5,5)
};

/*
int Char_Number_1[6]={32,32,0,32,32,0};
int Char_Number_2[6]={4,2,0,1,5,5};
int Char_Number_3[6]={4,2,0,6,5,0};


int Char_Number_4[6]={1,5,0,32,32,0};
int Char_Number_5[6]={1,2,3,6,5,0};
int Char_Number_6[6]={1,2,3,1,5,0};
int Char_Number_7[6]={1,7,0,32,32,0};
int Char_Number_8[6]={1,2,0,1,5,0};
int Char_Number_9[6]={1,2,0,6,5,0};
int Char_Symbol_Colon[2]={5,5};
*/


// 0 1 2 3 ... 9 , 10  11  12
//                  :   -   %



/****** END Block numbers bar ************************************/

bool LCDBigNumber_Setup()
{

    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    if (lcd == nullptr)
    {
        return false;
    }

    for(int i=0;i<8;i++)
    {
        lcd->createChar(i, FontBlocks1[i]);
    }
    // lcd->createChar(7, bar7);


    return true;
}

// Char_Number_0 {1,7,0,1,5,0}

void Print_Number(int column, int row, int * ACharNumber)
{
    LiquidCrystal_I2C *lcd = LCD_Get_LCDPointer();
    
for(int i=0;i<3;i++)
{
  //firast line
    lcd->setCursor(column+i, row);
    lcd->write(ACharNumber[i]);
    // lcd->write(byte(1));

  // 2nd line
    lcd->setCursor(column+i, row + 1);
    lcd->write(ACharNumber[i+3]);
}

/*    //first line
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
    */
}


/*
 // Char_Number_1  {32, 32, 0, 32,32,0 }
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

 // Char_Number_2  {4,2,0,1,5,5}

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

 // Char_Number_3 {4,2,0,6,5,0} 

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


 // Char_Number_4 {1,5,0,32,32,0} 

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

// Char_Number_5={1,2,3,6,5,0};

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


// Char_Number_6={1,2,3,1,5,0}


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

// Char_Number_7={1,7,0,32,32,0}


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

//Char_Number_8={1,2,0,1,5,0}


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

// Char_Number_9={1,2,0,6,5,0}

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

// Char_Symbol_Colon={5,5}
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

*/

void LCDBigNumber_Print_Height2_Right(int row, String number)
{
    int start = 0;

    for (int i=0; i < number.length(); i++)
    {
        Print_Number(start,row,&Char_Numbers[i][0]);

/*        if (number[i] == '0')
        {
          Print_Number(start,row,&Char_Number_0[0]);

          // Print_Number_0_h2(start, row);        
          start+=3;
        }
        else 
        if (number[i] == '1')
        {
          Print_Number(start,row,&Char_Number_0[1]);          
          // Print_Number_1_h2(start, row);        
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
  */

    }
}


/*
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
*/