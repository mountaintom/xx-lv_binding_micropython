
#include "mphalport.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/objarray.h"

#include "esp_lcd_panel_io.h"

#ifndef MODLCD_BUS_H
#define MODLCD_BUS_H

typedef struct _mp_lcd_bus_obj_t {
    mp_obj_base_t base;

    mp_obj_t callback;
    mp_obj_t user_ctx;

    int buffer_size;
    bool fb_in_psram;
    bool use_dma;
    bool trans_done;

    uint8_t *buf1;
    uint8_t *buf2;

    esp_lcd_panel_io_handle_t panel_io_handle;

} mp_lcd_bus_obj_t;


bool bus_trans_done_cb(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx);

void allocate_buffers(mp_lcd_bus_obj_t *self);


STATIC mp_obj_t mp_lcd_bus_tx_param(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_cmd, ARG_params };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,    MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_cmd,     MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_params,  MP_ARG_OBJ, {.u_obj = mp_const_none} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_bus_obj_t *self = (mp_lcd_bus_obj_t *)args[ARG_self].u_obj;
    esp_err_t ret;

    if (args[ARG_params].u_obj != mp_const_none) {
        mp_buffer_info_t bufinfo;
        mp_get_buffer_raise(args[ARG_params].u_obj, &bufinfo, MP_BUFFER_READ);
        ret = esp_lcd_panel_io_tx_param(self->panel_io_handle, (int)args[ARG_cmd].u_int, bufinfo.buf, bufinfo.len);
    } else {
        ret = esp_lcd_panel_io_tx_param(self->panel_io_handle, (int)args[ARG_cmd].u_int, NULL, 0);
    }

    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_tx_param)", ret);
    }

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_bus_tx_param_obj, 2, mp_lcd_bus_tx_param);


STATIC mp_obj_t mp_lcd_bus_tx_color(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
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

    mp_lcd_bus_obj_t *self = (mp_lcd_bus_obj_t *)args[ARG_self].u_obj;

    mp_obj_array_t * temp_array = (mp_obj_array_t *)args[ARG_data].u_obj;

    esp_err_t ret = esp_lcd_panel_io_tx_color(
        self->panel_io_handle,
        (int)args[ARG_cmd].u_int,
        (void *)temp_array->items,
        (size_t)(args[ARG_x_end].u_int - args[ARG_x_start].u_int + 1) * (args[ARG_y_end].u_int - args[ARG_y_start].u_int + 1)
    );

    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_tx_color)", ret);
    }

    if ((self.use_dma == false) && (self->callback != mp_const_none)) {
        mp_sched_schedule(self->callback, self->user_ctx);
    } else if ((self.use_dma == true) && (self->callback == mp_const_none)) {
        while (self->trans_done == false) {}
        self->trans_done = false;
    }

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_bus_tx_color_obj, 7, mp_lcd_bus_tx_color);


STATIC mp_obj_t mp_lcd_bus_rx_param(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_cmd, ARG_data };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_cmd,   MP_ARG_INT | MP_ARG_REQUIRED  },
        { MP_QSTR_data,  MP_ARG_OBJ | MP_ARG_REQUIRED  },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_bus_obj_t *self = (mp_lcd_bus_obj_t *)args[ARG_self].u_obj;

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[ARG_data].u_obj, &bufinfo, MP_BUFFER_WRITE);

    esp_err_t ret = esp_lcd_panel_io_rx_param(
        self->panel_io_handle,
        (int)args[ARG_cmd].u_int,
        bufinfo.buf,
        bufinfo.len
    );

    if (ret != 0) {
        mp_raise_msg_varg(&mp_type_OSError, "%d(esp_lcd_panel_io_rx_param)", ret);
    }
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_bus_rx_param_obj, 3, mp_lcd_bus_rx_param);


STATIC mp_obj_t mp_lcd_bus_register_callback(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_callback, ARG_user_data };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_callback,     MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_user_data,    MP_ARG_OBJ, {.u_obj = mp_const_none} },
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_bus_obj_t *self = (mp_lcd_bus_obj_t *)args[ARG_self].u_obj;

    self->callback = args[ARG_callback].u_obj;
    self->user_ctx = args[ARG_user_data].u_obj;

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_bus_register_callback_obj, 2, mp_lcd_bus_register_callback);


STATIC mp_obj_t mp_lcd_bus_get_frame_buffer(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self, ARG_buffer_number };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  },
        { MP_QSTR_buffer_number,   MP_ARG_INT | MP_ARG_REQUIRED  }
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_bus_obj_t *self = (mp_lcd_bus_obj_t *)args[ARG_self].u_obj;
    int buf_num = args[ARG_buffer_number].u_int;

    if (buf_num == 1) {
        return mp_obj_new_memoryview('B', self->buffer_size, self->buf1);
    }

    if (self->buf2 == NULL) {
        return mp_const_none;
    }
    return mp_obj_new_memoryview('B', self->buffer_size, self->buf2);

}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_bus_get_frame_buffer_obj, 2, mp_lcd_bus_get_frame_buffer);


STATIC mp_obj_t mp_lcd_bus_get_frame_buffer_size(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_self };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_self,         MP_ARG_OBJ | MP_ARG_REQUIRED  }
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_lcd_bus_obj_t *self = (mp_lcd_bus_obj_t *)args[ARG_self].u_obj;

    return mp_obj_new_int(self->buffer_size);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_KW(mp_lcd_bus_get_frame_buffer_size_obj, 1, mp_lcd_bus_get_frame_buffer_size);

#endif /*MODLCD_BUS_H*/
