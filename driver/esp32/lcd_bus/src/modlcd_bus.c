
#include "../include/modlcd_bus.h"
#include "../include/spi_bus.h"
#include "../include/i2c_bus.h"
#include "../include/i80_bus.h"
#include "../include/rgb_bus.h"

#include "esp_lcd_panel_io.h"
#include "esp_heap_caps.h"
#include "esp_lcd_types.h"

#include "mphalport.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/objarray.h"
#include "py/binary.h"


bool bus_trans_done_cb(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    mp_lcd_bus_obj_t *bus_obj = (mp_lcd_bus_obj_t *)user_ctx;
    if (bus_obj->callback != mp_const_none) {
        mp_call_function_n_kw(bus_obj->callback, 1, 0, bus_obj->user_ctx);
    } else {
        bus_obj->trans_done = true;
    }
    mp_hal_wake_main_task_from_isr();

    return false;
}


void allocate_buffers(mp_lcd_bus_obj_t *self) {
    uint32_t mem_cap = 0;

    if (self->fb_in_psram) {
        mem_cap |= MALLOC_CAP_SPIRAM;
    } else {
        mem_cap |= MALLOC_CAP_INTERNAL;
    }
    if (self->use_dma) {
        mem_cap |= MALLOC_CAP_DMA;
        self->buf1 = (void *)heap_caps_malloc((size_t)self->buffer_size, mem_cap);
        self->buf2 = (void *)heap_caps_malloc((size_t)self->buffer_size, mem_cap);

        if ((self->buf1 == NULL) || (self->buf2 == NULL)) {
            mp_raise_msg_varg(&mp_type_MemoryError, MP_ERROR_TEXT("Buffer size is to large to fit into DMA memory try decreasing the size (%d)"), self->buffer_size);
        }
    } else {
        self->buf1 = (void *)heap_caps_malloc((size_t)self->buffer_size, mem_cap);
        if (self->buf1 == NULL) {
            mp_raise_msg_varg(&mp_type_MemoryError, MP_ERROR_TEXT("Buffer size is to large try decreasing the size (%d)"), self->buffer_size);
        }
    }
}


STATIC const mp_map_elem_t mp_module_lcd_bus_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__),           MP_OBJ_NEW_QSTR(MP_QSTR_lcd_bus)      },
    { MP_ROM_QSTR(MP_QSTR_RGBBus),             (mp_obj_t)&mp_lcd_rgb_bus_type        },
    { MP_ROM_QSTR(MP_QSTR_SPIBus),             (mp_obj_t)&mp_lcd_spi_bus_type        },
    { MP_ROM_QSTR(MP_QSTR_I2CBus),             (mp_obj_t)&mp_lcd_i2c_bus_type        },
    { MP_ROM_QSTR(MP_QSTR_I80Bus),             (mp_obj_t)&mp_lcd_i80_bus_type        },
    { MP_ROM_QSTR(MP_QSTR_RGB),                MP_ROM_INT(ESP_LCD_COLOR_SPACE_RGB)           },
    { MP_ROM_QSTR(MP_QSTR_BGR),                MP_ROM_INT(ESP_LCD_COLOR_SPACE_BGR)           },
    { MP_ROM_QSTR(MP_QSTR_MONOCHROME),         MP_ROM_INT(ESP_LCD_COLOR_SPACE_MONOCHROME)    },
};

STATIC MP_DEFINE_CONST_DICT(mp_module_lcd_bus_globals, mp_module_lcd_bus_globals_table);


const mp_obj_module_t mp_module_lcd_bus = {
    .base    = {&mp_type_module},
    .globals = (mp_obj_dict_t *)&mp_module_lcd_bus_globals,
};

MP_REGISTER_MODULE(MP_QSTR_lcd_bus, mp_module_lcd_bus);







