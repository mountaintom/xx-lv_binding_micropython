
#if (SOC_LCD_RGB_SUPPORTED == 1)

#include "rgb_bus.h"
#include "bus_common.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_panel_ops.h"

#include "mphalport.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/gc.h"

#include <string.h>


bool rgb_bus_trans_done_cb(esp_lcd_panel_handle_t panel_io, const esp_lcd_rgb_panel_event_data_t *edata, void *user_ctx)
{
        mp_lcd_rgb_bus_obj_t *bus_obj = (mp_lcd_rgb_bus_obj_t *)user_ctx;
        if (bus_obj->callback != mp_const_none) {
            mp_sched_schedule(bus_obj->callback, bus_obj->user_ctx);
            mp_hal_wake_main_task_from_isr();
        }

        return false;
}


STATIC void mp_lcd_rgb_bus_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind)
{
    (void) kind;
    /*
    mp_lcd_rgb_bus_obj_t *self = MP_OBJ_TO_PTR(self_in);

    mp_printf(
        print,
        "<RGBBus pclk=%u, width=%u, height=%u>",
        self->pclk,
        self->width,
        self->height
    );
    */
}


mp_obj_t mp_lcd_rgb_bus_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    enum {
        ARG_hsync,
        ARG_vsync,
        ARG_de,
        ARG_disp,
        ARG_pclk,
        ARG_data0,
        ARG_data1,
        ARG_data2,
        ARG_data3,
        ARG_data4,
        ARG_data5,
        ARG_data6,
        ARG_data7,
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data8,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data9,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data10,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data11,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data12,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data13,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data14,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data15,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data16,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data17,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data18,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data19,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data20,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data21,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data22,
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        ARG_data23,
        #endif
        ARG_freq,
        ARG_num_fbs,
        ARG_bounce_buffer_size_px,
        ARG_hsync_front_porch,
        ARG_hsync_back_porch,
        ARG_hsync_pulse_width,
        ARG_hsync_idle_low,
        ARG_vsync_front_porch,
        ARG_vsync_back_porch,
        ARG_vsync_pulse_width,
        ARG_vsync_idle_low,
        ARG_de_idle_high,
        ARG_pclk_idle_high,
        ARG_pclk_active_neg,
        ARG_disp_active_low,
        ARG_refresh_on_demand,
        ARG_fb_in_psram,
        ARG_no_fb,
        ARG_bb_invalidate_cache,
    };
    const mp_arg_t allowed_args[] = {
        { MP_QSTR_hsync,              MP_ARG_INT  | MP_ARG_REQUIRED                      },
        { MP_QSTR_vsync,              MP_ARG_INT  | MP_ARG_REQUIRED                      },
        { MP_QSTR_de,                 MP_ARG_INT  | MP_ARG_REQUIRED                      },
        { MP_QSTR_disp,               MP_ARG_INT  | MP_ARG_REQUIRED                      },
        { MP_QSTR_pclk,               MP_ARG_INT  | MP_ARG_REQUIRED                      },
        { MP_QSTR_data0,              MP_ARG_INT  | MP_ARG_REQUIRED                      },
        { MP_QSTR_data1,              MP_ARG_INT  | MP_ARG_REQUIRED                      },
        { MP_QSTR_data2,              MP_ARG_INT  | MP_ARG_REQUIRED                      },
        { MP_QSTR_data3,              MP_ARG_INT  | MP_ARG_REQUIRED                      },
        { MP_QSTR_data4,              MP_ARG_INT  | MP_ARG_REQUIRED                      },
        { MP_QSTR_data5,              MP_ARG_INT  | MP_ARG_REQUIRED                      },
        { MP_QSTR_data6,              MP_ARG_INT  | MP_ARG_REQUIRED                      },
        { MP_QSTR_data7,              MP_ARG_INT  | MP_ARG_REQUIRED                      },
        #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
        { MP_QSTR_data8,              MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 10)
        { MP_QSTR_data9,              MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 11)
        { MP_QSTR_data10,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 12)
        { MP_QSTR_data11,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 13)
        { MP_QSTR_data12,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 14)
        { MP_QSTR_data13,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 15)
        { MP_QSTR_data14,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 16)
        { MP_QSTR_data15,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 17)
        { MP_QSTR_data16,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 18)
        { MP_QSTR_data17,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 19)
        { MP_QSTR_data18,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 20)
        { MP_QSTR_data19,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 21)
        { MP_QSTR_data20,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 22)
        { MP_QSTR_data21,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 23)
        { MP_QSTR_data22,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        #if (SOC_LCD_RGB_DATA_WIDTH >= 24)
        { MP_QSTR_data23,             MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = -1      } },
        #endif
        { MP_QSTR_freq,               MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = 8000000 } },
        { MP_QSTR_num_fbs,            MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_int = 2       } },
        { MP_QSTR_bb_size_px,         MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = 0       } },
        { MP_QSTR_hsync_front_porch,  MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = 0       } },
        { MP_QSTR_hsync_pulse_width,  MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = 0       } },
        { MP_QSTR_hsync_pulse_width,  MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = 1       } },
        { MP_QSTR_hsync_idle_low,     MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false  } },
        { MP_QSTR_vsync_front_porch,  MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = 0       } },
        { MP_QSTR_vsync_back_porch,   MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = 0       } },
        { MP_QSTR_vsync_pulse_width,  MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_int = 1       } },
        { MP_QSTR_vsync_idle_low,     MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false  } },
        { MP_QSTR_de_idle_high,       MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false  } },
        { MP_QSTR_pclk_idle_high,     MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false  } },
        { MP_QSTR_pclk_active_neg,    MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false  } },
        { MP_QSTR_disp_active_low,    MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false  } },
        { MP_QSTR_refresh_on_demand,  MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false  } },
        { MP_QSTR_fb_in_psram,        MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false  } },
        { MP_QSTR_no_fb,              MP_ARG_BOOL | MP_ARG_KW_ONLY, { .u_bool = false  } },
        { MP_QSTR_bb_inval_cache,     MP_ARG_INT  | MP_ARG_KW_ONLY, { .u_bool = false  } },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    // create new object
    mp_lcd_rgb_bus_obj_t *self = m_new_obj(mp_lcd_rgb_bus_obj_t);
    self->base.type = &mp_lcd_rgb_bus_type;

    self->callback = mp_const_none;
    self->user_ctx = mp_const_none;

    self->bus_config.pclk_hz = (uint32_t)args[ARG_freq].u_int;
    self->bus_config.hsync_pulse_width = (uint32_t)args[ARG_hsync_pulse_width].u_int;
    self->bus_config.hsync_back_porch = (uint32_t)args[ARG_hsync_back_porch].u_int;
    self->bus_config.hsync_front_porch = (uint32_t)args[ARG_hsync_front_porch].u_int;
    self->bus_config.vsync_pulse_width = (uint32_t)args[ARG_vsync_pulse_width].u_int;
    self->bus_config.vsync_back_porch = (uint32_t)args[ARG_vsync_back_porch].u_int;
    self->bus_config.vsync_front_porch = (uint32_t)args[ARG_vsync_front_porch].u_int;
    self->bus_config.flags.hsync_idle_low = (uint32_t)args[ARG_hsync_idle_low].u_bool;
    self->bus_config.flags.vsync_idle_low = (uint32_t)args[ARG_vsync_idle_low].u_bool;
    self->bus_config.flags.de_idle_high = (uint32_t)args[ARG_de_idle_high].u_bool;
    self->bus_config.flags.pclk_active_neg = (uint32_t)args[ARG_pclk_active_neg].u_bool;
    self->bus_config.flags.pclk_idle_high = (uint32_t)args[ARG_pclk_idle_high].u_bool;

    self->panel_io_config.clk_src = LCD_CLK_SRC_PLL160M;
    self->panel_io_config.timings = self->bus_config;
    self->panel_io_config.num_fbs = (size_t)args[ARG_num_fbs].u_int;
    self->panel_io_config.bounce_buffer_size_px = (size_t)args[ARG_bounce_buffer_size_px].u_int;
    self->panel_io_config.hsync_gpio_num = (int)args[ARG_hsync].u_int;
    self->panel_io_config.vsync_gpio_num = (int)args[ARG_vsync].u_int;
    self->panel_io_config.de_gpio_num = (int)args[ARG_de].u_int;
    self->panel_io_config.pclk_gpio_num = (int)args[ARG_pclk].u_int;
    self->panel_io_config.data_gpio_nums[0] = args[ARG_data0].u_int;
    self->panel_io_config.data_gpio_nums[1] = args[ARG_data1].u_int;
    self->panel_io_config.data_gpio_nums[2] = args[ARG_data2].u_int;
    self->panel_io_config.data_gpio_nums[3] = args[ARG_data3].u_int;
    self->panel_io_config.data_gpio_nums[4] = args[ARG_data4].u_int;
    self->panel_io_config.data_gpio_nums[5] = args[ARG_data5].u_int;
    self->panel_io_config.data_gpio_nums[6] = args[ARG_data6].u_int;
    self->panel_io_config.data_gpio_nums[7] = args[ARG_data7].u_int;
    #if (SOC_LCD_RGB_DATA_WIDTH >= 9)
    self->panel_io_config.data_gpio_nums[8] = args[ARG_data8].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 10)
    self->panel_io_config.data_gpio_nums[9] = args[ARG_data9].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 11)
    self->panel_io_config.data_gpio_nums[10] = args[ARG_data10].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 12)
    self->panel_io_config.data_gpio_nums[11] = args[ARG_data11].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 13)
    self->panel_io_config.data_gpio_nums[12] = args[ARG_data12].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 14)
    self->panel_io_config.data_gpio_nums[13] = args[ARG_data13].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 15)
    self->panel_io_config.data_gpio_nums[14] = args[ARG_data14].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 16)
    self->panel_io_config.data_gpio_nums[15] = args[ARG_data15].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 17)
    self->panel_io_config.data_gpio_nums[16] = args[ARG_data16].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 18)
    self->panel_io_config.data_gpio_nums[17] = args[ARG_data17].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 19)
    self->panel_io_config.data_gpio_nums[18] = args[ARG_data18].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 20)
    self->panel_io_config.data_gpio_nums[19] = args[ARG_data19].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 21)
    self->panel_io_config.data_gpio_nums[20] = args[ARG_data20].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 22)
    self->panel_io_config.data_gpio_nums[21] = args[ARG_data21].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 23)
    self->panel_io_config.data_gpio_nums[22] = args[ARG_data22].u_int;
    #endif
    #if (SOC_LCD_RGB_DATA_WIDTH >= 24)
    self->panel_io_config.data_gpio_nums[23] = args[ARG_data23].u_int;
    #endif

    self->panel_io_config.disp_gpio_num = (int)args[ARG_disp].u_int;
    self->panel_io_config.sram_trans_align = 64;
    self->panel_io_config.psram_trans_align = 64;
    self->panel_io_config.flags.disp_active_low = (uint32_t)args[ARG_disp_active_low].u_bool;
    self->panel_io_config.flags.refresh_on_demand = (uint32_t)args[ARG_refresh_on_demand].u_bool;
    self->panel_io_config.flags.fb_in_psram = (uint32_t)args[ARG_fb_in_psram].u_bool;
    self->panel_io_config.flags.no_fb = (uint32_t)args[ARG_no_fb].u_bool;
    self->panel_io_config.flags.bb_invalidate_cache = (uint32_t)args[ARG_bb_invalidate_cache].u_bool;

    int i = 0;
    for (; i < SOC_LCD_RGB_DATA_WIDTH; i++) {
        if (self->panel_io_config.data_gpio_nums[i] == -1) {
            i -= 1;
            break;
        }
    }

    self->panel_io_config.data_width = (size_t)(i + 1);

    return MP_OBJ_FROM_PTR(self);
}


STATIC mp_obj_t mp_lcd_rgb_bus_init(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_width, ARG_height, ARG_bpp };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_width,        MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_height,       MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_bpp,          MP_ARG_INT | MP_ARG_REQUIRED  },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_rgb_bus_obj_t *self = (mp_lcd_rgb_bus_obj_t *)args[ARG_self].u_obj;

    self->panel_io_config.timings.h_res = (uint32_t)args[ARG_width].u_int;
    self->panel_io_config.timings.v_res = (uint32_t)args[ARG_height].u_int;
    self->panel_io_config.bits_per_pixel = (size_t)args[ARG_bpp].u_int;

    esp_err_t ret = esp_lcd_new_rgb_panel(&self->panel_io_config, &self->panel_io_handle);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_new_rgb_panel)", ret);
    }

    esp_lcd_rgb_panel_event_callbacks_t callbacks = {
        .on_vsync = rgb_bus_trans_done_cb
    };

    ret = esp_lcd_rgb_panel_register_event_callbacks(self->panel_io_handle, &callbacks, self);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_rgb_panel_register_event_callbacks)", ret);
    }

    ret = esp_lcd_panel_reset(self->panel_io_handle);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_reset)", ret);
    }

    ret = esp_lcd_panel_init(self->panel_io_handle);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_init)", ret);
    }


    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_rgb_bus_init_obj, 4, mp_lcd_rgb_bus_init);


STATIC mp_obj_t mp_lcd_rgb_bus_deinit(mp_obj_t self_in) {
    mp_lcd_rgb_bus_obj_t *self = self_in;

    esp_err_t ret = esp_lcd_panel_del(self->panel_io_handle);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_del)", ret);
    }
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(mp_lcd_rgb_bus_deinit_obj, mp_lcd_rgb_bus_deinit);


STATIC mp_obj_t mp_lcd_rgb_bus_register_callback(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_callback, ARG_user_data };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_callback,     MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_user_data,    MP_ARG_OBJ, {.u_obj = mp_const_none} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_rgb_bus_obj_t *self = (mp_lcd_rgb_bus_obj_t *)args[ARG_self].u_obj;

    self->callback = args[ARG_callback].u_obj;
    self->user_ctx = args[ARG_user_data].u_obj;

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_rgb_bus_register_callback_obj, 2, mp_lcd_rgb_bus_register_callback);


STATIC mp_obj_t mp_lcd_rgb_bus_tx_param(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_cmd, ARG_params };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_cmd,     MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_params,  MP_ARG_OBJ, {.u_obj = mp_const_none} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    /*
    mp_lcd_rgb_bus_obj_t *self = (mp_lcd_rgb_bus_obj_t *)args[ARG_self].u_obj;
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
    */

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_rgb_bus_tx_param_obj, 2, mp_lcd_rgb_bus_tx_param);


STATIC mp_obj_t mp_lcd_rgb_bus_tx_color(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {

    enum { ARG_self, ARG_cmd, ARG_data, ARG_x_start, ARG_y_start, ARG_x_end, ARG_y_end };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,    MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_cmd,     MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_data,    MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_x_start, MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_y_start, MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_x_end,   MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_y_end,   MP_ARG_INT | MP_ARG_REQUIRED  },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_rgb_bus_obj_t *self = (mp_lcd_rgb_bus_obj_t *)args[ARG_self].u_obj;
    // int cmd = args[ARG_cmd].u_int;

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[ARG_data].u_obj, &bufinfo, MP_BUFFER_READ);

    esp_err_t ret = esp_lcd_panel_draw_bitmap(self->panel_io_handle, args[ARG_x_start].u_int, args[ARG_y_start].u_int, args[ARG_x_end].u_int, args[ARG_y_end].u_int, bufinfo.buf);

    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_draw_bitmap)", ret);
    }

    gc_collect();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_rgb_bus_tx_color_obj, 3, mp_lcd_rgb_bus_tx_color);


STATIC mp_obj_t mp_lcd_rgb_bus_rx_param(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {

    enum { ARG_self, ARG_cmd, ARG_data };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_cmd,   MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_data,  MP_ARG_OBJ | MP_ARG_REQUIRED  },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);
    /*
    mp_lcd_rgb_bus_obj_t *self = (mp_lcd_rgb_bus_obj_t *)args[ARG_self].u_obj;
    int cmd = args[ARG_cmd].u_int;

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[ARG_data].u_obj, &bufinfo, MP_BUFFER_WRITE);
    esp_err_t ret = esp_lcd_panel_io_rx_param(self->panel_io_handle, cmd, bufinfo.buf, bufinfo.len);

    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_rx_param)", ret);
    }
    */
    return mp_const_none;

}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_rgb_bus_rx_param_obj, 3, mp_lcd_rgb_bus_rx_param);


STATIC mp_obj_t mp_lcd_rgb_bus_get_frame_buffer(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_buffer_number };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_buffer_number,   MP_ARG_INT | MP_ARG_REQUIRED  }
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_rgb_bus_obj_t *self = (mp_lcd_rgb_bus_obj_t *)args[ARG_self].u_obj;
    int buf_num = args[ARG_buffer_number].u_int;

    void *buf1;
    void *buf2;

    if (self->panel_io_config.flags.double_fb == 1) {
        esp_lcd_rgb_panel_get_frame_buffer(self->panel_io_handle, 2, &buf1, &buf2);
    } else {
        esp_lcd_rgb_panel_get_frame_buffer(self->panel_io_handle, 1, &buf1);
    }

    if (buf_num == 2) {
        return (mp_obj_t) buf2;
    }

    return (mp_obj_t) buf1;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_rgb_bus_get_frame_buffer_obj, 2, mp_lcd_rgb_bus_get_frame_buffer);


STATIC const mp_rom_map_elem_t mp_lcd_rgb_bus_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_get_frame_buffer),  MP_ROM_PTR(&mp_lcd_rgb_bus_get_frame_buffer_obj)  },
    { MP_ROM_QSTR(MP_QSTR_tx_param),          MP_ROM_PTR(&mp_lcd_rgb_bus_tx_param_obj)          },
    { MP_ROM_QSTR(MP_QSTR_tx_color),          MP_ROM_PTR(&mp_lcd_rgb_bus_tx_color_obj)          },
    { MP_ROM_QSTR(MP_QSTR_rx_param),          MP_ROM_PTR(&mp_lcd_rgb_bus_rx_param_obj)          },
    { MP_ROM_QSTR(MP_QSTR_register_callback), MP_ROM_PTR(&mp_lcd_rgb_bus_register_callback_obj) },
    { MP_ROM_QSTR(MP_QSTR_init),              MP_ROM_PTR(&mp_lcd_rgb_bus_init_obj)              },
    { MP_ROM_QSTR(MP_QSTR_deinit),            MP_ROM_PTR(&mp_lcd_rgb_bus_deinit_obj)            },
    { MP_ROM_QSTR(MP_QSTR___del__),           MP_ROM_PTR(&mp_lcd_rgb_bus_deinit_obj)            },
};

STATIC MP_DEFINE_CONST_DICT(mp_lcd_rgb_bus_locals_dict, mp_lcd_rgb_bus_locals_dict_table);


STATIC inline void mp_lcd_rgb_bus_p_rx_param(mp_obj_base_t *self_in, int lcd_cmd, void *param, size_t param_size) {
/*
    mp_lcd_spi_bus_obj_t *self = (mp_lcd_spi_bus_obj_t *)self_in;
    esp_err_t ret = esp_lcd_panel_io_rx_param(self->panel_io_handle, lcd_cmd, param, param_size);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_rx_param)", ret);
    }
    */
}


STATIC inline void mp_lcd_rgb_bus_p_tx_param(mp_obj_base_t *self_in, int lcd_cmd, void *param, size_t param_size) {
    /*
    mp_lcd_spi_bus_obj_t *self = (mp_lcd_spi_bus_obj_t *)self_in;

    esp_err_t ret = esp_lcd_panel_io_tx_param(self->panel_io_handle, lcd_cmd, param, param_size);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_tx_param)", ret);
    }
    */
}


STATIC inline void mp_lcd_rgb_bus_p_tx_color(mp_obj_base_t *self_in, int lcd_cmd, void *color, int x_start, int y_start, int x_end, int y_end) {
    mp_lcd_rgb_bus_obj_t *self = MP_OBJ_TO_PTR(self_in);

    esp_err_t ret = esp_lcd_panel_draw_bitmap(self->panel_io_handle, x_start, y_start, x_end, y_end, color);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_draw_bitmap)", ret);
    }
}


STATIC inline void mp_lcd_rgb_bus_p_deinit(mp_obj_base_t *self_in) {
    mp_lcd_rgb_bus_obj_t *self = MP_OBJ_TO_PTR(self_in);

    esp_err_t ret = esp_lcd_panel_del(self->panel_io_handle);
    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_del)", ret);
    }
}


STATIC const mp_lcd_bus_p_t mp_lcd_bus_p = {
    .rx_param = mp_lcd_rgb_bus_p_rx_param,
    .tx_param = mp_lcd_rgb_bus_p_tx_param,
    .rgb_tx_color = mp_lcd_rgb_bus_p_tx_color,
    .deinit = mp_lcd_rgb_bus_p_deinit
};


#ifdef MP_OBJ_TYPE_GET_SLOT
MP_DEFINE_CONST_OBJ_TYPE(
    mp_lcd_rgb_bus_type,
    MP_QSTR_RGBBus,
    MP_TYPE_FLAG_NONE,
    print, mp_lcd_rgb_bus_print,
    make_new, mp_lcd_rgb_bus_make_new,
    protocol, &mp_lcd_bus_p,
    locals_dict, (mp_obj_dict_t *)&mp_lcd_rgb_bus_locals_dict
);
#else
const mp_obj_type_t mp_lcd_rgb_bus_type = {
    { &mp_type_type },
    .name = MP_QSTR_RGBBus,
    .print = mp_lcd_rgb_bus_print,
    .make_new = mp_lcd_rgb_bus_make_new,
    .protocol = &mp_lcd_bus_p,
    .locals_dict = (mp_obj_dict_t *)&mp_lcd_rgb_bus_locals_dict,
};
#endif

#endif /*(SOC_LCD_RGB_SUPPORTED == 1)*/
