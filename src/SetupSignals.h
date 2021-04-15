#include <Arduino.h>
#define Long_Signal 1000
#define Short_Signal 100
#define Pause_Signal 500

void Setup_Signals_Init();
void Setup_Signals_Long_And_Short(unsigned int longsSignals, unsigned int shortSignals, bool order);
void Setup_Signals_Blinking_Light(unsigned int repeatTimes, String colourLight);

