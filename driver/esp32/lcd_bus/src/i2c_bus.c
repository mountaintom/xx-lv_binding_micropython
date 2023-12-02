#include "../include/i2c_bus.h"
#include "../include/modlcd_bus.h"

#include "esp_lcd_panel_io.h"
#include "driver/i2c.h"

#include "mphalport.h"
#include "py/obj.h"
#include "py/runtime.h"

#include <string.h>


STATIC mp_obj_t mp_lcd_i2c_bus_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    enum {
        ARG_sda,
        ARG_scl,
        ARG_addr,
        ARG_host,
        ARG_control_phase_bytes,
        ARG_dc_bit_offset,
        ARG_freq,
        ARG_cmd_bits,
        ARG_param_bits,
        ARG_buffer_size,
        ARG_fb_in_psram,
        ARG_use_dma,
        ARG_dc_low_on_data,
        ARG_sda_pullup,
        ARG_scl_pullup,
        ARG_disable_control_phase
    };

    const mp_arg_t make_new_args[] = {
        { MP_QSTR_sda,                   MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_scl,                   MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_addr,                  MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_host,                  MP_ARG_INT  | MP_ARG_KW_ONLY,  {.u_int = 0         } },
        { MP_QSTR_control_phase_bytes,   MP_ARG_INT  | MP_ARG_KW_ONLY,  {.u_int = 1         } },
        { MP_QSTR_dc_bit_offset,         MP_ARG_INT  | MP_ARG_KW_ONLY,  {.u_int = 6         } },
        { MP_QSTR_freq,                  MP_ARG_INT  | MP_ARG_KW_ONLY,  {.u_int = 10000000  } },
        { MP_QSTR_cmd_bits,              MP_ARG_INT  | MP_ARG_KW_ONLY,  {.u_int = 8         } },
        { MP_QSTR_param_bits,            MP_ARG_INT  | MP_ARG_KW_ONLY,  {.u_int = 8         } },
        { MP_QSTR_buffer_size,           MP_ARG_INT  | MP_ARG_KW_ONLY,  {.u_int = -1        } },
        { MP_QSTR_fb_in_psram,           MP_ARG_BOOL | MP_ARG_KW_ONLY,  {.u_bool = false    } },
        { MP_QSTR_use_dma,               MP_ARG_BOOL | MP_ARG_KW_ONLY,  {.u_bool = true     } },
        { MP_QSTR_dc_low_on_data,        MP_ARG_BOOL | MP_ARG_KW_ONLY,  {.u_bool = false    } },
        { MP_QSTR_sda_pullup,            MP_ARG_BOOL | MP_ARG_KW_ONLY,  {.u_bool = true     } },
        { MP_QSTR_scl_pullup,            MP_ARG_BOOL | MP_ARG_KW_ONLY,  {.u_bool = true     } },
        { MP_QSTR_disable_control_phase, MP_ARG_BOOL | MP_ARG_KW_ONLY,  {.u_bool = false    } }
    };

    mp_arg_val_t args[MP_ARRAY_SIZE(make_new_args)];
    mp_arg_parse_all_kw_array(
        n_args,
        n_kw,
        all_args,
        MP_ARRAY_SIZE(make_new_args),
        make_new_args,
        args
    );

    // create new object
    mp_lcd_i2c_bus_obj_t *self = m_new_obj(mp_lcd_i2c_bus_obj_t);
    self->base.type = &mp_lcd_i2c_bus_type;

    initilize_buffers((mp_lcd_bus_obj_t *)self);

    self->buffer_size = (int) args[ARG_buffer_size].u_int;
    self->fb_in_psram = (bool) args[ARG_fb_in_psram].u_bool;
    self->use_dma = (bool) args[ARG_use_dma].u_bool;

    if (self->buffer_size != -1) {
        allocate_buffers((mp_lcd_bus_obj_t *)self);
    }

    self->callback = mp_const_none;
    self->user_ctx = mp_const_none;

    self->host = args[ARG_host].u_int;
    self->bus_handle = (esp_lcd_i2c_bus_handle_t)((uint32_t)self->host);

    self->bus_config.mode = I2C_MODE_MASTER;
    self->bus_config.sda_io_num = (int)args[ARG_sda].u_int;
    self->bus_config.scl_io_num = (int)args[ARG_scl].u_int;
    self->bus_config.sda_pullup_en = (bool)args[ARG_sda_pullup].u_bool;
    self->bus_config.scl_pullup_en = (bool)args[ARG_scl_pullup].u_bool;
    self->bus_config.master.clk_speed = (uint32_t)args[ARG_freq].u_int;
    self->bus_config.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

    self->panel_io_config.dev_addr = (uint32_t)args[ARG_addr].u_int;
    self->panel_io_config.on_color_trans_done = bus_trans_done_cb;
    self->panel_io_config.user_ctx = self;
    self->panel_io_config.control_phase_bytes = (size_t)args[ARG_control_phase_bytes].u_int;
    self->panel_io_config.dc_bit_offset = (unsigned int)args[ARG_dc_bit_offset].u_int;
    self->panel_io_config.lcd_cmd_bits = (int)args[ARG_cmd_bits].u_int;
    self->panel_io_config.lcd_param_bits = (int)args[ARG_param_bits].u_int;
    self->panel_io_config.flags.dc_low_on_data = (unsigned int)args[ARG_dc_low_on_data].u_bool;
    self->panel_io_config.flags.disable_control_phase = (unsigned int)args[ARG_disable_control_phase].u_bool;

    return MP_OBJ_FROM_PTR(self);
}


STATIC mp_obj_t mp_lcd_i2c_bus_init(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_width, ARG_height, ARG_bpp };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_width,        MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_height,       MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_bpp,          MP_ARG_INT | MP_ARG_REQUIRED  },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_i2c_bus_obj_t *self = (mp_lcd_i2c_bus_obj_t *)args[ARG_self].u_obj;

    if (self->buffer_size == -1) {
        int width = args[ARG_width].u_int;
        int height = args[ARG_height].u_int;
        int bpp = args[ARG_bpp].u_int;
        self->buffer_size = ((width * height) / 10) * (bpp / 8);

        allocate_buffers((mp_lcd_bus_obj_t *)self);
    }

    esp_err_t ret = i2c_param_config(self->host, &self->bus_config);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(i2c_param_config)", ret);
    }

    ret = i2c_driver_install(self->host, I2C_MODE_MASTER, 0, 0, 0);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(i2c_driver_install)", ret);
    }

    ret = esp_lcd_new_panel_io_i2c(self->bus_handle , &self->panel_io_config, &self->panel_io_handle);

    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_new_panel_io_i2c)", ret);
    }

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_i2c_bus_init_obj, 4, mp_lcd_i2c_bus_init);


STATIC mp_obj_t mp_lcd_i2c_bus_deinit(mp_obj_t self_in) {
    mp_lcd_i2c_bus_obj_t *self = self_in;

    esp_err_t ret = esp_lcd_panel_io_del(self->panel_io_handle);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_del)", ret);
    }
    ret = i2c_driver_delete(self->host);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(i2c_driver_delete)", ret);
    }

    heap_caps_free(self->buf1.items);
    heap_caps_free(self->buf2.items);

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_lcd_i2c_bus_deinit_obj, mp_lcd_i2c_bus_deinit);


STATIC const mp_rom_map_elem_t mp_lcd_i2c_bus_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_get_frame_buffer_size),  MP_ROM_PTR(&mp_lcd_bus_get_frame_buffer_size_obj)  },
    { MP_ROM_QSTR(MP_QSTR_get_frame_buffer),  MP_ROM_PTR(&mp_lcd_bus_get_frame_buffer_obj)  },
    { MP_ROM_QSTR(MP_QSTR_register_callback), MP_ROM_PTR(&mp_lcd_bus_register_callback_obj) },
    { MP_ROM_QSTR(MP_QSTR_tx_param),          MP_ROM_PTR(&mp_lcd_bus_tx_param_obj)          },
    { MP_ROM_QSTR(MP_QSTR_tx_color),          MP_ROM_PTR(&mp_lcd_bus_tx_color_obj)          },
    { MP_ROM_QSTR(MP_QSTR_rx_param),          MP_ROM_PTR(&mp_lcd_bus_rx_param_obj)          },
    { MP_ROM_QSTR(MP_QSTR_init),              MP_ROM_PTR(&mp_lcd_i2c_bus_init_obj)          },
    { MP_ROM_QSTR(MP_QSTR_deinit),            MP_ROM_PTR(&mp_lcd_i2c_bus_deinit_obj)        },
    { MP_ROM_QSTR(MP_QSTR___del__),           MP_ROM_PTR(&mp_lcd_i2c_bus_deinit_obj)        },
};

STATIC MP_DEFINE_CONST_DICT(mp_lcd_i2c_bus_locals_dict, mp_lcd_i2c_bus_locals_dict_table);


MP_DEFINE_CONST_OBJ_TYPE(
    mp_lcd_i2c_bus_type,
    MP_QSTR_I2CBus,
    MP_TYPE_FLAG_NONE,
    make_new, mp_lcd_i2c_bus_make_new,
    locals_dict, (mp_obj_dict_t *)&mp_lcd_i2c_bus_locals_dict
);

