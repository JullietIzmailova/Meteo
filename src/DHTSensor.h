#include "src/libraries/DHT_sensor_library/DHT.h"

//true если сенсор доступен
//false если сенсор не доступен
bool DHT_Setup();

//true если сенсор доступен
//false если сенсор не доступен

bool DHT_Get_Status();

float DHT_Get_Temperature();

float DHT_Get_Humidity();

float DHT_Get_Heat_Index();
      