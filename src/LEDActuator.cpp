#include "config.h"
#include "LEDActuator.h"
#include <Arduino.h>

bool LED_Setup()
{
    LED_RED_Setup();
    LED_GREEN_Setup();
    LED_YELLOW_Setup();
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