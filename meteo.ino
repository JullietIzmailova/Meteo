#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#define DHTPIN 2 // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors. This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
byte drop[8] = {
0b00100,
0b01010,
0b10001,
0b10001,
0b10001,
0b01110,
0b00000,
0b00000
};

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
void setup() {
Serial.begin(9600);
Serial.println(F("DHTxx test!"));
pinMode(6, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);

dht.begin();
lcd.init(); 
lcd.createChar(0, drop); 
lcd.backlight();
 lcd.setCursor(5,0);
 lcd.print("hello");
 lcd.setCursor(4,1);
 lcd.print("wait...");
}

void loop() {
// Wait a few seconds between measurements.
delay(2000);
lcd.clear();


// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
float h = dht.readHumidity();
// Read temperature as Celsius (the default)
float t = dht.readTemperature();
// Read temperature as Fahrenheit (isFahrenheit = true)
float f = dht.readTemperature(true);

// Check if any reads failed and exit early (to try again).
if (isnan(h) || isnan(t) || isnan(f)) {
  lcd.setCursor(0,0);
 lcd.print("dht error");
Serial.println(F("Failed to read from DHT sensor!"));
return;
}

// Compute heat index in Fahrenheit (the default)
float hif = dht.computeHeatIndex(f, h);
// Compute heat index in Celsius (isFahreheit = false)
float hic = dht.computeHeatIndex(t, h, false);

if(hic>27){
  if(hic>30){
  digitalWrite(6,1);
  digitalWrite(4,0);
  digitalWrite(3,0);
  }
  else{
  digitalWrite(6,0);
  digitalWrite(4,1);
  digitalWrite(3,0);
  }
 }
else{
  digitalWrite(6,0);
  digitalWrite(4,0);
  digitalWrite(3,1);
}
 int L=analogRead(A5);
 lcd.setCursor(0,0);
 lcd.print("T "+String(t));
 lcd.print("C");
 lcd.print(char(223));
 lcd.print(" L "+String(L));
   lcd.setCursor(0,1);
   lcd.write(byte(0));
 lcd.print(" "+String(h)); 
 lcd.print("% H " + String(hif));

 Serial.println(L);
Serial.print(F("Humidity: "));
Serial.print(h);
Serial.print(F("% Temperature: "));
Serial.print(t);
Serial.print(F("°C "));
Serial.print(f);
Serial.print(F("°F Heat index: "));
Serial.print(hic);
Serial.print(F("°C "));
Serial.print(hif);
Serial.println(F("°F"));
}
