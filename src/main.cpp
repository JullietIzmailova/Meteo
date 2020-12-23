
//Исходные коды метеостанции
#include "DHTSensor.h"
#include "src/libraries/LiquidCrystal_I2C/LiquidCrystal_I2C.h"


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


byte drop[8] = {
    0b00100,
    0b01010,
    0b10001,
    0b10001,
    0b10001,
    0b01110,
    0b00000,
    0b00000};

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 20 chars and 4 line display
void setup()
{
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  DHTInit();

  lcd.init();
  lcd.createChar(0, drop);
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("hello");
  lcd.setCursor(4, 1);
  lcd.print("wait...");
}

void loop()
{
  // Wait a few seconds between measurements.
  delay(2000);
  lcd.clear();

  float hic = DHTHeatIndex();

  if (hic > 27)
  {
    if (hic > 30)
    {
      digitalWrite(6, 1);
      digitalWrite(4, 0);
      digitalWrite(3, 0);
    }
    else
    {
      digitalWrite(6, 0);
      digitalWrite(4, 1);
      digitalWrite(3, 0);
    }
  }
  else
  {
    digitalWrite(6, 0);
    digitalWrite(4, 0);
    digitalWrite(3, 1);
  }
  int L = analogRead(A5);
  lcd.setCursor(0, 0);
  lcd.print("T " + String(DHTTemperature()));
  lcd.print(" ");
  lcd.print(char(223));
  lcd.print("C");
  lcd.print(" L " + String(L));
  lcd.setCursor(0, 1);
  lcd.write(byte(0));
  lcd.print(" " + String(DHTHumidity()));
  lcd.print(" %  H " + String(hic));

  Serial.println(L);
  Serial.print(F("Humidity: "));
  Serial.print(DHTHumidity());
  Serial.print(F(" % Temperature: "));
  Serial.print(DHTTemperature());
  Serial.print(F(" °C "));
  Serial.print(hic);

}