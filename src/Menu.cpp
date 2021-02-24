#include "config.h"
#include "log.h"
#include "LCDActuator.h"
#include "Buttons.h"
#include "Menu.h"

bool Edit_Mode = false;
#define MENU_ITEMS_SIZE 2

int Current_Screen_Index = MODE_METEO;

int Get_Current_Screen_Index()
{
  return Current_Screen_Index;
}

void Set_Edit_Mode(bool mode)
{
  Edit_Mode = mode;
}

bool Get_Edit_Mode()
{
  return Edit_Mode;
}

void Menu_Read_Buttons()
{
  if (!Edit_Mode)
  {
    if (Get_Button2_ShortPress() == true)
    {
      Log("Select menu item UP");
      Current_Screen_Index--;
      if (Current_Screen_Index < 0)
      {
        Current_Screen_Index = MENU_ITEMS_SIZE;
      }
    }

    if (Get_Button3_ShortPress() == true)
    {
      Log("Select menu item UP");
      Current_Screen_Index++;
      if (Current_Screen_Index > MENU_ITEMS_SIZE)
      {
        Current_Screen_Index = 0;
      }
    }
  }
}
