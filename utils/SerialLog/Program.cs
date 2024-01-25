using System;
using System.IO;
using System.IO.Ports;
using System.Threading;

namespace SerialLog {
    class Program
    {
        private static void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            CustomSerialPort serialPort = (CustomSerialPort)sender;        
            string data = serialPort.ReadLine();
            Console.WriteLine($"{DateTime.Now:yyyy-MM-dd HH:mm:ss} - {serialPort.ConsolePrefix} - {data}");
            File.AppendAllText(serialPort.FileName, $"{DateTime.Now:yyyy-MM-dd HH:mm:ss} - {data}\n");
        }

        private static CustomSerialPort InitSerialPort(string port, int baud, string fileName, string consolePrefix, bool enableRts = false, bool enableDtr = false) {
            CustomSerialPort serialPort = new CustomSerialPort(port, baud, fileName, consolePrefix)
            {
                RtsEnable = enableRts,
                DtrEnable = enableDtr
            };
            serialPort.DataReceived += DataReceivedHandler;
            return serialPort;
        }

        private static void Main()
        {
            CustomSerialPort rp2040Port = InitSerialPort("COM6", 115200, $"./Data/{DateTime.Now:yyyyMMdd_HHmmss}_RP2040.txt", "[RP]", true, true);
            CustomSerialPort esp8266Port = InitSerialPort("COM8", 115200, $"./Data/{DateTime.Now:yyyyMMdd_HHmmss}_ESP8266.txt", "[ESP]");
            rp2040Port.Open();
            esp8266Port.Open();

            Console.WriteLine("Press any key to close.");
            Console.ReadKey();

            rp2040Port.Close();
            esp8266Port.Close();
        }
    }
}