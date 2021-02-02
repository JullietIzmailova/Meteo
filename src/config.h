
#ifndef CONFIG_H
#define CONFIG_H

//Main Define

#define SERIAL_BAUD 9600
#define SETUP_DELAY 100
#define MAIN_LOOP_DELAY 2000

#define HEAT_INDEX_LEVEL_LOW 27
#define HEAT_INDEX_LEVEL_HIGH 30



//DHT Define section
#define DHT_PIN 2
#define DHT_TYPE DHT22 

//LCD Define siction
#define LCD_PORT 0x27
#define LCD_COLS 20
#define LCD_ROWS 4

//LED Define section
#define LED_RED_PIN 4
#define LED_GREEN_PIN 5
#define LED_YELLOW_PIN 6

//LIGHT SENSOR Define section 
#define LIGHT_SENSOR_ANALOG_PIN -1
#define LIGHT_SENSOR_DIGITAL_PIN -1

#endif


