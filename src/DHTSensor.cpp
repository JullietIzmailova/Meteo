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

#include "config.h"
#include "Log.h"
#include "DHTSensor.h"

DHT *dht = nullptr;

float Temperature = -255;
float Humidity = 101;
float HeatIndex = 0;

//true если сенсор доступен
//false если сенсор не доступен
bool DHT_Setup()
{  
    dht = new DHT(DHT_PIN, DHT_TYPE);
    dht->begin();
    if (DHT_Get_Status())
    {
      Log("DHT setup complete");
      return true;
    }
    else 
    {
      Log("DHT setup failed");
      return false;
    }
}

bool DHT_Get_Status()
{
  float h = dht->readHumidity();

  if (isnan(h))
  {
    return false;
  }
  else 
  {
    return true;  
  }
}

float DHT_Get_Temperature()
{
  Temperature = dht->readTemperature();
  return Temperature;    
}

float DHT_Get_Humidity()
{
  Humidity = dht->readHumidity();
  return Humidity;  
}

float DHT_Get_Heat_Index()
{
  HeatIndex = dht->computeHeatIndex(false);
  return HeatIndex;
}
