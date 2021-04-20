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

GitHub: https://github.com/KirinDenis/Meteo

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
#include <Arduino.h>
#include "config.h"
#include "DHTSensor.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
#include "Clock.h"

#include "Log.h"

#define OK_ANSWER "OK: "
#define PUBLISH_ANSWER "PUB: "
#define CANCEL_ANSWER "CANCEL: "
#define ERROR_ANSWER "ERROR: "

#define TOKENS_SIZE 10

extern int GreenLedData;
extern int YellowLedData;
extern int RedLedData;
extern int BuzzerData;

extern String Date;
extern String Time;
extern String Alarm;
extern bool AlarmStatus;

extern float Temperature;
extern float Humidity;
extern float HeatIndex;

String SerialInput;

bool busy = false;

void UARTSend(String topic, String payload)
{
  Serial.print(PUBLISH_ANSWER + topic + " " + payload + "\n\n");
}

void UARTSendError(String topic, String payload)
{
  Serial.print(ERROR_ANSWER + topic + "\n");
  Serial.print(payload + "\n\n");
}

void UARTSendOK(String topic, const String &payload)
{
  Serial.print(OK_ANSWER + topic + " " + String(payload.length()) + "\n");
  Serial.print(payload);
  Serial.print("\n\n");
}

void UARTSendADP(String topic)
{
  //const String payload = "PF:RLed\nid=RLed//r\nd=" + String(RedLedData) + "//isPF:GLed\nid=GLed//r\nd="  + String(GreenLedData) + "//is\nPF:YLed\nid=YLed//r\nd=" + String(YellowLedData) + "//is\nPF:Beep\nid=Beep//r\nd=" + String(BuzzerData) + "//is\nPF:Clock\nid=Clock//r\nd=" + Clock_Get_Date() + "//s\nt=" + Clock_Get_Time() + "//s\na=" + Clock_Get_Alarm1() + "//s\nas=" + Clock_Get_Alarm1_Status()  + "//sb\n\0";
  //"PF:DHT\nid=DHT//r\nt=" + DHT_Get_Temperature() + "//rs\nh=" + DHT_Get_Humidity() + "//rs\nht=" + DHT_Get_Heat_Index() + "//rs\n\0";

  Serial.print(OK_ANSWER + topic + "\n");

  Serial.print("PF:RL\nd=" + String(RedLedData) + "//i\nPF:GL\nd=" + String(GreenLedData) + "//i\n");      
  delay(20);

  Serial.print("PF:YL\nd=" + String(YellowLedData) + "//i\nPF:BZ\nd=" + String(BuzzerData) + "//i\n");    
  delay(20);

  Serial.print("PF:CL\nd=" + Date + "//\nt=" + Time + "//\na=" + Alarm + "//\nas=" + AlarmStatus + "//b\n");    
  delay(20);

  Serial.print("PF:DHT\nt=" + String(Temperature) + "//r\nh=" + String(Humidity) + "//r\ni=" + String(HeatIndex) + "//r\n\0");      
  delay(20);

  Serial.print("\n\n");
}

void UARTRecv(String command)
{
  if (command.length() > 0)
  {
    command.replace("\n", "");
    //--- Tokenize command
    String token[TOKENS_SIZE];
    int count = 0;
    while (command.indexOf(" ") != -1)
    {
      if (count > TOKENS_SIZE - 2)
      {
        break;
      }
      token[count] = command.substring(0, command.indexOf(" "));
      command.replace(token[count] + " ", "");
      count++;
    }

    command.replace(" ", "");
    token[count] = command;
    count++;
    //--- ENDOF Tokenize command

    if ((count > 0) && (token[0].length() > 0))
    {
      token[0].toUpperCase();
      if (token[0].equals("AT+ADP?"))
      {
        UARTSendADP(token[0]);
      }    
    else 
    //GET driver propery
    if (token[0].equals("AT+DP?"))
    {
      if (count > 2)
      {
        token[1].toLowerCase();
        token[2].toLowerCase();
        String result = "";
        if ((token[1].equals("rl")) && (token[2].equals("d")))
        {
          result = String(RedLedData);
        }
        else if ((token[1].equals("yl")) && (token[2].equals("d")))
        {
          result = String(YellowLedData);
        }
        else if ((token[1].equals("gl")) && (token[2].equals("d")))
        {
          result = String(GreenLedData);
        }
        else if ((token[1].equals("bz")) && (token[2].equals("d")))
        {
          result = String(BuzzerData);
        }
        else if (token[1].equals("cl"))
        {
          if (token[2].equals("d"))
          {
            result = Clock_Get_Date();
          }
          else if (token[2].equals("t"))
          {
            result = Clock_Get_Time();
          }
          else if (token[2].equals("a"))
          {
            result = Clock_Get_Alarm1();
          }
          else if (token[2].equals("as"))
          {
            result = String(Clock_Get_Alarm1_Status());
          }
        }
        else if (token[1].equals("dht"))
        {
          if (token[2].equals("t"))
          {
            result = String(DHT_Get_Temperature());
          }
          else if (token[2].equals("h"))
          {
            result = String(DHT_Get_Humidity());
          }
          else if (token[2].equals("i"))
          {
            result = String(DHT_Get_Heat_Index());
          }
        }
        if (result.length() > 0)
        {
          UARTSendOK(token[0], result);
        }
        else
        {
          UARTSendError("Unknow driver or property", token[1] + " " + token[2]);
        }
      }
      else
      {
        UARTSendError("Bad parameters", "");
      }
    }
    else 
    //SET driver propery
    if (token[0].equals("AT+DP"))
    {
      if (count > 3)
      {
        
        token[1].toLowerCase();
        token[2].toLowerCase();
        Serial.print(token[1] + " " + token[2]);
        String result = "";
        if ((token[1].equals("rl")) && (token[2].equals("d")))
        {
          LED_Red_Set_Light(atoi(token[3].c_str()));
          result = "1"; //1 is success
        }
        else if ((token[1].equals("yl")) && (token[2].equals("d")))
        {
          LED_Yellow_Set_Light(atoi(token[3].c_str()));
          result = "1";
        }
        else if ((token[1].equals("gl")) && (token[2].equals("d")))
        {
          LED_Green_Set_Light(atoi(token[3].c_str()));
          result = "1";
        }
        else if ((token[1].equals("bz")) && (token[2].equals("d")))
        {
          BUZZER_Set_sound(atoi(token[3].c_str()));
          result = "1";
        }
        else if (token[1].equals("cl"))
        {
          if (token[2].equals("d"))
          {
            result = "0";
          }
          else if (token[2].equals("t"))
          {
            result = "0";
          }
          else if (token[2].equals("a"))
          {
            result = "0";
          }
          else if (token[2].equals("as"))
          {
            Serial.print(atoi(token[3].c_str()));
            Clock_Set_Alarm1_Status(atoi(token[3].c_str()));
            result = "1";
          }
        }

        if (result.length() > 0)
        {
          UARTSendOK(token[0], result);
        }
        else
        {
          UARTSendError("Unknow driver or property", token[1] + " " + token[2]);
        }
      }
      else
      {
        UARTSendError("Bad parameters", "");
      }
    }
    else
    {
      UARTSendError("unknown command", "");
    }
    }
    else 
    {
      UARTSendError("Bad command", "");
    }
  }
}

void UARTLoop()
{
  if (busy)
  {
    SerialInput = "";
    LED_Red_Set_Light(true);
    delay(200);
    LED_Red_Set_Light(false);
  }
  else if (Serial.available() > 0)
  {
    String currentStr = Serial.readString();
    SerialInput += currentStr;
    if (SerialInput.indexOf('\r') != -1)
    {

      busy = true;
      //Serial.flush();
      SerialInput.replace("\r", "");
      SerialInput.replace("\n", "");
      UARTRecv(SerialInput);
      SerialInput = "";

      Serial.flush();
      Serial.clearWriteError();
      busy = false;
    }
  }
}