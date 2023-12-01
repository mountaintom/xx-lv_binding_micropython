#include "../include/i80_bus.h"
#include "../include/modlcd_bus.h"

#include "esp_lcd_panel_io.h"
#include "esp_heap_caps.h"
#include "hal/lcd_types.h"

#include "mphalport.h"
#include "py/obj.h"
#include "py/runtime.h"


#include <string.h>


STATIC mp_obj_t mp_lcd_i80_bus_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    enum {
        ARG_dc,
        ARG_wr,
        ARG_cs,
        ARG_data0,
        ARG_data1,
        ARG_data2,
        ARG_data3,
        ARG_data4,
        ARG_data5,
        ARG_data6,
        ARG_data7,
        ARG_data8,
        ARG_data9,
        ARG_data10,
        ARG_data11,
        ARG_data12,
        ARG_data13,
        ARG_data14,
        ARG_data15,
        #if (SOC_LCD_I80_BUS_WIDTH > 16)
            ARG_data16,
            ARG_data17,
            ARG_data18,
            ARG_data19,
            ARG_data20,
            ARG_data21,
            ARG_data22,
            ARG_data23,
        #endif
        ARG_freq,
        ARG_dc_idle_level,
        ARG_dc_cmd_level,
        ARG_dc_dummy_level,
        ARG_dc_data_level,
        ARG_cmd_bits,
        ARG_param_bits,
        ARG_buffer_size,
        ARG_fb_in_psram,
        ARG_use_dma,
        ARG_cs_active_high,
        ARG_reverse_color_bits,
        ARG_swap_color_bytes,
        ARG_pclk_active_neg,
        ARG_pclk_idle_low,
    };

    const mp_arg_t make_new_args[] = {
        { MP_QSTR_dc,                 MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_wr,                 MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_cs,                 MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_data0,              MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_data1,              MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_data2,              MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_data3,              MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_data4,              MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_data5,              MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_data6,              MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_data7,              MP_ARG_INT  | MP_ARG_REQUIRED                        },
        { MP_QSTR_data8,              MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
        { MP_QSTR_data9,              MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
        { MP_QSTR_data10,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
        { MP_QSTR_data11,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
        { MP_QSTR_data12,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
        { MP_QSTR_data13,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
        { MP_QSTR_data14,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
        { MP_QSTR_data15,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
        #if (SOC_LCD_I80_BUS_WIDTH > 16)
            { MP_QSTR_data16,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
            { MP_QSTR_data17,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
            { MP_QSTR_data18,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
            { MP_QSTR_data19,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
            { MP_QSTR_data20,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
            { MP_QSTR_data21,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
            { MP_QSTR_data22,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
            { MP_QSTR_data23,             MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = -1       } },
        #endif
        { MP_QSTR_freq,               MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = 10000000 } },
        { MP_QSTR_dc_idle_level,      MP_ARG_BOOL | MP_ARG_KW_ONLY,  { .u_bool = false   } },
        { MP_QSTR_dc_cmd_level,       MP_ARG_BOOL | MP_ARG_KW_ONLY,  { .u_bool = false   } },
        { MP_QSTR_dc_dummy_level,     MP_ARG_BOOL | MP_ARG_KW_ONLY,  { .u_bool = false   } },
        { MP_QSTR_dc_data_level,      MP_ARG_BOOL | MP_ARG_KW_ONLY,  { .u_bool = false   } },
        { MP_QSTR_cmd_bits,           MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = 8        } },
        { MP_QSTR_param_bits,         MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = 8        } },
        { MP_QSTR_buffer_size,        MP_ARG_INT  | MP_ARG_KW_ONLY,  { .u_int = 0        } },
        { MP_QSTR_fb_in_psram,        MP_ARG_BOOL | MP_ARG_KW_ONLY,  { .u_bool = false   } },
        { MP_QSTR_use_dma,            MP_ARG_BOOL | MP_ARG_KW_ONLY,  { .u_bool = true    } },
        { MP_QSTR_cs_active_high,     MP_ARG_BOOL | MP_ARG_KW_ONLY,  { .u_bool = false   } },
        { MP_QSTR_reverse_color_bits, MP_ARG_BOOL | MP_ARG_KW_ONLY,  { .u_bool = false   } },
        { MP_QSTR_swap_color_bytes,   MP_ARG_BOOL | MP_ARG_KW_ONLY,  { .u_bool = false   } },
        { MP_QSTR_pclk_active_neg,    MP_ARG_BOOL | MP_ARG_KW_ONLY,  { .u_bool = false   } },
        { MP_QSTR_pclk_idle_low,      MP_ARG_BOOL | MP_ARG_KW_ONLY,  { .u_bool = false   } }
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
    mp_lcd_i80_bus_obj_t *self = m_new_obj(mp_lcd_i80_bus_obj_t);
    self->base.type = &mp_lcd_i80_bus_type;

    #if SOC_LCD_I80_SUPPORTED
        self->buffer_size = (int) args[ARG_buffer_size].u_int;
        self->fb_in_psram = (bool) args[ARG_fb_in_psram].u_bool;
        self->use_dma = (bool) args[ARG_use_dma].u_bool;

        if (self->buffer_size != -1) {
            allocate_buffers((mp_lcd_bus_obj_t *)self);
            self->bus_config.max_transfer_bytes = (size_t)self->buffer_size;
        }

        self->callback = mp_const_none;
        self->user_ctx = mp_const_none;

        self->bus_config.dc_gpio_num = (int)args[ARG_dc].u_int;
        self->bus_config.wr_gpio_num = (int)args[ARG_wr].u_int;
        self->bus_config.clk_src = LCD_CLK_SRC_PLL160M;
        self->bus_config.data_gpio_nums[0] = args[ARG_data0].u_int;
        self->bus_config.data_gpio_nums[1] = args[ARG_data1].u_int;
        self->bus_config.data_gpio_nums[2] = args[ARG_data2].u_int;
        self->bus_config.data_gpio_nums[3] = args[ARG_data3].u_int;
        self->bus_config.data_gpio_nums[4] = args[ARG_data4].u_int;
        self->bus_config.data_gpio_nums[5] = args[ARG_data5].u_int;
        self->bus_config.data_gpio_nums[6] = args[ARG_data6].u_int;
        self->bus_config.data_gpio_nums[7] = args[ARG_data7].u_int;
        self->bus_config.data_gpio_nums[8] = args[ARG_data8].u_int;
        self->bus_config.data_gpio_nums[9] = args[ARG_data9].u_int;
        self->bus_config.data_gpio_nums[10] = args[ARG_data10].u_int;
        self->bus_config.data_gpio_nums[11] = args[ARG_data11].u_int;
        self->bus_config.data_gpio_nums[12] = args[ARG_data12].u_int;
        self->bus_config.data_gpio_nums[13] = args[ARG_data13].u_int;
        self->bus_config.data_gpio_nums[14] = args[ARG_data14].u_int;
        self->bus_config.data_gpio_nums[15] = args[ARG_data15].u_int;
        #if (SOC_LCD_I80_BUS_WIDTH > 16)
            self->bus_config.data_gpio_nums[16] = args[ARG_data16].u_int;
            self->bus_config.data_gpio_nums[17] = args[ARG_data17].u_int;
            self->bus_config.data_gpio_nums[18] = args[ARG_data18].u_int;
            self->bus_config.data_gpio_nums[19] = args[ARG_data19].u_int;
            self->bus_config.data_gpio_nums[20] = args[ARG_data20].u_int;
            self->bus_config.data_gpio_nums[21] = args[ARG_data21].u_int;
            self->bus_config.data_gpio_nums[22] = args[ARG_data22].u_int;
            self->bus_config.data_gpio_nums[23] = args[ARG_data23].u_int;
        #endif

        uint8_t i = 0;
        for (; i < SOC_LCD_I80_BUS_WIDTH; i++) {
            if (self->bus_config.data_gpio_nums[i] == -1) {
                i -= 1;
                break;
            }
        }

        self->bus_config.bus_width = (size_t)(i + 1);

        self->panel_io_config.cs_gpio_num = (int)args[ARG_cs].u_int;
        self->panel_io_config.pclk_hz = (uint32_t)args[ARG_freq].u_int;
        self->panel_io_config.trans_queue_depth = 1;
        self->panel_io_config.on_color_trans_done = bus_trans_done_cb;
        self->panel_io_config.user_ctx = self;
        self->panel_io_config.lcd_cmd_bits = (int)args[ARG_cmd_bits].u_int;
        self->panel_io_config.lcd_param_bits = (int)args[ARG_param_bits].u_int;
        self->panel_io_config.dc_levels.dc_idle_level = (unsigned int)args[ARG_dc_idle_level].u_int;
        self->panel_io_config.dc_levels.dc_cmd_level = (unsigned int)args[ARG_dc_cmd_level].u_int;
        self->panel_io_config.dc_levels.dc_dummy_level = (unsigned int)args[ARG_dc_dummy_level].u_int;
        self->panel_io_config.dc_levels.dc_data_level = (unsigned int)args[ARG_dc_data_level].u_int;
        self->panel_io_config.flags.cs_active_high = (unsigned int)args[ARG_cs_active_high].u_bool;
        self->panel_io_config.flags.reverse_color_bits = (unsigned int)args[ARG_reverse_color_bits].u_bool;
        self->panel_io_config.flags.swap_color_bytes = (unsigned int)args[ARG_swap_color_bytes].u_bool;
        self->panel_io_config.flags.pclk_active_neg = (unsigned int)args[ARG_pclk_active_neg].u_bool;
        self->panel_io_config.flags.pclk_idle_low = (unsigned int)args[ARG_pclk_idle_low].u_bool;

    #else
        mp_raise_msg(&mp_type_OSError, "I8080 display bus is not supported by this board");
    #endif

    return MP_OBJ_FROM_PTR(self);
}

#if SOC_LCD_I80_SUPPORTED

    STATIC mp_obj_t mp_lcd_i80_bus_init(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
        enum { ARG_self, ARG_width, ARG_height, ARG_bpp };
        static const mp_arg_t allowed_args[] = {
            { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
            { MP_QSTR_width,        MP_ARG_INT | MP_ARG_REQUIRED  },
            { MP_QSTR_height,       MP_ARG_INT | MP_ARG_REQUIRED  },
            { MP_QSTR_bpp,          MP_ARG_INT | MP_ARG_REQUIRED  },
        };
        mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
        mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

        mp_lcd_i80_bus_obj_t *self = (mp_lcd_i80_bus_obj_t *)args[ARG_self].u_obj;

        if (self->buffer_size == -1) {
            int width = args[ARG_width].u_int;
            int height = args[ARG_height].u_int;
            int bpp = args[ARG_bpp].u_int;
            self->buffer_size = ((width * height) / 10) * (bpp / 8);
            allocate_buffers((mp_lcd_bus_obj_t *)self);
            self->bus_config.max_transfer_bytes = (size_t)self->buffer_size;
        }

        esp_err_t ret = esp_lcd_new_i80_bus(&self->bus_config, &self->bus_handle);
        if (ret != 0) {
            mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_new_i80_bus)", ret);
        }

        ret = esp_lcd_new_panel_io_i80(self->bus_handle, &self->panel_io_config, &self->panel_io_handle);
        if (ret != 0) {
            mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_new_panel_io_i80)", ret);
        }

        return mp_const_none;
    }

    STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_i80_bus_init_obj, 4, mp_lcd_i80_bus_init);


    STATIC mp_obj_t mp_lcd_i80_bus_deinit(mp_obj_t self_in) {
        mp_lcd_i80_bus_obj_t *self = self_in;

        esp_err_t ret = esp_lcd_panel_io_del(self->panel_io_handle);
        if (ret != 0) {
            mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_del)", ret);
        }

        ret = esp_lcd_del_i80_bus(self->bus_handle);
        if (ret != 0) {
            mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_del_i80_bus)", ret);
        }

        heap_caps_free(self->buf1);
        heap_caps_free(self->buf2);

        return mp_const_none;
    }

    STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_lcd_i80_bus_deinit_obj, mp_lcd_i80_bus_deinit);

    STATIC const mp_rom_map_elem_t mp_lcd_i80_bus_locals_dict_table[] = {
        { MP_ROM_QSTR(MP_QSTR_get_frame_buffer_size),  MP_ROM_PTR(&mp_lcd_bus_get_frame_buffer_size_obj)  },
        { MP_ROM_QSTR(MP_QSTR_get_frame_buffer),  MP_ROM_PTR(&mp_lcd_bus_get_frame_buffer_obj)  },
        { MP_ROM_QSTR(MP_QSTR_register_callback), MP_ROM_PTR(&mp_lcd_bus_register_callback_obj) },
        { MP_ROM_QSTR(MP_QSTR_tx_param),          MP_ROM_PTR(&mp_lcd_bus_tx_param_obj)          },
        { MP_ROM_QSTR(MP_QSTR_tx_color),          MP_ROM_PTR(&mp_lcd_bus_tx_color_obj)          },
        { MP_ROM_QSTR(MP_QSTR_tx_param),          MP_ROM_PTR(&mp_lcd_bus_rx_param_obj)          },
        { MP_ROM_QSTR(MP_QSTR_init),              MP_ROM_PTR(&mp_lcd_i80_bus_init_obj)          },
        { MP_ROM_QSTR(MP_QSTR_deinit),            MP_ROM_PTR(&mp_lcd_i80_bus_deinit_obj)        },
        { MP_ROM_QSTR(MP_QSTR___del__),           MP_ROM_PTR(&mp_lcd_i80_bus_deinit_obj)        },
        { MP_ROM_QSTR(MP_QSTR_HIGH),              MP_ROM_TRUE                                   },
        { MP_ROM_QSTR(MP_QSTR_LOW),               MP_ROM_FALSE                                  },
    };

    STATIC MP_DEFINE_CONST_DICT(mp_lcd_i80_bus_locals_dict, mp_lcd_i80_bus_locals_dict_table);


    MP_DEFINE_CONST_OBJ_TYPE(
        mp_lcd_i80_bus_type,
        MP_QSTR_I8080Bus,
        MP_TYPE_FLAG_NONE,
        make_new, mp_lcd_i80_bus_make_new,
        locals_dict, (mp_obj_dict_t *)&mp_lcd_i80_bus_locals_dict
    );
#else
    MP_DEFINE_CONST_OBJ_TYPE(
        mp_lcd_i80_bus_type,
        MP_QSTR_I8080Bus,
        MP_TYPE_FLAG_NONE,
        make_new, mp_lcd_i80_bus_make_new
    );
#endif /*SOC_LCD_I80_SUPPORTED*/
