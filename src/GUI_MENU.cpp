#include "Log.h"

void DoShortPress_GUI_MENU()
{

}
void DoLongPress_GUI_MENU()
{

}
void Reapint_GUI_MENU()
{

    Log("Slow loop");
    Loop_Count = 0;

    if (Screen_Mode == DATA_MODE)
    {

      LCD_Clear();

      float current_heat_index = DHT_Get_Heat_Index();

      if (current_heat_index > HEAT_INDEX_LEVEL_LOW)
      {
        if (current_heat_index > HEAT_INDEX_LEVEL_HIGH)
        {
          LED_Only_Red_Set_Light();
        }
        else
        {
          LED_Only_Yellow_Set_Light();
        }
      }
      else
      {
        LED_Only_Green_Set_Light();
      }

#ifdef LIGHT_SENSOR_ANALOG_PIN
      float lightValue = LIGHT_GET_data();
      //работаем с Вольтами снятыми с аналогового пина
      LCD_Print_Line4("V => " + String(lightValue) + " Ph => " + String(LIGHT_GET_data()));
#else
      float lightValue = LIGHT_GET_data();
      //работаем с Bool снятого с цифрового пина
      LCD_Print_Line4("A => " + String(lightValue) + " Ph => " + String(LIGHT_GET_data()));
#endif

      LCD_Print_Line1("Temp ====> " + String(DHT_Get_Temperature()) + char(223) + "C");
      LCD_Print_Line2("Hum =====> " + String(DHT_Get_Humidity()) + " %");
      LCD_Print_Line3("curr Hi => " + String(current_heat_index));
    }
  }
}


  if (Button1_EventLongPress == true)
  {
    ///
    Log("btn1 Long press");

    if (Screen_Mode == DATA_MODE)
    {
      LCD_Clear();
      Save_Menu_Selected_Index = -1;
      Screen_Mode = MENU_MODE;
    }
    else
    {
      LCD_Clear();
      Screen_Mode = DATA_MODE;
      Loop_Count = MAIN_LOOP_COUNT_LIMIT;
    }
  }

  //Draw menu items
  if (Screen_Mode == MENU_MODE)
  {
    if (Button1_EventShortPress == true)
    {
      ///
      Log("btn1 Short press");
    }

    //----END OF BUTTON1 HANDLERS-----------

    //----BUTTON2 HANDLERS------------------

    if (Button2_EventShortPress == true)
    {
      ///
      Log("btn2 Short press");
      Menu_Selected_Index--;
    }

    //----END OF BUTTON2 HANDLERS-----------

    //----BUTTON3 HANDLERS------------------

    if (Button3_EventShortPress == true)
    {
      ///
      Log("btn3 Short press");
      Menu_Selected_Index++;
    }
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
  } //---ENDOF Draw menu
