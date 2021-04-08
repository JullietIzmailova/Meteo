#include <Arduino.h>
#include "Log.h"

void Log(String text)
{
    Serial.println("LOG: " + text);
}