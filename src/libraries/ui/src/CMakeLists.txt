SET(SOURCES screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_background_png.c
    images/ui_img_sec_dot_png.c
    fonts/ui_font_Montserrat_light_120.c
    fonts/ui_font_Montserrat_light_72.c)

add_library(ui ${SOURCES})
