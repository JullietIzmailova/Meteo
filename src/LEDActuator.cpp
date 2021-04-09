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
#include "LEDActuator.h"
#include <Arduino.h>

bool LED_Setup()
{
    LED_RED_Setup();
    LED_GREEN_Setup();
    LED_YELLOW_Setup();
#ifdef DEBUG_SETUP
    LED_Only_Red_Set_Light();
    delay(DEBUG_SETUP_DELAY);
    LED_Only_Yellow_Set_Light();
    delay(DEBUG_SETUP_DELAY);
    LED_Only_Green_Set_Light();
    delay(DEBUG_SETUP_DELAY);
    LED_Green_Set_Light(false);    
#endif
    Log("LED setup complete");
    return true;
}


bool LED_RED_Setup()
{
    pinMode(LED_RED_PIN, OUTPUT);
    return true;
}

bool LED_GREEN_Setup()
{
    pinMode(LED_GREEN_PIN, OUTPUT);
    return true;
}

bool LED_YELLOW_Setup()
{
    pinMode(LED_YELLOW_PIN, OUTPUT);
    return true;
}


void LED_Red_Set_Light(bool on)
{
    if(on)
    {
        digitalWrite(LED_RED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_RED_PIN, LOW);
    }
    
}

void LED_Green_Set_Light(bool on)
{
    if(on)
    {
        digitalWrite(LED_GREEN_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_GREEN_PIN, LOW);
    }
    
}

void LED_Yellow_Set_Light(bool on)
{
    if(on)
    {
        digitalWrite(LED_YELLOW_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_YELLOW_PIN, LOW);
    }    
}

void LED_Only_Red_Set_Light()
{
    LED_Red_Set_Light(true);
    LED_Green_Set_Light(false);
    LED_Yellow_Set_Light(false);
}

void LED_Only_Green_Set_Light()
{
    LED_Red_Set_Light(false);
    LED_Green_Set_Light(true);
    LED_Yellow_Set_Light(false);
}

void LED_Only_Yellow_Set_Light()
{
    LED_Red_Set_Light(false);
    LED_Green_Set_Light(false);
    LED_Yellow_Set_Light(true);
}