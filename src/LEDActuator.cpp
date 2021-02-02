#include "config.h"
#include "LEDActuator.h"

bool LED_RED_Setup()
{
    pinMode(LED_RED_PIN, OUTPUT);
}

bool LED_GREEN_Setup()
{
    pinMode(LED_GREEN_PIN, OUTPUT);
}

bool LED_YELLOW_Setup()
{
    pinMode(LED_YELLOW_PIN, OUTPUT);
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