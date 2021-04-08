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
	->Set time - появляется экран редактирования времени - выход длительное нажатие меню Button1. 
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
#include "LCDBigNumbers.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
#include "Clock.h"

#include "UART.h"
#include "Buttons.h"

#include "ScreenMeteo.h"
#include "ScreenClock.h"
#include "ScreenSetClock.h"
#include "ScreenAlarm.h"

int Loop_Count = MAIN_LOOP_COUNT_LIMIT;

int App_Mode = MODE_CLOCK;
int App_Saved_Mode = MODE_METEO;

//Setup section -------------------------------
void setup()
{
  Serial.begin(SERIAL_BAUD);
  delay(SETUP_DELAY);
  Log("Do setup...");

  LCD_Setup();
  LCD_Set_Light(true);

  LCDBigNumber_Setup();

  LCD_Print_CenterLine1("Hello Meteo");
  LCD_Print_CenterLine3("Please wait...");

#ifdef DEBUG_SETUP
  delay(DEBUG_SETUP_DELAY);

  Buttons_Setup();
  LCD_Print_CenterLine2("Buttons setup...OK");
  delay(DEBUG_SETUP_DELAY);

  BUZZER_Setup();
  LCD_Print_CenterLine2("Buzzer setup...OK");
  delay(DEBUG_SETUP_DELAY);

  LIGHT_Setup();
  LCD_Print_CenterLine2("Light setup...OK");
  delay(DEBUG_SETUP_DELAY);

  LED_Setup();
  LCD_Print_CenterLine2("Led setup...OK");
  delay(DEBUG_SETUP_DELAY);

  DHT_Setup();
  LCD_Print_CenterLine2("DHT setup...OK");
  delay(DEBUG_SETUP_DELAY);

  Clock_Setup();
  LCD_Print_CenterLine2("Clock setup...OK");
  delay(DEBUG_SETUP_DELAY);
  LCD_Print_CenterLine2("");
  LCD_Print_CenterLine3("Setup complete");
  delay(DEBUG_SETUP_DELAY);
  Log("Setup complete");
#else
  Buttons_Setup();

  BUZZER_Setup();

  LIGHT_Setup();

  LED_Setup();

  DHT_Setup();

  Clock_Setup();
#endif
}

int Saved_Mode = MODE_NULL;


void loop()
{
  // Wait a few seconds between measurements.
  delay(MAIN_LOOP_DELAY);

  UARTLoop();

  Buttons_Loop();


  App_Saved_Mode = App_Mode;
  if ((App_Mode != MODE_SET_METEO) && (App_Mode != MODE_SET_CLOCK) && (App_Mode != MODE_SET_ALARM))
  {
     if (Get_Button2_ShortPress() == true)
     {
       if (App_Mode > MODE_METEO)
       {
         App_Mode--;
       }
       else 
       {
         App_Mode = MODE_ALARM;
       }
     }

     if (Get_Button3_ShortPress() == true)
     {
       if (App_Mode < MODE_ALARM)
       {
         App_Mode++;
       }
       else 
       {
         App_Mode = MODE_METEO;
       }
     }

  }


  if (App_Saved_Mode != App_Mode) // is previous state of application the same?
  {
    switch (App_Mode)
    {
    case MODE_METEO:
      Screen_Meteo_Init();
      break;
    case MODE_CLOCK:
      Screen_Clock_Init();
      break;
    case MODE_ALARM:
      Screen_Alarm_Init();
      break;
    case MODE_SET_CLOCK:
      Screen_SetClock_Init();
      break;
    }
  }

  switch (App_Mode)
  {
  case MODE_METEO:
  case MODE_SET_METEO:
    Screen_Meteo_Read_Buttons();
    break;
  case MODE_CLOCK:
  case MODE_SET_CLOCK:  
    Screen_Clock_Read_Buttons();
    break;
  case MODE_ALARM:
  case MODE_SET_ALARM:  
    Screen_Alarm_Read_Buttons();
    break;
  }

  //Slow loop
  Loop_Count++;
  if (Loop_Count > MAIN_LOOP_COUNT_LIMIT)
  {
    Loop_Count = 0;

    switch (App_Mode)
    {
    case MODE_METEO:
    case MODE_SET_METEO:
      Screen_Meteo_Draw();
      break;
    case MODE_CLOCK:
    case MODE_SET_CLOCK:  
      Screen_Clock_Draw();
      break;
    case MODE_ALARM:
    case MODE_SET_ALARM:  
      Screen_Alarm_Draw();
      break;
    }
  }
}

