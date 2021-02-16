#include "config.h"
#include "log.h"
#include "BUZZERActuator.h"
#include <Arduino.h>

bool BUZZER_Setup()
{
    pinMode(BUZZER_PIN, OUTPUT);
#ifdef DEBUG_SETUP
    BUZZER_Set_sound(true);
    delay(DEBUG_SETUP_DELAY);
    BUZZER_Set_sound(false);
#endif

    Log("BUZZER setup complete");
    return true;
}

void BUZZER_Set_sound(bool on)
{
    if (on)
    {
        digitalWrite(BUZZER_PIN, HIGH);
    }
    else
    {
        digitalWrite(BUZZER_PIN, LOW);
    }
}
