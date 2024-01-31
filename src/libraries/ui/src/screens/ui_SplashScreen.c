// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Waveshare-RP2040-Touch-LCD-1.28

#include "../ui.h"

void ui_SplashScreen_screen_init(void)
{
ui_SplashScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_SplashScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Image1 = lv_img_create(ui_SplashScreen);
lv_img_set_src(ui_Image1, &ui_img_splash_screen_png);
lv_obj_set_width( ui_Image1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Image1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Image1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Image1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Image1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

lv_obj_add_event_cb(ui_SplashScreen, ui_event_SplashScreen, LV_EVENT_ALL, NULL);

}
