// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Waveshare-RP2040-Touch-LCD-1.28

#include "../ui.h"

void ui_ScrClock_screen_init(void)
{
    ui_ScrClock = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScrClock, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_ScrClock, &ui_img_background_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImgSeconde = lv_img_create(ui_ScrClock);
    lv_img_set_src(ui_ImgSeconde, &ui_img_sec_dot_png);
    lv_obj_set_width(ui_ImgSeconde, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ImgSeconde, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ImgSeconde, 0);
    lv_obj_set_y(ui_ImgSeconde, -115);
    lv_obj_set_align(ui_ImgSeconde, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImgSeconde, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ImgSeconde, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_pivot(ui_ImgSeconde, 4, 118);

    ui_LbMinute00 = lv_label_create(ui_ScrClock);
    lv_obj_set_width(ui_LbMinute00, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LbMinute00, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LbMinute00, 58);
    lv_obj_set_y(ui_LbMinute00, 6);
    lv_obj_set_align(ui_LbMinute00, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LbMinute00, "27");
    lv_obj_set_style_text_color(ui_LbMinute00, lv_color_hex(0xEE1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbMinute00, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbMinute00, &ui_font_Montserrat_light_72, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_GpHour = lv_obj_create(ui_ScrClock);
    lv_obj_set_width(ui_GpHour, 135);
    lv_obj_set_height(ui_GpHour, 135);
    lv_obj_clear_flag(ui_GpHour, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_GpHour, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_GpHour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_GpHour, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_GpHour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LbHour0h = lv_label_create(ui_GpHour);
    lv_obj_set_width(ui_LbHour0h, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LbHour0h, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LbHour0h, -35);
    lv_obj_set_y(ui_LbHour0h, 21);
    lv_obj_set_align(ui_LbHour0h, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LbHour0h, "2");
    lv_obj_set_style_text_color(ui_LbHour0h, lv_color_hex(0x393939), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbHour0h, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbHour0h, &ui_font_Montserrat_light_120, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LbHourh0 = lv_label_create(ui_GpHour);
    lv_obj_set_width(ui_LbHourh0, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LbHourh0, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LbHourh0, 47);
    lv_obj_set_y(ui_LbHourh0, 21);
    lv_obj_set_align(ui_LbHourh0, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_LbHourh0, "2");
    lv_obj_set_style_text_color(ui_LbHourh0, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbHourh0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbHourh0, &ui_font_Montserrat_light_120, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BtGoToWeatherScreen = lv_obj_create(ui_ScrClock);
    lv_obj_set_width(ui_BtGoToWeatherScreen, 48);
    lv_obj_set_height(ui_BtGoToWeatherScreen, 50);
    lv_obj_set_x(ui_BtGoToWeatherScreen, 88);
    lv_obj_set_y(ui_BtGoToWeatherScreen, 62);
    lv_obj_set_align(ui_BtGoToWeatherScreen, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_BtGoToWeatherScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_BtGoToWeatherScreen, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BtGoToWeatherScreen, lv_color_hex(0xEE1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BtGoToWeatherScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BtGoToWeatherScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BtGoToWeatherScreen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BtGoToWeatherScreen, lv_color_hex(0xEE1E1E), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_BtGoToWeatherScreen, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_ImgWeather = lv_img_create(ui_BtGoToWeatherScreen);
    lv_img_set_src(ui_ImgWeather, &ui_img_weather_png);
    lv_obj_set_width(ui_ImgWeather, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ImgWeather, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ImgWeather, -8);
    lv_obj_set_y(ui_ImgWeather, -6);
    lv_obj_set_align(ui_ImgWeather, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImgWeather, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ImgWeather, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ImgArc = lv_img_create(ui_BtGoToWeatherScreen);
    lv_img_set_src(ui_ImgArc, &ui_img_btn_bg_3_png);
    lv_obj_set_width(ui_ImgArc, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ImgArc, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ImgArc, 5);
    lv_obj_set_y(ui_ImgArc, 2);
    lv_obj_set_align(ui_ImgArc, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImgArc, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ImgArc, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_PnlCalendar = lv_obj_create(ui_ScrClock);
    lv_obj_set_width(ui_PnlCalendar, 100);
    lv_obj_set_height(ui_PnlCalendar, 50);
    lv_obj_set_x(ui_PnlCalendar, 53);
    lv_obj_set_y(ui_PnlCalendar, -64);
    lv_obj_set_align(ui_PnlCalendar, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PnlCalendar, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PnlCalendar, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PnlCalendar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PnlCalendar, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PnlCalendar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LbDayOfWeek = lv_label_create(ui_PnlCalendar);
    lv_obj_set_width(ui_LbDayOfWeek, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LbDayOfWeek, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LbDayOfWeek, -20);
    lv_obj_set_y(ui_LbDayOfWeek, -15);
    lv_obj_set_align(ui_LbDayOfWeek, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LbDayOfWeek, "MON");
    lv_obj_set_style_text_color(ui_LbDayOfWeek, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbDayOfWeek, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbDayOfWeek, &ui_font_Montsererat_bold_12_extended, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LbDate = lv_label_create(ui_PnlCalendar);
    lv_obj_set_width(ui_LbDate, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LbDate, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LbDate, -15);
    lv_obj_set_y(ui_LbDate, 0);
    lv_obj_set_align(ui_LbDate, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LbDate, "18 FEB");
    lv_obj_set_style_text_color(ui_LbDate, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbDate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbDate, &ui_font_Montserrat_medium_12_extended, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LbYear = lv_label_create(ui_PnlCalendar);
    lv_obj_set_width(ui_LbYear, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LbYear, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LbYear, -21);
    lv_obj_set_y(ui_LbYear, 14);
    lv_obj_set_align(ui_LbYear, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LbYear, "2022");
    lv_obj_set_style_text_color(ui_LbYear, lv_color_hex(0x6B6B6B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbYear, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbYear, &ui_font_Montserrat_medium_12_extended, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PnlActualWeather = lv_obj_create(ui_ScrClock);
    lv_obj_set_width(ui_PnlActualWeather, 79);
    lv_obj_set_height(ui_PnlActualWeather, 32);
    lv_obj_set_x(ui_PnlActualWeather, -33);
    lv_obj_set_y(ui_PnlActualWeather, 21);
    lv_obj_set_align(ui_PnlActualWeather, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PnlActualWeather, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PnlActualWeather, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PnlActualWeather, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PnlActualWeather, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PnlActualWeather, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LbActualTemperature = lv_label_create(ui_PnlActualWeather);
    lv_obj_set_width(ui_LbActualTemperature, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LbActualTemperature, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LbActualTemperature, -14);
    lv_obj_set_y(ui_LbActualTemperature, -3);
    lv_obj_set_align(ui_LbActualTemperature, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LbActualTemperature, "26°");
    lv_obj_set_style_text_color(ui_LbActualTemperature, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbActualTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbActualTemperature, &ui_font_Montserrat_light_20_extended,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImgActualWeather = lv_img_create(ui_PnlActualWeather);
    lv_img_set_src(ui_ImgActualWeather, &ui_img_weather_cloud_fog_png);
    lv_obj_set_width(ui_ImgActualWeather, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ImgActualWeather, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ImgActualWeather, 17);
    lv_obj_set_y(ui_ImgActualWeather, -3);
    lv_obj_set_align(ui_ImgActualWeather, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImgActualWeather, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ImgActualWeather, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_PnlTemperature = lv_obj_create(ui_ScrClock);
    lv_obj_set_width(ui_PnlTemperature, 126);
    lv_obj_set_height(ui_PnlTemperature, 50);
    lv_obj_set_x(ui_PnlTemperature, 0);
    lv_obj_set_y(ui_PnlTemperature, 55);
    lv_obj_set_align(ui_PnlTemperature, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PnlTemperature, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PnlTemperature, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PnlTemperature, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PnlTemperature, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PnlTemperature, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LbActualWeatherText = lv_label_create(ui_PnlTemperature);
    lv_obj_set_width(ui_LbActualWeatherText, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LbActualWeatherText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LbActualWeatherText, -4);
    lv_obj_set_y(ui_LbActualWeatherText, -11);
    lv_obj_set_align(ui_LbActualWeatherText, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LbActualWeatherText, "Party Cloudly");
    lv_obj_set_style_text_color(ui_LbActualWeatherText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbActualWeatherText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbActualWeatherText, &ui_font_Montserrat_medium_12_extended,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LbActualRangeTemperature = lv_label_create(ui_PnlTemperature);
    lv_obj_set_width(ui_LbActualRangeTemperature, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LbActualRangeTemperature, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LbActualRangeTemperature, 3);
    lv_obj_set_y(ui_LbActualRangeTemperature, 4);
    lv_obj_set_align(ui_LbActualRangeTemperature, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LbActualRangeTemperature, "Max: 18° Min: 12°");
    lv_obj_set_style_text_color(ui_LbActualRangeTemperature, lv_color_hex(0x6D6D6D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbActualRangeTemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbActualRangeTemperature, &ui_font_Montserrat_medium_12_extended,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PnlElectricity = lv_obj_create(ui_ScrClock);
    lv_obj_set_width(ui_PnlElectricity, 170);
    lv_obj_set_height(ui_PnlElectricity, 115);
    lv_obj_set_align(ui_PnlElectricity, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_clear_flag(ui_PnlElectricity, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PnlElectricity, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PnlElectricity, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PnlElectricity, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PnlElectricity, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ArcMainElectricity = lv_arc_create(ui_PnlElectricity);
    lv_obj_set_width(ui_ArcMainElectricity, 250);
    lv_obj_set_height(ui_ArcMainElectricity, 245);
    lv_obj_set_x(ui_ArcMainElectricity, 49);
    lv_obj_set_y(ui_ArcMainElectricity, -74);
    lv_obj_set_align(ui_ArcMainElectricity, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ArcMainElectricity, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_arc_set_value(ui_ArcMainElectricity, 90);
    lv_arc_set_bg_angles(ui_ArcMainElectricity, 97, 160);
    lv_obj_set_style_border_color(ui_ArcMainElectricity, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ArcMainElectricity, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_ArcMainElectricity, lv_color_hex(0x303030), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_ArcMainElectricity, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_ArcMainElectricity, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui_ArcMainElectricity, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_ArcMainElectricity, lv_color_hex(0xB0E14A), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_ArcMainElectricity, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_ArcMainElectricity, 6, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui_ArcMainElectricity, true, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_ArcMainElectricity, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ArcMainElectricity, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_ArcSecondElectricity = lv_arc_create(ui_PnlElectricity);
    lv_obj_set_width(ui_ArcSecondElectricity, 250);
    lv_obj_set_height(ui_ArcSecondElectricity, 245);
    lv_obj_set_x(ui_ArcSecondElectricity, 55);
    lv_obj_set_y(ui_ArcSecondElectricity, -81);
    lv_obj_set_align(ui_ArcSecondElectricity, LV_ALIGN_CENTER);
    lv_arc_set_value(ui_ArcSecondElectricity, 50);
    lv_arc_set_bg_angles(ui_ArcSecondElectricity, 100, 135);
    lv_obj_set_style_arc_width(ui_ArcSecondElectricity, 6, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_ArcSecondElectricity, lv_color_hex(0xFF8F40), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_ArcSecondElectricity, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_ArcSecondElectricity, 6, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_ArcSecondElectricity, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ArcSecondElectricity, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_ArcThirdElectricity = lv_arc_create(ui_PnlElectricity);
    lv_obj_set_width(ui_ArcThirdElectricity, 250);
    lv_obj_set_height(ui_ArcThirdElectricity, 245);
    lv_obj_set_x(ui_ArcThirdElectricity, 61);
    lv_obj_set_y(ui_ArcThirdElectricity, -88);
    lv_obj_set_align(ui_ArcThirdElectricity, LV_ALIGN_CENTER);
    lv_arc_set_value(ui_ArcThirdElectricity, 50);
    lv_arc_set_bg_angles(ui_ArcThirdElectricity, 103, 120);
    lv_obj_set_style_arc_width(ui_ArcThirdElectricity, 6, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_ArcThirdElectricity, lv_color_hex(0xFF4040), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_ArcThirdElectricity, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_ArcThirdElectricity, 6, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_ArcThirdElectricity, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ArcThirdElectricity, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

}
