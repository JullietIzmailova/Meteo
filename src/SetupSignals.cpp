#include "LEDActuator.h"
#include "BUZZERActuator.h"
#include "SetupSignals.h"

void Setup_Signals_Long_And_Short(unsigned int longsSignals, unsigned int shortSignals, bool order)
{

  for (unsigned int i = 1; i <= (longsSignals+shortSignals); i++)
  {
    if(order)
    {
      
      if(i <= longsSignals)
      {
        LED_Red_Set_Light(true);
        BUZZER_Set_sound(true);
        delay(Long_Signal); 
      }
      
      if(i > longsSignals && i <= (shortSignals+longsSignals) )
      {
        LED_Red_Set_Light(true);
        BUZZER_Set_sound(true);
        delay(Short_Signal); 
      }

    }
    else
    {
      if(i <= shortSignals)
      {
        LED_Red_Set_Light(true);
        BUZZER_Set_sound(true);
        delay(Short_Signal); 
      }
      if(i > shortSignals && i <= (shortSignals+longsSignals))
      {
        LED_Red_Set_Light(true);
        BUZZER_Set_sound(true);
        delay(Long_Signal); 
      }
    }
    
 
    LED_Red_Set_Light(false);
    BUZZER_Set_sound(false);
    delay(Pause_Signal);
  }

}

void Setup_Signals_Blinking_Light(unsigned int repeatTimes, String colourLight)
{
   for (unsigned int i = 0; i <repeatTimes; i++)
   {
       if(colourLight.equals("red")) LED_Red_Set_Light(true);
       if(colourLight.equals("green")) LED_Green_Set_Light(true);
       if(colourLight.equals("yellow")) LED_Yellow_Set_Light(true);

       delay(Long_Signal);
       
       if(colourLight.equals("red")) LED_Red_Set_Light(false);
       if(colourLight.equals("green")) LED_Green_Set_Light(false);
       if(colourLight.equals("yellow")) LED_Yellow_Set_Light(false);

       delay(Pause_Signal);
   }
  
   delay(Long_Signal);
   
}

