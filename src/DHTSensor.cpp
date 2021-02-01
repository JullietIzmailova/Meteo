#include "DHTSensor.h"
#include "config.h"

DHT *dht = nullptr;

//true если сенсор доступен
//false если сенсор не доступен
bool DHT_Setup()
{
    dht = new DHT(DHT_PIN, DHT_TYPE);
    dht->begin();
    return DHT_Get_Status();
}

bool DHT_Get_Status()
{
  float h = dht->readHumidity();

  if (isnan(h))
  {
    return false;
  }
  else 
  {
    return true;  
  }
}

float DHT_Get_Temperature()
{
  return dht->readTemperature();    
}

float DHT_Get_Humidity()
{
  return dht->readHumidity();  
}

float DHT_Get_HeatIndex()
{
  return dht->computeHeatIndex(false);
}
