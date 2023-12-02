
#include "mphalport.h"
#include "py/obj.h"
#include "esp_lcd_panel_io.h"
#include "driver/i2c.h"
#include "py/objarray.h"


typedef struct _mp_lcd_i2c_bus_obj_t {
    mp_obj_base_t base;

    mp_obj_t callback;
    mp_obj_t user_ctx;

    int buffer_size;
    bool fb_in_psram;
    bool use_dma;
    bool trans_done;

    mp_obj_array_t buf1;
    mp_obj_array_t buf2;

    esp_lcd_panel_io_handle_t panel_io_handle;
    esp_lcd_panel_io_i2c_config_t panel_io_config;
    i2c_config_t bus_config;
    esp_lcd_i2c_bus_handle_t bus_handle;

    int host;

} mp_lcd_i2c_bus_obj_t;


extern const mp_obj_type_t mp_lcd_i2c_bus_type;

