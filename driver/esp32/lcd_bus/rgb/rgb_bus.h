#ifndef LCD_RGB_BUS_H_
#define LCD_RGB_BUS_H_


#include "mphalport.h"
#include "py/obj.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_rgb.h"


typedef struct _mp_lcd_rgb_bus_obj_t {
    mp_obj_base_t base;

    mp_obj_t callback;
    mp_obj_t user_ctx;

    esp_lcd_rgb_panel_config_t panel_io_config;
    esp_lcd_panel_handle_t panel_io_handle;

    esp_lcd_rgb_timing_t bus_config;

} mp_lcd_rgb_bus_obj_t;


extern const mp_obj_type_t mp_lcd_rgb_bus_type;

#endif /*LCD_RGB_BUS_H_*/