// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Waveshare-RP2040-Touch-LCD-1.28

#include "../ui.h"


// COMPONENT Hour group

lv_obj_t * ui_Hour_group_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_Hour_group;
    cui_Hour_group = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_Hour_group, 134);
    lv_obj_set_height(cui_Hour_group, 97);
    lv_obj_set_x(cui_Hour_group, -24);
    lv_obj_set_y(cui_Hour_group, 20);
    lv_obj_set_align(cui_Hour_group, LV_ALIGN_CENTER);
    lv_obj_clear_flag(cui_Hour_group, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_HOUR_GROUP_NUM);
    children[UI_COMP_HOUR_GROUP_HOUR_GROUP] = cui_Hour_group;
    lv_obj_add_event_cb(cui_Hour_group, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_Hour_group, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_Hour_group_create_hook(cui_Hour_group);
    return cui_Hour_group;
}
