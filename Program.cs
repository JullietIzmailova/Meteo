using System;
using System.IO.Ports;
using System.Threading;
using System.Management;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace Meteo
{

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
    public struct PHYSICAL_MONITOR
    {
        public IntPtr hPhysicalMonitor;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
        public string szPhysicalMonitorDescription;
    }

    public class BrightnessController : IDisposable
    {
        [DllImport("user32.dll", EntryPoint = "MonitorFromWindow")]
        public static extern IntPtr MonitorFromWindow([In] IntPtr hwnd, uint dwFlags);

        [DllImport("dxva2.dll", EntryPoint = "DestroyPhysicalMonitors")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool DestroyPhysicalMonitors(uint dwPhysicalMonitorArraySize, ref PHYSICAL_MONITOR[] pPhysicalMonitorArray);

        [DllImport("dxva2.dll", EntryPoint = "GetNumberOfPhysicalMonitorsFromHMONITOR")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetNumberOfPhysicalMonitorsFromHMONITOR(IntPtr hMonitor, ref uint pdwNumberOfPhysicalMonitors);

        [DllImport("dxva2.dll", EntryPoint = "GetPhysicalMonitorsFromHMONITOR")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetPhysicalMonitorsFromHMONITOR(IntPtr hMonitor, uint dwPhysicalMonitorArraySize, [Out] PHYSICAL_MONITOR[] pPhysicalMonitorArray);

        [DllImport("dxva2.dll", EntryPoint = "GetMonitorBrightness")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetMonitorBrightness(IntPtr handle, ref uint minimumBrightness, ref uint currentBrightness, ref uint maxBrightness);

        [DllImport("dxva2.dll", EntryPoint = "SetMonitorBrightness")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool SetMonitorBrightness(IntPtr handle, uint newBrightness);
       

        private uint _physicalMonitorsCount = 1;
        private PHYSICAL_MONITOR[] _physicalMonitorArray;

        private IntPtr _firstMonitorHandle;

        private uint _minValue = 0;
        private uint _maxValue = 0;
        private uint _currentValue = 0;

        public BrightnessController(IntPtr windowHandle)
        {
            uint dwFlags = 0u;
            IntPtr ptr = MonitorFromWindow(windowHandle, dwFlags);
            if (!GetNumberOfPhysicalMonitorsFromHMONITOR(ptr, ref _physicalMonitorsCount))
            {
                throw new Exception("Cannot get monitor count!");
            }
            _physicalMonitorArray = new PHYSICAL_MONITOR[_physicalMonitorsCount];

            if (!GetPhysicalMonitorsFromHMONITOR(ptr, _physicalMonitorsCount, _physicalMonitorArray))
            {
                throw new Exception("Cannot get phisical monitor handle!");
            }
            _firstMonitorHandle = _physicalMonitorArray[0].hPhysicalMonitor;

            if (!GetMonitorBrightness(_firstMonitorHandle, ref _minValue, ref _currentValue, ref _maxValue))
            {
                throw new Exception("Cannot get monitor brightness!");
            }
        }

        public void SetBrightness(int newValue) // 0 ~ 100
        {
            newValue = Math.Min(newValue, Math.Max(0, newValue));
            _currentValue = (_maxValue - _minValue) * (uint)newValue / 100u + _minValue;
            SetMonitorBrightness(_firstMonitorHandle, _currentValue);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (_physicalMonitorsCount > 0)
                {
                    DestroyPhysicalMonitors(_physicalMonitorsCount, ref _physicalMonitorArray);
                }
            }
        }
    }
    internal class Program
    {

        [DllImport("user32.dll", EntryPoint = "FindWindow", SetLastError = true)]
        public static extern IntPtr FindWindowByCaption(IntPtr zeroOnly, string lpWindowName);

        private static BrightnessController brightnessController;

        private  static string buffer = string.Empty;
        private static void Main(string[] args)
        {
            //git update-index --assume-unchanged  C:\Users\Egor3\Source\Repos\JullietIzmailova\Meteo\.vs\slnx.sqlite
            IntPtr handle = FindWindowByCaption(IntPtr.Zero, Console.Title);

            brightnessController = new BrightnessController(handle);


            Console.WriteLine("Meteo UART");

            SerialPort _serialPort = new SerialPort("COM4",
                                        9600,
                                        Parity.None,
                                        8,
                                        StopBits.One)
            {
                Handshake = Handshake.None
            };

            _serialPort.DataReceived += new SerialDataReceivedEventHandler(sp_DataReceived);

            _serialPort.Open();

            while (true)
            {
                _serialPort.Write("AT+L?\n");
                Thread.Sleep(5000);
                
            }

            Console.ReadLine();
        }

        private static void sp_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string data = sp.ReadExisting();

            buffer = buffer + data;

            try
            {
                
                if (buffer.IndexOf("\r") != -1)
                {
                    Console.WriteLine(buffer);
                    if (buffer.IndexOf("OK AT+L? ") == 0)
                    {
                        string strLight = buffer.Substring(buffer.IndexOf("? ") + 2);
                        strLight = strLight.Substring(0, strLight.IndexOf("\r"));
                        strLight = strLight.Replace('.', ',');
                        float light = 0;
                        if (float.TryParse(strLight, out light))
                        {
                            brightnessController.SetBrightness((int)(100 - light * 20));
                        }
                    }
                    buffer = string.Empty;
                }
                
            }
            catch { }

            
        }


    }
}
