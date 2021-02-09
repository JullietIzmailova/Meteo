#include <Arduino.h>
#include "Log.h"

inline void Log(String text)
{
#ifdef DBG_CONSOLE_ENABLE
    Serial.println(text);
#endif
}