using System;
using System.IO.Ports;
using System.Threading;

namespace Meteo
{
    class Program
    {
        static void Main(string[] args)
        {
            //git update-index --assume-unchanged  C:\Users\Egor3\Source\Repos\JullietIzmailova\Meteo\.vs\slnx.sqlite

            Console.WriteLine("Meteo UART");

            SerialPort _serialPort = new SerialPort("COM10", 
                                        9600, 
                                        Parity.None,
                                        8,
                                        StopBits.One);
            _serialPort.Handshake = Handshake.None;

            _serialPort.DataReceived += new SerialDataReceivedEventHandler(sp_DataReceived);

            _serialPort.Open();

            while (true) { 
            _serialPort.Write("AT+T?\n");
                Thread.Sleep(5000);
            }

            Console.ReadLine();
        }

        static void sp_DataReceived(object sender, SerialDataReceivedEventArgs e)
{
            SerialPort sp = (SerialPort)sender;
            String data = sp.ReadExisting();

            Console.WriteLine(data);
}

    }
}
