#include "src/libraries/DHT_sensor_library/DHT.h"

//true если сенсор доступен
//false если сенсор не доступен
bool DHTInit();

//true если сенсор доступен
//false если сенсор не доступен
bool DHTAvailable();

float DHTTemperature();

float DHTHumidity();

float DHTHeatIndex();