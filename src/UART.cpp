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

void UARTSendOK(String topic, const String & payload)
{
  
  Serial.print(OK_ANSWER + topic + " " + String(payload.length()) + "\n");
  Serial.print(payload);
/*
  String payloadStr = String(payload.c_str());
  Serial.print(String(payloadStr.length()) + "\n");
  while (payloadStr.indexOf("\n") != -1)
  {
    String sendStr = payloadStr.substring(0, payloadStr.indexOf("\n") + 1);
    Serial.print(sendStr);
    delay(10);
    payloadStr.replace(sendStr, "");
  }
  */
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
        // UARTSendOK(token[0], LED_Get_Properties());
        UARTSendOK(token[0], "PF:RLed\nid=rLed//r\nv=" + String(RedLedData) + "//is\nPF:GLed\nid=gLed//r\nv=" + String(GreenLedData) + "//is\PF:yLed\nid=yLed//r\nv=" + String(YellowLedData) + "//is\n\0");
      }
    }
    else
    {
      UARTSendError(token[0], "empty command");
    }
  }

  /*
    if (s.equals("AT+B\n"))
    {
      BUZZER_Set_sound(true);
      delay(2000);
      BUZZER_Set_sound(false);
    }
    else if (s.equals("AT+T?\n"))
    {
      Serial.println("OK AT+T? " + String(DHT_Get_Temperature()));
    }
    else if (s.equals("AT+H?\n"))
    {
      Serial.println("OK AT+H? " + String(DHT_Get_Humidity()));
    }
    else if (s.equals("AT+I?\n"))
    {
      Serial.println("OK AT+I? " + String(DHT_Get_Heat_Index()));
    }
    else if (s.equals("AT+L?\n"))
    {
      Serial.println("OK AT+L? " + String(LIGHT_GET_data()));
    }
    else if (s.equals("AT+ADP?"))
    {
      
      Serial.print(OK_ANSWER + String("AT+ADP?\n"));    
      Serial.print(LED_Get_Properties() + "\n\n");              
    }
    else
    {
      Serial.println("Unknown Command");
    }  
    */
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
      Serial.flush();
      SerialInput.replace("\r", "");
      SerialInput.replace("\n", "");
      UARTRecv(SerialInput);
      SerialInput = "";
      busy = false;

      Serial.flush();
      Serial.clearWriteError();
    }
  }
}