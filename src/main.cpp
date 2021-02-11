/* Архитектура меню 
Buttons map, слева на право:
- Button1 - Mode - Режим
- Button2 - Left - Влево (Вверх)
- Button3 - Right - Вправо (Вниз)

Включение. 
Hello Screen.
Диагностика, по окончанию 
 - OK переход в режим Метеостанция
 -- сенсоры, мигнуть диодами, бузер. 
 - Error сообщения об ошибках (коды ошибок?) ожидания любой клавиши, после чего в Метеостанцию. 

Режимы:
Режим меню. 
- Главное меню
-- настройка часов (дата-время)
-- настройка будильника. 
-- настройка Метеостанции.
--- цельсии - F
--- последовательность пунктов (варианты отображения)
-- настройка графиков. 
Видение пользователя:
- После загрузки (если ОК) пользователь попадает в режим Метеостанция. 
- Долговременное зажатие кнопки Mode (режим, button1)


- Режим Метеостанция:
  На экране отображаются показания DHT и Light. 

- Режим Часы:
  Дата - время (индикатор будильника)

- (Advanced) Режим графиков. 
  Диаграмы температуры, света, heat index, light.




------------------------------- */


//Исходные коды метеостанции
#include "config.h"
#include "log.h"
#include "DHTSensor.h"
#include "LCDActuator.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
//#include "Main.h"
#include "Buttons.h"



#define MENU_ITEMS_SIZE 2
String Menu_Items[] = {"Item 1", "Item 2", "Item 3"};

int Menu_Selected_Index = 0;
int Save_Menu_Selected_Index = -1;

#define DATA_MODE 0
#define MENU_MODE 1
int Screen_Mode = DATA_MODE;

int Loop_Count = MAIN_LOOP_COUNT_LIMIT;


//--------------------------------------------------------------------------------
//-------------------------------MAIN Loop Section -------------------------------
//--------------------------------------------------------------------------------



//Setup section -------------------------------
void setup()
{
  Serial.begin(SERIAL_BAUD);
  delay(SETUP_DELAY);
  

  Log("Do setup...");

  Buttons_Setup();

  // Setup beeper
  BUZZER_Setup();

  // Setup light bulbs
  LIGHT_Setup();

  LED_Setup();

  DHT_Setup();

  // Setup screen
  LCD_Setup();
  LCD_Set_Light(true);
  LCD_Print_Line1("Hello");
  LCD_Print_Line3("wait...");

  Log("Setup complete");
}

void loop()
{
  // Wait a few seconds between measurements.
  delay(MAIN_LOOP_DELAY);
  
  Buttons_Loop();
  

  if (Get_Button1_LongPress() == true)
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
    if (Get_Button1_ShortPress() == true)
    {
      ///
      Log("btn1 Short press");
    }

    //----END OF BUTTON1 HANDLERS-----------

    //----BUTTON2 HANDLERS------------------

    if (Get_Button2_ShortPress() == true)
    {
      ///
      Log("btn2 Short press");
      Menu_Selected_Index--;
    }

    //----END OF BUTTON2 HANDLERS-----------

    //----BUTTON3 HANDLERS------------------

    if (Get_Button3_ShortPress() == true)
    {
      ///
      Log("btn3 Short press");
      Menu_Selected_Index++;
    }

    //----END OF BUTTON3 HANDLERS-----------

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
  else if (Screen_Mode == DATA_MODE)
  {
  }

  //Slow loop
  Loop_Count++;
  if (Loop_Count > MAIN_LOOP_COUNT_LIMIT)
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