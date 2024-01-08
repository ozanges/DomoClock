#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "secrets.h" // rename & update secrets.template.h
#include "debug.h"
#include "utils.h"

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
    DPRINT(".");
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

    String payload    = "{";
    payload += "\"hh\":" + String(timeClient.getHours()) + ",";
    payload += "\"mm\":" + String(timeClient.getMinutes()) + ",";
    payload += "\"ss\":" + String(timeClient.getSeconds()) + ",";
    payload += "\"wk\":" + weekDays[timeClient.getDay()] + ",";
    payload += "\"md\":" + String(monthDay) + ",";
    payload += "\"mn\":" + currentMonthName + ",";
    payload += "\"yy\":" + String(currentYear);
    payload += "}";

    DPRINTLN(payload);
    Serial1.println(payload);
	}
}
