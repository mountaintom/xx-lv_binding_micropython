
#include "mphalport.h"
#include "py/obj.h"

#include "esp_lcd_panel_io.h"


#if SOC_LCD_RGB_SUPPORTED
#include "esp_lcd_panel_rgb.h"
#endif /*SOC_LCD_RGB_SUPPORTED*/


typedef struct _mp_lcd_rgb_bus_obj_t {
    mp_obj_base_t base;

    mp_obj_t callback;
    mp_obj_t user_ctx;

    esp_lcd_panel_handle_t panel_io_handle;

#if SOC_LCD_RGB_SUPPORTED
    esp_lcd_rgb_panel_config_t panel_io_config;
    esp_lcd_rgb_timing_t bus_config;
#endif /*SOC_LCD_RGB_SUPPORTED*/

} mp_lcd_rgb_bus_obj_t;


extern const mp_obj_type_t mp_lcd_rgb_bus_type;
