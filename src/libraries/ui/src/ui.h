// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Waveshare-RP2040-Touch-LCD-1.28

#ifndef _WAVESHARE_RP2040_TOUCH_LCD_1_28_UI_H
#define _WAVESHARE_RP2040_TOUCH_LCD_1_28_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "components/ui_comp.h"
#include "components/ui_comp_hook.h"
#include "ui_events.h"
void AniImgSeconde_Animation(lv_obj_t * TargetObject, int delay);
void AniGpHour_Animation(lv_obj_t * TargetObject, int delay);
void AniLbMinute00_Animation(lv_obj_t * TargetObject, int delay);
// SCREEN: ui_ScrClock
void ui_ScrClock_screen_init(void);
extern lv_obj_t * ui_ScrClock;
extern lv_obj_t * ui_Button1;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_ImgSeconde;
extern lv_obj_t * ui_LbMinute00;
extern lv_obj_t * ui_GpHour;
extern lv_obj_t * ui_LbHour0h;
extern lv_obj_t * ui_LbHourh0;
extern lv_obj_t * ui_BtGoToWeatherScreen;
extern lv_obj_t * ui_ImgWeather;
extern lv_obj_t * ui_ImgArc;
extern lv_obj_t * ui_PnlCalendar;
extern lv_obj_t * ui_LbDayOfWeek;
extern lv_obj_t * ui_LbDate;
extern lv_obj_t * ui_LbYear;
extern lv_obj_t * ui_PnlActualWeather;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_Image1;
void ui_event____initial_actions0(lv_event_t * e);
extern lv_obj_t * ui____initial_actions0;

LV_IMG_DECLARE(ui_img_background_png);    // assets\background.png
LV_IMG_DECLARE(ui_img_sec_dot_png);    // assets\sec_dot.png
LV_IMG_DECLARE(ui_img_weather_png);    // assets\weather.png
LV_IMG_DECLARE(ui_img_btn_bg_3_png);    // assets\btn_bg_3.png
LV_IMG_DECLARE(ui_img_weather_cloud_fog_png);    // assets\weather_cloud_fog.png

LV_FONT_DECLARE(ui_font_Montsererat_bold_12_extended);
LV_FONT_DECLARE(ui_font_Montserrat_light_120);
LV_FONT_DECLARE(ui_font_Montserrat_light_20_extended);
LV_FONT_DECLARE(ui_font_Montserrat_light_72);
LV_FONT_DECLARE(ui_font_Montserrat_medium_12_extended);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
