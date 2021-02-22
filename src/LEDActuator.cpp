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