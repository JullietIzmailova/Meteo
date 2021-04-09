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
    else if (s.indexOf("AT+SDT") == 0)
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
      String time = date.substring(date.indexOf(";") + 1, date.length()); //21:32:40
      Log("|" + time + "|");
      date = date.substring(0, date.indexOf(";")); //Mar 3 2021
      Log("|" + date + "|");

      Clock_Set_DateTime(date, time);
    }
    else
    {
      Serial.println("Unknown Command");
    }
  }
}