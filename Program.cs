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

using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Threading;

namespace Meteo
{
    public class Program
    {
        private static readonly int baudRate = 115200;
        private static string buffer = string.Empty;
        private static readonly int interval = 10000;
        private static void Main(string[] args)
        {
            Console.WindowWidth = 80;
            Console.WindowHeight = 20;
            Console.CursorVisible = false;

            WriteLine("                          --=== OWLOS Meteo UART ===--                         ", ConsoleColor.Yellow, ConsoleColor.Blue);
            WriteLine("");
            WriteLine("Searching for connected devices...", ConsoleColor.White);


            SerialPort serialPort = new SerialPort
            {
                BaudRate = baudRate,
                RtsEnable = true
            };
            for (int i = 1; i < 24; i++)
            {

                serialPort.PortName = "COM" + i.ToString();
                WriteLine(" try open port " + serialPort.PortName, ConsoleColor.Yellow);

                serialPort.DataReceived += new SerialDataReceivedEventHandler(sp_DataReceived);

                try
                {
                    serialPort.Open();
                }
                catch (Exception)
                {
                    WriteLine(" can't open " + serialPort.PortName, ConsoleColor.Red);
                    WriteLine("");
                    continue;
                }
                break;
            }

            if (!serialPort.IsOpen)
            {
                WriteLine("Device not found...", ConsoleColor.Red);
                WriteLine("Press Enter to close this application");
                Console.ReadLine();
            }
            else
            {
                Console.Clear();
                WriteLine("                          --=== OWLOS Meteo UART ===--                          ", ConsoleColor.Yellow, ConsoleColor.Blue);
                WriteLine("OWLOS Meteo at " + serialPort.PortName + " (" + serialPort.BaudRate +")", ConsoleColor.Green);
                WriteLine("Waiting for a data... ", 0, 3, ConsoleColor.Yellow);
                while (true)
                {
                    if (serialPort.IsOpen)
                    {
                        try
                        {                         
                            serialPort.WriteLine("AT+ADP?" + "\n\r");
                            Thread.Sleep(interval);
                        }
                        catch { }
                    }
                    else
                    {
                        WriteLine("OWLOS Meteo close port " + serialPort.PortName + ", please restart application", 0, 1, ConsoleColor.Red);
                    }
                }
            }
        }

        private static void WriteLine(string text, ConsoleColor foregroundColor = ConsoleColor.Gray, ConsoleColor backgroundColor = ConsoleColor.Black)
        {
            Console.ForegroundColor = foregroundColor;
            Console.BackgroundColor = backgroundColor;
            Console.WriteLine(text);
        }

        private static void WriteLine(string text, int x, int y, ConsoleColor foregroundColor = ConsoleColor.Gray, ConsoleColor backgroundColor = ConsoleColor.Black)
        {
            Console.CursorLeft = x;
            Console.CursorTop = y;
            Console.ForegroundColor = foregroundColor;
            Console.BackgroundColor = backgroundColor;
            Console.WriteLine(text);
        }

        private static bool ParseFloatFromRx(string TxData, out float data)
        {
            try
            {
                TxData = TxData.Substring(buffer.IndexOf("? ") + 2);
                TxData = TxData.Substring(0, TxData.IndexOf("\r"));
                TxData = TxData.Replace('.', ',');

                if (float.TryParse(TxData, out data))
                {
                    return true;
                }
            }
            catch { }
            data = float.NaN;
            return false;
        }

        private static void sp_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

            WriteLine("last session " + DateTime.Now.ToString(), 45, 1);

            SerialPort sp = (SerialPort)sender;
            string data = sp.ReadExisting();

            buffer = buffer + data;
        //    WriteLine("RX<-" + buffer + "                      ", 0, 8);

            try
            {
                if (buffer.IndexOf("\n\n") != -1)
                {
                    if (buffer.IndexOf("OK: AT+ADP?") == 0)
                    {
                        List<string> driverRaw = buffer.Split('\n').ToList();

                        string driverName = string.Empty;

                        foreach (string driverProp in driverRaw)
                        {
                            //find driver
                            if ((driverProp.IndexOf("properties for:") != -1) || (driverProp.IndexOf("PF:") != -1))
                            {
                                driverName = driverProp.Substring(driverProp.IndexOf(":") + 1);
                            }
                            else
                            {
                                if (driverProp.IndexOf("=") != -1)
                                {
                                    string key = driverProp.Substring(0, driverProp.IndexOf("="));
                                    string value = driverProp.Substring(driverProp.IndexOf("=") + 1);
                                    value = value.Substring(0, value.IndexOf("//"));

                                    if (driverName.Equals("RL"))
                                    {
                                        if (key.Equals("d"))
                                        {
                                            WriteLine("Red led:                          ", 0, 3, ConsoleColor.White);
                                            if (value.Equals("1"))
                                            {
                                                WriteLine("On", 15, 3, ConsoleColor.Red);
                                            }
                                            else
                                            {
                                                WriteLine("Off", 15, 3, ConsoleColor.Gray);
                                            }
                                        }
                                    }
                                    else
                                    if (driverName.Equals("YL"))
                                    {
                                        if (key.Equals("d"))
                                        {
                                            WriteLine("Yellow led: ", 0, 4, ConsoleColor.White);
                                            if (value.Equals("1"))
                                            {
                                                WriteLine("On", 15, 4, ConsoleColor.Yellow);
                                            }
                                            else
                                            {
                                                WriteLine("Off", 15, 4, ConsoleColor.Gray);
                                            }
                                        }
                                    }
                                    else
                                    if (driverName.Equals("GL"))
                                    {
                                        if (key.Equals("d"))
                                        {
                                            WriteLine("Green led: ", 0, 5, ConsoleColor.White);
                                            if (value.Equals("1"))
                                            {
                                                WriteLine("On", 15, 5, ConsoleColor.Green);
                                            }
                                            else
                                            {
                                                WriteLine("Off", 15, 5, ConsoleColor.Gray);
                                            }
                                        }
                                    }
                                    else
                                    if (driverName.Equals("BZ"))
                                    {
                                        if (key.Equals("d"))
                                        {
                                            WriteLine("Buzzer: ", 0, 6, ConsoleColor.White);
                                            if (value.Equals("1"))
                                            {
                                                WriteLine("On", 15, 6, ConsoleColor.White);
                                            }
                                            else
                                            {
                                                WriteLine("Off", 15, 6, ConsoleColor.Gray);
                                            }
                                        }
                                    }
                                    else
                                    if (driverName.Equals("CL"))
                                    {
                                        if (key.Equals("t"))
                                        {
                                            WriteLine("Time: ", 22, 3, ConsoleColor.White);
                                            WriteLine(value, 37, 3, ConsoleColor.Gray);
                                        }
                                        else
                                        if (key.Equals("d"))
                                        {
                                            WriteLine("Date: ", 22, 4, ConsoleColor.White);
                                            WriteLine(value, 37, 4, ConsoleColor.Gray);
                                        }
                                        else
                                        if (key.Equals("a"))
                                        {
                                            WriteLine("Alarm: ", 22, 5, ConsoleColor.White);
                                            WriteLine(value, 37, 5, ConsoleColor.Gray);
                                        }
                                        else
                                        if (key.Equals("as"))
                                        {
                                            WriteLine("Alarm status ", 22, 6, ConsoleColor.White);
                                            if (value.Equals("1"))
                                            {
                                                WriteLine("On", 37, 6, ConsoleColor.Green);
                                            }
                                            else
                                            {
                                                WriteLine("Off", 37, 6, ConsoleColor.Red);
                                            }
                                        }
                                    }
                                    if (driverName.Equals("DHT"))
                                    {
                                        if (key.Equals("t"))
                                        {
                                            WriteLine("Temperature: ", 50, 3, ConsoleColor.White);
                                            WriteLine(value, 65, 3, ConsoleColor.Gray);
                                        }
                                        else
                                        if (key.Equals("h"))
                                        {
                                            WriteLine("Humidity: ", 50, 4, ConsoleColor.White);
                                            WriteLine(value, 65, 4, ConsoleColor.Gray);
                                        }
                                        else
                                        if (key.Equals("i"))
                                        {
                                            WriteLine("Heat Index: ", 50, 5, ConsoleColor.White);
                                            WriteLine(value, 65, 5, ConsoleColor.Gray);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    buffer = string.Empty;
                }
            }
            catch { }
        }
    }
}
