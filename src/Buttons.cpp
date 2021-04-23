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
#include "log.h"
#include "Buttons.h"
#include <Arduino.h>

// BUTTON 1
// Button events
bool Button1_EventShortPress = false;
bool Button1_EventLongPress = false;

// BUTTON2
// Button events
bool Button2_EventShortPress = false;
bool Button2_EventLongPress = false;

// BUTTON3
// Button events
bool Button3_EventShortPress = false;
bool Button3_EventLongPress = false;

// Button states
bool Button1_Pressed = false;
bool Button1_LastState = false;
int Button1_StateTicker = 0;


// Button states
bool Button2_Pressed = false;
bool Button2_LastState = false;
int Button2_StateTicker = 0;

// Button states
bool Button3_Pressed = false;
bool Button3_LastState = false;
int Button3_StateTicker = 0;

bool Get_Button1_ShortPress()
{
  return Button1_EventShortPress;
}

bool Get_Button1_LongPress()
{
  return Button1_EventLongPress;
}

bool Get_Button2_ShortPress()
{
  return Button2_EventShortPress;
}

bool Get_Button2_LongPress()
{
  return Button2_EventLongPress;
}

bool Get_Button3_ShortPress()
{
  return Button3_EventShortPress;
}

bool Get_Button3_LongPress()
{
  return Button3_EventLongPress;
}


void Buttons_Setup()
{
  //  Setup buttons
  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
  pinMode(BUTTON3_PIN, INPUT);    
  Log("BUTTONS setup complete");
}

void ReadButtonStates()
{
  Button1_Pressed = digitalRead(9);
  Button2_Pressed = digitalRead(10);
  Button3_Pressed = digitalRead(11);

  // ... all buttons
}

void ResetEvents()
{
  Button1_EventShortPress = false;
  Button1_EventLongPress = false;

  Button2_EventShortPress = false;
  Button2_EventLongPress = false;

  Button3_EventShortPress = false;
  Button3_EventLongPress = false;
}

void Buttons_Loop()
{
  ReadButtonStates();
  ResetEvents();

  // _________________Raise button events______________________________

  // _______Button1 events_________
  if (Button1_LastState == Button1_Pressed)
  {
    Button1_StateTicker++;
  }
  else
  {
    Button1_StateTicker = 0;
  }

  if (Button1_Pressed == true)
  {

    if (Button1_StateTicker == BUTTON_SHORTPRESS_LIMIT)
    {
      Button1_EventShortPress = true;
    }

    if (Button1_StateTicker == BUTTON_LONGPRESS_LIMIT)
    {
      Button1_EventLongPress = true;
    }
  }

  Button1_LastState = Button1_Pressed;

  //______________________________

  // _______Button2 events_________

  if (Button2_LastState == Button2_Pressed)
  {
    Button2_StateTicker++;
  }
  else
  {
    Button2_StateTicker = 0;
  }

  if (Button2_Pressed == true)
  {

    if (Button2_StateTicker == BUTTON_SHORTPRESS_LIMIT)
    {
      Button2_EventShortPress = true;
    }

    if (Button2_StateTicker == BUTTON_LONGPRESS_LIMIT)
    {
      Button2_EventLongPress = true;
    }
  }

  Button2_LastState = Button2_Pressed;

  //______________________________

  // _______Button3 events_________
  if (Button3_LastState == Button3_Pressed)
  {
    Button3_StateTicker++;
  }
  else
  {
    Button3_StateTicker = 0;
  }

  if (Button3_Pressed == true)
  {

    if (Button3_StateTicker == BUTTON_SHORTPRESS_LIMIT)
    {
      Button3_EventShortPress = true;
    }

    if (Button3_StateTicker == BUTTON_LONGPRESS_LIMIT)
    {
      Button3_EventLongPress = true;
    }
  }

  Button3_LastState = Button3_Pressed;

  //______________________________
}