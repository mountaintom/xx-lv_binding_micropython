#include "spi_bus.h"
#include "bus_common.h"
#include "esp_lcd_panel_io.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "soc/gpio_sig_map.h"
#include "rom/gpio.h"
#include "soc/spi_pins.h"

#include "esp_heap_caps.h"

#include "mphalport.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/gc.h"

#include <string.h>


bool spi_bus_trans_done_cb(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx) {
        mp_lcd_spi_bus_obj_t *bus_obj = (mp_lcd_spi_bus_obj_t *)user_ctx;

        if (bus_obj->callback != mp_const_none) {
            mp_sched_schedule(bus_obj->callback, bus_obj->user_ctx);
            mp_hal_wake_main_task_from_isr();
        }

        return false;
}


STATIC void mp_lcd_spi_bus_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    (void) kind;
    mp_lcd_spi_bus_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(
        print,
        "<SPIBus mosi=%u, miso=%u, sck=%u, dc=%u, cs=%u, host=%u, pclk_hz=%u, dc_low_on_data=%u, cs_high_active=%u, cmd_bits=%u, param_bits=%u, max_transfer_sz=%u, spi_mode=%u>",
        self->bus_config.mosi_io_num,
        self->bus_config.miso_io_num,
        self->bus_config.sclk_io_num,
        self->panel_io_config.dc_gpio_num,
        self->panel_io_config.cs_gpio_num,
        self->host,
        self->panel_io_config.pclk_hz,
        self->panel_io_config.flags.dc_low_on_data,
        self->panel_io_config.flags.cs_high_active,
        self->panel_io_config.lcd_cmd_bits,
        self->panel_io_config.lcd_param_bits,
        self->bus_config.max_transfer_sz,
        self->panel_io_config.spi_mode
    );
}


STATIC mp_obj_t mp_lcd_spi_bus_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {

    enum {
        ARG_dc,
        ARG_host,
        ARG_mosi,
        ARG_miso,
        ARG_sclk,
        ARG_cs,
        ARG_freq,
        ARG_wp,
        ARG_hd,
        ARG_quad_spi,
        ARG_tx_only,
        ARG_cmd_bits,
        ARG_param_bits,
        ARG_buffer_size,
        ARG_fb_in_psram,
        ARG_use_dma,
        ARG_dc_low_on_data,
        ARG_sio_mode,
        ARG_lsb_first,
        ARG_cs_high_active,
        ARG_spi_mode
    };

    const mp_arg_t make_new_args[] = {
        { MP_QSTR_dc,               MP_ARG_INT | MP_ARG_REQUIRED                      },
        { MP_QSTR_host,             MP_ARG_INT,                   { .u_int = 2      } },
        { MP_QSTR_mosi,             MP_ARG_INT,                   { .u_int = -1     } },
        { MP_QSTR_miso,             MP_ARG_INT,                   { .u_int = -1     } },
        { MP_QSTR_sclk,             MP_ARG_INT,                   { .u_int = -1     } },
        { MP_QSTR_cs,               MP_ARG_INT,                   { .u_int = -1     } },
        { MP_QSTR_freq,             MP_ARG_INT,                   { .u_int = -1     } },
        { MP_QSTR_wp,               MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1     } },
        { MP_QSTR_hd,               MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1     } },
        { MP_QSTR_quad_spi,         MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false } },
        { MP_QSTR_tx_only,          MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false } },
        { MP_QSTR_cmd_bits,         MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = 8      } },
        { MP_QSTR_param_bits,       MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = 8      } },
        { MP_QSTR_buffer_size,      MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1     } },
        { MP_QSTR_fb_in_psram,      MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false } },
        { MP_QSTR_use_dma,          MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = true  } },
        { MP_QSTR_dc_low_on_data,   MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false } },
        { MP_QSTR_sio_mode,         MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false } },
        { MP_QSTR_lsb_first,        MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false } },
        { MP_QSTR_cs_high_active,   MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false } },
        { MP_QSTR_spi_mode,         MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = 0      } }
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
    mp_lcd_spi_bus_obj_t *self = m_new_obj(mp_lcd_spi_bus_obj_t);
    self->base.type = &mp_lcd_spi_bus_type;

    self->buffer_size = (int) args[ARG_buffer_size].u_int;
    self->fb_in_psram = (bool) args[ARG_fb_in_psram].u_bool;
    self->use_dma = (bool) args[ARG_use_dma].u_bool;

    if (self->buffer_size != -1) {
        uint32_t mem_cap = 0;

        if (self->fb_in_psram) {
            mem_cap |= MALLOC_CAP_SPIRAM;
        } else {
            mem_cap |= MALLOC_CAP_INTERNAL;
        }

        if (self->use_dma) {
            mem_cap |= MALLOC_CAP_DMA;
            self->buf1 = (uint8_t *)heap_caps_malloc((size_t)self->buffer_size, mem_cap);
            self->buf2 = (uint8_t *)heap_caps_malloc((size_t)self->buffer_size, mem_cap);
            self->bus_config.max_transfer_sz = self->buffer_size;
        } else {
            self->buf1 = (uint8_t *)heap_caps_malloc((size_t)self->buffer_size, mem_cap);
            self->bus_config.max_transfer_sz = SOC_SPI_MAXIMUM_BUFFER_SIZE;
        }
    }

    uint32_t flags = SPICOMMON_BUSFLAG_MASTER;
    int dc = (int) args[ARG_dc].u_int;
    int host = (int) args[ARG_host].u_int;
    int mosi = (int) args[ARG_mosi].u_int;
    int miso = (int) args[ARG_miso].u_int;
    int sclk = (int) args[ARG_sclk].u_int;
    int cs = (int) args[ARG_cs].u_int;
    int freq = (int) args[ARG_freq].u_int;
    int wp = (int) args[ARG_wp].u_int;
    int hd = (int) args[ARG_hd].u_int;

    if ((args[ARG_spi_mode].u_int > 3) || (args[ARG_spi_mode].u_int < 0)) {
        mp_raise_msg_varg(&mp_type_OSError, "invalid spi mode (%d)", args[ARG_spi_mode].u_int);
    }


    if ((mosi == -1) && (miso == -1) && (sclk == -1)) {
        if (host == 2) {
            cs = 15;
            sclk = 14;
            miso = 12;
            mosi = 13;

            if (args[ARG_quad_spi].u_bool) {
                if (wp == -1) {
                    wp = 2;
                }
                if (hd == -1) {
                    hd = 4;
                }
            }
        } else if (host == 3) {
            cs = 5;
            sclk = 18;
            miso = 19;
            mosi = 23;

            if (args[ARG_quad_spi].u_bool) {
                if (wp == -1) {
                    wp = 22;
                }
                if (hd == -1) {
                    hd = 21;
                }
            }
        } else {
            mp_raise_msg_varg(&mp_type_OSError, "invalid host (%d)", host);
        }
    }

    if (!args[ARG_quad_spi].u_bool) {
        wp = -1;
        hd = -1;
    } else {
        flags |= SPICOMMON_BUSFLAG_QUAD;
    }

    if (args[ARG_tx_only].u_bool) {
        miso = -1;
    }

    if (
        //  host 2          host 3
        ((sclk != 14) && (sclk != 18)) ||
        ((mosi != 13) && (mosi != 23)) ||
        ((miso != 12) && (miso != 19) && (miso != -1)) ||
        ((wp != 2)    && (wp != 22)   && (wp != -1))   ||
        ((hd != 4)    && (hd != 21)   && (hd != -1))   ||
        ((cs != 15)   && (cs != 5)    && (cs != -1))
    ) {
        // gpio mux maximum speed
        if (freq == -1) {
            freq = 26600000;
        }
        flags |= SPICOMMON_BUSFLAG_GPIO_PINS;
    } else {
        // io mux maximum speed
        if (freq == -1) {
            freq = 80000000;
        }
        flags |= SPICOMMON_BUSFLAG_IOMUX_PINS;
    }

    self->callback = mp_const_none;
    self->user_ctx = mp_const_none;

    self->host = host;
    self->bus_handle = (esp_lcd_spi_bus_handle_t)((uint32_t)host);

    self->bus_config.sclk_io_num = sclk;
    self->bus_config.mosi_io_num = mosi;
    self->bus_config.miso_io_num = miso;
    self->bus_config.quadwp_io_num = wp;
    self->bus_config.quadhd_io_num = hd;
    self->bus_config.data4_io_num = -1;
    self->bus_config.data5_io_num = -1;
    self->bus_config.data6_io_num = -1;
    self->bus_config.data7_io_num = -1;
    self->bus_config.flags = flags;

    self->panel_io_config.cs_gpio_num = cs;
    self->panel_io_config.dc_gpio_num = dc;
    self->panel_io_config.spi_mode = args[ARG_spi_mode].u_int;
    self->panel_io_config.pclk_hz = freq;
    self->panel_io_config.trans_queue_depth = 1;
    self->panel_io_config.on_color_trans_done = spi_bus_trans_done_cb;
    self->panel_io_config.user_ctx = self;
    self->panel_io_config.lcd_cmd_bits = args[ARG_cmd_bits].u_int;
    self->panel_io_config.lcd_param_bits = args[ARG_param_bits].u_int;
    self->panel_io_config.flags.dc_low_on_data = args[ARG_dc_low_on_data].u_bool;
    self->panel_io_config.flags.sio_mode = args[ARG_sio_mode].u_bool;
    self->panel_io_config.flags.lsb_first = args[ARG_lsb_first].u_bool;
    self->panel_io_config.flags.cs_high_active = args[ARG_cs_high_active].u_bool;
    self->panel_io_config.flags.octal_mode = 0;

    return MP_OBJ_FROM_PTR(self);
}

STATIC mp_obj_t mp_lcd_spi_bus_init(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_width, ARG_height, ARG_bpp };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_width,        MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_height,       MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_bpp,          MP_ARG_INT | MP_ARG_REQUIRED  },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_spi_bus_obj_t *self = (mp_lcd_spi_bus_obj_t *)args[ARG_self].u_obj;

    if (self->buffer_size == -1) {
        int width = args[ARG_width].u_int;
        int height = args[ARG_height].u_int;
        int bpp = args[ARG_bpp].u_int;
        self->buffer_size = ((width * height) / 10) * (bpp / 8);

        uint32_t mem_cap = 0;

        if (self->fb_in_psram) {
            mem_cap |= MALLOC_CAP_SPIRAM;
        } else {
            mem_cap |= MALLOC_CAP_INTERNAL;
        }

        if (self->use_dma) {
            mem_cap |= MALLOC_CAP_DMA;
            self->buf1 = (uint8_t *)heap_caps_malloc((size_t)self->buffer_size, mem_cap);
            self->buf2 = (uint8_t *)heap_caps_malloc((size_t)self->buffer_size, mem_cap);
            self->bus_config.max_transfer_sz = self->buffer_size;
        } else {
            self->buf1 = (uint8_t *)heap_caps_malloc((size_t)self->buffer_size, mem_cap);
            self->bus_config.max_transfer_sz = SOC_SPI_MAXIMUM_BUFFER_SIZE;
        }
    }

    esp_err_t ret = spi_bus_initialize(self->host, &self->bus_config, self->use_dma ? SPI_DMA_CH_AUTO : SPI_DMA_DISABLED);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(spi_bus_initialize)", ret);
    }

    ret = esp_lcd_new_panel_io_spi(self->bus_handle, &self->panel_io_config, &self->panel_io_handle);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_new_panel_io_spi)", ret);
    }

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_spi_bus_init_obj, 4, mp_lcd_spi_bus_init);


STATIC mp_obj_t mp_lcd_spi_bus_deinit(mp_obj_t self_in) {
    mp_lcd_spi_bus_obj_t *self = self_in;

    esp_err_t ret = esp_lcd_panel_io_del(self->panel_io_handle);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_del)", ret);
    }

    ret = spi_bus_free(self->host);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(spi_bus_free)", ret);
    }

    gpio_pad_select_gpio(self->bus_config.miso_io_num);
    gpio_matrix_out(self->bus_config.miso_io_num, SIG_GPIO_OUT_IDX, false, false);
    gpio_set_direction(self->bus_config.miso_io_num, GPIO_MODE_INPUT);

    gpio_pad_select_gpio(self->bus_config.mosi_io_num);
    gpio_matrix_out(self->bus_config.mosi_io_num, SIG_GPIO_OUT_IDX, false, false);
    gpio_set_direction(self->bus_config.mosi_io_num, GPIO_MODE_INPUT);

    gpio_pad_select_gpio(self->bus_config.sclk_io_num);
    gpio_matrix_out(self->bus_config.sclk_io_num, SIG_GPIO_OUT_IDX, false, false);
    gpio_set_direction(self->bus_config.sclk_io_num, GPIO_MODE_INPUT);

    heap_caps_free(self->buf1);
    heap_caps_free(self->buf2);

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_lcd_spi_bus_deinit_obj, mp_lcd_spi_bus_deinit);


STATIC mp_obj_t mp_lcd_spi_bus_register_callback(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_callback, ARG_user_data };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_callback,     MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_user_data,    MP_ARG_OBJ, {.u_obj = mp_const_none} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_spi_bus_obj_t *self = (mp_lcd_spi_bus_obj_t *)args[ARG_self].u_obj;

    self->callback = args[ARG_callback].u_obj;
    self->user_ctx = args[ARG_user_data].u_obj;

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_spi_bus_register_callback_obj, 2, mp_lcd_spi_bus_register_callback);


STATIC mp_obj_t mp_lcd_spi_bus_tx_param(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_cmd, ARG_params };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,    MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_cmd,     MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_params,  MP_ARG_OBJ, {.u_obj = mp_const_none} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_spi_bus_obj_t *self = (mp_lcd_spi_bus_obj_t *)args[ARG_self].u_obj;
    int cmd = args[ARG_cmd].u_int;
    esp_err_t ret;

    if (args[ARG_params].u_obj != mp_const_none) {
        mp_buffer_info_t bufinfo;
        mp_get_buffer_raise(args[ARG_params].u_obj, &bufinfo, MP_BUFFER_READ);
        ret = esp_lcd_panel_io_tx_param(self->panel_io_handle, cmd, bufinfo.buf, bufinfo.len);
    } else {
        ret = esp_lcd_panel_io_tx_param(self->panel_io_handle, cmd, NULL, 0);
    }

    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_tx_param)", ret);
    }

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_spi_bus_tx_param_obj, 2, mp_lcd_spi_bus_tx_param);


STATIC mp_obj_t mp_lcd_spi_bus_tx_color(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_cmd, ARG_data };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_cmd,   MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_data,  MP_ARG_OBJ | MP_ARG_REQUIRED  },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_spi_bus_obj_t *self = (mp_lcd_spi_bus_obj_t *)args[ARG_self].u_obj;
    int cmd = args[ARG_cmd].u_int;

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[ARG_data].u_obj, &bufinfo, MP_BUFFER_READ);
    esp_err_t ret = esp_lcd_panel_io_tx_color(self->panel_io_handle, cmd, bufinfo.buf, bufinfo.len);

    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_tx_color)", ret);
    }

    gc_collect();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_spi_bus_tx_color_obj, 3, mp_lcd_spi_bus_tx_color);


STATIC mp_obj_t mp_lcd_spi_bus_rx_param(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_cmd, ARG_data };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_cmd,   MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_data,  MP_ARG_OBJ | MP_ARG_REQUIRED  },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_spi_bus_obj_t *self = (mp_lcd_spi_bus_obj_t *)args[ARG_self].u_obj;
    int cmd = args[ARG_cmd].u_int;

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[ARG_data].u_obj, &bufinfo, MP_BUFFER_WRITE);
    esp_err_t ret = esp_lcd_panel_io_rx_param(self->panel_io_handle, cmd, bufinfo.buf, bufinfo.len);

    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_rx_param)", ret);
    }
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_spi_bus_rx_param_obj, 3, mp_lcd_spi_bus_rx_param);


STATIC mp_obj_t mp_lcd_spi_bus_get_frame_buffer(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_buffer_number };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_buffer_number,   MP_ARG_INT | MP_ARG_REQUIRED  }
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_spi_bus_obj_t *self = (mp_lcd_spi_bus_obj_t *)args[ARG_self].u_obj;
    int buf_num = args[ARG_buffer_number].u_int;

    if (buf_num == 1) {
        return (mp_obj_t *)self->buf1;
    }

    return (mp_obj_t *)self->buf2;

}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_spi_bus_get_frame_buffer_obj, 2, mp_lcd_spi_bus_get_frame_buffer);


STATIC const mp_rom_map_elem_t mp_lcd_spi_bus_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_get_frame_buffer),  MP_ROM_PTR(&mp_lcd_spi_bus_get_frame_buffer_obj)  },
    { MP_ROM_QSTR(MP_QSTR_register_callback), MP_ROM_PTR(&mp_lcd_spi_bus_register_callback_obj) },
    { MP_ROM_QSTR(MP_QSTR_tx_param),          MP_ROM_PTR(&mp_lcd_spi_bus_tx_param_obj)          },
    { MP_ROM_QSTR(MP_QSTR_tx_color),          MP_ROM_PTR(&mp_lcd_spi_bus_tx_color_obj)          },
    { MP_ROM_QSTR(MP_QSTR_rx_param),          MP_ROM_PTR(&mp_lcd_spi_bus_rx_param_obj)          },
    { MP_ROM_QSTR(MP_QSTR_init),              MP_ROM_PTR(&mp_lcd_spi_bus_init_obj)              },
    { MP_ROM_QSTR(MP_QSTR_deinit),            MP_ROM_PTR(&mp_lcd_spi_bus_deinit_obj)            },
    { MP_ROM_QSTR(MP_QSTR___del__),           MP_ROM_PTR(&mp_lcd_spi_bus_deinit_obj)            },
};

STATIC MP_DEFINE_CONST_DICT(mp_lcd_spi_bus_locals_dict, mp_lcd_spi_bus_locals_dict_table);


STATIC inline void mp_lcd_spi_bus_p_rx_param(mp_obj_base_t *self_in, int lcd_cmd, void *param, size_t param_size) {
    mp_lcd_spi_bus_obj_t *self = (mp_lcd_spi_bus_obj_t *)self_in;

    esp_err_t ret = esp_lcd_panel_io_rx_param(self->panel_io_handle, lcd_cmd, param, param_size);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_rx_param)", ret);
    }
}


STATIC inline void mp_lcd_spi_bus_p_tx_param(mp_obj_base_t *self_in, int lcd_cmd, void *param, size_t param_size) {
    mp_lcd_spi_bus_obj_t *self = (mp_lcd_spi_bus_obj_t *)self_in;

    esp_err_t ret = esp_lcd_panel_io_tx_param(self->panel_io_handle, lcd_cmd, param, param_size);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_tx_param)", ret);
    }
}


STATIC inline void mp_lcd_spi_bus_p_tx_color(mp_obj_base_t *self_in, int lcd_cmd, void *color, size_t color_size) {
    mp_lcd_spi_bus_obj_t *self = (mp_lcd_spi_bus_obj_t *)self_in;

    esp_err_t ret = esp_lcd_panel_io_tx_color(self->panel_io_handle, lcd_cmd, color, color_size);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_tx_color)", ret);
    }
}


STATIC inline void mp_lcd_spi_bus_p_deinit(mp_obj_base_t *self_in) {
    mp_lcd_spi_bus_obj_t *self = (mp_lcd_spi_bus_obj_t *)self_in;

    esp_err_t ret = esp_lcd_panel_io_del(self->panel_io_handle);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_del)", ret);
    }

    ret = spi_bus_free(self->host);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(spi_bus_free)", ret);
    }

    gpio_pad_select_gpio(self->bus_config.miso_io_num);
    gpio_matrix_out(self->bus_config.miso_io_num, SIG_GPIO_OUT_IDX, false, false);
    gpio_set_direction(self->bus_config.miso_io_num, GPIO_MODE_INPUT);

    gpio_pad_select_gpio(self->bus_config.mosi_io_num);
    gpio_matrix_out(self->bus_config.mosi_io_num, SIG_GPIO_OUT_IDX, false, false);
    gpio_set_direction(self->bus_config.mosi_io_num, GPIO_MODE_INPUT);

    gpio_pad_select_gpio(self->bus_config.sclk_io_num);
    gpio_matrix_out(self->bus_config.sclk_io_num, SIG_GPIO_OUT_IDX, false, false);
    gpio_set_direction(self->bus_config.sclk_io_num, GPIO_MODE_INPUT);

    heap_caps_free(self->buf1);
    heap_caps_free(self->buf2);
}


STATIC const mp_lcd_bus_p_t mp_lcd_bus_p = {
    .rx_param = mp_lcd_spi_bus_p_rx_param,
    .tx_param = mp_lcd_spi_bus_p_tx_param,
    .tx_color = mp_lcd_spi_bus_p_tx_color,
    .deinit = mp_lcd_spi_bus_p_deinit
};

#ifdef MP_OBJ_TYPE_GET_SLOT
MP_DEFINE_CONST_OBJ_TYPE(
    mp_lcd_spi_bus_type,
    MP_QSTR_SPI_Bus,
    MP_TYPE_FLAG_NONE,
    print, mp_lcd_spi_bus_print,
    make_new, mp_lcd_spi_bus_make_new,
    protocol, &mp_lcd_bus_p,
    locals_dict, (mp_obj_dict_t *)&mp_lcd_spi_bus_locals_dict
);
#else
const mp_obj_type_t mp_lcd_spi_bus_type = {
    { &mp_type_type },
    .name = MP_QSTR_SPI_Bus,
    .print = mp_lcd_spi_bus_print,
    .make_new = mp_lcd_spi_bus_make_new,
    .protocol = &mp_lcd_bus_p,
    .locals_dict = (mp_obj_dict_t *)&mp_lcd_spi_bus_locals_dict,
};
#endif
