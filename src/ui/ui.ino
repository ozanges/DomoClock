#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include "CST816S.h"
#include "communication.h"
#include <time.h>
#include <sys/time.h>

struct RequestData{
  char key[5];
  int  previousMillis;
  int  refreshDelay;
  int  acknowledgeState; // 0 = must be initialized ; 1 = sent notification; 2 = acknowledged
};

struct ResponseData{
  char *key;
  const char *value;
};

#define  DATALIST_SIZE 8
RequestData _dataList[DATALIST_SIZE];

/*Don't forget to set Sketchbook location in File/Preferencesto the path of your UI project (the parent foder of this INO file)*/

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

void Touch_INT_callback();
uint8_t flag = 0;

const byte _txPin = 27;
const byte _rxPin = 28;

//SoftwareSerial mySerial (rxPin, txPin);
Communication _serial(_rxPin, _txPin);


long            _delayTX            = 1000;
unsigned long   _previousTXMillis   = 0;
bool _isFirstTimeSet                = false;
float actualTemperature             = 0.0;
float minTemperature                = 0.0;
float maxTemperature                = 0.0;
String actualStatus                 = "";
int houseTodayPricePercentage       = 0;
int laundryTodayPricePercentage     = 0;
int garageTodayPricePercentage      = 0;
bool _isEpochFirstValidation        = true;

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

void TFT_SET_BL(uint8_t Value) {
  if (Value < 0 || Value > 100) {
    printf("TFT_SET_BL Error \r\n");
  } else {
    analogWrite(TFT_BL, Value * 2.55);
  }
}

int _tft_backlight_value = 0;

void OnBackgrounClicked(lv_event_t * e)
{
	if (_tft_backlight_value < 100) {
		_tft_backlight_value = _tft_backlight_value + 15;
	}

	if (_tft_backlight_value > 100) {
		_tft_backlight_value = 0;
	}

	TFT_SET_BL(_tft_backlight_value);
}

void setup()
{
    _dataList[0] = {"ep", millis(), /*5 * 60*/ 30 * 1000, 0}; // 5 min
    _dataList[1] = {"actp", millis(), 2 * 60 * 1000, 0}; // 2 min
    _dataList[2] = {"mitp", millis(), 2 * 60 * 1000, 0};
    _dataList[3] = {"matp", millis(), 2 * 60 * 1000, 0};
    _dataList[4] = {"as", millis(), 30 * 60 * 1000, 0}; // 30 min
    _dataList[5] = {"hp", millis(), 5 * 60 * 1000, 0}; // 5 min
    _dataList[6] = {"lp", millis(), 5 * 60 * 1000, 0}; // 5 min
    _dataList[7] = {"gp", millis(), 5 * 60 * 1000, 0}; // 5 min

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

    // pinMode(rxPin, INPUT);
    // pinMode(txPin, OUTPUT);
    // mySerial.begin(115200);
    _serial.setup();

    tft.begin();          /* TFT init */
    tft.setRotation( 0 ); /* Landscape orientation, flipped */
    
    // TFT_SET_BL(75); // set back light brightness

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

    delay(7000); // delay for start SerialLog

    Serial.println( "Setup done" );
}

void calculerCouleur(uint8_t valeur, uint8_t* rouge, uint8_t* vert, uint8_t* bleu) {
    if (valeur <= 33) {
        // Vert à Jaune
        *rouge = map(valeur, 0, 33, 0, 255);
        *vert = 255;
        *bleu = 0;
    } else if (valeur <= 66) {
        // Jaune à Rouge
        *rouge = 255;
        *vert = map(valeur, 34, 66, 255, 0);
        *bleu = 0;
    } else {
        // Rouge
        *rouge = 255;
        *vert = 0;
        *bleu = 0;
    }
}

void displayDataListValue(String title) {
  Serial.print(title);
  for (int i = 0; i < DATALIST_SIZE; i++) {
    Serial.print(_dataList[i].key);
    Serial.print(".state=");
    Serial.print(_dataList[i].acknowledgeState);
    Serial.print(" - ");
  }

  Serial.println();
}

bool is_valid_timestamp(const char *str) {
    // Vérifier que la chaîne ne contient que des chiffres
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            Serial.println("timestamp : valeur non numérique");
            return false;
        }
    }

    // Vérifier la plage de la valeur (optionnel, ajustez selon vos besoins)
    long long timestamp = strtoll(str, NULL, 10);
    if (strlen(str) != 10 || timestamp < 0 /* || timestamp > time(NULL)*/) {
        Serial.println("timestamp : incohérence de valeur");
        return false;
    }

    if (!_isEpochFirstValidation) {
      time_t now = time(NULL);
      Serial.print("time(NULL) = ");
      Serial.println(now);
      if (timestamp < now - (5 * 60)  || timestamp > now + (5 * 60)) {
        Serial.println("timestamp : différence de valeur trop grande.");
        return false;
      }
    }

    return true;
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);

  if (_serial.listen()) {
    char * message = _serial.getMessage();
    Serial.print(F("Received: ")); Serial.println(message);
    const char delimiter[2] = ":";

    ResponseData response = ResponseData();
    response.key = strtok(message, delimiter);
    response.value = strtok(NULL, delimiter);
    // Serial.print("** Response key=");
    // Serial.print(response.key);
    // Serial.print(";value=");
    // Serial.println(response.value);

    bool mustAknowledgeState = false;
    if (strcmp(response.key, "ep") == 0)  {
      struct timeval tv;
      if (is_valid_timestamp(response.value)) {
        tv.tv_sec = strtoll(response.value, NULL, 10);
        tv.tv_usec = 0;
        settimeofday(&tv, nullptr);
        mustAknowledgeState = true;
        Serial.print("epoch=");
        Serial.println(tv.tv_sec);
        _isEpochFirstValidation = false;
      } 
    } else if (strcmp(response.key, "actp") == 0)  {
      actualTemperature = strtof(response.value, NULL);
      Serial.print("actualTemperature=");
      Serial.println(actualTemperature);
      mustAknowledgeState = true;
    } else if (strcmp(response.key, "mitp") == 0)  {
      minTemperature = strtof(response.value, NULL);
      mustAknowledgeState = true;
      Serial.print("mitp=");
      Serial.println(minTemperature);
    } else if (strcmp(response.key, "matp") == 0)  {
      maxTemperature = strtof(response.value, NULL);
      mustAknowledgeState = true;
      Serial.print("matp=");
      Serial.println(mustAknowledgeState);
    } else if (strcmp(response.key, "as") == 0)  {
      actualStatus = response.value;
      mustAknowledgeState = true;
      Serial.print("as=");
      Serial.println(actualStatus);
    } else if (strcmp(response.key, "hp") == 0)  {
      houseTodayPricePercentage = atoi(response.value);
      mustAknowledgeState = true;
      Serial.print("hp=");
      Serial.println(houseTodayPricePercentage);
    } else if (strcmp(response.key, "lp") == 0)  {
      laundryTodayPricePercentage = atoi(response.value);
      mustAknowledgeState = true;
      Serial.print("lp=");
      Serial.println(laundryTodayPricePercentage);
    } else if (strcmp(response.key, "gp") == 0)  {
      garageTodayPricePercentage = atoi(response.value);
      mustAknowledgeState = true;
      Serial.print("gp=");
      Serial.println(garageTodayPricePercentage);
    } else {
      Serial.println("Unknown data response !");
    }

    displayDataListValue("before mustAknowledgeState : ");
    if (mustAknowledgeState) {
      for (int i = 0; i < DATALIST_SIZE; i++) {
        if (strcmp(response.key, _dataList[i].key) == 0) {
          _dataList[i].acknowledgeState = 2;
          Serial.print("Aknowledged : ");
          Serial.println(_dataList[i].key);
          break;
        }
      }
    }
    displayDataListValue("after mustAknowledgeState : ");
  }

  RequestData mustAknowledgeData = {"NULL", 0, 0, 0};;
  for (int i = 0; i < DATALIST_SIZE; i++) {
    if (_dataList[i].acknowledgeState == 1) {
      mustAknowledgeData = _dataList[i];
      break;
    }
  }

  unsigned long currentMillis = millis();
  if (strcmp(mustAknowledgeData.key, "NULL") != 0) {
    if (currentMillis - _previousTXMillis >= _delayTX + 1000) {
      _previousTXMillis = currentMillis;

      displayDataListValue("before ask for aknowledgment : ");
      mustAknowledgeData.previousMillis = currentMillis;
      Serial.print("************ MUST AKNOWLEDGE : ");
      Serial.println(mustAknowledgeData.key);
      _serial.sendMessage(mustAknowledgeData.key);
    }
  } else {
    currentMillis = millis();
    for (int i = 0; i < DATALIST_SIZE; i++) {
      currentMillis = millis();
      bool mustBeInitialized = _dataList[i].acknowledgeState == 0;
      bool isTimeToRefresh = currentMillis - _dataList[i].previousMillis >= _dataList[i].refreshDelay;
      if (mustBeInitialized || isTimeToRefresh) {
        Serial.print("mustBeInitialized = "); 
        Serial.print(mustBeInitialized); 
        Serial.print("; isTimeToRefresh = "); 
        Serial.println(isTimeToRefresh); 
        displayDataListValue("before asking : ");    
        _dataList[i].previousMillis = currentMillis;

        Serial.print("************ ASKING FOR : ");
        Serial.println(_dataList[i].key);
        _serial.sendMessage(_dataList[i].key);
        _dataList[i].acknowledgeState = 1;

        break;
        // Serial.print("i=");
        // Serial.print(i);
        // Serial.print(";key=");
        // Serial.print(_dataList[i].key);
        // Serial.print(";previousMillis=");
        // Serial.print(_dataList[i].previousMillis);
        // Serial.print(";refreshDelay=");
        // Serial.println(_dataList[i].refreshDelay);
      }
    }
  }

  currentMillis = millis();
  if (currentMillis - _previousTXMillis >= _delayTX + 1000) {
      _previousTXMillis = currentMillis;

      time_t now;
      char buff[80];

      time(&now);
      strftime(buff, sizeof(buff), "%c", localtime(&now));
      //Serial.println(buff);

      char dayOfWeek[4];
      char month[4];
      int day;
      int hour, minute, second;
      int year;
      char formattedMinute[3];

      sscanf(buff, "%s %s %d %d:%d:%d %d", dayOfWeek, month, &day, &hour, &minute, &second, &year);
      sprintf(formattedMinute, "%02d", minute);

      // Affichage des résultats
      // Serial.print("Jour de la semaine : "); Serial.println(dayOfWeek);
      // Serial.print("Mois : "); Serial.println(month);
      // Serial.print("Jour du mois : "); Serial.println(day);
      // Serial.print("Heure : "); Serial.print(hour); Serial.print(":"); Serial.print(minute); Serial.print(":"); Serial.println(second);
      // Serial.print("Année : "); Serial.println(year);
      // Serial.print("formattedMinute : "); Serial.println(formattedMinute);

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

      lv_arc_set_value(ui_ArcMainElectricity, houseTodayPricePercentage);
      lv_arc_set_value(ui_ArcSecondElectricity, laundryTodayPricePercentage);
      lv_arc_set_value(ui_ArcThirdElectricity, garageTodayPricePercentage);

      uint8_t rouge, vert, bleu;
      calculerCouleur(houseTodayPricePercentage, &rouge, &vert, &bleu);
      lv_color_t color = lv_color_make(rouge, vert, bleu);
      lv_obj_set_style_arc_color(ui_ArcMainElectricity, color, LV_PART_INDICATOR | LV_STATE_DEFAULT);

      calculerCouleur(laundryTodayPricePercentage, &rouge, &vert, &bleu);
      color = lv_color_make(rouge, vert, bleu);
      lv_obj_set_style_arc_color(ui_ArcSecondElectricity, color, LV_PART_INDICATOR | LV_STATE_DEFAULT);
      
      calculerCouleur(garageTodayPricePercentage, &rouge, &vert, &bleu);
      color = lv_color_make(rouge, vert, bleu);
      lv_obj_set_style_arc_color(ui_ArcThirdElectricity, color, LV_PART_INDICATOR | LV_STATE_DEFAULT);
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
