#include "config.h"
#include "log.h"
#include "BUZZERActuator.h"
#include <Arduino.h>

bool BUZZER_Setup(){
    pinMode(BUZZER_PIN, OUTPUT);
    Log("BUZZER setup complete");
    return true;
}

void BUZZER_Set_sound(bool on){
        if(on)
    {
        digitalWrite(BUZZER_PIN, HIGH);
    }
    else
    {
        digitalWrite(BUZZER_PIN, LOW);
    }
}