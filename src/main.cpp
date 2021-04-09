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

