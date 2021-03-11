
#include "config.h"
#include "log.h"
#include "LCDActuator.h"
#include "Buttons.h"
#include "Menu.h"
#include "main.h"

#define MENU_ITEMS_SIZE 2

extern int App_Mode;
extern int App_Saved_Mode;


void Menu_Read_Buttons()
{
  if (!Is_Edit_Mode())
  {
    if (Get_Button2_ShortPress() == true)
    {
      Log("Select menu item UP");
      App_Mode--;
      if (App_Mode < 0)
      {
        App_Mode = MENU_ITEMS_SIZE;
      }
    }

    if (Get_Button3_ShortPress() == true)
    {
      Log("Select menu item UP");
      App_Mode++;
      if (App_Mode > MENU_ITEMS_SIZE)
      {
        App_Mode = 0;
      }
    }
  }
}
