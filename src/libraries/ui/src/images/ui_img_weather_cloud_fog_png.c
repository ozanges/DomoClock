// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Waveshare-RP2040-Touch-LCD-1.28

#include "../ui.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
    #define LV_ATTRIBUTE_MEM_ALIGN
#endif

// IMAGE DATA: assets\weather_cloud_fog.png
const LV_ATTRIBUTE_MEM_ALIGN uint8_t ui_img_weather_cloud_fog_png_data[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x67,0xFF,0xFF,0xDE,0xFF,0xFF,0xFB,0xFF,0xFF,0xF1,0xFF,0xFF,0x97,0xFF,0xFF,0x0F,0x00,0x00,0x00,0xFF,0xFF,0x13,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x7B,0xFF,0xFF,0xE2,0xFF,0xFF,0x5C,0xFF,0xFF,0x22,0xFF,0xFF,0x37,0xFF,0xFF,0xB5,0xFF,0xFF,0xC8,0xFF,0xFF,0xBC,0xFF,0xFF,0xDA,0xFF,0xFF,0xC8,0xFF,0xFF,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x27,0xFF,0xFF,0xE4,0xFF,0xFF,0x39,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x07,0xFF,0xFF,0xAA,0xFF,0xFF,0x89,0xFF,0xFF,0x39,0xFF,0xFF,0x80,0xFF,0xFF,0xE8,0xFF,0xFF,0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x57,0xFF,0xFF,0xCB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xAC,0xFF,0xFF,0xB5,0xFF,0xFF,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x49,0xFF,0xFF,0xE9,0xFF,0xFF,0x8D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x5F,0xFF,0xFF,0xCF,0xFF,0xFF,0xDD,0xFF,0xFF,0x74,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x24,0xFF,0xFF,0xE4,0xFF,0xFF,0x6F,0xFF,0xFF,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x05,0xFF,0xFF,0x41,
    0xFF,0xFF,0xDE,0xFF,0xFF,0x56,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x88,0xFF,0xFF,0xAD,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x80,0xFF,0xFF,0xB5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x9B,0xFF,0xFF,0x9C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x69,0xFF,0xFF,0xB9,0xFF,0xFF,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x47,0xFF,0xFF,0xDA,0xFF,0xFF,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xFF,0xFF,0x0C,0xFF,0xFF,0xC4,0xFF,0xFF,0x83,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x89,0xFF,0xFF,0xD6,0xFF,0xFF,0x95,0xFF,0xFF,0x7C,0xFF,0xFF,0x7E,0xFF,0xFF,0x7E,0xFF,0xFF,0x7E,0xFF,0xFF,0x7E,0xFF,0xFF,0x7E,0xFF,0xFF,0x7E,0xFF,0xFF,0x7E,0xFF,0xFF,0x7E,0xFF,0xFF,0x7C,0xFF,0xFF,0x8A,0xFF,0xFF,0xCB,0xFF,0xFF,0xB9,0xFF,0xFF,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x54,0xFF,0xFF,0x9F,0xFF,0xFF,0xA5,0xFF,0xFF,0xA4,0xFF,0xFF,0xA4,0xFF,0xFF,0xA4,0xFF,0xFF,0xA4,0xFF,0xFF,0xA4,0xFF,0xFF,0xA4,0xFF,0xFF,0xA4,0xFF,0xFF,0xA4,0xFF,0xFF,0xA4,0xFF,0xFF,0xA3,0xFF,0xFF,0x6E,0xFF,0xFF,0x0B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x2A,0xFF,0xFF,0x47,0xFF,0xFF,0x45,0xFF,0xFF,0x45,0xFF,0xFF,0x45,0xFF,0xFF,0x45,0xFF,0xFF,0x44,0xFF,0xFF,0x44,0xFF,0xFF,0x44,0xFF,0xFF,0x44,0xFF,0xFF,0x44,0xFF,0xFF,0x44,0xFF,0xFF,0x44,0xFF,0xFF,0x44,0xFF,0xFF,0x44,0xFF,0xFF,0x44,0xFF,0xFF,0x45,0xFF,0xFF,0x45,0xFF,0xFF,0x48,0xFF,0xFF,0x2A,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x86,0xFF,0xFF,0xCD,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xC9,0xFF,0xFF,0xD0,0xFF,0xFF,0x83,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x05,0xFF,0xFF,0x0D,0xFF,0xFF,0x0A,0xFF,0xFF,0x07,0xFF,0xFF,0x07,0xFF,0xFF,0x07,0xFF,0xFF,0x07,0xFF,0xFF,0x08,0xFF,0xFF,0x0C,0xFF,0xFF,0x0C,0xFF,0xFF,0x08,0xFF,0xFF,0x07,
    0xFF,0xFF,0x07,0xFF,0xFF,0x07,0xFF,0xFF,0x07,0xFF,0xFF,0x07,0xFF,0xFF,0x07,0xFF,0xFF,0x07,0xFF,0xFF,0x07,0xFF,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x0C,0xFF,0xFF,0x20,0xFF,0xFF,0x1F,0xFF,0xFF,0x1F,0xFF,0xFF,0x21,0xFF,0xFF,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x18,0xFF,0xFF,0x20,0xFF,0xFF,0x1F,0xFF,0xFF,0x1F,0xFF,0xFF,0x1F,0xFF,0xFF,0x1F,0xFF,0xFF,0x1F,0xFF,0xFF,0x1F,0xFF,0xFF,0x1F,0xFF,0xFF,0x20,0xFF,0xFF,0x22,0xFF,0xFF,0x1A,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x6F,0xFF,0xFF,0xF2,0xFF,0xFF,0xEE,0xFF,0xFF,0xED,0xFF,0xFF,0xF5,0xFF,0xFF,0xB5,0x00,0x00,0x00,0xFF,0xFF,0x03,0xFF,0xFF,0xC9,0xFF,0xFF,0xF2,0xFF,0xFF,0xED,0xFF,0xFF,0xED,0xFF,0xFF,0xED,0xFF,0xFF,0xED,0xFF,0xFF,0xED,0xFF,0xFF,0xED,0xFF,0xFF,0xED,0xFF,0xFF,0xED,0xFF,0xFF,0xF0,0xFF,0xFF,0xC4,
};
const lv_img_dsc_t ui_img_weather_cloud_fog_png = {
    .header.always_zero = 0,
    .header.w = 22,
    .header.h = 17,
    .data_size = sizeof(ui_img_weather_cloud_fog_png_data),
    .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
    .data = ui_img_weather_cloud_fog_png_data
};

