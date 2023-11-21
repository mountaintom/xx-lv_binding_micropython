
#ifndef _LCD_BUS_COMMON_H_
#define _LCD_BUS_COMMON_H_

#include "py/obj.h"


typedef struct _mp_lcd_bus_p_t {
    void (*rx_param)(mp_obj_base_t* self_in, int lcd_cmd, void* param, size_t param_size);
    void (*tx_param)(mp_obj_base_t* self_in, int lcd_cmd, void* param, size_t param_size);
    union {
        void (*tx_color)(mp_obj_base_t* self_in, int lcd_cmd, void* color, size_t color_size);
        void (*rgb_tx_color)(mp_obj_base_t* self_in, int lcd_cmd, void* color, int x_start, int y_start, int x_end, int y_end);
    };
    void (*deinit)(mp_obj_base_t* self_in);
} mp_lcd_bus_p_t;


#endif