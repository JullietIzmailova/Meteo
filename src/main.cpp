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
  - Длительное нажатие кнопки Mode - вызов меню. 
  - Переключени C-F
  - Включает/Выключает LCD  

- Режим Часы:
  Дата - время (индикатор будильника)



------------------------------- */

//Исходные коды метеостанции
#include "config.h"
#include "log.h"
#include "DHTSensor.h"
#include "LCDActuator.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"

#include "Buttons.h"

#include "ScreenMeteo.h"
#include "ScreenMenu.h"

int Loop_Count = MAIN_LOOP_COUNT_LIMIT;

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

int Saved_Mode = MODE_NULL;

void loop()
{
  // Wait a few seconds between measurements.
  delay(MAIN_LOOP_DELAY);

  if (Saved_Mode != Get_Current_Screen())
  {
    switch (Get_Current_Screen())
    {
    case MODE_METEO:
      Screen_Meteo_Init();
      break;
    case MODE_MENU:
      Screen_Menu_Init();
      break;
    }
  }

  Saved_Mode = Get_Current_Screen();

  Buttons_Loop();

  switch (Get_Current_Screen())
  {
  case MODE_METEO:
    Screen_Meteo_Read_Buttons();
    break;
  case MODE_MENU:
    Screen_Menu_Read_Buttons();
    break;
  }

  //Slow loop
  Loop_Count++;
  if (Loop_Count > MAIN_LOOP_COUNT_LIMIT)
  {
    Loop_Count = 0;

    switch (Get_Current_Screen())
    {
    case MODE_METEO:
      Screen_Meteo_Draw();
      break;
    case MODE_MENU:
      Screen_Menu_Draw();
      break;
    }
  }
}