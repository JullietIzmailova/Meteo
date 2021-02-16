#include "config.h"
#include "LIGHTActuator.h"
#include <Arduino.h>
#include "Log.h"

bool LIGHT_Setup()
{
#ifdef LIGHT_SENSOR_ANALOG_PIN    
    if(LIGHT_SENSOR_ANALOG_Setup()) {
        LIGHT_SENSOR_ANALOG_Setup();
        Log("LIGHT sensor analog setup complete");
         return true;          
    }    
#endif    
#ifndef LIGHT_SENSOR_ANALOG_PIN    
    if(LIGHT_SENSOR_DIGITAL_Setup()){
        LIGHT_SENSOR_DIGITAL_Setup();
        Log("LIGHT sensor digital setup complete");
        return true;
    }
#endif    
    Log("LIGHT sensor setup failed");
    return false;
}

#ifdef LIGHT_SENSOR_ANALOG_PIN    
bool LIGHT_SENSOR_ANALOG_Setup()
{
    if(LIGHT_SENSOR_ANALOG_PIN!=-1){
        pinMode(LIGHT_SENSOR_ANALOG_PIN, INPUT);
        return true;
    }
    else {
        return false;
    }    
}
#endif

#ifndef LIGHT_SENSOR_ANALOG_PIN    
bool LIGHT_SENSOR_DIGITAL_Setup()
{
    if(LIGHT_SENSOR_DIGITAL_PIN!=-1){
        pinMode(LIGHT_SENSOR_DIGITAL_PIN, INPUT);
        return true;    
    }
    else {
        return false;
    }
}
#endif

float LIGHT_GET_data()
{
#ifdef LIGHT_SENSOR_ANALOG_PIN    
    if(LIGHT_SENSOR_ANALOG_PIN!=-1){
        return analogRead(LIGHT_SENSOR_ANALOG_PIN) * 0.48 / 100; //Конвертируем уровень аналогового сигнала в Вольты        
    }
#endif

#ifndef LIGHT_SENSOR_ANALOG_PIN    
    if(LIGHT_SENSOR_DIGITAL_PIN!=1){
        if(digitalRead(LIGHT_SENSOR_DIGITAL_PIN)==HIGH){
            return 1;
        }
        if(digitalRead(LIGHT_SENSOR_DIGITAL_PIN)==LOW){
            return 0;
        }
    }            
#endif    
    return -1;
}
