// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Waveshare-RP2040-Touch-LCD-1.28

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_Screen1, &ui_img_background_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button1 = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_Button1, 100);
    lv_obj_set_height(ui_Button1, 50);
    lv_obj_set_x(ui_Button1, 0);
    lv_obj_set_y(ui_Button1, 64);
    lv_obj_set_align(ui_Button1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label1 = lv_label_create(ui_Button1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "Click");

    ui_Secondes = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Secondes, &ui_img_sec_dot_png);
    lv_obj_set_width(ui_Secondes, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Secondes, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Secondes, 0);
    lv_obj_set_y(ui_Secondes, -115);
    lv_obj_set_align(ui_Secondes, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Secondes, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Secondes, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_pivot(ui_Secondes, 4, 118);

    ui_Minute_label_00 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Minute_label_00, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Minute_label_00, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Minute_label_00, 45);
    lv_obj_set_y(ui_Minute_label_00, 6);
    lv_obj_set_align(ui_Minute_label_00, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Minute_label_00, "27");
    lv_obj_set_style_text_color(ui_Minute_label_00, lv_color_hex(0xEE1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Minute_label_00, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Minute_label_00, &ui_font_Montserrat_light_72, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Hour_group = ui_Hour_group_create(ui_Screen1);
    lv_obj_set_width(ui_Hour_group, 135);
    lv_obj_set_height(ui_Hour_group, 135);
    lv_obj_set_x(ui_Hour_group, 0);
    lv_obj_set_y(ui_Hour_group, 0);
    lv_obj_set_align(ui_Hour_group, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_layout(ui_Hour_group, 0, 0);
    lv_obj_set_style_bg_color(ui_Hour_group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Hour_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Hour_group, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Hour_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Hour_Label_00 = lv_label_create(ui_Hour_group);
    lv_obj_set_width(ui_Hour_Label_00, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Hour_Label_00, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Hour_Label_00, -38);
    lv_obj_set_y(ui_Hour_Label_00, 22);
    lv_obj_set_align(ui_Hour_Label_00, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Hour_Label_00, "0");
    lv_obj_set_style_text_color(ui_Hour_Label_00, lv_color_hex(0x393939), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Hour_Label_00, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Hour_Label_00, &ui_font_Montserrat_light_120, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Hour_label_01 = lv_label_create(ui_Hour_group);
    lv_obj_set_width(ui_Hour_label_01, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Hour_label_01, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Hour_label_01, 41);
    lv_obj_set_y(ui_Hour_label_01, 21);
    lv_obj_set_align(ui_Hour_label_01, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Hour_label_01, "3");
    lv_obj_set_style_text_color(ui_Hour_label_01, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Hour_label_01, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Hour_label_01, &ui_font_Montserrat_light_120, LV_PART_MAIN | LV_STATE_DEFAULT);

}
