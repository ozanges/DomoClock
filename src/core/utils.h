#include "debug.h"

#define MAX_NEGATIVE_DEEPSLEEP_MESSAGE 3

void blink(int count)
{
  for(int i = 0; i < count; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(125);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(125);
  }
}

int _negativeDeepSleepMessageCount = 0;

/*
 * ESP8266 : Remember to connect physically RESET pin (with D0 for Wemos)
 */
void deepSleep(int second)
{
  if(second > 0) {
    delay(2000); // Minimum to give a chance to the previous action to finish (eg. data transfert over wifi)
    DPRINT(F("Going to sleep for "));
    DPRINT(second);
    DPRINTLN(F(" sec."));
    ESP.deepSleep(second * 1000000);
  }
  else {
    if(_negativeDeepSleepMessageCount++ < MAX_NEGATIVE_DEEPSLEEP_MESSAGE) {
      DPRINTLN(F("second parameter is negative, cannot going to deepsleep."));
    }
  }
}
