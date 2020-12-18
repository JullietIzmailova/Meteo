#include "DHTSensor.h"
#include "config.h"

DHT *dht = nullptr;

//true если сенсор доступен
//false если сенсор не доступен
bool DHTInit()
{
    dht = new DHT(DHTPIN, DHTTYPE);
    dht->begin();
    return DHTAvailable();
}

bool DHTAvailable()
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

float DHTTemperature()
{
  return dht->readTemperature();    
}

float DHTHumidity()
{
  return dht->readHumidity();  
}

float DHTHeatIndex()
{
  return dht->computeHeatIndex(false);
}
