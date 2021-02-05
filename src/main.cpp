//Исходные коды метеостанции
#include "config.h"
#include "log.h"
#include "DHTSensor.h"
#include "LCDActuator.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"

//Setup section -------------------------------
void setup()
{
  Serial.begin(SERIAL_BAUD);
  delay(SETUP_DELAY);

  Log("Do setup...");

  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

  BUZZER_Setup();

  LIGHT_Setup();

  LED_Setup();

  DHT_Setup();

  LCD_Setup();
  LCD_Set_Light(true);
  LCD_Print_Line1("Hello");
  LCD_Print_Line3("wait...");

  Log("Setup complete");
}

#define MENU_ITEMS_SIZE 2
String Menu_Items[] = {"Item 1", "Item 2", "Item 3"};

int Menu_Selected_Index = 0;
int Save_Menu_Selected_Index = -1;

#define DATA_MODE 0
#define MENU_MODE 1
int Screen_Mode = DATA_MODE;

int Loop_Count = MAIN_LOOP_COUNT_LIMIT;
int Button1_Pressed_Timer = 0;
int Button2_Pressed_Timer = 0;
int Button3_Pressed_Timer = 0;
//Loop Section -------------------------------
void loop()
{
  // Wait a few seconds between measurements.
  delay(MAIN_LOOP_DELAY);

  int a = digitalRead(9);

  if (a == HIGH)
  {
    Button1_Pressed_Timer++;
    //BUZZER_Set_sound(true);
  }
  else
  {
    Button1_Pressed_Timer = 0;
    //BUZZER_Set_sound(false);
  }

  if (Button1_Pressed_Timer != 0)
  {
    if (Button1_Pressed_Timer < 100)
    {      
      //Log("Short press");
    }
    else
    {
      //Log("Long press");
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
      Button1_Pressed_Timer = 0;
    }
  }

  if (digitalRead(10) == HIGH)
  {
    Button2_Pressed_Timer++;
    if (Button2_Pressed_Timer > 10)
    {
       Menu_Selected_Index--;
       Button2_Pressed_Timer = 0;
    }
  }
  else 
  {
    Button2_Pressed_Timer = 0;
  }

  if (digitalRead(11) == HIGH)
  {
    Button3_Pressed_Timer++;
    if (Button3_Pressed_Timer > 10)
    {
      Menu_Selected_Index++;
      Button3_Pressed_Timer = 0;
    }
  }
  else 
  {
    Button3_Pressed_Timer = 0;
  }


  //Draw menu items
  if (Screen_Mode == MENU_MODE)
  {
    
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