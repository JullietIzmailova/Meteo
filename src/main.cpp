//Исходные коды метеостанции
#include "config.h"
#include "log.h"
#include "DHTSensor.h"
#include "LCDActuator.h"
#include "LEDActuator.h" 
#include "LIGHTActuator.h"

//Setup section -------------------------------
void setup()
{  
  Serial.begin(SERIAL_BAUD);
  delay(SETUP_DELAY);
  
  Log("Do setup...");
  
  LIGHT_Setup();

  LED_Setup();

  DHT_Setup();

  LCD_Setup();
  LCD_Set_Light(true);
  LCD_Print_Line1("Hello");
  LCD_Print_Line3("wait...");


  Log("Setup complete");
}
//Loop Section -------------------------------
void loop()
{
  // Wait a few seconds between measurements.
  delay(MAIN_LOOP_DELAY);

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

  int L = analogRead(A5);

  int LIGHT_data = LIGHT_GET_data(); 

  LCD_Print_Line1("Temp ====> " + String(DHT_Get_Temperature()) + char(223) + "C");
  LCD_Print_Line2("Hum =====> " + String(DHT_Get_Humidity()) + " %");
  LCD_Print_Line3("curr Hi => " + String(current_heat_index));
  LCD_Print_Line4("L =======> " + String(L));
}