// This module handle Menu user screen repaint case ("event") and button-press case ("event")
// Info about which button was pressed  stored in CurBtnIndex

#include "config.h"
#include "log.h"
#include "DHTSensor.h"
#include "LCDActuator.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"

#include "GUI_Meteo.h"
#include "GUI_MENU.h"

#include "main.h"

extern TButton btnSender;
extern int Loop_Count;
extern int Screen_Mode;

void DoShortPress_GUI_MENU()
{
  switch (btnIndex)
  {

  case 0:
    Log("btn[0] Short press in Menu mode");
  case 1:
    Log("btn[1] Short press in Menu mode");
    Menu_Selected_Index--;
  case 2:
    Log("btn[2] Short press in Menu mode");
    Menu_Selected_Index++;
  }

// verify if Index is in range
  if (Menu_Selected_Index < 0)
  {
    Menu_Selected_Index = MENU_ITEMS_SIZE;
  }

  if (Menu_Selected_Index > MENU_ITEMS_SIZE)
  {
    Menu_Selected_Index = 0;
  }
}
void DoLongPress_GUI_MENU()
{
}

void Repaint_GUI_MENU()
{
  if (Save_Menu_Selected_Index != Menu_Selected_Index)
  {
    LCD_Print_Line1(Menu_Items[Menu_Selected_Index]);
    Save_Menu_Selected_Index = Menu_Selected_Index;
  }

} //---ENDOF Draw menu
