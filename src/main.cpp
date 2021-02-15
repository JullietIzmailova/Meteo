/* Архитектура меню 
Buttons map, слева на право:
            at screen\at menu
- Button1 - Menu     \Back - Режим
- Button2 -   *      \Select item
- Button3 -   *      \Set item

Пункты меню. 
Meteo->
	->Celsium
	->Graph
	->Digital
Clock->
	->Set date - скрин редактирования времени, по окончанию назад в меню, а потом назад в скрин. 
	->Set time - появляется экран редактирования времени - выход длительное нажатие меню. 
               и возврат назад в меню на этот же пункт откуда я вызвал. 
               Нажание Manu/Back возврат к скрину откуда вызвано меню. 
	->Set 24/12 [24] ? где запомнить 
	->Graph      - сразу в часы в графическом режиме - назад по меню не вернутся. 
	->Digital
Alarm->
	->Alarm set
	->Alarm on
	->Timer set
	->Timer on
-- три разновидности подпунктов
- меняю сразу и остаемся в меню. 
- вызывают скрин setup и возврат в меню, потом к скрину. 
- сразу переключению в скрин.   

Если в режиме экрана, нажать Меню (кнопку) появится первый пункт верхнего уровня меню. 
- Перебор пунктов Select (Button2).
- Выбор пункта - Set.
Для подпунктов:
- Set выбор пункта. 
- Возврат из пункта в меню кнопка Menu.
- Кнопка Menu в самом Menu это на уровень выше и Back.


Включение. 
Hello Screen.
Диагностика, по окончанию 
 - OK переход в режим Метеостанция
 -- сенсоры, мигнуть диодами, бузер. 
 - Error сообщения об ошибках (коды ошибок?) ожидания любой клавиши, после чего в Метеостанцию. 

-- Метеостанция
- Button1 меню. 




------------------------------- */

//Исходные коды метеостанции
#include "config.h"
#include "log.h"
#include "DHTSensor.h"
#include "LCDActuator.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
#include "Clock.h"

#include "Buttons.h"

#include "ScreenMenu.h"
#include "ScreenMeteo.h"
#include "ScreenClock.h"

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
  Clock_Setup();
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
    case MODE_MENU:
      Screen_Menu_Init();
      break;
    case MODE_METEO:
      Screen_Meteo_Init();
      break;
    case MODE_CLOCK:
      Screen_Clock_Init();
      break;

    }
  }

  Saved_Mode = Get_Current_Screen();

  Buttons_Loop();

  switch (Get_Current_Screen())
  {
  case MODE_MENU:
    Screen_Menu_Read_Buttons();
    break;
  case MODE_METEO:
    Screen_Meteo_Read_Buttons();
    break;
  case MODE_CLOCK:
    Screen_Clock_Read_Buttons();
    break;
  }

  //Slow loop
  Loop_Count++;
  if (Loop_Count > MAIN_LOOP_COUNT_LIMIT)
  {
    Loop_Count = 0;

    switch (Get_Current_Screen())
    {
    case MODE_MENU:
      Screen_Menu_Draw();
      break;
    case MODE_METEO:
      Screen_Meteo_Draw();
      break;
    case MODE_CLOCK:
      Screen_Clock_Draw();
      break;
    }
  }
}