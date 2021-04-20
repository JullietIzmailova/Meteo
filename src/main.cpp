/* ----------------------------------------------------------------------------
Ready IoT Solution - OWLOS Meteo
Copyright 2020, 2021 by:
- Julliet Izmailova
- Vitalii Glushchenko (cehoweek@gmail.com)
- Denys Melnychuk (meldenvar@gmail.com)
- Denis Kirin (deniskirinacs@gmail.com)
- Serhii Lehkii (sergey@light.kiev.ua)

This file is part of Ready IoT Solution - OWLOS

OWLOS is free software : you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

OWLOS is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with OWLOS. If not, see < https://www.gnu.org/licenses/>.

GitHub: https://github.com/KirinDenis/owlos

(Этот файл — часть Ready IoT Solution - OWLOS.

OWLOS - свободная программа: вы можете перераспространять ее и/или изменять
ее на условиях Стандартной общественной лицензии GNU в том виде, в каком она
была опубликована Фондом свободного программного обеспечения; версии 3
лицензии, любой более поздней версии.

OWLOS распространяется в надежде, что она будет полезной, но БЕЗО ВСЯКИХ
ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА или ПРИГОДНОСТИ ДЛЯ
ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ.
Подробнее см.в Стандартной общественной лицензии GNU.

Вы должны были получить копию Стандартной общественной лицензии GNU вместе с
этой программой. Если это не так, см. <https://www.gnu.org/licenses/>.)
--------------------------------------------------------------------------------------*/

#include "config.h"
#include "log.h"
#include "DHTSensor.h"
#include "LCDBigNumbers.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
#include "Clock.h"

#include "UART.h"
#include "Buttons.h"

#include "ScreenMeteo.h"
#include "ScreenClock.h"
#include "ScreenAlarm.h"
#include "SetupSignals.h"

//Счетчик количество loop() итераций которое будет пропущено перед очередным
//выводам данных на LCD экран. Инициализируется предельным значением MAIN_LOOP_COUNT_LIMIT,
//таким образом после setup() - первая этерация loop() выведет данные на экран и перейдет в
//режим ожидания (сбросит счетчик Loop_Count в ноль), пока счетик Loop_Count сново не
//достигнет значения MAIN_LOOP_COUNT_LIMIT. Каждый loop() увеличивает  Loop_Count на единицу.
int Loop_Count = MAIN_LOOP_COUNT_LIMIT;

//Текущий режим LCD экрана, влияет на вывод данных
int App_Mode = MODE_METEO;
//Предидущий режим LCD экрана, дает возможность оценить - изменил ли пользователь режим экрана
int App_Saved_Mode = MODE_NULL;
//Текущий элемент настройки (который пользователь может изменять)
int currentEdit = 0;
//Используется, для подстветки текущего элемента настройки
bool blink = false;
//Используется будильником для отключения сигнала
bool AnyKey = false;

//Setup section -------------------------------
//Значения параметров настройки смотрите в файлы config.h
void setup()
{
  Serial.begin(SERIAL_BAUD); //Устанавливаем скорость UART (Serial)
  delay(SETUP_DELAY);        //Даем время соединеному устройству принять новую скорость UART (Serial) (смотрите: config.h)
  Log("Do setup...");

  BUZZER_Setup(); //инициализация "пищалки"
  delay(SETUP_DELAY);

  if(!LCD_Setup())
  {
    Setup_Signals_Long_And_Short(NO_LCD_Long_Signals, NO_LCD_Short_Signals, true);
  }
           //Инициализируем дисплей (параметры дисплея и номер порта смотрите config.h)
  LCD_Set_Light(true); //Включаем подсветку дисплея

  LCDBigNumber_Setup(); //Инициализируем таблицы переопределения симводов дисплея, для прорисовки "больших" цифр

  LCD_Print_CenterLine1("-= OWLOS Meteo =-"); //выводим приветствие
  LCD_Print_CenterLine3("Please wait...");
  delay(LOGO_DELAY); //задержка для экрана приветствия

//если определен этот Define - инициализация устройств проводится с печатью отладочной информации на LCD и определенным
//интервалом задержки после инициализации каждого подключеного устройства
#ifdef DEBUG_SETUP

  LCD_Print_CenterLine2("Buzzer setup...OK");
  delay(DEBUG_SETUP_DELAY);

  Buttons_Setup(); //инициализация кнопок
  LCD_Print_CenterLine2("Buttons setup...OK");
  delay(DEBUG_SETUP_DELAY);

  LED_Setup(); //инициализация светодиодов
  LCD_Print_CenterLine2("Led setup...OK");
  delay(DEBUG_SETUP_DELAY);

  LIGHT_Setup(); //инициализация сенсора освещения
  LCD_Print_CenterLine2("Light setup...OK");
  delay(DEBUG_SETUP_DELAY);

  if (DHT_Setup())
  { //инициализация сенсора температуры-влажности
    LCD_Print_CenterLine2("DHT setup...OK");
  }
  else
  {
   LCD_Print_CenterLine2("DHT setup...Bad");
   Setup_Signals_Long_And_Short(NO_DHT_Long_Signals, NO_DHT_Short_Signals, true);
  }
  delay(DEBUG_SETUP_DELAY);

  if (Clock_Setup()) //инициализация часов реального времени
  {
    LCD_Print_CenterLine2("Clock setup...OK");
  }
  else
  {
    LCD_Print_CenterLine2("Clock setup...Bad");
    Setup_Signals_Long_And_Short(NO_CLOCK_Long_Signals, NO_CLOCK_Short_Signals, true);
  }
  delay(DEBUG_SETUP_DELAY);

  LCD_Print_CenterLine2("");
  LCD_Print_CenterLine3("Setup complete");
  delay(DEBUG_SETUP_DELAY);
  Log("Setup complete");
#else //обычная, неотладочная инициализация устройств
  Buttons_Setup();

  BUZZER_Setup();

  LIGHT_Setup();

  LED_Setup();

  DHT_Setup();

  Clock_Setup();
#endif
}
//ENDOF Setup Section ----------------------------------------

int Saved_Mode = MODE_NULL;

//Loop Section -----------------------------------------------
void loop()
{
  //Каждый loop() вызывает задержку перед очередной итерацией - подробнее смотрите config.h->MAIN_LOOP_DELAY
  delay(MAIN_LOOP_DELAY);

  UARTLoop(); //Обслуживание комуникации с устройством подключенным по UART (Serial)

  Buttons_Loop(); //Считывание и анализ состояния кнопок после предидущего loop()

  //Если одна из трех кнопок нажата
  if (Get_Button1_ShortPress() || Get_Button2_ShortPress() || Get_Button3_ShortPress())
  {
    AnyKey = true; //взводим этот флажек - его использует будильник для отключения сигнала Alarm
    //таким образом, пользователь может отключить звук будильника нажатием на любую кнопку
  }

  //Внимание:
  //Далее следуют вызовы процедур вывода данных на экран.
  //Весь код связаный с обслуживанием и выводом данных на экран хранится в соответствующих модулях:
  //ScreenMeteo - обслуживыет режимом метеостанции
  //ScreenClock - обслуживает часы реального времени
  //ScreenAlarm - обслуживает будильник

  //Изучите структуру этих модулей перед тем как ознакамливатся с кодом ниже.
  //В зависимости от текущего режима экрана, главная процедура loop() -> мы в ней сейчас находимся :)
  //вызывает соответсвующие процедуры для обработки нажатия кнопок и вывода данных на экран -> через
  //определенные интервалы времени. (нажатие кнопок обрабатываются чаще, чем выводя данных - таким образом
  //мы добиваемся отзывчевой реакции на нажатие пользователем кнопок и не нагружаем контроллер избыточным
  //выводом данных)

  //---
  //Индекс текущего режима экрана (Screen Mode) хранится в переменной App_Mode
  //O режимах экрана можно прочитать в config.h -> #define MODE_NNN
  //Сохраняем значение этой переменной и анализируем нажимал ли пользователь кнопки #2 и #3
  //Нажатие этих кнопок в режимах просмотра данных - приведет к переключению экрана в следующий режим.
  //Переключение режимов экрана закальцована ->Meteo_Mode->Clock_Mode->Alarm_Mode->Meteo_Mode->
  //App_Saved_Mode = App_Mode;
  //Если не один из режимов настройки
  if ((App_Mode != MODE_SET_METEO) && (App_Mode != MODE_SET_CLOCK) && (App_Mode != MODE_SET_ALARM))
  {
    if (Get_Button2_ShortPress() == true) //Если нажата кнопка #2 ("листание" экранов влево)
    {
      if (App_Mode > MODE_METEO) //Если текущий режим не режим просмотра метео данных
      {
        App_Mode--; //"Листаем" экраны влево
      }
      else
      {
        App_Mode = MODE_ALARM; //переходим к последнему экрану (закольцовываем просмотр экранов)
      }
    }

    if (Get_Button3_ShortPress() == true) //Если нажата кнопка #3 листаем экраны в право (также как и для кнопки #2 но в другую сторону)
    {
      if (App_Mode < MODE_ALARM)
      {
        App_Mode++;
      }
      else
      {
        App_Mode = MODE_METEO;
      }
    }
  }

  //Теперь проверяем переключил ли пользователь режим просмотра экрана
  if (App_Saved_Mode != App_Mode) //Если да - подготавливаем экран к выводу новых данных (очищаем данные предидущего экрана)
  {
    //Только режимы просмотра данных - режимы настройки выбираются отдельно
    switch (App_Mode)
    {
    case MODE_METEO:
      Screen_Meteo_Init();
      break;
    case MODE_CLOCK:
      Screen_Clock_Init();
      break;
    case MODE_ALARM:
      Screen_Alarm_Init();
      break;
    }
    App_Saved_Mode = App_Mode;
  }

  //В зависемости от текущего режима экрана - вызываем соответствующие процедуры
  //обработки нажатия кнопок в модулях обслуживающих текущий экран.
  switch (App_Mode)
  {
  case MODE_METEO:
  case MODE_SET_METEO:
    Screen_Meteo_Read_Buttons();
    break;
  case MODE_CLOCK:
  case MODE_SET_CLOCK:
    Screen_Clock_Read_Buttons();
    break;
  case MODE_ALARM:
  case MODE_SET_ALARM:
    Screen_Alarm_Read_Buttons();
    break;
  }

  //После обработок кнопок, так же в зависемости от текущего режима экрана
  //вызываем процедуры вывода данных, но с большей задержкой (или другими словами - реже) чем обрабатываем кнопки.
  //Счетчик Loop_Count подсчитывает колличество loop() итераций которые будут пропущены.
  //MAIN_LOOP_COUNT_LIMIT определят колличество loop() которое надо пропустить.
  Loop_Count++;
  if (Loop_Count > MAIN_LOOP_COUNT_LIMIT)
  {
    Loop_Count = 0; //Сбрасывам счетчик пропущеных loop()
    //Выводим данные в зависемости от текущего режима
    switch (App_Mode)
    {
    case MODE_METEO:
    case MODE_SET_METEO:
      Screen_Meteo_Draw();
      break;
    case MODE_CLOCK:
    case MODE_SET_CLOCK:
      Screen_Clock_Draw();
      break;
    case MODE_ALARM:
    case MODE_SET_ALARM:
      Screen_Alarm_Draw();
      break;
    }
  }
}
//ENDOF Loop Section -------------------------------------------
