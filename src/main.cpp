//Исходные коды метеостанции
#include "DHTSensor.h"
#include "LCDActuator.h"
    
//Setup section -------------------------------
void setup()
{
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  DHT_Setup();

  LCD_Setup();
  LCD_Set_Light(true);
  LCD_Print_Line1("Hello");
  LCD_Print_Line3("wait...");
}
//Loop Section -------------------------------
void loop()
{
  // Wait a few seconds between measurements.
  delay(2000);
  LCD_Clear();

  float hic = DHT_Get_Heat_Index();

  if (hic > 27)
  {
    if (hic > 30)
    {
      digitalWrite(6, 1);
      digitalWrite(4, 0);
      digitalWrite(3, 0);
    }
    else
    {
      digitalWrite(6, 0);
      digitalWrite(4, 1);
      digitalWrite(3, 0);
    }
  }
  else
  {
    digitalWrite(6, 0);
    digitalWrite(4, 0);
    digitalWrite(3, 1);
  }
  int L = analogRead(A5);

  LCD_Print_Line1("T " + String(DHT_Get_Temperature()));
  LCD_Print_Line2(" " + String(DHT_Get_Humidity()));
  LCD_Print_Line3(" %  H " + String(hic));
  LCD_Print_Line4(" L " + String(L));


/*
  Serial.println(L);
  Serial.print(F("Humidity: "));
  Serial.print(DHTHumidity());
  Serial.print(F(" % Temperature: "));
  Serial.print(DHTTemperature());
  Serial.print(F(" °C "));
  Serial.print(hic);
*/
}