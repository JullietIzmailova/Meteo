#include "config.h"
#include "Log.h"
#include "DHTSensor.h"


DHT *dht = nullptr;

//true если сенсор доступен
//false если сенсор не доступен
bool DHT_Setup()
{  
    dht = new DHT(DHT_PIN, DHT_TYPE);
    dht->begin();
    if (DHT_Get_Status())
    {
      Log("DHT setup complete");
      return true;
    }
    else 
    {
      Log("DHT setup failed");
      return false;
    }
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

float DHT_Get_Heat_Index()
{
  return dht->computeHeatIndex(false);
}
