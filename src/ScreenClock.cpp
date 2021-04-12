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

GitHub: https://github.com/KirinDenis/Meteo

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
#include "LCDBigNumbers.h"
#include "LEDActuator.h"
#include "LIGHTActuator.h"
#include "BUZZERActuator.h"
#include "Clock.h"
#include "src/libraries/DS3231/DS3231.h"

#include "Buttons.h"
#include "ScreenClock.h"

extern int App_Mode; //текущий режик экрана из main

RTCDateTime editDT; //сохраняется текущая дата и время при настройке
RTCDateTime saveDT; //дублируется сохраненя дата и время при настройке

//индексы элементов редактирования
#define EDIT_HOURE 0
#define EDIT_MINUTE 1
#define EDIT_SECONDS 2
#define EDIT_DAY 3
#define EDIT_MONTH 4
#define EDIT_YEAR 5

//индекс текущего элемента редактирования
extern int currentEdit;

//флажек обеспечивающий "мигания" текущего элемента редактирования на экране
extern bool blink;

//Вызывается когда экран переключен в режимы MODE_CLOCK или MODE_SET_CLOCK
void Screen_Clock_Init()
{
    LCD_Clear();
    Screen_Clock_Draw();
}

//Для режимов экрана: MODE_CLOCK и MODE_SET_CLOCK
//Главная процедура loop() вызывает эту процедуру каждый раз когда этот экран активен.
//Таким образом кнопки нажатые пользователем для этого экрана будуту обработаны этой
//процедурой. Подобные процедуры для других режимов экрана - вызваны не будут.
void Screen_Clock_Read_Buttons()
{
    //Если кнопка #1 была долго зажата, переключаем режимы просмотр-настройка
    if (Get_Button1_LongPress() == true)
    {
        //Переходим в режим настройки если были в просмотра
        if (App_Mode != MODE_SET_CLOCK)
        {
            App_Mode = MODE_SET_CLOCK; //выбираем режим экрана - настройка часов
            currentEdit = EDIT_HOURE;  //выставляем первый редактируемый элемент "часы", далее следуют "минуты", "секунды"...
            editDT = Get_DateTime();   //считываем текущее время, его предложим пользователю изменить
            saveDT = editDT;           //сохраняем считаное время в эту переменную, editDT и saveDT на данном этапе одинаковые - так мы сможем понять редактировал ли пользователь время
            LCD_Clear();               //очищаем экран
        }
        else //Иначе переходим в режим просмотра если были в настройках
        {
            App_Mode = MODE_CLOCK; //выбираем режим просмотрa
            //проверяем редактировал ли пользователь время и дату, если да устанавливаем новое время и дату
            if ((saveDT.year != editDT.year) ||
                (saveDT.month != editDT.month) ||
                (saveDT.day != editDT.day) ||
                (saveDT.hour != editDT.hour) ||
                (saveDT.minute != editDT.minute) ||
                (saveDT.second != editDT.second))
            {
                Clock_Set_DateTime(editDT.year, editDT.month, editDT.day, editDT.hour, editDT.minute, editDT.second);
            }
        }
    }

    //если режим настройки и пользователь нажал кнопку #1 (короткое нажатие) переходим к следующему элементу настройки
    //перемещение по элементам зациклено - часы, минуты, секунды, день, месяц, год - часы, минуты...
    if ((Get_Button1_ShortPress() == true) && (App_Mode == MODE_SET_CLOCK))
    {
        if (currentEdit >= EDIT_YEAR) //если перешли за пределы редактированя года, то уходим "на круг"
        {
            currentEdit = EDIT_HOURE;
        }
        else
        {
            currentEdit++; //выбираем следующий элемент
        }
    }

    //если режим настройки и пользователь нажал кнопку #2 (короткое нажатие) уменьшаем значение текущего элемента редактирования
    if ((Get_Button2_ShortPress() == true) && (App_Mode == MODE_SET_CLOCK))
    {
        //если текущий элемент "год"
        if (currentEdit == EDIT_YEAR)
        {
            if (editDT.year > 2021) //если год более чем 2021 уменьшаяем значение
            {
                editDT.year--;
            }
            else
            {
                editDT.year = 2021; //младьше 2021 года быть не может
                //^^^ если вы используете этот код при постройке машины времени, измените этот параметр на расчетный предельный
                //для вашего устройства.
            }
        } //если текущий элемент месяц
        else if (currentEdit == EDIT_MONTH)
        {
            //если это не Январь уменьшаем значение
            if (editDT.month > 1)
            {
                editDT.month--;
            }
            else
            {
                editDT.month = 12; //если Январь то закольцовываем выбо, после Января -Декабрь, потом Ноябрь и так далее
            }
        } //день также как и месяц с закольцовкой после 31
        else if (currentEdit == EDIT_DAY)
        {
            if (editDT.day > 1)
            {
                editDT.day--;
            }
            else
            {
                editDT.day = 31;
            }
        } //часы
        else if (currentEdit == EDIT_HOURE)
        {
            if (editDT.hour > 0)
            {
                editDT.hour--;
            }
            else
            {
                editDT.hour = 23;
            }
        } //минуты
        else if (currentEdit == EDIT_MINUTE)
        {
            if (editDT.minute > 0)
            {
                editDT.minute--;
            }
            else
            {
                editDT.minute = 59;
            }
        } //секунды
        else if (currentEdit == EDIT_SECONDS)
        {
            if (editDT.second > 0)
            {
                editDT.second--;
            }
            else
            {
                editDT.second = 59;
            }
        }
    }
    //если режим настройки и пользователь нажал кнопку #3 (короткое нажатие) увеличиваем значение текущего элемента редактирования
    //Так же как для кнопки #2 только увеличение (в обратную сторону)
    if ((Get_Button3_ShortPress() == true) && (App_Mode == MODE_SET_CLOCK))
    {
        if (currentEdit == EDIT_YEAR)
        {
            editDT.year++;
            //Please note:
            //- сейчас возможности вашего устройство для перемещения во времени ограничены только uint_16t, учтите этот двухбайтовый факт.
            //- данный код строго не рекомендован для использования в далеком будущем города Ember.
        }
        else if (currentEdit == EDIT_MONTH)
        {
            if (editDT.month < 12)
            {
                editDT.month++;
            }
            else
            {
                editDT.month = 1;
            }
        }
        else if (currentEdit == EDIT_DAY)
        {
            if (editDT.day < 31)
            {
                editDT.day++;
            }
            else
            {
                editDT.day = 1;
            }
        }
        else if (currentEdit == EDIT_HOURE)
        {
            if (editDT.hour < 23)
            {
                editDT.hour++;
            }
            else
            {
                editDT.hour = 0;
            }
        }
        else if (currentEdit == EDIT_MINUTE)
        {
            if (editDT.minute < 59)
            {
                editDT.minute++;
            }
            else
            {
                editDT.minute = 0;
            }
        }
        else if (currentEdit == EDIT_SECONDS)
        {
            if (editDT.second < 59)
            {
                editDT.second++;
            }
            else
            {
                editDT.second = 0;
            }
        }
    }
}

//Для режимов экрана: MODE_CLOCK и MODE_SET_CLOCK
//Главная процедура loop() вызывает эту процедуру через определенный интервал и каждый раз когда этот
//экран активен. Все данные относящиеся к данному режиму экрана должны быть выведены этой процедурой.
void Screen_Clock_Draw()
{
    //Если сейчас режим просмотра времени
    if (App_Mode != MODE_SET_CLOCK)
    {
        if(Clock_Get_Setup())
        {
          //Выводим значение времени большими цифрами
          LCDBigNumber_Print_Height2_Left(0, String(Clock_Get_Time()));
          LCD_Print_CenterLine3(" ");
          //Выводим текующею дату
          LCD_Print_CenterLine4(String(Clock_Get_Date()));
          //Если будильник установлен выводым символы "<A>" в правом нижнем углу экрана
          if (Clock_Get_Alarm1_Status())
          {
            LCD_Print_Text(20 - 3, 3, "<A>");
          }
          else //Если будильник не установлен, очищаем то место где были символы "<A>" тремя пробелами
          {
            LCD_Print_Text(20 - 3, 3, "  ");
          }
        }
        else
        {
           LCD_Print_CenterLine1("Clock");
           LCD_Print_CenterLine4(NO_CLOCK);
        }
    }
    else //Если режим настройки даты и времени
    {
        LCD_Print_Text(0, 2, "Set date:");

        if(Clock_Get_Setup()){
            //Переменая currentEdit содержит индекс текущего редактируемого элемента
            //Флажек blink изменяет свое значение через определеный интервал времени
            //Таким образом текущий выбранный эелемнт "мигает" на экране
            //Day -----------------------------------
            //Если сейчас редактируется день и флажек blink взведен - стираем элемент с экрана
            if ((currentEdit == EDIT_DAY) && (blink))
            {
            LCD_Print_Text(10, 3, "  ");
            }
            else //иначе рисуем эелемент в определенной позиции как обычно
            {
              LCD_Print_Number(10, 3, 2, editDT.day);
            }
               LCD_Print_Text(12, 3, ".");
             //Month -----------------------------------
            if ((currentEdit == EDIT_MONTH) && (blink))
            {
                LCD_Print_Text(13, 3, "  ");
            }
            else
            {
              LCD_Print_Number(13, 3, 2, editDT.month);
            }
              LCD_Print_Text(15, 3, ".");
            //Year -----------------------------------
            if ((currentEdit == EDIT_YEAR) && (blink))
            {
              LCD_Print_Text(16, 3, "    ");
            }
            else
            {
              LCD_Print_Number(16, 3, 4, editDT.year);
            }
            LCD_Print_Text(0, 0, "Set time:");
            //Houre -----------------------------------
            if ((currentEdit == EDIT_HOURE) && (blink))
            {
              LCD_Print_Text(10, 1, "  ");
            }
            else
            {
              LCD_Print_Number(10, 1, 2, editDT.hour);
            }
              LCD_Print_Text(12, 1, ":");
             //Minute -----------------------------------
            if ((currentEdit == EDIT_MINUTE) && (blink))
            {
              LCD_Print_Text(13, 1, "  ");
            }
            else
            {
              LCD_Print_Number(13, 1, 2, editDT.minute);
            }
            LCD_Print_Text(15, 1, ":");
            //Seconds -----------------------------------
            if ((currentEdit == EDIT_SECONDS) && (blink))
            {
              LCD_Print_Text(16, 1, "  ");
            }
            else
            {
              LCD_Print_Number(16, 1, 2, editDT.second);
            }

            blink = !blink;
        }
        else
        {
           LCD_Print_CenterLine4(NO_CLOCK);            
        }
    }
}
