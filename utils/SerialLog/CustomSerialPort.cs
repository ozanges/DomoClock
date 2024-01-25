using System.IO.Ports;

namespace SerialLog 
{
    public class CustomSerialPort : SerialPort {
        private string _fileName;
        private string _consolePrefix;

        public string FileName { 
            get {
                return _fileName;
            }
            set {
                _fileName = value;
            }
        }

        public string ConsolePrefix { 
            get {
                return _consolePrefix;
            }
            set {
                _consolePrefix = value;
            }
        }

        public CustomSerialPort(string port, int baud) : base(port, baud) {}

        public CustomSerialPort(string port, int baud, string fileName = null, string consolePrefix = null) : base(port, baud) {
            _fileName = fileName;
            _consolePrefix = consolePrefix;
        }
    }
}