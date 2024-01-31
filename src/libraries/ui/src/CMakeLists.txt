SET(SOURCES components/ui_comp_hour_group.c
    components/ui_comp.c
    screens/ui_ScrClock.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_background_png.c
    images/ui_img_sec_dot_png.c
    images/ui_img_weather_png.c
    images/ui_img_btn_bg_3_png.c
    images/ui_img_weather_thunderstorm_png.c
    fonts/ui_font_Montsererat_bold_12_extended.c
    fonts/ui_font_Montserrat_light_120.c
    fonts/ui_font_Montserrat_light_20_extended.c
    fonts/ui_font_Montserrat_light_72.c
    fonts/ui_font_Montserrat_medium_12_extended.c)

add_library(ui ${SOURCES})
