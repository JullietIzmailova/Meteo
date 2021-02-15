#include "config.h"
#include "log.h"
#include "LCDActuator.h"
#include "Buttons.h"
#include "ScreenMenu.h"

#define MENU_ITEMS_SIZE 2
String Menu_Items[] = {"Item 1", "Item 2", "Item 3"};

int Menu_Selected_Index = 0;
int Save_Menu_Selected_Index = -1;


void Screen_Menu_Init()
{
  LCD_Clear();
  Screen_Menu_Draw();
}

void Screen_Menu_Read_Buttons()
{  
    if (Get_Button1_LongPress() == true)
    {
        Log("Got to Meteo");
        
        Set_Current_Screen(MODE_CLOCK);        
    }

    if (Get_Button1_ShortPress() == true)
    {
      ///Выбор пункта меню
      Log("Press menu item");
    }

    //----END OF BUTTON1 HANDLERS-----------

    //----BUTTON2 HANDLERS------------------

    if (Get_Button2_ShortPress() == true)
    {
      ///
      Log("Select menu item UP");
      Menu_Selected_Index--;
      Screen_Menu_Draw();
    }

    //----END OF BUTTON2 HANDLERS-----------

    //----BUTTON3 HANDLERS------------------

    if (Get_Button3_ShortPress() == true)
    {
      ///
      Log("Select menu item DOWN");
      Menu_Selected_Index++;
      Screen_Menu_Draw();
    }

    //----END OF BUTTON3 HANDLERS-----------

  } //---ENDOF Draw menu



void Screen_Menu_Draw()
{
    if (Menu_Selected_Index < 0)
    {
      Menu_Selected_Index = MENU_ITEMS_SIZE;
    }

    if (Menu_Selected_Index > MENU_ITEMS_SIZE)
    {
      Menu_Selected_Index = 0;
    }

    if (Save_Menu_Selected_Index != Menu_Selected_Index)
    {
      LCD_Print_Line1(Menu_Items[Menu_Selected_Index]);
      Save_Menu_Selected_Index = Menu_Selected_Index;
    }

}