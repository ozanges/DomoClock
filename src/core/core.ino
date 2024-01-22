// #include <SoftwareSerial.h>
#include "communication.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "secrets.h" // rename & update secrets.template.h
#include "debug.h"
#include "utils.h"

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


long            _delayTX                      = 2000;
unsigned long   _previousTXMillis             = 0;
int             _wifiProblemDeepSleepDuration = 150; // 2min30
String          weekDays[7]                   = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String          months[12]                    = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

const           byte _txPin = 5;
const           byte _rxPin = 4;
Communication _serial(_rxPin, _txPin);

void wifiSetup()
{
  DPRINTLN();
  DPRINT(F("Try to connect to "));
  DPRINTLN(SSID);

  int wifiRetry = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    DPRINT(F("."));
    delay(500);
    blink(1);

    if (wifiRetry++ >= MAX_WIFI_CONNECTION_RETRY_COUNT)
    {
      DPRINTLN();
      DPRINT(F("Wifi connexion failure after "));
      DPRINT(wifiRetry);
      DPRINTLN(F(" attempt(s)."));
      deepSleep(_wifiProblemDeepSleepDuration);
    }
  }

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  DPRINTLN();
  DPRINTLN("Wifi connexion success ! ");
  DPRINT("=> IP address : ");
  DPRINTLN(WiFi.localIP());
}

void timeClientSetup() {
  timeClient.begin();
  timeClient.setTimeOffset(3600);
}

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  pinMode(LED_BUILTIN, OUTPUT);

  wifiSetup();
  timeClientSetup();
  _serial.setup();
}

String getWebData(const String& url) {
  String data = "";
  WiFiClient client;
  HTTPClient http;
  if (http.begin(client, url)) { 
    int httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        data = http.getString();
        // DPRINTLN(data);
      }
    } 
#ifdef DEBUG    
    else { Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str()); }
#endif

    http.end();
  }

  return data;
}

String _actualTemperature = "0.0";
String _minTemperature = "0.0";
String _maxtemperature = "0.0";
String _actualStatus = "empty";
String _houseTodayPricePercentage = "0";
String _laundryTodayPricePercentage = "0";
String _garageTodayPricePercentage = "0";

void loop() {
  
  if (_serial.listen()) {
    Serial.print(F("Received: [")); Serial.print(_serial.getMessage()); Serial.println(F("]"));
    if (strcmp(_serial.getMessage(), "ep") == 0) {
      time_t epochTime = timeClient.getEpochTime();
      struct tm *ptm = gmtime ((time_t *)&epochTime); 
      int monthDay = ptm->tm_mday;
      int currentMonth = ptm->tm_mon+1;
      String currentMonthName = months[currentMonth-1];
      int currentYear = ptm->tm_year+1900;

      _serial.sendMessage(("ep:" + String(epochTime)).c_str());
    } else if (strcmp(_serial.getMessage(), "actp") == 0) {
      _serial.sendMessage(("actp:" + String(_actualTemperature)).c_str());
    } else if (strcmp(_serial.getMessage(), "mitp") == 0) {
      _serial.sendMessage(("mitp:" + String(_minTemperature)).c_str());
    } else if (strcmp(_serial.getMessage(), "matp") == 0) {
      _serial.sendMessage(("matp:" + String(_maxtemperature)).c_str());
    } else if (strcmp(_serial.getMessage(), "as") == 0) {
      _serial.sendMessage(("as:" + String(_actualStatus)).c_str());
    } else if (strcmp(_serial.getMessage(), "hp") == 0) {
      _serial.sendMessage(("hp:" + String(_houseTodayPricePercentage)).c_str());
    } else if (strcmp(_serial.getMessage(), "lp") == 0) {
      _serial.sendMessage(("lp:" + String(_laundryTodayPricePercentage)).c_str());
    } else if (strcmp(_serial.getMessage(), "gp") == 0) {
      _serial.sendMessage(("gp:" + String(_garageTodayPricePercentage)).c_str());
    } else {
      Serial.println("Unknown data asked !");
    }
  }

  unsigned long currentMillis = millis();
	if (currentMillis - _previousTXMillis >= _delayTX) {
    timeClient.update();
		_previousTXMillis = currentMillis;

    _actualTemperature = getWebData("http://192.168.1.50/core/api/jeeApi.php?apikey=ffZimVXpb3Brc1xHeCex7iGsW70GXJXB&type=cmd&id=1313");
    _minTemperature = getWebData("http://192.168.1.50/core/api/jeeApi.php?apikey=ffZimVXpb3Brc1xHeCex7iGsW70GXJXB&type=cmd&id=1302");
    _maxtemperature = getWebData("http://192.168.1.50/core/api/jeeApi.php?apikey=ffZimVXpb3Brc1xHeCex7iGsW70GXJXB&type=cmd&id=1303");
    _actualStatus = getWebData("http://192.168.1.50/core/api/jeeApi.php?apikey=ffZimVXpb3Brc1xHeCex7iGsW70GXJXB&type=cmd&id=3084");
    _houseTodayPricePercentage = getWebData("http://192.168.1.50/core/api/jeeApi.php?apikey=ffZimVXpb3Brc1xHeCex7iGsW70GXJXB&type=cmd&id=3090");
    _laundryTodayPricePercentage = getWebData("http://192.168.1.50/core/api/jeeApi.php?apikey=ffZimVXpb3Brc1xHeCex7iGsW70GXJXB&type=cmd&id=3088");
    _garageTodayPricePercentage = getWebData("http://192.168.1.50/core/api/jeeApi.php?apikey=ffZimVXpb3Brc1xHeCex7iGsW70GXJXB&type=cmd&id=3089");

    Serial.print(F("Free heap : "));
    Serial.println(ESP.getFreeHeap());
	}
}
