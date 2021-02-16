#include "config.h"
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
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);    
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