// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Waveshare-RP2040-Touch-LCD-1.28

#include "../ui.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
    #define LV_ATTRIBUTE_MEM_ALIGN
#endif

// IMAGE DATA: assets\weather.png
const LV_ATTRIBUTE_MEM_ALIGN uint8_t ui_img_weather_png_data[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x01,0xFF,0xFF,0xA9,0xFF,0xFF,0xCB,0xFF,0xFF,0x2A,0xFF,0xFF,0x29,0xFF,0xFF,0xCA,0xFF,0xFF,0xAC,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x08,0xFF,0xFF,0xD9,0xFF,0xFF,0xA3,0xFF,0xFF,0xDF,0xFF,0xFF,0xE1,0xFF,0xFF,0xAA,0xFF,0xFF,0xE7,0xFF,0xFF,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x09,0xFF,0xFF,0x34,0xFF,0xFF,0x7D,0xFF,0xFF,0xD2,0xFF,0xFF,0x0E,0xFF,0xFF,0x44,0xFF,0xFF,0x49,0xFF,0xFF,0x08,0xFF,0xFF,0xD6,0xFF,0xFF,0x7B,0xFF,0xFF,0x33,0xFF,0xFF,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xA6,0xFF,0xFF,0xE2,0xFF,0xFF,0xB8,0xFF,0xFF,0x67,0xFF,0xFF,0x38,0xFF,0xFF,0x9A,0xFF,0xFF,0x95,0xFF,0xFF,0x46,0xFF,0xFF,0x8A,0xFF,0xFF,0xEB,0xFF,0xFF,0xEC,0xFF,0xFF,0x99,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x7D,0xFF,0xFF,0xCD,0xFF,0xFF,0x03,0xFF,0xFF,0x23,0xFF,0xFF,0xD9,0xFF,0xFF,0x7F,0xFF,0xFF,0xBC,0xFF,0xFF,0xF4,0xFF,0xFF,0xC9,0xFF,0xFF,0xD3,0xFF,0xFF,0xFB,0xFF,0xFF,0x8E,0xFF,0xFF,0x1E,0xFF,0xFF,0x1A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xBA,0xFF,0xFF,0x7A,0xFF,0xFF,0x5F,0xFF,0xFF,0xA8,0xFF,0xFF,0x30,0xFF,0xFF,0xD2,0xFF,0xFF,0x60,0xFF,0xFF,0x0F,0xFF,0xFF,0x19,0xFF,0xFF,0x89,0xFF,0xFF,0xEA,0xFF,0xFF,0xF2,0xFF,0xFF,0xE7,0xFF,0xFF,0x73,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x14,0xFF,0xFF,0xC6,0xFF,0xFF,0x52,0xFF,0xFF,0x4F,0xFF,0xFF,0xB7,0xFF,0xFF,0xAF,0xFF,0xFF,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x03,0xFF,0xFF,0x54,0xFF,0xFF,0x25,0xFF,0xFF,0x44,0xFF,0xFF,0xE7,0xFF,0xFF,0x45,0x00,0x00,0x00,0xFF,0xFF,0xA7,0xFF,0xFF,0xCF,0xFF,0xFF,0x19,0xFF,0xFF,0x14,0xFF,0xFF,0xBA,0xFF,0xFF,0xFF,0xFF,0xFF,0x35,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x96,0xFF,0xFF,0x85,0x00,0x00,0x00,0xFF,0xFF,0x6D,0xFF,0xFF,0xC6,0xFF,0xFF,0xF0,0xFF,0xFF,0xC3,0xFF,0xFF,0xD3,0xFF,0xFF,0xA4,0xFF,0xFF,0x17,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x8A,0xFF,0xFF,0xE3,0xFF,0xFF,0x3C,0x00,0x00,0x00,0xFF,0xFF,0x0B,0xFF,0xFF,0x3A,0xFF,0xFF,0xFD,0xFF,0xFF,0x7A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x08,0xFF,0xFF,0x77,0xFF,0xFF,0xE3,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x15,0xFF,0xFF,0xD7,0xFF,0xFF,0x23,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x04,0xFF,0xFF,0xC3,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x11,0xFF,0xFF,0xE3,0xFF,0xFF,0x3B,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x09,0xFF,0xFF,0xCD,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x82,0xFF,0xFF,0xD0,0xFF,0xFF,0x40,0xFF,0xFF,0x28,0xFF,0xFF,0x29,0xFF,0xFF,0x29,0xFF,0xFF,0x29,0xFF,0xFF,0x29,0xFF,0xFF,0x29,0xFF,0xFF,0x29,0xFF,0xFF,0x29,0xFF,0xFF,0x29,0xFF,0xFF,0x95,0xFF,0xFF,0xD5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x06,0xFF,0xFF,0x86,0xFF,0xFF,0xF1,0xFF,0xFF,0xF3,0xFF,0xFF,0xF1,0xFF,0xFF,0xF1,0xFF,0xFF,0xF1,0xFF,0xFF,0xF1,0xFF,0xFF,0xF1,0xFF,0xFF,0xF1,0xFF,0xFF,0xF0,0xFF,0xFF,0xFC,0xFF,0xFF,0xBE,0xFF,0xFF,0x23,
};
const lv_img_dsc_t ui_img_weather_png = {
    .header.always_zero = 0,
    .header.w = 17,
    .header.h = 14,
    .data_size = sizeof(ui_img_weather_png_data),
    .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
    .data = ui_img_weather_png_data
};
