/* ----------------------------------------------------------------------------
Ready IoT Solution - OWLOS Meteo
Copyright 2020, 2021 by:
- Julliet Izmailova
- Vitalii Glushchenko (cehoweek@gmail.com)
- Denys Melnychuk (meldenvar@gmail.com)
- Denis Kirin (deniskirinacs@gmail.com)
- Serhii Lehkii (sergey@light.kiev.ua)

This file is part of Ready IoT Solution - OWLOS

OWLOS is free software : you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

OWLOS is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with OWLOS. If not, see < https://www.gnu.org/licenses/>.

GitHub: https://github.com/KirinDenis/owlos

(Этот файл — часть Ready IoT Solution - OWLOS.

OWLOS - свободная программа: вы можете перераспространять ее и/или изменять
ее на условиях Стандартной общественной лицензии GNU в том виде, в каком она
была опубликована Фондом свободного программного обеспечения; версии 3
лицензии, любой более поздней версии.

OWLOS распространяется в надежде, что она будет полезной, но БЕЗО ВСЯКИХ
ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА или ПРИГОДНОСТИ ДЛЯ
ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ.
Подробнее см.в Стандартной общественной лицензии GNU.

Вы должны были получить копию Стандартной общественной лицензии GNU вместе с
этой программой. Если это не так, см. <https://www.gnu.org/licenses/>.)
--------------------------------------------------------------------------------------*/

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

int App_Mode = MODE_METEO;
int App_Saved_Mode = MODE_METEO;
int currentEdit = 0;
bool blink = false;
bool AnyKey = false;

//Setup section -------------------------------
void setup()
{
  Serial.begin(SERIAL_BAUD);
  delay(SETUP_DELAY);
  Log("Do setup...");

  LCD_Setup();
  LCD_Set_Light(true);

  LCDBigNumber_Setup();

  LCD_Print_CenterLine1("-= OWLOS Meteo =-");
  LCD_Print_CenterLine3("Please wait...");
  delay(LOGO_DELAY);

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

  if (Get_Button1_ShortPress() || Get_Button2_ShortPress() || Get_Button3_ShortPress())
  {
    AnyKey = true;
  }

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
