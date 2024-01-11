#include <SoftwareSerial.h>
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

const           byte txPin = 1;
const           byte rxPin = 3;
SoftwareSerial  mySerial(rxPin, txPin);

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

void serialSetup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);
}

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif

  Serial1.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  wifiSetup();
  timeClientSetup();
  //serialSetup();
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

void loop() {
  unsigned long currentMillis = millis();
	if (currentMillis - _previousTXMillis >= _delayTX) {
    timeClient.update();
		_previousTXMillis = currentMillis;

    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime ((time_t *)&epochTime); 
    int monthDay = ptm->tm_mday;
    int currentMonth = ptm->tm_mon+1;
    String currentMonthName = months[currentMonth-1];
    int currentYear = ptm->tm_year+1900;
    
    String actualTemperature = getWebData("http://192.168.1.50/core/api/jeeApi.php?apikey=ffZimVXpb3Brc1xHeCex7iGsW70GXJXB&type=cmd&id=1313");
    String minTemperature = getWebData("http://192.168.1.50/core/api/jeeApi.php?apikey=ffZimVXpb3Brc1xHeCex7iGsW70GXJXB&type=cmd&id=1302");
    String maxtemperature = getWebData("http://192.168.1.50/core/api/jeeApi.php?apikey=ffZimVXpb3Brc1xHeCex7iGsW70GXJXB&type=cmd&id=1303");
    String actualStatus = getWebData("http://192.168.1.50/core/api/jeeApi.php?apikey=ffZimVXpb3Brc1xHeCex7iGsW70GXJXB&type=cmd&id=3084");

    String payload    = "{";
    payload += "\"ep\":" + String(epochTime) + ",";
    payload += "\"actp\":" + actualTemperature + ",";
    payload += "\"mitp\":" + minTemperature + ",";
    payload += "\"matp\":" + maxtemperature + ",";
    payload += "\"as\":\"" + actualStatus + "\"";
    payload += "}";

    DPRINTLN(payload);
    Serial1.println(payload);
	}
}
