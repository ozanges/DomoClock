// #include <SoftwareSerial.h>
#include "communication.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include "SparkFunCCS811.h"
#include "secrets.h" // rename & update secrets.template.h
#include "debug.h"
#include "utils.h"

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define CCS811_ADDR 0x5A

struct RequestData {
  char key[5];
  int  state; // 0 = must be computed ; 1 = computed
  char uri[128];
  int lastComputationTime;
};

#define  DATALIST_SIZE 12
RequestData _dataList[DATALIST_SIZE] = {
  {"ep", 0, "", 0}
  , {"co2", 0, "", 0}
  , {"tvoc", 0, "", 0}
  , {"actp", 0, DATA_01_URL, 0}
  , {"mitp", 0, DATA_02_URL, 0}
  , {"matp", 0, DATA_03_URL, 0}
  , {"as", 0, DATA_04_URL, 0}
  , {"hp", 0, DATA_05_URL, 0}
  , {"lp", 0, DATA_06_URL, 0}
  , {"gp", 0, DATA_07_URL, 0}
  , {"hu", 0, DATA_08_URL, 0}
  , {"in", 0, DATA_09_URL, 0}
};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

long            _delayTime                    = 1 * 1000; // 1 sec
long            _delayMem                     = 60 * 1000; // 60 sec
unsigned long   _previousTimeMillis           = 0;
unsigned long   _previousMemMillis            = 0;
int             _wifiProblemDeepSleepDuration = 150; // 2min30

const           byte _txPin = 14; //5;
const           byte _rxPin = 12; //4;
Communication   _serial(_rxPin, _txPin);
CCS811          _ccsSensor(CCS811_ADDR);

void wifiSetup()
{
  DPRINTLN();
  DPRINT(F("Try to connect to "));
  DPRINTLN(SSID);

  int wifiRetry = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WIFI_PASSWORD);

  while(WiFi.status() != WL_CONNECTED) {
    DPRINT(F("."));
    delay(500);
    blink(1);

    if(wifiRetry++ >= MAX_WIFI_CONNECTION_RETRY_COUNT) {
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

void timeClientSetup()
{
  timeClient.begin();
  timeClient.setTimeOffset(3600);
}

void setup()
{
#ifdef DEBUG
  Serial.begin(115200);
#endif
  pinMode(LED_BUILTIN, OUTPUT);

  Wire.begin();
  if(_ccsSensor.begin() == false) {
    Serial.print("CCS811 error. Please check wiring. Freezing...");
    while(1)
      ;
  }

  wifiSetup();
  timeClientSetup();
  _serial.setup();
}

String getWebData(const String & url)
{
  String data = "";
  WiFiClient client;
  HTTPClient http;
  if(http.begin(client, url)) {
    int httpCode = http.GET();
    if(httpCode > 0) {
      if(httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        data = http.getString();
        // DPRINTLN(data);
      }
    }
#ifdef DEBUG
    else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
#endif

    http.end();
  }

  return data;
}

void loop()
{
  if(_serial.listen()) {
    Serial.print(F("Received: ["));
    Serial.print(_serial.getMessage());
    Serial.println(F("]"));
    for(int i = 0; i < DATALIST_SIZE; i++) {
      if(strcmp(_serial.getMessage(), _dataList[i].key) == 0) {
        _dataList[i].state = 0;
        Serial.print("Aknowledge : ");
        Serial.print(_dataList[i].key);
        Serial.println(" / state = 0");
        break;
      }
    }
  }

  for(int i = 0; i < DATALIST_SIZE; i++) {
    if(_dataList[i].state == 0) {
      if(strcmp(_dataList[i].key, "ep") == 0) {
        time_t epochTime = timeClient.getEpochTime();
        Serial.println(epochTime);
        Serial.println(("ep:" + String(epochTime)).c_str());
        _serial.sendMessage(("ep:" + String(epochTime)).c_str());
        _dataList[i].state = 1;
        Serial.println("Sent ep value");
        break;
      }
      else if(strcmp(_dataList[i].key, "co2") == 0) {
        if(_ccsSensor.dataAvailable()) {
          _ccsSensor.readAlgorithmResults();
          int co2 = _ccsSensor.getCO2();
          Serial.println(("co2:" + String(co2)).c_str());
          _serial.sendMessage(("co2:" + String(co2)).c_str());

          char postDataBuffer[129];
          snprintf(postDataBuffer, sizeof(postDataBuffer), "%s%d", DATA_50_URL, co2);
          Serial.println(postDataBuffer);
          getWebData(postDataBuffer);
        }
        _dataList[i].state = 1;
        Serial.println("Sent co2 value");
        break;
      }
      else if(strcmp(_dataList[i].key, "tvoc") == 0) {
        if(_ccsSensor.dataAvailable()) {
          _ccsSensor.readAlgorithmResults();
          int tvoc = _ccsSensor.getTVOC();
          Serial.println(("tvoc:" + String(tvoc)).c_str());
          _serial.sendMessage(("tvoc:" + String(tvoc)).c_str());

          char postDataBuffer[129];
          snprintf(postDataBuffer, sizeof(postDataBuffer), "%s%d", DATA_51_URL, tvoc);
          Serial.println(postDataBuffer);
          getWebData(postDataBuffer);
        }
        _dataList[i].state = 1;
        Serial.println("Sent tvoc value");
        break;
      }
      else {
        char result[32];
        snprintf(result, sizeof(result), "%s:%s", _dataList[i].key, getWebData(_dataList[i].uri).c_str());

        _serial.sendMessage(result);
        _dataList[i].state = 1;
        Serial.print("Sent ");
        Serial.print(_dataList[i].key);
        Serial.print(" = ");
        Serial.println(result);
        break;
      }
    }
  }

  unsigned long currentMillis = millis();
  if(currentMillis - _previousTimeMillis >= _delayTime) {
    timeClient.update();
    _previousTimeMillis = currentMillis;
  }

  currentMillis = millis();
  if(currentMillis - _previousMemMillis >= _delayMem) {
    char humidityBuffer[6];
    snprintf(humidityBuffer, sizeof(humidityBuffer), "%s", getWebData(DATA_08_URL).c_str());
    float humidity = strtof(humidityBuffer, NULL);
    Serial.print("Humidity=");
    Serial.println(humidity);

    char temperatureBuffer[6];
    snprintf(temperatureBuffer, sizeof(temperatureBuffer), "%s", getWebData(DATA_01_URL).c_str());
    float temperature = strtof(temperatureBuffer, NULL);
    Serial.print("Temperature=");
    Serial.println(temperature);

    _ccsSensor.setEnvironmentalData(humidity, temperature);

    Serial.print(F("Free heap : "));
    Serial.println(ESP.getFreeHeap());
    _previousMemMillis = currentMillis;
  }
}
