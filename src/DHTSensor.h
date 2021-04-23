#include "src/libraries/DHT_sensor_library/DHT.h"

//true если сенсор доступен
//false если сенсор не доступен
#define NO_DHT "DHT error [0x15]"
#define NO_DHT_LED_Color "yellow"
#define NO_DHT_LED_Blink 3
#define NO_DHT_Long_Signals 3
#define NO_DHT_Short_Signals 3

bool DHT_Setup();

//true если сенсор доступен
//false если сенсор не доступен

bool DHT_Get_Status();

float DHT_Get_Temperature();

float DHT_Get_Humidity();

float DHT_Get_Heat_Index();
      