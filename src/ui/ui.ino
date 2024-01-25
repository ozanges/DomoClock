/*Don't forget to set Sketchbook location in File/Preferencesto the path of your UI project (the parent foder of this INO file)*/

#include "communication.h"
#include "CST816S.h"
#include "SerialData.h"
#include <lvgl.h>
#include <sys/time.h>
#include <time.h>
#include <TFT_eSPI.h>
#include <ui.h>

#define  DATALIST_SIZE 8

/*Change to your screen resolution*/
static const uint16_t     _screenWidth  = 240;
static const uint16_t     _screenHeight = 240;
static lv_disp_draw_buf_t _draw_buf;
static lv_color_t         _buf[ _screenWidth * _screenHeight / 10 ];
uint8_t                   flag                         = 0;
const byte                _txPin                       = 27;
const byte                _rxPin                       = 28;
long                      _delayTX                     = 1000;
unsigned long             _previousTXMillis            = 0;
bool                      _isFirstTimeSet              = false;
float                     _actualTemperature           = 0.0;
float                     _minTemperature              = 0.0;
float                     _maxTemperature              = 0.0;
String                    _actualStatus                = "";
int                       _houseTodayPricePercentage   = 0;
int                       _laundryTodayPricePercentage = 0;
int                       _garageTodayPricePercentage  = 0;
bool                      _isEpochFirstValidation      = true;
int                       _tft_backlight_value         = 0;
RequestData               _dataList[DATALIST_SIZE];

TFT_eSPI                  _tft = TFT_eSPI(_screenWidth, _screenHeight);
Communication             _serial(_rxPin, _txPin);

void compute_color            (uint8_t valeur, uint8_t* rouge, uint8_t* vert, uint8_t* bleu);
void disp_flush               (lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void on_background_clicked    (lv_event_t * e);
void set_backlight_intensity  (uint8_t Value);
void touch_callback           ();
void touchpad_read            (lv_indev_drv_t * indev_driver, lv_indev_data_t * data);

#if LV_USE_LOG != 0
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

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
    attachInterrupt(Touch_INT_PIN, &touch_callback, RISING);

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    _serial.setup();
    _tft.begin();          
    _tft.setRotation( 0 ); 
    set_backlight_intensity(75);

    lv_disp_draw_buf_init( &_draw_buf, _buf, NULL, _screenWidth * _screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = _screenWidth;
    disp_drv.ver_res = _screenHeight;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &_draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    lv_indev_drv_register( &indev_drv );

    ui_init();

    //secondes_Animation(ui_Secondes, 0);

    struct timeval tv;
    tv.tv_sec =  320185583;
    tv.tv_usec = 0;
    settimeofday(&tv, nullptr);

    delay(7000); // delay for start SerialLog

    Serial.println( "Setup done" );
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
      _actualTemperature = strtof(response.value, NULL);
      Serial.print("_actualTemperature=");
      Serial.println(_actualTemperature);
      mustAknowledgeState = true;
    } else if (strcmp(response.key, "mitp") == 0)  {
      _minTemperature = strtof(response.value, NULL);
      mustAknowledgeState = true;
      Serial.print("mitp=");
      Serial.println(_minTemperature);
    } else if (strcmp(response.key, "matp") == 0)  {
      _maxTemperature = strtof(response.value, NULL);
      mustAknowledgeState = true;
      Serial.print("matp=");
      Serial.println(mustAknowledgeState);
    } else if (strcmp(response.key, "as") == 0)  {
      _actualStatus = response.value;
      mustAknowledgeState = true;
      Serial.print("as=");
      Serial.println(_actualStatus);
    } else if (strcmp(response.key, "hp") == 0)  {
      _houseTodayPricePercentage = atoi(response.value);
      mustAknowledgeState = true;
      Serial.print("hp=");
      Serial.println(_houseTodayPricePercentage);
    } else if (strcmp(response.key, "lp") == 0)  {
      _laundryTodayPricePercentage = atoi(response.value);
      mustAknowledgeState = true;
      Serial.print("lp=");
      Serial.println(_laundryTodayPricePercentage);
    } else if (strcmp(response.key, "gp") == 0)  {
      _garageTodayPricePercentage = atoi(response.value);
      mustAknowledgeState = true;
      Serial.print("gp=");
      Serial.println(_garageTodayPricePercentage);
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

      String rangeTemperature = "Min: " + String(_minTemperature, 0) + "° Max: " + String(_maxTemperature, 0) + "°";
      lv_label_set_text(ui_LbActualWeatherText, _actualStatus.c_str());
      lv_label_set_text(ui_LbActualTemperature, String(_actualTemperature, 0).c_str());
      lv_label_set_text(ui_LbActualRangeTemperature, rangeTemperature.c_str());

      lv_arc_set_value(ui_ArcMainElectricity, _houseTodayPricePercentage);
      lv_arc_set_value(ui_ArcSecondElectricity, _laundryTodayPricePercentage);
      lv_arc_set_value(ui_ArcThirdElectricity, _garageTodayPricePercentage);

      uint8_t rouge, vert, bleu;
      compute_color(_houseTodayPricePercentage, &rouge, &vert, &bleu);
      lv_color_t color = lv_color_make(rouge, vert, bleu);
      lv_obj_set_style_arc_color(ui_ArcMainElectricity, color, LV_PART_INDICATOR | LV_STATE_DEFAULT);

      compute_color(_laundryTodayPricePercentage, &rouge, &vert, &bleu);
      color = lv_color_make(rouge, vert, bleu);
      lv_obj_set_style_arc_color(ui_ArcSecondElectricity, color, LV_PART_INDICATOR | LV_STATE_DEFAULT);
      
      compute_color(_garageTodayPricePercentage, &rouge, &vert, &bleu);
      color = lv_color_make(rouge, vert, bleu);
      lv_obj_set_style_arc_color(ui_ArcThirdElectricity, color, LV_PART_INDICATOR | LV_STATE_DEFAULT);
  }
}

void compute_color(uint8_t valeur, uint8_t* rouge, uint8_t* vert, uint8_t* bleu) {
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

/* Display flushing */
void disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    _tft.startWrite();
    _tft.setAddrWindow( area->x1, area->y1, w, h );
    _tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    _tft.endWrite();

    lv_disp_flush_ready( disp );
}

void on_background_clicked(lv_event_t * e)
{
	if (_tft_backlight_value < 100) {
		_tft_backlight_value = _tft_backlight_value + 15;
	}

	if (_tft_backlight_value > 100) {
		_tft_backlight_value = 0;
	}

	set_backlight_intensity(_tft_backlight_value);
}

void set_backlight_intensity(uint8_t Value) {
  if (Value < 0 || Value > 100) {
    printf("set_backlight_intensity Error \r\n");
  } else {
    analogWrite(TFT_BL, Value * 2.55);
  }
}

void touch_callback()
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

/*Read the touchpad*/
void touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    bool touched = false;
    if (flag == 1)
    {
        touched = Touch_CTS816.x_point < _screenWidth && Touch_CTS816.y_point < _screenHeight;
        flag = 0;
    }

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = Touch_CTS816.x_point;
        data->point.y = Touch_CTS816.y_point;

        // Serial.print( "Data x " );
        // Serial.println( Touch_CTS816.x_point );

        // Serial.print( "Data y " );
        // Serial.println( Touch_CTS816.y_point );
    }
}