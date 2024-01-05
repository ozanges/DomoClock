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
#include "ui_events.h"
void secondes_Animation(lv_obj_t * TargetObject, int delay);
// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_Button1;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Hour_Label_00;
extern lv_obj_t * ui_Hour_Label_01;
extern lv_obj_t * ui_Minute_Label_00;
extern lv_obj_t * ui_Secondes;
extern lv_obj_t * ui____initial_actions0;

LV_IMG_DECLARE(ui_img_background_png);    // assets\background.png
LV_IMG_DECLARE(ui_img_sec_dot_png);    // assets\sec_dot.png

LV_FONT_DECLARE(ui_font_Montserrat_light_120);
LV_FONT_DECLARE(ui_font_Montserrat_light_72);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
