
#include "mphalport.h"
#include "py/obj.h"
#include "esp_lcd_panel_io.h"
#include "driver/i2c.h"


typedef struct _mp_lcd_i2c_bus_obj_t {
    mp_obj_base_t base;

    mp_obj_t callback;
    mp_obj_t user_ctx;

    esp_lcd_panel_io_i2c_config_t panel_io_config;
    esp_lcd_panel_io_handle_t panel_io_handle;

    i2c_config_t bus_config;
    esp_lcd_i2c_bus_handle_t bus_handle;

    int buffer_size;
    bool fb_in_psram;
    bool use_dma;

    uint8_t *buf1;
    uint8_t *buf2;

    uint8_t host;

} mp_lcd_i2c_bus_obj_t;


extern const mp_obj_type_t mp_lcd_i2c_bus_type;

