#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include "CST816S.h"
#include <SoftwareSerial.h>

#include <time.h>
#include <sys/time.h>

#include <ArduinoJson.h>


/*Don't forget to set Sketchbook location in File/Preferencesto the path of your UI project (the parent foder of this INO file)*/

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

void Touch_INT_callback();
uint8_t flag = 0;

const byte txPin = 27;
const byte rxPin = 28;

SoftwareSerial mySerial (rxPin, txPin);
int myIndex = 0;

long            _delayTX            = 1000;
unsigned long   _previousTXMillis   = 0;
bool _isFirstTimeSet                = false;
float actualTemperature             = 0.0;
float minTemperature                = 0.0;
float maxTemperature                = 0.0;
String actualStatus                 = "";

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    bool touched = false;
    if (flag == 1)
    {
        touched = Touch_CTS816.x_point < screenWidth && Touch_CTS816.y_point < screenHeight;
        flag = 0;
    }

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = Touch_CTS816.x_point;
        data->point.y = Touch_CTS816.y_point;

        Serial.print( "Data x " );
        Serial.println( Touch_CTS816.x_point );

        Serial.print( "Data y " );
        Serial.println( Touch_CTS816.y_point );
    }
}

void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */

    if (DEV_Module_Init() != 0)
        Serial.println("GPIO Init Fail!");
    else
        Serial.println("GPIO Init successful!");

    CST816S_init(CST816S_Point_Mode);
    pinMode(Touch_INT_PIN, INPUT_PULLUP);
    attachInterrupt(Touch_INT_PIN, &Touch_INT_callback, RISING);

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    mySerial.begin(115200);

    tft.begin();          /* TFT init */
    tft.setRotation( 0 ); /* Landscape orientation, flipped */

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );


    ui_init();

    //secondes_Animation(ui_Secondes, 0);

    struct timeval tv;

    tv.tv_sec = 1704752282; // Jan 21, 2021  3:14:15AM ...RPi Pico Release;
    tv.tv_usec = 0;
    settimeofday(&tv, nullptr);

    Serial.println( "Setup done" );
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);

  // while (mySerial.available() > 0) {
  //   char recieved  = mySerial.read();
  //   if (recieved == '/i') {
  //     Serial.println("a");
  //   } else {
  //     Serial.println(recieved);
  //   }
  // }

  unsigned long currentMillis = millis();
  if (currentMillis - _previousTXMillis >= _delayTX) {
    _previousTXMillis = currentMillis;
    
    time_t now;
    char buff[80];

    time(&now);
    strftime(buff, sizeof(buff), "%c", localtime(&now));
    Serial.println(buff);

    char dayOfWeek[4];
    char month[4];
    int day;
    int hour, minute, second;
    int year;
    char formattedMinute[3];

    sscanf(buff, "%s %s %d %d:%d:%d %d", dayOfWeek, month, &day, &hour, &minute, &second, &year);
    sprintf(formattedMinute, "%02d", minute);

    // Affichage des résultats
    Serial.print("Jour de la semaine : "); Serial.println(dayOfWeek);
    Serial.print("Mois : "); Serial.println(month);
    Serial.print("Jour du mois : "); Serial.println(day);
    Serial.print("Heure : "); Serial.print(hour); Serial.print(":"); Serial.print(minute); Serial.print(":"); Serial.println(second);
    Serial.print("Année : "); Serial.println(year);
    Serial.print("formattedMinute : "); Serial.println(formattedMinute);

    int firstHour = hour / 10;
    int secondHour = hour % 10;
    int sec_angle = 3600 * second / 60;
    
    lv_label_set_text(ui_LbHour0h, String(firstHour).c_str());
    lv_label_set_text(ui_LbHourh0, String(secondHour).c_str());
    lv_label_set_text(ui_LbMinute00, String(formattedMinute).c_str());
    lv_label_set_text(ui_LbDayOfWeek, dayOfWeek);
    lv_label_set_text(ui_LbDate, String(String(day) + " " + month).c_str());
    lv_label_set_text(ui_LbYear, String(year).c_str());
    lv_img_set_angle(ui_ImgSeconde, sec_angle);

    String rangeTemperature = "Min: " + String(minTemperature, 0) + "° Max: " + String(maxTemperature, 0) + "°";
    lv_label_set_text(ui_LbActualWeatherText, actualStatus.c_str());
    lv_label_set_text(ui_LbActualTemperature, String(actualTemperature, 0).c_str());
    lv_label_set_text(ui_LbActualRangeTemperature, rangeTemperature.c_str());
  }

  if (!_isFirstTimeSet) {
    String data = "";
    while (mySerial.available() > 0) {
      data = mySerial.readStringUntil('\n');
    }

    if (data.length() > 0) {
      Serial.println(data);
      StaticJsonDocument<128> doc;
      DeserializationError    error = deserializeJson(doc, data);
      if (error) {
        Serial.print(F("RX() deserializeJson() failed: "));
        Serial.println(error.f_str());
        //return false;
      } else {
        struct timeval tv;
        tv.tv_sec = doc["ep"]; // Jan 21, 2021  3:14:15AM ...RPi Pico Release;
        tv.tv_usec = 0;
        settimeofday(&tv, nullptr);

        actualTemperature = doc["actp"];
        minTemperature = doc["mitp"];
        maxTemperature = doc["matp"];
        String actualStatusJson = doc["as"];
        actualStatus = actualStatusJson;

        _isFirstTimeSet = true;
      }
    }
  }
}

void Touch_INT_callback()
{

    if (Touch_CTS816.mode == CST816S_Gesture_Mode)
    {
        uint8_t gesture = CST816S_Get_Gesture();
        if (gesture == CST816S_Gesture_Long_Press)
        {
            flag = 1;
        }
    }
    else
    {
        CST816S_Get_Point();
        flag = 1;
    }
}
