#include <Arduino.h>
#include "DHTSensor.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
#include "Clock.h"

#include "Log.h"


void UARTLoop()
{
  if (Serial.available())
  {
     String s = Serial.readString();
     String origin = s;
     s.toUpperCase();

     if (s.equals("AT+B\n")) 
     {
       BUZZER_Set_sound(true);
       delay(2000);
       BUZZER_Set_sound(false);
     }
     else  
     if (s.equals("AT+T?\n"))     
     {
       Serial.println(DHT_Get_Temperature());
     }
     else
     if (s.equals("AT+H?\n"))     
     {
       Serial.println(DHT_Get_Humidity());
     }
     else 
     if (s.indexOf("AT+SDT") == 0)     
     {
       //AT+SDT Mar 03 2021;21:55:40    
       //AT+SDT Mar 03 2021;21:32:40    
       //          
       //AT+SDT Dec 03 2024;23:59:40
       //           ^2 char если меньше добавляется пробел или ноль       
       Log(__DATE__);
       Log(__TIME__);
       Log(origin);
       String date = origin.substring(s.indexOf(" ") + 1); //Mar 3 2021;21:32:40       
       Log("|" + date + "|");
       String time = date.substring(date.indexOf(";")+1, date.length()); //21:32:40       
       Log("|" + time + "|");
       date = date.substring(0, date.indexOf(";")); //Mar 3 2021
       Log("|" + date + "|");

       Clock_Set_DateTime(date, time);

     }
     else 
      {
        Serial.println ("Unknown Command");
      }
    
  }

}