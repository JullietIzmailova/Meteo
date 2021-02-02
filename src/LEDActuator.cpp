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