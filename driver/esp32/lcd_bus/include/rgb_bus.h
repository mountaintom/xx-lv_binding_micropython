
#include "mphalport.h"
#include "py/obj.h"
#include "esp_lcd_panel_io.h"
#include "py/objarray.h"


#if SOC_LCD_RGB_SUPPORTED
#include "esp_lcd_panel_rgb.h"
#endif /*SOC_LCD_RGB_SUPPORTED*/


typedef struct _mp_lcd_rgb_bus_obj_t {
    mp_obj_base_t base;

    mp_obj_t callback;
    mp_obj_t user_ctx;

    int buffer_size;
    bool fb_in_psram;
    bool use_dma;
    bool trans_done;

    void *buf1;
    void *buf2;

#if SOC_LCD_RGB_SUPPORTED
    esp_lcd_panel_handle_t panel_io_handle;
    esp_lcd_rgb_panel_config_t panel_io_config;
    esp_lcd_rgb_timing_t bus_config;
#else
    esp_lcd_panel_io_handle_t panel_io_handle;
    void *panel_io_config;
    void *bus_config;
#endif /*SOC_LCD_RGB_SUPPORTED*/

    void* bus_handle;

} mp_lcd_rgb_bus_obj_t;


extern const mp_obj_type_t mp_lcd_rgb_bus_type;
