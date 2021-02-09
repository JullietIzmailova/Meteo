/* Архитектура меню 
Buttons map, слева на право:
- Button1 - Mode - Режим  btn[0]
- Button2 - Left - Влево (Вверх) btn[1]
- Button3 - Right - Вправо (Вниз) btn[2]

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

#include "GUI_Meteo.h"
#include "GUI_MENU.h"

//---comment this line in release version----
#define DBG_CONSOLE_ENABLE
//-------------------------------------------

#define MENU_ITEMS_SIZE 2
String Menu_Items[] = {"Item 1", "Item 2", "Item 3"};

int Menu_Selected_Index = 0;
int Save_Menu_Selected_Index = -1;

#define DATA_MODE 0
#define MENU_MODE 1
int Screen_Mode = DATA_MODE;

int Loop_Count = MAIN_LOOP_COUNT_LIMIT;

struct TButton
{
  // Button states
  bool Pressed = false;
  bool LastState = false;
  int  StateTicker = 0;

  // Button events
  bool EventShortPress = false;
  bool EventLongPress = false;

  // Pointers to Event handlers of buttons. 
  // Handler should be out to a separate unit and named: DoShortPress_<UnitName> , DoLongPress_<UnitName>
  void * DoShortPress;
  void * DoLongPress;    
};

TButton btn[3] = {};

void * Repaint;    
 

// button setup
#define BUTTON_SHORTPRESS_LIMIT 10
#define BUTTON_LONGPRESS_LIMIT 100

//--------------------------------------------------------------------------------
//-------------------------------MAIN Loop Section -------------------------------
//--------------------------------------------------------------------------------

void ReadButtonStates()
{
    btn[0].Pressed= digitalRead(9);
    btn[1].Pressed = digitalRead(10);
    btn[2].Pressed = digitalRead(11);
}



void RaiseEvents()
{
  int i;

  // _________________Raise button events______________________________

  for (i = 0; i < 3; i++)
  {
      // Reset events

      btn[i].EventShortPress = false;
      btn[i].EventLongPress = false;

      // Verify if we need raise new events

      if (btn[i].LastState == btn[i].Pressed)  // if button state is the same
      {
          btn[i].StateTicker++;
      }
      else  // button state was changed
      {
          if (btn[i].Pressed = false) // if KEY_UP
          {
              if ((btn[i].StateTicker > BUTTON_SHORTPRESS_LIMIT) && (btn[i].StateTicker < BUTTON_LONGPRESS_LIMIT))
              {
                  btn[i].EventShortPress = true;
              }
          }
          btn[i].StateTicker = 0;
      }

      if ((btn[i].Pressed) && (btn[i].StateTicker == BUTTON_LONGPRESS_LIMIT))
      {
          btn[i].EventLongPress = true;
      }
      btn[i].LastState =btn[i].Pressed;
  }
}

//Setup section -------------------------------
void setup()
{
  Serial.begin(SERIAL_BAUD);
  delay(SETUP_DELAY);

  Log("Do setup...");

  //  Setup buttons
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

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

// by default user see Meteo mode

  btn[0].DoShortPress()=DoShortPress_GUI_METEO;
  btn[0].DoLongPress()=DoLongPress_GUI_METEO;

  //btn[1].DoShortPress()=DoShortPress_GUI_MENU;
  //btn[1].DoLongPress()=DoLongPress_GUI_MENU;

  Repaint()=Repaint_GUI_METEO;
}

void loop()
{
  // Wait a few seconds between measurements.
  delay(MAIN_LOOP_DELAY);

  ReadButtonStates();

  RaiseEvents();

  // Call handler for every button, if necessary
  for(i=0;i<3;i++)
  {
    if (btn[i].EventShortPress)
    {
      btn[i].DoShortPress();
    }

    if (btn[i].EventLongPress)
    {
      btn[i].DoLongPress();
    }
  }

  //Slow loop
  Loop_Count++;
  if (Loop_Count > MAIN_LOOP_COUNT_LIMIT)
  {
    Repaint();
  }
}