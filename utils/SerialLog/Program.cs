using System;
using System.IO.Ports;
using System.IO;
using System.Threading;

class SerialLog
{
    private static string _fileName;

    static void Main()
    {
        _fileName = $"ArduinoData_{DateTime.Now:yyyyMMdd_HHmmss}.txt";

        // Configurer le port série
        SerialPort serialPort = new SerialPort("COM6", 115200)
        {
            RtsEnable = true,
            DtrEnable = true
        };
        serialPort.DataReceived += DataReceivedHandler;
        serialPort.Open();
        Console.WriteLine("Appuyez sur une touche pour fermer.");
        Console.ReadKey();

        // Fermer le port série
        serialPort.Close();
    }

    private static void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
    {
        SerialPort sp = (SerialPort)sender;
        string indata = sp.ReadLine();
        Console.WriteLine($"{DateTime.Now:yyyy-MM-dd HH:mm:ss} - {indata}");
        File.AppendAllText(_fileName, $"{DateTime.Now:yyyy-MM-dd HH:mm:ss} - {indata}\n");
    }
}
