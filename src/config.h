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

#ifndef CONFIG_H
#define CONFIG_H

#define SERIAL_BAUD 9600 //скорость UART (Serial)
#define SETUP_DELAY 1000  //задержка процедуры Setup() после инициализации UART (Serial)
#define LOGO_DELAY 1500  //интервал задержки Logo Screen при загрузки

#define DEBUG_SETUP  //включает отладочный режим процедуры Setup()
#define DEBUG_SETUP_DELAY 100  //интервал задержки этапов инциализации (задержки между секциями процедуры Setup())

#define MAIN_LOOP_DELAY 10 //задержка процедуры Loop() после очередной итерации (чем значение больше, тем контроллер менее нагружен, но "хуже" реагирует на события)

//MAIN_LOOP_COUNT_LIMIT - колличество итераций Loop() после которого будут обновлены данные на экране.
//Этот праметр работает в паре с MAIN_LOOP_DELAY -> MAIN_LOOP_COUNT_LIMIT * MAIN_LOOP_DELAY = время в миллисекундах по истечению которого перерисовываеться изображение
//на экране. Если > 1 секунды (1000 миллисекунд) будет задержка в прорисовке секунд (проскальзывание), при этом слишком маленький интервал нагружает контроллер. 
#define MAIN_LOOP_COUNT_LIMIT 20 

//Настройка времени ожидания нажатия кнопок
#define BUTTON_SHORTPRESS_LIMIT 10 //количество итераций Loop() после которого считается что кнопка была нажата (короткое нажатие) BUTTON_SHORTPRESS_LIMIT * MAIN_LOOP_DELAY
#define BUTTON_LONGPRESS_LIMIT 100 //количество итераций Loop() после которого считается что кнопка была нажата (длинное нажатие) BUTTON_LONGPRESS_LIMIT * MAIN_LOOP_DELAY
//^^^OWLOS Meteo использует кнопки в двух режимах - короткого и длинного нажатия, например - при настройке времени и даты - короткое нажатие кнопки #1 приводит к 
//перемещению пользователя к следующему элементу настройки (часы, минуты, секунды...), при этом длинное нажатие этой же кнопки закончивает настройку и 
//возвращает пользователя в режим просмотре времени и даты. Изменения этих параметров, приведет к изменению реакции на время нажатия кнопок. Мы рекомендуем подобрать эти параметры 
//самостоятельно, по своему вкусу.

//О Heat Index можно прочитать тут https://en.wikipedia.org/wiki/Heat_index или тут https://ru.wikipedia.org/wiki/Humidex
#define HEAT_INDEX_LEVEL_LOW 27  //если Heat Index меньше этого предела, то отношение температуры к влажности считается хорошим для ощущений человека (зелный светодиод)
#define HEAT_INDEX_LEVEL_HIGH 30 //выше этого предела Heat Index считается неблагоприятным (крысный светодиод), между LOW и HIGH - приемлемое отношение (желтый светодиод)

//Настройки подключения и параметров перефейных устройств. 
//Схема подключения находится здесь: https://raw.githubusercontent.com/KirinDenis/Meteo/main/resources/gallery/MeteoSchematic.jpg
//DHT Сенсор
#define DHT_PIN 2       //подключается ко пину номер два
#define DHT_TYPE DHT11  //мы используем DHT11, однако библиотека поддерживает DHT22 и другие, вы можете подключить другой тип сенсора

//I2C LCD Жидкокристалический дисплей с I2C шиной
#define LCD_PORT 0x27 //номер порта для I2C шины, возможно у вас дисплей с другим номером порта, очень часто это 0x3F (в LCDActuator библиотеке подробно описано как подобрать ннужный порт)
#define LCD_COLS 20   //колличество колонок
#define LCD_ROWS 4    //колличество строк

//LED номера пинов для подключения светодиодов
#define LED_RED_PIN 4
#define LED_GREEN_PIN 5
#define LED_YELLOW_PIN 6

//LIGHT SENSOR номер пина для подключения сенсора освещенности, предусмотрены цифровой и аналоговый варианты этого сенсора - мы используем аналоговый
#define LIGHT_SENSOR_ANALOG_PIN A2

#ifndef LIGHT_SENSOR_ANALOG_PIN
#define LIGHT_SENSOR_DIGITAL_PIN -1
#endif

//BUZZER номер пина для подключения "пищалки"
#define BUZZER_PIN 7

//Номера пинов для подключения кнопок
#define BUTTON1_PIN 9
#define BUTTON2_PIN 10
#define BUTTON3_PIN 11

//Режимы экрана -------------------------------------
//О Режимах экрана:
//OWLOS Metoe (на момент написания этого текста) - поддерживает 6 режимов (Mode) экранa для отображения данных.
//Индексы режимов и описания перечислены ниже. 

//Режимы экрана делятся на две основных группы:
//- режимы просмотра данных MODE_NNN - в этих режимах пользователь просмотривает данные
//- режимы настройки MODE_SET_NNN - в этих режимах пользовать настраивает устройство (переводит часы, устанавливае будильник...)

//Вaжано! -> управление кнопками зависит от текущего активного режима. 
//- в режимах просмотра 
//-- долго нажатая кнопка #1 - переводит устройсво в режим настройки (смотрите: BUTTON_LONGPRESS_LIMIT)
//-- нажатие кнопок #2 и #3 "перелистывает" экраны просмотра 
//- в режимах настройки
//-- долго нажатая кнопка #1 - переводит устройсво в режим просмотра
//-- быстрое нажатие кнопки #1 - приводит к переходу к следующему параметру настройки (наприме: часы, минуты, секутнды...)
//-- нажатие кнопок #2 и #3 изменяет текущие значения параметра настройки

#define MODE_NULL -1  //режим инициализации
#define MODE_METEO 0  //режим метеостанции - отображаются метео данные температуры, влажность и прочее
#define MODE_CLOCK 1  //режим часов - отображается текущее время и дата
#define MODE_ALARM 2  //режим будильника - отображается текущие настройки будильника
#define MODE_SET_CLOCK 3 //режим настройки времени и даты
#define MODE_SET_ALARM 4 //режим установки будильника
#define MODE_SET_METEO 5 //режим настройки отображения метео данных

#endif
