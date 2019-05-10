
/*
 * Auto-Generated file, DO NOT EDIT!
 *
 * Command line:
 * gen_mpy.py -X anim -X group -X task -I../../berkeley-db-1.xx/PORT/include -I../../lv_bindings -I. -I../.. -Ibuild -I../../mp-readline -I ../../lv_bindings/pycparser/utils/fake_libc_include ../../lv_bindings/lvgl/lvgl.h
 *
 * Preprocessing command:
 * gcc -E -std=c99 -DPYCPARSER  -I ../../berkeley-db-1.xx/PORT/include -I ../../lv_bindings -I . -I ../.. -I build -I ../../mp-readline -I ../../lv_bindings/pycparser/utils/fake_libc_include -include ../../lv_bindings/lvgl/lvgl.h ../../lv_bindings/lvgl/lvgl.h
 *
 * Generating Objects: obj(None), cont(obj), btn(obj), imgbtn(obj), label(obj), img(obj), line(obj), page(obj), list(obj), chart(obj), table(obj), cb(obj), bar(obj), slider(obj), led(obj), btnm(obj), kb(obj), ddlist(obj), roller(obj), ta(obj), canvas(obj), win(obj), tabview(obj), tileview(obj), mbox(obj), lmeter(obj), gauge(obj), sw(obj), arc(obj), preload(obj), calendar(obj), spinbox(obj)
 */

/*
 * Mpy includes
 */

#include <stdlib.h>
#include <string.h>
#include "py/obj.h"
#include "py/objstr.h"
#include "py/runtime.h"
#include "py/binary.h"

/*
 * lvgl includes
 */

#include "../../lv_bindings/lvgl/lvgl.h"


/*
 * Helper functions
 */

typedef lv_obj_t* (*lv_create)(lv_obj_t * par, const lv_obj_t * copy);

typedef struct mp_lv_obj_t {
    mp_obj_base_t base;
    lv_obj_t *lv_obj;
    lv_obj_t *callbacks;
} mp_lv_obj_t;

STATIC mp_obj_t get_native_obj(mp_obj_t *mp_obj)
{
    const mp_obj_type_t *native_type = ((mp_obj_base_t*)mp_obj)->type;
    if (native_type->parent == NULL) return mp_obj;
    while (native_type->parent) native_type = native_type->parent;
    return mp_instance_cast_to_native_base(mp_obj, MP_OBJ_FROM_PTR(native_type));
}

STATIC mp_obj_t dict_to_struct(mp_obj_t dict, const mp_obj_type_t *type);

STATIC mp_obj_t *cast(mp_obj_t *mp_obj, const mp_obj_type_t *mp_type)
{
    mp_obj_t *res = NULL;
    if (MP_OBJ_IS_OBJ(mp_obj)){
        res = get_native_obj(mp_obj);
        if (res){
            const mp_obj_type_t *res_type = ((mp_obj_base_t*)res)->type;
            if (res_type != mp_type){
                if (res_type == &mp_type_dict) res = dict_to_struct(res, mp_type);
                else res = NULL;
            }
        }
    }
    if (res == NULL) nlr_raise(
        mp_obj_new_exception_msg_varg(
            &mp_type_SyntaxError, "Can't convert %s to %s!", mp_obj_get_type_str(mp_obj), qstr_str(mp_type->name)));
    return res;
}

STATIC inline lv_obj_t *mp_to_lv(mp_obj_t *mp_obj)
{
    if (mp_obj == NULL || mp_obj == mp_const_none) return NULL;
    mp_lv_obj_t *mp_lv_obj = MP_OBJ_TO_PTR(get_native_obj(mp_obj));
    return mp_lv_obj->lv_obj;
}

STATIC inline lv_obj_t *mp_get_callbacks(mp_obj_t *mp_obj)
{
    if (mp_obj == NULL || mp_obj == mp_const_none) return NULL;
    mp_lv_obj_t *mp_lv_obj = MP_OBJ_TO_PTR(get_native_obj(mp_obj));
    if (!mp_lv_obj->callbacks) mp_lv_obj->callbacks = mp_obj_new_dict(0);
    return mp_lv_obj->callbacks;
}

STATIC inline const mp_obj_type_t *get_BaseObj_type();

STATIC inline mp_obj_t *lv_to_mp(lv_obj_t *lv_obj)
{
    mp_lv_obj_t *self = (mp_lv_obj_t*)lv_obj->user_data;
    if (!self) 
    {
        self = m_new_obj(mp_lv_obj_t);
        *self = (mp_lv_obj_t){
            .base = {get_BaseObj_type()},
            .lv_obj = lv_obj,
            .callbacks = NULL,
        };
        lv_obj->user_data = self;
    }
    return MP_OBJ_FROM_PTR(self);
}

STATIC mp_obj_t make_new(
    lv_create create,
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    mp_arg_check_num(n_args, n_kw, 0, 2, false);
    mp_lv_obj_t *self = m_new_obj(mp_lv_obj_t);
    lv_obj_t *parent = n_args > 0? mp_to_lv(args[0]): NULL;
    lv_obj_t *copy = n_args > 1? mp_to_lv(args[1]): NULL;
    *self = (mp_lv_obj_t){
        .base = {type}, 
        .lv_obj = create(parent, copy),
        .callbacks = NULL,
    };
    self->lv_obj->user_data = self;
    return MP_OBJ_FROM_PTR(self);
}

STATIC inline mp_obj_t convert_to_bool(bool b)
{
    return b? mp_const_true: mp_const_false;
}

STATIC inline mp_obj_t convert_to_str(const char *str)
{
    return mp_obj_new_str(str, strlen(str));
}

STATIC void field_not_found(qstr struct_name, qstr field_name)
{
    nlr_raise(
        mp_obj_new_exception_msg_varg(
            &mp_type_SyntaxError, 
            "Cannot access field %s. Field does not exist in struct %s!", 
            qstr_str(field_name), 
            qstr_str(struct_name)));
}

typedef struct mp_lv_struct_t
{
    mp_obj_base_t base;
    void *data;
} mp_lv_struct_t;

STATIC inline mp_lv_struct_t *mp_to_lv_struct(mp_obj_t *mp_obj)
{
    if (mp_obj == NULL || mp_obj == mp_const_none) return NULL;
    if (!MP_OBJ_IS_OBJ(mp_obj)) nlr_raise(
            mp_obj_new_exception_msg(
                &mp_type_SyntaxError, "Struct argument is not an object!"));
    mp_lv_struct_t *mp_lv_struct = MP_OBJ_TO_PTR(get_native_obj(mp_obj));
    return mp_lv_struct;
}

STATIC inline size_t get_lv_struct_size(const mp_obj_type_t *type)
{
    mp_obj_t size_obj = mp_obj_dict_get(type->locals_dict, MP_OBJ_NEW_QSTR(MP_QSTR_SIZE));
    return (size_t)mp_obj_get_int(size_obj);
}

STATIC mp_obj_t make_new_lv_struct(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    size_t size = get_lv_struct_size(type);
    mp_arg_check_num(n_args, n_kw, 0, 1, false);
    mp_lv_struct_t *self = m_new_obj(mp_lv_struct_t);
    *self = (mp_lv_struct_t){
        .base = {type}, 
        .data = malloc(size)
    };
    mp_lv_struct_t *other = n_args > 0? mp_to_lv_struct(cast(args[0], type)): NULL;
    if (other) {
        memcpy(self->data, other->data, size);
    }
    return MP_OBJ_FROM_PTR(self);
}

STATIC void *copy_buffer(const void *buffer, size_t size)
{
    void *new_buffer = malloc(size);
    memcpy(new_buffer, buffer, size);
    return new_buffer;
}

// Reference an existing lv struct (or part of it)

STATIC mp_obj_t lv_to_mp_struct(const mp_obj_type_t *type, void *lv_struct)
{
    mp_lv_struct_t *self = m_new_obj(mp_lv_struct_t);
    *self = (mp_lv_struct_t){
        .base = {type},
        .data = lv_struct
    };
    return MP_OBJ_FROM_PTR(self);
}

// Convert dict to struct

STATIC mp_obj_t dict_to_struct(mp_obj_t dict, const mp_obj_type_t *type)
{
    mp_obj_t mp_struct = make_new_lv_struct(type, 0, 0, NULL);
    mp_obj_t *native_dict = cast(dict, &mp_type_dict);
    mp_map_t *map = mp_obj_dict_get_map(native_dict);
    if (map == NULL) return mp_const_none;
    for (uint i = 0; i < map->alloc; i++) {
        mp_obj_t key = map->table[i].key;
        mp_obj_t value = map->table[i].value;
        if (key != MP_OBJ_NULL) {
            type->attr(mp_struct, mp_obj_str_get_qstr(key), (mp_obj_t[]){MP_OBJ_SENTINEL, value});
        }
    }
    return mp_struct;
}


// Blob is a wrapper for void* 

STATIC void mp_blob_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl Blob");
}

STATIC mp_int_t mp_blob_get_buffer(mp_obj_t self_in, mp_buffer_info_t *bufinfo, mp_uint_t flags) {
    (void)flags;
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);

    bufinfo->buf = &self->data;
    bufinfo->len = sizeof(self->data);
    bufinfo->typecode = BYTEARRAY_TYPECODE;
    return 0;
}

STATIC const mp_obj_type_t mp_blob_type = {
    { &mp_type_type },
    .name = MP_QSTR_Blob,
    .print = mp_blob_print,
    //.make_new = make_new_blob,
    //.attr = mp_blob_attr,
    //.locals_dict = (mp_obj_dict_t*)&mp_blob_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC void* mp_to_ptr(mp_obj_t self_in)
{
    mp_buffer_info_t buffer_info;
    if (self_in == mp_const_none)
        return NULL;
    mp_get_buffer_raise(self_in, &buffer_info, MP_BUFFER_READ);
    const mp_obj_type_t *self_in_type = ((mp_obj_base_t*)self_in)->type;
    if (self_in_type == &mp_type_bytes || 
        self_in_type == &mp_type_bytearray ||
        self_in_type == &mp_type_memoryview ||
        self_in_type == &mp_type_str)
            return buffer_info.buf;
    else
    {
        void *result;
        if (buffer_info.len != sizeof(result) || buffer_info.typecode != BYTEARRAY_TYPECODE){
            nlr_raise(
                mp_obj_new_exception_msg_varg(
                    &mp_type_SyntaxError, "Cannot convert %s to pointer!", mp_obj_get_type_str(self_in)));
        }
        memcpy(&result, buffer_info.buf, sizeof(result));
        return result;
    }
}

STATIC inline mp_obj_t ptr_to_mp(void *data)
{
    if (data == NULL) return mp_const_none;
    return lv_to_mp_struct(&mp_blob_type, data);
}

// Cast pointer to struct

STATIC mp_obj_t mp_lv_cast(mp_obj_t type_obj, mp_obj_t ptr_obj)
{
    mp_lv_struct_t *self = m_new_obj(mp_lv_struct_t);
    *self = (mp_lv_struct_t){
        .base = {(const mp_obj_type_t*)type_obj}, 
        .data = mp_to_ptr(ptr_obj)
    };
    return self;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_2(mp_lv_cast_obj, mp_lv_cast);
STATIC MP_DEFINE_CONST_CLASSMETHOD_OBJ(mp_lv_cast_class_method, MP_ROM_PTR(&mp_lv_cast_obj));

STATIC const mp_obj_type_t mp_obj_type;

// Callback function handling
// Callback is either a callable object or a pointer. If it's a callable object, set user_data to the callback.
// Multiple callbacks are kept per object/struct using a dict that associate callback name with callback object
// In case of an lv_obj_t, user_data is mp_lv_obj_t which contains a member "callbacks" for that dict.
// In case of a struct, user_data is a pointer to that dict directly

STATIC mp_obj_t get_callback_dict_from_user_data(void *user_data)
{
    if (user_data){
        mp_obj_t obj = MP_OBJ_FROM_PTR(user_data);
        return 
            MP_OBJ_IS_TYPE(obj, &mp_type_dict)? obj: // Handle the case of dict for a struct
            mp_get_callbacks(obj); // Handle the case of mp_lv_obj_t for an lv_obj_t
    }
    return NULL;
}

STATIC void *mp_lv_callback(mp_obj_t mp_callback, void *lv_callback, qstr callback_name, void **user_data_ptr)
{
    if (lv_callback && mp_obj_is_callable(mp_callback)){
        if (user_data_ptr){
            // user_data is either a dict of callbacks in case of struct, or a pointer to mp_lv_obj_t in case of lv_obj_t
            if (! (*user_data_ptr) ) *user_data_ptr = MP_OBJ_TO_PTR(mp_obj_new_dict(0)); // if it's NULL - it's a dict for a struct
            mp_obj_t callbacks = get_callback_dict_from_user_data(*user_data_ptr);
            mp_obj_dict_store(callbacks, MP_OBJ_NEW_QSTR(callback_name), mp_callback);
        }
        return lv_callback;
    } else {
        return mp_to_ptr(mp_callback);
    }
}


/*
 * LVGL string constants
 */

MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_AUDIO, LV_SYMBOL_AUDIO);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_VIDEO, LV_SYMBOL_VIDEO);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_LIST, LV_SYMBOL_LIST);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_OK, LV_SYMBOL_OK);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_CLOSE, LV_SYMBOL_CLOSE);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_POWER, LV_SYMBOL_POWER);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_SETTINGS, LV_SYMBOL_SETTINGS);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_TRASH, LV_SYMBOL_TRASH);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_HOME, LV_SYMBOL_HOME);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_DOWNLOAD, LV_SYMBOL_DOWNLOAD);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_DRIVE, LV_SYMBOL_DRIVE);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_REFRESH, LV_SYMBOL_REFRESH);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_MUTE, LV_SYMBOL_MUTE);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_VOLUME_MID, LV_SYMBOL_VOLUME_MID);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_VOLUME_MAX, LV_SYMBOL_VOLUME_MAX);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_IMAGE, LV_SYMBOL_IMAGE);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_EDIT, LV_SYMBOL_EDIT);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_PREV, LV_SYMBOL_PREV);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_PLAY, LV_SYMBOL_PLAY);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_PAUSE, LV_SYMBOL_PAUSE);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_STOP, LV_SYMBOL_STOP);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_NEXT, LV_SYMBOL_NEXT);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_EJECT, LV_SYMBOL_EJECT);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_LEFT, LV_SYMBOL_LEFT);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_RIGHT, LV_SYMBOL_RIGHT);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_PLUS, LV_SYMBOL_PLUS);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_MINUS, LV_SYMBOL_MINUS);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_WARNING, LV_SYMBOL_WARNING);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_SHUFFLE, LV_SYMBOL_SHUFFLE);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_UP, LV_SYMBOL_UP);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_DOWN, LV_SYMBOL_DOWN);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_LOOP, LV_SYMBOL_LOOP);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_DIRECTORY, LV_SYMBOL_DIRECTORY);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_UPLOAD, LV_SYMBOL_UPLOAD);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_CALL, LV_SYMBOL_CALL);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_CUT, LV_SYMBOL_CUT);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_COPY, LV_SYMBOL_COPY);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_SAVE, LV_SYMBOL_SAVE);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_CHARGE, LV_SYMBOL_CHARGE);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_BELL, LV_SYMBOL_BELL);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_KEYBOARD, LV_SYMBOL_KEYBOARD);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_GPS, LV_SYMBOL_GPS);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_FILE, LV_SYMBOL_FILE);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_WIFI, LV_SYMBOL_WIFI);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_BATTERY_FULL, LV_SYMBOL_BATTERY_FULL);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_BATTERY_3, LV_SYMBOL_BATTERY_3);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_BATTERY_2, LV_SYMBOL_BATTERY_2);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_BATTERY_1, LV_SYMBOL_BATTERY_1);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_BATTERY_EMPTY, LV_SYMBOL_BATTERY_EMPTY);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_BLUETOOTH, LV_SYMBOL_BLUETOOTH);
MP_DEFINE_STR_OBJ(mp_LV_SYMBOL_DUMMY, LV_SYMBOL_DUMMY);

/*
 * lvgl LV_TASK_PRIO object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_TASK_PRIO_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_OFF), MP_ROM_PTR(MP_ROM_INT(LV_TASK_PRIO_OFF)) },
    { MP_ROM_QSTR(MP_QSTR_LOWEST), MP_ROM_PTR(MP_ROM_INT(LV_TASK_PRIO_LOWEST)) },
    { MP_ROM_QSTR(MP_QSTR_LOW), MP_ROM_PTR(MP_ROM_INT(LV_TASK_PRIO_LOW)) },
    { MP_ROM_QSTR(MP_QSTR_MID), MP_ROM_PTR(MP_ROM_INT(LV_TASK_PRIO_MID)) },
    { MP_ROM_QSTR(MP_QSTR_HIGH), MP_ROM_PTR(MP_ROM_INT(LV_TASK_PRIO_HIGH)) },
    { MP_ROM_QSTR(MP_QSTR_HIGHEST), MP_ROM_PTR(MP_ROM_INT(LV_TASK_PRIO_HIGHEST)) },
    { MP_ROM_QSTR(MP_QSTR_NUM), MP_ROM_PTR(MP_ROM_INT(LV_TASK_PRIO_NUM)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_TASK_PRIO_locals_dict, LV_TASK_PRIO_locals_dict_table);

STATIC void LV_TASK_PRIO_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_TASK_PRIO");
}



STATIC const mp_obj_type_t mp_LV_TASK_PRIO_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_TASK_PRIO,
    .print = LV_TASK_PRIO_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_TASK_PRIO_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_OPA object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_OPA_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_TRANSP), MP_ROM_PTR(MP_ROM_INT(LV_OPA_TRANSP)) },
    { MP_ROM_QSTR(MP_QSTR__0), MP_ROM_PTR(MP_ROM_INT(LV_OPA_0)) },
    { MP_ROM_QSTR(MP_QSTR__10), MP_ROM_PTR(MP_ROM_INT(LV_OPA_10)) },
    { MP_ROM_QSTR(MP_QSTR__20), MP_ROM_PTR(MP_ROM_INT(LV_OPA_20)) },
    { MP_ROM_QSTR(MP_QSTR__30), MP_ROM_PTR(MP_ROM_INT(LV_OPA_30)) },
    { MP_ROM_QSTR(MP_QSTR__40), MP_ROM_PTR(MP_ROM_INT(LV_OPA_40)) },
    { MP_ROM_QSTR(MP_QSTR__50), MP_ROM_PTR(MP_ROM_INT(LV_OPA_50)) },
    { MP_ROM_QSTR(MP_QSTR__60), MP_ROM_PTR(MP_ROM_INT(LV_OPA_60)) },
    { MP_ROM_QSTR(MP_QSTR__70), MP_ROM_PTR(MP_ROM_INT(LV_OPA_70)) },
    { MP_ROM_QSTR(MP_QSTR__80), MP_ROM_PTR(MP_ROM_INT(LV_OPA_80)) },
    { MP_ROM_QSTR(MP_QSTR__90), MP_ROM_PTR(MP_ROM_INT(LV_OPA_90)) },
    { MP_ROM_QSTR(MP_QSTR__100), MP_ROM_PTR(MP_ROM_INT(LV_OPA_100)) },
    { MP_ROM_QSTR(MP_QSTR_COVER), MP_ROM_PTR(MP_ROM_INT(LV_OPA_COVER)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_OPA_locals_dict, LV_OPA_locals_dict_table);

STATIC void LV_OPA_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_OPA");
}



STATIC const mp_obj_type_t mp_LV_OPA_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_OPA,
    .print = LV_OPA_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_OPA_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_INDEV_TYPE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_INDEV_TYPE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_NONE), MP_ROM_PTR(MP_ROM_INT(LV_INDEV_TYPE_NONE)) },
    { MP_ROM_QSTR(MP_QSTR_POINTER), MP_ROM_PTR(MP_ROM_INT(LV_INDEV_TYPE_POINTER)) },
    { MP_ROM_QSTR(MP_QSTR_KEYPAD), MP_ROM_PTR(MP_ROM_INT(LV_INDEV_TYPE_KEYPAD)) },
    { MP_ROM_QSTR(MP_QSTR_BUTTON), MP_ROM_PTR(MP_ROM_INT(LV_INDEV_TYPE_BUTTON)) },
    { MP_ROM_QSTR(MP_QSTR_ENCODER), MP_ROM_PTR(MP_ROM_INT(LV_INDEV_TYPE_ENCODER)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_INDEV_TYPE_locals_dict, LV_INDEV_TYPE_locals_dict_table);

STATIC void LV_INDEV_TYPE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_INDEV_TYPE");
}



STATIC const mp_obj_type_t mp_LV_INDEV_TYPE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_INDEV_TYPE,
    .print = LV_INDEV_TYPE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_INDEV_TYPE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_INDEV_STATE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_INDEV_STATE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_REL), MP_ROM_PTR(MP_ROM_INT(LV_INDEV_STATE_REL)) },
    { MP_ROM_QSTR(MP_QSTR_PR), MP_ROM_PTR(MP_ROM_INT(LV_INDEV_STATE_PR)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_INDEV_STATE_locals_dict, LV_INDEV_STATE_locals_dict_table);

STATIC void LV_INDEV_STATE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_INDEV_STATE");
}



STATIC const mp_obj_type_t mp_LV_INDEV_STATE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_INDEV_STATE,
    .print = LV_INDEV_STATE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_INDEV_STATE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_BORDER object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_BORDER_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_NONE), MP_ROM_PTR(MP_ROM_INT(LV_BORDER_NONE)) },
    { MP_ROM_QSTR(MP_QSTR_BOTTOM), MP_ROM_PTR(MP_ROM_INT(LV_BORDER_BOTTOM)) },
    { MP_ROM_QSTR(MP_QSTR_TOP), MP_ROM_PTR(MP_ROM_INT(LV_BORDER_TOP)) },
    { MP_ROM_QSTR(MP_QSTR_LEFT), MP_ROM_PTR(MP_ROM_INT(LV_BORDER_LEFT)) },
    { MP_ROM_QSTR(MP_QSTR_RIGHT), MP_ROM_PTR(MP_ROM_INT(LV_BORDER_RIGHT)) },
    { MP_ROM_QSTR(MP_QSTR_FULL), MP_ROM_PTR(MP_ROM_INT(LV_BORDER_FULL)) },
    { MP_ROM_QSTR(MP_QSTR_INTERNAL), MP_ROM_PTR(MP_ROM_INT(LV_BORDER_INTERNAL)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_BORDER_locals_dict, LV_BORDER_locals_dict_table);

STATIC void LV_BORDER_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_BORDER");
}



STATIC const mp_obj_type_t mp_LV_BORDER_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_BORDER,
    .print = LV_BORDER_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_BORDER_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_SHADOW object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_SHADOW_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BOTTOM), MP_ROM_PTR(MP_ROM_INT(LV_SHADOW_BOTTOM)) },
    { MP_ROM_QSTR(MP_QSTR_FULL), MP_ROM_PTR(MP_ROM_INT(LV_SHADOW_FULL)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_SHADOW_locals_dict, LV_SHADOW_locals_dict_table);

STATIC void LV_SHADOW_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_SHADOW");
}



STATIC const mp_obj_type_t mp_LV_SHADOW_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_SHADOW,
    .print = LV_SHADOW_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_SHADOW_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_DESIGN object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_DESIGN_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_DRAW_MAIN), MP_ROM_PTR(MP_ROM_INT(LV_DESIGN_DRAW_MAIN)) },
    { MP_ROM_QSTR(MP_QSTR_DRAW_POST), MP_ROM_PTR(MP_ROM_INT(LV_DESIGN_DRAW_POST)) },
    { MP_ROM_QSTR(MP_QSTR_COVER_CHK), MP_ROM_PTR(MP_ROM_INT(LV_DESIGN_COVER_CHK)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_DESIGN_locals_dict, LV_DESIGN_locals_dict_table);

STATIC void LV_DESIGN_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_DESIGN");
}



STATIC const mp_obj_type_t mp_LV_DESIGN_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_DESIGN,
    .print = LV_DESIGN_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_DESIGN_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_RES object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_RES_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_INV), MP_ROM_PTR(MP_ROM_INT(LV_RES_INV)) },
    { MP_ROM_QSTR(MP_QSTR_OK), MP_ROM_PTR(MP_ROM_INT(LV_RES_OK)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_RES_locals_dict, LV_RES_locals_dict_table);

STATIC void LV_RES_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_RES");
}



STATIC const mp_obj_type_t mp_LV_RES_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_RES,
    .print = LV_RES_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_RES_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_EVENT object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_EVENT_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_PRESSED), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_PRESSED)) },
    { MP_ROM_QSTR(MP_QSTR_PRESSING), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_PRESSING)) },
    { MP_ROM_QSTR(MP_QSTR_PRESS_LOST), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_PRESS_LOST)) },
    { MP_ROM_QSTR(MP_QSTR_SHORT_CLICKED), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_SHORT_CLICKED)) },
    { MP_ROM_QSTR(MP_QSTR_LONG_PRESSED), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_LONG_PRESSED)) },
    { MP_ROM_QSTR(MP_QSTR_LONG_PRESSED_REPEAT), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_LONG_PRESSED_REPEAT)) },
    { MP_ROM_QSTR(MP_QSTR_CLICKED), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_CLICKED)) },
    { MP_ROM_QSTR(MP_QSTR_RELEASED), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_RELEASED)) },
    { MP_ROM_QSTR(MP_QSTR_DRAG_BEGIN), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_DRAG_BEGIN)) },
    { MP_ROM_QSTR(MP_QSTR_DRAG_END), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_DRAG_END)) },
    { MP_ROM_QSTR(MP_QSTR_DRAG_THROW_BEGIN), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_DRAG_THROW_BEGIN)) },
    { MP_ROM_QSTR(MP_QSTR_FOCUSED), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_FOCUSED)) },
    { MP_ROM_QSTR(MP_QSTR_DEFOCUSED), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_DEFOCUSED)) },
    { MP_ROM_QSTR(MP_QSTR_VALUE_CHANGED), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_VALUE_CHANGED)) },
    { MP_ROM_QSTR(MP_QSTR_INSERT), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_INSERT)) },
    { MP_ROM_QSTR(MP_QSTR_SELECTED), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_SELECTED)) },
    { MP_ROM_QSTR(MP_QSTR_REFRESH), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_REFRESH)) },
    { MP_ROM_QSTR(MP_QSTR_APPLY), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_APPLY)) },
    { MP_ROM_QSTR(MP_QSTR_CANCEL), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_CANCEL)) },
    { MP_ROM_QSTR(MP_QSTR_DELETE), MP_ROM_PTR(MP_ROM_INT(LV_EVENT_DELETE)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_EVENT_locals_dict, LV_EVENT_locals_dict_table);

STATIC void LV_EVENT_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_EVENT");
}



STATIC const mp_obj_type_t mp_LV_EVENT_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_EVENT,
    .print = LV_EVENT_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_EVENT_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_SIGNAL object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_SIGNAL_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_CLEANUP), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_CLEANUP)) },
    { MP_ROM_QSTR(MP_QSTR_CHILD_CHG), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_CHILD_CHG)) },
    { MP_ROM_QSTR(MP_QSTR_CORD_CHG), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_CORD_CHG)) },
    { MP_ROM_QSTR(MP_QSTR_PARENT_SIZE_CHG), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_PARENT_SIZE_CHG)) },
    { MP_ROM_QSTR(MP_QSTR_STYLE_CHG), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_STYLE_CHG)) },
    { MP_ROM_QSTR(MP_QSTR_REFR_EXT_DRAW_PAD), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_REFR_EXT_DRAW_PAD)) },
    { MP_ROM_QSTR(MP_QSTR_GET_TYPE), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_GET_TYPE)) },
    { MP_ROM_QSTR(MP_QSTR_PRESSED), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_PRESSED)) },
    { MP_ROM_QSTR(MP_QSTR_PRESSING), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_PRESSING)) },
    { MP_ROM_QSTR(MP_QSTR_PRESS_LOST), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_PRESS_LOST)) },
    { MP_ROM_QSTR(MP_QSTR_RELEASED), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_RELEASED)) },
    { MP_ROM_QSTR(MP_QSTR_LONG_PRESS), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_LONG_PRESS)) },
    { MP_ROM_QSTR(MP_QSTR_LONG_PRESS_REP), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_LONG_PRESS_REP)) },
    { MP_ROM_QSTR(MP_QSTR_DRAG_BEGIN), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_DRAG_BEGIN)) },
    { MP_ROM_QSTR(MP_QSTR_DRAG_END), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_DRAG_END)) },
    { MP_ROM_QSTR(MP_QSTR_FOCUS), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_FOCUS)) },
    { MP_ROM_QSTR(MP_QSTR_DEFOCUS), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_DEFOCUS)) },
    { MP_ROM_QSTR(MP_QSTR_CONTROL), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_CONTROL)) },
    { MP_ROM_QSTR(MP_QSTR_GET_EDITABLE), MP_ROM_PTR(MP_ROM_INT(LV_SIGNAL_GET_EDITABLE)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_SIGNAL_locals_dict, LV_SIGNAL_locals_dict_table);

STATIC void LV_SIGNAL_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_SIGNAL");
}



STATIC const mp_obj_type_t mp_LV_SIGNAL_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_SIGNAL,
    .print = LV_SIGNAL_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_SIGNAL_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_ALIGN object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_ALIGN_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_CENTER), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_CENTER)) },
    { MP_ROM_QSTR(MP_QSTR_IN_TOP_LEFT), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_IN_TOP_LEFT)) },
    { MP_ROM_QSTR(MP_QSTR_IN_TOP_MID), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_IN_TOP_MID)) },
    { MP_ROM_QSTR(MP_QSTR_IN_TOP_RIGHT), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_IN_TOP_RIGHT)) },
    { MP_ROM_QSTR(MP_QSTR_IN_BOTTOM_LEFT), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_IN_BOTTOM_LEFT)) },
    { MP_ROM_QSTR(MP_QSTR_IN_BOTTOM_MID), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_IN_BOTTOM_MID)) },
    { MP_ROM_QSTR(MP_QSTR_IN_BOTTOM_RIGHT), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_IN_BOTTOM_RIGHT)) },
    { MP_ROM_QSTR(MP_QSTR_IN_LEFT_MID), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_IN_LEFT_MID)) },
    { MP_ROM_QSTR(MP_QSTR_IN_RIGHT_MID), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_IN_RIGHT_MID)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_TOP_LEFT), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_OUT_TOP_LEFT)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_TOP_MID), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_OUT_TOP_MID)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_TOP_RIGHT), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_OUT_TOP_RIGHT)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_BOTTOM_LEFT), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_OUT_BOTTOM_LEFT)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_BOTTOM_MID), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_OUT_BOTTOM_MID)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_BOTTOM_RIGHT), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_OUT_BOTTOM_RIGHT)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_LEFT_TOP), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_OUT_LEFT_TOP)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_LEFT_MID), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_OUT_LEFT_MID)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_LEFT_BOTTOM), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_OUT_LEFT_BOTTOM)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_RIGHT_TOP), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_OUT_RIGHT_TOP)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_RIGHT_MID), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_OUT_RIGHT_MID)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_RIGHT_BOTTOM), MP_ROM_PTR(MP_ROM_INT(LV_ALIGN_OUT_RIGHT_BOTTOM)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_ALIGN_locals_dict, LV_ALIGN_locals_dict_table);

STATIC void LV_ALIGN_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_ALIGN");
}



STATIC const mp_obj_type_t mp_LV_ALIGN_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_ALIGN,
    .print = LV_ALIGN_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_ALIGN_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_DRAG_DIR object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_DRAG_DIR_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_HOR), MP_ROM_PTR(MP_ROM_INT(LV_DRAG_DIR_HOR)) },
    { MP_ROM_QSTR(MP_QSTR_VER), MP_ROM_PTR(MP_ROM_INT(LV_DRAG_DIR_VER)) },
    { MP_ROM_QSTR(MP_QSTR_ALL), MP_ROM_PTR(MP_ROM_INT(LV_DRAG_DIR_ALL)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_DRAG_DIR_locals_dict, LV_DRAG_DIR_locals_dict_table);

STATIC void LV_DRAG_DIR_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_DRAG_DIR");
}



STATIC const mp_obj_type_t mp_LV_DRAG_DIR_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_DRAG_DIR,
    .print = LV_DRAG_DIR_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_DRAG_DIR_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_PROTECT object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_PROTECT_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_NONE), MP_ROM_PTR(MP_ROM_INT(LV_PROTECT_NONE)) },
    { MP_ROM_QSTR(MP_QSTR_CHILD_CHG), MP_ROM_PTR(MP_ROM_INT(LV_PROTECT_CHILD_CHG)) },
    { MP_ROM_QSTR(MP_QSTR_PARENT), MP_ROM_PTR(MP_ROM_INT(LV_PROTECT_PARENT)) },
    { MP_ROM_QSTR(MP_QSTR_POS), MP_ROM_PTR(MP_ROM_INT(LV_PROTECT_POS)) },
    { MP_ROM_QSTR(MP_QSTR_FOLLOW), MP_ROM_PTR(MP_ROM_INT(LV_PROTECT_FOLLOW)) },
    { MP_ROM_QSTR(MP_QSTR_PRESS_LOST), MP_ROM_PTR(MP_ROM_INT(LV_PROTECT_PRESS_LOST)) },
    { MP_ROM_QSTR(MP_QSTR_CLICK_FOCUS), MP_ROM_PTR(MP_ROM_INT(LV_PROTECT_CLICK_FOCUS)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_PROTECT_locals_dict, LV_PROTECT_locals_dict_table);

STATIC void LV_PROTECT_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_PROTECT");
}



STATIC const mp_obj_type_t mp_LV_PROTECT_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_PROTECT,
    .print = LV_PROTECT_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_PROTECT_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_GROUP_REFOCUS_POLICY object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_GROUP_REFOCUS_POLICY_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_NEXT), MP_ROM_PTR(MP_ROM_INT(LV_GROUP_REFOCUS_POLICY_NEXT)) },
    { MP_ROM_QSTR(MP_QSTR_PREV), MP_ROM_PTR(MP_ROM_INT(LV_GROUP_REFOCUS_POLICY_PREV)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_GROUP_REFOCUS_POLICY_locals_dict, LV_GROUP_REFOCUS_POLICY_locals_dict_table);

STATIC void LV_GROUP_REFOCUS_POLICY_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_GROUP_REFOCUS_POLICY");
}



STATIC const mp_obj_type_t mp_LV_GROUP_REFOCUS_POLICY_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_GROUP_REFOCUS_POLICY,
    .print = LV_GROUP_REFOCUS_POLICY_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_GROUP_REFOCUS_POLICY_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_LAYOUT object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_LAYOUT_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_OFF), MP_ROM_PTR(MP_ROM_INT(LV_LAYOUT_OFF)) },
    { MP_ROM_QSTR(MP_QSTR_CENTER), MP_ROM_PTR(MP_ROM_INT(LV_LAYOUT_CENTER)) },
    { MP_ROM_QSTR(MP_QSTR_COL_L), MP_ROM_PTR(MP_ROM_INT(LV_LAYOUT_COL_L)) },
    { MP_ROM_QSTR(MP_QSTR_COL_M), MP_ROM_PTR(MP_ROM_INT(LV_LAYOUT_COL_M)) },
    { MP_ROM_QSTR(MP_QSTR_COL_R), MP_ROM_PTR(MP_ROM_INT(LV_LAYOUT_COL_R)) },
    { MP_ROM_QSTR(MP_QSTR_ROW_T), MP_ROM_PTR(MP_ROM_INT(LV_LAYOUT_ROW_T)) },
    { MP_ROM_QSTR(MP_QSTR_ROW_M), MP_ROM_PTR(MP_ROM_INT(LV_LAYOUT_ROW_M)) },
    { MP_ROM_QSTR(MP_QSTR_ROW_B), MP_ROM_PTR(MP_ROM_INT(LV_LAYOUT_ROW_B)) },
    { MP_ROM_QSTR(MP_QSTR_PRETTY), MP_ROM_PTR(MP_ROM_INT(LV_LAYOUT_PRETTY)) },
    { MP_ROM_QSTR(MP_QSTR_GRID), MP_ROM_PTR(MP_ROM_INT(LV_LAYOUT_GRID)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_LAYOUT_locals_dict, LV_LAYOUT_locals_dict_table);

STATIC void LV_LAYOUT_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_LAYOUT");
}



STATIC const mp_obj_type_t mp_LV_LAYOUT_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_LAYOUT,
    .print = LV_LAYOUT_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_LAYOUT_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_FIT object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_FIT_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_NONE), MP_ROM_PTR(MP_ROM_INT(LV_FIT_NONE)) },
    { MP_ROM_QSTR(MP_QSTR_TIGHT), MP_ROM_PTR(MP_ROM_INT(LV_FIT_TIGHT)) },
    { MP_ROM_QSTR(MP_QSTR_FLOOD), MP_ROM_PTR(MP_ROM_INT(LV_FIT_FLOOD)) },
    { MP_ROM_QSTR(MP_QSTR_FILL), MP_ROM_PTR(MP_ROM_INT(LV_FIT_FILL)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_FIT_locals_dict, LV_FIT_locals_dict_table);

STATIC void LV_FIT_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_FIT");
}



STATIC const mp_obj_type_t mp_LV_FIT_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_FIT,
    .print = LV_FIT_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_FIT_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_BTN_STATE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_BTN_STATE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_REL), MP_ROM_PTR(MP_ROM_INT(LV_BTN_STATE_REL)) },
    { MP_ROM_QSTR(MP_QSTR_PR), MP_ROM_PTR(MP_ROM_INT(LV_BTN_STATE_PR)) },
    { MP_ROM_QSTR(MP_QSTR_TGL_REL), MP_ROM_PTR(MP_ROM_INT(LV_BTN_STATE_TGL_REL)) },
    { MP_ROM_QSTR(MP_QSTR_TGL_PR), MP_ROM_PTR(MP_ROM_INT(LV_BTN_STATE_TGL_PR)) },
    { MP_ROM_QSTR(MP_QSTR_INA), MP_ROM_PTR(MP_ROM_INT(LV_BTN_STATE_INA)) },
    { MP_ROM_QSTR(MP_QSTR_NUM), MP_ROM_PTR(MP_ROM_INT(LV_BTN_STATE_NUM)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_BTN_STATE_locals_dict, LV_BTN_STATE_locals_dict_table);

STATIC void LV_BTN_STATE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_BTN_STATE");
}



STATIC const mp_obj_type_t mp_LV_BTN_STATE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_BTN_STATE,
    .print = LV_BTN_STATE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_BTN_STATE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_BTN_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_BTN_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_REL), MP_ROM_PTR(MP_ROM_INT(LV_BTN_STYLE_REL)) },
    { MP_ROM_QSTR(MP_QSTR_PR), MP_ROM_PTR(MP_ROM_INT(LV_BTN_STYLE_PR)) },
    { MP_ROM_QSTR(MP_QSTR_TGL_REL), MP_ROM_PTR(MP_ROM_INT(LV_BTN_STYLE_TGL_REL)) },
    { MP_ROM_QSTR(MP_QSTR_TGL_PR), MP_ROM_PTR(MP_ROM_INT(LV_BTN_STYLE_TGL_PR)) },
    { MP_ROM_QSTR(MP_QSTR_INA), MP_ROM_PTR(MP_ROM_INT(LV_BTN_STYLE_INA)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_BTN_STYLE_locals_dict, LV_BTN_STYLE_locals_dict_table);

STATIC void LV_BTN_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_BTN_STYLE");
}



STATIC const mp_obj_type_t mp_LV_BTN_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_BTN_STYLE,
    .print = LV_BTN_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_BTN_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_TXT_FLAG object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_TXT_FLAG_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_NONE), MP_ROM_PTR(MP_ROM_INT(LV_TXT_FLAG_NONE)) },
    { MP_ROM_QSTR(MP_QSTR_RECOLOR), MP_ROM_PTR(MP_ROM_INT(LV_TXT_FLAG_RECOLOR)) },
    { MP_ROM_QSTR(MP_QSTR_EXPAND), MP_ROM_PTR(MP_ROM_INT(LV_TXT_FLAG_EXPAND)) },
    { MP_ROM_QSTR(MP_QSTR_CENTER), MP_ROM_PTR(MP_ROM_INT(LV_TXT_FLAG_CENTER)) },
    { MP_ROM_QSTR(MP_QSTR_RIGHT), MP_ROM_PTR(MP_ROM_INT(LV_TXT_FLAG_RIGHT)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_TXT_FLAG_locals_dict, LV_TXT_FLAG_locals_dict_table);

STATIC void LV_TXT_FLAG_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_TXT_FLAG");
}



STATIC const mp_obj_type_t mp_LV_TXT_FLAG_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_TXT_FLAG,
    .print = LV_TXT_FLAG_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_TXT_FLAG_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_TXT_CMD_STATE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_TXT_CMD_STATE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_WAIT), MP_ROM_PTR(MP_ROM_INT(LV_TXT_CMD_STATE_WAIT)) },
    { MP_ROM_QSTR(MP_QSTR_PAR), MP_ROM_PTR(MP_ROM_INT(LV_TXT_CMD_STATE_PAR)) },
    { MP_ROM_QSTR(MP_QSTR_IN), MP_ROM_PTR(MP_ROM_INT(LV_TXT_CMD_STATE_IN)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_TXT_CMD_STATE_locals_dict, LV_TXT_CMD_STATE_locals_dict_table);

STATIC void LV_TXT_CMD_STATE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_TXT_CMD_STATE");
}



STATIC const mp_obj_type_t mp_LV_TXT_CMD_STATE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_TXT_CMD_STATE,
    .print = LV_TXT_CMD_STATE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_TXT_CMD_STATE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_IMG_SRC object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_IMG_SRC_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_VARIABLE), MP_ROM_PTR(MP_ROM_INT(LV_IMG_SRC_VARIABLE)) },
    { MP_ROM_QSTR(MP_QSTR_FILE), MP_ROM_PTR(MP_ROM_INT(LV_IMG_SRC_FILE)) },
    { MP_ROM_QSTR(MP_QSTR_SYMBOL), MP_ROM_PTR(MP_ROM_INT(LV_IMG_SRC_SYMBOL)) },
    { MP_ROM_QSTR(MP_QSTR_UNKNOWN), MP_ROM_PTR(MP_ROM_INT(LV_IMG_SRC_UNKNOWN)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_IMG_SRC_locals_dict, LV_IMG_SRC_locals_dict_table);

STATIC void LV_IMG_SRC_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_IMG_SRC");
}



STATIC const mp_obj_type_t mp_LV_IMG_SRC_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_IMG_SRC,
    .print = LV_IMG_SRC_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_IMG_SRC_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_IMG_CF object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_IMG_CF_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_UNKNOWN), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_UNKNOWN)) },
    { MP_ROM_QSTR(MP_QSTR_RAW), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_RAW)) },
    { MP_ROM_QSTR(MP_QSTR_RAW_ALPHA), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_RAW_ALPHA)) },
    { MP_ROM_QSTR(MP_QSTR_RAW_CHROMA_KEYED), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_RAW_CHROMA_KEYED)) },
    { MP_ROM_QSTR(MP_QSTR_TRUE_COLOR), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_TRUE_COLOR)) },
    { MP_ROM_QSTR(MP_QSTR_TRUE_COLOR_ALPHA), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_TRUE_COLOR_ALPHA)) },
    { MP_ROM_QSTR(MP_QSTR_TRUE_COLOR_CHROMA_KEYED), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED)) },
    { MP_ROM_QSTR(MP_QSTR_INDEXED_1BIT), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_INDEXED_1BIT)) },
    { MP_ROM_QSTR(MP_QSTR_INDEXED_2BIT), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_INDEXED_2BIT)) },
    { MP_ROM_QSTR(MP_QSTR_INDEXED_4BIT), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_INDEXED_4BIT)) },
    { MP_ROM_QSTR(MP_QSTR_INDEXED_8BIT), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_INDEXED_8BIT)) },
    { MP_ROM_QSTR(MP_QSTR_ALPHA_1BIT), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_ALPHA_1BIT)) },
    { MP_ROM_QSTR(MP_QSTR_ALPHA_2BIT), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_ALPHA_2BIT)) },
    { MP_ROM_QSTR(MP_QSTR_ALPHA_4BIT), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_ALPHA_4BIT)) },
    { MP_ROM_QSTR(MP_QSTR_ALPHA_8BIT), MP_ROM_PTR(MP_ROM_INT(LV_IMG_CF_ALPHA_8BIT)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_IMG_CF_locals_dict, LV_IMG_CF_locals_dict_table);

STATIC void LV_IMG_CF_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_IMG_CF");
}



STATIC const mp_obj_type_t mp_LV_IMG_CF_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_IMG_CF,
    .print = LV_IMG_CF_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_IMG_CF_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_IMGBTN_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_IMGBTN_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_REL), MP_ROM_PTR(MP_ROM_INT(LV_IMGBTN_STYLE_REL)) },
    { MP_ROM_QSTR(MP_QSTR_PR), MP_ROM_PTR(MP_ROM_INT(LV_IMGBTN_STYLE_PR)) },
    { MP_ROM_QSTR(MP_QSTR_TGL_REL), MP_ROM_PTR(MP_ROM_INT(LV_IMGBTN_STYLE_TGL_REL)) },
    { MP_ROM_QSTR(MP_QSTR_TGL_PR), MP_ROM_PTR(MP_ROM_INT(LV_IMGBTN_STYLE_TGL_PR)) },
    { MP_ROM_QSTR(MP_QSTR_INA), MP_ROM_PTR(MP_ROM_INT(LV_IMGBTN_STYLE_INA)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_IMGBTN_STYLE_locals_dict, LV_IMGBTN_STYLE_locals_dict_table);

STATIC void LV_IMGBTN_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_IMGBTN_STYLE");
}



STATIC const mp_obj_type_t mp_LV_IMGBTN_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_IMGBTN_STYLE,
    .print = LV_IMGBTN_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_IMGBTN_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_FS_RES object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_FS_RES_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_OK), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_OK)) },
    { MP_ROM_QSTR(MP_QSTR_HW_ERR), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_HW_ERR)) },
    { MP_ROM_QSTR(MP_QSTR_FS_ERR), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_FS_ERR)) },
    { MP_ROM_QSTR(MP_QSTR_NOT_EX), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_NOT_EX)) },
    { MP_ROM_QSTR(MP_QSTR_FULL), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_FULL)) },
    { MP_ROM_QSTR(MP_QSTR_LOCKED), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_LOCKED)) },
    { MP_ROM_QSTR(MP_QSTR_DENIED), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_DENIED)) },
    { MP_ROM_QSTR(MP_QSTR_BUSY), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_BUSY)) },
    { MP_ROM_QSTR(MP_QSTR_TOUT), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_TOUT)) },
    { MP_ROM_QSTR(MP_QSTR_NOT_IMP), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_NOT_IMP)) },
    { MP_ROM_QSTR(MP_QSTR_OUT_OF_MEM), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_OUT_OF_MEM)) },
    { MP_ROM_QSTR(MP_QSTR_INV_PARAM), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_INV_PARAM)) },
    { MP_ROM_QSTR(MP_QSTR_UNKNOWN), MP_ROM_PTR(MP_ROM_INT(LV_FS_RES_UNKNOWN)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_FS_RES_locals_dict, LV_FS_RES_locals_dict_table);

STATIC void LV_FS_RES_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_FS_RES");
}



STATIC const mp_obj_type_t mp_LV_FS_RES_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_FS_RES,
    .print = LV_FS_RES_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_FS_RES_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_FS_MODE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_FS_MODE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_WR), MP_ROM_PTR(MP_ROM_INT(LV_FS_MODE_WR)) },
    { MP_ROM_QSTR(MP_QSTR_RD), MP_ROM_PTR(MP_ROM_INT(LV_FS_MODE_RD)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_FS_MODE_locals_dict, LV_FS_MODE_locals_dict_table);

STATIC void LV_FS_MODE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_FS_MODE");
}



STATIC const mp_obj_type_t mp_LV_FS_MODE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_FS_MODE,
    .print = LV_FS_MODE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_FS_MODE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_LABEL_LONG object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_LABEL_LONG_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_EXPAND), MP_ROM_PTR(MP_ROM_INT(LV_LABEL_LONG_EXPAND)) },
    { MP_ROM_QSTR(MP_QSTR_BREAK), MP_ROM_PTR(MP_ROM_INT(LV_LABEL_LONG_BREAK)) },
    { MP_ROM_QSTR(MP_QSTR_DOT), MP_ROM_PTR(MP_ROM_INT(LV_LABEL_LONG_DOT)) },
    { MP_ROM_QSTR(MP_QSTR_ROLL), MP_ROM_PTR(MP_ROM_INT(LV_LABEL_LONG_ROLL)) },
    { MP_ROM_QSTR(MP_QSTR_ROLL_CIRC), MP_ROM_PTR(MP_ROM_INT(LV_LABEL_LONG_ROLL_CIRC)) },
    { MP_ROM_QSTR(MP_QSTR_CROP), MP_ROM_PTR(MP_ROM_INT(LV_LABEL_LONG_CROP)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_LABEL_LONG_locals_dict, LV_LABEL_LONG_locals_dict_table);

STATIC void LV_LABEL_LONG_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_LABEL_LONG");
}



STATIC const mp_obj_type_t mp_LV_LABEL_LONG_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_LABEL_LONG,
    .print = LV_LABEL_LONG_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_LABEL_LONG_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_LABEL_ALIGN object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_LABEL_ALIGN_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_LEFT), MP_ROM_PTR(MP_ROM_INT(LV_LABEL_ALIGN_LEFT)) },
    { MP_ROM_QSTR(MP_QSTR_CENTER), MP_ROM_PTR(MP_ROM_INT(LV_LABEL_ALIGN_CENTER)) },
    { MP_ROM_QSTR(MP_QSTR_RIGHT), MP_ROM_PTR(MP_ROM_INT(LV_LABEL_ALIGN_RIGHT)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_LABEL_ALIGN_locals_dict, LV_LABEL_ALIGN_locals_dict_table);

STATIC void LV_LABEL_ALIGN_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_LABEL_ALIGN");
}



STATIC const mp_obj_type_t mp_LV_LABEL_ALIGN_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_LABEL_ALIGN,
    .print = LV_LABEL_ALIGN_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_LABEL_ALIGN_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_SB_MODE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_SB_MODE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_OFF), MP_ROM_PTR(MP_ROM_INT(LV_SB_MODE_OFF)) },
    { MP_ROM_QSTR(MP_QSTR_ON), MP_ROM_PTR(MP_ROM_INT(LV_SB_MODE_ON)) },
    { MP_ROM_QSTR(MP_QSTR_DRAG), MP_ROM_PTR(MP_ROM_INT(LV_SB_MODE_DRAG)) },
    { MP_ROM_QSTR(MP_QSTR_AUTO), MP_ROM_PTR(MP_ROM_INT(LV_SB_MODE_AUTO)) },
    { MP_ROM_QSTR(MP_QSTR_HIDE), MP_ROM_PTR(MP_ROM_INT(LV_SB_MODE_HIDE)) },
    { MP_ROM_QSTR(MP_QSTR_UNHIDE), MP_ROM_PTR(MP_ROM_INT(LV_SB_MODE_UNHIDE)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_SB_MODE_locals_dict, LV_SB_MODE_locals_dict_table);

STATIC void LV_SB_MODE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_SB_MODE");
}



STATIC const mp_obj_type_t mp_LV_SB_MODE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_SB_MODE,
    .print = LV_SB_MODE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_SB_MODE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_PAGE_EDGE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_PAGE_EDGE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_LEFT), MP_ROM_PTR(MP_ROM_INT(LV_PAGE_EDGE_LEFT)) },
    { MP_ROM_QSTR(MP_QSTR_TOP), MP_ROM_PTR(MP_ROM_INT(LV_PAGE_EDGE_TOP)) },
    { MP_ROM_QSTR(MP_QSTR_RIGHT), MP_ROM_PTR(MP_ROM_INT(LV_PAGE_EDGE_RIGHT)) },
    { MP_ROM_QSTR(MP_QSTR_BOTTOM), MP_ROM_PTR(MP_ROM_INT(LV_PAGE_EDGE_BOTTOM)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_PAGE_EDGE_locals_dict, LV_PAGE_EDGE_locals_dict_table);

STATIC void LV_PAGE_EDGE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_PAGE_EDGE");
}



STATIC const mp_obj_type_t mp_LV_PAGE_EDGE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_PAGE_EDGE,
    .print = LV_PAGE_EDGE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_PAGE_EDGE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_PAGE_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_PAGE_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_PAGE_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_SCRL), MP_ROM_PTR(MP_ROM_INT(LV_PAGE_STYLE_SCRL)) },
    { MP_ROM_QSTR(MP_QSTR_SB), MP_ROM_PTR(MP_ROM_INT(LV_PAGE_STYLE_SB)) },
    { MP_ROM_QSTR(MP_QSTR_EDGE_FLASH), MP_ROM_PTR(MP_ROM_INT(LV_PAGE_STYLE_EDGE_FLASH)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_PAGE_STYLE_locals_dict, LV_PAGE_STYLE_locals_dict_table);

STATIC void LV_PAGE_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_PAGE_STYLE");
}



STATIC const mp_obj_type_t mp_LV_PAGE_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_PAGE_STYLE,
    .print = LV_PAGE_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_PAGE_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_LIST_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_LIST_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_LIST_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_SCRL), MP_ROM_PTR(MP_ROM_INT(LV_LIST_STYLE_SCRL)) },
    { MP_ROM_QSTR(MP_QSTR_SB), MP_ROM_PTR(MP_ROM_INT(LV_LIST_STYLE_SB)) },
    { MP_ROM_QSTR(MP_QSTR_EDGE_FLASH), MP_ROM_PTR(MP_ROM_INT(LV_LIST_STYLE_EDGE_FLASH)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_REL), MP_ROM_PTR(MP_ROM_INT(LV_LIST_STYLE_BTN_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_PR), MP_ROM_PTR(MP_ROM_INT(LV_LIST_STYLE_BTN_PR)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_TGL_REL), MP_ROM_PTR(MP_ROM_INT(LV_LIST_STYLE_BTN_TGL_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_TGL_PR), MP_ROM_PTR(MP_ROM_INT(LV_LIST_STYLE_BTN_TGL_PR)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_INA), MP_ROM_PTR(MP_ROM_INT(LV_LIST_STYLE_BTN_INA)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_LIST_STYLE_locals_dict, LV_LIST_STYLE_locals_dict_table);

STATIC void LV_LIST_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_LIST_STYLE");
}



STATIC const mp_obj_type_t mp_LV_LIST_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_LIST_STYLE,
    .print = LV_LIST_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_LIST_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_CHART_TYPE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_CHART_TYPE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_LINE), MP_ROM_PTR(MP_ROM_INT(LV_CHART_TYPE_LINE)) },
    { MP_ROM_QSTR(MP_QSTR_COLUMN), MP_ROM_PTR(MP_ROM_INT(LV_CHART_TYPE_COLUMN)) },
    { MP_ROM_QSTR(MP_QSTR_POINT), MP_ROM_PTR(MP_ROM_INT(LV_CHART_TYPE_POINT)) },
    { MP_ROM_QSTR(MP_QSTR_VERTICAL_LINE), MP_ROM_PTR(MP_ROM_INT(LV_CHART_TYPE_VERTICAL_LINE)) },
    { MP_ROM_QSTR(MP_QSTR_AREA), MP_ROM_PTR(MP_ROM_INT(LV_CHART_TYPE_AREA)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_CHART_TYPE_locals_dict, LV_CHART_TYPE_locals_dict_table);

STATIC void LV_CHART_TYPE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_CHART_TYPE");
}



STATIC const mp_obj_type_t mp_LV_CHART_TYPE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_CHART_TYPE,
    .print = LV_CHART_TYPE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_CHART_TYPE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_CHART_UPDATE_MODE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_CHART_UPDATE_MODE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SHIFT), MP_ROM_PTR(MP_ROM_INT(LV_CHART_UPDATE_MODE_SHIFT)) },
    { MP_ROM_QSTR(MP_QSTR_CIRCULAR), MP_ROM_PTR(MP_ROM_INT(LV_CHART_UPDATE_MODE_CIRCULAR)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_CHART_UPDATE_MODE_locals_dict, LV_CHART_UPDATE_MODE_locals_dict_table);

STATIC void LV_CHART_UPDATE_MODE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_CHART_UPDATE_MODE");
}



STATIC const mp_obj_type_t mp_LV_CHART_UPDATE_MODE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_CHART_UPDATE_MODE,
    .print = LV_CHART_UPDATE_MODE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_CHART_UPDATE_MODE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_CHART_AXIS_DRAW_LAST object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_CHART_AXIS_DRAW_LAST_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_TICK), MP_ROM_PTR(MP_ROM_INT(LV_CHART_AXIS_DRAW_LAST_TICK)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_CHART_AXIS_DRAW_LAST_locals_dict, LV_CHART_AXIS_DRAW_LAST_locals_dict_table);

STATIC void LV_CHART_AXIS_DRAW_LAST_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_CHART_AXIS_DRAW_LAST");
}



STATIC const mp_obj_type_t mp_LV_CHART_AXIS_DRAW_LAST_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_CHART_AXIS_DRAW_LAST,
    .print = LV_CHART_AXIS_DRAW_LAST_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_CHART_AXIS_DRAW_LAST_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_TABLE_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_TABLE_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_TABLE_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_CELL1), MP_ROM_PTR(MP_ROM_INT(LV_TABLE_STYLE_CELL1)) },
    { MP_ROM_QSTR(MP_QSTR_CELL2), MP_ROM_PTR(MP_ROM_INT(LV_TABLE_STYLE_CELL2)) },
    { MP_ROM_QSTR(MP_QSTR_CELL3), MP_ROM_PTR(MP_ROM_INT(LV_TABLE_STYLE_CELL3)) },
    { MP_ROM_QSTR(MP_QSTR_CELL4), MP_ROM_PTR(MP_ROM_INT(LV_TABLE_STYLE_CELL4)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_TABLE_STYLE_locals_dict, LV_TABLE_STYLE_locals_dict_table);

STATIC void LV_TABLE_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_TABLE_STYLE");
}



STATIC const mp_obj_type_t mp_LV_TABLE_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_TABLE_STYLE,
    .print = LV_TABLE_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_TABLE_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_CB_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_CB_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_CB_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_BOX_REL), MP_ROM_PTR(MP_ROM_INT(LV_CB_STYLE_BOX_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BOX_PR), MP_ROM_PTR(MP_ROM_INT(LV_CB_STYLE_BOX_PR)) },
    { MP_ROM_QSTR(MP_QSTR_BOX_TGL_REL), MP_ROM_PTR(MP_ROM_INT(LV_CB_STYLE_BOX_TGL_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BOX_TGL_PR), MP_ROM_PTR(MP_ROM_INT(LV_CB_STYLE_BOX_TGL_PR)) },
    { MP_ROM_QSTR(MP_QSTR_BOX_INA), MP_ROM_PTR(MP_ROM_INT(LV_CB_STYLE_BOX_INA)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_CB_STYLE_locals_dict, LV_CB_STYLE_locals_dict_table);

STATIC void LV_CB_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_CB_STYLE");
}



STATIC const mp_obj_type_t mp_LV_CB_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_CB_STYLE,
    .print = LV_CB_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_CB_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_BAR_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_BAR_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_BAR_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_INDIC), MP_ROM_PTR(MP_ROM_INT(LV_BAR_STYLE_INDIC)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_BAR_STYLE_locals_dict, LV_BAR_STYLE_locals_dict_table);

STATIC void LV_BAR_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_BAR_STYLE");
}



STATIC const mp_obj_type_t mp_LV_BAR_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_BAR_STYLE,
    .print = LV_BAR_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_BAR_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_SLIDER_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_SLIDER_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_SLIDER_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_INDIC), MP_ROM_PTR(MP_ROM_INT(LV_SLIDER_STYLE_INDIC)) },
    { MP_ROM_QSTR(MP_QSTR_KNOB), MP_ROM_PTR(MP_ROM_INT(LV_SLIDER_STYLE_KNOB)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_SLIDER_STYLE_locals_dict, LV_SLIDER_STYLE_locals_dict_table);

STATIC void LV_SLIDER_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_SLIDER_STYLE");
}



STATIC const mp_obj_type_t mp_LV_SLIDER_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_SLIDER_STYLE,
    .print = LV_SLIDER_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_SLIDER_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_BTNM_CTRL object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_BTNM_CTRL_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_HIDDEN), MP_ROM_PTR(MP_ROM_INT(LV_BTNM_CTRL_HIDDEN)) },
    { MP_ROM_QSTR(MP_QSTR_NO_REPEAT), MP_ROM_PTR(MP_ROM_INT(LV_BTNM_CTRL_NO_REPEAT)) },
    { MP_ROM_QSTR(MP_QSTR_INACTIVE), MP_ROM_PTR(MP_ROM_INT(LV_BTNM_CTRL_INACTIVE)) },
    { MP_ROM_QSTR(MP_QSTR_TGL_ENABLE), MP_ROM_PTR(MP_ROM_INT(LV_BTNM_CTRL_TGL_ENABLE)) },
    { MP_ROM_QSTR(MP_QSTR_TGL_STATE), MP_ROM_PTR(MP_ROM_INT(LV_BTNM_CTRL_TGL_STATE)) },
    { MP_ROM_QSTR(MP_QSTR_CLICK_TRIG), MP_ROM_PTR(MP_ROM_INT(LV_BTNM_CTRL_CLICK_TRIG)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_BTNM_CTRL_locals_dict, LV_BTNM_CTRL_locals_dict_table);

STATIC void LV_BTNM_CTRL_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_BTNM_CTRL");
}



STATIC const mp_obj_type_t mp_LV_BTNM_CTRL_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_BTNM_CTRL,
    .print = LV_BTNM_CTRL_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_BTNM_CTRL_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_BTNM_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_BTNM_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_BTNM_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_REL), MP_ROM_PTR(MP_ROM_INT(LV_BTNM_STYLE_BTN_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_PR), MP_ROM_PTR(MP_ROM_INT(LV_BTNM_STYLE_BTN_PR)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_TGL_REL), MP_ROM_PTR(MP_ROM_INT(LV_BTNM_STYLE_BTN_TGL_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_TGL_PR), MP_ROM_PTR(MP_ROM_INT(LV_BTNM_STYLE_BTN_TGL_PR)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_INA), MP_ROM_PTR(MP_ROM_INT(LV_BTNM_STYLE_BTN_INA)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_BTNM_STYLE_locals_dict, LV_BTNM_STYLE_locals_dict_table);

STATIC void LV_BTNM_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_BTNM_STYLE");
}



STATIC const mp_obj_type_t mp_LV_BTNM_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_BTNM_STYLE,
    .print = LV_BTNM_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_BTNM_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_KB_MODE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_KB_MODE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_TEXT), MP_ROM_PTR(MP_ROM_INT(LV_KB_MODE_TEXT)) },
    { MP_ROM_QSTR(MP_QSTR_NUM), MP_ROM_PTR(MP_ROM_INT(LV_KB_MODE_NUM)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_KB_MODE_locals_dict, LV_KB_MODE_locals_dict_table);

STATIC void LV_KB_MODE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_KB_MODE");
}



STATIC const mp_obj_type_t mp_LV_KB_MODE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_KB_MODE,
    .print = LV_KB_MODE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_KB_MODE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_KB_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_KB_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_KB_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_REL), MP_ROM_PTR(MP_ROM_INT(LV_KB_STYLE_BTN_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_PR), MP_ROM_PTR(MP_ROM_INT(LV_KB_STYLE_BTN_PR)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_TGL_REL), MP_ROM_PTR(MP_ROM_INT(LV_KB_STYLE_BTN_TGL_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_TGL_PR), MP_ROM_PTR(MP_ROM_INT(LV_KB_STYLE_BTN_TGL_PR)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_INA), MP_ROM_PTR(MP_ROM_INT(LV_KB_STYLE_BTN_INA)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_KB_STYLE_locals_dict, LV_KB_STYLE_locals_dict_table);

STATIC void LV_KB_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_KB_STYLE");
}



STATIC const mp_obj_type_t mp_LV_KB_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_KB_STYLE,
    .print = LV_KB_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_KB_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_DDLIST_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_DDLIST_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_DDLIST_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_SEL), MP_ROM_PTR(MP_ROM_INT(LV_DDLIST_STYLE_SEL)) },
    { MP_ROM_QSTR(MP_QSTR_SB), MP_ROM_PTR(MP_ROM_INT(LV_DDLIST_STYLE_SB)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_DDLIST_STYLE_locals_dict, LV_DDLIST_STYLE_locals_dict_table);

STATIC void LV_DDLIST_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_DDLIST_STYLE");
}



STATIC const mp_obj_type_t mp_LV_DDLIST_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_DDLIST_STYLE,
    .print = LV_DDLIST_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_DDLIST_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_ROLLER_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_ROLLER_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_ROLLER_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_SEL), MP_ROM_PTR(MP_ROM_INT(LV_ROLLER_STYLE_SEL)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_ROLLER_STYLE_locals_dict, LV_ROLLER_STYLE_locals_dict_table);

STATIC void LV_ROLLER_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_ROLLER_STYLE");
}



STATIC const mp_obj_type_t mp_LV_ROLLER_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_ROLLER_STYLE,
    .print = LV_ROLLER_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_ROLLER_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_CURSOR object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_CURSOR_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_NONE), MP_ROM_PTR(MP_ROM_INT(LV_CURSOR_NONE)) },
    { MP_ROM_QSTR(MP_QSTR_LINE), MP_ROM_PTR(MP_ROM_INT(LV_CURSOR_LINE)) },
    { MP_ROM_QSTR(MP_QSTR_BLOCK), MP_ROM_PTR(MP_ROM_INT(LV_CURSOR_BLOCK)) },
    { MP_ROM_QSTR(MP_QSTR_OUTLINE), MP_ROM_PTR(MP_ROM_INT(LV_CURSOR_OUTLINE)) },
    { MP_ROM_QSTR(MP_QSTR_UNDERLINE), MP_ROM_PTR(MP_ROM_INT(LV_CURSOR_UNDERLINE)) },
    { MP_ROM_QSTR(MP_QSTR_HIDDEN), MP_ROM_PTR(MP_ROM_INT(LV_CURSOR_HIDDEN)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_CURSOR_locals_dict, LV_CURSOR_locals_dict_table);

STATIC void LV_CURSOR_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_CURSOR");
}



STATIC const mp_obj_type_t mp_LV_CURSOR_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_CURSOR,
    .print = LV_CURSOR_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_CURSOR_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_TA_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_TA_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_TA_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_SB), MP_ROM_PTR(MP_ROM_INT(LV_TA_STYLE_SB)) },
    { MP_ROM_QSTR(MP_QSTR_EDGE_FLASH), MP_ROM_PTR(MP_ROM_INT(LV_TA_STYLE_EDGE_FLASH)) },
    { MP_ROM_QSTR(MP_QSTR_CURSOR), MP_ROM_PTR(MP_ROM_INT(LV_TA_STYLE_CURSOR)) },
    { MP_ROM_QSTR(MP_QSTR_PLACEHOLDER), MP_ROM_PTR(MP_ROM_INT(LV_TA_STYLE_PLACEHOLDER)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_TA_STYLE_locals_dict, LV_TA_STYLE_locals_dict_table);

STATIC void LV_TA_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_TA_STYLE");
}



STATIC const mp_obj_type_t mp_LV_TA_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_TA_STYLE,
    .print = LV_TA_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_TA_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_CANVAS_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_CANVAS_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_MAIN), MP_ROM_PTR(MP_ROM_INT(LV_CANVAS_STYLE_MAIN)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_CANVAS_STYLE_locals_dict, LV_CANVAS_STYLE_locals_dict_table);

STATIC void LV_CANVAS_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_CANVAS_STYLE");
}



STATIC const mp_obj_type_t mp_LV_CANVAS_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_CANVAS_STYLE,
    .print = LV_CANVAS_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_CANVAS_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_WIN_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_WIN_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_WIN_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_CONTENT_BG), MP_ROM_PTR(MP_ROM_INT(LV_WIN_STYLE_CONTENT_BG)) },
    { MP_ROM_QSTR(MP_QSTR_CONTENT_SCRL), MP_ROM_PTR(MP_ROM_INT(LV_WIN_STYLE_CONTENT_SCRL)) },
    { MP_ROM_QSTR(MP_QSTR_SB), MP_ROM_PTR(MP_ROM_INT(LV_WIN_STYLE_SB)) },
    { MP_ROM_QSTR(MP_QSTR_HEADER), MP_ROM_PTR(MP_ROM_INT(LV_WIN_STYLE_HEADER)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_REL), MP_ROM_PTR(MP_ROM_INT(LV_WIN_STYLE_BTN_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_PR), MP_ROM_PTR(MP_ROM_INT(LV_WIN_STYLE_BTN_PR)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_WIN_STYLE_locals_dict, LV_WIN_STYLE_locals_dict_table);

STATIC void LV_WIN_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_WIN_STYLE");
}



STATIC const mp_obj_type_t mp_LV_WIN_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_WIN_STYLE,
    .print = LV_WIN_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_WIN_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_TABVIEW_BTNS_POS object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_TABVIEW_BTNS_POS_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_TOP), MP_ROM_PTR(MP_ROM_INT(LV_TABVIEW_BTNS_POS_TOP)) },
    { MP_ROM_QSTR(MP_QSTR_BOTTOM), MP_ROM_PTR(MP_ROM_INT(LV_TABVIEW_BTNS_POS_BOTTOM)) },
    { MP_ROM_QSTR(MP_QSTR_LEFT), MP_ROM_PTR(MP_ROM_INT(LV_TABVIEW_BTNS_POS_LEFT)) },
    { MP_ROM_QSTR(MP_QSTR_RIGHT), MP_ROM_PTR(MP_ROM_INT(LV_TABVIEW_BTNS_POS_RIGHT)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_TABVIEW_BTNS_POS_locals_dict, LV_TABVIEW_BTNS_POS_locals_dict_table);

STATIC void LV_TABVIEW_BTNS_POS_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_TABVIEW_BTNS_POS");
}



STATIC const mp_obj_type_t mp_LV_TABVIEW_BTNS_POS_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_TABVIEW_BTNS_POS,
    .print = LV_TABVIEW_BTNS_POS_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_TABVIEW_BTNS_POS_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_TABVIEW_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_TABVIEW_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_TABVIEW_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_INDIC), MP_ROM_PTR(MP_ROM_INT(LV_TABVIEW_STYLE_INDIC)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_BG), MP_ROM_PTR(MP_ROM_INT(LV_TABVIEW_STYLE_BTN_BG)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_REL), MP_ROM_PTR(MP_ROM_INT(LV_TABVIEW_STYLE_BTN_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_PR), MP_ROM_PTR(MP_ROM_INT(LV_TABVIEW_STYLE_BTN_PR)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_TGL_REL), MP_ROM_PTR(MP_ROM_INT(LV_TABVIEW_STYLE_BTN_TGL_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_TGL_PR), MP_ROM_PTR(MP_ROM_INT(LV_TABVIEW_STYLE_BTN_TGL_PR)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_TABVIEW_STYLE_locals_dict, LV_TABVIEW_STYLE_locals_dict_table);

STATIC void LV_TABVIEW_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_TABVIEW_STYLE");
}



STATIC const mp_obj_type_t mp_LV_TABVIEW_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_TABVIEW_STYLE,
    .print = LV_TABVIEW_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_TABVIEW_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_TILEVIEW_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_TILEVIEW_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_TILEVIEW_STYLE_BG)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_TILEVIEW_STYLE_locals_dict, LV_TILEVIEW_STYLE_locals_dict_table);

STATIC void LV_TILEVIEW_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_TILEVIEW_STYLE");
}



STATIC const mp_obj_type_t mp_LV_TILEVIEW_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_TILEVIEW_STYLE,
    .print = LV_TILEVIEW_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_TILEVIEW_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_MBOX_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_MBOX_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_MBOX_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_BG), MP_ROM_PTR(MP_ROM_INT(LV_MBOX_STYLE_BTN_BG)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_REL), MP_ROM_PTR(MP_ROM_INT(LV_MBOX_STYLE_BTN_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_PR), MP_ROM_PTR(MP_ROM_INT(LV_MBOX_STYLE_BTN_PR)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_TGL_REL), MP_ROM_PTR(MP_ROM_INT(LV_MBOX_STYLE_BTN_TGL_REL)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_TGL_PR), MP_ROM_PTR(MP_ROM_INT(LV_MBOX_STYLE_BTN_TGL_PR)) },
    { MP_ROM_QSTR(MP_QSTR_BTN_INA), MP_ROM_PTR(MP_ROM_INT(LV_MBOX_STYLE_BTN_INA)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_MBOX_STYLE_locals_dict, LV_MBOX_STYLE_locals_dict_table);

STATIC void LV_MBOX_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_MBOX_STYLE");
}



STATIC const mp_obj_type_t mp_LV_MBOX_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_MBOX_STYLE,
    .print = LV_MBOX_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_MBOX_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_SW_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_SW_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_SW_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_INDIC), MP_ROM_PTR(MP_ROM_INT(LV_SW_STYLE_INDIC)) },
    { MP_ROM_QSTR(MP_QSTR_KNOB_OFF), MP_ROM_PTR(MP_ROM_INT(LV_SW_STYLE_KNOB_OFF)) },
    { MP_ROM_QSTR(MP_QSTR_KNOB_ON), MP_ROM_PTR(MP_ROM_INT(LV_SW_STYLE_KNOB_ON)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_SW_STYLE_locals_dict, LV_SW_STYLE_locals_dict_table);

STATIC void LV_SW_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_SW_STYLE");
}



STATIC const mp_obj_type_t mp_LV_SW_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_SW_STYLE,
    .print = LV_SW_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_SW_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_ARC_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_ARC_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_MAIN), MP_ROM_PTR(MP_ROM_INT(LV_ARC_STYLE_MAIN)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_ARC_STYLE_locals_dict, LV_ARC_STYLE_locals_dict_table);

STATIC void LV_ARC_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_ARC_STYLE");
}



STATIC const mp_obj_type_t mp_LV_ARC_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_ARC_STYLE,
    .print = LV_ARC_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_ARC_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_PRELOAD_TYPE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_PRELOAD_TYPE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SPINNING_ARC), MP_ROM_PTR(MP_ROM_INT(LV_PRELOAD_TYPE_SPINNING_ARC)) },
    { MP_ROM_QSTR(MP_QSTR_FILLSPIN_ARC), MP_ROM_PTR(MP_ROM_INT(LV_PRELOAD_TYPE_FILLSPIN_ARC)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_PRELOAD_TYPE_locals_dict, LV_PRELOAD_TYPE_locals_dict_table);

STATIC void LV_PRELOAD_TYPE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_PRELOAD_TYPE");
}



STATIC const mp_obj_type_t mp_LV_PRELOAD_TYPE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_PRELOAD_TYPE,
    .print = LV_PRELOAD_TYPE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_PRELOAD_TYPE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_PRELOAD_DIR object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_PRELOAD_DIR_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_FORWARD), MP_ROM_PTR(MP_ROM_INT(LV_PRELOAD_DIR_FORWARD)) },
    { MP_ROM_QSTR(MP_QSTR_BACKWARD), MP_ROM_PTR(MP_ROM_INT(LV_PRELOAD_DIR_BACKWARD)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_PRELOAD_DIR_locals_dict, LV_PRELOAD_DIR_locals_dict_table);

STATIC void LV_PRELOAD_DIR_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_PRELOAD_DIR");
}



STATIC const mp_obj_type_t mp_LV_PRELOAD_DIR_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_PRELOAD_DIR,
    .print = LV_PRELOAD_DIR_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_PRELOAD_DIR_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_PRELOAD_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_PRELOAD_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_MAIN), MP_ROM_PTR(MP_ROM_INT(LV_PRELOAD_STYLE_MAIN)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_PRELOAD_STYLE_locals_dict, LV_PRELOAD_STYLE_locals_dict_table);

STATIC void LV_PRELOAD_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_PRELOAD_STYLE");
}



STATIC const mp_obj_type_t mp_LV_PRELOAD_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_PRELOAD_STYLE,
    .print = LV_PRELOAD_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_PRELOAD_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_CALENDAR_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_CALENDAR_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_CALENDAR_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_HEADER), MP_ROM_PTR(MP_ROM_INT(LV_CALENDAR_STYLE_HEADER)) },
    { MP_ROM_QSTR(MP_QSTR_HEADER_PR), MP_ROM_PTR(MP_ROM_INT(LV_CALENDAR_STYLE_HEADER_PR)) },
    { MP_ROM_QSTR(MP_QSTR_DAY_NAMES), MP_ROM_PTR(MP_ROM_INT(LV_CALENDAR_STYLE_DAY_NAMES)) },
    { MP_ROM_QSTR(MP_QSTR_HIGHLIGHTED_DAYS), MP_ROM_PTR(MP_ROM_INT(LV_CALENDAR_STYLE_HIGHLIGHTED_DAYS)) },
    { MP_ROM_QSTR(MP_QSTR_INACTIVE_DAYS), MP_ROM_PTR(MP_ROM_INT(LV_CALENDAR_STYLE_INACTIVE_DAYS)) },
    { MP_ROM_QSTR(MP_QSTR_WEEK_BOX), MP_ROM_PTR(MP_ROM_INT(LV_CALENDAR_STYLE_WEEK_BOX)) },
    { MP_ROM_QSTR(MP_QSTR_TODAY_BOX), MP_ROM_PTR(MP_ROM_INT(LV_CALENDAR_STYLE_TODAY_BOX)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_CALENDAR_STYLE_locals_dict, LV_CALENDAR_STYLE_locals_dict_table);

STATIC void LV_CALENDAR_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_CALENDAR_STYLE");
}



STATIC const mp_obj_type_t mp_LV_CALENDAR_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_CALENDAR_STYLE,
    .print = LV_CALENDAR_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_CALENDAR_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_SPINBOX_STYLE object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_SPINBOX_STYLE_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_BG), MP_ROM_PTR(MP_ROM_INT(LV_SPINBOX_STYLE_BG)) },
    { MP_ROM_QSTR(MP_QSTR_SB), MP_ROM_PTR(MP_ROM_INT(LV_SPINBOX_STYLE_SB)) },
    { MP_ROM_QSTR(MP_QSTR_CURSOR), MP_ROM_PTR(MP_ROM_INT(LV_SPINBOX_STYLE_CURSOR)) }
};

STATIC MP_DEFINE_CONST_DICT(LV_SPINBOX_STYLE_locals_dict, LV_SPINBOX_STYLE_locals_dict_table);

STATIC void LV_SPINBOX_STYLE_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_SPINBOX_STYLE");
}



STATIC const mp_obj_type_t mp_LV_SPINBOX_STYLE_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_SPINBOX_STYLE,
    .print = LV_SPINBOX_STYLE_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_SPINBOX_STYLE_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl LV_SYMBOL object definitions
 */
    

STATIC const mp_rom_map_elem_t LV_SYMBOL_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_AUDIO), MP_ROM_PTR(&mp_LV_SYMBOL_AUDIO) },
    { MP_ROM_QSTR(MP_QSTR_VIDEO), MP_ROM_PTR(&mp_LV_SYMBOL_VIDEO) },
    { MP_ROM_QSTR(MP_QSTR_LIST), MP_ROM_PTR(&mp_LV_SYMBOL_LIST) },
    { MP_ROM_QSTR(MP_QSTR_OK), MP_ROM_PTR(&mp_LV_SYMBOL_OK) },
    { MP_ROM_QSTR(MP_QSTR_CLOSE), MP_ROM_PTR(&mp_LV_SYMBOL_CLOSE) },
    { MP_ROM_QSTR(MP_QSTR_POWER), MP_ROM_PTR(&mp_LV_SYMBOL_POWER) },
    { MP_ROM_QSTR(MP_QSTR_SETTINGS), MP_ROM_PTR(&mp_LV_SYMBOL_SETTINGS) },
    { MP_ROM_QSTR(MP_QSTR_TRASH), MP_ROM_PTR(&mp_LV_SYMBOL_TRASH) },
    { MP_ROM_QSTR(MP_QSTR_HOME), MP_ROM_PTR(&mp_LV_SYMBOL_HOME) },
    { MP_ROM_QSTR(MP_QSTR_DOWNLOAD), MP_ROM_PTR(&mp_LV_SYMBOL_DOWNLOAD) },
    { MP_ROM_QSTR(MP_QSTR_DRIVE), MP_ROM_PTR(&mp_LV_SYMBOL_DRIVE) },
    { MP_ROM_QSTR(MP_QSTR_REFRESH), MP_ROM_PTR(&mp_LV_SYMBOL_REFRESH) },
    { MP_ROM_QSTR(MP_QSTR_MUTE), MP_ROM_PTR(&mp_LV_SYMBOL_MUTE) },
    { MP_ROM_QSTR(MP_QSTR_VOLUME_MID), MP_ROM_PTR(&mp_LV_SYMBOL_VOLUME_MID) },
    { MP_ROM_QSTR(MP_QSTR_VOLUME_MAX), MP_ROM_PTR(&mp_LV_SYMBOL_VOLUME_MAX) },
    { MP_ROM_QSTR(MP_QSTR_IMAGE), MP_ROM_PTR(&mp_LV_SYMBOL_IMAGE) },
    { MP_ROM_QSTR(MP_QSTR_EDIT), MP_ROM_PTR(&mp_LV_SYMBOL_EDIT) },
    { MP_ROM_QSTR(MP_QSTR_PREV), MP_ROM_PTR(&mp_LV_SYMBOL_PREV) },
    { MP_ROM_QSTR(MP_QSTR_PLAY), MP_ROM_PTR(&mp_LV_SYMBOL_PLAY) },
    { MP_ROM_QSTR(MP_QSTR_PAUSE), MP_ROM_PTR(&mp_LV_SYMBOL_PAUSE) },
    { MP_ROM_QSTR(MP_QSTR_STOP), MP_ROM_PTR(&mp_LV_SYMBOL_STOP) },
    { MP_ROM_QSTR(MP_QSTR_NEXT), MP_ROM_PTR(&mp_LV_SYMBOL_NEXT) },
    { MP_ROM_QSTR(MP_QSTR_EJECT), MP_ROM_PTR(&mp_LV_SYMBOL_EJECT) },
    { MP_ROM_QSTR(MP_QSTR_LEFT), MP_ROM_PTR(&mp_LV_SYMBOL_LEFT) },
    { MP_ROM_QSTR(MP_QSTR_RIGHT), MP_ROM_PTR(&mp_LV_SYMBOL_RIGHT) },
    { MP_ROM_QSTR(MP_QSTR_PLUS), MP_ROM_PTR(&mp_LV_SYMBOL_PLUS) },
    { MP_ROM_QSTR(MP_QSTR_MINUS), MP_ROM_PTR(&mp_LV_SYMBOL_MINUS) },
    { MP_ROM_QSTR(MP_QSTR_WARNING), MP_ROM_PTR(&mp_LV_SYMBOL_WARNING) },
    { MP_ROM_QSTR(MP_QSTR_SHUFFLE), MP_ROM_PTR(&mp_LV_SYMBOL_SHUFFLE) },
    { MP_ROM_QSTR(MP_QSTR_UP), MP_ROM_PTR(&mp_LV_SYMBOL_UP) },
    { MP_ROM_QSTR(MP_QSTR_DOWN), MP_ROM_PTR(&mp_LV_SYMBOL_DOWN) },
    { MP_ROM_QSTR(MP_QSTR_LOOP), MP_ROM_PTR(&mp_LV_SYMBOL_LOOP) },
    { MP_ROM_QSTR(MP_QSTR_DIRECTORY), MP_ROM_PTR(&mp_LV_SYMBOL_DIRECTORY) },
    { MP_ROM_QSTR(MP_QSTR_UPLOAD), MP_ROM_PTR(&mp_LV_SYMBOL_UPLOAD) },
    { MP_ROM_QSTR(MP_QSTR_CALL), MP_ROM_PTR(&mp_LV_SYMBOL_CALL) },
    { MP_ROM_QSTR(MP_QSTR_CUT), MP_ROM_PTR(&mp_LV_SYMBOL_CUT) },
    { MP_ROM_QSTR(MP_QSTR_COPY), MP_ROM_PTR(&mp_LV_SYMBOL_COPY) },
    { MP_ROM_QSTR(MP_QSTR_SAVE), MP_ROM_PTR(&mp_LV_SYMBOL_SAVE) },
    { MP_ROM_QSTR(MP_QSTR_CHARGE), MP_ROM_PTR(&mp_LV_SYMBOL_CHARGE) },
    { MP_ROM_QSTR(MP_QSTR_BELL), MP_ROM_PTR(&mp_LV_SYMBOL_BELL) },
    { MP_ROM_QSTR(MP_QSTR_KEYBOARD), MP_ROM_PTR(&mp_LV_SYMBOL_KEYBOARD) },
    { MP_ROM_QSTR(MP_QSTR_GPS), MP_ROM_PTR(&mp_LV_SYMBOL_GPS) },
    { MP_ROM_QSTR(MP_QSTR_FILE), MP_ROM_PTR(&mp_LV_SYMBOL_FILE) },
    { MP_ROM_QSTR(MP_QSTR_WIFI), MP_ROM_PTR(&mp_LV_SYMBOL_WIFI) },
    { MP_ROM_QSTR(MP_QSTR_BATTERY_FULL), MP_ROM_PTR(&mp_LV_SYMBOL_BATTERY_FULL) },
    { MP_ROM_QSTR(MP_QSTR_BATTERY_3), MP_ROM_PTR(&mp_LV_SYMBOL_BATTERY_3) },
    { MP_ROM_QSTR(MP_QSTR_BATTERY_2), MP_ROM_PTR(&mp_LV_SYMBOL_BATTERY_2) },
    { MP_ROM_QSTR(MP_QSTR_BATTERY_1), MP_ROM_PTR(&mp_LV_SYMBOL_BATTERY_1) },
    { MP_ROM_QSTR(MP_QSTR_BATTERY_EMPTY), MP_ROM_PTR(&mp_LV_SYMBOL_BATTERY_EMPTY) },
    { MP_ROM_QSTR(MP_QSTR_BLUETOOTH), MP_ROM_PTR(&mp_LV_SYMBOL_BLUETOOTH) },
    { MP_ROM_QSTR(MP_QSTR_DUMMY), MP_ROM_PTR(&mp_LV_SYMBOL_DUMMY) }
};

STATIC MP_DEFINE_CONST_DICT(LV_SYMBOL_locals_dict, LV_SYMBOL_locals_dict_table);

STATIC void LV_SYMBOL_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl LV_SYMBOL");
}



STATIC const mp_obj_type_t mp_LV_SYMBOL_type = {
    { &mp_type_type },
    .name = MP_QSTR_LV_SYMBOL,
    .print = LV_SYMBOL_print,
    
    .locals_dict = (mp_obj_dict_t*)&LV_SYMBOL_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * lv_res_t lv_obj_del(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_del(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_res_t res = lv_obj_del(obj);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_del_obj, 1, 1, mp_lv_obj_del);

 

/*
 * lvgl extension definition for:
 * void lv_obj_clean(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_clean(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_clean(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_clean_obj, 1, 1, mp_lv_obj_clean);

 

/*
 * lvgl extension definition for:
 * void lv_obj_invalidate(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_invalidate(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_invalidate(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_invalidate_obj, 1, 1, mp_lv_obj_invalidate);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_parent(lv_obj_t *obj, lv_obj_t *parent)
 */
 
STATIC mp_obj_t mp_lv_obj_set_parent(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_t *parent = mp_to_lv(args[1]);
    lv_obj_set_parent(obj, parent);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_parent_obj, 2, 2, mp_lv_obj_set_parent);

 

/*
 * lvgl extension definition for:
 * void lv_obj_move_foreground(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_move_foreground(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_move_foreground(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_move_foreground_obj, 1, 1, mp_lv_obj_move_foreground);

 

/*
 * lvgl extension definition for:
 * void lv_obj_move_background(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_move_background(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_move_background(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_move_background_obj, 1, 1, mp_lv_obj_move_background);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_pos(lv_obj_t *obj, lv_coord_t x, lv_coord_t y)
 */
 
STATIC mp_obj_t mp_lv_obj_set_pos(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    lv_obj_set_pos(obj, x, y);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_pos_obj, 3, 3, mp_lv_obj_set_pos);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_x(lv_obj_t *obj, lv_coord_t x)
 */
 
STATIC mp_obj_t mp_lv_obj_set_x(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_obj_set_x(obj, x);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_x_obj, 2, 2, mp_lv_obj_set_x);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_y(lv_obj_t *obj, lv_coord_t y)
 */
 
STATIC mp_obj_t mp_lv_obj_set_y(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[1]);
    lv_obj_set_y(obj, y);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_y_obj, 2, 2, mp_lv_obj_set_y);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_size(lv_obj_t *obj, lv_coord_t w, lv_coord_t h)
 */
 
STATIC mp_obj_t mp_lv_obj_set_size(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t w = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t h = (int16_t)mp_obj_get_int(args[2]);
    lv_obj_set_size(obj, w, h);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_size_obj, 3, 3, mp_lv_obj_set_size);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_width(lv_obj_t *obj, lv_coord_t w)
 */
 
STATIC mp_obj_t mp_lv_obj_set_width(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t w = (int16_t)mp_obj_get_int(args[1]);
    lv_obj_set_width(obj, w);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_width_obj, 2, 2, mp_lv_obj_set_width);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_height(lv_obj_t *obj, lv_coord_t h)
 */
 
STATIC mp_obj_t mp_lv_obj_set_height(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t h = (int16_t)mp_obj_get_int(args[1]);
    lv_obj_set_height(obj, h);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_height_obj, 2, 2, mp_lv_obj_set_height);

 

/*
 * lvgl extension definition for:
 * void lv_obj_align(lv_obj_t *obj, const lv_obj_t *base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod)
 */
 
STATIC mp_obj_t mp_lv_obj_align(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    const lv_obj_t *base = mp_to_lv(args[1]);
    lv_align_t align = (uint8_t)mp_obj_get_int(args[2]);
    lv_coord_t x_mod = (int16_t)mp_obj_get_int(args[3]);
    lv_coord_t y_mod = (int16_t)mp_obj_get_int(args[4]);
    lv_obj_align(obj, base, align, x_mod, y_mod);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_align_obj, 5, 5, mp_lv_obj_align);

 

/*
 * lvgl extension definition for:
 * void lv_obj_align_origo(lv_obj_t *obj, const lv_obj_t *base, lv_align_t align, lv_coord_t x_mod, lv_coord_t y_mod)
 */
 
STATIC mp_obj_t mp_lv_obj_align_origo(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    const lv_obj_t *base = mp_to_lv(args[1]);
    lv_align_t align = (uint8_t)mp_obj_get_int(args[2]);
    lv_coord_t x_mod = (int16_t)mp_obj_get_int(args[3]);
    lv_coord_t y_mod = (int16_t)mp_obj_get_int(args[4]);
    lv_obj_align_origo(obj, base, align, x_mod, y_mod);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_align_origo_obj, 5, 5, mp_lv_obj_align_origo);

 

/*
 * lvgl extension definition for:
 * void lv_obj_realign(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_realign(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_realign(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_realign_obj, 1, 1, mp_lv_obj_realign);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_auto_realign(lv_obj_t *obj, bool en)
 */
 
STATIC mp_obj_t mp_lv_obj_set_auto_realign(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_obj_set_auto_realign(obj, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_auto_realign_obj, 2, 2, mp_lv_obj_set_auto_realign);

 
typedef typeof( ((lv_style_t*)(0))->body ) lv_style_body_t;
typedef typeof( ((lv_color32_t*)(0))->ch ) lv_color32_ch_t;

/*
 * Struct lv_color32_ch_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_color32_ch_t_type();

STATIC inline lv_color32_ch_t* mp_write_ptr_lv_color32_ch_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_color32_ch_t_type()));
    return (lv_color32_ch_t*)self->data;
}

#define mp_write_lv_color32_ch_t(struct_obj) *mp_write_ptr_lv_color32_ch_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_color32_ch_t(lv_color32_ch_t *field)
{
    return lv_to_mp_struct(get_mp_lv_color32_ch_t_type(), field);
}

#define mp_read_lv_color32_ch_t(field) mp_read_ptr_lv_color32_ch_t(copy_buffer(&field, sizeof(lv_color32_ch_t)))
#define mp_read_byref_lv_color32_ch_t(field) mp_read_ptr_lv_color32_ch_t(&field)

STATIC void mp_lv_color32_ch_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_color32_ch_t *data = (lv_color32_ch_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_blue: dest[0] = mp_obj_new_int_from_uint(data->blue); break; // converting from uint8_t;
            case MP_QSTR_green: dest[0] = mp_obj_new_int_from_uint(data->green); break; // converting from uint8_t;
            case MP_QSTR_red: dest[0] = mp_obj_new_int_from_uint(data->red); break; // converting from uint8_t;
            case MP_QSTR_alpha: dest[0] = mp_obj_new_int_from_uint(data->alpha); break; // converting from uint8_t;
            default: field_not_found(MP_QSTR_lv_color32_ch_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_blue: data->blue = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_green: data->green = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_red: data->red = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_alpha: data->alpha = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                default: field_not_found(MP_QSTR_lv_color32_ch_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_color32_ch_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_color32_ch_t");
}

STATIC const mp_rom_map_elem_t mp_lv_color32_ch_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_color32_ch_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_color32_ch_t_locals_dict, mp_lv_color32_ch_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_color32_ch_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_color32_ch_t,
    .print = mp_lv_color32_ch_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_color32_ch_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_color32_ch_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_color32_ch_t_type()
{
    return &mp_lv_color32_ch_t_type;
}
    

/*
 * Struct lv_color32_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_color32_t_type();

STATIC inline lv_color32_t* mp_write_ptr_lv_color32_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_color32_t_type()));
    return (lv_color32_t*)self->data;
}

#define mp_write_lv_color32_t(struct_obj) *mp_write_ptr_lv_color32_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_color32_t(lv_color32_t *field)
{
    return lv_to_mp_struct(get_mp_lv_color32_t_type(), field);
}

#define mp_read_lv_color32_t(field) mp_read_ptr_lv_color32_t(copy_buffer(&field, sizeof(lv_color32_t)))
#define mp_read_byref_lv_color32_t(field) mp_read_ptr_lv_color32_t(&field)

STATIC void mp_lv_color32_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_color32_t *data = (lv_color32_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_ch: dest[0] = mp_read_byref_lv_color32_ch_t(data->ch); break; // converting from lv_color32_ch_t;
            case MP_QSTR_full: dest[0] = mp_obj_new_int_from_uint(data->full); break; // converting from uint32_t;
            default: field_not_found(MP_QSTR_lv_color32_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_ch: data->ch = mp_write_lv_color32_ch_t(dest[1]); break; // converting to lv_color32_ch_t;
                case MP_QSTR_full: data->full = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                default: field_not_found(MP_QSTR_lv_color32_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_color32_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_color32_t");
}

STATIC const mp_rom_map_elem_t mp_lv_color32_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_color32_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_color32_t_locals_dict, mp_lv_color32_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_color32_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_color32_t,
    .print = mp_lv_color32_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_color32_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_color32_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_color32_t_type()
{
    return &mp_lv_color32_t_type;
}
    
typedef typeof( ((lv_style_body_t*)(0))->border ) lv_style_body_border_t;

/*
 * Struct lv_style_body_border_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_style_body_border_t_type();

STATIC inline lv_style_body_border_t* mp_write_ptr_lv_style_body_border_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_style_body_border_t_type()));
    return (lv_style_body_border_t*)self->data;
}

#define mp_write_lv_style_body_border_t(struct_obj) *mp_write_ptr_lv_style_body_border_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_style_body_border_t(lv_style_body_border_t *field)
{
    return lv_to_mp_struct(get_mp_lv_style_body_border_t_type(), field);
}

#define mp_read_lv_style_body_border_t(field) mp_read_ptr_lv_style_body_border_t(copy_buffer(&field, sizeof(lv_style_body_border_t)))
#define mp_read_byref_lv_style_body_border_t(field) mp_read_ptr_lv_style_body_border_t(&field)

STATIC void mp_lv_style_body_border_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_style_body_border_t *data = (lv_style_body_border_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_color: dest[0] = mp_read_byref_lv_color32_t(data->color); break; // converting from lv_color_t;
            case MP_QSTR_width: dest[0] = mp_obj_new_int(data->width); break; // converting from lv_coord_t;
            case MP_QSTR_part: dest[0] = mp_obj_new_int_from_uint(data->part); break; // converting from lv_border_part_t;
            case MP_QSTR_opa: dest[0] = mp_obj_new_int_from_uint(data->opa); break; // converting from lv_opa_t;
            default: field_not_found(MP_QSTR_lv_style_body_border_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_color: data->color = mp_write_lv_color32_t(dest[1]); break; // converting to lv_color_t;
                case MP_QSTR_width: data->width = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_part: data->part = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to lv_border_part_t;
                case MP_QSTR_opa: data->opa = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to lv_opa_t;
                default: field_not_found(MP_QSTR_lv_style_body_border_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_style_body_border_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_style_body_border_t");
}

STATIC const mp_rom_map_elem_t mp_lv_style_body_border_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_style_body_border_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_style_body_border_t_locals_dict, mp_lv_style_body_border_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_style_body_border_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_style_body_border_t,
    .print = mp_lv_style_body_border_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_style_body_border_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_style_body_border_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_style_body_border_t_type()
{
    return &mp_lv_style_body_border_t_type;
}
    
typedef typeof( ((lv_style_body_t*)(0))->shadow ) lv_style_body_shadow_t;

/*
 * Struct lv_style_body_shadow_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_style_body_shadow_t_type();

STATIC inline lv_style_body_shadow_t* mp_write_ptr_lv_style_body_shadow_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_style_body_shadow_t_type()));
    return (lv_style_body_shadow_t*)self->data;
}

#define mp_write_lv_style_body_shadow_t(struct_obj) *mp_write_ptr_lv_style_body_shadow_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_style_body_shadow_t(lv_style_body_shadow_t *field)
{
    return lv_to_mp_struct(get_mp_lv_style_body_shadow_t_type(), field);
}

#define mp_read_lv_style_body_shadow_t(field) mp_read_ptr_lv_style_body_shadow_t(copy_buffer(&field, sizeof(lv_style_body_shadow_t)))
#define mp_read_byref_lv_style_body_shadow_t(field) mp_read_ptr_lv_style_body_shadow_t(&field)

STATIC void mp_lv_style_body_shadow_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_style_body_shadow_t *data = (lv_style_body_shadow_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_color: dest[0] = mp_read_byref_lv_color32_t(data->color); break; // converting from lv_color_t;
            case MP_QSTR_width: dest[0] = mp_obj_new_int(data->width); break; // converting from lv_coord_t;
            case MP_QSTR_type: dest[0] = mp_obj_new_int_from_uint(data->type); break; // converting from lv_shadow_type_t;
            default: field_not_found(MP_QSTR_lv_style_body_shadow_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_color: data->color = mp_write_lv_color32_t(dest[1]); break; // converting to lv_color_t;
                case MP_QSTR_width: data->width = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_type: data->type = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to lv_shadow_type_t;
                default: field_not_found(MP_QSTR_lv_style_body_shadow_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_style_body_shadow_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_style_body_shadow_t");
}

STATIC const mp_rom_map_elem_t mp_lv_style_body_shadow_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_style_body_shadow_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_style_body_shadow_t_locals_dict, mp_lv_style_body_shadow_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_style_body_shadow_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_style_body_shadow_t,
    .print = mp_lv_style_body_shadow_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_style_body_shadow_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_style_body_shadow_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_style_body_shadow_t_type()
{
    return &mp_lv_style_body_shadow_t_type;
}
    
typedef typeof( ((lv_style_body_t*)(0))->padding ) lv_style_body_padding_t;

/*
 * Struct lv_style_body_padding_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_style_body_padding_t_type();

STATIC inline lv_style_body_padding_t* mp_write_ptr_lv_style_body_padding_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_style_body_padding_t_type()));
    return (lv_style_body_padding_t*)self->data;
}

#define mp_write_lv_style_body_padding_t(struct_obj) *mp_write_ptr_lv_style_body_padding_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_style_body_padding_t(lv_style_body_padding_t *field)
{
    return lv_to_mp_struct(get_mp_lv_style_body_padding_t_type(), field);
}

#define mp_read_lv_style_body_padding_t(field) mp_read_ptr_lv_style_body_padding_t(copy_buffer(&field, sizeof(lv_style_body_padding_t)))
#define mp_read_byref_lv_style_body_padding_t(field) mp_read_ptr_lv_style_body_padding_t(&field)

STATIC void mp_lv_style_body_padding_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_style_body_padding_t *data = (lv_style_body_padding_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_top: dest[0] = mp_obj_new_int(data->top); break; // converting from lv_coord_t;
            case MP_QSTR_bottom: dest[0] = mp_obj_new_int(data->bottom); break; // converting from lv_coord_t;
            case MP_QSTR_left: dest[0] = mp_obj_new_int(data->left); break; // converting from lv_coord_t;
            case MP_QSTR_right: dest[0] = mp_obj_new_int(data->right); break; // converting from lv_coord_t;
            case MP_QSTR_inner: dest[0] = mp_obj_new_int(data->inner); break; // converting from lv_coord_t;
            default: field_not_found(MP_QSTR_lv_style_body_padding_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_top: data->top = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_bottom: data->bottom = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_left: data->left = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_right: data->right = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_inner: data->inner = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                default: field_not_found(MP_QSTR_lv_style_body_padding_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_style_body_padding_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_style_body_padding_t");
}

STATIC const mp_rom_map_elem_t mp_lv_style_body_padding_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_style_body_padding_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_style_body_padding_t_locals_dict, mp_lv_style_body_padding_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_style_body_padding_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_style_body_padding_t,
    .print = mp_lv_style_body_padding_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_style_body_padding_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_style_body_padding_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_style_body_padding_t_type()
{
    return &mp_lv_style_body_padding_t_type;
}
    

/*
 * Struct lv_style_body_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_style_body_t_type();

STATIC inline lv_style_body_t* mp_write_ptr_lv_style_body_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_style_body_t_type()));
    return (lv_style_body_t*)self->data;
}

#define mp_write_lv_style_body_t(struct_obj) *mp_write_ptr_lv_style_body_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_style_body_t(lv_style_body_t *field)
{
    return lv_to_mp_struct(get_mp_lv_style_body_t_type(), field);
}

#define mp_read_lv_style_body_t(field) mp_read_ptr_lv_style_body_t(copy_buffer(&field, sizeof(lv_style_body_t)))
#define mp_read_byref_lv_style_body_t(field) mp_read_ptr_lv_style_body_t(&field)

STATIC void mp_lv_style_body_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_style_body_t *data = (lv_style_body_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_main_color: dest[0] = mp_read_byref_lv_color32_t(data->main_color); break; // converting from lv_color_t;
            case MP_QSTR_grad_color: dest[0] = mp_read_byref_lv_color32_t(data->grad_color); break; // converting from lv_color_t;
            case MP_QSTR_radius: dest[0] = mp_obj_new_int(data->radius); break; // converting from lv_coord_t;
            case MP_QSTR_opa: dest[0] = mp_obj_new_int_from_uint(data->opa); break; // converting from lv_opa_t;
            case MP_QSTR_border: dest[0] = mp_read_byref_lv_style_body_border_t(data->border); break; // converting from lv_style_body_border_t;
            case MP_QSTR_shadow: dest[0] = mp_read_byref_lv_style_body_shadow_t(data->shadow); break; // converting from lv_style_body_shadow_t;
            case MP_QSTR_padding: dest[0] = mp_read_byref_lv_style_body_padding_t(data->padding); break; // converting from lv_style_body_padding_t;
            default: field_not_found(MP_QSTR_lv_style_body_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_main_color: data->main_color = mp_write_lv_color32_t(dest[1]); break; // converting to lv_color_t;
                case MP_QSTR_grad_color: data->grad_color = mp_write_lv_color32_t(dest[1]); break; // converting to lv_color_t;
                case MP_QSTR_radius: data->radius = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_opa: data->opa = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to lv_opa_t;
                case MP_QSTR_border: data->border = mp_write_lv_style_body_border_t(dest[1]); break; // converting to lv_style_body_border_t;
                case MP_QSTR_shadow: data->shadow = mp_write_lv_style_body_shadow_t(dest[1]); break; // converting to lv_style_body_shadow_t;
                case MP_QSTR_padding: data->padding = mp_write_lv_style_body_padding_t(dest[1]); break; // converting to lv_style_body_padding_t;
                default: field_not_found(MP_QSTR_lv_style_body_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_style_body_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_style_body_t");
}

STATIC const mp_rom_map_elem_t mp_lv_style_body_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_style_body_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_style_body_t_locals_dict, mp_lv_style_body_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_style_body_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_style_body_t,
    .print = mp_lv_style_body_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_style_body_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_style_body_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_style_body_t_type()
{
    return &mp_lv_style_body_t_type;
}
    
typedef typeof( ((lv_style_t*)(0))->text ) lv_style_text_t;

/*
 * Struct lv_font_glyph_dsc_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_font_glyph_dsc_t_type();

STATIC inline lv_font_glyph_dsc_t* mp_write_ptr_lv_font_glyph_dsc_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_font_glyph_dsc_t_type()));
    return (lv_font_glyph_dsc_t*)self->data;
}

#define mp_write_lv_font_glyph_dsc_t(struct_obj) *mp_write_ptr_lv_font_glyph_dsc_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_font_glyph_dsc_t(lv_font_glyph_dsc_t *field)
{
    return lv_to_mp_struct(get_mp_lv_font_glyph_dsc_t_type(), field);
}

#define mp_read_lv_font_glyph_dsc_t(field) mp_read_ptr_lv_font_glyph_dsc_t(copy_buffer(&field, sizeof(lv_font_glyph_dsc_t)))
#define mp_read_byref_lv_font_glyph_dsc_t(field) mp_read_ptr_lv_font_glyph_dsc_t(&field)

STATIC void mp_lv_font_glyph_dsc_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_font_glyph_dsc_t *data = (lv_font_glyph_dsc_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_w_px: dest[0] = mp_obj_new_int_from_uint(data->w_px); break; // converting from uint32_t;
            case MP_QSTR_glyph_index: dest[0] = mp_obj_new_int_from_uint(data->glyph_index); break; // converting from uint32_t;
            default: field_not_found(MP_QSTR_lv_font_glyph_dsc_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_w_px: data->w_px = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_glyph_index: data->glyph_index = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                default: field_not_found(MP_QSTR_lv_font_glyph_dsc_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_font_glyph_dsc_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_font_glyph_dsc_t");
}

STATIC const mp_rom_map_elem_t mp_lv_font_glyph_dsc_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_font_glyph_dsc_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_font_glyph_dsc_t_locals_dict, mp_lv_font_glyph_dsc_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_font_glyph_dsc_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_font_glyph_dsc_t,
    .print = mp_lv_font_glyph_dsc_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_font_glyph_dsc_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_font_glyph_dsc_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_font_glyph_dsc_t_type()
{
    return &mp_lv_font_glyph_dsc_t_type;
}
    
STATIC const uint8_t * get_bitmap_callback(const struct _lv_font_struct *, uint32_t);
STATIC int16_t get_width_callback(const struct _lv_font_struct *, uint32_t);

/*
 * Struct lv_font_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_font_t_type();

STATIC inline lv_font_t* mp_write_ptr_lv_font_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_font_t_type()));
    return (lv_font_t*)self->data;
}

#define mp_write_lv_font_t(struct_obj) *mp_write_ptr_lv_font_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_font_t(lv_font_t *field)
{
    return lv_to_mp_struct(get_mp_lv_font_t_type(), field);
}

#define mp_read_lv_font_t(field) mp_read_ptr_lv_font_t(copy_buffer(&field, sizeof(lv_font_t)))
#define mp_read_byref_lv_font_t(field) mp_read_ptr_lv_font_t(&field)

STATIC void mp_lv_font_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_font_t *data = (lv_font_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_unicode_first: dest[0] = mp_obj_new_int_from_uint(data->unicode_first); break; // converting from uint32_t;
            case MP_QSTR_unicode_last: dest[0] = mp_obj_new_int_from_uint(data->unicode_last); break; // converting from uint32_t;
            case MP_QSTR_glyph_bitmap: dest[0] = ptr_to_mp((void*)data->glyph_bitmap); break; // converting from uint8_t *;
            case MP_QSTR_glyph_dsc: dest[0] = ptr_to_mp((void*)data->glyph_dsc); break; // converting from lv_font_glyph_dsc_t *;
            case MP_QSTR_unicode_list: dest[0] = ptr_to_mp((void*)data->unicode_list); break; // converting from uint32_t *;
            case MP_QSTR_get_bitmap: dest[0] = ptr_to_mp((void*)data->get_bitmap); break; // converting from uint8_t *(*)(lv_font_t *, uint32_t);
            case MP_QSTR_get_width: dest[0] = ptr_to_mp((void*)data->get_width); break; // converting from int16_t (*)(lv_font_t *, uint32_t);
            case MP_QSTR_next_page: dest[0] = ptr_to_mp((void*)data->next_page); break; // converting from lv_font_t *;
            case MP_QSTR_h_px: dest[0] = mp_obj_new_int_from_uint(data->h_px); break; // converting from uint32_t;
            case MP_QSTR_bpp: dest[0] = mp_obj_new_int_from_uint(data->bpp); break; // converting from uint32_t;
            case MP_QSTR_monospace: dest[0] = mp_obj_new_int_from_uint(data->monospace); break; // converting from uint32_t;
            case MP_QSTR_glyph_cnt: dest[0] = mp_obj_new_int_from_uint(data->glyph_cnt); break; // converting from uint16_t;
            default: field_not_found(MP_QSTR_lv_font_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_unicode_first: data->unicode_first = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_unicode_last: data->unicode_last = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_glyph_bitmap: data->glyph_bitmap = (void*)mp_to_ptr(dest[1]); break; // converting to uint8_t *;
                case MP_QSTR_glyph_dsc: data->glyph_dsc = (void*)mp_to_ptr(dest[1]); break; // converting to lv_font_glyph_dsc_t *;
                case MP_QSTR_unicode_list: data->unicode_list = (void*)mp_to_ptr(dest[1]); break; // converting to uint32_t *;
                case MP_QSTR_get_bitmap: data->get_bitmap = (void*)mp_lv_callback(dest[1], NULL ,MP_QSTR_get_bitmap, NULL); break; // converting to uint8_t *(*)(lv_font_t *, uint32_t);
                case MP_QSTR_get_width: data->get_width = (void*)mp_lv_callback(dest[1], NULL ,MP_QSTR_get_width, NULL); break; // converting to int16_t (*)(lv_font_t *, uint32_t);
                case MP_QSTR_next_page: data->next_page = (void*)mp_to_ptr(dest[1]); break; // converting to lv_font_t *;
                case MP_QSTR_h_px: data->h_px = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_bpp: data->bpp = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_monospace: data->monospace = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_glyph_cnt: data->glyph_cnt = (uint16_t)mp_obj_get_int(dest[1]); break; // converting to uint16_t;
                default: field_not_found(MP_QSTR_lv_font_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_font_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_font_t");
}

STATIC const mp_rom_map_elem_t mp_lv_font_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_font_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_font_t_locals_dict, mp_lv_font_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_font_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_font_t,
    .print = mp_lv_font_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_font_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_font_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_font_t_type()
{
    return &mp_lv_font_t_type;
}
    

/*
 * Struct lv_style_text_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_style_text_t_type();

STATIC inline lv_style_text_t* mp_write_ptr_lv_style_text_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_style_text_t_type()));
    return (lv_style_text_t*)self->data;
}

#define mp_write_lv_style_text_t(struct_obj) *mp_write_ptr_lv_style_text_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_style_text_t(lv_style_text_t *field)
{
    return lv_to_mp_struct(get_mp_lv_style_text_t_type(), field);
}

#define mp_read_lv_style_text_t(field) mp_read_ptr_lv_style_text_t(copy_buffer(&field, sizeof(lv_style_text_t)))
#define mp_read_byref_lv_style_text_t(field) mp_read_ptr_lv_style_text_t(&field)

STATIC void mp_lv_style_text_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_style_text_t *data = (lv_style_text_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_color: dest[0] = mp_read_byref_lv_color32_t(data->color); break; // converting from lv_color_t;
            case MP_QSTR_sel_color: dest[0] = mp_read_byref_lv_color32_t(data->sel_color); break; // converting from lv_color_t;
            case MP_QSTR_font: dest[0] = ptr_to_mp((void*)data->font); break; // converting from lv_font_t *;
            case MP_QSTR_letter_space: dest[0] = mp_obj_new_int(data->letter_space); break; // converting from lv_coord_t;
            case MP_QSTR_line_space: dest[0] = mp_obj_new_int(data->line_space); break; // converting from lv_coord_t;
            case MP_QSTR_opa: dest[0] = mp_obj_new_int_from_uint(data->opa); break; // converting from lv_opa_t;
            default: field_not_found(MP_QSTR_lv_style_text_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_color: data->color = mp_write_lv_color32_t(dest[1]); break; // converting to lv_color_t;
                case MP_QSTR_sel_color: data->sel_color = mp_write_lv_color32_t(dest[1]); break; // converting to lv_color_t;
                case MP_QSTR_font: data->font = (void*)mp_to_ptr(dest[1]); break; // converting to lv_font_t *;
                case MP_QSTR_letter_space: data->letter_space = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_line_space: data->line_space = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_opa: data->opa = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to lv_opa_t;
                default: field_not_found(MP_QSTR_lv_style_text_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_style_text_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_style_text_t");
}

STATIC const mp_rom_map_elem_t mp_lv_style_text_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_style_text_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_style_text_t_locals_dict, mp_lv_style_text_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_style_text_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_style_text_t,
    .print = mp_lv_style_text_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_style_text_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_style_text_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_style_text_t_type()
{
    return &mp_lv_style_text_t_type;
}
    
typedef typeof( ((lv_style_t*)(0))->image ) lv_style_image_t;

/*
 * Struct lv_style_image_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_style_image_t_type();

STATIC inline lv_style_image_t* mp_write_ptr_lv_style_image_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_style_image_t_type()));
    return (lv_style_image_t*)self->data;
}

#define mp_write_lv_style_image_t(struct_obj) *mp_write_ptr_lv_style_image_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_style_image_t(lv_style_image_t *field)
{
    return lv_to_mp_struct(get_mp_lv_style_image_t_type(), field);
}

#define mp_read_lv_style_image_t(field) mp_read_ptr_lv_style_image_t(copy_buffer(&field, sizeof(lv_style_image_t)))
#define mp_read_byref_lv_style_image_t(field) mp_read_ptr_lv_style_image_t(&field)

STATIC void mp_lv_style_image_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_style_image_t *data = (lv_style_image_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_color: dest[0] = mp_read_byref_lv_color32_t(data->color); break; // converting from lv_color_t;
            case MP_QSTR_intense: dest[0] = mp_obj_new_int_from_uint(data->intense); break; // converting from lv_opa_t;
            case MP_QSTR_opa: dest[0] = mp_obj_new_int_from_uint(data->opa); break; // converting from lv_opa_t;
            default: field_not_found(MP_QSTR_lv_style_image_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_color: data->color = mp_write_lv_color32_t(dest[1]); break; // converting to lv_color_t;
                case MP_QSTR_intense: data->intense = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to lv_opa_t;
                case MP_QSTR_opa: data->opa = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to lv_opa_t;
                default: field_not_found(MP_QSTR_lv_style_image_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_style_image_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_style_image_t");
}

STATIC const mp_rom_map_elem_t mp_lv_style_image_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_style_image_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_style_image_t_locals_dict, mp_lv_style_image_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_style_image_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_style_image_t,
    .print = mp_lv_style_image_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_style_image_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_style_image_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_style_image_t_type()
{
    return &mp_lv_style_image_t_type;
}
    
typedef typeof( ((lv_style_t*)(0))->line ) lv_style_line_t;

/*
 * Struct lv_style_line_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_style_line_t_type();

STATIC inline lv_style_line_t* mp_write_ptr_lv_style_line_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_style_line_t_type()));
    return (lv_style_line_t*)self->data;
}

#define mp_write_lv_style_line_t(struct_obj) *mp_write_ptr_lv_style_line_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_style_line_t(lv_style_line_t *field)
{
    return lv_to_mp_struct(get_mp_lv_style_line_t_type(), field);
}

#define mp_read_lv_style_line_t(field) mp_read_ptr_lv_style_line_t(copy_buffer(&field, sizeof(lv_style_line_t)))
#define mp_read_byref_lv_style_line_t(field) mp_read_ptr_lv_style_line_t(&field)

STATIC void mp_lv_style_line_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_style_line_t *data = (lv_style_line_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_color: dest[0] = mp_read_byref_lv_color32_t(data->color); break; // converting from lv_color_t;
            case MP_QSTR_width: dest[0] = mp_obj_new_int(data->width); break; // converting from lv_coord_t;
            case MP_QSTR_opa: dest[0] = mp_obj_new_int_from_uint(data->opa); break; // converting from lv_opa_t;
            case MP_QSTR_rounded: dest[0] = mp_obj_new_int_from_uint(data->rounded); break; // converting from uint8_t;
            default: field_not_found(MP_QSTR_lv_style_line_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_color: data->color = mp_write_lv_color32_t(dest[1]); break; // converting to lv_color_t;
                case MP_QSTR_width: data->width = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_opa: data->opa = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to lv_opa_t;
                case MP_QSTR_rounded: data->rounded = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                default: field_not_found(MP_QSTR_lv_style_line_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_style_line_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_style_line_t");
}

STATIC const mp_rom_map_elem_t mp_lv_style_line_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_style_line_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_style_line_t_locals_dict, mp_lv_style_line_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_style_line_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_style_line_t,
    .print = mp_lv_style_line_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_style_line_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_style_line_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_style_line_t_type()
{
    return &mp_lv_style_line_t_type;
}
    

/*
 * Struct lv_style_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_style_t_type();

STATIC inline lv_style_t* mp_write_ptr_lv_style_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_style_t_type()));
    return (lv_style_t*)self->data;
}

#define mp_write_lv_style_t(struct_obj) *mp_write_ptr_lv_style_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_style_t(lv_style_t *field)
{
    return lv_to_mp_struct(get_mp_lv_style_t_type(), field);
}

#define mp_read_lv_style_t(field) mp_read_ptr_lv_style_t(copy_buffer(&field, sizeof(lv_style_t)))
#define mp_read_byref_lv_style_t(field) mp_read_ptr_lv_style_t(&field)

STATIC void mp_lv_style_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_style_t *data = (lv_style_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_glass: dest[0] = mp_obj_new_int_from_uint(data->glass); break; // converting from uint8_t;
            case MP_QSTR_body: dest[0] = mp_read_byref_lv_style_body_t(data->body); break; // converting from lv_style_body_t;
            case MP_QSTR_text: dest[0] = mp_read_byref_lv_style_text_t(data->text); break; // converting from lv_style_text_t;
            case MP_QSTR_image: dest[0] = mp_read_byref_lv_style_image_t(data->image); break; // converting from lv_style_image_t;
            case MP_QSTR_line: dest[0] = mp_read_byref_lv_style_line_t(data->line); break; // converting from lv_style_line_t;
            default: field_not_found(MP_QSTR_lv_style_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_glass: data->glass = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_body: data->body = mp_write_lv_style_body_t(dest[1]); break; // converting to lv_style_body_t;
                case MP_QSTR_text: data->text = mp_write_lv_style_text_t(dest[1]); break; // converting to lv_style_text_t;
                case MP_QSTR_image: data->image = mp_write_lv_style_image_t(dest[1]); break; // converting to lv_style_image_t;
                case MP_QSTR_line: data->line = mp_write_lv_style_line_t(dest[1]); break; // converting to lv_style_line_t;
                default: field_not_found(MP_QSTR_lv_style_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_style_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_style_t");
}

STATIC const mp_rom_map_elem_t mp_lv_style_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_style_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_style_t_locals_dict, mp_lv_style_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_style_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_style_t,
    .print = mp_lv_style_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_style_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_style_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_style_t_type()
{
    return &mp_lv_style_t_type;
}
    

/*
 * lvgl extension definition for:
 * void lv_obj_set_style(lv_obj_t *obj, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_obj_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    const lv_style_t *style = mp_to_ptr(args[1]);
    lv_obj_set_style(obj, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_style_obj, 2, 2, mp_lv_obj_set_style);

 

/*
 * lvgl extension definition for:
 * void lv_obj_refresh_style(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_refresh_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_refresh_style(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_refresh_style_obj, 1, 1, mp_lv_obj_refresh_style);

 

/*
 * lvgl extension definition for:
 * void lv_obj_report_style_mod(lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_obj_report_style_mod(size_t n_args, const mp_obj_t *args)
{
    lv_style_t *style = mp_to_ptr(args[0]);
    lv_obj_report_style_mod(style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_report_style_mod_obj, 1, 1, mp_lv_obj_report_style_mod);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_hidden(lv_obj_t *obj, bool en)
 */
 
STATIC mp_obj_t mp_lv_obj_set_hidden(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_obj_set_hidden(obj, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_hidden_obj, 2, 2, mp_lv_obj_set_hidden);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_click(lv_obj_t *obj, bool en)
 */
 
STATIC mp_obj_t mp_lv_obj_set_click(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_obj_set_click(obj, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_click_obj, 2, 2, mp_lv_obj_set_click);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_top(lv_obj_t *obj, bool en)
 */
 
STATIC mp_obj_t mp_lv_obj_set_top(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_obj_set_top(obj, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_top_obj, 2, 2, mp_lv_obj_set_top);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_drag(lv_obj_t *obj, bool en)
 */
 
STATIC mp_obj_t mp_lv_obj_set_drag(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_obj_set_drag(obj, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_drag_obj, 2, 2, mp_lv_obj_set_drag);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_drag_dir(lv_obj_t *obj, lv_drag_dir_t drag_dir)
 */
 
STATIC mp_obj_t mp_lv_obj_set_drag_dir(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_drag_dir_t drag_dir = (uint8_t)mp_obj_get_int(args[1]);
    lv_obj_set_drag_dir(obj, drag_dir);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_drag_dir_obj, 2, 2, mp_lv_obj_set_drag_dir);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_drag_throw(lv_obj_t *obj, bool en)
 */
 
STATIC mp_obj_t mp_lv_obj_set_drag_throw(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_obj_set_drag_throw(obj, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_drag_throw_obj, 2, 2, mp_lv_obj_set_drag_throw);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_drag_parent(lv_obj_t *obj, bool en)
 */
 
STATIC mp_obj_t mp_lv_obj_set_drag_parent(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_obj_set_drag_parent(obj, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_drag_parent_obj, 2, 2, mp_lv_obj_set_drag_parent);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_parent_event(lv_obj_t *obj, bool en)
 */
 
STATIC mp_obj_t mp_lv_obj_set_parent_event(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_obj_set_parent_event(obj, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_parent_event_obj, 2, 2, mp_lv_obj_set_parent_event);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_opa_scale_enable(lv_obj_t *obj, bool en)
 */
 
STATIC mp_obj_t mp_lv_obj_set_opa_scale_enable(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_obj_set_opa_scale_enable(obj, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_opa_scale_enable_obj, 2, 2, mp_lv_obj_set_opa_scale_enable);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_opa_scale(lv_obj_t *obj, lv_opa_t opa_scale)
 */
 
STATIC mp_obj_t mp_lv_obj_set_opa_scale(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_opa_t opa_scale = (uint8_t)mp_obj_get_int(args[1]);
    lv_obj_set_opa_scale(obj, opa_scale);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_opa_scale_obj, 2, 2, mp_lv_obj_set_opa_scale);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_protect(lv_obj_t *obj, uint8_t prot)
 */
 
STATIC mp_obj_t mp_lv_obj_set_protect(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    uint8_t prot = (uint8_t)mp_obj_get_int(args[1]);
    lv_obj_set_protect(obj, prot);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_protect_obj, 2, 2, mp_lv_obj_set_protect);

 

/*
 * lvgl extension definition for:
 * void lv_obj_clear_protect(lv_obj_t *obj, uint8_t prot)
 */
 
STATIC mp_obj_t mp_lv_obj_clear_protect(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    uint8_t prot = (uint8_t)mp_obj_get_int(args[1]);
    lv_obj_clear_protect(obj, prot);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_clear_protect_obj, 2, 2, mp_lv_obj_clear_protect);

 

/*
 * Callback function event_cb
 * void lv_event_cb_t(struct _lv_obj_t *obj, lv_event_t event)
 */

STATIC void event_cb_callback(lv_obj_t * arg0, lv_event_t arg1)
{
    mp_obj_t args[2];
    args[0] = lv_to_mp((void*)arg0);
    args[1] = mp_obj_new_int_from_uint(arg1);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_event_cb)) , 2, 0, args);
    return;
}


/*
 * lvgl extension definition for:
 * void lv_obj_set_event_cb(lv_obj_t *obj, lv_event_cb_t event_cb)
 */
 
STATIC mp_obj_t mp_lv_obj_set_event_cb(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_event_cb_t event_cb = mp_lv_callback(args[1], &event_cb_callback, MP_QSTR_event_cb, &obj->user_data);
    lv_obj_set_event_cb(obj, event_cb);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_event_cb_obj, 2, 2, mp_lv_obj_set_event_cb);

 

/*
 * Callback function signal_cb
 * lv_res_t lv_signal_cb_t(struct _lv_obj_t *obj, lv_signal_t sign, void *param)
 */

STATIC lv_res_t signal_cb_callback(lv_obj_t * arg0, lv_signal_t arg1, void * arg2)
{
    mp_obj_t args[3];
    args[0] = lv_to_mp((void*)arg0);
    args[1] = mp_obj_new_int_from_uint(arg1);
    args[2] = ptr_to_mp((void*)arg2);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_obj_t callback_result = mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_signal_cb)) , 3, 0, args);
    return (uint8_t)mp_obj_get_int(callback_result);
}


/*
 * lvgl extension definition for:
 * void lv_obj_set_signal_cb(lv_obj_t *obj, lv_signal_cb_t signal_cb)
 */
 
STATIC mp_obj_t mp_lv_obj_set_signal_cb(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_signal_cb_t signal_cb = mp_lv_callback(args[1], &signal_cb_callback, MP_QSTR_signal_cb, &obj->user_data);
    lv_obj_set_signal_cb(obj, signal_cb);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_signal_cb_obj, 2, 2, mp_lv_obj_set_signal_cb);

 

/*
 * Struct lv_area_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_area_t_type();

STATIC inline lv_area_t* mp_write_ptr_lv_area_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_area_t_type()));
    return (lv_area_t*)self->data;
}

#define mp_write_lv_area_t(struct_obj) *mp_write_ptr_lv_area_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_area_t(lv_area_t *field)
{
    return lv_to_mp_struct(get_mp_lv_area_t_type(), field);
}

#define mp_read_lv_area_t(field) mp_read_ptr_lv_area_t(copy_buffer(&field, sizeof(lv_area_t)))
#define mp_read_byref_lv_area_t(field) mp_read_ptr_lv_area_t(&field)

STATIC void mp_lv_area_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_area_t *data = (lv_area_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_x1: dest[0] = mp_obj_new_int(data->x1); break; // converting from lv_coord_t;
            case MP_QSTR_y1: dest[0] = mp_obj_new_int(data->y1); break; // converting from lv_coord_t;
            case MP_QSTR_x2: dest[0] = mp_obj_new_int(data->x2); break; // converting from lv_coord_t;
            case MP_QSTR_y2: dest[0] = mp_obj_new_int(data->y2); break; // converting from lv_coord_t;
            default: field_not_found(MP_QSTR_lv_area_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_x1: data->x1 = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_y1: data->y1 = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_x2: data->x2 = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_y2: data->y2 = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                default: field_not_found(MP_QSTR_lv_area_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_area_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_area_t");
}

STATIC const mp_rom_map_elem_t mp_lv_area_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_area_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_area_t_locals_dict, mp_lv_area_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_area_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_area_t,
    .print = mp_lv_area_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_area_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_area_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_area_t_type()
{
    return &mp_lv_area_t_type;
}
    

/*
 * Callback function design_cb
 * bool lv_design_cb_t(struct _lv_obj_t *obj, const lv_area_t *mask_p, lv_design_mode_t mode)
 */

STATIC bool design_cb_callback(lv_obj_t * arg0, const lv_area_t * arg1, lv_design_mode_t arg2)
{
    mp_obj_t args[3];
    args[0] = lv_to_mp((void*)arg0);
    args[1] = ptr_to_mp((void*)arg1);
    args[2] = mp_obj_new_int_from_uint(arg2);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_obj_t callback_result = mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_design_cb)) , 3, 0, args);
    return mp_obj_is_true(callback_result);
}


/*
 * lvgl extension definition for:
 * void lv_obj_set_design_cb(lv_obj_t *obj, lv_design_cb_t design_cb)
 */
 
STATIC mp_obj_t mp_lv_obj_set_design_cb(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_design_cb_t design_cb = mp_lv_callback(args[1], &design_cb_callback, MP_QSTR_design_cb, &obj->user_data);
    lv_obj_set_design_cb(obj, design_cb);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_design_cb_obj, 2, 2, mp_lv_obj_set_design_cb);

 

/*
 * lvgl extension definition for:
 * void *lv_obj_allocate_ext_attr(lv_obj_t *obj, uint16_t ext_size)
 */
 
STATIC mp_obj_t mp_lv_obj_allocate_ext_attr(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    uint16_t ext_size = (uint16_t)mp_obj_get_int(args[1]);
    void * res = lv_obj_allocate_ext_attr(obj, ext_size);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_allocate_ext_attr_obj, 2, 2, mp_lv_obj_allocate_ext_attr);

 

/*
 * lvgl extension definition for:
 * void lv_obj_refresh_ext_draw_pad(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_refresh_ext_draw_pad(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_refresh_ext_draw_pad(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_refresh_ext_draw_pad_obj, 1, 1, mp_lv_obj_refresh_ext_draw_pad);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_obj_get_screen(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_screen(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_t * res = lv_obj_get_screen(obj);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_screen_obj, 1, 1, mp_lv_obj_get_screen);

 

/*
 * Struct lv_disp_buf_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_disp_buf_t_type();

STATIC inline lv_disp_buf_t* mp_write_ptr_lv_disp_buf_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_disp_buf_t_type()));
    return (lv_disp_buf_t*)self->data;
}

#define mp_write_lv_disp_buf_t(struct_obj) *mp_write_ptr_lv_disp_buf_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_disp_buf_t(lv_disp_buf_t *field)
{
    return lv_to_mp_struct(get_mp_lv_disp_buf_t_type(), field);
}

#define mp_read_lv_disp_buf_t(field) mp_read_ptr_lv_disp_buf_t(copy_buffer(&field, sizeof(lv_disp_buf_t)))
#define mp_read_byref_lv_disp_buf_t(field) mp_read_ptr_lv_disp_buf_t(&field)

STATIC void mp_lv_disp_buf_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_disp_buf_t *data = (lv_disp_buf_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_buf1: dest[0] = ptr_to_mp((void*)data->buf1); break; // converting from void *;
            case MP_QSTR_buf2: dest[0] = ptr_to_mp((void*)data->buf2); break; // converting from void *;
            case MP_QSTR_buf_act: dest[0] = ptr_to_mp((void*)data->buf_act); break; // converting from void *;
            case MP_QSTR_size: dest[0] = mp_obj_new_int_from_uint(data->size); break; // converting from uint32_t;
            case MP_QSTR_area: dest[0] = mp_read_byref_lv_area_t(data->area); break; // converting from lv_area_t;
            case MP_QSTR_flushing: dest[0] = mp_obj_new_int_from_uint(data->flushing); break; // converting from uint32_t;
            default: field_not_found(MP_QSTR_lv_disp_buf_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_buf1: data->buf1 = (void*)mp_to_ptr(dest[1]); break; // converting to void *;
                case MP_QSTR_buf2: data->buf2 = (void*)mp_to_ptr(dest[1]); break; // converting to void *;
                case MP_QSTR_buf_act: data->buf_act = (void*)mp_to_ptr(dest[1]); break; // converting to void *;
                case MP_QSTR_size: data->size = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_area: data->area = mp_write_lv_area_t(dest[1]); break; // converting to lv_area_t;
                case MP_QSTR_flushing: data->flushing = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                default: field_not_found(MP_QSTR_lv_disp_buf_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_disp_buf_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_disp_buf_t");
}

STATIC const mp_rom_map_elem_t mp_lv_disp_buf_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_disp_buf_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_disp_buf_t_locals_dict, mp_lv_disp_buf_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_disp_buf_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_disp_buf_t,
    .print = mp_lv_disp_buf_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_disp_buf_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_disp_buf_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_disp_buf_t_type()
{
    return &mp_lv_disp_buf_t_type;
}
    
STATIC void flush_cb_callback(struct _disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
STATIC void rounder_cb_callback(struct _disp_drv_t *disp_drv, lv_area_t *area);
STATIC void set_px_cb_callback(struct _disp_drv_t *disp_drv, uint8_t *buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa);
STATIC void monitor_cb_callback(struct _disp_drv_t *disp_drv, uint32_t time, uint32_t px);
STATIC void mem_blend_cb_callback(struct _disp_drv_t *disp_drv, lv_color_t *dest, const lv_color_t *src, uint32_t length, lv_opa_t opa);
STATIC void mem_fill_cb_callback(struct _disp_drv_t *disp_drv, lv_color_t *dest_buf, const lv_area_t *dest_area, const lv_area_t *fill_area, lv_color_t color);

/*
 * Struct lv_disp_drv_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_disp_drv_t_type();

STATIC inline lv_disp_drv_t* mp_write_ptr_lv_disp_drv_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_disp_drv_t_type()));
    return (lv_disp_drv_t*)self->data;
}

#define mp_write_lv_disp_drv_t(struct_obj) *mp_write_ptr_lv_disp_drv_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_disp_drv_t(lv_disp_drv_t *field)
{
    return lv_to_mp_struct(get_mp_lv_disp_drv_t_type(), field);
}

#define mp_read_lv_disp_drv_t(field) mp_read_ptr_lv_disp_drv_t(copy_buffer(&field, sizeof(lv_disp_drv_t)))
#define mp_read_byref_lv_disp_drv_t(field) mp_read_ptr_lv_disp_drv_t(&field)

STATIC void mp_lv_disp_drv_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_disp_drv_t *data = (lv_disp_drv_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_hor_res: dest[0] = mp_obj_new_int(data->hor_res); break; // converting from lv_coord_t;
            case MP_QSTR_ver_res: dest[0] = mp_obj_new_int(data->ver_res); break; // converting from lv_coord_t;
            case MP_QSTR_buffer: dest[0] = ptr_to_mp((void*)data->buffer); break; // converting from lv_disp_buf_t *;
            case MP_QSTR_antialiasing: dest[0] = mp_obj_new_int_from_uint(data->antialiasing); break; // converting from uint32_t;
            case MP_QSTR_rotated: dest[0] = mp_obj_new_int_from_uint(data->rotated); break; // converting from uint32_t;
            case MP_QSTR_flush_cb: dest[0] = ptr_to_mp((void*)data->flush_cb); break; // converting from void (*)(lv_disp_drv_t *disp_drv, lv_area_t *area, lv_color_t *color_p);
            case MP_QSTR_rounder_cb: dest[0] = ptr_to_mp((void*)data->rounder_cb); break; // converting from void (*)(lv_disp_drv_t *disp_drv, lv_area_t *area);
            case MP_QSTR_set_px_cb: dest[0] = ptr_to_mp((void*)data->set_px_cb); break; // converting from void (*)(lv_disp_drv_t *disp_drv, uint8_t *buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa);
            case MP_QSTR_monitor_cb: dest[0] = ptr_to_mp((void*)data->monitor_cb); break; // converting from void (*)(lv_disp_drv_t *disp_drv, uint32_t time, uint32_t px);
            case MP_QSTR_mem_blend_cb: dest[0] = ptr_to_mp((void*)data->mem_blend_cb); break; // converting from void (*)(lv_disp_drv_t *disp_drv, lv_color_t *dest, lv_color_t *src, uint32_t length, lv_opa_t opa);
            case MP_QSTR_mem_fill_cb: dest[0] = ptr_to_mp((void*)data->mem_fill_cb); break; // converting from void (*)(lv_disp_drv_t *disp_drv, lv_color_t *dest_buf, lv_area_t *dest_area, lv_area_t *fill_area, lv_color_t color);
            case MP_QSTR_user_data: dest[0] = ptr_to_mp(data->user_data); break; // converting from lv_disp_drv_user_data_t;
            default: field_not_found(MP_QSTR_lv_disp_drv_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_hor_res: data->hor_res = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_ver_res: data->ver_res = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_buffer: data->buffer = (void*)mp_to_ptr(dest[1]); break; // converting to lv_disp_buf_t *;
                case MP_QSTR_antialiasing: data->antialiasing = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_rotated: data->rotated = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_flush_cb: data->flush_cb = (void*)mp_lv_callback(dest[1], flush_cb_callback ,MP_QSTR_flush_cb, &data->user_data); break; // converting to void (*)(lv_disp_drv_t *disp_drv, lv_area_t *area, lv_color_t *color_p);
                case MP_QSTR_rounder_cb: data->rounder_cb = (void*)mp_lv_callback(dest[1], rounder_cb_callback ,MP_QSTR_rounder_cb, &data->user_data); break; // converting to void (*)(lv_disp_drv_t *disp_drv, lv_area_t *area);
                case MP_QSTR_set_px_cb: data->set_px_cb = (void*)mp_lv_callback(dest[1], set_px_cb_callback ,MP_QSTR_set_px_cb, &data->user_data); break; // converting to void (*)(lv_disp_drv_t *disp_drv, uint8_t *buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa);
                case MP_QSTR_monitor_cb: data->monitor_cb = (void*)mp_lv_callback(dest[1], monitor_cb_callback ,MP_QSTR_monitor_cb, &data->user_data); break; // converting to void (*)(lv_disp_drv_t *disp_drv, uint32_t time, uint32_t px);
                case MP_QSTR_mem_blend_cb: data->mem_blend_cb = (void*)mp_lv_callback(dest[1], mem_blend_cb_callback ,MP_QSTR_mem_blend_cb, &data->user_data); break; // converting to void (*)(lv_disp_drv_t *disp_drv, lv_color_t *dest, lv_color_t *src, uint32_t length, lv_opa_t opa);
                case MP_QSTR_mem_fill_cb: data->mem_fill_cb = (void*)mp_lv_callback(dest[1], mem_fill_cb_callback ,MP_QSTR_mem_fill_cb, &data->user_data); break; // converting to void (*)(lv_disp_drv_t *disp_drv, lv_color_t *dest_buf, lv_area_t *dest_area, lv_area_t *fill_area, lv_color_t color);
                case MP_QSTR_user_data: data->user_data = mp_to_ptr(dest[1]); break; // converting to lv_disp_drv_user_data_t;
                default: field_not_found(MP_QSTR_lv_disp_drv_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_disp_drv_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_disp_drv_t");
}

STATIC const mp_rom_map_elem_t mp_lv_disp_drv_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_disp_drv_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_disp_drv_t_locals_dict, mp_lv_disp_drv_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_disp_drv_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_disp_drv_t,
    .print = mp_lv_disp_drv_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_disp_drv_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_disp_drv_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_disp_drv_t_type()
{
    return &mp_lv_disp_drv_t_type;
}
    
STATIC void task_cb_callback(struct _lv_task_t *);

/*
 * Struct lv_task_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_task_t_type();

STATIC inline lv_task_t* mp_write_ptr_lv_task_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_task_t_type()));
    return (lv_task_t*)self->data;
}

#define mp_write_lv_task_t(struct_obj) *mp_write_ptr_lv_task_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_task_t(lv_task_t *field)
{
    return lv_to_mp_struct(get_mp_lv_task_t_type(), field);
}

#define mp_read_lv_task_t(field) mp_read_ptr_lv_task_t(copy_buffer(&field, sizeof(lv_task_t)))
#define mp_read_byref_lv_task_t(field) mp_read_ptr_lv_task_t(&field)

STATIC void mp_lv_task_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_task_t *data = (lv_task_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_period: dest[0] = mp_obj_new_int_from_uint(data->period); break; // converting from uint32_t;
            case MP_QSTR_last_run: dest[0] = mp_obj_new_int_from_uint(data->last_run); break; // converting from uint32_t;
            case MP_QSTR_task_cb: dest[0] = ptr_to_mp((void*)data->task_cb); break; // converting from void (*)(lv_task_t *);
            case MP_QSTR_user_data: dest[0] = ptr_to_mp((void*)data->user_data); break; // converting from void *;
            case MP_QSTR_prio: dest[0] = mp_obj_new_int_from_uint(data->prio); break; // converting from uint8_t;
            case MP_QSTR_once: dest[0] = mp_obj_new_int_from_uint(data->once); break; // converting from uint8_t;
            default: field_not_found(MP_QSTR_lv_task_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_period: data->period = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_last_run: data->last_run = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_task_cb: data->task_cb = (void*)mp_lv_callback(dest[1], task_cb_callback ,MP_QSTR_task_cb, &data->user_data); break; // converting to void (*)(lv_task_t *);
                case MP_QSTR_user_data: data->user_data = (void*)mp_to_ptr(dest[1]); break; // converting to void *;
                case MP_QSTR_prio: data->prio = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_once: data->once = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                default: field_not_found(MP_QSTR_lv_task_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_task_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_task_t");
}

STATIC const mp_rom_map_elem_t mp_lv_task_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_task_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_task_t_locals_dict, mp_lv_task_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_task_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_task_t,
    .print = mp_lv_task_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_task_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_task_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_task_t_type()
{
    return &mp_lv_task_t_type;
}
    

/*
 * Struct lv_ll_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_ll_t_type();

STATIC inline lv_ll_t* mp_write_ptr_lv_ll_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_ll_t_type()));
    return (lv_ll_t*)self->data;
}

#define mp_write_lv_ll_t(struct_obj) *mp_write_ptr_lv_ll_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_ll_t(lv_ll_t *field)
{
    return lv_to_mp_struct(get_mp_lv_ll_t_type(), field);
}

#define mp_read_lv_ll_t(field) mp_read_ptr_lv_ll_t(copy_buffer(&field, sizeof(lv_ll_t)))
#define mp_read_byref_lv_ll_t(field) mp_read_ptr_lv_ll_t(&field)

STATIC void mp_lv_ll_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_ll_t *data = (lv_ll_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_n_size: dest[0] = mp_obj_new_int_from_uint(data->n_size); break; // converting from uint32_t;
            case MP_QSTR_head: dest[0] = ptr_to_mp((void*)data->head); break; // converting from lv_ll_node_t *;
            case MP_QSTR_tail: dest[0] = ptr_to_mp((void*)data->tail); break; // converting from lv_ll_node_t *;
            default: field_not_found(MP_QSTR_lv_ll_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_n_size: data->n_size = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_head: data->head = (void*)mp_to_ptr(dest[1]); break; // converting to lv_ll_node_t *;
                case MP_QSTR_tail: data->tail = (void*)mp_to_ptr(dest[1]); break; // converting to lv_ll_node_t *;
                default: field_not_found(MP_QSTR_lv_ll_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_ll_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_ll_t");
}

STATIC const mp_rom_map_elem_t mp_lv_ll_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_ll_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_ll_t_locals_dict, mp_lv_ll_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_ll_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_ll_t,
    .print = mp_lv_ll_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_ll_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_ll_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_ll_t_type()
{
    return &mp_lv_ll_t_type;
}
    

/*
 * Struct lv_disp_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_disp_t_type();

STATIC inline lv_disp_t* mp_write_ptr_lv_disp_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_disp_t_type()));
    return (lv_disp_t*)self->data;
}

#define mp_write_lv_disp_t(struct_obj) *mp_write_ptr_lv_disp_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_disp_t(lv_disp_t *field)
{
    return lv_to_mp_struct(get_mp_lv_disp_t_type(), field);
}

#define mp_read_lv_disp_t(field) mp_read_ptr_lv_disp_t(copy_buffer(&field, sizeof(lv_disp_t)))
#define mp_read_byref_lv_disp_t(field) mp_read_ptr_lv_disp_t(&field)

STATIC void mp_lv_disp_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_disp_t *data = (lv_disp_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_driver: dest[0] = mp_read_byref_lv_disp_drv_t(data->driver); break; // converting from lv_disp_drv_t;
            case MP_QSTR_refr_task: dest[0] = ptr_to_mp((void*)data->refr_task); break; // converting from lv_task_t *;
            case MP_QSTR_scr_ll: dest[0] = mp_read_byref_lv_ll_t(data->scr_ll); break; // converting from lv_ll_t;
            case MP_QSTR_act_scr: dest[0] = lv_to_mp((void*)data->act_scr); break; // converting from lv_obj_t *;
            case MP_QSTR_top_layer: dest[0] = lv_to_mp((void*)data->top_layer); break; // converting from lv_obj_t *;
            case MP_QSTR_sys_layer: dest[0] = lv_to_mp((void*)data->sys_layer); break; // converting from lv_obj_t *;
            case MP_QSTR_inv_areas: dest[0] = ptr_to_mp(&data->inv_areas); break; // converting from lv_area_t [32];
            case MP_QSTR_inv_area_joined: dest[0] = ptr_to_mp(&data->inv_area_joined); break; // converting from uint8_t [32];
            case MP_QSTR_inv_p: dest[0] = mp_obj_new_int_from_uint(data->inv_p); break; // converting from uint32_t;
            case MP_QSTR_last_activity_time: dest[0] = mp_obj_new_int_from_uint(data->last_activity_time); break; // converting from uint32_t;
            default: field_not_found(MP_QSTR_lv_disp_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_driver: data->driver = mp_write_lv_disp_drv_t(dest[1]); break; // converting to lv_disp_drv_t;
                case MP_QSTR_refr_task: data->refr_task = (void*)mp_to_ptr(dest[1]); break; // converting to lv_task_t *;
                case MP_QSTR_scr_ll: data->scr_ll = mp_write_lv_ll_t(dest[1]); break; // converting to lv_ll_t;
                case MP_QSTR_act_scr: data->act_scr = (void*)mp_to_lv(dest[1]); break; // converting to lv_obj_t *;
                case MP_QSTR_top_layer: data->top_layer = (void*)mp_to_lv(dest[1]); break; // converting to lv_obj_t *;
                case MP_QSTR_sys_layer: data->sys_layer = (void*)mp_to_lv(dest[1]); break; // converting to lv_obj_t *;
                case MP_QSTR_inv_areas: memcpy(&data->inv_areas, mp_to_ptr(dest[1]), sizeof(lv_area_t)*32); break; // converting to lv_area_t [32];
                case MP_QSTR_inv_area_joined: memcpy(&data->inv_area_joined, mp_to_ptr(dest[1]), sizeof(uint8_t)*32); break; // converting to uint8_t [32];
                case MP_QSTR_inv_p: data->inv_p = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_last_activity_time: data->last_activity_time = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                default: field_not_found(MP_QSTR_lv_disp_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_disp_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_disp_t");
}

STATIC const mp_rom_map_elem_t mp_lv_disp_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_disp_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_disp_t_locals_dict, mp_lv_disp_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_disp_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_disp_t,
    .print = mp_lv_disp_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_disp_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_disp_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_disp_t_type()
{
    return &mp_lv_disp_t_type;
}
    

/*
 * lvgl extension definition for:
 * lv_disp_t *lv_obj_get_disp(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_disp(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_disp_t * res = lv_obj_get_disp(obj);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_disp_obj, 1, 1, mp_lv_obj_get_disp);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_obj_get_parent(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_parent(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_t * res = lv_obj_get_parent(obj);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_parent_obj, 1, 1, mp_lv_obj_get_parent);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_obj_get_child(const lv_obj_t *obj, const lv_obj_t *child)
 */
 
STATIC mp_obj_t mp_lv_obj_get_child(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    const lv_obj_t *child = mp_to_lv(args[1]);
    lv_obj_t * res = lv_obj_get_child(obj, child);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_child_obj, 2, 2, mp_lv_obj_get_child);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_obj_get_child_back(const lv_obj_t *obj, const lv_obj_t *child)
 */
 
STATIC mp_obj_t mp_lv_obj_get_child_back(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    const lv_obj_t *child = mp_to_lv(args[1]);
    lv_obj_t * res = lv_obj_get_child_back(obj, child);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_child_back_obj, 2, 2, mp_lv_obj_get_child_back);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_obj_count_children(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_count_children(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    uint16_t res = lv_obj_count_children(obj);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_count_children_obj, 1, 1, mp_lv_obj_count_children);

 

/*
 * lvgl extension definition for:
 * void lv_obj_get_coords(const lv_obj_t *obj, lv_area_t *cords_p)
 */
 
STATIC mp_obj_t mp_lv_obj_get_coords(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_area_t *cords_p = mp_to_ptr(args[1]);
    lv_obj_get_coords(obj, cords_p);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_coords_obj, 2, 2, mp_lv_obj_get_coords);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_obj_get_x(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_x(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t res = lv_obj_get_x(obj);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_x_obj, 1, 1, mp_lv_obj_get_x);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_obj_get_y(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_y(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t res = lv_obj_get_y(obj);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_y_obj, 1, 1, mp_lv_obj_get_y);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_obj_get_width(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_width(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t res = lv_obj_get_width(obj);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_width_obj, 1, 1, mp_lv_obj_get_width);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_obj_get_height(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_height(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t res = lv_obj_get_height(obj);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_height_obj, 1, 1, mp_lv_obj_get_height);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_obj_get_width_fit(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_width_fit(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t res = lv_obj_get_width_fit(obj);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_width_fit_obj, 1, 1, mp_lv_obj_get_width_fit);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_obj_get_height_fit(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_height_fit(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t res = lv_obj_get_height_fit(obj);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_height_fit_obj, 1, 1, mp_lv_obj_get_height_fit);

 

/*
 * lvgl extension definition for:
 * bool lv_obj_get_auto_realign(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_auto_realign(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    bool res = lv_obj_get_auto_realign(obj);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_auto_realign_obj, 1, 1, mp_lv_obj_get_auto_realign);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_obj_get_ext_draw_pad(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_ext_draw_pad(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_coord_t res = lv_obj_get_ext_draw_pad(obj);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_ext_draw_pad_obj, 1, 1, mp_lv_obj_get_ext_draw_pad);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_obj_get_style(const lv_obj_t *obj)
 */
    

/*
 * lvgl extension definition for:
 * bool lv_obj_get_hidden(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_hidden(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    bool res = lv_obj_get_hidden(obj);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_hidden_obj, 1, 1, mp_lv_obj_get_hidden);

 

/*
 * lvgl extension definition for:
 * bool lv_obj_get_click(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_click(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    bool res = lv_obj_get_click(obj);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_click_obj, 1, 1, mp_lv_obj_get_click);

 

/*
 * lvgl extension definition for:
 * bool lv_obj_get_top(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_top(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    bool res = lv_obj_get_top(obj);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_top_obj, 1, 1, mp_lv_obj_get_top);

 

/*
 * lvgl extension definition for:
 * bool lv_obj_get_drag(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_drag(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    bool res = lv_obj_get_drag(obj);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_drag_obj, 1, 1, mp_lv_obj_get_drag);

 

/*
 * lvgl extension definition for:
 * lv_drag_dir_t lv_obj_get_drag_dir(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_drag_dir(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_drag_dir_t res = lv_obj_get_drag_dir(obj);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_drag_dir_obj, 1, 1, mp_lv_obj_get_drag_dir);

 

/*
 * lvgl extension definition for:
 * bool lv_obj_get_drag_throw(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_drag_throw(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    bool res = lv_obj_get_drag_throw(obj);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_drag_throw_obj, 1, 1, mp_lv_obj_get_drag_throw);

 

/*
 * lvgl extension definition for:
 * bool lv_obj_get_drag_parent(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_drag_parent(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    bool res = lv_obj_get_drag_parent(obj);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_drag_parent_obj, 1, 1, mp_lv_obj_get_drag_parent);

 

/*
 * lvgl extension definition for:
 * bool lv_obj_get_parent_event(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_parent_event(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    bool res = lv_obj_get_parent_event(obj);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_parent_event_obj, 1, 1, mp_lv_obj_get_parent_event);

 

/*
 * lvgl extension definition for:
 * lv_opa_t lv_obj_get_opa_scale_enable(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_opa_scale_enable(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_opa_t res = lv_obj_get_opa_scale_enable(obj);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_opa_scale_enable_obj, 1, 1, mp_lv_obj_get_opa_scale_enable);

 

/*
 * lvgl extension definition for:
 * lv_opa_t lv_obj_get_opa_scale(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_opa_scale(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_opa_t res = lv_obj_get_opa_scale(obj);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_opa_scale_obj, 1, 1, mp_lv_obj_get_opa_scale);

 

/*
 * lvgl extension definition for:
 * uint8_t lv_obj_get_protect(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_protect(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    uint8_t res = lv_obj_get_protect(obj);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_protect_obj, 1, 1, mp_lv_obj_get_protect);

 

/*
 * lvgl extension definition for:
 * bool lv_obj_is_protected(const lv_obj_t *obj, uint8_t prot)
 */
 
STATIC mp_obj_t mp_lv_obj_is_protected(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    uint8_t prot = (uint8_t)mp_obj_get_int(args[1]);
    bool res = lv_obj_is_protected(obj, prot);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_is_protected_obj, 2, 2, mp_lv_obj_is_protected);

 

/*
 * lvgl extension definition for:
 * lv_signal_cb_t lv_obj_get_signal_cb(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_signal_cb(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_signal_cb_t res = lv_obj_get_signal_cb(obj);
    return ptr_to_mp(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_signal_cb_obj, 1, 1, mp_lv_obj_get_signal_cb);

 

/*
 * lvgl extension definition for:
 * lv_design_cb_t lv_obj_get_design_cb(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_design_cb(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_design_cb_t res = lv_obj_get_design_cb(obj);
    return ptr_to_mp(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_design_cb_obj, 1, 1, mp_lv_obj_get_design_cb);

 

/*
 * lvgl extension definition for:
 * lv_event_cb_t lv_obj_get_event_cb(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_event_cb(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    lv_event_cb_t res = lv_obj_get_event_cb(obj);
    return ptr_to_mp(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_event_cb_obj, 1, 1, mp_lv_obj_get_event_cb);

 

/*
 * lvgl extension definition for:
 * void *lv_obj_get_ext_attr(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_ext_attr(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    void * res = lv_obj_get_ext_attr(obj);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_ext_attr_obj, 1, 1, mp_lv_obj_get_ext_attr);

 

/*
 * Struct lv_obj_type_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_obj_type_t_type();

STATIC inline lv_obj_type_t* mp_write_ptr_lv_obj_type_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_obj_type_t_type()));
    return (lv_obj_type_t*)self->data;
}

#define mp_write_lv_obj_type_t(struct_obj) *mp_write_ptr_lv_obj_type_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_obj_type_t(lv_obj_type_t *field)
{
    return lv_to_mp_struct(get_mp_lv_obj_type_t_type(), field);
}

#define mp_read_lv_obj_type_t(field) mp_read_ptr_lv_obj_type_t(copy_buffer(&field, sizeof(lv_obj_type_t)))
#define mp_read_byref_lv_obj_type_t(field) mp_read_ptr_lv_obj_type_t(&field)

STATIC void mp_lv_obj_type_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_obj_type_t *data = (lv_obj_type_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_type: dest[0] = ptr_to_mp(&data->type); break; // converting from char *[8];
            default: field_not_found(MP_QSTR_lv_obj_type_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_type: memcpy(&data->type, mp_to_ptr(dest[1]), sizeof(const char *)*8); break; // converting to char *[8];
                default: field_not_found(MP_QSTR_lv_obj_type_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_obj_type_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_obj_type_t");
}

STATIC const mp_rom_map_elem_t mp_lv_obj_type_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_obj_type_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_obj_type_t_locals_dict, mp_lv_obj_type_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_obj_type_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_obj_type_t,
    .print = mp_lv_obj_type_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_obj_type_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_obj_type_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_obj_type_t_type()
{
    return &mp_lv_obj_type_t_type;
}
    

/*
 * lvgl extension definition for:
 * void lv_obj_get_type(lv_obj_t *obj, lv_obj_type_t *buf)
 */
 
STATIC mp_obj_t mp_lv_obj_get_type(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_type_t *buf = mp_to_ptr(args[1]);
    lv_obj_get_type(obj, buf);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_type_obj, 2, 2, mp_lv_obj_get_type);

 

/*
 * lvgl extension definition for:
 * lv_obj_user_data_t lv_obj_get_user_data(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_user_data(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_user_data_t res = lv_obj_get_user_data(obj);
    return ptr_to_mp(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_user_data_obj, 1, 1, mp_lv_obj_get_user_data);

 

/*
 * lvgl extension definition for:
 * lv_obj_user_data_t *lv_obj_get_user_data_ptr(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_user_data_ptr(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_user_data_t * res = lv_obj_get_user_data_ptr(obj);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_user_data_ptr_obj, 1, 1, mp_lv_obj_get_user_data_ptr);

 

/*
 * lvgl extension definition for:
 * void lv_obj_set_user_data(lv_obj_t *obj, lv_obj_user_data_t data)
 */
 
STATIC mp_obj_t mp_lv_obj_set_user_data(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_obj_user_data_t data = mp_to_ptr(args[1]);
    lv_obj_set_user_data(obj, data);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_set_user_data_obj, 2, 2, mp_lv_obj_set_user_data);

 

/*
 * lvgl extension definition for:
 * void *lv_obj_get_group(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_get_group(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    void * res = lv_obj_get_group(obj);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_get_group_obj, 1, 1, mp_lv_obj_get_group);

 

/*
 * lvgl extension definition for:
 * bool lv_obj_is_focused(const lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_obj_is_focused(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *obj = mp_to_lv(args[0]);
    bool res = lv_obj_is_focused(obj);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_obj_is_focused_obj, 1, 1, mp_lv_obj_is_focused);

 

/*
 * lvgl obj object definitions
 */
    

STATIC const mp_rom_map_elem_t obj_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) }
};

STATIC MP_DEFINE_CONST_DICT(obj_locals_dict, obj_locals_dict_table);

STATIC void obj_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl obj");
}


STATIC mp_obj_t obj_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_obj_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_obj_type = {
    { &mp_type_type },
    .name = MP_QSTR_obj,
    .print = obj_print,
    .make_new = obj_make_new,
    .locals_dict = (mp_obj_dict_t*)&obj_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_cont_set_fit2(lv_obj_t *cont, lv_fit_t hor, lv_fit_t ver)
 */
 
STATIC mp_obj_t mp_lv_cont_set_fit2(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *cont = mp_to_lv(args[0]);
    lv_fit_t hor = (uint8_t)mp_obj_get_int(args[1]);
    lv_fit_t ver = (uint8_t)mp_obj_get_int(args[2]);
    lv_cont_set_fit2(cont, hor, ver);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cont_set_fit2_obj, 3, 3, mp_lv_cont_set_fit2);

 

/*
 * lvgl extension definition for:
 * inline static void lv_cont_set_fit(lv_obj_t *cont, lv_fit_t fit)
 */
 
STATIC mp_obj_t mp_lv_cont_set_fit(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *cont = mp_to_lv(args[0]);
    lv_fit_t fit = (uint8_t)mp_obj_get_int(args[1]);
    lv_cont_set_fit(cont, fit);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cont_set_fit_obj, 2, 2, mp_lv_cont_set_fit);

 

/*
 * lvgl extension definition for:
 * inline static void lv_cont_set_style(lv_obj_t *cont, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_cont_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *cont = mp_to_lv(args[0]);
    const lv_style_t *style = mp_to_ptr(args[1]);
    lv_cont_set_style(cont, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cont_set_style_obj, 2, 2, mp_lv_cont_set_style);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * inline static const lv_style_t *lv_cont_get_style(const lv_obj_t *cont)
 */
    

/*
 * lvgl extension definition for:
 * void lv_cont_set_layout(lv_obj_t *cont, lv_layout_t layout)
 */
 
STATIC mp_obj_t mp_lv_cont_set_layout(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *cont = mp_to_lv(args[0]);
    lv_layout_t layout = (uint8_t)mp_obj_get_int(args[1]);
    lv_cont_set_layout(cont, layout);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cont_set_layout_obj, 2, 2, mp_lv_cont_set_layout);

 

/*
 * lvgl extension definition for:
 * void lv_cont_set_fit4(lv_obj_t *cont, lv_fit_t left, lv_fit_t right, lv_fit_t top, lv_fit_t bottom)
 */
 
STATIC mp_obj_t mp_lv_cont_set_fit4(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *cont = mp_to_lv(args[0]);
    lv_fit_t left = (uint8_t)mp_obj_get_int(args[1]);
    lv_fit_t right = (uint8_t)mp_obj_get_int(args[2]);
    lv_fit_t top = (uint8_t)mp_obj_get_int(args[3]);
    lv_fit_t bottom = (uint8_t)mp_obj_get_int(args[4]);
    lv_cont_set_fit4(cont, left, right, top, bottom);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cont_set_fit4_obj, 5, 5, mp_lv_cont_set_fit4);

 

/*
 * lvgl extension definition for:
 * lv_layout_t lv_cont_get_layout(const lv_obj_t *cont)
 */
 
STATIC mp_obj_t mp_lv_cont_get_layout(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *cont = mp_to_lv(args[0]);
    lv_layout_t res = lv_cont_get_layout(cont);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cont_get_layout_obj, 1, 1, mp_lv_cont_get_layout);

 

/*
 * lvgl extension definition for:
 * lv_fit_t lv_cont_get_fit_left(const lv_obj_t *cont)
 */
 
STATIC mp_obj_t mp_lv_cont_get_fit_left(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *cont = mp_to_lv(args[0]);
    lv_fit_t res = lv_cont_get_fit_left(cont);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cont_get_fit_left_obj, 1, 1, mp_lv_cont_get_fit_left);

 

/*
 * lvgl extension definition for:
 * lv_fit_t lv_cont_get_fit_right(const lv_obj_t *cont)
 */
 
STATIC mp_obj_t mp_lv_cont_get_fit_right(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *cont = mp_to_lv(args[0]);
    lv_fit_t res = lv_cont_get_fit_right(cont);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cont_get_fit_right_obj, 1, 1, mp_lv_cont_get_fit_right);

 

/*
 * lvgl extension definition for:
 * lv_fit_t lv_cont_get_fit_top(const lv_obj_t *cont)
 */
 
STATIC mp_obj_t mp_lv_cont_get_fit_top(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *cont = mp_to_lv(args[0]);
    lv_fit_t res = lv_cont_get_fit_top(cont);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cont_get_fit_top_obj, 1, 1, mp_lv_cont_get_fit_top);

 

/*
 * lvgl extension definition for:
 * lv_fit_t lv_cont_get_fit_bottom(const lv_obj_t *cont)
 */
 
STATIC mp_obj_t mp_lv_cont_get_fit_bottom(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *cont = mp_to_lv(args[0]);
    lv_fit_t res = lv_cont_get_fit_bottom(cont);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cont_get_fit_bottom_obj, 1, 1, mp_lv_cont_get_fit_bottom);

 

/*
 * lvgl cont object definitions
 */
    

STATIC const mp_rom_map_elem_t cont_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_fit2), MP_ROM_PTR(&mp_lv_cont_set_fit2_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_fit), MP_ROM_PTR(&mp_lv_cont_set_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_cont_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_layout), MP_ROM_PTR(&mp_lv_cont_set_layout_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_fit4), MP_ROM_PTR(&mp_lv_cont_set_fit4_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_layout), MP_ROM_PTR(&mp_lv_cont_get_layout_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_fit_left), MP_ROM_PTR(&mp_lv_cont_get_fit_left_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_fit_right), MP_ROM_PTR(&mp_lv_cont_get_fit_right_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_fit_top), MP_ROM_PTR(&mp_lv_cont_get_fit_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_fit_bottom), MP_ROM_PTR(&mp_lv_cont_get_fit_bottom_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) }
};

STATIC MP_DEFINE_CONST_DICT(cont_locals_dict, cont_locals_dict_table);

STATIC void cont_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl cont");
}


STATIC mp_obj_t cont_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_cont_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_cont_type = {
    { &mp_type_type },
    .name = MP_QSTR_cont,
    .print = cont_print,
    .make_new = cont_make_new,
    .locals_dict = (mp_obj_dict_t*)&cont_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_btn_set_layout(lv_obj_t *btn, lv_layout_t layout)
 */
 
STATIC mp_obj_t mp_lv_btn_set_layout(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btn = mp_to_lv(args[0]);
    lv_layout_t layout = (uint8_t)mp_obj_get_int(args[1]);
    lv_btn_set_layout(btn, layout);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_set_layout_obj, 2, 2, mp_lv_btn_set_layout);

 

/*
 * lvgl extension definition for:
 * inline static void lv_btn_set_fit4(lv_obj_t *btn, lv_fit_t left, lv_fit_t right, lv_fit_t top, lv_fit_t bottom)
 */
 
STATIC mp_obj_t mp_lv_btn_set_fit4(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btn = mp_to_lv(args[0]);
    lv_fit_t left = (uint8_t)mp_obj_get_int(args[1]);
    lv_fit_t right = (uint8_t)mp_obj_get_int(args[2]);
    lv_fit_t top = (uint8_t)mp_obj_get_int(args[3]);
    lv_fit_t bottom = (uint8_t)mp_obj_get_int(args[4]);
    lv_btn_set_fit4(btn, left, right, top, bottom);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_set_fit4_obj, 5, 5, mp_lv_btn_set_fit4);

 

/*
 * lvgl extension definition for:
 * inline static void lv_btn_set_fit2(lv_obj_t *btn, lv_fit_t hor, lv_fit_t ver)
 */
 
STATIC mp_obj_t mp_lv_btn_set_fit2(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btn = mp_to_lv(args[0]);
    lv_fit_t hor = (uint8_t)mp_obj_get_int(args[1]);
    lv_fit_t ver = (uint8_t)mp_obj_get_int(args[2]);
    lv_btn_set_fit2(btn, hor, ver);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_set_fit2_obj, 3, 3, mp_lv_btn_set_fit2);

 

/*
 * lvgl extension definition for:
 * inline static void lv_btn_set_fit(lv_obj_t *cont, lv_fit_t fit)
 */
 
STATIC mp_obj_t mp_lv_btn_set_fit(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *cont = mp_to_lv(args[0]);
    lv_fit_t fit = (uint8_t)mp_obj_get_int(args[1]);
    lv_btn_set_fit(cont, fit);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_set_fit_obj, 2, 2, mp_lv_btn_set_fit);

 

/*
 * lvgl extension definition for:
 * inline static lv_layout_t lv_btn_get_layout(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_btn_get_layout(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    lv_layout_t res = lv_btn_get_layout(btn);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_get_layout_obj, 1, 1, mp_lv_btn_get_layout);

 

/*
 * lvgl extension definition for:
 * inline static lv_fit_t lv_btn_get_fit_left(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_btn_get_fit_left(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    lv_fit_t res = lv_btn_get_fit_left(btn);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_get_fit_left_obj, 1, 1, mp_lv_btn_get_fit_left);

 

/*
 * lvgl extension definition for:
 * inline static lv_fit_t lv_btn_get_fit_right(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_btn_get_fit_right(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    lv_fit_t res = lv_btn_get_fit_right(btn);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_get_fit_right_obj, 1, 1, mp_lv_btn_get_fit_right);

 

/*
 * lvgl extension definition for:
 * inline static lv_fit_t lv_btn_get_fit_top(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_btn_get_fit_top(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    lv_fit_t res = lv_btn_get_fit_top(btn);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_get_fit_top_obj, 1, 1, mp_lv_btn_get_fit_top);

 

/*
 * lvgl extension definition for:
 * inline static lv_fit_t lv_btn_get_fit_bottom(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_btn_get_fit_bottom(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    lv_fit_t res = lv_btn_get_fit_bottom(btn);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_get_fit_bottom_obj, 1, 1, mp_lv_btn_get_fit_bottom);

 

/*
 * lvgl extension definition for:
 * void lv_btn_set_toggle(lv_obj_t *btn, bool tgl)
 */
 
STATIC mp_obj_t mp_lv_btn_set_toggle(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btn = mp_to_lv(args[0]);
    bool tgl = mp_obj_is_true(args[1]);
    lv_btn_set_toggle(btn, tgl);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_set_toggle_obj, 2, 2, mp_lv_btn_set_toggle);

 

/*
 * lvgl extension definition for:
 * void lv_btn_set_state(lv_obj_t *btn, lv_btn_state_t state)
 */
 
STATIC mp_obj_t mp_lv_btn_set_state(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btn = mp_to_lv(args[0]);
    lv_btn_state_t state = (uint8_t)mp_obj_get_int(args[1]);
    lv_btn_set_state(btn, state);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_set_state_obj, 2, 2, mp_lv_btn_set_state);

 

/*
 * lvgl extension definition for:
 * void lv_btn_toggle(lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_btn_toggle(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btn = mp_to_lv(args[0]);
    lv_btn_toggle(btn);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_toggle_obj, 1, 1, mp_lv_btn_toggle);

 

/*
 * lvgl extension definition for:
 * void lv_btn_set_ink_in_time(lv_obj_t *btn, uint16_t time)
 */
 
STATIC mp_obj_t mp_lv_btn_set_ink_in_time(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btn = mp_to_lv(args[0]);
    uint16_t time = (uint16_t)mp_obj_get_int(args[1]);
    lv_btn_set_ink_in_time(btn, time);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_set_ink_in_time_obj, 2, 2, mp_lv_btn_set_ink_in_time);

 

/*
 * lvgl extension definition for:
 * void lv_btn_set_ink_wait_time(lv_obj_t *btn, uint16_t time)
 */
 
STATIC mp_obj_t mp_lv_btn_set_ink_wait_time(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btn = mp_to_lv(args[0]);
    uint16_t time = (uint16_t)mp_obj_get_int(args[1]);
    lv_btn_set_ink_wait_time(btn, time);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_set_ink_wait_time_obj, 2, 2, mp_lv_btn_set_ink_wait_time);

 

/*
 * lvgl extension definition for:
 * void lv_btn_set_ink_out_time(lv_obj_t *btn, uint16_t time)
 */
 
STATIC mp_obj_t mp_lv_btn_set_ink_out_time(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btn = mp_to_lv(args[0]);
    uint16_t time = (uint16_t)mp_obj_get_int(args[1]);
    lv_btn_set_ink_out_time(btn, time);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_set_ink_out_time_obj, 2, 2, mp_lv_btn_set_ink_out_time);

 

/*
 * lvgl extension definition for:
 * void lv_btn_set_style(lv_obj_t *btn, lv_btn_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_btn_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btn = mp_to_lv(args[0]);
    lv_btn_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_btn_set_style(btn, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_set_style_obj, 3, 3, mp_lv_btn_set_style);

 

/*
 * lvgl extension definition for:
 * lv_btn_state_t lv_btn_get_state(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_btn_get_state(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    lv_btn_state_t res = lv_btn_get_state(btn);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_get_state_obj, 1, 1, mp_lv_btn_get_state);

 

/*
 * lvgl extension definition for:
 * bool lv_btn_get_toggle(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_btn_get_toggle(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    bool res = lv_btn_get_toggle(btn);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_get_toggle_obj, 1, 1, mp_lv_btn_get_toggle);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_btn_get_ink_in_time(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_btn_get_ink_in_time(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    uint16_t res = lv_btn_get_ink_in_time(btn);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_get_ink_in_time_obj, 1, 1, mp_lv_btn_get_ink_in_time);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_btn_get_ink_wait_time(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_btn_get_ink_wait_time(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    uint16_t res = lv_btn_get_ink_wait_time(btn);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_get_ink_wait_time_obj, 1, 1, mp_lv_btn_get_ink_wait_time);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_btn_get_ink_out_time(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_btn_get_ink_out_time(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    uint16_t res = lv_btn_get_ink_out_time(btn);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btn_get_ink_out_time_obj, 1, 1, mp_lv_btn_get_ink_out_time);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_btn_get_style(const lv_obj_t *btn, lv_btn_style_t type)
 */
    

/*
 * lvgl btn object definitions
 */
    

STATIC const mp_rom_map_elem_t btn_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_layout), MP_ROM_PTR(&mp_lv_btn_set_layout_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_fit4), MP_ROM_PTR(&mp_lv_btn_set_fit4_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_fit2), MP_ROM_PTR(&mp_lv_btn_set_fit2_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_fit), MP_ROM_PTR(&mp_lv_btn_set_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_layout), MP_ROM_PTR(&mp_lv_btn_get_layout_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_fit_left), MP_ROM_PTR(&mp_lv_btn_get_fit_left_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_fit_right), MP_ROM_PTR(&mp_lv_btn_get_fit_right_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_fit_top), MP_ROM_PTR(&mp_lv_btn_get_fit_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_fit_bottom), MP_ROM_PTR(&mp_lv_btn_get_fit_bottom_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_toggle), MP_ROM_PTR(&mp_lv_btn_set_toggle_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_state), MP_ROM_PTR(&mp_lv_btn_set_state_obj) },
    { MP_ROM_QSTR(MP_QSTR_toggle), MP_ROM_PTR(&mp_lv_btn_toggle_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_ink_in_time), MP_ROM_PTR(&mp_lv_btn_set_ink_in_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_ink_wait_time), MP_ROM_PTR(&mp_lv_btn_set_ink_wait_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_ink_out_time), MP_ROM_PTR(&mp_lv_btn_set_ink_out_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_btn_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_state), MP_ROM_PTR(&mp_lv_btn_get_state_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_toggle), MP_ROM_PTR(&mp_lv_btn_get_toggle_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ink_in_time), MP_ROM_PTR(&mp_lv_btn_get_ink_in_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ink_wait_time), MP_ROM_PTR(&mp_lv_btn_get_ink_wait_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ink_out_time), MP_ROM_PTR(&mp_lv_btn_get_ink_out_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STATE), MP_ROM_PTR(&mp_LV_BTN_STATE_type) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_BTN_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(btn_locals_dict, btn_locals_dict_table);

STATIC void btn_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl btn");
}


STATIC mp_obj_t btn_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_btn_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_btn_type = {
    { &mp_type_type },
    .name = MP_QSTR_btn,
    .print = btn_print,
    .make_new = btn_make_new,
    .locals_dict = (mp_obj_dict_t*)&btn_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_imgbtn_set_toggle(lv_obj_t *imgbtn, bool tgl)
 */
 
STATIC mp_obj_t mp_lv_imgbtn_set_toggle(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *imgbtn = mp_to_lv(args[0]);
    bool tgl = mp_obj_is_true(args[1]);
    lv_imgbtn_set_toggle(imgbtn, tgl);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_imgbtn_set_toggle_obj, 2, 2, mp_lv_imgbtn_set_toggle);

 

/*
 * lvgl extension definition for:
 * inline static void lv_imgbtn_set_state(lv_obj_t *imgbtn, lv_btn_state_t state)
 */
 
STATIC mp_obj_t mp_lv_imgbtn_set_state(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *imgbtn = mp_to_lv(args[0]);
    lv_btn_state_t state = (uint8_t)mp_obj_get_int(args[1]);
    lv_imgbtn_set_state(imgbtn, state);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_imgbtn_set_state_obj, 2, 2, mp_lv_imgbtn_set_state);

 

/*
 * lvgl extension definition for:
 * inline static void lv_imgbtn_toggle(lv_obj_t *imgbtn)
 */
 
STATIC mp_obj_t mp_lv_imgbtn_toggle(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *imgbtn = mp_to_lv(args[0]);
    lv_imgbtn_toggle(imgbtn);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_imgbtn_toggle_obj, 1, 1, mp_lv_imgbtn_toggle);

 

/*
 * lvgl extension definition for:
 * inline static lv_btn_state_t lv_imgbtn_get_state(const lv_obj_t *imgbtn)
 */
 
STATIC mp_obj_t mp_lv_imgbtn_get_state(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *imgbtn = mp_to_lv(args[0]);
    lv_btn_state_t res = lv_imgbtn_get_state(imgbtn);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_imgbtn_get_state_obj, 1, 1, mp_lv_imgbtn_get_state);

 

/*
 * lvgl extension definition for:
 * inline static bool lv_imgbtn_get_toggle(const lv_obj_t *imgbtn)
 */
 
STATIC mp_obj_t mp_lv_imgbtn_get_toggle(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *imgbtn = mp_to_lv(args[0]);
    bool res = lv_imgbtn_get_toggle(imgbtn);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_imgbtn_get_toggle_obj, 1, 1, mp_lv_imgbtn_get_toggle);

 

/*
 * lvgl extension definition for:
 * void lv_imgbtn_set_src(lv_obj_t *imgbtn, lv_btn_state_t state, const void *src)
 */
 
STATIC mp_obj_t mp_lv_imgbtn_set_src(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *imgbtn = mp_to_lv(args[0]);
    lv_btn_state_t state = (uint8_t)mp_obj_get_int(args[1]);
    const void *src = mp_to_ptr(args[2]);
    lv_imgbtn_set_src(imgbtn, state, src);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_imgbtn_set_src_obj, 3, 3, mp_lv_imgbtn_set_src);

 

/*
 * lvgl extension definition for:
 * void lv_imgbtn_set_style(lv_obj_t *imgbtn, lv_imgbtn_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_imgbtn_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *imgbtn = mp_to_lv(args[0]);
    lv_imgbtn_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_imgbtn_set_style(imgbtn, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_imgbtn_set_style_obj, 3, 3, mp_lv_imgbtn_set_style);

 

/*
 * lvgl extension definition for:
 * const void *lv_imgbtn_get_src(lv_obj_t *imgbtn, lv_btn_state_t state)
 */
 
STATIC mp_obj_t mp_lv_imgbtn_get_src(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *imgbtn = mp_to_lv(args[0]);
    lv_btn_state_t state = (uint8_t)mp_obj_get_int(args[1]);
    const void * res = lv_imgbtn_get_src(imgbtn, state);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_imgbtn_get_src_obj, 2, 2, mp_lv_imgbtn_get_src);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_imgbtn_get_style(const lv_obj_t *imgbtn, lv_imgbtn_style_t type)
 */
    

/*
 * lvgl imgbtn object definitions
 */
    

STATIC const mp_rom_map_elem_t imgbtn_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_toggle), MP_ROM_PTR(&mp_lv_imgbtn_set_toggle_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_state), MP_ROM_PTR(&mp_lv_imgbtn_set_state_obj) },
    { MP_ROM_QSTR(MP_QSTR_toggle), MP_ROM_PTR(&mp_lv_imgbtn_toggle_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_state), MP_ROM_PTR(&mp_lv_imgbtn_get_state_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_toggle), MP_ROM_PTR(&mp_lv_imgbtn_get_toggle_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_src), MP_ROM_PTR(&mp_lv_imgbtn_set_src_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_imgbtn_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_src), MP_ROM_PTR(&mp_lv_imgbtn_get_src_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_IMGBTN_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(imgbtn_locals_dict, imgbtn_locals_dict_table);

STATIC void imgbtn_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl imgbtn");
}


STATIC mp_obj_t imgbtn_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_imgbtn_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_imgbtn_type = {
    { &mp_type_type },
    .name = MP_QSTR_imgbtn,
    .print = imgbtn_print,
    .make_new = imgbtn_make_new,
    .locals_dict = (mp_obj_dict_t*)&imgbtn_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_label_set_style(lv_obj_t *label, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_label_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    const lv_style_t *style = mp_to_ptr(args[1]);
    lv_label_set_style(label, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_set_style_obj, 2, 2, mp_lv_label_set_style);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * inline static const lv_style_t *lv_label_get_style(const lv_obj_t *label)
 */
    

/*
 * lvgl extension definition for:
 * void lv_label_set_text(lv_obj_t *label, const char *text)
 */
 
STATIC mp_obj_t mp_lv_label_set_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    const char *text = (char*)mp_obj_str_get_str(args[1]);
    lv_label_set_text(label, text);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_set_text_obj, 2, 2, mp_lv_label_set_text);

 

/*
 * lvgl extension definition for:
 * void lv_label_set_array_text(lv_obj_t *label, const char *array, uint16_t size)
 */
 
STATIC mp_obj_t mp_lv_label_set_array_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    const char *array = (char*)mp_obj_str_get_str(args[1]);
    uint16_t size = (uint16_t)mp_obj_get_int(args[2]);
    lv_label_set_array_text(label, array, size);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_set_array_text_obj, 3, 3, mp_lv_label_set_array_text);

 

/*
 * lvgl extension definition for:
 * void lv_label_set_static_text(lv_obj_t *label, const char *text)
 */
 
STATIC mp_obj_t mp_lv_label_set_static_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    const char *text = (char*)mp_obj_str_get_str(args[1]);
    lv_label_set_static_text(label, text);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_set_static_text_obj, 2, 2, mp_lv_label_set_static_text);

 

/*
 * lvgl extension definition for:
 * void lv_label_set_long_mode(lv_obj_t *label, lv_label_long_mode_t long_mode)
 */
 
STATIC mp_obj_t mp_lv_label_set_long_mode(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    lv_label_long_mode_t long_mode = (uint8_t)mp_obj_get_int(args[1]);
    lv_label_set_long_mode(label, long_mode);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_set_long_mode_obj, 2, 2, mp_lv_label_set_long_mode);

 

/*
 * lvgl extension definition for:
 * void lv_label_set_align(lv_obj_t *label, lv_label_align_t align)
 */
 
STATIC mp_obj_t mp_lv_label_set_align(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    lv_label_align_t align = (uint8_t)mp_obj_get_int(args[1]);
    lv_label_set_align(label, align);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_set_align_obj, 2, 2, mp_lv_label_set_align);

 

/*
 * lvgl extension definition for:
 * void lv_label_set_recolor(lv_obj_t *label, bool en)
 */
 
STATIC mp_obj_t mp_lv_label_set_recolor(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_label_set_recolor(label, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_set_recolor_obj, 2, 2, mp_lv_label_set_recolor);

 

/*
 * lvgl extension definition for:
 * void lv_label_set_body_draw(lv_obj_t *label, bool en)
 */
 
STATIC mp_obj_t mp_lv_label_set_body_draw(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_label_set_body_draw(label, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_set_body_draw_obj, 2, 2, mp_lv_label_set_body_draw);

 

/*
 * lvgl extension definition for:
 * void lv_label_set_anim_speed(lv_obj_t *label, uint16_t anim_speed)
 */
 
STATIC mp_obj_t mp_lv_label_set_anim_speed(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    uint16_t anim_speed = (uint16_t)mp_obj_get_int(args[1]);
    lv_label_set_anim_speed(label, anim_speed);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_set_anim_speed_obj, 2, 2, mp_lv_label_set_anim_speed);

 

/*
 * lvgl extension definition for:
 * void lv_label_set_text_sel_start(lv_obj_t *label, uint16_t index)
 */
 
STATIC mp_obj_t mp_lv_label_set_text_sel_start(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    uint16_t index = (uint16_t)mp_obj_get_int(args[1]);
    lv_label_set_text_sel_start(label, index);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_set_text_sel_start_obj, 2, 2, mp_lv_label_set_text_sel_start);

 

/*
 * lvgl extension definition for:
 * void lv_label_set_text_sel_end(lv_obj_t *label, uint16_t index)
 */
 
STATIC mp_obj_t mp_lv_label_set_text_sel_end(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    uint16_t index = (uint16_t)mp_obj_get_int(args[1]);
    lv_label_set_text_sel_end(label, index);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_set_text_sel_end_obj, 2, 2, mp_lv_label_set_text_sel_end);

 

/*
 * lvgl extension definition for:
 * char *lv_label_get_text(const lv_obj_t *label)
 */
 
STATIC mp_obj_t mp_lv_label_get_text(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *label = mp_to_lv(args[0]);
    char * res = lv_label_get_text(label);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_get_text_obj, 1, 1, mp_lv_label_get_text);

 

/*
 * lvgl extension definition for:
 * lv_label_long_mode_t lv_label_get_long_mode(const lv_obj_t *label)
 */
 
STATIC mp_obj_t mp_lv_label_get_long_mode(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *label = mp_to_lv(args[0]);
    lv_label_long_mode_t res = lv_label_get_long_mode(label);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_get_long_mode_obj, 1, 1, mp_lv_label_get_long_mode);

 

/*
 * lvgl extension definition for:
 * lv_label_align_t lv_label_get_align(const lv_obj_t *label)
 */
 
STATIC mp_obj_t mp_lv_label_get_align(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *label = mp_to_lv(args[0]);
    lv_label_align_t res = lv_label_get_align(label);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_get_align_obj, 1, 1, mp_lv_label_get_align);

 

/*
 * lvgl extension definition for:
 * bool lv_label_get_recolor(const lv_obj_t *label)
 */
 
STATIC mp_obj_t mp_lv_label_get_recolor(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *label = mp_to_lv(args[0]);
    bool res = lv_label_get_recolor(label);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_get_recolor_obj, 1, 1, mp_lv_label_get_recolor);

 

/*
 * lvgl extension definition for:
 * bool lv_label_get_body_draw(const lv_obj_t *label)
 */
 
STATIC mp_obj_t mp_lv_label_get_body_draw(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *label = mp_to_lv(args[0]);
    bool res = lv_label_get_body_draw(label);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_get_body_draw_obj, 1, 1, mp_lv_label_get_body_draw);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_label_get_anim_speed(const lv_obj_t *label)
 */
 
STATIC mp_obj_t mp_lv_label_get_anim_speed(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *label = mp_to_lv(args[0]);
    uint16_t res = lv_label_get_anim_speed(label);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_get_anim_speed_obj, 1, 1, mp_lv_label_get_anim_speed);

 

/*
 * Struct lv_point_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_point_t_type();

STATIC inline lv_point_t* mp_write_ptr_lv_point_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_point_t_type()));
    return (lv_point_t*)self->data;
}

#define mp_write_lv_point_t(struct_obj) *mp_write_ptr_lv_point_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_point_t(lv_point_t *field)
{
    return lv_to_mp_struct(get_mp_lv_point_t_type(), field);
}

#define mp_read_lv_point_t(field) mp_read_ptr_lv_point_t(copy_buffer(&field, sizeof(lv_point_t)))
#define mp_read_byref_lv_point_t(field) mp_read_ptr_lv_point_t(&field)

STATIC void mp_lv_point_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_point_t *data = (lv_point_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_x: dest[0] = mp_obj_new_int(data->x); break; // converting from lv_coord_t;
            case MP_QSTR_y: dest[0] = mp_obj_new_int(data->y); break; // converting from lv_coord_t;
            default: field_not_found(MP_QSTR_lv_point_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_x: data->x = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                case MP_QSTR_y: data->y = (int16_t)mp_obj_get_int(dest[1]); break; // converting to lv_coord_t;
                default: field_not_found(MP_QSTR_lv_point_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_point_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_point_t");
}

STATIC const mp_rom_map_elem_t mp_lv_point_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_point_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_point_t_locals_dict, mp_lv_point_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_point_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_point_t,
    .print = mp_lv_point_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_point_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_point_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_point_t_type()
{
    return &mp_lv_point_t_type;
}
    

/*
 * lvgl extension definition for:
 * void lv_label_get_letter_pos(const lv_obj_t *label, uint16_t index, lv_point_t *pos)
 */
 
STATIC mp_obj_t mp_lv_label_get_letter_pos(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *label = mp_to_lv(args[0]);
    uint16_t index = (uint16_t)mp_obj_get_int(args[1]);
    lv_point_t *pos = mp_to_ptr(args[2]);
    lv_label_get_letter_pos(label, index, pos);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_get_letter_pos_obj, 3, 3, mp_lv_label_get_letter_pos);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_label_get_letter_on(const lv_obj_t *label, lv_point_t *pos)
 */
 
STATIC mp_obj_t mp_lv_label_get_letter_on(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *label = mp_to_lv(args[0]);
    lv_point_t *pos = mp_to_ptr(args[1]);
    uint16_t res = lv_label_get_letter_on(label, pos);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_get_letter_on_obj, 2, 2, mp_lv_label_get_letter_on);

 

/*
 * lvgl extension definition for:
 * bool lv_label_is_char_under_pos(const lv_obj_t *label, lv_point_t *pos)
 */
 
STATIC mp_obj_t mp_lv_label_is_char_under_pos(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *label = mp_to_lv(args[0]);
    lv_point_t *pos = mp_to_ptr(args[1]);
    bool res = lv_label_is_char_under_pos(label, pos);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_is_char_under_pos_obj, 2, 2, mp_lv_label_is_char_under_pos);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_label_get_text_sel_start(const lv_obj_t *label)
 */
 
STATIC mp_obj_t mp_lv_label_get_text_sel_start(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *label = mp_to_lv(args[0]);
    uint16_t res = lv_label_get_text_sel_start(label);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_get_text_sel_start_obj, 1, 1, mp_lv_label_get_text_sel_start);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_label_get_text_sel_end(const lv_obj_t *label)
 */
 
STATIC mp_obj_t mp_lv_label_get_text_sel_end(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *label = mp_to_lv(args[0]);
    uint16_t res = lv_label_get_text_sel_end(label);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_get_text_sel_end_obj, 1, 1, mp_lv_label_get_text_sel_end);

 

/*
 * lvgl extension definition for:
 * void lv_label_ins_text(lv_obj_t *label, uint32_t pos, const char *txt)
 */
 
STATIC mp_obj_t mp_lv_label_ins_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    uint32_t pos = (uint32_t)mp_obj_get_int(args[1]);
    const char *txt = (char*)mp_obj_str_get_str(args[2]);
    lv_label_ins_text(label, pos, txt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_ins_text_obj, 3, 3, mp_lv_label_ins_text);

 

/*
 * lvgl extension definition for:
 * void lv_label_cut_text(lv_obj_t *label, uint32_t pos, uint32_t cnt)
 */
 
STATIC mp_obj_t mp_lv_label_cut_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *label = mp_to_lv(args[0]);
    uint32_t pos = (uint32_t)mp_obj_get_int(args[1]);
    uint32_t cnt = (uint32_t)mp_obj_get_int(args[2]);
    lv_label_cut_text(label, pos, cnt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_label_cut_text_obj, 3, 3, mp_lv_label_cut_text);

 

/*
 * lvgl label object definitions
 */
    

STATIC const mp_rom_map_elem_t label_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_label_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_text), MP_ROM_PTR(&mp_lv_label_set_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_array_text), MP_ROM_PTR(&mp_lv_label_set_array_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_static_text), MP_ROM_PTR(&mp_lv_label_set_static_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_long_mode), MP_ROM_PTR(&mp_lv_label_set_long_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_align), MP_ROM_PTR(&mp_lv_label_set_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_recolor), MP_ROM_PTR(&mp_lv_label_set_recolor_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_body_draw), MP_ROM_PTR(&mp_lv_label_set_body_draw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_anim_speed), MP_ROM_PTR(&mp_lv_label_set_anim_speed_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_text_sel_start), MP_ROM_PTR(&mp_lv_label_set_text_sel_start_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_text_sel_end), MP_ROM_PTR(&mp_lv_label_set_text_sel_end_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_text), MP_ROM_PTR(&mp_lv_label_get_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_long_mode), MP_ROM_PTR(&mp_lv_label_get_long_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_align), MP_ROM_PTR(&mp_lv_label_get_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_recolor), MP_ROM_PTR(&mp_lv_label_get_recolor_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_body_draw), MP_ROM_PTR(&mp_lv_label_get_body_draw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_anim_speed), MP_ROM_PTR(&mp_lv_label_get_anim_speed_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_letter_pos), MP_ROM_PTR(&mp_lv_label_get_letter_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_letter_on), MP_ROM_PTR(&mp_lv_label_get_letter_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_char_under_pos), MP_ROM_PTR(&mp_lv_label_is_char_under_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_text_sel_start), MP_ROM_PTR(&mp_lv_label_get_text_sel_start_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_text_sel_end), MP_ROM_PTR(&mp_lv_label_get_text_sel_end_obj) },
    { MP_ROM_QSTR(MP_QSTR_ins_text), MP_ROM_PTR(&mp_lv_label_ins_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_cut_text), MP_ROM_PTR(&mp_lv_label_cut_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_LONG), MP_ROM_PTR(&mp_LV_LABEL_LONG_type) },
    { MP_ROM_QSTR(MP_QSTR_ALIGN), MP_ROM_PTR(&mp_LV_LABEL_ALIGN_type) }
};

STATIC MP_DEFINE_CONST_DICT(label_locals_dict, label_locals_dict_table);

STATIC void label_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl label");
}


STATIC mp_obj_t label_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_label_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_label_type = {
    { &mp_type_type },
    .name = MP_QSTR_label,
    .print = label_print,
    .make_new = label_make_new,
    .locals_dict = (mp_obj_dict_t*)&label_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_img_set_file(lv_obj_t *img, const char *fn)
 */
 
STATIC mp_obj_t mp_lv_img_set_file(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *img = mp_to_lv(args[0]);
    const char *fn = (char*)mp_obj_str_get_str(args[1]);
    lv_img_set_file(img, fn);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_set_file_obj, 2, 2, mp_lv_img_set_file);

 

/*
 * lvgl extension definition for:
 * inline static void lv_img_set_style(lv_obj_t *img, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_img_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *img = mp_to_lv(args[0]);
    const lv_style_t *style = mp_to_ptr(args[1]);
    lv_img_set_style(img, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_set_style_obj, 2, 2, mp_lv_img_set_style);

 

/*
 * lvgl extension definition for:
 * inline static void lv_img_set_upscale(lv_obj_t *img, bool upcale)
 */
 
STATIC mp_obj_t mp_lv_img_set_upscale(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *img = mp_to_lv(args[0]);
    bool upcale = mp_obj_is_true(args[1]);
    lv_img_set_upscale(img, upcale);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_set_upscale_obj, 2, 2, mp_lv_img_set_upscale);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * inline static const lv_style_t *lv_img_get_style(const lv_obj_t *img)
 */
    

/*
 * lvgl extension definition for:
 * inline static bool lv_img_get_upscale(const lv_obj_t *img)
 */
 
STATIC mp_obj_t mp_lv_img_get_upscale(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *img = mp_to_lv(args[0]);
    bool res = lv_img_get_upscale(img);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_get_upscale_obj, 1, 1, mp_lv_img_get_upscale);

 

/*
 * Struct lv_img_header_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_img_header_t_type();

STATIC inline lv_img_header_t* mp_write_ptr_lv_img_header_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_img_header_t_type()));
    return (lv_img_header_t*)self->data;
}

#define mp_write_lv_img_header_t(struct_obj) *mp_write_ptr_lv_img_header_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_img_header_t(lv_img_header_t *field)
{
    return lv_to_mp_struct(get_mp_lv_img_header_t_type(), field);
}

#define mp_read_lv_img_header_t(field) mp_read_ptr_lv_img_header_t(copy_buffer(&field, sizeof(lv_img_header_t)))
#define mp_read_byref_lv_img_header_t(field) mp_read_ptr_lv_img_header_t(&field)

STATIC void mp_lv_img_header_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_img_header_t *data = (lv_img_header_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_cf: dest[0] = mp_obj_new_int_from_uint(data->cf); break; // converting from uint32_t;
            case MP_QSTR_always_zero: dest[0] = mp_obj_new_int_from_uint(data->always_zero); break; // converting from uint32_t;
            case MP_QSTR_reserved: dest[0] = mp_obj_new_int_from_uint(data->reserved); break; // converting from uint32_t;
            case MP_QSTR_w: dest[0] = mp_obj_new_int_from_uint(data->w); break; // converting from uint32_t;
            case MP_QSTR_h: dest[0] = mp_obj_new_int_from_uint(data->h); break; // converting from uint32_t;
            default: field_not_found(MP_QSTR_lv_img_header_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_cf: data->cf = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_always_zero: data->always_zero = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_reserved: data->reserved = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_w: data->w = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_h: data->h = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                default: field_not_found(MP_QSTR_lv_img_header_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_img_header_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_img_header_t");
}

STATIC const mp_rom_map_elem_t mp_lv_img_header_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_img_header_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_img_header_t_locals_dict, mp_lv_img_header_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_img_header_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_img_header_t,
    .print = mp_lv_img_header_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_img_header_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_img_header_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_img_header_t_type()
{
    return &mp_lv_img_header_t_type;
}
    

/*
 * lvgl extension definition for:
 * lv_res_t lv_img_dsc_get_info(const char *src, lv_img_header_t *header)
 */
 
STATIC mp_obj_t mp_lv_img_dsc_get_info(size_t n_args, const mp_obj_t *args)
{
    const char *src = (char*)mp_obj_str_get_str(args[0]);
    lv_img_header_t *header = mp_to_ptr(args[1]);
    lv_res_t res = lv_img_dsc_get_info(src, header);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_dsc_get_info_obj, 2, 2, mp_lv_img_dsc_get_info);

 

/*
 * lvgl extension definition for:
 * lv_img_src_t lv_img_src_get_type(const void *src)
 */
 
STATIC mp_obj_t mp_lv_img_src_get_type(size_t n_args, const mp_obj_t *args)
{
    const void *src = mp_to_ptr(args[0]);
    lv_img_src_t res = lv_img_src_get_type(src);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_src_get_type_obj, 1, 1, mp_lv_img_src_get_type);

 

/*
 * Function NOT generated:
 * Callback argument 'lv_img_decoder_info_f_t info_fp' cannot be the first argument! We assume the first argument contains the user_data
 * void lv_img_decoder_set_custom(lv_img_decoder_info_f_t info_fp, lv_img_decoder_open_f_t open_fp, lv_img_decoder_read_line_f_t read_fp, lv_img_decoder_close_f_t close_fp)
 */
    

/*
 * Struct lv_img_dsc_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_img_dsc_t_type();

STATIC inline lv_img_dsc_t* mp_write_ptr_lv_img_dsc_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_img_dsc_t_type()));
    return (lv_img_dsc_t*)self->data;
}

#define mp_write_lv_img_dsc_t(struct_obj) *mp_write_ptr_lv_img_dsc_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_img_dsc_t(lv_img_dsc_t *field)
{
    return lv_to_mp_struct(get_mp_lv_img_dsc_t_type(), field);
}

#define mp_read_lv_img_dsc_t(field) mp_read_ptr_lv_img_dsc_t(copy_buffer(&field, sizeof(lv_img_dsc_t)))
#define mp_read_byref_lv_img_dsc_t(field) mp_read_ptr_lv_img_dsc_t(&field)

STATIC void mp_lv_img_dsc_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_img_dsc_t *data = (lv_img_dsc_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_header: dest[0] = mp_read_byref_lv_img_header_t(data->header); break; // converting from lv_img_header_t;
            case MP_QSTR_data_size: dest[0] = mp_obj_new_int_from_uint(data->data_size); break; // converting from uint32_t;
            case MP_QSTR_data: dest[0] = ptr_to_mp((void*)data->data); break; // converting from uint8_t *;
            default: field_not_found(MP_QSTR_lv_img_dsc_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_header: data->header = mp_write_lv_img_header_t(dest[1]); break; // converting to lv_img_header_t;
                case MP_QSTR_data_size: data->data_size = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_data: data->data = (void*)mp_to_ptr(dest[1]); break; // converting to uint8_t *;
                default: field_not_found(MP_QSTR_lv_img_dsc_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_img_dsc_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_img_dsc_t");
}

STATIC const mp_rom_map_elem_t mp_lv_img_dsc_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_img_dsc_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_img_dsc_t_locals_dict, mp_lv_img_dsc_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_img_dsc_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_img_dsc_t,
    .print = mp_lv_img_dsc_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_img_dsc_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_img_dsc_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_img_dsc_t_type()
{
    return &mp_lv_img_dsc_t_type;
}
    

/*
 * lvgl extension definition for:
 * lv_color_t lv_img_buf_get_px_color(lv_img_dsc_t *dsc, lv_coord_t x, lv_coord_t y, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_img_buf_get_px_color(size_t n_args, const mp_obj_t *args)
{
    lv_img_dsc_t *dsc = mp_to_ptr(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    const lv_style_t *style = mp_to_ptr(args[3]);
    lv_color_t res = lv_img_buf_get_px_color(dsc, x, y, style);
    return mp_read_lv_color32_t(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_buf_get_px_color_obj, 4, 4, mp_lv_img_buf_get_px_color);

 

/*
 * lvgl extension definition for:
 * lv_opa_t lv_img_buf_get_px_alpha(lv_img_dsc_t *dsc, lv_coord_t x, lv_coord_t y)
 */
 
STATIC mp_obj_t mp_lv_img_buf_get_px_alpha(size_t n_args, const mp_obj_t *args)
{
    lv_img_dsc_t *dsc = mp_to_ptr(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    lv_opa_t res = lv_img_buf_get_px_alpha(dsc, x, y);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_buf_get_px_alpha_obj, 3, 3, mp_lv_img_buf_get_px_alpha);

 

/*
 * lvgl extension definition for:
 * void lv_img_buf_set_px_color(lv_img_dsc_t *dsc, lv_coord_t x, lv_coord_t y, lv_color_t c)
 */
 
STATIC mp_obj_t mp_lv_img_buf_set_px_color(size_t n_args, const mp_obj_t *args)
{
    lv_img_dsc_t *dsc = mp_to_ptr(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    lv_color_t c = mp_write_lv_color32_t(args[3]);
    lv_img_buf_set_px_color(dsc, x, y, c);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_buf_set_px_color_obj, 4, 4, mp_lv_img_buf_set_px_color);

 

/*
 * lvgl extension definition for:
 * void lv_img_buf_set_px_alpha(lv_img_dsc_t *dsc, lv_coord_t x, lv_coord_t y, lv_opa_t opa)
 */
 
STATIC mp_obj_t mp_lv_img_buf_set_px_alpha(size_t n_args, const mp_obj_t *args)
{
    lv_img_dsc_t *dsc = mp_to_ptr(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    lv_opa_t opa = (uint8_t)mp_obj_get_int(args[3]);
    lv_img_buf_set_px_alpha(dsc, x, y, opa);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_buf_set_px_alpha_obj, 4, 4, mp_lv_img_buf_set_px_alpha);

 

/*
 * lvgl extension definition for:
 * void lv_img_buf_set_palette(lv_img_dsc_t *dsc, int color_id, lv_color_t color)
 */
 
STATIC mp_obj_t mp_lv_img_buf_set_palette(size_t n_args, const mp_obj_t *args)
{
    lv_img_dsc_t *dsc = mp_to_ptr(args[0]);
    int color_id = (int)mp_obj_get_int(args[1]);
    lv_color_t color = mp_write_lv_color32_t(args[2]);
    lv_img_buf_set_palette(dsc, color_id, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_buf_set_palette_obj, 3, 3, mp_lv_img_buf_set_palette);

 

/*
 * lvgl extension definition for:
 * uint8_t lv_img_color_format_get_px_size(lv_img_cf_t cf)
 */
 
STATIC mp_obj_t mp_lv_img_color_format_get_px_size(size_t n_args, const mp_obj_t *args)
{
    lv_img_cf_t cf = (uint8_t)mp_obj_get_int(args[0]);
    uint8_t res = lv_img_color_format_get_px_size(cf);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_color_format_get_px_size_obj, 1, 1, mp_lv_img_color_format_get_px_size);

 

/*
 * lvgl extension definition for:
 * bool lv_img_color_format_is_chroma_keyed(lv_img_cf_t cf)
 */
 
STATIC mp_obj_t mp_lv_img_color_format_is_chroma_keyed(size_t n_args, const mp_obj_t *args)
{
    lv_img_cf_t cf = (uint8_t)mp_obj_get_int(args[0]);
    bool res = lv_img_color_format_is_chroma_keyed(cf);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_color_format_is_chroma_keyed_obj, 1, 1, mp_lv_img_color_format_is_chroma_keyed);

 

/*
 * lvgl extension definition for:
 * bool lv_img_color_format_has_alpha(lv_img_cf_t cf)
 */
 
STATIC mp_obj_t mp_lv_img_color_format_has_alpha(size_t n_args, const mp_obj_t *args)
{
    lv_img_cf_t cf = (uint8_t)mp_obj_get_int(args[0]);
    bool res = lv_img_color_format_has_alpha(cf);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_color_format_has_alpha_obj, 1, 1, mp_lv_img_color_format_has_alpha);

 

/*
 * lvgl extension definition for:
 * void lv_img_set_src(lv_obj_t *img, const void *src_img)
 */
 
STATIC mp_obj_t mp_lv_img_set_src(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *img = mp_to_lv(args[0]);
    const void *src_img = mp_to_ptr(args[1]);
    lv_img_set_src(img, src_img);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_set_src_obj, 2, 2, mp_lv_img_set_src);

 

/*
 * lvgl extension definition for:
 * void lv_img_set_auto_size(lv_obj_t *img, bool autosize_en)
 */
 
STATIC mp_obj_t mp_lv_img_set_auto_size(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *img = mp_to_lv(args[0]);
    bool autosize_en = mp_obj_is_true(args[1]);
    lv_img_set_auto_size(img, autosize_en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_set_auto_size_obj, 2, 2, mp_lv_img_set_auto_size);

 

/*
 * lvgl extension definition for:
 * void lv_img_set_offset(lv_obj_t *img, lv_coord_t x, lv_coord_t y)
 */
 
STATIC mp_obj_t mp_lv_img_set_offset(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *img = mp_to_lv(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    lv_img_set_offset(img, x, y);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_set_offset_obj, 3, 3, mp_lv_img_set_offset);

 

/*
 * lvgl extension definition for:
 * void lv_img_set_offset_x(lv_obj_t *img, lv_coord_t x)
 */
 
STATIC mp_obj_t mp_lv_img_set_offset_x(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *img = mp_to_lv(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_img_set_offset_x(img, x);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_set_offset_x_obj, 2, 2, mp_lv_img_set_offset_x);

 

/*
 * lvgl extension definition for:
 * void lv_img_set_offset_y(lv_obj_t *img, lv_coord_t y)
 */
 
STATIC mp_obj_t mp_lv_img_set_offset_y(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *img = mp_to_lv(args[0]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[1]);
    lv_img_set_offset_y(img, y);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_set_offset_y_obj, 2, 2, mp_lv_img_set_offset_y);

 

/*
 * lvgl extension definition for:
 * const void *lv_img_get_src(lv_obj_t *img)
 */
 
STATIC mp_obj_t mp_lv_img_get_src(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *img = mp_to_lv(args[0]);
    const void * res = lv_img_get_src(img);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_get_src_obj, 1, 1, mp_lv_img_get_src);

 

/*
 * lvgl extension definition for:
 * const char *lv_img_get_file_name(const lv_obj_t *img)
 */
 
STATIC mp_obj_t mp_lv_img_get_file_name(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *img = mp_to_lv(args[0]);
    const char * res = lv_img_get_file_name(img);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_get_file_name_obj, 1, 1, mp_lv_img_get_file_name);

 

/*
 * lvgl extension definition for:
 * bool lv_img_get_auto_size(const lv_obj_t *img)
 */
 
STATIC mp_obj_t mp_lv_img_get_auto_size(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *img = mp_to_lv(args[0]);
    bool res = lv_img_get_auto_size(img);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_get_auto_size_obj, 1, 1, mp_lv_img_get_auto_size);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_img_get_offset_x(lv_obj_t *img)
 */
 
STATIC mp_obj_t mp_lv_img_get_offset_x(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *img = mp_to_lv(args[0]);
    lv_coord_t res = lv_img_get_offset_x(img);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_get_offset_x_obj, 1, 1, mp_lv_img_get_offset_x);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_img_get_offset_y(lv_obj_t *img)
 */
 
STATIC mp_obj_t mp_lv_img_get_offset_y(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *img = mp_to_lv(args[0]);
    lv_coord_t res = lv_img_get_offset_y(img);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_img_get_offset_y_obj, 1, 1, mp_lv_img_get_offset_y);

 

/*
 * lvgl img object definitions
 */
    

STATIC const mp_rom_map_elem_t img_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_file), MP_ROM_PTR(&mp_lv_img_set_file_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_img_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_upscale), MP_ROM_PTR(&mp_lv_img_set_upscale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_upscale), MP_ROM_PTR(&mp_lv_img_get_upscale_obj) },
    { MP_ROM_QSTR(MP_QSTR_dsc_get_info), MP_ROM_PTR(&mp_lv_img_dsc_get_info_obj) },
    { MP_ROM_QSTR(MP_QSTR_src_get_type), MP_ROM_PTR(&mp_lv_img_src_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_buf_get_px_color), MP_ROM_PTR(&mp_lv_img_buf_get_px_color_obj) },
    { MP_ROM_QSTR(MP_QSTR_buf_get_px_alpha), MP_ROM_PTR(&mp_lv_img_buf_get_px_alpha_obj) },
    { MP_ROM_QSTR(MP_QSTR_buf_set_px_color), MP_ROM_PTR(&mp_lv_img_buf_set_px_color_obj) },
    { MP_ROM_QSTR(MP_QSTR_buf_set_px_alpha), MP_ROM_PTR(&mp_lv_img_buf_set_px_alpha_obj) },
    { MP_ROM_QSTR(MP_QSTR_buf_set_palette), MP_ROM_PTR(&mp_lv_img_buf_set_palette_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_format_get_px_size), MP_ROM_PTR(&mp_lv_img_color_format_get_px_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_format_is_chroma_keyed), MP_ROM_PTR(&mp_lv_img_color_format_is_chroma_keyed_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_format_has_alpha), MP_ROM_PTR(&mp_lv_img_color_format_has_alpha_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_src), MP_ROM_PTR(&mp_lv_img_set_src_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_size), MP_ROM_PTR(&mp_lv_img_set_auto_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_offset), MP_ROM_PTR(&mp_lv_img_set_offset_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_offset_x), MP_ROM_PTR(&mp_lv_img_set_offset_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_offset_y), MP_ROM_PTR(&mp_lv_img_set_offset_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_src), MP_ROM_PTR(&mp_lv_img_get_src_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_file_name), MP_ROM_PTR(&mp_lv_img_get_file_name_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_size), MP_ROM_PTR(&mp_lv_img_get_auto_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_offset_x), MP_ROM_PTR(&mp_lv_img_get_offset_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_offset_y), MP_ROM_PTR(&mp_lv_img_get_offset_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_SRC), MP_ROM_PTR(&mp_LV_IMG_SRC_type) },
    { MP_ROM_QSTR(MP_QSTR_CF), MP_ROM_PTR(&mp_LV_IMG_CF_type) }
};

STATIC MP_DEFINE_CONST_DICT(img_locals_dict, img_locals_dict_table);

STATIC void img_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl img");
}


STATIC mp_obj_t img_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_img_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_img_type = {
    { &mp_type_type },
    .name = MP_QSTR_img,
    .print = img_print,
    .make_new = img_make_new,
    .locals_dict = (mp_obj_dict_t*)&img_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_line_set_style(lv_obj_t *line, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_line_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *line = mp_to_lv(args[0]);
    const lv_style_t *style = mp_to_ptr(args[1]);
    lv_line_set_style(line, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_line_set_style_obj, 2, 2, mp_lv_line_set_style);

 

/*
 * lvgl extension definition for:
 * inline static void lv_line_set_upscale(lv_obj_t *line, bool upcale)
 */
 
STATIC mp_obj_t mp_lv_line_set_upscale(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *line = mp_to_lv(args[0]);
    bool upcale = mp_obj_is_true(args[1]);
    lv_line_set_upscale(line, upcale);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_line_set_upscale_obj, 2, 2, mp_lv_line_set_upscale);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * inline static const lv_style_t *lv_line_get_style(const lv_obj_t *line)
 */
    

/*
 * lvgl extension definition for:
 * inline static bool lv_line_get_upscale(const lv_obj_t *line)
 */
 
STATIC mp_obj_t mp_lv_line_get_upscale(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *line = mp_to_lv(args[0]);
    bool res = lv_line_get_upscale(line);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_line_get_upscale_obj, 1, 1, mp_lv_line_get_upscale);

 

/*
 * lvgl extension definition for:
 * void lv_line_set_points(lv_obj_t *line, const lv_point_t *point_a, uint16_t point_num)
 */
 
STATIC mp_obj_t mp_lv_line_set_points(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *line = mp_to_lv(args[0]);
    const lv_point_t *point_a = mp_to_ptr(args[1]);
    uint16_t point_num = (uint16_t)mp_obj_get_int(args[2]);
    lv_line_set_points(line, point_a, point_num);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_line_set_points_obj, 3, 3, mp_lv_line_set_points);

 

/*
 * lvgl extension definition for:
 * void lv_line_set_auto_size(lv_obj_t *line, bool en)
 */
 
STATIC mp_obj_t mp_lv_line_set_auto_size(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *line = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_line_set_auto_size(line, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_line_set_auto_size_obj, 2, 2, mp_lv_line_set_auto_size);

 

/*
 * lvgl extension definition for:
 * void lv_line_set_y_invert(lv_obj_t *line, bool en)
 */
 
STATIC mp_obj_t mp_lv_line_set_y_invert(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *line = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_line_set_y_invert(line, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_line_set_y_invert_obj, 2, 2, mp_lv_line_set_y_invert);

 

/*
 * lvgl extension definition for:
 * bool lv_line_get_auto_size(const lv_obj_t *line)
 */
 
STATIC mp_obj_t mp_lv_line_get_auto_size(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *line = mp_to_lv(args[0]);
    bool res = lv_line_get_auto_size(line);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_line_get_auto_size_obj, 1, 1, mp_lv_line_get_auto_size);

 

/*
 * lvgl extension definition for:
 * bool lv_line_get_y_invert(const lv_obj_t *line)
 */
 
STATIC mp_obj_t mp_lv_line_get_y_invert(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *line = mp_to_lv(args[0]);
    bool res = lv_line_get_y_invert(line);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_line_get_y_invert_obj, 1, 1, mp_lv_line_get_y_invert);

 

/*
 * lvgl line object definitions
 */
    

STATIC const mp_rom_map_elem_t line_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_line_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_upscale), MP_ROM_PTR(&mp_lv_line_set_upscale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_upscale), MP_ROM_PTR(&mp_lv_line_get_upscale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_points), MP_ROM_PTR(&mp_lv_line_set_points_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_size), MP_ROM_PTR(&mp_lv_line_set_auto_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y_invert), MP_ROM_PTR(&mp_lv_line_set_y_invert_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_size), MP_ROM_PTR(&mp_lv_line_get_auto_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y_invert), MP_ROM_PTR(&mp_lv_line_get_y_invert_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) }
};

STATIC MP_DEFINE_CONST_DICT(line_locals_dict, line_locals_dict_table);

STATIC void line_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl line");
}


STATIC mp_obj_t line_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_line_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_line_type = {
    { &mp_type_type },
    .name = MP_QSTR_line,
    .print = line_print,
    .make_new = line_make_new,
    .locals_dict = (mp_obj_dict_t*)&line_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_page_set_scrl_fit4(lv_obj_t *page, lv_fit_t left, lv_fit_t right, lv_fit_t top, lv_fit_t bottom)
 */
 
STATIC mp_obj_t mp_lv_page_set_scrl_fit4(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_fit_t left = (uint8_t)mp_obj_get_int(args[1]);
    lv_fit_t right = (uint8_t)mp_obj_get_int(args[2]);
    lv_fit_t top = (uint8_t)mp_obj_get_int(args[3]);
    lv_fit_t bottom = (uint8_t)mp_obj_get_int(args[4]);
    lv_page_set_scrl_fit4(page, left, right, top, bottom);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_set_scrl_fit4_obj, 5, 5, mp_lv_page_set_scrl_fit4);

 

/*
 * lvgl extension definition for:
 * inline static void lv_page_set_scrl_fit2(lv_obj_t *page, lv_fit_t hor, lv_fit_t ver)
 */
 
STATIC mp_obj_t mp_lv_page_set_scrl_fit2(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_fit_t hor = (uint8_t)mp_obj_get_int(args[1]);
    lv_fit_t ver = (uint8_t)mp_obj_get_int(args[2]);
    lv_page_set_scrl_fit2(page, hor, ver);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_set_scrl_fit2_obj, 3, 3, mp_lv_page_set_scrl_fit2);

 

/*
 * lvgl extension definition for:
 * inline static void lv_page_set_scrl_fit(lv_obj_t *page, lv_fit_t fit)
 */
 
STATIC mp_obj_t mp_lv_page_set_scrl_fit(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_fit_t fit = (uint8_t)mp_obj_get_int(args[1]);
    lv_page_set_scrl_fit(page, fit);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_set_scrl_fit_obj, 2, 2, mp_lv_page_set_scrl_fit);

 

/*
 * lvgl extension definition for:
 * inline static void lv_page_set_scrl_width(lv_obj_t *page, lv_coord_t w)
 */
 
STATIC mp_obj_t mp_lv_page_set_scrl_width(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_coord_t w = (int16_t)mp_obj_get_int(args[1]);
    lv_page_set_scrl_width(page, w);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_set_scrl_width_obj, 2, 2, mp_lv_page_set_scrl_width);

 

/*
 * lvgl extension definition for:
 * inline static void lv_page_set_scrl_height(lv_obj_t *page, lv_coord_t h)
 */
 
STATIC mp_obj_t mp_lv_page_set_scrl_height(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_coord_t h = (int16_t)mp_obj_get_int(args[1]);
    lv_page_set_scrl_height(page, h);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_set_scrl_height_obj, 2, 2, mp_lv_page_set_scrl_height);

 

/*
 * lvgl extension definition for:
 * inline static void lv_page_set_scrl_layout(lv_obj_t *page, lv_layout_t layout)
 */
 
STATIC mp_obj_t mp_lv_page_set_scrl_layout(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_layout_t layout = (uint8_t)mp_obj_get_int(args[1]);
    lv_page_set_scrl_layout(page, layout);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_set_scrl_layout_obj, 2, 2, mp_lv_page_set_scrl_layout);

 

/*
 * lvgl extension definition for:
 * inline static lv_coord_t lv_page_get_scrl_width(const lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_scrl_width(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *page = mp_to_lv(args[0]);
    lv_coord_t res = lv_page_get_scrl_width(page);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_scrl_width_obj, 1, 1, mp_lv_page_get_scrl_width);

 

/*
 * lvgl extension definition for:
 * inline static lv_coord_t lv_page_get_scrl_height(const lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_scrl_height(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *page = mp_to_lv(args[0]);
    lv_coord_t res = lv_page_get_scrl_height(page);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_scrl_height_obj, 1, 1, mp_lv_page_get_scrl_height);

 

/*
 * lvgl extension definition for:
 * inline static lv_layout_t lv_page_get_scrl_layout(const lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_scrl_layout(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *page = mp_to_lv(args[0]);
    lv_layout_t res = lv_page_get_scrl_layout(page);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_scrl_layout_obj, 1, 1, mp_lv_page_get_scrl_layout);

 

/*
 * lvgl extension definition for:
 * inline static lv_fit_t lv_page_get_scrl_fit_left(const lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_scrl_fit_left(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *page = mp_to_lv(args[0]);
    lv_fit_t res = lv_page_get_scrl_fit_left(page);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_scrl_fit_left_obj, 1, 1, mp_lv_page_get_scrl_fit_left);

 

/*
 * lvgl extension definition for:
 * inline static lv_fit_t lv_page_get_scrl_fit_right(const lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_scrl_fit_right(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *page = mp_to_lv(args[0]);
    lv_fit_t res = lv_page_get_scrl_fit_right(page);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_scrl_fit_right_obj, 1, 1, mp_lv_page_get_scrl_fit_right);

 

/*
 * lvgl extension definition for:
 * inline static lv_fit_t lv_page_get_scrl_fit_top(const lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_scrl_fit_top(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *page = mp_to_lv(args[0]);
    lv_fit_t res = lv_page_get_scrl_fit_top(page);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_scrl_fit_top_obj, 1, 1, mp_lv_page_get_scrl_fit_top);

 

/*
 * lvgl extension definition for:
 * inline static lv_fit_t lv_page_get_scrl_fit_bottom(const lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_scrl_fit_bottom(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *page = mp_to_lv(args[0]);
    lv_fit_t res = lv_page_get_scrl_fit_bottom(page);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_scrl_fit_bottom_obj, 1, 1, mp_lv_page_get_scrl_fit_bottom);

 

/*
 * lvgl extension definition for:
 * void lv_page_clean(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_page_clean(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_page_clean(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_clean_obj, 1, 1, mp_lv_page_clean);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_page_get_scrl(const lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_scrl(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *page = mp_to_lv(args[0]);
    lv_obj_t * res = lv_page_get_scrl(page);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_scrl_obj, 1, 1, mp_lv_page_get_scrl);

 

/*
 * lvgl extension definition for:
 * void lv_page_set_sb_mode(lv_obj_t *page, lv_sb_mode_t sb_mode)
 */
 
STATIC mp_obj_t mp_lv_page_set_sb_mode(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_sb_mode_t sb_mode = (uint8_t)mp_obj_get_int(args[1]);
    lv_page_set_sb_mode(page, sb_mode);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_set_sb_mode_obj, 2, 2, mp_lv_page_set_sb_mode);

 

/*
 * lvgl extension definition for:
 * void lv_page_set_arrow_scroll(lv_obj_t *page, bool en)
 */
 
STATIC mp_obj_t mp_lv_page_set_arrow_scroll(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_page_set_arrow_scroll(page, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_set_arrow_scroll_obj, 2, 2, mp_lv_page_set_arrow_scroll);

 

/*
 * lvgl extension definition for:
 * void lv_page_set_scroll_propagation(lv_obj_t *page, bool en)
 */
 
STATIC mp_obj_t mp_lv_page_set_scroll_propagation(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_page_set_scroll_propagation(page, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_set_scroll_propagation_obj, 2, 2, mp_lv_page_set_scroll_propagation);

 

/*
 * lvgl extension definition for:
 * void lv_page_set_edge_flash(lv_obj_t *page, bool en)
 */
 
STATIC mp_obj_t mp_lv_page_set_edge_flash(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_page_set_edge_flash(page, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_set_edge_flash_obj, 2, 2, mp_lv_page_set_edge_flash);

 

/*
 * lvgl extension definition for:
 * void lv_page_set_style(lv_obj_t *page, lv_page_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_page_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_page_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_page_set_style(page, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_set_style_obj, 3, 3, mp_lv_page_set_style);

 

/*
 * lvgl extension definition for:
 * lv_sb_mode_t lv_page_get_sb_mode(const lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_sb_mode(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *page = mp_to_lv(args[0]);
    lv_sb_mode_t res = lv_page_get_sb_mode(page);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_sb_mode_obj, 1, 1, mp_lv_page_get_sb_mode);

 

/*
 * lvgl extension definition for:
 * bool lv_page_get_arrow_scroll(const lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_arrow_scroll(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *page = mp_to_lv(args[0]);
    bool res = lv_page_get_arrow_scroll(page);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_arrow_scroll_obj, 1, 1, mp_lv_page_get_arrow_scroll);

 

/*
 * lvgl extension definition for:
 * bool lv_page_get_scroll_propagation(lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_scroll_propagation(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    bool res = lv_page_get_scroll_propagation(page);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_scroll_propagation_obj, 1, 1, mp_lv_page_get_scroll_propagation);

 

/*
 * lvgl extension definition for:
 * bool lv_page_get_edge_flash(lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_edge_flash(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    bool res = lv_page_get_edge_flash(page);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_edge_flash_obj, 1, 1, mp_lv_page_get_edge_flash);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_page_get_fit_width(lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_fit_width(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_coord_t res = lv_page_get_fit_width(page);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_fit_width_obj, 1, 1, mp_lv_page_get_fit_width);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_page_get_fit_height(lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_get_fit_height(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_coord_t res = lv_page_get_fit_height(page);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_get_fit_height_obj, 1, 1, mp_lv_page_get_fit_height);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_page_get_style(const lv_obj_t *page, lv_page_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * bool lv_page_on_edge(lv_obj_t *page, lv_page_edge_t edge)
 */
 
STATIC mp_obj_t mp_lv_page_on_edge(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_page_edge_t edge = (uint8_t)mp_obj_get_int(args[1]);
    bool res = lv_page_on_edge(page, edge);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_on_edge_obj, 2, 2, mp_lv_page_on_edge);

 

/*
 * lvgl extension definition for:
 * void lv_page_glue_obj(lv_obj_t *obj, bool glue)
 */
 
STATIC mp_obj_t mp_lv_page_glue_obj(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    bool glue = mp_obj_is_true(args[1]);
    lv_page_glue_obj(obj, glue);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_glue_obj_obj, 2, 2, mp_lv_page_glue_obj);

 

/*
 * lvgl extension definition for:
 * void lv_page_focus(lv_obj_t *page, const lv_obj_t *obj, uint16_t anim_time)
 */
 
STATIC mp_obj_t mp_lv_page_focus(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    const lv_obj_t *obj = mp_to_lv(args[1]);
    uint16_t anim_time = (uint16_t)mp_obj_get_int(args[2]);
    lv_page_focus(page, obj, anim_time);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_focus_obj, 3, 3, mp_lv_page_focus);

 

/*
 * lvgl extension definition for:
 * void lv_page_scroll_hor(lv_obj_t *page, lv_coord_t dist)
 */
 
STATIC mp_obj_t mp_lv_page_scroll_hor(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_coord_t dist = (int16_t)mp_obj_get_int(args[1]);
    lv_page_scroll_hor(page, dist);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_scroll_hor_obj, 2, 2, mp_lv_page_scroll_hor);

 

/*
 * lvgl extension definition for:
 * void lv_page_scroll_ver(lv_obj_t *page, lv_coord_t dist)
 */
 
STATIC mp_obj_t mp_lv_page_scroll_ver(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_coord_t dist = (int16_t)mp_obj_get_int(args[1]);
    lv_page_scroll_ver(page, dist);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_scroll_ver_obj, 2, 2, mp_lv_page_scroll_ver);

 

/*
 * lvgl extension definition for:
 * void lv_page_start_edge_flash(lv_obj_t *page)
 */
 
STATIC mp_obj_t mp_lv_page_start_edge_flash(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *page = mp_to_lv(args[0]);
    lv_page_start_edge_flash(page);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_page_start_edge_flash_obj, 1, 1, mp_lv_page_start_edge_flash);

 

/*
 * lvgl page object definitions
 */
    

STATIC const mp_rom_map_elem_t page_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_scrl_fit4), MP_ROM_PTR(&mp_lv_page_set_scrl_fit4_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_scrl_fit2), MP_ROM_PTR(&mp_lv_page_set_scrl_fit2_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_scrl_fit), MP_ROM_PTR(&mp_lv_page_set_scrl_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_scrl_width), MP_ROM_PTR(&mp_lv_page_set_scrl_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_scrl_height), MP_ROM_PTR(&mp_lv_page_set_scrl_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_scrl_layout), MP_ROM_PTR(&mp_lv_page_set_scrl_layout_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scrl_width), MP_ROM_PTR(&mp_lv_page_get_scrl_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scrl_height), MP_ROM_PTR(&mp_lv_page_get_scrl_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scrl_layout), MP_ROM_PTR(&mp_lv_page_get_scrl_layout_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scrl_fit_left), MP_ROM_PTR(&mp_lv_page_get_scrl_fit_left_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scrl_fit_right), MP_ROM_PTR(&mp_lv_page_get_scrl_fit_right_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scrl_fit_top), MP_ROM_PTR(&mp_lv_page_get_scrl_fit_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scrl_fit_bottom), MP_ROM_PTR(&mp_lv_page_get_scrl_fit_bottom_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_page_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scrl), MP_ROM_PTR(&mp_lv_page_get_scrl_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_sb_mode), MP_ROM_PTR(&mp_lv_page_set_sb_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_arrow_scroll), MP_ROM_PTR(&mp_lv_page_set_arrow_scroll_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_scroll_propagation), MP_ROM_PTR(&mp_lv_page_set_scroll_propagation_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_edge_flash), MP_ROM_PTR(&mp_lv_page_set_edge_flash_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_page_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_sb_mode), MP_ROM_PTR(&mp_lv_page_get_sb_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_arrow_scroll), MP_ROM_PTR(&mp_lv_page_get_arrow_scroll_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scroll_propagation), MP_ROM_PTR(&mp_lv_page_get_scroll_propagation_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_edge_flash), MP_ROM_PTR(&mp_lv_page_get_edge_flash_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_fit_width), MP_ROM_PTR(&mp_lv_page_get_fit_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_fit_height), MP_ROM_PTR(&mp_lv_page_get_fit_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_on_edge), MP_ROM_PTR(&mp_lv_page_on_edge_obj) },
    { MP_ROM_QSTR(MP_QSTR_glue_obj), MP_ROM_PTR(&mp_lv_page_glue_obj_obj) },
    { MP_ROM_QSTR(MP_QSTR_focus), MP_ROM_PTR(&mp_lv_page_focus_obj) },
    { MP_ROM_QSTR(MP_QSTR_scroll_hor), MP_ROM_PTR(&mp_lv_page_scroll_hor_obj) },
    { MP_ROM_QSTR(MP_QSTR_scroll_ver), MP_ROM_PTR(&mp_lv_page_scroll_ver_obj) },
    { MP_ROM_QSTR(MP_QSTR_start_edge_flash), MP_ROM_PTR(&mp_lv_page_start_edge_flash_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_EDGE), MP_ROM_PTR(&mp_LV_PAGE_EDGE_type) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_PAGE_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(page_locals_dict, page_locals_dict_table);

STATIC void page_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl page");
}


STATIC mp_obj_t page_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_page_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_page_type = {
    { &mp_type_type },
    .name = MP_QSTR_page,
    .print = page_print,
    .make_new = page_make_new,
    .locals_dict = (mp_obj_dict_t*)&page_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_list_set_sb_mode(lv_obj_t *list, lv_sb_mode_t mode)
 */
 
STATIC mp_obj_t mp_lv_list_set_sb_mode(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *list = mp_to_lv(args[0]);
    lv_sb_mode_t mode = (uint8_t)mp_obj_get_int(args[1]);
    lv_list_set_sb_mode(list, mode);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_set_sb_mode_obj, 2, 2, mp_lv_list_set_sb_mode);

 

/*
 * lvgl extension definition for:
 * inline static void lv_list_set_scroll_propagation(lv_obj_t *list, bool en)
 */
 
STATIC mp_obj_t mp_lv_list_set_scroll_propagation(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *list = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_list_set_scroll_propagation(list, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_set_scroll_propagation_obj, 2, 2, mp_lv_list_set_scroll_propagation);

 

/*
 * lvgl extension definition for:
 * inline static void lv_list_set_edge_flash(lv_obj_t *list, bool en)
 */
 
STATIC mp_obj_t mp_lv_list_set_edge_flash(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *list = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_list_set_edge_flash(list, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_set_edge_flash_obj, 2, 2, mp_lv_list_set_edge_flash);

 

/*
 * lvgl extension definition for:
 * inline static lv_sb_mode_t lv_list_get_sb_mode(const lv_obj_t *list)
 */
 
STATIC mp_obj_t mp_lv_list_get_sb_mode(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *list = mp_to_lv(args[0]);
    lv_sb_mode_t res = lv_list_get_sb_mode(list);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_sb_mode_obj, 1, 1, mp_lv_list_get_sb_mode);

 

/*
 * lvgl extension definition for:
 * inline static bool lv_list_get_scroll_propagation(lv_obj_t *list)
 */
 
STATIC mp_obj_t mp_lv_list_get_scroll_propagation(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *list = mp_to_lv(args[0]);
    bool res = lv_list_get_scroll_propagation(list);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_scroll_propagation_obj, 1, 1, mp_lv_list_get_scroll_propagation);

 

/*
 * lvgl extension definition for:
 * inline static bool lv_list_get_edge_flash(lv_obj_t *list)
 */
 
STATIC mp_obj_t mp_lv_list_get_edge_flash(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *list = mp_to_lv(args[0]);
    bool res = lv_list_get_edge_flash(list);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_edge_flash_obj, 1, 1, mp_lv_list_get_edge_flash);

 

/*
 * lvgl extension definition for:
 * void lv_list_clean(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_list_clean(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_list_clean(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_clean_obj, 1, 1, mp_lv_list_clean);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_list_add(lv_obj_t *list, const void *img_src, const char *txt, lv_event_cb_t event_cb)
 */
 
STATIC mp_obj_t mp_lv_list_add(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *list = mp_to_lv(args[0]);
    const void *img_src = mp_to_ptr(args[1]);
    const char *txt = (char*)mp_obj_str_get_str(args[2]);
    lv_event_cb_t event_cb = mp_lv_callback(args[3], &event_cb_callback, MP_QSTR_event_cb, &list->user_data);
    lv_obj_t * res = lv_list_add(list, img_src, txt, event_cb);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_add_obj, 4, 4, mp_lv_list_add);

 

/*
 * lvgl extension definition for:
 * bool lv_list_remove(const lv_obj_t *list, uint32_t index)
 */
 
STATIC mp_obj_t mp_lv_list_remove(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *list = mp_to_lv(args[0]);
    uint32_t index = (uint32_t)mp_obj_get_int(args[1]);
    bool res = lv_list_remove(list, index);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_remove_obj, 2, 2, mp_lv_list_remove);

 

/*
 * lvgl extension definition for:
 * void lv_list_set_single_mode(lv_obj_t *list, bool mode)
 */
 
STATIC mp_obj_t mp_lv_list_set_single_mode(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *list = mp_to_lv(args[0]);
    bool mode = mp_obj_is_true(args[1]);
    lv_list_set_single_mode(list, mode);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_set_single_mode_obj, 2, 2, mp_lv_list_set_single_mode);

 

/*
 * lvgl extension definition for:
 * void lv_list_set_btn_selected(lv_obj_t *list, lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_list_set_btn_selected(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *list = mp_to_lv(args[0]);
    lv_obj_t *btn = mp_to_lv(args[1]);
    lv_list_set_btn_selected(list, btn);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_set_btn_selected_obj, 2, 2, mp_lv_list_set_btn_selected);

 

/*
 * lvgl extension definition for:
 * void lv_list_set_anim_time(lv_obj_t *list, uint16_t anim_time)
 */
 
STATIC mp_obj_t mp_lv_list_set_anim_time(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *list = mp_to_lv(args[0]);
    uint16_t anim_time = (uint16_t)mp_obj_get_int(args[1]);
    lv_list_set_anim_time(list, anim_time);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_set_anim_time_obj, 2, 2, mp_lv_list_set_anim_time);

 

/*
 * lvgl extension definition for:
 * void lv_list_set_style(lv_obj_t *list, lv_list_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_list_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *list = mp_to_lv(args[0]);
    lv_list_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_list_set_style(list, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_set_style_obj, 3, 3, mp_lv_list_set_style);

 

/*
 * lvgl extension definition for:
 * bool lv_list_get_single_mode(lv_obj_t *list)
 */
 
STATIC mp_obj_t mp_lv_list_get_single_mode(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *list = mp_to_lv(args[0]);
    bool res = lv_list_get_single_mode(list);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_single_mode_obj, 1, 1, mp_lv_list_get_single_mode);

 

/*
 * lvgl extension definition for:
 * const char *lv_list_get_btn_text(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_list_get_btn_text(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    const char * res = lv_list_get_btn_text(btn);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_btn_text_obj, 1, 1, mp_lv_list_get_btn_text);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_list_get_btn_label(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_list_get_btn_label(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    lv_obj_t * res = lv_list_get_btn_label(btn);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_btn_label_obj, 1, 1, mp_lv_list_get_btn_label);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_list_get_btn_img(const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_list_get_btn_img(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    lv_obj_t * res = lv_list_get_btn_img(btn);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_btn_img_obj, 1, 1, mp_lv_list_get_btn_img);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_list_get_prev_btn(const lv_obj_t *list, lv_obj_t *prev_btn)
 */
 
STATIC mp_obj_t mp_lv_list_get_prev_btn(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *list = mp_to_lv(args[0]);
    lv_obj_t *prev_btn = mp_to_lv(args[1]);
    lv_obj_t * res = lv_list_get_prev_btn(list, prev_btn);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_prev_btn_obj, 2, 2, mp_lv_list_get_prev_btn);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_list_get_next_btn(const lv_obj_t *list, lv_obj_t *prev_btn)
 */
 
STATIC mp_obj_t mp_lv_list_get_next_btn(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *list = mp_to_lv(args[0]);
    lv_obj_t *prev_btn = mp_to_lv(args[1]);
    lv_obj_t * res = lv_list_get_next_btn(list, prev_btn);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_next_btn_obj, 2, 2, mp_lv_list_get_next_btn);

 

/*
 * lvgl extension definition for:
 * int32_t lv_list_get_btn_index(const lv_obj_t *list, const lv_obj_t *btn)
 */
 
STATIC mp_obj_t mp_lv_list_get_btn_index(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *list = mp_to_lv(args[0]);
    const lv_obj_t *btn = mp_to_lv(args[1]);
    int32_t res = lv_list_get_btn_index(list, btn);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_btn_index_obj, 2, 2, mp_lv_list_get_btn_index);

 

/*
 * lvgl extension definition for:
 * uint32_t lv_list_get_size(const lv_obj_t *list)
 */
 
STATIC mp_obj_t mp_lv_list_get_size(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *list = mp_to_lv(args[0]);
    uint32_t res = lv_list_get_size(list);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_size_obj, 1, 1, mp_lv_list_get_size);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_list_get_btn_selected(const lv_obj_t *list)
 */
 
STATIC mp_obj_t mp_lv_list_get_btn_selected(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *list = mp_to_lv(args[0]);
    lv_obj_t * res = lv_list_get_btn_selected(list);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_btn_selected_obj, 1, 1, mp_lv_list_get_btn_selected);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_list_get_anim_time(const lv_obj_t *list)
 */
 
STATIC mp_obj_t mp_lv_list_get_anim_time(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *list = mp_to_lv(args[0]);
    uint16_t res = lv_list_get_anim_time(list);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_get_anim_time_obj, 1, 1, mp_lv_list_get_anim_time);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_list_get_style(const lv_obj_t *list, lv_list_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * void lv_list_up(const lv_obj_t *list)
 */
 
STATIC mp_obj_t mp_lv_list_up(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *list = mp_to_lv(args[0]);
    lv_list_up(list);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_up_obj, 1, 1, mp_lv_list_up);

 

/*
 * lvgl extension definition for:
 * void lv_list_down(const lv_obj_t *list)
 */
 
STATIC mp_obj_t mp_lv_list_down(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *list = mp_to_lv(args[0]);
    lv_list_down(list);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_down_obj, 1, 1, mp_lv_list_down);

 

/*
 * lvgl extension definition for:
 * void lv_list_focus(const lv_obj_t *btn, bool anim_en)
 */
 
STATIC mp_obj_t mp_lv_list_focus(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btn = mp_to_lv(args[0]);
    bool anim_en = mp_obj_is_true(args[1]);
    lv_list_focus(btn, anim_en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_list_focus_obj, 2, 2, mp_lv_list_focus);

 

/*
 * lvgl list object definitions
 */
    

STATIC const mp_rom_map_elem_t list_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_sb_mode), MP_ROM_PTR(&mp_lv_list_set_sb_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_scroll_propagation), MP_ROM_PTR(&mp_lv_list_set_scroll_propagation_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_edge_flash), MP_ROM_PTR(&mp_lv_list_set_edge_flash_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_sb_mode), MP_ROM_PTR(&mp_lv_list_get_sb_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scroll_propagation), MP_ROM_PTR(&mp_lv_list_get_scroll_propagation_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_edge_flash), MP_ROM_PTR(&mp_lv_list_get_edge_flash_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_list_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_add), MP_ROM_PTR(&mp_lv_list_add_obj) },
    { MP_ROM_QSTR(MP_QSTR_remove), MP_ROM_PTR(&mp_lv_list_remove_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_single_mode), MP_ROM_PTR(&mp_lv_list_set_single_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_btn_selected), MP_ROM_PTR(&mp_lv_list_set_btn_selected_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_anim_time), MP_ROM_PTR(&mp_lv_list_set_anim_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_list_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_single_mode), MP_ROM_PTR(&mp_lv_list_get_single_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_btn_text), MP_ROM_PTR(&mp_lv_list_get_btn_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_btn_label), MP_ROM_PTR(&mp_lv_list_get_btn_label_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_btn_img), MP_ROM_PTR(&mp_lv_list_get_btn_img_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_prev_btn), MP_ROM_PTR(&mp_lv_list_get_prev_btn_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_next_btn), MP_ROM_PTR(&mp_lv_list_get_next_btn_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_btn_index), MP_ROM_PTR(&mp_lv_list_get_btn_index_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_size), MP_ROM_PTR(&mp_lv_list_get_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_btn_selected), MP_ROM_PTR(&mp_lv_list_get_btn_selected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_anim_time), MP_ROM_PTR(&mp_lv_list_get_anim_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_up), MP_ROM_PTR(&mp_lv_list_up_obj) },
    { MP_ROM_QSTR(MP_QSTR_down), MP_ROM_PTR(&mp_lv_list_down_obj) },
    { MP_ROM_QSTR(MP_QSTR_focus), MP_ROM_PTR(&mp_lv_list_focus_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_LIST_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(list_locals_dict, list_locals_dict_table);

STATIC void list_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl list");
}


STATIC mp_obj_t list_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_list_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_list_type = {
    { &mp_type_type },
    .name = MP_QSTR_list,
    .print = list_print,
    .make_new = list_make_new,
    .locals_dict = (mp_obj_dict_t*)&list_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_chart_set_style(lv_obj_t *chart, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_chart_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    const lv_style_t *style = mp_to_ptr(args[1]);
    lv_chart_set_style(chart, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_style_obj, 2, 2, mp_lv_chart_set_style);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * inline static const lv_style_t *lv_chart_get_style(const lv_obj_t *chart)
 */
    

/*
 * Struct lv_chart_series_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_chart_series_t_type();

STATIC inline lv_chart_series_t* mp_write_ptr_lv_chart_series_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_chart_series_t_type()));
    return (lv_chart_series_t*)self->data;
}

#define mp_write_lv_chart_series_t(struct_obj) *mp_write_ptr_lv_chart_series_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_chart_series_t(lv_chart_series_t *field)
{
    return lv_to_mp_struct(get_mp_lv_chart_series_t_type(), field);
}

#define mp_read_lv_chart_series_t(field) mp_read_ptr_lv_chart_series_t(copy_buffer(&field, sizeof(lv_chart_series_t)))
#define mp_read_byref_lv_chart_series_t(field) mp_read_ptr_lv_chart_series_t(&field)

STATIC void mp_lv_chart_series_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_chart_series_t *data = (lv_chart_series_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_points: dest[0] = ptr_to_mp((void*)data->points); break; // converting from lv_coord_t *;
            case MP_QSTR_color: dest[0] = mp_read_byref_lv_color32_t(data->color); break; // converting from lv_color_t;
            case MP_QSTR_start_point: dest[0] = mp_obj_new_int_from_uint(data->start_point); break; // converting from uint16_t;
            default: field_not_found(MP_QSTR_lv_chart_series_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_points: data->points = (void*)mp_to_ptr(dest[1]); break; // converting to lv_coord_t *;
                case MP_QSTR_color: data->color = mp_write_lv_color32_t(dest[1]); break; // converting to lv_color_t;
                case MP_QSTR_start_point: data->start_point = (uint16_t)mp_obj_get_int(dest[1]); break; // converting to uint16_t;
                default: field_not_found(MP_QSTR_lv_chart_series_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_chart_series_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_chart_series_t");
}

STATIC const mp_rom_map_elem_t mp_lv_chart_series_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_chart_series_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_chart_series_t_locals_dict, mp_lv_chart_series_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_chart_series_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_chart_series_t,
    .print = mp_lv_chart_series_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_chart_series_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_chart_series_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_chart_series_t_type()
{
    return &mp_lv_chart_series_t_type;
}
    

/*
 * lvgl extension definition for:
 * lv_chart_series_t *lv_chart_add_series(lv_obj_t *chart, lv_color_t color)
 */
 
STATIC mp_obj_t mp_lv_chart_add_series(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    lv_color_t color = mp_write_lv_color32_t(args[1]);
    lv_chart_series_t * res = lv_chart_add_series(chart, color);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_add_series_obj, 2, 2, mp_lv_chart_add_series);

 

/*
 * lvgl extension definition for:
 * void lv_chart_clear_serie(lv_obj_t *chart, lv_chart_series_t *serie)
 */
 
STATIC mp_obj_t mp_lv_chart_clear_serie(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    lv_chart_series_t *serie = mp_to_ptr(args[1]);
    lv_chart_clear_serie(chart, serie);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_clear_serie_obj, 2, 2, mp_lv_chart_clear_serie);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_div_line_count(lv_obj_t *chart, uint8_t hdiv, uint8_t vdiv)
 */
 
STATIC mp_obj_t mp_lv_chart_set_div_line_count(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    uint8_t hdiv = (uint8_t)mp_obj_get_int(args[1]);
    uint8_t vdiv = (uint8_t)mp_obj_get_int(args[2]);
    lv_chart_set_div_line_count(chart, hdiv, vdiv);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_div_line_count_obj, 3, 3, mp_lv_chart_set_div_line_count);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_range(lv_obj_t *chart, lv_coord_t ymin, lv_coord_t ymax)
 */
 
STATIC mp_obj_t mp_lv_chart_set_range(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    lv_coord_t ymin = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t ymax = (int16_t)mp_obj_get_int(args[2]);
    lv_chart_set_range(chart, ymin, ymax);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_range_obj, 3, 3, mp_lv_chart_set_range);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_type(lv_obj_t *chart, lv_chart_type_t type)
 */
 
STATIC mp_obj_t mp_lv_chart_set_type(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    lv_chart_type_t type = (uint8_t)mp_obj_get_int(args[1]);
    lv_chart_set_type(chart, type);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_type_obj, 2, 2, mp_lv_chart_set_type);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_point_count(lv_obj_t *chart, uint16_t point_cnt)
 */
 
STATIC mp_obj_t mp_lv_chart_set_point_count(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    uint16_t point_cnt = (uint16_t)mp_obj_get_int(args[1]);
    lv_chart_set_point_count(chart, point_cnt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_point_count_obj, 2, 2, mp_lv_chart_set_point_count);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_series_opa(lv_obj_t *chart, lv_opa_t opa)
 */
 
STATIC mp_obj_t mp_lv_chart_set_series_opa(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    lv_opa_t opa = (uint8_t)mp_obj_get_int(args[1]);
    lv_chart_set_series_opa(chart, opa);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_series_opa_obj, 2, 2, mp_lv_chart_set_series_opa);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_series_width(lv_obj_t *chart, lv_coord_t width)
 */
 
STATIC mp_obj_t mp_lv_chart_set_series_width(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    lv_coord_t width = (int16_t)mp_obj_get_int(args[1]);
    lv_chart_set_series_width(chart, width);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_series_width_obj, 2, 2, mp_lv_chart_set_series_width);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_series_darking(lv_obj_t *chart, lv_opa_t dark_eff)
 */
 
STATIC mp_obj_t mp_lv_chart_set_series_darking(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    lv_opa_t dark_eff = (uint8_t)mp_obj_get_int(args[1]);
    lv_chart_set_series_darking(chart, dark_eff);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_series_darking_obj, 2, 2, mp_lv_chart_set_series_darking);

 

/*
 * lvgl extension definition for:
 * void lv_chart_init_points(lv_obj_t *chart, lv_chart_series_t *ser, lv_coord_t y)
 */
 
STATIC mp_obj_t mp_lv_chart_init_points(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    lv_chart_series_t *ser = mp_to_ptr(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    lv_chart_init_points(chart, ser, y);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_init_points_obj, 3, 3, mp_lv_chart_init_points);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_points(lv_obj_t *chart, lv_chart_series_t *ser, lv_coord_t *y_array)
 */
 
STATIC mp_obj_t mp_lv_chart_set_points(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    lv_chart_series_t *ser = mp_to_ptr(args[1]);
    lv_coord_t *y_array = mp_to_ptr(args[2]);
    lv_chart_set_points(chart, ser, y_array);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_points_obj, 3, 3, mp_lv_chart_set_points);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_next(lv_obj_t *chart, lv_chart_series_t *ser, lv_coord_t y)
 */
 
STATIC mp_obj_t mp_lv_chart_set_next(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    lv_chart_series_t *ser = mp_to_ptr(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    lv_chart_set_next(chart, ser, y);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_next_obj, 3, 3, mp_lv_chart_set_next);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_update_mode(lv_obj_t *chart, lv_chart_update_mode_t update_mode)
 */
 
STATIC mp_obj_t mp_lv_chart_set_update_mode(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    lv_chart_update_mode_t update_mode = (uint8_t)mp_obj_get_int(args[1]);
    lv_chart_set_update_mode(chart, update_mode);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_update_mode_obj, 2, 2, mp_lv_chart_set_update_mode);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_margin(lv_obj_t *chart, uint16_t margin)
 */
 
STATIC mp_obj_t mp_lv_chart_set_margin(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    uint16_t margin = (uint16_t)mp_obj_get_int(args[1]);
    lv_chart_set_margin(chart, margin);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_margin_obj, 2, 2, mp_lv_chart_set_margin);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_x_ticks(lv_obj_t *chart, const char *list_of_values, uint8_t num_tick_marks, uint8_t major_tick_len, uint8_t minor_tick_len, lv_chart_axis_options_t options)
 */
 
STATIC mp_obj_t mp_lv_chart_set_x_ticks(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    const char *list_of_values = (char*)mp_obj_str_get_str(args[1]);
    uint8_t num_tick_marks = (uint8_t)mp_obj_get_int(args[2]);
    uint8_t major_tick_len = (uint8_t)mp_obj_get_int(args[3]);
    uint8_t minor_tick_len = (uint8_t)mp_obj_get_int(args[4]);
    lv_chart_axis_options_t options = (uint8_t)mp_obj_get_int(args[5]);
    lv_chart_set_x_ticks(chart, list_of_values, num_tick_marks, major_tick_len, minor_tick_len, options);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_x_ticks_obj, 6, 6, mp_lv_chart_set_x_ticks);

 

/*
 * lvgl extension definition for:
 * void lv_chart_set_y_ticks(lv_obj_t *chart, const char *list_of_values, uint8_t num_tick_marks, uint8_t major_tick_len, uint8_t minor_tick_len, lv_chart_axis_options_t options)
 */
 
STATIC mp_obj_t mp_lv_chart_set_y_ticks(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    const char *list_of_values = (char*)mp_obj_str_get_str(args[1]);
    uint8_t num_tick_marks = (uint8_t)mp_obj_get_int(args[2]);
    uint8_t major_tick_len = (uint8_t)mp_obj_get_int(args[3]);
    uint8_t minor_tick_len = (uint8_t)mp_obj_get_int(args[4]);
    lv_chart_axis_options_t options = (uint8_t)mp_obj_get_int(args[5]);
    lv_chart_set_y_ticks(chart, list_of_values, num_tick_marks, major_tick_len, minor_tick_len, options);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_set_y_ticks_obj, 6, 6, mp_lv_chart_set_y_ticks);

 

/*
 * lvgl extension definition for:
 * lv_chart_type_t lv_chart_get_type(const lv_obj_t *chart)
 */
 
STATIC mp_obj_t mp_lv_chart_get_type(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *chart = mp_to_lv(args[0]);
    lv_chart_type_t res = lv_chart_get_type(chart);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_get_type_obj, 1, 1, mp_lv_chart_get_type);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_chart_get_point_cnt(const lv_obj_t *chart)
 */
 
STATIC mp_obj_t mp_lv_chart_get_point_cnt(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *chart = mp_to_lv(args[0]);
    uint16_t res = lv_chart_get_point_cnt(chart);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_get_point_cnt_obj, 1, 1, mp_lv_chart_get_point_cnt);

 

/*
 * lvgl extension definition for:
 * lv_opa_t lv_chart_get_series_opa(const lv_obj_t *chart)
 */
 
STATIC mp_obj_t mp_lv_chart_get_series_opa(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *chart = mp_to_lv(args[0]);
    lv_opa_t res = lv_chart_get_series_opa(chart);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_get_series_opa_obj, 1, 1, mp_lv_chart_get_series_opa);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_chart_get_series_width(const lv_obj_t *chart)
 */
 
STATIC mp_obj_t mp_lv_chart_get_series_width(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *chart = mp_to_lv(args[0]);
    lv_coord_t res = lv_chart_get_series_width(chart);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_get_series_width_obj, 1, 1, mp_lv_chart_get_series_width);

 

/*
 * lvgl extension definition for:
 * lv_opa_t lv_chart_get_series_darking(const lv_obj_t *chart)
 */
 
STATIC mp_obj_t mp_lv_chart_get_series_darking(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *chart = mp_to_lv(args[0]);
    lv_opa_t res = lv_chart_get_series_darking(chart);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_get_series_darking_obj, 1, 1, mp_lv_chart_get_series_darking);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_chart_get_margin(lv_obj_t *chart)
 */
 
STATIC mp_obj_t mp_lv_chart_get_margin(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    uint16_t res = lv_chart_get_margin(chart);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_get_margin_obj, 1, 1, mp_lv_chart_get_margin);

 

/*
 * lvgl extension definition for:
 * void lv_chart_refresh(lv_obj_t *chart)
 */
 
STATIC mp_obj_t mp_lv_chart_refresh(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *chart = mp_to_lv(args[0]);
    lv_chart_refresh(chart);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_chart_refresh_obj, 1, 1, mp_lv_chart_refresh);

 

/*
 * lvgl chart object definitions
 */
    

STATIC const mp_rom_map_elem_t chart_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_chart_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_add_series), MP_ROM_PTR(&mp_lv_chart_add_series_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_serie), MP_ROM_PTR(&mp_lv_chart_clear_serie_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_div_line_count), MP_ROM_PTR(&mp_lv_chart_set_div_line_count_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_range), MP_ROM_PTR(&mp_lv_chart_set_range_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_type), MP_ROM_PTR(&mp_lv_chart_set_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_point_count), MP_ROM_PTR(&mp_lv_chart_set_point_count_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_series_opa), MP_ROM_PTR(&mp_lv_chart_set_series_opa_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_series_width), MP_ROM_PTR(&mp_lv_chart_set_series_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_series_darking), MP_ROM_PTR(&mp_lv_chart_set_series_darking_obj) },
    { MP_ROM_QSTR(MP_QSTR_init_points), MP_ROM_PTR(&mp_lv_chart_init_points_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_points), MP_ROM_PTR(&mp_lv_chart_set_points_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_next), MP_ROM_PTR(&mp_lv_chart_set_next_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_update_mode), MP_ROM_PTR(&mp_lv_chart_set_update_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_margin), MP_ROM_PTR(&mp_lv_chart_set_margin_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x_ticks), MP_ROM_PTR(&mp_lv_chart_set_x_ticks_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y_ticks), MP_ROM_PTR(&mp_lv_chart_set_y_ticks_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_chart_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_point_cnt), MP_ROM_PTR(&mp_lv_chart_get_point_cnt_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_series_opa), MP_ROM_PTR(&mp_lv_chart_get_series_opa_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_series_width), MP_ROM_PTR(&mp_lv_chart_get_series_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_series_darking), MP_ROM_PTR(&mp_lv_chart_get_series_darking_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_margin), MP_ROM_PTR(&mp_lv_chart_get_margin_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh), MP_ROM_PTR(&mp_lv_chart_refresh_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_TYPE), MP_ROM_PTR(&mp_LV_CHART_TYPE_type) },
    { MP_ROM_QSTR(MP_QSTR_UPDATE_MODE), MP_ROM_PTR(&mp_LV_CHART_UPDATE_MODE_type) },
    { MP_ROM_QSTR(MP_QSTR_AXIS_DRAW_LAST), MP_ROM_PTR(&mp_LV_CHART_AXIS_DRAW_LAST_type) }
};

STATIC MP_DEFINE_CONST_DICT(chart_locals_dict, chart_locals_dict_table);

STATIC void chart_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl chart");
}


STATIC mp_obj_t chart_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_chart_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_chart_type = {
    { &mp_type_type },
    .name = MP_QSTR_chart,
    .print = chart_print,
    .make_new = chart_make_new,
    .locals_dict = (mp_obj_dict_t*)&chart_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * void lv_table_set_cell_value(lv_obj_t *table, uint16_t row, uint16_t col, const char *txt)
 */
 
STATIC mp_obj_t mp_lv_table_set_cell_value(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t row = (uint16_t)mp_obj_get_int(args[1]);
    uint16_t col = (uint16_t)mp_obj_get_int(args[2]);
    const char *txt = (char*)mp_obj_str_get_str(args[3]);
    lv_table_set_cell_value(table, row, col, txt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_set_cell_value_obj, 4, 4, mp_lv_table_set_cell_value);

 

/*
 * lvgl extension definition for:
 * void lv_table_set_row_cnt(lv_obj_t *table, uint16_t row_cnt)
 */
 
STATIC mp_obj_t mp_lv_table_set_row_cnt(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t row_cnt = (uint16_t)mp_obj_get_int(args[1]);
    lv_table_set_row_cnt(table, row_cnt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_set_row_cnt_obj, 2, 2, mp_lv_table_set_row_cnt);

 

/*
 * lvgl extension definition for:
 * void lv_table_set_col_cnt(lv_obj_t *table, uint16_t col_cnt)
 */
 
STATIC mp_obj_t mp_lv_table_set_col_cnt(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t col_cnt = (uint16_t)mp_obj_get_int(args[1]);
    lv_table_set_col_cnt(table, col_cnt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_set_col_cnt_obj, 2, 2, mp_lv_table_set_col_cnt);

 

/*
 * lvgl extension definition for:
 * void lv_table_set_col_width(lv_obj_t *table, uint16_t col_id, lv_coord_t w)
 */
 
STATIC mp_obj_t mp_lv_table_set_col_width(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t col_id = (uint16_t)mp_obj_get_int(args[1]);
    lv_coord_t w = (int16_t)mp_obj_get_int(args[2]);
    lv_table_set_col_width(table, col_id, w);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_set_col_width_obj, 3, 3, mp_lv_table_set_col_width);

 

/*
 * lvgl extension definition for:
 * void lv_table_set_cell_align(lv_obj_t *table, uint16_t row, uint16_t col, lv_label_align_t align)
 */
 
STATIC mp_obj_t mp_lv_table_set_cell_align(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t row = (uint16_t)mp_obj_get_int(args[1]);
    uint16_t col = (uint16_t)mp_obj_get_int(args[2]);
    lv_label_align_t align = (uint8_t)mp_obj_get_int(args[3]);
    lv_table_set_cell_align(table, row, col, align);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_set_cell_align_obj, 4, 4, mp_lv_table_set_cell_align);

 

/*
 * lvgl extension definition for:
 * void lv_table_set_cell_type(lv_obj_t *table, uint16_t row, uint16_t col, uint8_t type)
 */
 
STATIC mp_obj_t mp_lv_table_set_cell_type(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t row = (uint16_t)mp_obj_get_int(args[1]);
    uint16_t col = (uint16_t)mp_obj_get_int(args[2]);
    uint8_t type = (uint8_t)mp_obj_get_int(args[3]);
    lv_table_set_cell_type(table, row, col, type);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_set_cell_type_obj, 4, 4, mp_lv_table_set_cell_type);

 

/*
 * lvgl extension definition for:
 * void lv_table_set_cell_crop(lv_obj_t *table, uint16_t row, uint16_t col, bool crop)
 */
 
STATIC mp_obj_t mp_lv_table_set_cell_crop(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t row = (uint16_t)mp_obj_get_int(args[1]);
    uint16_t col = (uint16_t)mp_obj_get_int(args[2]);
    bool crop = mp_obj_is_true(args[3]);
    lv_table_set_cell_crop(table, row, col, crop);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_set_cell_crop_obj, 4, 4, mp_lv_table_set_cell_crop);

 

/*
 * lvgl extension definition for:
 * void lv_table_set_cell_merge_right(lv_obj_t *table, uint16_t row, uint16_t col, bool en)
 */
 
STATIC mp_obj_t mp_lv_table_set_cell_merge_right(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t row = (uint16_t)mp_obj_get_int(args[1]);
    uint16_t col = (uint16_t)mp_obj_get_int(args[2]);
    bool en = mp_obj_is_true(args[3]);
    lv_table_set_cell_merge_right(table, row, col, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_set_cell_merge_right_obj, 4, 4, mp_lv_table_set_cell_merge_right);

 

/*
 * lvgl extension definition for:
 * void lv_table_set_style(lv_obj_t *table, lv_table_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_table_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    lv_table_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_table_set_style(table, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_set_style_obj, 3, 3, mp_lv_table_set_style);

 

/*
 * lvgl extension definition for:
 * const char *lv_table_get_cell_value(lv_obj_t *table, uint16_t row, uint16_t col)
 */
 
STATIC mp_obj_t mp_lv_table_get_cell_value(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t row = (uint16_t)mp_obj_get_int(args[1]);
    uint16_t col = (uint16_t)mp_obj_get_int(args[2]);
    const char * res = lv_table_get_cell_value(table, row, col);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_get_cell_value_obj, 3, 3, mp_lv_table_get_cell_value);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_table_get_row_cnt(lv_obj_t *table)
 */
 
STATIC mp_obj_t mp_lv_table_get_row_cnt(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t res = lv_table_get_row_cnt(table);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_get_row_cnt_obj, 1, 1, mp_lv_table_get_row_cnt);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_table_get_col_cnt(lv_obj_t *table)
 */
 
STATIC mp_obj_t mp_lv_table_get_col_cnt(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t res = lv_table_get_col_cnt(table);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_get_col_cnt_obj, 1, 1, mp_lv_table_get_col_cnt);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_table_get_col_width(lv_obj_t *table, uint16_t col_id)
 */
 
STATIC mp_obj_t mp_lv_table_get_col_width(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t col_id = (uint16_t)mp_obj_get_int(args[1]);
    lv_coord_t res = lv_table_get_col_width(table, col_id);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_get_col_width_obj, 2, 2, mp_lv_table_get_col_width);

 

/*
 * lvgl extension definition for:
 * lv_label_align_t lv_table_get_cell_align(lv_obj_t *table, uint16_t row, uint16_t col)
 */
 
STATIC mp_obj_t mp_lv_table_get_cell_align(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t row = (uint16_t)mp_obj_get_int(args[1]);
    uint16_t col = (uint16_t)mp_obj_get_int(args[2]);
    lv_label_align_t res = lv_table_get_cell_align(table, row, col);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_get_cell_align_obj, 3, 3, mp_lv_table_get_cell_align);

 

/*
 * lvgl extension definition for:
 * lv_label_align_t lv_table_get_cell_type(lv_obj_t *table, uint16_t row, uint16_t col)
 */
 
STATIC mp_obj_t mp_lv_table_get_cell_type(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t row = (uint16_t)mp_obj_get_int(args[1]);
    uint16_t col = (uint16_t)mp_obj_get_int(args[2]);
    lv_label_align_t res = lv_table_get_cell_type(table, row, col);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_get_cell_type_obj, 3, 3, mp_lv_table_get_cell_type);

 

/*
 * lvgl extension definition for:
 * lv_label_align_t lv_table_get_cell_crop(lv_obj_t *table, uint16_t row, uint16_t col)
 */
 
STATIC mp_obj_t mp_lv_table_get_cell_crop(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t row = (uint16_t)mp_obj_get_int(args[1]);
    uint16_t col = (uint16_t)mp_obj_get_int(args[2]);
    lv_label_align_t res = lv_table_get_cell_crop(table, row, col);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_get_cell_crop_obj, 3, 3, mp_lv_table_get_cell_crop);

 

/*
 * lvgl extension definition for:
 * bool lv_table_get_cell_merge_right(lv_obj_t *table, uint16_t row, uint16_t col)
 */
 
STATIC mp_obj_t mp_lv_table_get_cell_merge_right(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *table = mp_to_lv(args[0]);
    uint16_t row = (uint16_t)mp_obj_get_int(args[1]);
    uint16_t col = (uint16_t)mp_obj_get_int(args[2]);
    bool res = lv_table_get_cell_merge_right(table, row, col);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_table_get_cell_merge_right_obj, 3, 3, mp_lv_table_get_cell_merge_right);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_table_get_style(const lv_obj_t *table, lv_table_style_t type)
 */
    

/*
 * lvgl table object definitions
 */
    

STATIC const mp_rom_map_elem_t table_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_cell_value), MP_ROM_PTR(&mp_lv_table_set_cell_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_row_cnt), MP_ROM_PTR(&mp_lv_table_set_row_cnt_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_col_cnt), MP_ROM_PTR(&mp_lv_table_set_col_cnt_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_col_width), MP_ROM_PTR(&mp_lv_table_set_col_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_cell_align), MP_ROM_PTR(&mp_lv_table_set_cell_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_cell_type), MP_ROM_PTR(&mp_lv_table_set_cell_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_cell_crop), MP_ROM_PTR(&mp_lv_table_set_cell_crop_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_cell_merge_right), MP_ROM_PTR(&mp_lv_table_set_cell_merge_right_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_table_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_cell_value), MP_ROM_PTR(&mp_lv_table_get_cell_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_row_cnt), MP_ROM_PTR(&mp_lv_table_get_row_cnt_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_col_cnt), MP_ROM_PTR(&mp_lv_table_get_col_cnt_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_col_width), MP_ROM_PTR(&mp_lv_table_get_col_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_cell_align), MP_ROM_PTR(&mp_lv_table_get_cell_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_cell_type), MP_ROM_PTR(&mp_lv_table_get_cell_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_cell_crop), MP_ROM_PTR(&mp_lv_table_get_cell_crop_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_cell_merge_right), MP_ROM_PTR(&mp_lv_table_get_cell_merge_right_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_TABLE_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(table_locals_dict, table_locals_dict_table);

STATIC void table_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl table");
}


STATIC mp_obj_t table_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_table_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_table_type = {
    { &mp_type_type },
    .name = MP_QSTR_table,
    .print = table_print,
    .make_new = table_make_new,
    .locals_dict = (mp_obj_dict_t*)&table_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_cb_set_checked(lv_obj_t *cb, bool checked)
 */
 
STATIC mp_obj_t mp_lv_cb_set_checked(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *cb = mp_to_lv(args[0]);
    bool checked = mp_obj_is_true(args[1]);
    lv_cb_set_checked(cb, checked);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cb_set_checked_obj, 2, 2, mp_lv_cb_set_checked);

 

/*
 * lvgl extension definition for:
 * inline static void lv_cb_set_inactive(lv_obj_t *cb)
 */
 
STATIC mp_obj_t mp_lv_cb_set_inactive(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *cb = mp_to_lv(args[0]);
    lv_cb_set_inactive(cb);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cb_set_inactive_obj, 1, 1, mp_lv_cb_set_inactive);

 

/*
 * lvgl extension definition for:
 * inline static bool lv_cb_is_checked(const lv_obj_t *cb)
 */
 
STATIC mp_obj_t mp_lv_cb_is_checked(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *cb = mp_to_lv(args[0]);
    bool res = lv_cb_is_checked(cb);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cb_is_checked_obj, 1, 1, mp_lv_cb_is_checked);

 

/*
 * lvgl extension definition for:
 * void lv_cb_set_text(lv_obj_t *cb, const char *txt)
 */
 
STATIC mp_obj_t mp_lv_cb_set_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *cb = mp_to_lv(args[0]);
    const char *txt = (char*)mp_obj_str_get_str(args[1]);
    lv_cb_set_text(cb, txt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cb_set_text_obj, 2, 2, mp_lv_cb_set_text);

 

/*
 * lvgl extension definition for:
 * void lv_cb_set_static_text(lv_obj_t *cb, const char *txt)
 */
 
STATIC mp_obj_t mp_lv_cb_set_static_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *cb = mp_to_lv(args[0]);
    const char *txt = (char*)mp_obj_str_get_str(args[1]);
    lv_cb_set_static_text(cb, txt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cb_set_static_text_obj, 2, 2, mp_lv_cb_set_static_text);

 

/*
 * lvgl extension definition for:
 * void lv_cb_set_style(lv_obj_t *cb, lv_cb_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_cb_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *cb = mp_to_lv(args[0]);
    lv_cb_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_cb_set_style(cb, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cb_set_style_obj, 3, 3, mp_lv_cb_set_style);

 

/*
 * lvgl extension definition for:
 * const char *lv_cb_get_text(const lv_obj_t *cb)
 */
 
STATIC mp_obj_t mp_lv_cb_get_text(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *cb = mp_to_lv(args[0]);
    const char * res = lv_cb_get_text(cb);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_cb_get_text_obj, 1, 1, mp_lv_cb_get_text);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_cb_get_style(const lv_obj_t *cb, lv_cb_style_t type)
 */
    

/*
 * lvgl cb object definitions
 */
    

STATIC const mp_rom_map_elem_t cb_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_checked), MP_ROM_PTR(&mp_lv_cb_set_checked_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_inactive), MP_ROM_PTR(&mp_lv_cb_set_inactive_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_checked), MP_ROM_PTR(&mp_lv_cb_is_checked_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_text), MP_ROM_PTR(&mp_lv_cb_set_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_static_text), MP_ROM_PTR(&mp_lv_cb_set_static_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_cb_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_text), MP_ROM_PTR(&mp_lv_cb_get_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_CB_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(cb_locals_dict, cb_locals_dict_table);

STATIC void cb_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl cb");
}


STATIC mp_obj_t cb_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_cb_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_cb_type = {
    { &mp_type_type },
    .name = MP_QSTR_cb,
    .print = cb_print,
    .make_new = cb_make_new,
    .locals_dict = (mp_obj_dict_t*)&cb_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * void lv_bar_set_value(lv_obj_t *bar, int16_t value, bool anim)
 */
 
STATIC mp_obj_t mp_lv_bar_set_value(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *bar = mp_to_lv(args[0]);
    int16_t value = (int16_t)mp_obj_get_int(args[1]);
    bool anim = mp_obj_is_true(args[2]);
    lv_bar_set_value(bar, value, anim);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_bar_set_value_obj, 3, 3, mp_lv_bar_set_value);

 

/*
 * lvgl extension definition for:
 * void lv_bar_set_range(lv_obj_t *bar, int16_t min, int16_t max)
 */
 
STATIC mp_obj_t mp_lv_bar_set_range(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *bar = mp_to_lv(args[0]);
    int16_t min = (int16_t)mp_obj_get_int(args[1]);
    int16_t max = (int16_t)mp_obj_get_int(args[2]);
    lv_bar_set_range(bar, min, max);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_bar_set_range_obj, 3, 3, mp_lv_bar_set_range);

 

/*
 * lvgl extension definition for:
 * void lv_bar_set_sym(lv_obj_t *bar, bool en)
 */
 
STATIC mp_obj_t mp_lv_bar_set_sym(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *bar = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_bar_set_sym(bar, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_bar_set_sym_obj, 2, 2, mp_lv_bar_set_sym);

 

/*
 * lvgl extension definition for:
 * void lv_bar_set_style(lv_obj_t *bar, lv_bar_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_bar_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *bar = mp_to_lv(args[0]);
    lv_bar_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_bar_set_style(bar, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_bar_set_style_obj, 3, 3, mp_lv_bar_set_style);

 

/*
 * lvgl extension definition for:
 * int16_t lv_bar_get_value(const lv_obj_t *bar)
 */
 
STATIC mp_obj_t mp_lv_bar_get_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *bar = mp_to_lv(args[0]);
    int16_t res = lv_bar_get_value(bar);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_bar_get_value_obj, 1, 1, mp_lv_bar_get_value);

 

/*
 * lvgl extension definition for:
 * int16_t lv_bar_get_min_value(const lv_obj_t *bar)
 */
 
STATIC mp_obj_t mp_lv_bar_get_min_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *bar = mp_to_lv(args[0]);
    int16_t res = lv_bar_get_min_value(bar);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_bar_get_min_value_obj, 1, 1, mp_lv_bar_get_min_value);

 

/*
 * lvgl extension definition for:
 * int16_t lv_bar_get_max_value(const lv_obj_t *bar)
 */
 
STATIC mp_obj_t mp_lv_bar_get_max_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *bar = mp_to_lv(args[0]);
    int16_t res = lv_bar_get_max_value(bar);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_bar_get_max_value_obj, 1, 1, mp_lv_bar_get_max_value);

 

/*
 * lvgl extension definition for:
 * bool lv_bar_get_sym(lv_obj_t *bar)
 */
 
STATIC mp_obj_t mp_lv_bar_get_sym(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *bar = mp_to_lv(args[0]);
    bool res = lv_bar_get_sym(bar);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_bar_get_sym_obj, 1, 1, mp_lv_bar_get_sym);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_bar_get_style(const lv_obj_t *bar, lv_bar_style_t type)
 */
    

/*
 * lvgl bar object definitions
 */
    

STATIC const mp_rom_map_elem_t bar_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_value), MP_ROM_PTR(&mp_lv_bar_set_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_range), MP_ROM_PTR(&mp_lv_bar_set_range_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_sym), MP_ROM_PTR(&mp_lv_bar_set_sym_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_bar_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_value), MP_ROM_PTR(&mp_lv_bar_get_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_min_value), MP_ROM_PTR(&mp_lv_bar_get_min_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_max_value), MP_ROM_PTR(&mp_lv_bar_get_max_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_sym), MP_ROM_PTR(&mp_lv_bar_get_sym_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_BAR_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(bar_locals_dict, bar_locals_dict_table);

STATIC void bar_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl bar");
}


STATIC mp_obj_t bar_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_bar_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_bar_type = {
    { &mp_type_type },
    .name = MP_QSTR_bar,
    .print = bar_print,
    .make_new = bar_make_new,
    .locals_dict = (mp_obj_dict_t*)&bar_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_slider_set_value(lv_obj_t *slider, int16_t value, bool anim)
 */
 
STATIC mp_obj_t mp_lv_slider_set_value(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *slider = mp_to_lv(args[0]);
    int16_t value = (int16_t)mp_obj_get_int(args[1]);
    bool anim = mp_obj_is_true(args[2]);
    lv_slider_set_value(slider, value, anim);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_slider_set_value_obj, 3, 3, mp_lv_slider_set_value);

 

/*
 * lvgl extension definition for:
 * inline static void lv_slider_set_range(lv_obj_t *slider, int16_t min, int16_t max)
 */
 
STATIC mp_obj_t mp_lv_slider_set_range(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *slider = mp_to_lv(args[0]);
    int16_t min = (int16_t)mp_obj_get_int(args[1]);
    int16_t max = (int16_t)mp_obj_get_int(args[2]);
    lv_slider_set_range(slider, min, max);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_slider_set_range_obj, 3, 3, mp_lv_slider_set_range);

 

/*
 * lvgl extension definition for:
 * inline static int16_t lv_slider_get_min_value(const lv_obj_t *slider)
 */
 
STATIC mp_obj_t mp_lv_slider_get_min_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *slider = mp_to_lv(args[0]);
    int16_t res = lv_slider_get_min_value(slider);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_slider_get_min_value_obj, 1, 1, mp_lv_slider_get_min_value);

 

/*
 * lvgl extension definition for:
 * inline static int16_t lv_slider_get_max_value(const lv_obj_t *slider)
 */
 
STATIC mp_obj_t mp_lv_slider_get_max_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *slider = mp_to_lv(args[0]);
    int16_t res = lv_slider_get_max_value(slider);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_slider_get_max_value_obj, 1, 1, mp_lv_slider_get_max_value);

 

/*
 * lvgl extension definition for:
 * void lv_slider_set_knob_in(lv_obj_t *slider, bool in)
 */
 
STATIC mp_obj_t mp_lv_slider_set_knob_in(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *slider = mp_to_lv(args[0]);
    bool in = mp_obj_is_true(args[1]);
    lv_slider_set_knob_in(slider, in);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_slider_set_knob_in_obj, 2, 2, mp_lv_slider_set_knob_in);

 

/*
 * lvgl extension definition for:
 * void lv_slider_set_style(lv_obj_t *slider, lv_slider_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_slider_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *slider = mp_to_lv(args[0]);
    lv_slider_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_slider_set_style(slider, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_slider_set_style_obj, 3, 3, mp_lv_slider_set_style);

 

/*
 * lvgl extension definition for:
 * int16_t lv_slider_get_value(const lv_obj_t *slider)
 */
 
STATIC mp_obj_t mp_lv_slider_get_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *slider = mp_to_lv(args[0]);
    int16_t res = lv_slider_get_value(slider);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_slider_get_value_obj, 1, 1, mp_lv_slider_get_value);

 

/*
 * lvgl extension definition for:
 * bool lv_slider_is_dragged(const lv_obj_t *slider)
 */
 
STATIC mp_obj_t mp_lv_slider_is_dragged(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *slider = mp_to_lv(args[0]);
    bool res = lv_slider_is_dragged(slider);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_slider_is_dragged_obj, 1, 1, mp_lv_slider_is_dragged);

 

/*
 * lvgl extension definition for:
 * bool lv_slider_get_knob_in(const lv_obj_t *slider)
 */
 
STATIC mp_obj_t mp_lv_slider_get_knob_in(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *slider = mp_to_lv(args[0]);
    bool res = lv_slider_get_knob_in(slider);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_slider_get_knob_in_obj, 1, 1, mp_lv_slider_get_knob_in);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_slider_get_style(const lv_obj_t *slider, lv_slider_style_t type)
 */
    

/*
 * lvgl slider object definitions
 */
    

STATIC const mp_rom_map_elem_t slider_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_value), MP_ROM_PTR(&mp_lv_slider_set_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_range), MP_ROM_PTR(&mp_lv_slider_set_range_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_min_value), MP_ROM_PTR(&mp_lv_slider_get_min_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_max_value), MP_ROM_PTR(&mp_lv_slider_get_max_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_knob_in), MP_ROM_PTR(&mp_lv_slider_set_knob_in_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_slider_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_value), MP_ROM_PTR(&mp_lv_slider_get_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_dragged), MP_ROM_PTR(&mp_lv_slider_is_dragged_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_knob_in), MP_ROM_PTR(&mp_lv_slider_get_knob_in_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_SLIDER_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(slider_locals_dict, slider_locals_dict_table);

STATIC void slider_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl slider");
}


STATIC mp_obj_t slider_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_slider_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_slider_type = {
    { &mp_type_type },
    .name = MP_QSTR_slider,
    .print = slider_print,
    .make_new = slider_make_new,
    .locals_dict = (mp_obj_dict_t*)&slider_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_led_set_style(lv_obj_t *led, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_led_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *led = mp_to_lv(args[0]);
    const lv_style_t *style = mp_to_ptr(args[1]);
    lv_led_set_style(led, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_led_set_style_obj, 2, 2, mp_lv_led_set_style);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * inline static const lv_style_t *lv_led_get_style(const lv_obj_t *led)
 */
    

/*
 * lvgl extension definition for:
 * void lv_led_set_bright(lv_obj_t *led, uint8_t bright)
 */
 
STATIC mp_obj_t mp_lv_led_set_bright(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *led = mp_to_lv(args[0]);
    uint8_t bright = (uint8_t)mp_obj_get_int(args[1]);
    lv_led_set_bright(led, bright);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_led_set_bright_obj, 2, 2, mp_lv_led_set_bright);

 

/*
 * lvgl extension definition for:
 * void lv_led_on(lv_obj_t *led)
 */
 
STATIC mp_obj_t mp_lv_led_on(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *led = mp_to_lv(args[0]);
    lv_led_on(led);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_led_on_obj, 1, 1, mp_lv_led_on);

 

/*
 * lvgl extension definition for:
 * void lv_led_off(lv_obj_t *led)
 */
 
STATIC mp_obj_t mp_lv_led_off(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *led = mp_to_lv(args[0]);
    lv_led_off(led);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_led_off_obj, 1, 1, mp_lv_led_off);

 

/*
 * lvgl extension definition for:
 * void lv_led_toggle(lv_obj_t *led)
 */
 
STATIC mp_obj_t mp_lv_led_toggle(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *led = mp_to_lv(args[0]);
    lv_led_toggle(led);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_led_toggle_obj, 1, 1, mp_lv_led_toggle);

 

/*
 * lvgl extension definition for:
 * uint8_t lv_led_get_bright(const lv_obj_t *led)
 */
 
STATIC mp_obj_t mp_lv_led_get_bright(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *led = mp_to_lv(args[0]);
    uint8_t res = lv_led_get_bright(led);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_led_get_bright_obj, 1, 1, mp_lv_led_get_bright);

 

/*
 * lvgl led object definitions
 */
    

STATIC const mp_rom_map_elem_t led_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_led_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_bright), MP_ROM_PTR(&mp_lv_led_set_bright_obj) },
    { MP_ROM_QSTR(MP_QSTR_on), MP_ROM_PTR(&mp_lv_led_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_off), MP_ROM_PTR(&mp_lv_led_off_obj) },
    { MP_ROM_QSTR(MP_QSTR_toggle), MP_ROM_PTR(&mp_lv_led_toggle_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_bright), MP_ROM_PTR(&mp_lv_led_get_bright_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) }
};

STATIC MP_DEFINE_CONST_DICT(led_locals_dict, led_locals_dict_table);

STATIC void led_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl led");
}


STATIC mp_obj_t led_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_led_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_led_type = {
    { &mp_type_type },
    .name = MP_QSTR_led,
    .print = led_print,
    .make_new = led_make_new,
    .locals_dict = (mp_obj_dict_t*)&led_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * void lv_btnm_set_map(const lv_obj_t *btnm, const char *map[])
 */
 
STATIC mp_obj_t mp_lv_btnm_set_map(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btnm = mp_to_lv(args[0]);
    const char **map = mp_to_ptr(args[1]);
    lv_btnm_set_map(btnm, map);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_set_map_obj, 2, 2, mp_lv_btnm_set_map);

 

/*
 * lvgl extension definition for:
 * void lv_btnm_set_ctrl_map(const lv_obj_t *btnm, const lv_btnm_ctrl_t ctrl_map[])
 */
 
STATIC mp_obj_t mp_lv_btnm_set_ctrl_map(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btnm = mp_to_lv(args[0]);
    const lv_btnm_ctrl_t *ctrl_map = mp_to_ptr(args[1]);
    lv_btnm_set_ctrl_map(btnm, ctrl_map);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_set_ctrl_map_obj, 2, 2, mp_lv_btnm_set_ctrl_map);

 

/*
 * lvgl extension definition for:
 * void lv_btnm_set_pressed(const lv_obj_t *btnm, uint16_t id)
 */
 
STATIC mp_obj_t mp_lv_btnm_set_pressed(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btnm = mp_to_lv(args[0]);
    uint16_t id = (uint16_t)mp_obj_get_int(args[1]);
    lv_btnm_set_pressed(btnm, id);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_set_pressed_obj, 2, 2, mp_lv_btnm_set_pressed);

 

/*
 * lvgl extension definition for:
 * void lv_btnm_set_style(lv_obj_t *btnm, lv_btnm_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_btnm_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btnm = mp_to_lv(args[0]);
    lv_btnm_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_btnm_set_style(btnm, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_set_style_obj, 3, 3, mp_lv_btnm_set_style);

 

/*
 * lvgl extension definition for:
 * void lv_btnm_set_recolor(const lv_obj_t *btnm, bool en)
 */
 
STATIC mp_obj_t mp_lv_btnm_set_recolor(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btnm = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_btnm_set_recolor(btnm, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_set_recolor_obj, 2, 2, mp_lv_btnm_set_recolor);

 

/*
 * lvgl extension definition for:
 * void lv_btnm_set_btn_ctrl(const lv_obj_t *btnm, uint16_t btn_id, lv_btnm_ctrl_t ctrl, bool en)
 */
 
STATIC mp_obj_t mp_lv_btnm_set_btn_ctrl(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btnm = mp_to_lv(args[0]);
    uint16_t btn_id = (uint16_t)mp_obj_get_int(args[1]);
    lv_btnm_ctrl_t ctrl = (uint16_t)mp_obj_get_int(args[2]);
    bool en = mp_obj_is_true(args[3]);
    lv_btnm_set_btn_ctrl(btnm, btn_id, ctrl, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_set_btn_ctrl_obj, 4, 4, mp_lv_btnm_set_btn_ctrl);

 

/*
 * lvgl extension definition for:
 * void lv_btnm_set_btn_ctrl_all(lv_obj_t *btnm, lv_btnm_ctrl_t ctrl, bool en)
 */
 
STATIC mp_obj_t mp_lv_btnm_set_btn_ctrl_all(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btnm = mp_to_lv(args[0]);
    lv_btnm_ctrl_t ctrl = (uint16_t)mp_obj_get_int(args[1]);
    bool en = mp_obj_is_true(args[2]);
    lv_btnm_set_btn_ctrl_all(btnm, ctrl, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_set_btn_ctrl_all_obj, 3, 3, mp_lv_btnm_set_btn_ctrl_all);

 

/*
 * lvgl extension definition for:
 * void lv_btnm_set_btn_width(const lv_obj_t *btnm, uint16_t btn_id, uint8_t width)
 */
 
STATIC mp_obj_t mp_lv_btnm_set_btn_width(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btnm = mp_to_lv(args[0]);
    uint16_t btn_id = (uint16_t)mp_obj_get_int(args[1]);
    uint8_t width = (uint8_t)mp_obj_get_int(args[2]);
    lv_btnm_set_btn_width(btnm, btn_id, width);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_set_btn_width_obj, 3, 3, mp_lv_btnm_set_btn_width);

 

/*
 * lvgl extension definition for:
 * void lv_btnm_set_one_toggle(lv_obj_t *btnm, bool one_toggle)
 */
 
STATIC mp_obj_t mp_lv_btnm_set_one_toggle(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btnm = mp_to_lv(args[0]);
    bool one_toggle = mp_obj_is_true(args[1]);
    lv_btnm_set_one_toggle(btnm, one_toggle);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_set_one_toggle_obj, 2, 2, mp_lv_btnm_set_one_toggle);

 

/*
 * Function NOT generated:
 * Missing convertion from const char **
 * const char **lv_btnm_get_map_array(const lv_obj_t *btnm)
 */
    

/*
 * lvgl extension definition for:
 * bool lv_btnm_get_recolor(const lv_obj_t *btnm)
 */
 
STATIC mp_obj_t mp_lv_btnm_get_recolor(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btnm = mp_to_lv(args[0]);
    bool res = lv_btnm_get_recolor(btnm);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_get_recolor_obj, 1, 1, mp_lv_btnm_get_recolor);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_btnm_get_active_btn(const lv_obj_t *btnm)
 */
 
STATIC mp_obj_t mp_lv_btnm_get_active_btn(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btnm = mp_to_lv(args[0]);
    uint16_t res = lv_btnm_get_active_btn(btnm);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_get_active_btn_obj, 1, 1, mp_lv_btnm_get_active_btn);

 

/*
 * lvgl extension definition for:
 * const char *lv_btnm_get_active_btn_text(const lv_obj_t *btnm)
 */
 
STATIC mp_obj_t mp_lv_btnm_get_active_btn_text(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btnm = mp_to_lv(args[0]);
    const char * res = lv_btnm_get_active_btn_text(btnm);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_get_active_btn_text_obj, 1, 1, mp_lv_btnm_get_active_btn_text);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_btnm_get_pressed_btn(const lv_obj_t *btnm)
 */
 
STATIC mp_obj_t mp_lv_btnm_get_pressed_btn(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btnm = mp_to_lv(args[0]);
    uint16_t res = lv_btnm_get_pressed_btn(btnm);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_get_pressed_btn_obj, 1, 1, mp_lv_btnm_get_pressed_btn);

 

/*
 * lvgl extension definition for:
 * const char *lv_btnm_get_btn_text(const lv_obj_t *btnm, uint16_t btn_id)
 */
 
STATIC mp_obj_t mp_lv_btnm_get_btn_text(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btnm = mp_to_lv(args[0]);
    uint16_t btn_id = (uint16_t)mp_obj_get_int(args[1]);
    const char * res = lv_btnm_get_btn_text(btnm, btn_id);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_get_btn_text_obj, 2, 2, mp_lv_btnm_get_btn_text);

 

/*
 * lvgl extension definition for:
 * bool lv_btnm_get_btn_ctrl(lv_obj_t *btnm, uint16_t btn_id, lv_btnm_ctrl_t ctrl)
 */
 
STATIC mp_obj_t mp_lv_btnm_get_btn_ctrl(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btnm = mp_to_lv(args[0]);
    uint16_t btn_id = (uint16_t)mp_obj_get_int(args[1]);
    lv_btnm_ctrl_t ctrl = (uint16_t)mp_obj_get_int(args[2]);
    bool res = lv_btnm_get_btn_ctrl(btnm, btn_id, ctrl);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_get_btn_ctrl_obj, 3, 3, mp_lv_btnm_get_btn_ctrl);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_btnm_get_style(const lv_obj_t *btnm, lv_btnm_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * bool lv_btnm_get_one_toggle(const lv_obj_t *btnm)
 */
 
STATIC mp_obj_t mp_lv_btnm_get_one_toggle(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *btnm = mp_to_lv(args[0]);
    bool res = lv_btnm_get_one_toggle(btnm);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_btnm_get_one_toggle_obj, 1, 1, mp_lv_btnm_get_one_toggle);

 

/*
 * lvgl btnm object definitions
 */
    

STATIC const mp_rom_map_elem_t btnm_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_map), MP_ROM_PTR(&mp_lv_btnm_set_map_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_ctrl_map), MP_ROM_PTR(&mp_lv_btnm_set_ctrl_map_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pressed), MP_ROM_PTR(&mp_lv_btnm_set_pressed_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_btnm_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_recolor), MP_ROM_PTR(&mp_lv_btnm_set_recolor_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_btn_ctrl), MP_ROM_PTR(&mp_lv_btnm_set_btn_ctrl_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_btn_ctrl_all), MP_ROM_PTR(&mp_lv_btnm_set_btn_ctrl_all_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_btn_width), MP_ROM_PTR(&mp_lv_btnm_set_btn_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_one_toggle), MP_ROM_PTR(&mp_lv_btnm_set_one_toggle_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_recolor), MP_ROM_PTR(&mp_lv_btnm_get_recolor_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_active_btn), MP_ROM_PTR(&mp_lv_btnm_get_active_btn_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_active_btn_text), MP_ROM_PTR(&mp_lv_btnm_get_active_btn_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_pressed_btn), MP_ROM_PTR(&mp_lv_btnm_get_pressed_btn_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_btn_text), MP_ROM_PTR(&mp_lv_btnm_get_btn_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_btn_ctrl), MP_ROM_PTR(&mp_lv_btnm_get_btn_ctrl_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_one_toggle), MP_ROM_PTR(&mp_lv_btnm_get_one_toggle_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_CTRL), MP_ROM_PTR(&mp_LV_BTNM_CTRL_type) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_BTNM_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(btnm_locals_dict, btnm_locals_dict_table);

STATIC void btnm_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl btnm");
}


STATIC mp_obj_t btnm_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_btnm_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_btnm_type = {
    { &mp_type_type },
    .name = MP_QSTR_btnm,
    .print = btnm_print,
    .make_new = btnm_make_new,
    .locals_dict = (mp_obj_dict_t*)&btnm_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_kb_set_map(lv_obj_t *kb, const char *map[])
 */
 
STATIC mp_obj_t mp_lv_kb_set_map(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *kb = mp_to_lv(args[0]);
    const char **map = mp_to_ptr(args[1]);
    lv_kb_set_map(kb, map);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_kb_set_map_obj, 2, 2, mp_lv_kb_set_map);

 

/*
 * lvgl extension definition for:
 * inline static void lv_kb_set_ctrl_map(lv_obj_t *kb, const lv_btnm_ctrl_t ctrl_map[])
 */
 
STATIC mp_obj_t mp_lv_kb_set_ctrl_map(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *kb = mp_to_lv(args[0]);
    const lv_btnm_ctrl_t *ctrl_map = mp_to_ptr(args[1]);
    lv_kb_set_ctrl_map(kb, ctrl_map);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_kb_set_ctrl_map_obj, 2, 2, mp_lv_kb_set_ctrl_map);

 

/*
 * Function NOT generated:
 * Missing convertion from const char **
 * inline static const char **lv_kb_get_map_array(const lv_obj_t *kb)
 */
    

/*
 * lvgl extension definition for:
 * void lv_kb_set_ta(lv_obj_t *kb, lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_kb_set_ta(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *kb = mp_to_lv(args[0]);
    lv_obj_t *ta = mp_to_lv(args[1]);
    lv_kb_set_ta(kb, ta);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_kb_set_ta_obj, 2, 2, mp_lv_kb_set_ta);

 

/*
 * lvgl extension definition for:
 * void lv_kb_set_mode(lv_obj_t *kb, lv_kb_mode_t mode)
 */
 
STATIC mp_obj_t mp_lv_kb_set_mode(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *kb = mp_to_lv(args[0]);
    lv_kb_mode_t mode = (uint8_t)mp_obj_get_int(args[1]);
    lv_kb_set_mode(kb, mode);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_kb_set_mode_obj, 2, 2, mp_lv_kb_set_mode);

 

/*
 * lvgl extension definition for:
 * void lv_kb_set_cursor_manage(lv_obj_t *kb, bool en)
 */
 
STATIC mp_obj_t mp_lv_kb_set_cursor_manage(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *kb = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_kb_set_cursor_manage(kb, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_kb_set_cursor_manage_obj, 2, 2, mp_lv_kb_set_cursor_manage);

 

/*
 * lvgl extension definition for:
 * void lv_kb_set_style(lv_obj_t *kb, lv_kb_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_kb_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *kb = mp_to_lv(args[0]);
    lv_kb_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_kb_set_style(kb, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_kb_set_style_obj, 3, 3, mp_lv_kb_set_style);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_kb_get_ta(const lv_obj_t *kb)
 */
 
STATIC mp_obj_t mp_lv_kb_get_ta(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *kb = mp_to_lv(args[0]);
    lv_obj_t * res = lv_kb_get_ta(kb);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_kb_get_ta_obj, 1, 1, mp_lv_kb_get_ta);

 

/*
 * lvgl extension definition for:
 * lv_kb_mode_t lv_kb_get_mode(const lv_obj_t *kb)
 */
 
STATIC mp_obj_t mp_lv_kb_get_mode(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *kb = mp_to_lv(args[0]);
    lv_kb_mode_t res = lv_kb_get_mode(kb);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_kb_get_mode_obj, 1, 1, mp_lv_kb_get_mode);

 

/*
 * lvgl extension definition for:
 * bool lv_kb_get_cursor_manage(const lv_obj_t *kb)
 */
 
STATIC mp_obj_t mp_lv_kb_get_cursor_manage(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *kb = mp_to_lv(args[0]);
    bool res = lv_kb_get_cursor_manage(kb);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_kb_get_cursor_manage_obj, 1, 1, mp_lv_kb_get_cursor_manage);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_kb_get_style(const lv_obj_t *kb, lv_kb_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * void lv_kb_def_event_cb(lv_obj_t *kb, lv_event_t event)
 */
 
STATIC mp_obj_t mp_lv_kb_def_event_cb(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *kb = mp_to_lv(args[0]);
    lv_event_t event = (uint8_t)mp_obj_get_int(args[1]);
    lv_kb_def_event_cb(kb, event);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_kb_def_event_cb_obj, 2, 2, mp_lv_kb_def_event_cb);

 

/*
 * lvgl kb object definitions
 */
    

STATIC const mp_rom_map_elem_t kb_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_map), MP_ROM_PTR(&mp_lv_kb_set_map_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_ctrl_map), MP_ROM_PTR(&mp_lv_kb_set_ctrl_map_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_ta), MP_ROM_PTR(&mp_lv_kb_set_ta_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_mode), MP_ROM_PTR(&mp_lv_kb_set_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_cursor_manage), MP_ROM_PTR(&mp_lv_kb_set_cursor_manage_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_kb_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ta), MP_ROM_PTR(&mp_lv_kb_get_ta_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_mode), MP_ROM_PTR(&mp_lv_kb_get_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_cursor_manage), MP_ROM_PTR(&mp_lv_kb_get_cursor_manage_obj) },
    { MP_ROM_QSTR(MP_QSTR_def_event_cb), MP_ROM_PTR(&mp_lv_kb_def_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_MODE), MP_ROM_PTR(&mp_LV_KB_MODE_type) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_KB_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(kb_locals_dict, kb_locals_dict_table);

STATIC void kb_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl kb");
}


STATIC mp_obj_t kb_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_kb_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_kb_type = {
    { &mp_type_type },
    .name = MP_QSTR_kb,
    .print = kb_print,
    .make_new = kb_make_new,
    .locals_dict = (mp_obj_dict_t*)&kb_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_ddlist_set_sb_mode(lv_obj_t *ddlist, lv_sb_mode_t mode)
 */
 
STATIC mp_obj_t mp_lv_ddlist_set_sb_mode(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    lv_sb_mode_t mode = (uint8_t)mp_obj_get_int(args[1]);
    lv_ddlist_set_sb_mode(ddlist, mode);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_set_sb_mode_obj, 2, 2, mp_lv_ddlist_set_sb_mode);

 

/*
 * lvgl extension definition for:
 * inline static lv_sb_mode_t lv_ddlist_get_sb_mode(const lv_obj_t *ddlist)
 */
 
STATIC mp_obj_t mp_lv_ddlist_get_sb_mode(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ddlist = mp_to_lv(args[0]);
    lv_sb_mode_t res = lv_ddlist_get_sb_mode(ddlist);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_get_sb_mode_obj, 1, 1, mp_lv_ddlist_get_sb_mode);

 

/*
 * lvgl extension definition for:
 * void lv_ddlist_set_options(lv_obj_t *ddlist, const char *options)
 */
 
STATIC mp_obj_t mp_lv_ddlist_set_options(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    const char *options = (char*)mp_obj_str_get_str(args[1]);
    lv_ddlist_set_options(ddlist, options);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_set_options_obj, 2, 2, mp_lv_ddlist_set_options);

 

/*
 * lvgl extension definition for:
 * void lv_ddlist_set_selected(lv_obj_t *ddlist, uint16_t sel_opt)
 */
 
STATIC mp_obj_t mp_lv_ddlist_set_selected(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    uint16_t sel_opt = (uint16_t)mp_obj_get_int(args[1]);
    lv_ddlist_set_selected(ddlist, sel_opt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_set_selected_obj, 2, 2, mp_lv_ddlist_set_selected);

 

/*
 * lvgl extension definition for:
 * void lv_ddlist_set_fix_height(lv_obj_t *ddlist, lv_coord_t h)
 */
 
STATIC mp_obj_t mp_lv_ddlist_set_fix_height(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    lv_coord_t h = (int16_t)mp_obj_get_int(args[1]);
    lv_ddlist_set_fix_height(ddlist, h);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_set_fix_height_obj, 2, 2, mp_lv_ddlist_set_fix_height);

 

/*
 * lvgl extension definition for:
 * void lv_ddlist_set_hor_fit(lv_obj_t *ddlist, lv_fit_t fit)
 */
 
STATIC mp_obj_t mp_lv_ddlist_set_hor_fit(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    lv_fit_t fit = (uint8_t)mp_obj_get_int(args[1]);
    lv_ddlist_set_hor_fit(ddlist, fit);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_set_hor_fit_obj, 2, 2, mp_lv_ddlist_set_hor_fit);

 

/*
 * lvgl extension definition for:
 * void lv_ddlist_set_draw_arrow(lv_obj_t *ddlist, bool en)
 */
 
STATIC mp_obj_t mp_lv_ddlist_set_draw_arrow(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_ddlist_set_draw_arrow(ddlist, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_set_draw_arrow_obj, 2, 2, mp_lv_ddlist_set_draw_arrow);

 

/*
 * lvgl extension definition for:
 * void lv_ddlist_set_stay_open(lv_obj_t *ddlist, bool en)
 */
 
STATIC mp_obj_t mp_lv_ddlist_set_stay_open(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_ddlist_set_stay_open(ddlist, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_set_stay_open_obj, 2, 2, mp_lv_ddlist_set_stay_open);

 

/*
 * lvgl extension definition for:
 * void lv_ddlist_set_anim_time(lv_obj_t *ddlist, uint16_t anim_time)
 */
 
STATIC mp_obj_t mp_lv_ddlist_set_anim_time(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    uint16_t anim_time = (uint16_t)mp_obj_get_int(args[1]);
    lv_ddlist_set_anim_time(ddlist, anim_time);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_set_anim_time_obj, 2, 2, mp_lv_ddlist_set_anim_time);

 

/*
 * lvgl extension definition for:
 * void lv_ddlist_set_style(lv_obj_t *ddlist, lv_ddlist_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_ddlist_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    lv_ddlist_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_ddlist_set_style(ddlist, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_set_style_obj, 3, 3, mp_lv_ddlist_set_style);

 

/*
 * lvgl extension definition for:
 * void lv_ddlist_set_align(lv_obj_t *ddlist, lv_label_align_t align)
 */
 
STATIC mp_obj_t mp_lv_ddlist_set_align(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    lv_label_align_t align = (uint8_t)mp_obj_get_int(args[1]);
    lv_ddlist_set_align(ddlist, align);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_set_align_obj, 2, 2, mp_lv_ddlist_set_align);

 

/*
 * lvgl extension definition for:
 * const char *lv_ddlist_get_options(const lv_obj_t *ddlist)
 */
 
STATIC mp_obj_t mp_lv_ddlist_get_options(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ddlist = mp_to_lv(args[0]);
    const char * res = lv_ddlist_get_options(ddlist);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_get_options_obj, 1, 1, mp_lv_ddlist_get_options);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_ddlist_get_selected(const lv_obj_t *ddlist)
 */
 
STATIC mp_obj_t mp_lv_ddlist_get_selected(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ddlist = mp_to_lv(args[0]);
    uint16_t res = lv_ddlist_get_selected(ddlist);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_get_selected_obj, 1, 1, mp_lv_ddlist_get_selected);

 

/*
 * lvgl extension definition for:
 * void lv_ddlist_get_selected_str(const lv_obj_t *ddlist, char *buf, uint16_t buf_size)
 */
 
STATIC mp_obj_t mp_lv_ddlist_get_selected_str(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ddlist = mp_to_lv(args[0]);
    char *buf = (char*)mp_obj_str_get_str(args[1]);
    uint16_t buf_size = (uint16_t)mp_obj_get_int(args[2]);
    lv_ddlist_get_selected_str(ddlist, buf, buf_size);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_get_selected_str_obj, 3, 3, mp_lv_ddlist_get_selected_str);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_ddlist_get_fix_height(const lv_obj_t *ddlist)
 */
 
STATIC mp_obj_t mp_lv_ddlist_get_fix_height(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ddlist = mp_to_lv(args[0]);
    lv_coord_t res = lv_ddlist_get_fix_height(ddlist);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_get_fix_height_obj, 1, 1, mp_lv_ddlist_get_fix_height);

 

/*
 * lvgl extension definition for:
 * bool lv_ddlist_get_draw_arrow(lv_obj_t *ddlist)
 */
 
STATIC mp_obj_t mp_lv_ddlist_get_draw_arrow(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    bool res = lv_ddlist_get_draw_arrow(ddlist);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_get_draw_arrow_obj, 1, 1, mp_lv_ddlist_get_draw_arrow);

 

/*
 * lvgl extension definition for:
 * bool lv_ddlist_get_stay_open(lv_obj_t *ddlist)
 */
 
STATIC mp_obj_t mp_lv_ddlist_get_stay_open(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    bool res = lv_ddlist_get_stay_open(ddlist);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_get_stay_open_obj, 1, 1, mp_lv_ddlist_get_stay_open);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_ddlist_get_anim_time(const lv_obj_t *ddlist)
 */
 
STATIC mp_obj_t mp_lv_ddlist_get_anim_time(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ddlist = mp_to_lv(args[0]);
    uint16_t res = lv_ddlist_get_anim_time(ddlist);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_get_anim_time_obj, 1, 1, mp_lv_ddlist_get_anim_time);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_ddlist_get_style(const lv_obj_t *ddlist, lv_ddlist_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * lv_label_align_t lv_ddlist_get_align(const lv_obj_t *ddlist)
 */
 
STATIC mp_obj_t mp_lv_ddlist_get_align(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ddlist = mp_to_lv(args[0]);
    lv_label_align_t res = lv_ddlist_get_align(ddlist);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_get_align_obj, 1, 1, mp_lv_ddlist_get_align);

 

/*
 * lvgl extension definition for:
 * void lv_ddlist_open(lv_obj_t *ddlist, bool anim_en)
 */
 
STATIC mp_obj_t mp_lv_ddlist_open(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    bool anim_en = mp_obj_is_true(args[1]);
    lv_ddlist_open(ddlist, anim_en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_open_obj, 2, 2, mp_lv_ddlist_open);

 

/*
 * lvgl extension definition for:
 * void lv_ddlist_close(lv_obj_t *ddlist, bool anim_en)
 */
 
STATIC mp_obj_t mp_lv_ddlist_close(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ddlist = mp_to_lv(args[0]);
    bool anim_en = mp_obj_is_true(args[1]);
    lv_ddlist_close(ddlist, anim_en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ddlist_close_obj, 2, 2, mp_lv_ddlist_close);

 

/*
 * lvgl ddlist object definitions
 */
    

STATIC const mp_rom_map_elem_t ddlist_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_sb_mode), MP_ROM_PTR(&mp_lv_ddlist_set_sb_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_sb_mode), MP_ROM_PTR(&mp_lv_ddlist_get_sb_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_options), MP_ROM_PTR(&mp_lv_ddlist_set_options_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_selected), MP_ROM_PTR(&mp_lv_ddlist_set_selected_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_fix_height), MP_ROM_PTR(&mp_lv_ddlist_set_fix_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hor_fit), MP_ROM_PTR(&mp_lv_ddlist_set_hor_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_draw_arrow), MP_ROM_PTR(&mp_lv_ddlist_set_draw_arrow_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_stay_open), MP_ROM_PTR(&mp_lv_ddlist_set_stay_open_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_anim_time), MP_ROM_PTR(&mp_lv_ddlist_set_anim_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_ddlist_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_align), MP_ROM_PTR(&mp_lv_ddlist_set_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_options), MP_ROM_PTR(&mp_lv_ddlist_get_options_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_selected), MP_ROM_PTR(&mp_lv_ddlist_get_selected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_selected_str), MP_ROM_PTR(&mp_lv_ddlist_get_selected_str_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_fix_height), MP_ROM_PTR(&mp_lv_ddlist_get_fix_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_draw_arrow), MP_ROM_PTR(&mp_lv_ddlist_get_draw_arrow_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_stay_open), MP_ROM_PTR(&mp_lv_ddlist_get_stay_open_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_anim_time), MP_ROM_PTR(&mp_lv_ddlist_get_anim_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_align), MP_ROM_PTR(&mp_lv_ddlist_get_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_open), MP_ROM_PTR(&mp_lv_ddlist_open_obj) },
    { MP_ROM_QSTR(MP_QSTR_close), MP_ROM_PTR(&mp_lv_ddlist_close_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_DDLIST_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(ddlist_locals_dict, ddlist_locals_dict_table);

STATIC void ddlist_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl ddlist");
}


STATIC mp_obj_t ddlist_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_ddlist_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_ddlist_type = {
    { &mp_type_type },
    .name = MP_QSTR_ddlist,
    .print = ddlist_print,
    .make_new = ddlist_make_new,
    .locals_dict = (mp_obj_dict_t*)&ddlist_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_roller_set_hor_fit(lv_obj_t *roller, lv_fit_t fit)
 */
 
STATIC mp_obj_t mp_lv_roller_set_hor_fit(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *roller = mp_to_lv(args[0]);
    lv_fit_t fit = (uint8_t)mp_obj_get_int(args[1]);
    lv_roller_set_hor_fit(roller, fit);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_set_hor_fit_obj, 2, 2, mp_lv_roller_set_hor_fit);

 

/*
 * lvgl extension definition for:
 * inline static void lv_roller_set_anim_time(lv_obj_t *roller, uint16_t anim_time)
 */
 
STATIC mp_obj_t mp_lv_roller_set_anim_time(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *roller = mp_to_lv(args[0]);
    uint16_t anim_time = (uint16_t)mp_obj_get_int(args[1]);
    lv_roller_set_anim_time(roller, anim_time);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_set_anim_time_obj, 2, 2, mp_lv_roller_set_anim_time);

 

/*
 * lvgl extension definition for:
 * inline static void lv_roller_get_selected_str(const lv_obj_t *roller, char *buf, uint16_t buf_size)
 */
 
STATIC mp_obj_t mp_lv_roller_get_selected_str(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *roller = mp_to_lv(args[0]);
    char *buf = (char*)mp_obj_str_get_str(args[1]);
    uint16_t buf_size = (uint16_t)mp_obj_get_int(args[2]);
    lv_roller_get_selected_str(roller, buf, buf_size);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_get_selected_str_obj, 3, 3, mp_lv_roller_get_selected_str);

 

/*
 * lvgl extension definition for:
 * inline static const char *lv_roller_get_options(const lv_obj_t *roller)
 */
 
STATIC mp_obj_t mp_lv_roller_get_options(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *roller = mp_to_lv(args[0]);
    const char * res = lv_roller_get_options(roller);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_get_options_obj, 1, 1, mp_lv_roller_get_options);

 

/*
 * lvgl extension definition for:
 * inline static uint16_t lv_roller_get_anim_time(const lv_obj_t *roller)
 */
 
STATIC mp_obj_t mp_lv_roller_get_anim_time(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *roller = mp_to_lv(args[0]);
    uint16_t res = lv_roller_get_anim_time(roller);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_get_anim_time_obj, 1, 1, mp_lv_roller_get_anim_time);

 

/*
 * lvgl extension definition for:
 * void lv_roller_set_options(lv_obj_t *roller, const char *options, bool inf)
 */
 
STATIC mp_obj_t mp_lv_roller_set_options(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *roller = mp_to_lv(args[0]);
    const char *options = (char*)mp_obj_str_get_str(args[1]);
    bool inf = mp_obj_is_true(args[2]);
    lv_roller_set_options(roller, options, inf);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_set_options_obj, 3, 3, mp_lv_roller_set_options);

 

/*
 * lvgl extension definition for:
 * void lv_roller_set_align(lv_obj_t *roller, lv_label_align_t align)
 */
 
STATIC mp_obj_t mp_lv_roller_set_align(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *roller = mp_to_lv(args[0]);
    lv_label_align_t align = (uint8_t)mp_obj_get_int(args[1]);
    lv_roller_set_align(roller, align);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_set_align_obj, 2, 2, mp_lv_roller_set_align);

 

/*
 * lvgl extension definition for:
 * void lv_roller_set_selected(lv_obj_t *roller, uint16_t sel_opt, bool anim_en)
 */
 
STATIC mp_obj_t mp_lv_roller_set_selected(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *roller = mp_to_lv(args[0]);
    uint16_t sel_opt = (uint16_t)mp_obj_get_int(args[1]);
    bool anim_en = mp_obj_is_true(args[2]);
    lv_roller_set_selected(roller, sel_opt, anim_en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_set_selected_obj, 3, 3, mp_lv_roller_set_selected);

 

/*
 * lvgl extension definition for:
 * void lv_roller_set_visible_row_count(lv_obj_t *roller, uint8_t row_cnt)
 */
 
STATIC mp_obj_t mp_lv_roller_set_visible_row_count(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *roller = mp_to_lv(args[0]);
    uint8_t row_cnt = (uint8_t)mp_obj_get_int(args[1]);
    lv_roller_set_visible_row_count(roller, row_cnt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_set_visible_row_count_obj, 2, 2, mp_lv_roller_set_visible_row_count);

 

/*
 * lvgl extension definition for:
 * void lv_roller_set_style(lv_obj_t *roller, lv_roller_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_roller_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *roller = mp_to_lv(args[0]);
    lv_roller_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_roller_set_style(roller, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_set_style_obj, 3, 3, mp_lv_roller_set_style);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_roller_get_selected(const lv_obj_t *roller)
 */
 
STATIC mp_obj_t mp_lv_roller_get_selected(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *roller = mp_to_lv(args[0]);
    uint16_t res = lv_roller_get_selected(roller);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_get_selected_obj, 1, 1, mp_lv_roller_get_selected);

 

/*
 * lvgl extension definition for:
 * lv_label_align_t lv_roller_get_align(const lv_obj_t *roller)
 */
 
STATIC mp_obj_t mp_lv_roller_get_align(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *roller = mp_to_lv(args[0]);
    lv_label_align_t res = lv_roller_get_align(roller);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_get_align_obj, 1, 1, mp_lv_roller_get_align);

 

/*
 * lvgl extension definition for:
 * bool lv_roller_get_hor_fit(const lv_obj_t *roller)
 */
 
STATIC mp_obj_t mp_lv_roller_get_hor_fit(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *roller = mp_to_lv(args[0]);
    bool res = lv_roller_get_hor_fit(roller);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_roller_get_hor_fit_obj, 1, 1, mp_lv_roller_get_hor_fit);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_roller_get_style(const lv_obj_t *roller, lv_roller_style_t type)
 */
    

/*
 * lvgl roller object definitions
 */
    

STATIC const mp_rom_map_elem_t roller_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_hor_fit), MP_ROM_PTR(&mp_lv_roller_set_hor_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_anim_time), MP_ROM_PTR(&mp_lv_roller_set_anim_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_selected_str), MP_ROM_PTR(&mp_lv_roller_get_selected_str_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_options), MP_ROM_PTR(&mp_lv_roller_get_options_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_anim_time), MP_ROM_PTR(&mp_lv_roller_get_anim_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_options), MP_ROM_PTR(&mp_lv_roller_set_options_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_align), MP_ROM_PTR(&mp_lv_roller_set_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_selected), MP_ROM_PTR(&mp_lv_roller_set_selected_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_visible_row_count), MP_ROM_PTR(&mp_lv_roller_set_visible_row_count_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_roller_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_selected), MP_ROM_PTR(&mp_lv_roller_get_selected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_align), MP_ROM_PTR(&mp_lv_roller_get_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hor_fit), MP_ROM_PTR(&mp_lv_roller_get_hor_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_ROLLER_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(roller_locals_dict, roller_locals_dict_table);

STATIC void roller_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl roller");
}


STATIC mp_obj_t roller_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_roller_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_roller_type = {
    { &mp_type_type },
    .name = MP_QSTR_roller,
    .print = roller_print,
    .make_new = roller_make_new,
    .locals_dict = (mp_obj_dict_t*)&roller_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_ta_set_sb_mode(lv_obj_t *ta, lv_sb_mode_t mode)
 */
 
STATIC mp_obj_t mp_lv_ta_set_sb_mode(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    lv_sb_mode_t mode = (uint8_t)mp_obj_get_int(args[1]);
    lv_ta_set_sb_mode(ta, mode);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_sb_mode_obj, 2, 2, mp_lv_ta_set_sb_mode);

 

/*
 * lvgl extension definition for:
 * inline static void lv_ta_set_scroll_propagation(lv_obj_t *ta, bool en)
 */
 
STATIC mp_obj_t mp_lv_ta_set_scroll_propagation(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_ta_set_scroll_propagation(ta, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_scroll_propagation_obj, 2, 2, mp_lv_ta_set_scroll_propagation);

 

/*
 * lvgl extension definition for:
 * inline static void lv_ta_set_edge_flash(lv_obj_t *ta, bool en)
 */
 
STATIC mp_obj_t mp_lv_ta_set_edge_flash(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_ta_set_edge_flash(ta, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_edge_flash_obj, 2, 2, mp_lv_ta_set_edge_flash);

 

/*
 * lvgl extension definition for:
 * inline static lv_sb_mode_t lv_ta_get_sb_mode(const lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_sb_mode(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ta = mp_to_lv(args[0]);
    lv_sb_mode_t res = lv_ta_get_sb_mode(ta);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_sb_mode_obj, 1, 1, mp_lv_ta_get_sb_mode);

 

/*
 * lvgl extension definition for:
 * inline static bool lv_ta_get_scroll_propagation(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_scroll_propagation(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    bool res = lv_ta_get_scroll_propagation(ta);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_scroll_propagation_obj, 1, 1, mp_lv_ta_get_scroll_propagation);

 

/*
 * lvgl extension definition for:
 * inline static bool lv_ta_get_edge_flash(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_edge_flash(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    bool res = lv_ta_get_edge_flash(ta);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_edge_flash_obj, 1, 1, mp_lv_ta_get_edge_flash);

 

/*
 * lvgl extension definition for:
 * void lv_ta_add_char(lv_obj_t *ta, uint32_t c)
 */
 
STATIC mp_obj_t mp_lv_ta_add_char(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    uint32_t c = (uint32_t)mp_obj_get_int(args[1]);
    lv_ta_add_char(ta, c);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_add_char_obj, 2, 2, mp_lv_ta_add_char);

 

/*
 * lvgl extension definition for:
 * void lv_ta_add_text(lv_obj_t *ta, const char *txt)
 */
 
STATIC mp_obj_t mp_lv_ta_add_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    const char *txt = (char*)mp_obj_str_get_str(args[1]);
    lv_ta_add_text(ta, txt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_add_text_obj, 2, 2, mp_lv_ta_add_text);

 

/*
 * lvgl extension definition for:
 * void lv_ta_del_char(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_del_char(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    lv_ta_del_char(ta);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_del_char_obj, 1, 1, mp_lv_ta_del_char);

 

/*
 * lvgl extension definition for:
 * void lv_ta_del_char_forward(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_del_char_forward(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    lv_ta_del_char_forward(ta);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_del_char_forward_obj, 1, 1, mp_lv_ta_del_char_forward);

 

/*
 * lvgl extension definition for:
 * void lv_ta_set_text(lv_obj_t *ta, const char *txt)
 */
 
STATIC mp_obj_t mp_lv_ta_set_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    const char *txt = (char*)mp_obj_str_get_str(args[1]);
    lv_ta_set_text(ta, txt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_text_obj, 2, 2, mp_lv_ta_set_text);

 

/*
 * lvgl extension definition for:
 * void lv_ta_set_placeholder_text(lv_obj_t *ta, const char *txt)
 */
 
STATIC mp_obj_t mp_lv_ta_set_placeholder_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    const char *txt = (char*)mp_obj_str_get_str(args[1]);
    lv_ta_set_placeholder_text(ta, txt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_placeholder_text_obj, 2, 2, mp_lv_ta_set_placeholder_text);

 

/*
 * lvgl extension definition for:
 * void lv_ta_set_cursor_pos(lv_obj_t *ta, int16_t pos)
 */
 
STATIC mp_obj_t mp_lv_ta_set_cursor_pos(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    int16_t pos = (int16_t)mp_obj_get_int(args[1]);
    lv_ta_set_cursor_pos(ta, pos);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_cursor_pos_obj, 2, 2, mp_lv_ta_set_cursor_pos);

 

/*
 * lvgl extension definition for:
 * void lv_ta_set_cursor_type(lv_obj_t *ta, lv_cursor_type_t cur_type)
 */
 
STATIC mp_obj_t mp_lv_ta_set_cursor_type(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    lv_cursor_type_t cur_type = (uint8_t)mp_obj_get_int(args[1]);
    lv_ta_set_cursor_type(ta, cur_type);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_cursor_type_obj, 2, 2, mp_lv_ta_set_cursor_type);

 

/*
 * lvgl extension definition for:
 * void lv_ta_set_pwd_mode(lv_obj_t *ta, bool en)
 */
 
STATIC mp_obj_t mp_lv_ta_set_pwd_mode(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_ta_set_pwd_mode(ta, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_pwd_mode_obj, 2, 2, mp_lv_ta_set_pwd_mode);

 

/*
 * lvgl extension definition for:
 * void lv_ta_set_one_line(lv_obj_t *ta, bool en)
 */
 
STATIC mp_obj_t mp_lv_ta_set_one_line(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_ta_set_one_line(ta, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_one_line_obj, 2, 2, mp_lv_ta_set_one_line);

 

/*
 * lvgl extension definition for:
 * void lv_ta_set_text_align(lv_obj_t *ta, lv_label_align_t align)
 */
 
STATIC mp_obj_t mp_lv_ta_set_text_align(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    lv_label_align_t align = (uint8_t)mp_obj_get_int(args[1]);
    lv_ta_set_text_align(ta, align);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_text_align_obj, 2, 2, mp_lv_ta_set_text_align);

 

/*
 * lvgl extension definition for:
 * void lv_ta_set_accepted_chars(lv_obj_t *ta, const char *list)
 */
 
STATIC mp_obj_t mp_lv_ta_set_accepted_chars(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    const char *list = (char*)mp_obj_str_get_str(args[1]);
    lv_ta_set_accepted_chars(ta, list);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_accepted_chars_obj, 2, 2, mp_lv_ta_set_accepted_chars);

 

/*
 * lvgl extension definition for:
 * void lv_ta_set_max_length(lv_obj_t *ta, uint16_t num)
 */
 
STATIC mp_obj_t mp_lv_ta_set_max_length(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    uint16_t num = (uint16_t)mp_obj_get_int(args[1]);
    lv_ta_set_max_length(ta, num);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_max_length_obj, 2, 2, mp_lv_ta_set_max_length);

 

/*
 * lvgl extension definition for:
 * void lv_ta_set_insert_replace(lv_obj_t *ta, const char *txt)
 */
 
STATIC mp_obj_t mp_lv_ta_set_insert_replace(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    const char *txt = (char*)mp_obj_str_get_str(args[1]);
    lv_ta_set_insert_replace(ta, txt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_insert_replace_obj, 2, 2, mp_lv_ta_set_insert_replace);

 

/*
 * lvgl extension definition for:
 * void lv_ta_set_style(lv_obj_t *ta, lv_ta_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_ta_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    lv_ta_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_ta_set_style(ta, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_style_obj, 3, 3, mp_lv_ta_set_style);

 

/*
 * lvgl extension definition for:
 * void lv_ta_set_text_sel(lv_obj_t *ta, bool en)
 */
 
STATIC mp_obj_t mp_lv_ta_set_text_sel(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_ta_set_text_sel(ta, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_set_text_sel_obj, 2, 2, mp_lv_ta_set_text_sel);

 

/*
 * lvgl extension definition for:
 * const char *lv_ta_get_text(const lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_text(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ta = mp_to_lv(args[0]);
    const char * res = lv_ta_get_text(ta);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_text_obj, 1, 1, mp_lv_ta_get_text);

 

/*
 * lvgl extension definition for:
 * const char *lv_ta_get_placeholder_text(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_placeholder_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    const char * res = lv_ta_get_placeholder_text(ta);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_placeholder_text_obj, 1, 1, mp_lv_ta_get_placeholder_text);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_ta_get_label(const lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_label(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ta = mp_to_lv(args[0]);
    lv_obj_t * res = lv_ta_get_label(ta);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_label_obj, 1, 1, mp_lv_ta_get_label);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_ta_get_cursor_pos(const lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_cursor_pos(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ta = mp_to_lv(args[0]);
    uint16_t res = lv_ta_get_cursor_pos(ta);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_cursor_pos_obj, 1, 1, mp_lv_ta_get_cursor_pos);

 

/*
 * lvgl extension definition for:
 * lv_cursor_type_t lv_ta_get_cursor_type(const lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_cursor_type(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ta = mp_to_lv(args[0]);
    lv_cursor_type_t res = lv_ta_get_cursor_type(ta);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_cursor_type_obj, 1, 1, mp_lv_ta_get_cursor_type);

 

/*
 * lvgl extension definition for:
 * bool lv_ta_get_pwd_mode(const lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_pwd_mode(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ta = mp_to_lv(args[0]);
    bool res = lv_ta_get_pwd_mode(ta);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_pwd_mode_obj, 1, 1, mp_lv_ta_get_pwd_mode);

 

/*
 * lvgl extension definition for:
 * bool lv_ta_get_one_line(const lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_one_line(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ta = mp_to_lv(args[0]);
    bool res = lv_ta_get_one_line(ta);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_one_line_obj, 1, 1, mp_lv_ta_get_one_line);

 

/*
 * lvgl extension definition for:
 * const char *lv_ta_get_accepted_chars(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_accepted_chars(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    const char * res = lv_ta_get_accepted_chars(ta);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_accepted_chars_obj, 1, 1, mp_lv_ta_get_accepted_chars);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_ta_get_max_length(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_max_length(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    uint16_t res = lv_ta_get_max_length(ta);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_max_length_obj, 1, 1, mp_lv_ta_get_max_length);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_ta_get_style(const lv_obj_t *ta, lv_ta_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * bool lv_ta_text_is_selected(const lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_text_is_selected(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ta = mp_to_lv(args[0]);
    bool res = lv_ta_text_is_selected(ta);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_text_is_selected_obj, 1, 1, mp_lv_ta_text_is_selected);

 

/*
 * lvgl extension definition for:
 * bool lv_ta_get_text_sel_en(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_get_text_sel_en(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    bool res = lv_ta_get_text_sel_en(ta);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_get_text_sel_en_obj, 1, 1, mp_lv_ta_get_text_sel_en);

 

/*
 * lvgl extension definition for:
 * void lv_ta_clear_selection(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_clear_selection(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    lv_ta_clear_selection(ta);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_clear_selection_obj, 1, 1, mp_lv_ta_clear_selection);

 

/*
 * lvgl extension definition for:
 * void lv_ta_cursor_right(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_cursor_right(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    lv_ta_cursor_right(ta);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_cursor_right_obj, 1, 1, mp_lv_ta_cursor_right);

 

/*
 * lvgl extension definition for:
 * void lv_ta_cursor_left(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_cursor_left(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    lv_ta_cursor_left(ta);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_cursor_left_obj, 1, 1, mp_lv_ta_cursor_left);

 

/*
 * lvgl extension definition for:
 * void lv_ta_cursor_down(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_cursor_down(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    lv_ta_cursor_down(ta);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_cursor_down_obj, 1, 1, mp_lv_ta_cursor_down);

 

/*
 * lvgl extension definition for:
 * void lv_ta_cursor_up(lv_obj_t *ta)
 */
 
STATIC mp_obj_t mp_lv_ta_cursor_up(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *ta = mp_to_lv(args[0]);
    lv_ta_cursor_up(ta);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ta_cursor_up_obj, 1, 1, mp_lv_ta_cursor_up);

 

/*
 * lvgl ta object definitions
 */
    

STATIC const mp_rom_map_elem_t ta_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_sb_mode), MP_ROM_PTR(&mp_lv_ta_set_sb_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_scroll_propagation), MP_ROM_PTR(&mp_lv_ta_set_scroll_propagation_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_edge_flash), MP_ROM_PTR(&mp_lv_ta_set_edge_flash_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_sb_mode), MP_ROM_PTR(&mp_lv_ta_get_sb_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scroll_propagation), MP_ROM_PTR(&mp_lv_ta_get_scroll_propagation_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_edge_flash), MP_ROM_PTR(&mp_lv_ta_get_edge_flash_obj) },
    { MP_ROM_QSTR(MP_QSTR_add_char), MP_ROM_PTR(&mp_lv_ta_add_char_obj) },
    { MP_ROM_QSTR(MP_QSTR_add_text), MP_ROM_PTR(&mp_lv_ta_add_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_del_char), MP_ROM_PTR(&mp_lv_ta_del_char_obj) },
    { MP_ROM_QSTR(MP_QSTR_del_char_forward), MP_ROM_PTR(&mp_lv_ta_del_char_forward_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_text), MP_ROM_PTR(&mp_lv_ta_set_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_placeholder_text), MP_ROM_PTR(&mp_lv_ta_set_placeholder_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_cursor_pos), MP_ROM_PTR(&mp_lv_ta_set_cursor_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_cursor_type), MP_ROM_PTR(&mp_lv_ta_set_cursor_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pwd_mode), MP_ROM_PTR(&mp_lv_ta_set_pwd_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_one_line), MP_ROM_PTR(&mp_lv_ta_set_one_line_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_text_align), MP_ROM_PTR(&mp_lv_ta_set_text_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_accepted_chars), MP_ROM_PTR(&mp_lv_ta_set_accepted_chars_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_max_length), MP_ROM_PTR(&mp_lv_ta_set_max_length_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_insert_replace), MP_ROM_PTR(&mp_lv_ta_set_insert_replace_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_ta_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_text_sel), MP_ROM_PTR(&mp_lv_ta_set_text_sel_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_text), MP_ROM_PTR(&mp_lv_ta_get_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_placeholder_text), MP_ROM_PTR(&mp_lv_ta_get_placeholder_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_label), MP_ROM_PTR(&mp_lv_ta_get_label_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_cursor_pos), MP_ROM_PTR(&mp_lv_ta_get_cursor_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_cursor_type), MP_ROM_PTR(&mp_lv_ta_get_cursor_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_pwd_mode), MP_ROM_PTR(&mp_lv_ta_get_pwd_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_one_line), MP_ROM_PTR(&mp_lv_ta_get_one_line_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_accepted_chars), MP_ROM_PTR(&mp_lv_ta_get_accepted_chars_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_max_length), MP_ROM_PTR(&mp_lv_ta_get_max_length_obj) },
    { MP_ROM_QSTR(MP_QSTR_text_is_selected), MP_ROM_PTR(&mp_lv_ta_text_is_selected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_text_sel_en), MP_ROM_PTR(&mp_lv_ta_get_text_sel_en_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_selection), MP_ROM_PTR(&mp_lv_ta_clear_selection_obj) },
    { MP_ROM_QSTR(MP_QSTR_cursor_right), MP_ROM_PTR(&mp_lv_ta_cursor_right_obj) },
    { MP_ROM_QSTR(MP_QSTR_cursor_left), MP_ROM_PTR(&mp_lv_ta_cursor_left_obj) },
    { MP_ROM_QSTR(MP_QSTR_cursor_down), MP_ROM_PTR(&mp_lv_ta_cursor_down_obj) },
    { MP_ROM_QSTR(MP_QSTR_cursor_up), MP_ROM_PTR(&mp_lv_ta_cursor_up_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_TA_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(ta_locals_dict, ta_locals_dict_table);

STATIC void ta_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl ta");
}


STATIC mp_obj_t ta_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_ta_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_ta_type = {
    { &mp_type_type },
    .name = MP_QSTR_ta,
    .print = ta_print,
    .make_new = ta_make_new,
    .locals_dict = (mp_obj_dict_t*)&ta_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * void lv_canvas_set_buffer(lv_obj_t *canvas, void *buf, lv_coord_t w, lv_coord_t h, lv_img_cf_t cf)
 */
 
STATIC mp_obj_t mp_lv_canvas_set_buffer(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    void *buf = mp_to_ptr(args[1]);
    lv_coord_t w = (int16_t)mp_obj_get_int(args[2]);
    lv_coord_t h = (int16_t)mp_obj_get_int(args[3]);
    lv_img_cf_t cf = (uint8_t)mp_obj_get_int(args[4]);
    lv_canvas_set_buffer(canvas, buf, w, h, cf);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_set_buffer_obj, 5, 5, mp_lv_canvas_set_buffer);

 

/*
 * lvgl extension definition for:
 * void lv_canvas_set_px(lv_obj_t *canvas, lv_coord_t x, lv_coord_t y, lv_color_t c)
 */
 
STATIC mp_obj_t mp_lv_canvas_set_px(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    lv_color_t c = mp_write_lv_color32_t(args[3]);
    lv_canvas_set_px(canvas, x, y, c);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_set_px_obj, 4, 4, mp_lv_canvas_set_px);

 

/*
 * lvgl extension definition for:
 * void lv_canvas_set_style(lv_obj_t *canvas, lv_canvas_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_canvas_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_canvas_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_canvas_set_style(canvas, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_set_style_obj, 3, 3, mp_lv_canvas_set_style);

 

/*
 * lvgl extension definition for:
 * lv_color_t lv_canvas_get_px(lv_obj_t *canvas, lv_coord_t x, lv_coord_t y)
 */
 
STATIC mp_obj_t mp_lv_canvas_get_px(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    lv_color_t res = lv_canvas_get_px(canvas, x, y);
    return mp_read_lv_color32_t(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_get_px_obj, 3, 3, mp_lv_canvas_get_px);

 

/*
 * lvgl extension definition for:
 * lv_img_dsc_t *lv_canvas_get_img(lv_obj_t *canvas)
 */
 
STATIC mp_obj_t mp_lv_canvas_get_img(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_img_dsc_t * res = lv_canvas_get_img(canvas);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_get_img_obj, 1, 1, mp_lv_canvas_get_img);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_canvas_get_style(const lv_obj_t *canvas, lv_canvas_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * void lv_canvas_copy_buf(lv_obj_t *canvas, const void *to_copy, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y)
 */
 
STATIC mp_obj_t mp_lv_canvas_copy_buf(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    const void *to_copy = mp_to_ptr(args[1]);
    lv_coord_t w = (int16_t)mp_obj_get_int(args[2]);
    lv_coord_t h = (int16_t)mp_obj_get_int(args[3]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[4]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[5]);
    lv_canvas_copy_buf(canvas, to_copy, w, h, x, y);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_copy_buf_obj, 6, 6, mp_lv_canvas_copy_buf);

 

/*
 * lvgl extension definition for:
 * void lv_canvas_mult_buf(lv_obj_t *canvas, void *to_copy, lv_coord_t w, lv_coord_t h, lv_coord_t x, lv_coord_t y)
 */
 
STATIC mp_obj_t mp_lv_canvas_mult_buf(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    void *to_copy = mp_to_ptr(args[1]);
    lv_coord_t w = (int16_t)mp_obj_get_int(args[2]);
    lv_coord_t h = (int16_t)mp_obj_get_int(args[3]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[4]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[5]);
    lv_canvas_mult_buf(canvas, to_copy, w, h, x, y);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_mult_buf_obj, 6, 6, mp_lv_canvas_mult_buf);

 

/*
 * lvgl extension definition for:
 * void lv_canvas_rotate(lv_obj_t *canvas, lv_img_dsc_t *img, int16_t angle, lv_coord_t offset_x, lv_coord_t offset_y, int32_t pivot_x, int32_t pivot_y)
 */
 
STATIC mp_obj_t mp_lv_canvas_rotate(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_img_dsc_t *img = mp_to_ptr(args[1]);
    int16_t angle = (int16_t)mp_obj_get_int(args[2]);
    lv_coord_t offset_x = (int16_t)mp_obj_get_int(args[3]);
    lv_coord_t offset_y = (int16_t)mp_obj_get_int(args[4]);
    int32_t pivot_x = (int32_t)mp_obj_get_int(args[5]);
    int32_t pivot_y = (int32_t)mp_obj_get_int(args[6]);
    lv_canvas_rotate(canvas, img, angle, offset_x, offset_y, pivot_x, pivot_y);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_rotate_obj, 7, 7, mp_lv_canvas_rotate);

 

/*
 * lvgl extension definition for:
 * void lv_canvas_draw_circle(lv_obj_t *canvas, lv_coord_t x0, lv_coord_t y0, lv_coord_t radius, lv_color_t color)
 */
 
STATIC mp_obj_t mp_lv_canvas_draw_circle(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_coord_t x0 = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y0 = (int16_t)mp_obj_get_int(args[2]);
    lv_coord_t radius = (int16_t)mp_obj_get_int(args[3]);
    lv_color_t color = mp_write_lv_color32_t(args[4]);
    lv_canvas_draw_circle(canvas, x0, y0, radius, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_draw_circle_obj, 5, 5, mp_lv_canvas_draw_circle);

 

/*
 * lvgl extension definition for:
 * void lv_canvas_draw_line(lv_obj_t *canvas, lv_point_t point1, lv_point_t point2, lv_color_t color)
 */
 
STATIC mp_obj_t mp_lv_canvas_draw_line(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_point_t point1 = mp_write_lv_point_t(args[1]);
    lv_point_t point2 = mp_write_lv_point_t(args[2]);
    lv_color_t color = mp_write_lv_color32_t(args[3]);
    lv_canvas_draw_line(canvas, point1, point2, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_draw_line_obj, 4, 4, mp_lv_canvas_draw_line);

 

/*
 * lvgl extension definition for:
 * void lv_canvas_draw_triangle(lv_obj_t *canvas, lv_point_t *points, lv_color_t color)
 */
 
STATIC mp_obj_t mp_lv_canvas_draw_triangle(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_point_t *points = mp_to_ptr(args[1]);
    lv_color_t color = mp_write_lv_color32_t(args[2]);
    lv_canvas_draw_triangle(canvas, points, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_draw_triangle_obj, 3, 3, mp_lv_canvas_draw_triangle);

 

/*
 * lvgl extension definition for:
 * void lv_canvas_draw_rect(lv_obj_t *canvas, lv_point_t *points, lv_color_t color)
 */
 
STATIC mp_obj_t mp_lv_canvas_draw_rect(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_point_t *points = mp_to_ptr(args[1]);
    lv_color_t color = mp_write_lv_color32_t(args[2]);
    lv_canvas_draw_rect(canvas, points, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_draw_rect_obj, 3, 3, mp_lv_canvas_draw_rect);

 

/*
 * lvgl extension definition for:
 * void lv_canvas_draw_polygon(lv_obj_t *canvas, lv_point_t *points, size_t size, lv_color_t color)
 */
 
STATIC mp_obj_t mp_lv_canvas_draw_polygon(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_point_t *points = mp_to_ptr(args[1]);
    size_t size = (size_t)mp_obj_get_int(args[2]);
    lv_color_t color = mp_write_lv_color32_t(args[3]);
    lv_canvas_draw_polygon(canvas, points, size, color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_draw_polygon_obj, 4, 4, mp_lv_canvas_draw_polygon);

 

/*
 * lvgl extension definition for:
 * void lv_canvas_fill_polygon(lv_obj_t *canvas, lv_point_t *points, size_t size, lv_color_t boundary_color, lv_color_t fill_color)
 */
 
STATIC mp_obj_t mp_lv_canvas_fill_polygon(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_point_t *points = mp_to_ptr(args[1]);
    size_t size = (size_t)mp_obj_get_int(args[2]);
    lv_color_t boundary_color = mp_write_lv_color32_t(args[3]);
    lv_color_t fill_color = mp_write_lv_color32_t(args[4]);
    lv_canvas_fill_polygon(canvas, points, size, boundary_color, fill_color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_fill_polygon_obj, 5, 5, mp_lv_canvas_fill_polygon);

 

/*
 * lvgl extension definition for:
 * void lv_canvas_boundary_fill4(lv_obj_t *canvas, lv_coord_t x, lv_coord_t y, lv_color_t boundary_color, lv_color_t fill_color)
 */
 
STATIC mp_obj_t mp_lv_canvas_boundary_fill4(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    lv_color_t boundary_color = mp_write_lv_color32_t(args[3]);
    lv_color_t fill_color = mp_write_lv_color32_t(args[4]);
    lv_canvas_boundary_fill4(canvas, x, y, boundary_color, fill_color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_boundary_fill4_obj, 5, 5, mp_lv_canvas_boundary_fill4);

 

/*
 * lvgl extension definition for:
 * void lv_canvas_flood_fill(lv_obj_t *canvas, lv_coord_t x, lv_coord_t y, lv_color_t fill_color, lv_color_t bg_color)
 */
 
STATIC mp_obj_t mp_lv_canvas_flood_fill(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *canvas = mp_to_lv(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    lv_color_t fill_color = mp_write_lv_color32_t(args[3]);
    lv_color_t bg_color = mp_write_lv_color32_t(args[4]);
    lv_canvas_flood_fill(canvas, x, y, fill_color, bg_color);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_canvas_flood_fill_obj, 5, 5, mp_lv_canvas_flood_fill);

 

/*
 * lvgl canvas object definitions
 */
    

STATIC const mp_rom_map_elem_t canvas_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_buffer), MP_ROM_PTR(&mp_lv_canvas_set_buffer_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_px), MP_ROM_PTR(&mp_lv_canvas_set_px_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_canvas_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_px), MP_ROM_PTR(&mp_lv_canvas_get_px_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_img), MP_ROM_PTR(&mp_lv_canvas_get_img_obj) },
    { MP_ROM_QSTR(MP_QSTR_copy_buf), MP_ROM_PTR(&mp_lv_canvas_copy_buf_obj) },
    { MP_ROM_QSTR(MP_QSTR_mult_buf), MP_ROM_PTR(&mp_lv_canvas_mult_buf_obj) },
    { MP_ROM_QSTR(MP_QSTR_rotate), MP_ROM_PTR(&mp_lv_canvas_rotate_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_circle), MP_ROM_PTR(&mp_lv_canvas_draw_circle_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_line), MP_ROM_PTR(&mp_lv_canvas_draw_line_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_triangle), MP_ROM_PTR(&mp_lv_canvas_draw_triangle_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_rect), MP_ROM_PTR(&mp_lv_canvas_draw_rect_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_polygon), MP_ROM_PTR(&mp_lv_canvas_draw_polygon_obj) },
    { MP_ROM_QSTR(MP_QSTR_fill_polygon), MP_ROM_PTR(&mp_lv_canvas_fill_polygon_obj) },
    { MP_ROM_QSTR(MP_QSTR_boundary_fill4), MP_ROM_PTR(&mp_lv_canvas_boundary_fill4_obj) },
    { MP_ROM_QSTR(MP_QSTR_flood_fill), MP_ROM_PTR(&mp_lv_canvas_flood_fill_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_CANVAS_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(canvas_locals_dict, canvas_locals_dict_table);

STATIC void canvas_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl canvas");
}


STATIC mp_obj_t canvas_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_canvas_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_canvas_type = {
    { &mp_type_type },
    .name = MP_QSTR_canvas,
    .print = canvas_print,
    .make_new = canvas_make_new,
    .locals_dict = (mp_obj_dict_t*)&canvas_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static bool lv_win_get_drag(const lv_obj_t *win)
 */
 
STATIC mp_obj_t mp_lv_win_get_drag(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *win = mp_to_lv(args[0]);
    bool res = lv_win_get_drag(win);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_get_drag_obj, 1, 1, mp_lv_win_get_drag);

 

/*
 * lvgl extension definition for:
 * inline static void lv_win_scroll_hor(lv_obj_t *win, lv_coord_t dist)
 */
 
STATIC mp_obj_t mp_lv_win_scroll_hor(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    lv_coord_t dist = (int16_t)mp_obj_get_int(args[1]);
    lv_win_scroll_hor(win, dist);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_scroll_hor_obj, 2, 2, mp_lv_win_scroll_hor);

 

/*
 * lvgl extension definition for:
 * inline static void lv_win_scroll_ver(lv_obj_t *win, lv_coord_t dist)
 */
 
STATIC mp_obj_t mp_lv_win_scroll_ver(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    lv_coord_t dist = (int16_t)mp_obj_get_int(args[1]);
    lv_win_scroll_ver(win, dist);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_scroll_ver_obj, 2, 2, mp_lv_win_scroll_ver);

 

/*
 * lvgl extension definition for:
 * void lv_win_clean(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_win_clean(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_win_clean(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_clean_obj, 1, 1, mp_lv_win_clean);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_win_add_btn(lv_obj_t *win, const void *img_src, lv_event_cb_t event_cb)
 */
 
STATIC mp_obj_t mp_lv_win_add_btn(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    const void *img_src = mp_to_ptr(args[1]);
    lv_event_cb_t event_cb = mp_lv_callback(args[2], &event_cb_callback, MP_QSTR_event_cb, &win->user_data);
    lv_obj_t * res = lv_win_add_btn(win, img_src, event_cb);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_add_btn_obj, 3, 3, mp_lv_win_add_btn);

 

/*
 * lvgl extension definition for:
 * void lv_win_close_event(lv_obj_t *btn, lv_event_t event)
 */
 
STATIC mp_obj_t mp_lv_win_close_event(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *btn = mp_to_lv(args[0]);
    lv_event_t event = (uint8_t)mp_obj_get_int(args[1]);
    lv_win_close_event(btn, event);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_close_event_obj, 2, 2, mp_lv_win_close_event);

 

/*
 * lvgl extension definition for:
 * void lv_win_set_title(lv_obj_t *win, const char *title)
 */
 
STATIC mp_obj_t mp_lv_win_set_title(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    const char *title = (char*)mp_obj_str_get_str(args[1]);
    lv_win_set_title(win, title);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_set_title_obj, 2, 2, mp_lv_win_set_title);

 

/*
 * lvgl extension definition for:
 * void lv_win_set_btn_size(lv_obj_t *win, lv_coord_t size)
 */
 
STATIC mp_obj_t mp_lv_win_set_btn_size(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    lv_coord_t size = (int16_t)mp_obj_get_int(args[1]);
    lv_win_set_btn_size(win, size);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_set_btn_size_obj, 2, 2, mp_lv_win_set_btn_size);

 

/*
 * lvgl extension definition for:
 * void lv_win_set_layout(lv_obj_t *win, lv_layout_t layout)
 */
 
STATIC mp_obj_t mp_lv_win_set_layout(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    lv_layout_t layout = (uint8_t)mp_obj_get_int(args[1]);
    lv_win_set_layout(win, layout);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_set_layout_obj, 2, 2, mp_lv_win_set_layout);

 

/*
 * lvgl extension definition for:
 * void lv_win_set_sb_mode(lv_obj_t *win, lv_sb_mode_t sb_mode)
 */
 
STATIC mp_obj_t mp_lv_win_set_sb_mode(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    lv_sb_mode_t sb_mode = (uint8_t)mp_obj_get_int(args[1]);
    lv_win_set_sb_mode(win, sb_mode);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_set_sb_mode_obj, 2, 2, mp_lv_win_set_sb_mode);

 

/*
 * lvgl extension definition for:
 * void lv_win_set_style(lv_obj_t *win, lv_win_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_win_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    lv_win_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_win_set_style(win, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_set_style_obj, 3, 3, mp_lv_win_set_style);

 

/*
 * lvgl extension definition for:
 * void lv_win_set_drag(lv_obj_t *win, bool en)
 */
 
STATIC mp_obj_t mp_lv_win_set_drag(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_win_set_drag(win, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_set_drag_obj, 2, 2, mp_lv_win_set_drag);

 

/*
 * lvgl extension definition for:
 * const char *lv_win_get_title(const lv_obj_t *win)
 */
 
STATIC mp_obj_t mp_lv_win_get_title(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *win = mp_to_lv(args[0]);
    const char * res = lv_win_get_title(win);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_get_title_obj, 1, 1, mp_lv_win_get_title);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_win_get_content(const lv_obj_t *win)
 */
 
STATIC mp_obj_t mp_lv_win_get_content(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *win = mp_to_lv(args[0]);
    lv_obj_t * res = lv_win_get_content(win);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_get_content_obj, 1, 1, mp_lv_win_get_content);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_win_get_btn_size(const lv_obj_t *win)
 */
 
STATIC mp_obj_t mp_lv_win_get_btn_size(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *win = mp_to_lv(args[0]);
    lv_coord_t res = lv_win_get_btn_size(win);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_get_btn_size_obj, 1, 1, mp_lv_win_get_btn_size);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_win_get_from_btn(const lv_obj_t *ctrl_btn)
 */
 
STATIC mp_obj_t mp_lv_win_get_from_btn(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *ctrl_btn = mp_to_lv(args[0]);
    lv_obj_t * res = lv_win_get_from_btn(ctrl_btn);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_get_from_btn_obj, 1, 1, mp_lv_win_get_from_btn);

 

/*
 * lvgl extension definition for:
 * lv_layout_t lv_win_get_layout(lv_obj_t *win)
 */
 
STATIC mp_obj_t mp_lv_win_get_layout(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    lv_layout_t res = lv_win_get_layout(win);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_get_layout_obj, 1, 1, mp_lv_win_get_layout);

 

/*
 * lvgl extension definition for:
 * lv_sb_mode_t lv_win_get_sb_mode(lv_obj_t *win)
 */
 
STATIC mp_obj_t mp_lv_win_get_sb_mode(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    lv_sb_mode_t res = lv_win_get_sb_mode(win);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_get_sb_mode_obj, 1, 1, mp_lv_win_get_sb_mode);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_win_get_width(lv_obj_t *win)
 */
 
STATIC mp_obj_t mp_lv_win_get_width(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    lv_coord_t res = lv_win_get_width(win);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_get_width_obj, 1, 1, mp_lv_win_get_width);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_win_get_style(const lv_obj_t *win, lv_win_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * void lv_win_focus(lv_obj_t *win, lv_obj_t *obj, uint16_t anim_time)
 */
 
STATIC mp_obj_t mp_lv_win_focus(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *win = mp_to_lv(args[0]);
    lv_obj_t *obj = mp_to_lv(args[1]);
    uint16_t anim_time = (uint16_t)mp_obj_get_int(args[2]);
    lv_win_focus(win, obj, anim_time);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_win_focus_obj, 3, 3, mp_lv_win_focus);

 

/*
 * lvgl win object definitions
 */
    

STATIC const mp_rom_map_elem_t win_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_win_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_scroll_hor), MP_ROM_PTR(&mp_lv_win_scroll_hor_obj) },
    { MP_ROM_QSTR(MP_QSTR_scroll_ver), MP_ROM_PTR(&mp_lv_win_scroll_ver_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_win_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_add_btn), MP_ROM_PTR(&mp_lv_win_add_btn_obj) },
    { MP_ROM_QSTR(MP_QSTR_close_event), MP_ROM_PTR(&mp_lv_win_close_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_title), MP_ROM_PTR(&mp_lv_win_set_title_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_btn_size), MP_ROM_PTR(&mp_lv_win_set_btn_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_layout), MP_ROM_PTR(&mp_lv_win_set_layout_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_sb_mode), MP_ROM_PTR(&mp_lv_win_set_sb_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_win_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_win_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_title), MP_ROM_PTR(&mp_lv_win_get_title_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_content), MP_ROM_PTR(&mp_lv_win_get_content_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_btn_size), MP_ROM_PTR(&mp_lv_win_get_btn_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_from_btn), MP_ROM_PTR(&mp_lv_win_get_from_btn_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_layout), MP_ROM_PTR(&mp_lv_win_get_layout_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_sb_mode), MP_ROM_PTR(&mp_lv_win_get_sb_mode_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_win_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_focus), MP_ROM_PTR(&mp_lv_win_focus_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_WIN_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(win_locals_dict, win_locals_dict_table);

STATIC void win_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl win");
}


STATIC mp_obj_t win_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_win_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_win_type = {
    { &mp_type_type },
    .name = MP_QSTR_win,
    .print = win_print,
    .make_new = win_make_new,
    .locals_dict = (mp_obj_dict_t*)&win_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * void lv_tabview_clean(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_tabview_clean(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_tabview_clean(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_clean_obj, 1, 1, mp_lv_tabview_clean);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_tabview_add_tab(lv_obj_t *tabview, const char *name)
 */
 
STATIC mp_obj_t mp_lv_tabview_add_tab(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tabview = mp_to_lv(args[0]);
    const char *name = (char*)mp_obj_str_get_str(args[1]);
    lv_obj_t * res = lv_tabview_add_tab(tabview, name);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_add_tab_obj, 2, 2, mp_lv_tabview_add_tab);

 

/*
 * lvgl extension definition for:
 * void lv_tabview_set_tab_act(lv_obj_t *tabview, uint16_t id, bool anim_en)
 */
 
STATIC mp_obj_t mp_lv_tabview_set_tab_act(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tabview = mp_to_lv(args[0]);
    uint16_t id = (uint16_t)mp_obj_get_int(args[1]);
    bool anim_en = mp_obj_is_true(args[2]);
    lv_tabview_set_tab_act(tabview, id, anim_en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_set_tab_act_obj, 3, 3, mp_lv_tabview_set_tab_act);

 

/*
 * lvgl extension definition for:
 * void lv_tabview_set_sliding(lv_obj_t *tabview, bool en)
 */
 
STATIC mp_obj_t mp_lv_tabview_set_sliding(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tabview = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_tabview_set_sliding(tabview, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_set_sliding_obj, 2, 2, mp_lv_tabview_set_sliding);

 

/*
 * lvgl extension definition for:
 * void lv_tabview_set_anim_time(lv_obj_t *tabview, uint16_t anim_time)
 */
 
STATIC mp_obj_t mp_lv_tabview_set_anim_time(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tabview = mp_to_lv(args[0]);
    uint16_t anim_time = (uint16_t)mp_obj_get_int(args[1]);
    lv_tabview_set_anim_time(tabview, anim_time);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_set_anim_time_obj, 2, 2, mp_lv_tabview_set_anim_time);

 

/*
 * lvgl extension definition for:
 * void lv_tabview_set_style(lv_obj_t *tabview, lv_tabview_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_tabview_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tabview = mp_to_lv(args[0]);
    lv_tabview_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_tabview_set_style(tabview, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_set_style_obj, 3, 3, mp_lv_tabview_set_style);

 

/*
 * lvgl extension definition for:
 * void lv_tabview_set_btns_pos(lv_obj_t *tabview, lv_tabview_btns_pos_t btns_pos)
 */
 
STATIC mp_obj_t mp_lv_tabview_set_btns_pos(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tabview = mp_to_lv(args[0]);
    lv_tabview_btns_pos_t btns_pos = (uint8_t)mp_obj_get_int(args[1]);
    lv_tabview_set_btns_pos(tabview, btns_pos);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_set_btns_pos_obj, 2, 2, mp_lv_tabview_set_btns_pos);

 

/*
 * lvgl extension definition for:
 * void lv_tabview_set_btns_hidden(lv_obj_t *tabview, bool en)
 */
 
STATIC mp_obj_t mp_lv_tabview_set_btns_hidden(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tabview = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_tabview_set_btns_hidden(tabview, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_set_btns_hidden_obj, 2, 2, mp_lv_tabview_set_btns_hidden);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_tabview_get_tab_act(const lv_obj_t *tabview)
 */
 
STATIC mp_obj_t mp_lv_tabview_get_tab_act(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *tabview = mp_to_lv(args[0]);
    uint16_t res = lv_tabview_get_tab_act(tabview);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_get_tab_act_obj, 1, 1, mp_lv_tabview_get_tab_act);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_tabview_get_tab_count(const lv_obj_t *tabview)
 */
 
STATIC mp_obj_t mp_lv_tabview_get_tab_count(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *tabview = mp_to_lv(args[0]);
    uint16_t res = lv_tabview_get_tab_count(tabview);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_get_tab_count_obj, 1, 1, mp_lv_tabview_get_tab_count);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_tabview_get_tab(const lv_obj_t *tabview, uint16_t id)
 */
 
STATIC mp_obj_t mp_lv_tabview_get_tab(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *tabview = mp_to_lv(args[0]);
    uint16_t id = (uint16_t)mp_obj_get_int(args[1]);
    lv_obj_t * res = lv_tabview_get_tab(tabview, id);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_get_tab_obj, 2, 2, mp_lv_tabview_get_tab);

 

/*
 * lvgl extension definition for:
 * bool lv_tabview_get_sliding(const lv_obj_t *tabview)
 */
 
STATIC mp_obj_t mp_lv_tabview_get_sliding(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *tabview = mp_to_lv(args[0]);
    bool res = lv_tabview_get_sliding(tabview);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_get_sliding_obj, 1, 1, mp_lv_tabview_get_sliding);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_tabview_get_anim_time(const lv_obj_t *tabview)
 */
 
STATIC mp_obj_t mp_lv_tabview_get_anim_time(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *tabview = mp_to_lv(args[0]);
    uint16_t res = lv_tabview_get_anim_time(tabview);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_get_anim_time_obj, 1, 1, mp_lv_tabview_get_anim_time);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_tabview_get_style(const lv_obj_t *tabview, lv_tabview_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * lv_tabview_btns_pos_t lv_tabview_get_btns_pos(const lv_obj_t *tabview)
 */
 
STATIC mp_obj_t mp_lv_tabview_get_btns_pos(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *tabview = mp_to_lv(args[0]);
    lv_tabview_btns_pos_t res = lv_tabview_get_btns_pos(tabview);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_get_btns_pos_obj, 1, 1, mp_lv_tabview_get_btns_pos);

 

/*
 * lvgl extension definition for:
 * bool lv_tabview_get_btns_hidden(const lv_obj_t *tabview)
 */
 
STATIC mp_obj_t mp_lv_tabview_get_btns_hidden(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *tabview = mp_to_lv(args[0]);
    bool res = lv_tabview_get_btns_hidden(tabview);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tabview_get_btns_hidden_obj, 1, 1, mp_lv_tabview_get_btns_hidden);

 

/*
 * lvgl tabview object definitions
 */
    

STATIC const mp_rom_map_elem_t tabview_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_tabview_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_add_tab), MP_ROM_PTR(&mp_lv_tabview_add_tab_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_tab_act), MP_ROM_PTR(&mp_lv_tabview_set_tab_act_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_sliding), MP_ROM_PTR(&mp_lv_tabview_set_sliding_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_anim_time), MP_ROM_PTR(&mp_lv_tabview_set_anim_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_tabview_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_btns_pos), MP_ROM_PTR(&mp_lv_tabview_set_btns_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_btns_hidden), MP_ROM_PTR(&mp_lv_tabview_set_btns_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_tab_act), MP_ROM_PTR(&mp_lv_tabview_get_tab_act_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_tab_count), MP_ROM_PTR(&mp_lv_tabview_get_tab_count_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_tab), MP_ROM_PTR(&mp_lv_tabview_get_tab_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_sliding), MP_ROM_PTR(&mp_lv_tabview_get_sliding_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_anim_time), MP_ROM_PTR(&mp_lv_tabview_get_anim_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_btns_pos), MP_ROM_PTR(&mp_lv_tabview_get_btns_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_btns_hidden), MP_ROM_PTR(&mp_lv_tabview_get_btns_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_BTNS_POS), MP_ROM_PTR(&mp_LV_TABVIEW_BTNS_POS_type) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_TABVIEW_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(tabview_locals_dict, tabview_locals_dict_table);

STATIC void tabview_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl tabview");
}


STATIC mp_obj_t tabview_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_tabview_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_tabview_type = {
    { &mp_type_type },
    .name = MP_QSTR_tabview,
    .print = tabview_print,
    .make_new = tabview_make_new,
    .locals_dict = (mp_obj_dict_t*)&tabview_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_tileview_set_edge_flash(lv_obj_t *tileview, bool en)
 */
 
STATIC mp_obj_t mp_lv_tileview_set_edge_flash(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tileview = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_tileview_set_edge_flash(tileview, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tileview_set_edge_flash_obj, 2, 2, mp_lv_tileview_set_edge_flash);

 

/*
 * lvgl extension definition for:
 * inline static bool lv_tileview_get_edge_flash(lv_obj_t *tileview)
 */
 
STATIC mp_obj_t mp_lv_tileview_get_edge_flash(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tileview = mp_to_lv(args[0]);
    bool res = lv_tileview_get_edge_flash(tileview);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tileview_get_edge_flash_obj, 1, 1, mp_lv_tileview_get_edge_flash);

 

/*
 * lvgl extension definition for:
 * void lv_tileview_add_element(lv_obj_t *tileview, lv_obj_t *element)
 */
 
STATIC mp_obj_t mp_lv_tileview_add_element(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tileview = mp_to_lv(args[0]);
    lv_obj_t *element = mp_to_lv(args[1]);
    lv_tileview_add_element(tileview, element);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tileview_add_element_obj, 2, 2, mp_lv_tileview_add_element);

 

/*
 * lvgl extension definition for:
 * void lv_tileview_set_valid_positions(lv_obj_t *tileview, const lv_point_t *valid_pos)
 */
 
STATIC mp_obj_t mp_lv_tileview_set_valid_positions(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tileview = mp_to_lv(args[0]);
    const lv_point_t *valid_pos = mp_to_ptr(args[1]);
    lv_tileview_set_valid_positions(tileview, valid_pos);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tileview_set_valid_positions_obj, 2, 2, mp_lv_tileview_set_valid_positions);

 

/*
 * lvgl extension definition for:
 * void lv_tileview_set_tile_act(lv_obj_t *tileview, lv_coord_t x, lv_coord_t y, bool anim_en)
 */
 
STATIC mp_obj_t mp_lv_tileview_set_tile_act(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tileview = mp_to_lv(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    bool anim_en = mp_obj_is_true(args[3]);
    lv_tileview_set_tile_act(tileview, x, y, anim_en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tileview_set_tile_act_obj, 4, 4, mp_lv_tileview_set_tile_act);

 

/*
 * lvgl extension definition for:
 * void lv_tileview_set_style(lv_obj_t *tileview, lv_tileview_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_tileview_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *tileview = mp_to_lv(args[0]);
    lv_tileview_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_tileview_set_style(tileview, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tileview_set_style_obj, 3, 3, mp_lv_tileview_set_style);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_tileview_get_style(const lv_obj_t *tileview, lv_tileview_style_t type)
 */
    

/*
 * lvgl tileview object definitions
 */
    

STATIC const mp_rom_map_elem_t tileview_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_edge_flash), MP_ROM_PTR(&mp_lv_tileview_set_edge_flash_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_edge_flash), MP_ROM_PTR(&mp_lv_tileview_get_edge_flash_obj) },
    { MP_ROM_QSTR(MP_QSTR_add_element), MP_ROM_PTR(&mp_lv_tileview_add_element_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_valid_positions), MP_ROM_PTR(&mp_lv_tileview_set_valid_positions_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_tile_act), MP_ROM_PTR(&mp_lv_tileview_set_tile_act_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_tileview_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_TILEVIEW_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(tileview_locals_dict, tileview_locals_dict_table);

STATIC void tileview_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl tileview");
}


STATIC mp_obj_t tileview_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_tileview_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_tileview_type = {
    { &mp_type_type },
    .name = MP_QSTR_tileview,
    .print = tileview_print,
    .make_new = tileview_make_new,
    .locals_dict = (mp_obj_dict_t*)&tileview_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * void lv_mbox_add_btns(lv_obj_t *mbox, const char **btn_mapaction)
 */
 
STATIC mp_obj_t mp_lv_mbox_add_btns(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *mbox = mp_to_lv(args[0]);
    const char **btn_mapaction = mp_to_ptr(args[1]);
    lv_mbox_add_btns(mbox, btn_mapaction);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_add_btns_obj, 2, 2, mp_lv_mbox_add_btns);

 

/*
 * lvgl extension definition for:
 * void lv_mbox_set_text(lv_obj_t *mbox, const char *txt)
 */
 
STATIC mp_obj_t mp_lv_mbox_set_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *mbox = mp_to_lv(args[0]);
    const char *txt = (char*)mp_obj_str_get_str(args[1]);
    lv_mbox_set_text(mbox, txt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_set_text_obj, 2, 2, mp_lv_mbox_set_text);

 

/*
 * lvgl extension definition for:
 * void lv_mbox_set_anim_time(lv_obj_t *mbox, uint16_t anim_time)
 */
 
STATIC mp_obj_t mp_lv_mbox_set_anim_time(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *mbox = mp_to_lv(args[0]);
    uint16_t anim_time = (uint16_t)mp_obj_get_int(args[1]);
    lv_mbox_set_anim_time(mbox, anim_time);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_set_anim_time_obj, 2, 2, mp_lv_mbox_set_anim_time);

 

/*
 * lvgl extension definition for:
 * void lv_mbox_start_auto_close(lv_obj_t *mbox, uint16_t delay)
 */
 
STATIC mp_obj_t mp_lv_mbox_start_auto_close(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *mbox = mp_to_lv(args[0]);
    uint16_t delay = (uint16_t)mp_obj_get_int(args[1]);
    lv_mbox_start_auto_close(mbox, delay);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_start_auto_close_obj, 2, 2, mp_lv_mbox_start_auto_close);

 

/*
 * lvgl extension definition for:
 * void lv_mbox_stop_auto_close(lv_obj_t *mbox)
 */
 
STATIC mp_obj_t mp_lv_mbox_stop_auto_close(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *mbox = mp_to_lv(args[0]);
    lv_mbox_stop_auto_close(mbox);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_stop_auto_close_obj, 1, 1, mp_lv_mbox_stop_auto_close);

 

/*
 * lvgl extension definition for:
 * void lv_mbox_set_style(lv_obj_t *mbox, lv_mbox_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_mbox_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *mbox = mp_to_lv(args[0]);
    lv_mbox_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_mbox_set_style(mbox, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_set_style_obj, 3, 3, mp_lv_mbox_set_style);

 

/*
 * lvgl extension definition for:
 * void lv_mbox_set_recolor(lv_obj_t *mbox, bool en)
 */
 
STATIC mp_obj_t mp_lv_mbox_set_recolor(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *mbox = mp_to_lv(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_mbox_set_recolor(mbox, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_set_recolor_obj, 2, 2, mp_lv_mbox_set_recolor);

 

/*
 * lvgl extension definition for:
 * const char *lv_mbox_get_text(const lv_obj_t *mbox)
 */
 
STATIC mp_obj_t mp_lv_mbox_get_text(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *mbox = mp_to_lv(args[0]);
    const char * res = lv_mbox_get_text(mbox);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_get_text_obj, 1, 1, mp_lv_mbox_get_text);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_mbox_get_active_btn(lv_obj_t *mbox)
 */
 
STATIC mp_obj_t mp_lv_mbox_get_active_btn(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *mbox = mp_to_lv(args[0]);
    uint16_t res = lv_mbox_get_active_btn(mbox);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_get_active_btn_obj, 1, 1, mp_lv_mbox_get_active_btn);

 

/*
 * lvgl extension definition for:
 * const char *lv_mbox_get_active_btn_text(lv_obj_t *mbox)
 */
 
STATIC mp_obj_t mp_lv_mbox_get_active_btn_text(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *mbox = mp_to_lv(args[0]);
    const char * res = lv_mbox_get_active_btn_text(mbox);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_get_active_btn_text_obj, 1, 1, mp_lv_mbox_get_active_btn_text);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_mbox_get_anim_time(const lv_obj_t *mbox)
 */
 
STATIC mp_obj_t mp_lv_mbox_get_anim_time(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *mbox = mp_to_lv(args[0]);
    uint16_t res = lv_mbox_get_anim_time(mbox);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_get_anim_time_obj, 1, 1, mp_lv_mbox_get_anim_time);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_mbox_get_style(const lv_obj_t *mbox, lv_mbox_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * bool lv_mbox_get_recolor(const lv_obj_t *mbox)
 */
 
STATIC mp_obj_t mp_lv_mbox_get_recolor(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *mbox = mp_to_lv(args[0]);
    bool res = lv_mbox_get_recolor(mbox);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_get_recolor_obj, 1, 1, mp_lv_mbox_get_recolor);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_mbox_get_btnm(lv_obj_t *mbox)
 */
 
STATIC mp_obj_t mp_lv_mbox_get_btnm(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *mbox = mp_to_lv(args[0]);
    lv_obj_t * res = lv_mbox_get_btnm(mbox);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mbox_get_btnm_obj, 1, 1, mp_lv_mbox_get_btnm);

 

/*
 * lvgl mbox object definitions
 */
    

STATIC const mp_rom_map_elem_t mbox_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_add_btns), MP_ROM_PTR(&mp_lv_mbox_add_btns_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_text), MP_ROM_PTR(&mp_lv_mbox_set_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_anim_time), MP_ROM_PTR(&mp_lv_mbox_set_anim_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_start_auto_close), MP_ROM_PTR(&mp_lv_mbox_start_auto_close_obj) },
    { MP_ROM_QSTR(MP_QSTR_stop_auto_close), MP_ROM_PTR(&mp_lv_mbox_stop_auto_close_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_mbox_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_recolor), MP_ROM_PTR(&mp_lv_mbox_set_recolor_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_text), MP_ROM_PTR(&mp_lv_mbox_get_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_active_btn), MP_ROM_PTR(&mp_lv_mbox_get_active_btn_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_active_btn_text), MP_ROM_PTR(&mp_lv_mbox_get_active_btn_text_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_anim_time), MP_ROM_PTR(&mp_lv_mbox_get_anim_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_recolor), MP_ROM_PTR(&mp_lv_mbox_get_recolor_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_btnm), MP_ROM_PTR(&mp_lv_mbox_get_btnm_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_MBOX_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(mbox_locals_dict, mbox_locals_dict_table);

STATIC void mbox_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl mbox");
}


STATIC mp_obj_t mbox_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_mbox_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_mbox_type = {
    { &mp_type_type },
    .name = MP_QSTR_mbox,
    .print = mbox_print,
    .make_new = mbox_make_new,
    .locals_dict = (mp_obj_dict_t*)&mbox_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_lmeter_set_style(lv_obj_t *lmeter, lv_style_t *bg)
 */
 
STATIC mp_obj_t mp_lv_lmeter_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *lmeter = mp_to_lv(args[0]);
    lv_style_t *bg = mp_to_ptr(args[1]);
    lv_lmeter_set_style(lmeter, bg);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_lmeter_set_style_obj, 2, 2, mp_lv_lmeter_set_style);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * inline static const lv_style_t *lv_lmeter_get_style(const lv_obj_t *lmeter)
 */
    

/*
 * lvgl extension definition for:
 * void lv_lmeter_set_value(lv_obj_t *lmeter, int16_t value)
 */
 
STATIC mp_obj_t mp_lv_lmeter_set_value(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *lmeter = mp_to_lv(args[0]);
    int16_t value = (int16_t)mp_obj_get_int(args[1]);
    lv_lmeter_set_value(lmeter, value);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_lmeter_set_value_obj, 2, 2, mp_lv_lmeter_set_value);

 

/*
 * lvgl extension definition for:
 * void lv_lmeter_set_range(lv_obj_t *lmeter, int16_t min, int16_t max)
 */
 
STATIC mp_obj_t mp_lv_lmeter_set_range(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *lmeter = mp_to_lv(args[0]);
    int16_t min = (int16_t)mp_obj_get_int(args[1]);
    int16_t max = (int16_t)mp_obj_get_int(args[2]);
    lv_lmeter_set_range(lmeter, min, max);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_lmeter_set_range_obj, 3, 3, mp_lv_lmeter_set_range);

 

/*
 * lvgl extension definition for:
 * void lv_lmeter_set_scale(lv_obj_t *lmeter, uint16_t angle, uint8_t line_cnt)
 */
 
STATIC mp_obj_t mp_lv_lmeter_set_scale(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *lmeter = mp_to_lv(args[0]);
    uint16_t angle = (uint16_t)mp_obj_get_int(args[1]);
    uint8_t line_cnt = (uint8_t)mp_obj_get_int(args[2]);
    lv_lmeter_set_scale(lmeter, angle, line_cnt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_lmeter_set_scale_obj, 3, 3, mp_lv_lmeter_set_scale);

 

/*
 * lvgl extension definition for:
 * int16_t lv_lmeter_get_value(const lv_obj_t *lmeter)
 */
 
STATIC mp_obj_t mp_lv_lmeter_get_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *lmeter = mp_to_lv(args[0]);
    int16_t res = lv_lmeter_get_value(lmeter);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_lmeter_get_value_obj, 1, 1, mp_lv_lmeter_get_value);

 

/*
 * lvgl extension definition for:
 * int16_t lv_lmeter_get_min_value(const lv_obj_t *lmeter)
 */
 
STATIC mp_obj_t mp_lv_lmeter_get_min_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *lmeter = mp_to_lv(args[0]);
    int16_t res = lv_lmeter_get_min_value(lmeter);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_lmeter_get_min_value_obj, 1, 1, mp_lv_lmeter_get_min_value);

 

/*
 * lvgl extension definition for:
 * int16_t lv_lmeter_get_max_value(const lv_obj_t *lmeter)
 */
 
STATIC mp_obj_t mp_lv_lmeter_get_max_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *lmeter = mp_to_lv(args[0]);
    int16_t res = lv_lmeter_get_max_value(lmeter);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_lmeter_get_max_value_obj, 1, 1, mp_lv_lmeter_get_max_value);

 

/*
 * lvgl extension definition for:
 * uint8_t lv_lmeter_get_line_count(const lv_obj_t *lmeter)
 */
 
STATIC mp_obj_t mp_lv_lmeter_get_line_count(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *lmeter = mp_to_lv(args[0]);
    uint8_t res = lv_lmeter_get_line_count(lmeter);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_lmeter_get_line_count_obj, 1, 1, mp_lv_lmeter_get_line_count);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_lmeter_get_scale_angle(const lv_obj_t *lmeter)
 */
 
STATIC mp_obj_t mp_lv_lmeter_get_scale_angle(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *lmeter = mp_to_lv(args[0]);
    uint16_t res = lv_lmeter_get_scale_angle(lmeter);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_lmeter_get_scale_angle_obj, 1, 1, mp_lv_lmeter_get_scale_angle);

 

/*
 * lvgl lmeter object definitions
 */
    

STATIC const mp_rom_map_elem_t lmeter_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_lmeter_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_value), MP_ROM_PTR(&mp_lv_lmeter_set_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_range), MP_ROM_PTR(&mp_lv_lmeter_set_range_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_scale), MP_ROM_PTR(&mp_lv_lmeter_set_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_value), MP_ROM_PTR(&mp_lv_lmeter_get_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_min_value), MP_ROM_PTR(&mp_lv_lmeter_get_min_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_max_value), MP_ROM_PTR(&mp_lv_lmeter_get_max_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_line_count), MP_ROM_PTR(&mp_lv_lmeter_get_line_count_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scale_angle), MP_ROM_PTR(&mp_lv_lmeter_get_scale_angle_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) }
};

STATIC MP_DEFINE_CONST_DICT(lmeter_locals_dict, lmeter_locals_dict_table);

STATIC void lmeter_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl lmeter");
}


STATIC mp_obj_t lmeter_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_lmeter_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_lmeter_type = {
    { &mp_type_type },
    .name = MP_QSTR_lmeter,
    .print = lmeter_print,
    .make_new = lmeter_make_new,
    .locals_dict = (mp_obj_dict_t*)&lmeter_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_gauge_set_range(lv_obj_t *gauge, int16_t min, int16_t max)
 */
 
STATIC mp_obj_t mp_lv_gauge_set_range(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *gauge = mp_to_lv(args[0]);
    int16_t min = (int16_t)mp_obj_get_int(args[1]);
    int16_t max = (int16_t)mp_obj_get_int(args[2]);
    lv_gauge_set_range(gauge, min, max);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_set_range_obj, 3, 3, mp_lv_gauge_set_range);

 

/*
 * lvgl extension definition for:
 * inline static void lv_gauge_set_critical_value(lv_obj_t *gauge, int16_t value)
 */
 
STATIC mp_obj_t mp_lv_gauge_set_critical_value(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *gauge = mp_to_lv(args[0]);
    int16_t value = (int16_t)mp_obj_get_int(args[1]);
    lv_gauge_set_critical_value(gauge, value);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_set_critical_value_obj, 2, 2, mp_lv_gauge_set_critical_value);

 

/*
 * lvgl extension definition for:
 * inline static void lv_gauge_set_style(lv_obj_t *gauge, lv_style_t *bg)
 */
 
STATIC mp_obj_t mp_lv_gauge_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *gauge = mp_to_lv(args[0]);
    lv_style_t *bg = mp_to_ptr(args[1]);
    lv_gauge_set_style(gauge, bg);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_set_style_obj, 2, 2, mp_lv_gauge_set_style);

 

/*
 * lvgl extension definition for:
 * inline static int16_t lv_gauge_get_min_value(const lv_obj_t *lmeter)
 */
 
STATIC mp_obj_t mp_lv_gauge_get_min_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *lmeter = mp_to_lv(args[0]);
    int16_t res = lv_gauge_get_min_value(lmeter);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_get_min_value_obj, 1, 1, mp_lv_gauge_get_min_value);

 

/*
 * lvgl extension definition for:
 * inline static int16_t lv_gauge_get_max_value(const lv_obj_t *lmeter)
 */
 
STATIC mp_obj_t mp_lv_gauge_get_max_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *lmeter = mp_to_lv(args[0]);
    int16_t res = lv_gauge_get_max_value(lmeter);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_get_max_value_obj, 1, 1, mp_lv_gauge_get_max_value);

 

/*
 * lvgl extension definition for:
 * inline static int16_t lv_gauge_get_critical_value(const lv_obj_t *gauge)
 */
 
STATIC mp_obj_t mp_lv_gauge_get_critical_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *gauge = mp_to_lv(args[0]);
    int16_t res = lv_gauge_get_critical_value(gauge);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_get_critical_value_obj, 1, 1, mp_lv_gauge_get_critical_value);

 

/*
 * lvgl extension definition for:
 * inline static uint8_t lv_gauge_get_line_count(const lv_obj_t *gauge)
 */
 
STATIC mp_obj_t mp_lv_gauge_get_line_count(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *gauge = mp_to_lv(args[0]);
    uint8_t res = lv_gauge_get_line_count(gauge);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_get_line_count_obj, 1, 1, mp_lv_gauge_get_line_count);

 

/*
 * lvgl extension definition for:
 * inline static uint16_t lv_gauge_get_scale_angle(const lv_obj_t *gauge)
 */
 
STATIC mp_obj_t mp_lv_gauge_get_scale_angle(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *gauge = mp_to_lv(args[0]);
    uint16_t res = lv_gauge_get_scale_angle(gauge);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_get_scale_angle_obj, 1, 1, mp_lv_gauge_get_scale_angle);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * inline static const lv_style_t *lv_gauge_get_style(const lv_obj_t *gauge)
 */
    

/*
 * lvgl extension definition for:
 * void lv_gauge_set_needle_count(lv_obj_t *gauge, uint8_t needle_cnt, const lv_color_t colors[])
 */
 
STATIC mp_obj_t mp_lv_gauge_set_needle_count(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *gauge = mp_to_lv(args[0]);
    uint8_t needle_cnt = (uint8_t)mp_obj_get_int(args[1]);
    const lv_color_t *colors = mp_to_ptr(args[2]);
    lv_gauge_set_needle_count(gauge, needle_cnt, colors);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_set_needle_count_obj, 3, 3, mp_lv_gauge_set_needle_count);

 

/*
 * lvgl extension definition for:
 * void lv_gauge_set_value(lv_obj_t *gauge, uint8_t needle_id, int16_t value)
 */
 
STATIC mp_obj_t mp_lv_gauge_set_value(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *gauge = mp_to_lv(args[0]);
    uint8_t needle_id = (uint8_t)mp_obj_get_int(args[1]);
    int16_t value = (int16_t)mp_obj_get_int(args[2]);
    lv_gauge_set_value(gauge, needle_id, value);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_set_value_obj, 3, 3, mp_lv_gauge_set_value);

 

/*
 * lvgl extension definition for:
 * void lv_gauge_set_scale(lv_obj_t *gauge, uint16_t angle, uint8_t line_cnt, uint8_t label_cnt)
 */
 
STATIC mp_obj_t mp_lv_gauge_set_scale(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *gauge = mp_to_lv(args[0]);
    uint16_t angle = (uint16_t)mp_obj_get_int(args[1]);
    uint8_t line_cnt = (uint8_t)mp_obj_get_int(args[2]);
    uint8_t label_cnt = (uint8_t)mp_obj_get_int(args[3]);
    lv_gauge_set_scale(gauge, angle, line_cnt, label_cnt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_set_scale_obj, 4, 4, mp_lv_gauge_set_scale);

 

/*
 * lvgl extension definition for:
 * int16_t lv_gauge_get_value(const lv_obj_t *gauge, uint8_t needle)
 */
 
STATIC mp_obj_t mp_lv_gauge_get_value(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *gauge = mp_to_lv(args[0]);
    uint8_t needle = (uint8_t)mp_obj_get_int(args[1]);
    int16_t res = lv_gauge_get_value(gauge, needle);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_get_value_obj, 2, 2, mp_lv_gauge_get_value);

 

/*
 * lvgl extension definition for:
 * uint8_t lv_gauge_get_needle_count(const lv_obj_t *gauge)
 */
 
STATIC mp_obj_t mp_lv_gauge_get_needle_count(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *gauge = mp_to_lv(args[0]);
    uint8_t res = lv_gauge_get_needle_count(gauge);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_get_needle_count_obj, 1, 1, mp_lv_gauge_get_needle_count);

 

/*
 * lvgl extension definition for:
 * uint8_t lv_gauge_get_label_count(const lv_obj_t *gauge)
 */
 
STATIC mp_obj_t mp_lv_gauge_get_label_count(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *gauge = mp_to_lv(args[0]);
    uint8_t res = lv_gauge_get_label_count(gauge);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_gauge_get_label_count_obj, 1, 1, mp_lv_gauge_get_label_count);

 

/*
 * lvgl gauge object definitions
 */
    

STATIC const mp_rom_map_elem_t gauge_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_range), MP_ROM_PTR(&mp_lv_gauge_set_range_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_critical_value), MP_ROM_PTR(&mp_lv_gauge_set_critical_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_gauge_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_min_value), MP_ROM_PTR(&mp_lv_gauge_get_min_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_max_value), MP_ROM_PTR(&mp_lv_gauge_get_max_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_critical_value), MP_ROM_PTR(&mp_lv_gauge_get_critical_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_line_count), MP_ROM_PTR(&mp_lv_gauge_get_line_count_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_scale_angle), MP_ROM_PTR(&mp_lv_gauge_get_scale_angle_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_needle_count), MP_ROM_PTR(&mp_lv_gauge_set_needle_count_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_value), MP_ROM_PTR(&mp_lv_gauge_set_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_scale), MP_ROM_PTR(&mp_lv_gauge_set_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_value), MP_ROM_PTR(&mp_lv_gauge_get_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_needle_count), MP_ROM_PTR(&mp_lv_gauge_get_needle_count_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_label_count), MP_ROM_PTR(&mp_lv_gauge_get_label_count_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) }
};

STATIC MP_DEFINE_CONST_DICT(gauge_locals_dict, gauge_locals_dict_table);

STATIC void gauge_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl gauge");
}


STATIC mp_obj_t gauge_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_gauge_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_gauge_type = {
    { &mp_type_type },
    .name = MP_QSTR_gauge,
    .print = gauge_print,
    .make_new = gauge_make_new,
    .locals_dict = (mp_obj_dict_t*)&gauge_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static bool lv_sw_get_state(const lv_obj_t *sw)
 */
 
STATIC mp_obj_t mp_lv_sw_get_state(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *sw = mp_to_lv(args[0]);
    bool res = lv_sw_get_state(sw);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_sw_get_state_obj, 1, 1, mp_lv_sw_get_state);

 

/*
 * lvgl extension definition for:
 * void lv_sw_on(lv_obj_t *sw, bool anim)
 */
 
STATIC mp_obj_t mp_lv_sw_on(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *sw = mp_to_lv(args[0]);
    bool anim = mp_obj_is_true(args[1]);
    lv_sw_on(sw, anim);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_sw_on_obj, 2, 2, mp_lv_sw_on);

 

/*
 * lvgl extension definition for:
 * void lv_sw_off(lv_obj_t *sw, bool anim)
 */
 
STATIC mp_obj_t mp_lv_sw_off(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *sw = mp_to_lv(args[0]);
    bool anim = mp_obj_is_true(args[1]);
    lv_sw_off(sw, anim);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_sw_off_obj, 2, 2, mp_lv_sw_off);

 

/*
 * lvgl extension definition for:
 * bool lv_sw_toggle(lv_obj_t *sw, bool anim)
 */
 
STATIC mp_obj_t mp_lv_sw_toggle(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *sw = mp_to_lv(args[0]);
    bool anim = mp_obj_is_true(args[1]);
    bool res = lv_sw_toggle(sw, anim);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_sw_toggle_obj, 2, 2, mp_lv_sw_toggle);

 

/*
 * lvgl extension definition for:
 * void lv_sw_set_style(lv_obj_t *sw, lv_sw_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_sw_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *sw = mp_to_lv(args[0]);
    lv_sw_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_sw_set_style(sw, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_sw_set_style_obj, 3, 3, mp_lv_sw_set_style);

 

/*
 * lvgl extension definition for:
 * void lv_sw_set_anim_time(lv_obj_t *sw, uint16_t anim_time)
 */
 
STATIC mp_obj_t mp_lv_sw_set_anim_time(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *sw = mp_to_lv(args[0]);
    uint16_t anim_time = (uint16_t)mp_obj_get_int(args[1]);
    lv_sw_set_anim_time(sw, anim_time);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_sw_set_anim_time_obj, 2, 2, mp_lv_sw_set_anim_time);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_sw_get_style(const lv_obj_t *sw, lv_sw_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * uint16_t lv_sw_get_anim_time(const lv_obj_t *sw)
 */
 
STATIC mp_obj_t mp_lv_sw_get_anim_time(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *sw = mp_to_lv(args[0]);
    uint16_t res = lv_sw_get_anim_time(sw);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_sw_get_anim_time_obj, 1, 1, mp_lv_sw_get_anim_time);

 

/*
 * lvgl sw object definitions
 */
    

STATIC const mp_rom_map_elem_t sw_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_get_state), MP_ROM_PTR(&mp_lv_sw_get_state_obj) },
    { MP_ROM_QSTR(MP_QSTR_on), MP_ROM_PTR(&mp_lv_sw_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_off), MP_ROM_PTR(&mp_lv_sw_off_obj) },
    { MP_ROM_QSTR(MP_QSTR_toggle), MP_ROM_PTR(&mp_lv_sw_toggle_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_sw_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_anim_time), MP_ROM_PTR(&mp_lv_sw_set_anim_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_anim_time), MP_ROM_PTR(&mp_lv_sw_get_anim_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_SW_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(sw_locals_dict, sw_locals_dict_table);

STATIC void sw_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl sw");
}


STATIC mp_obj_t sw_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_sw_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_sw_type = {
    { &mp_type_type },
    .name = MP_QSTR_sw,
    .print = sw_print,
    .make_new = sw_make_new,
    .locals_dict = (mp_obj_dict_t*)&sw_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * void lv_arc_set_angles(lv_obj_t *arc, uint16_t start, uint16_t end)
 */
 
STATIC mp_obj_t mp_lv_arc_set_angles(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *arc = mp_to_lv(args[0]);
    uint16_t start = (uint16_t)mp_obj_get_int(args[1]);
    uint16_t end = (uint16_t)mp_obj_get_int(args[2]);
    lv_arc_set_angles(arc, start, end);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_arc_set_angles_obj, 3, 3, mp_lv_arc_set_angles);

 

/*
 * lvgl extension definition for:
 * void lv_arc_set_style(lv_obj_t *arc, lv_arc_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_arc_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *arc = mp_to_lv(args[0]);
    lv_arc_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_arc_set_style(arc, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_arc_set_style_obj, 3, 3, mp_lv_arc_set_style);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_arc_get_angle_start(lv_obj_t *arc)
 */
 
STATIC mp_obj_t mp_lv_arc_get_angle_start(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *arc = mp_to_lv(args[0]);
    uint16_t res = lv_arc_get_angle_start(arc);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_arc_get_angle_start_obj, 1, 1, mp_lv_arc_get_angle_start);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_arc_get_angle_end(lv_obj_t *arc)
 */
 
STATIC mp_obj_t mp_lv_arc_get_angle_end(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *arc = mp_to_lv(args[0]);
    uint16_t res = lv_arc_get_angle_end(arc);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_arc_get_angle_end_obj, 1, 1, mp_lv_arc_get_angle_end);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_arc_get_style(const lv_obj_t *arc, lv_arc_style_t type)
 */
    

/*
 * lvgl arc object definitions
 */
    

STATIC const mp_rom_map_elem_t arc_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_angles), MP_ROM_PTR(&mp_lv_arc_set_angles_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_arc_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_angle_start), MP_ROM_PTR(&mp_lv_arc_get_angle_start_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_angle_end), MP_ROM_PTR(&mp_lv_arc_get_angle_end_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_ARC_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(arc_locals_dict, arc_locals_dict_table);

STATIC void arc_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl arc");
}


STATIC mp_obj_t arc_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_arc_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_arc_type = {
    { &mp_type_type },
    .name = MP_QSTR_arc,
    .print = arc_print,
    .make_new = arc_make_new,
    .locals_dict = (mp_obj_dict_t*)&arc_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * void lv_preload_set_arc_length(lv_obj_t *preload, uint16_t deg)
 */
 
STATIC mp_obj_t mp_lv_preload_set_arc_length(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *preload = mp_to_lv(args[0]);
    uint16_t deg = (uint16_t)mp_obj_get_int(args[1]);
    lv_preload_set_arc_length(preload, deg);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_preload_set_arc_length_obj, 2, 2, mp_lv_preload_set_arc_length);

 

/*
 * lvgl extension definition for:
 * void lv_preload_set_spin_time(lv_obj_t *preload, uint16_t time)
 */
 
STATIC mp_obj_t mp_lv_preload_set_spin_time(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *preload = mp_to_lv(args[0]);
    uint16_t time = (uint16_t)mp_obj_get_int(args[1]);
    lv_preload_set_spin_time(preload, time);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_preload_set_spin_time_obj, 2, 2, mp_lv_preload_set_spin_time);

 

/*
 * lvgl extension definition for:
 * void lv_preload_set_style(lv_obj_t *preload, lv_preload_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_preload_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *preload = mp_to_lv(args[0]);
    lv_preload_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_preload_set_style(preload, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_preload_set_style_obj, 3, 3, mp_lv_preload_set_style);

 

/*
 * lvgl extension definition for:
 * void lv_preload_set_anim_type(lv_obj_t *preload, lv_preload_type_t type)
 */
 
STATIC mp_obj_t mp_lv_preload_set_anim_type(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *preload = mp_to_lv(args[0]);
    lv_preload_type_t type = (uint8_t)mp_obj_get_int(args[1]);
    lv_preload_set_anim_type(preload, type);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_preload_set_anim_type_obj, 2, 2, mp_lv_preload_set_anim_type);

 

/*
 * lvgl extension definition for:
 * void lv_preload_set_anim_dir(lv_obj_t *preload, lv_preload_dir_t dir)
 */
 
STATIC mp_obj_t mp_lv_preload_set_anim_dir(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *preload = mp_to_lv(args[0]);
    lv_preload_dir_t dir = (uint8_t)mp_obj_get_int(args[1]);
    lv_preload_set_anim_dir(preload, dir);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_preload_set_anim_dir_obj, 2, 2, mp_lv_preload_set_anim_dir);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_preload_get_arc_length(const lv_obj_t *preload)
 */
 
STATIC mp_obj_t mp_lv_preload_get_arc_length(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *preload = mp_to_lv(args[0]);
    uint16_t res = lv_preload_get_arc_length(preload);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_preload_get_arc_length_obj, 1, 1, mp_lv_preload_get_arc_length);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_preload_get_spin_time(const lv_obj_t *preload)
 */
 
STATIC mp_obj_t mp_lv_preload_get_spin_time(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *preload = mp_to_lv(args[0]);
    uint16_t res = lv_preload_get_spin_time(preload);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_preload_get_spin_time_obj, 1, 1, mp_lv_preload_get_spin_time);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_preload_get_style(const lv_obj_t *preload, lv_preload_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * lv_preload_type_t lv_preload_get_anim_type(lv_obj_t *preload)
 */
 
STATIC mp_obj_t mp_lv_preload_get_anim_type(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *preload = mp_to_lv(args[0]);
    lv_preload_type_t res = lv_preload_get_anim_type(preload);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_preload_get_anim_type_obj, 1, 1, mp_lv_preload_get_anim_type);

 

/*
 * lvgl extension definition for:
 * lv_preload_dir_t lv_preload_get_anim_dir(lv_obj_t *preload)
 */
 
STATIC mp_obj_t mp_lv_preload_get_anim_dir(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *preload = mp_to_lv(args[0]);
    lv_preload_dir_t res = lv_preload_get_anim_dir(preload);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_preload_get_anim_dir_obj, 1, 1, mp_lv_preload_get_anim_dir);

 

/*
 * lvgl extension definition for:
 * void lv_preload_spinner_anim(void *ptr, int32_t val)
 */
 
STATIC mp_obj_t mp_lv_preload_spinner_anim(size_t n_args, const mp_obj_t *args)
{
    void *ptr = mp_to_ptr(args[0]);
    int32_t val = (int32_t)mp_obj_get_int(args[1]);
    lv_preload_spinner_anim(ptr, val);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_preload_spinner_anim_obj, 2, 2, mp_lv_preload_spinner_anim);

 

/*
 * lvgl preload object definitions
 */
    

STATIC const mp_rom_map_elem_t preload_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_arc_length), MP_ROM_PTR(&mp_lv_preload_set_arc_length_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_spin_time), MP_ROM_PTR(&mp_lv_preload_set_spin_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_preload_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_anim_type), MP_ROM_PTR(&mp_lv_preload_set_anim_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_anim_dir), MP_ROM_PTR(&mp_lv_preload_set_anim_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_arc_length), MP_ROM_PTR(&mp_lv_preload_get_arc_length_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_spin_time), MP_ROM_PTR(&mp_lv_preload_get_spin_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_anim_type), MP_ROM_PTR(&mp_lv_preload_get_anim_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_anim_dir), MP_ROM_PTR(&mp_lv_preload_get_anim_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_spinner_anim), MP_ROM_PTR(&mp_lv_preload_spinner_anim_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_TYPE), MP_ROM_PTR(&mp_LV_PRELOAD_TYPE_type) },
    { MP_ROM_QSTR(MP_QSTR_DIR), MP_ROM_PTR(&mp_LV_PRELOAD_DIR_type) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_PRELOAD_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(preload_locals_dict, preload_locals_dict_table);

STATIC void preload_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl preload");
}


STATIC mp_obj_t preload_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_preload_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_preload_type = {
    { &mp_type_type },
    .name = MP_QSTR_preload,
    .print = preload_print,
    .make_new = preload_make_new,
    .locals_dict = (mp_obj_dict_t*)&preload_locals_dict,
    .parent = NULL,
};
    

/*
 * Struct lv_calendar_date_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_calendar_date_t_type();

STATIC inline lv_calendar_date_t* mp_write_ptr_lv_calendar_date_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_calendar_date_t_type()));
    return (lv_calendar_date_t*)self->data;
}

#define mp_write_lv_calendar_date_t(struct_obj) *mp_write_ptr_lv_calendar_date_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_calendar_date_t(lv_calendar_date_t *field)
{
    return lv_to_mp_struct(get_mp_lv_calendar_date_t_type(), field);
}

#define mp_read_lv_calendar_date_t(field) mp_read_ptr_lv_calendar_date_t(copy_buffer(&field, sizeof(lv_calendar_date_t)))
#define mp_read_byref_lv_calendar_date_t(field) mp_read_ptr_lv_calendar_date_t(&field)

STATIC void mp_lv_calendar_date_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_calendar_date_t *data = (lv_calendar_date_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_year: dest[0] = mp_obj_new_int_from_uint(data->year); break; // converting from uint16_t;
            case MP_QSTR_month: dest[0] = mp_obj_new_int(data->month); break; // converting from int8_t;
            case MP_QSTR_day: dest[0] = mp_obj_new_int(data->day); break; // converting from int8_t;
            default: field_not_found(MP_QSTR_lv_calendar_date_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_year: data->year = (uint16_t)mp_obj_get_int(dest[1]); break; // converting to uint16_t;
                case MP_QSTR_month: data->month = (int8_t)mp_obj_get_int(dest[1]); break; // converting to int8_t;
                case MP_QSTR_day: data->day = (int8_t)mp_obj_get_int(dest[1]); break; // converting to int8_t;
                default: field_not_found(MP_QSTR_lv_calendar_date_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_calendar_date_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_calendar_date_t");
}

STATIC const mp_rom_map_elem_t mp_lv_calendar_date_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_calendar_date_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_calendar_date_t_locals_dict, mp_lv_calendar_date_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_calendar_date_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_calendar_date_t,
    .print = mp_lv_calendar_date_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_calendar_date_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_calendar_date_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_calendar_date_t_type()
{
    return &mp_lv_calendar_date_t_type;
}
    

/*
 * lvgl extension definition for:
 * void lv_calendar_set_today_date(lv_obj_t *calendar, lv_calendar_date_t *today)
 */
 
STATIC mp_obj_t mp_lv_calendar_set_today_date(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *calendar = mp_to_lv(args[0]);
    lv_calendar_date_t *today = mp_to_ptr(args[1]);
    lv_calendar_set_today_date(calendar, today);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_calendar_set_today_date_obj, 2, 2, mp_lv_calendar_set_today_date);

 

/*
 * lvgl extension definition for:
 * void lv_calendar_set_showed_date(lv_obj_t *calendar, lv_calendar_date_t *showed)
 */
 
STATIC mp_obj_t mp_lv_calendar_set_showed_date(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *calendar = mp_to_lv(args[0]);
    lv_calendar_date_t *showed = mp_to_ptr(args[1]);
    lv_calendar_set_showed_date(calendar, showed);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_calendar_set_showed_date_obj, 2, 2, mp_lv_calendar_set_showed_date);

 

/*
 * lvgl extension definition for:
 * void lv_calendar_set_highlighted_dates(lv_obj_t *calendar, lv_calendar_date_t *highlighted, uint16_t date_num)
 */
 
STATIC mp_obj_t mp_lv_calendar_set_highlighted_dates(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *calendar = mp_to_lv(args[0]);
    lv_calendar_date_t *highlighted = mp_to_ptr(args[1]);
    uint16_t date_num = (uint16_t)mp_obj_get_int(args[2]);
    lv_calendar_set_highlighted_dates(calendar, highlighted, date_num);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_calendar_set_highlighted_dates_obj, 3, 3, mp_lv_calendar_set_highlighted_dates);

 

/*
 * lvgl extension definition for:
 * void lv_calendar_set_day_names(lv_obj_t *calendar, const char **day_names)
 */
 
STATIC mp_obj_t mp_lv_calendar_set_day_names(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *calendar = mp_to_lv(args[0]);
    const char **day_names = mp_to_ptr(args[1]);
    lv_calendar_set_day_names(calendar, day_names);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_calendar_set_day_names_obj, 2, 2, mp_lv_calendar_set_day_names);

 

/*
 * lvgl extension definition for:
 * void lv_calendar_set_month_names(lv_obj_t *calendar, const char **day_names)
 */
 
STATIC mp_obj_t mp_lv_calendar_set_month_names(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *calendar = mp_to_lv(args[0]);
    const char **day_names = mp_to_ptr(args[1]);
    lv_calendar_set_month_names(calendar, day_names);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_calendar_set_month_names_obj, 2, 2, mp_lv_calendar_set_month_names);

 

/*
 * lvgl extension definition for:
 * void lv_calendar_set_style(lv_obj_t *calendar, lv_calendar_style_t type, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_calendar_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *calendar = mp_to_lv(args[0]);
    lv_calendar_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_calendar_set_style(calendar, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_calendar_set_style_obj, 3, 3, mp_lv_calendar_set_style);

 

/*
 * lvgl extension definition for:
 * lv_calendar_date_t *lv_calendar_get_today_date(const lv_obj_t *calendar)
 */
 
STATIC mp_obj_t mp_lv_calendar_get_today_date(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *calendar = mp_to_lv(args[0]);
    lv_calendar_date_t * res = lv_calendar_get_today_date(calendar);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_calendar_get_today_date_obj, 1, 1, mp_lv_calendar_get_today_date);

 

/*
 * lvgl extension definition for:
 * lv_calendar_date_t *lv_calendar_get_showed_date(const lv_obj_t *calendar)
 */
 
STATIC mp_obj_t mp_lv_calendar_get_showed_date(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *calendar = mp_to_lv(args[0]);
    lv_calendar_date_t * res = lv_calendar_get_showed_date(calendar);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_calendar_get_showed_date_obj, 1, 1, mp_lv_calendar_get_showed_date);

 

/*
 * lvgl extension definition for:
 * lv_calendar_date_t *lv_calendar_get_pressed_date(const lv_obj_t *calendar)
 */
 
STATIC mp_obj_t mp_lv_calendar_get_pressed_date(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *calendar = mp_to_lv(args[0]);
    lv_calendar_date_t * res = lv_calendar_get_pressed_date(calendar);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_calendar_get_pressed_date_obj, 1, 1, mp_lv_calendar_get_pressed_date);

 

/*
 * lvgl extension definition for:
 * lv_calendar_date_t *lv_calendar_get_highlighted_dates(const lv_obj_t *calendar)
 */
 
STATIC mp_obj_t mp_lv_calendar_get_highlighted_dates(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *calendar = mp_to_lv(args[0]);
    lv_calendar_date_t * res = lv_calendar_get_highlighted_dates(calendar);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_calendar_get_highlighted_dates_obj, 1, 1, mp_lv_calendar_get_highlighted_dates);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_calendar_get_highlighted_dates_num(const lv_obj_t *calendar)
 */
 
STATIC mp_obj_t mp_lv_calendar_get_highlighted_dates_num(size_t n_args, const mp_obj_t *args)
{
    const lv_obj_t *calendar = mp_to_lv(args[0]);
    uint16_t res = lv_calendar_get_highlighted_dates_num(calendar);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_calendar_get_highlighted_dates_num_obj, 1, 1, mp_lv_calendar_get_highlighted_dates_num);

 

/*
 * Function NOT generated:
 * Missing convertion from const char **
 * const char **lv_calendar_get_day_names(const lv_obj_t *calendar)
 */
    

/*
 * Function NOT generated:
 * Missing convertion from const char **
 * const char **lv_calendar_get_month_names(const lv_obj_t *calendar)
 */
    

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * const lv_style_t *lv_calendar_get_style(const lv_obj_t *calendar, lv_calendar_style_t type)
 */
    

/*
 * lvgl calendar object definitions
 */
    

STATIC const mp_rom_map_elem_t calendar_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_today_date), MP_ROM_PTR(&mp_lv_calendar_set_today_date_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_showed_date), MP_ROM_PTR(&mp_lv_calendar_set_showed_date_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_highlighted_dates), MP_ROM_PTR(&mp_lv_calendar_set_highlighted_dates_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_day_names), MP_ROM_PTR(&mp_lv_calendar_set_day_names_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_month_names), MP_ROM_PTR(&mp_lv_calendar_set_month_names_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_calendar_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_today_date), MP_ROM_PTR(&mp_lv_calendar_get_today_date_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_showed_date), MP_ROM_PTR(&mp_lv_calendar_get_showed_date_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_pressed_date), MP_ROM_PTR(&mp_lv_calendar_get_pressed_date_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_highlighted_dates), MP_ROM_PTR(&mp_lv_calendar_get_highlighted_dates_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_highlighted_dates_num), MP_ROM_PTR(&mp_lv_calendar_get_highlighted_dates_num_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_CALENDAR_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(calendar_locals_dict, calendar_locals_dict_table);

STATIC void calendar_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl calendar");
}


STATIC mp_obj_t calendar_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_calendar_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_calendar_type = {
    { &mp_type_type },
    .name = MP_QSTR_calendar,
    .print = calendar_print,
    .make_new = calendar_make_new,
    .locals_dict = (mp_obj_dict_t*)&calendar_locals_dict,
    .parent = NULL,
};
    

/*
 * lvgl extension definition for:
 * inline static void lv_spinbox_set_style(lv_obj_t *spinbox, lv_spinbox_style_t type, lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_spinbox_set_style(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *spinbox = mp_to_lv(args[0]);
    lv_spinbox_style_t type = (uint8_t)mp_obj_get_int(args[1]);
    lv_style_t *style = mp_to_ptr(args[2]);
    lv_spinbox_set_style(spinbox, type, style);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_spinbox_set_style_obj, 3, 3, mp_lv_spinbox_set_style);

 

/*
 * Function NOT generated:
 * Missing convertion from const lv_style_t *
 * inline static const lv_style_t *lv_spinbox_get_style(lv_obj_t *spinbox, lv_spinbox_style_t type)
 */
    

/*
 * lvgl extension definition for:
 * void lv_spinbox_set_value(lv_obj_t *spinbox, int32_t i)
 */
 
STATIC mp_obj_t mp_lv_spinbox_set_value(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *spinbox = mp_to_lv(args[0]);
    int32_t i = (int32_t)mp_obj_get_int(args[1]);
    lv_spinbox_set_value(spinbox, i);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_spinbox_set_value_obj, 2, 2, mp_lv_spinbox_set_value);

 

/*
 * lvgl extension definition for:
 * void lv_spinbox_set_digit_format(lv_obj_t *spinbox, uint8_t digit_count, uint8_t separator_position)
 */
 
STATIC mp_obj_t mp_lv_spinbox_set_digit_format(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *spinbox = mp_to_lv(args[0]);
    uint8_t digit_count = (uint8_t)mp_obj_get_int(args[1]);
    uint8_t separator_position = (uint8_t)mp_obj_get_int(args[2]);
    lv_spinbox_set_digit_format(spinbox, digit_count, separator_position);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_spinbox_set_digit_format_obj, 3, 3, mp_lv_spinbox_set_digit_format);

 

/*
 * lvgl extension definition for:
 * void lv_spinbox_set_step(lv_obj_t *spinbox, uint32_t step)
 */
 
STATIC mp_obj_t mp_lv_spinbox_set_step(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *spinbox = mp_to_lv(args[0]);
    uint32_t step = (uint32_t)mp_obj_get_int(args[1]);
    lv_spinbox_set_step(spinbox, step);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_spinbox_set_step_obj, 2, 2, mp_lv_spinbox_set_step);

 

/*
 * lvgl extension definition for:
 * void lv_spinbox_set_range(lv_obj_t *spinbox, int32_t range_min, int32_t range_max)
 */
 
STATIC mp_obj_t mp_lv_spinbox_set_range(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *spinbox = mp_to_lv(args[0]);
    int32_t range_min = (int32_t)mp_obj_get_int(args[1]);
    int32_t range_max = (int32_t)mp_obj_get_int(args[2]);
    lv_spinbox_set_range(spinbox, range_min, range_max);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_spinbox_set_range_obj, 3, 3, mp_lv_spinbox_set_range);

 

/*
 * lvgl extension definition for:
 * void lv_spinbox_set_padding_left(lv_obj_t *spinbox, uint8_t padding)
 */
 
STATIC mp_obj_t mp_lv_spinbox_set_padding_left(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *spinbox = mp_to_lv(args[0]);
    uint8_t padding = (uint8_t)mp_obj_get_int(args[1]);
    lv_spinbox_set_padding_left(spinbox, padding);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_spinbox_set_padding_left_obj, 2, 2, mp_lv_spinbox_set_padding_left);

 

/*
 * lvgl extension definition for:
 * int32_t lv_spinbox_get_value(lv_obj_t *spinbox)
 */
 
STATIC mp_obj_t mp_lv_spinbox_get_value(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *spinbox = mp_to_lv(args[0]);
    int32_t res = lv_spinbox_get_value(spinbox);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_spinbox_get_value_obj, 1, 1, mp_lv_spinbox_get_value);

 

/*
 * lvgl extension definition for:
 * void lv_spinbox_step_next(lv_obj_t *spinbox)
 */
 
STATIC mp_obj_t mp_lv_spinbox_step_next(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *spinbox = mp_to_lv(args[0]);
    lv_spinbox_step_next(spinbox);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_spinbox_step_next_obj, 1, 1, mp_lv_spinbox_step_next);

 

/*
 * lvgl extension definition for:
 * void lv_spinbox_step_previous(lv_obj_t *spinbox)
 */
 
STATIC mp_obj_t mp_lv_spinbox_step_previous(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *spinbox = mp_to_lv(args[0]);
    lv_spinbox_step_previous(spinbox);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_spinbox_step_previous_obj, 1, 1, mp_lv_spinbox_step_previous);

 

/*
 * lvgl extension definition for:
 * void lv_spinbox_increment(lv_obj_t *spinbox)
 */
 
STATIC mp_obj_t mp_lv_spinbox_increment(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *spinbox = mp_to_lv(args[0]);
    lv_spinbox_increment(spinbox);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_spinbox_increment_obj, 1, 1, mp_lv_spinbox_increment);

 

/*
 * lvgl extension definition for:
 * void lv_spinbox_decrement(lv_obj_t *spinbox)
 */
 
STATIC mp_obj_t mp_lv_spinbox_decrement(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *spinbox = mp_to_lv(args[0]);
    lv_spinbox_decrement(spinbox);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_spinbox_decrement_obj, 1, 1, mp_lv_spinbox_decrement);

 

/*
 * lvgl spinbox object definitions
 */
    

STATIC const mp_rom_map_elem_t spinbox_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_spinbox_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_value), MP_ROM_PTR(&mp_lv_spinbox_set_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_digit_format), MP_ROM_PTR(&mp_lv_spinbox_set_digit_format_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_step), MP_ROM_PTR(&mp_lv_spinbox_set_step_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_range), MP_ROM_PTR(&mp_lv_spinbox_set_range_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_padding_left), MP_ROM_PTR(&mp_lv_spinbox_set_padding_left_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_value), MP_ROM_PTR(&mp_lv_spinbox_get_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_step_next), MP_ROM_PTR(&mp_lv_spinbox_step_next_obj) },
    { MP_ROM_QSTR(MP_QSTR_step_previous), MP_ROM_PTR(&mp_lv_spinbox_step_previous_obj) },
    { MP_ROM_QSTR(MP_QSTR_increment), MP_ROM_PTR(&mp_lv_spinbox_increment_obj) },
    { MP_ROM_QSTR(MP_QSTR_decrement), MP_ROM_PTR(&mp_lv_spinbox_decrement_obj) },
    { MP_ROM_QSTR(MP_QSTR_delete), MP_ROM_PTR(&mp_lv_obj_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_clean), MP_ROM_PTR(&mp_lv_obj_clean_obj) },
    { MP_ROM_QSTR(MP_QSTR_invalidate), MP_ROM_PTR(&mp_lv_obj_invalidate_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent), MP_ROM_PTR(&mp_lv_obj_set_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_foreground), MP_ROM_PTR(&mp_lv_obj_move_foreground_obj) },
    { MP_ROM_QSTR(MP_QSTR_move_background), MP_ROM_PTR(&mp_lv_obj_move_background_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_pos), MP_ROM_PTR(&mp_lv_obj_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_x), MP_ROM_PTR(&mp_lv_obj_set_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_y), MP_ROM_PTR(&mp_lv_obj_set_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_size), MP_ROM_PTR(&mp_lv_obj_set_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_width), MP_ROM_PTR(&mp_lv_obj_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_height), MP_ROM_PTR(&mp_lv_obj_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_align), MP_ROM_PTR(&mp_lv_obj_align_obj) },
    { MP_ROM_QSTR(MP_QSTR_align_origo), MP_ROM_PTR(&mp_lv_obj_align_origo_obj) },
    { MP_ROM_QSTR(MP_QSTR_realign), MP_ROM_PTR(&mp_lv_obj_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_auto_realign), MP_ROM_PTR(&mp_lv_obj_set_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_style), MP_ROM_PTR(&mp_lv_obj_set_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_style), MP_ROM_PTR(&mp_lv_obj_refresh_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_report_style_mod), MP_ROM_PTR(&mp_lv_obj_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_hidden), MP_ROM_PTR(&mp_lv_obj_set_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_click), MP_ROM_PTR(&mp_lv_obj_set_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_top), MP_ROM_PTR(&mp_lv_obj_set_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag), MP_ROM_PTR(&mp_lv_obj_set_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_dir), MP_ROM_PTR(&mp_lv_obj_set_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_throw), MP_ROM_PTR(&mp_lv_obj_set_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_drag_parent), MP_ROM_PTR(&mp_lv_obj_set_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_parent_event), MP_ROM_PTR(&mp_lv_obj_set_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_opa_scale), MP_ROM_PTR(&mp_lv_obj_set_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_protect), MP_ROM_PTR(&mp_lv_obj_set_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_clear_protect), MP_ROM_PTR(&mp_lv_obj_clear_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_event_cb), MP_ROM_PTR(&mp_lv_obj_set_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_signal_cb), MP_ROM_PTR(&mp_lv_obj_set_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_design_cb), MP_ROM_PTR(&mp_lv_obj_set_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_allocate_ext_attr), MP_ROM_PTR(&mp_lv_obj_allocate_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_refresh_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_refresh_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_screen), MP_ROM_PTR(&mp_lv_obj_get_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_disp), MP_ROM_PTR(&mp_lv_obj_get_disp_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent), MP_ROM_PTR(&mp_lv_obj_get_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child), MP_ROM_PTR(&mp_lv_obj_get_child_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_child_back), MP_ROM_PTR(&mp_lv_obj_get_child_back_obj) },
    { MP_ROM_QSTR(MP_QSTR_count_children), MP_ROM_PTR(&mp_lv_obj_count_children_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_coords), MP_ROM_PTR(&mp_lv_obj_get_coords_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_x), MP_ROM_PTR(&mp_lv_obj_get_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_y), MP_ROM_PTR(&mp_lv_obj_get_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width), MP_ROM_PTR(&mp_lv_obj_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height), MP_ROM_PTR(&mp_lv_obj_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_width_fit), MP_ROM_PTR(&mp_lv_obj_get_width_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_height_fit), MP_ROM_PTR(&mp_lv_obj_get_height_fit_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_auto_realign), MP_ROM_PTR(&mp_lv_obj_get_auto_realign_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_draw_pad), MP_ROM_PTR(&mp_lv_obj_get_ext_draw_pad_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_hidden), MP_ROM_PTR(&mp_lv_obj_get_hidden_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_click), MP_ROM_PTR(&mp_lv_obj_get_click_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_top), MP_ROM_PTR(&mp_lv_obj_get_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag), MP_ROM_PTR(&mp_lv_obj_get_drag_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_dir), MP_ROM_PTR(&mp_lv_obj_get_drag_dir_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_throw), MP_ROM_PTR(&mp_lv_obj_get_drag_throw_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_drag_parent), MP_ROM_PTR(&mp_lv_obj_get_drag_parent_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_parent_event), MP_ROM_PTR(&mp_lv_obj_get_parent_event_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale_enable), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_opa_scale), MP_ROM_PTR(&mp_lv_obj_get_opa_scale_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_protect), MP_ROM_PTR(&mp_lv_obj_get_protect_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_protected), MP_ROM_PTR(&mp_lv_obj_is_protected_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_signal_cb), MP_ROM_PTR(&mp_lv_obj_get_signal_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_design_cb), MP_ROM_PTR(&mp_lv_obj_get_design_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_event_cb), MP_ROM_PTR(&mp_lv_obj_get_event_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_ext_attr), MP_ROM_PTR(&mp_lv_obj_get_ext_attr_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_type), MP_ROM_PTR(&mp_lv_obj_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data), MP_ROM_PTR(&mp_lv_obj_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_user_data_ptr), MP_ROM_PTR(&mp_lv_obj_get_user_data_ptr_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_user_data), MP_ROM_PTR(&mp_lv_obj_set_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_group), MP_ROM_PTR(&mp_lv_obj_get_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_focused), MP_ROM_PTR(&mp_lv_obj_is_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_STYLE), MP_ROM_PTR(&mp_LV_SPINBOX_STYLE_type) }
};

STATIC MP_DEFINE_CONST_DICT(spinbox_locals_dict, spinbox_locals_dict_table);

STATIC void spinbox_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl spinbox");
}


STATIC mp_obj_t spinbox_make_new(
    const mp_obj_type_t *type,
    size_t n_args,
    size_t n_kw,
    const mp_obj_t *args)
{
    return make_new(&lv_spinbox_create, type, n_args, n_kw, args);           
}


STATIC const mp_obj_type_t mp_spinbox_type = {
    { &mp_type_type },
    .name = MP_QSTR_spinbox,
    .print = spinbox_print,
    .make_new = spinbox_make_new,
    .locals_dict = (mp_obj_dict_t*)&spinbox_locals_dict,
    .parent = NULL,
};
    

STATIC inline const mp_obj_type_t *get_BaseObj_type()
{
    return &mp_obj_type;
}


/* 
 *
 * Global Module Functions
 *
 */


/*
 * lvgl extension definition for:
 * inline static uint8_t lv_color_to1(lv_color_t color)
 */
 
STATIC mp_obj_t mp_lv_color_to1(size_t n_args, const mp_obj_t *args)
{
    lv_color_t color = mp_write_lv_color32_t(args[0]);
    uint8_t res = lv_color_to1(color);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_color_to1_obj, 1, 1, mp_lv_color_to1);

 

/*
 * lvgl extension definition for:
 * inline static uint8_t lv_color_to8(lv_color_t color)
 */
 
STATIC mp_obj_t mp_lv_color_to8(size_t n_args, const mp_obj_t *args)
{
    lv_color_t color = mp_write_lv_color32_t(args[0]);
    uint8_t res = lv_color_to8(color);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_color_to8_obj, 1, 1, mp_lv_color_to8);

 

/*
 * lvgl extension definition for:
 * inline static uint16_t lv_color_to16(lv_color_t color)
 */
 
STATIC mp_obj_t mp_lv_color_to16(size_t n_args, const mp_obj_t *args)
{
    lv_color_t color = mp_write_lv_color32_t(args[0]);
    uint16_t res = lv_color_to16(color);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_color_to16_obj, 1, 1, mp_lv_color_to16);

 

/*
 * lvgl extension definition for:
 * inline static uint32_t lv_color_to32(lv_color_t color)
 */
 
STATIC mp_obj_t mp_lv_color_to32(size_t n_args, const mp_obj_t *args)
{
    lv_color_t color = mp_write_lv_color32_t(args[0]);
    uint32_t res = lv_color_to32(color);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_color_to32_obj, 1, 1, mp_lv_color_to32);

 

/*
 * lvgl extension definition for:
 * inline static lv_color_t lv_color_mix(lv_color_t c1, lv_color_t c2, uint8_t mix)
 */
 
STATIC mp_obj_t mp_lv_color_mix(size_t n_args, const mp_obj_t *args)
{
    lv_color_t c1 = mp_write_lv_color32_t(args[0]);
    lv_color_t c2 = mp_write_lv_color32_t(args[1]);
    uint8_t mix = (uint8_t)mp_obj_get_int(args[2]);
    lv_color_t res = lv_color_mix(c1, c2, mix);
    return mp_read_lv_color32_t(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_color_mix_obj, 3, 3, mp_lv_color_mix);

 

/*
 * lvgl extension definition for:
 * inline static uint8_t lv_color_brightness(lv_color_t color)
 */
 
STATIC mp_obj_t mp_lv_color_brightness(size_t n_args, const mp_obj_t *args)
{
    lv_color_t color = mp_write_lv_color32_t(args[0]);
    uint8_t res = lv_color_brightness(color);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_color_brightness_obj, 1, 1, mp_lv_color_brightness);

 

/*
 * lvgl extension definition for:
 * inline static lv_color_t lv_color_make(uint8_t r8, uint8_t g8, uint8_t b8)
 */
 
STATIC mp_obj_t mp_lv_color_make(size_t n_args, const mp_obj_t *args)
{
    uint8_t r8 = (uint8_t)mp_obj_get_int(args[0]);
    uint8_t g8 = (uint8_t)mp_obj_get_int(args[1]);
    uint8_t b8 = (uint8_t)mp_obj_get_int(args[2]);
    lv_color_t res = lv_color_make(r8, g8, b8);
    return mp_read_lv_color32_t(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_color_make_obj, 3, 3, mp_lv_color_make);

 

/*
 * lvgl extension definition for:
 * inline static lv_color_t lv_color_hex(uint32_t c)
 */
 
STATIC mp_obj_t mp_lv_color_hex(size_t n_args, const mp_obj_t *args)
{
    uint32_t c = (uint32_t)mp_obj_get_int(args[0]);
    lv_color_t res = lv_color_hex(c);
    return mp_read_lv_color32_t(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_color_hex_obj, 1, 1, mp_lv_color_hex);

 

/*
 * lvgl extension definition for:
 * inline static lv_color_t lv_color_hex3(uint32_t c)
 */
 
STATIC mp_obj_t mp_lv_color_hex3(size_t n_args, const mp_obj_t *args)
{
    uint32_t c = (uint32_t)mp_obj_get_int(args[0]);
    lv_color_t res = lv_color_hex3(c);
    return mp_read_lv_color32_t(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_color_hex3_obj, 1, 1, mp_lv_color_hex3);

 

/*
 * lvgl extension definition for:
 * inline static void lv_area_copy(lv_area_t *dest, const lv_area_t *src)
 */
 
STATIC mp_obj_t mp_lv_area_copy(size_t n_args, const mp_obj_t *args)
{
    lv_area_t *dest = mp_to_ptr(args[0]);
    const lv_area_t *src = mp_to_ptr(args[1]);
    lv_area_copy(dest, src);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_copy_obj, 2, 2, mp_lv_area_copy);

 

/*
 * lvgl extension definition for:
 * inline static lv_coord_t lv_area_get_width(const lv_area_t *area_p)
 */
 
STATIC mp_obj_t mp_lv_area_get_width(size_t n_args, const mp_obj_t *args)
{
    const lv_area_t *area_p = mp_to_ptr(args[0]);
    lv_coord_t res = lv_area_get_width(area_p);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_get_width_obj, 1, 1, mp_lv_area_get_width);

 

/*
 * lvgl extension definition for:
 * inline static lv_coord_t lv_area_get_height(const lv_area_t *area_p)
 */
 
STATIC mp_obj_t mp_lv_area_get_height(size_t n_args, const mp_obj_t *args)
{
    const lv_area_t *area_p = mp_to_ptr(args[0]);
    lv_coord_t res = lv_area_get_height(area_p);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_get_height_obj, 1, 1, mp_lv_area_get_height);

 

/*
 * lvgl extension definition for:
 * inline static uint8_t lv_font_get_height(const lv_font_t *font_p)
 */
 
STATIC mp_obj_t mp_lv_font_get_height(size_t n_args, const mp_obj_t *args)
{
    const lv_font_t *font_p = mp_to_ptr(args[0]);
    uint8_t res = lv_font_get_height(font_p);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_get_height_obj, 1, 1, mp_lv_font_get_height);

 

/*
 * lvgl extension definition for:
 * inline static lv_obj_t *lv_scr_act(void)
 */
 
STATIC mp_obj_t mp_lv_scr_act(size_t n_args, const mp_obj_t *args)
{
    
    lv_obj_t * res = lv_scr_act();
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_scr_act_obj, 0, 0, mp_lv_scr_act);

 

/*
 * lvgl extension definition for:
 * inline static lv_obj_t *lv_layer_top(void)
 */
 
STATIC mp_obj_t mp_lv_layer_top(size_t n_args, const mp_obj_t *args)
{
    
    lv_obj_t * res = lv_layer_top();
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_layer_top_obj, 0, 0, mp_lv_layer_top);

 

/*
 * lvgl extension definition for:
 * inline static lv_obj_t *lv_layer_sys(void)
 */
 
STATIC mp_obj_t mp_lv_layer_sys(size_t n_args, const mp_obj_t *args)
{
    
    lv_obj_t * res = lv_layer_sys();
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_layer_sys_obj, 0, 0, mp_lv_layer_sys);

 

/*
 * lvgl extension definition for:
 * inline static void lv_scr_load(lv_obj_t *scr)
 */
 
STATIC mp_obj_t mp_lv_scr_load(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *scr = mp_to_lv(args[0]);
    lv_scr_load(scr);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_scr_load_obj, 1, 1, mp_lv_scr_load);

 

/*
 * Function NOT generated:
 * Callback argument 'void f(lv_log_level_t, const char *, uint32_t, const char *)' cannot be the first argument! We assume the first argument contains the user_data
 * void lv_log_register_print(void f(lv_log_level_t, const char *, uint32_t, const char *))
 */
    

/*
 * lvgl extension definition for:
 * void lv_log_add(lv_log_level_t level, const char *file, int line, const char *dsc)
 */
 
STATIC mp_obj_t mp_lv_log_add(size_t n_args, const mp_obj_t *args)
{
    lv_log_level_t level = (int8_t)mp_obj_get_int(args[0]);
    const char *file = (char*)mp_obj_str_get_str(args[1]);
    int line = (int)mp_obj_get_int(args[2]);
    const char *dsc = (char*)mp_obj_str_get_str(args[3]);
    lv_log_add(level, file, line, dsc);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_log_add_obj, 4, 4, mp_lv_log_add);

 

/*
 * lvgl extension definition for:
 * void lv_mem_init(void)
 */
 
STATIC mp_obj_t mp_lv_mem_init(size_t n_args, const mp_obj_t *args)
{
    
    lv_mem_init();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mem_init_obj, 0, 0, mp_lv_mem_init);

 

/*
 * lvgl extension definition for:
 * void *lv_mem_alloc(uint32_t size)
 */
 
STATIC mp_obj_t mp_lv_mem_alloc(size_t n_args, const mp_obj_t *args)
{
    uint32_t size = (uint32_t)mp_obj_get_int(args[0]);
    void * res = lv_mem_alloc(size);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mem_alloc_obj, 1, 1, mp_lv_mem_alloc);

 

/*
 * lvgl extension definition for:
 * void lv_mem_free(const void *data)
 */
 
STATIC mp_obj_t mp_lv_mem_free(size_t n_args, const mp_obj_t *args)
{
    const void *data = mp_to_ptr(args[0]);
    lv_mem_free(data);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mem_free_obj, 1, 1, mp_lv_mem_free);

 

/*
 * lvgl extension definition for:
 * void *lv_mem_realloc(void *data_p, uint32_t new_size)
 */
 
STATIC mp_obj_t mp_lv_mem_realloc(size_t n_args, const mp_obj_t *args)
{
    void *data_p = mp_to_ptr(args[0]);
    uint32_t new_size = (uint32_t)mp_obj_get_int(args[1]);
    void * res = lv_mem_realloc(data_p, new_size);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mem_realloc_obj, 2, 2, mp_lv_mem_realloc);

 

/*
 * lvgl extension definition for:
 * void lv_mem_defrag(void)
 */
 
STATIC mp_obj_t mp_lv_mem_defrag(size_t n_args, const mp_obj_t *args)
{
    
    lv_mem_defrag();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mem_defrag_obj, 0, 0, mp_lv_mem_defrag);

 

/*
 * Struct lv_mem_monitor_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_mem_monitor_t_type();

STATIC inline lv_mem_monitor_t* mp_write_ptr_lv_mem_monitor_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_mem_monitor_t_type()));
    return (lv_mem_monitor_t*)self->data;
}

#define mp_write_lv_mem_monitor_t(struct_obj) *mp_write_ptr_lv_mem_monitor_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_mem_monitor_t(lv_mem_monitor_t *field)
{
    return lv_to_mp_struct(get_mp_lv_mem_monitor_t_type(), field);
}

#define mp_read_lv_mem_monitor_t(field) mp_read_ptr_lv_mem_monitor_t(copy_buffer(&field, sizeof(lv_mem_monitor_t)))
#define mp_read_byref_lv_mem_monitor_t(field) mp_read_ptr_lv_mem_monitor_t(&field)

STATIC void mp_lv_mem_monitor_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_mem_monitor_t *data = (lv_mem_monitor_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_total_size: dest[0] = mp_obj_new_int_from_uint(data->total_size); break; // converting from uint32_t;
            case MP_QSTR_free_cnt: dest[0] = mp_obj_new_int_from_uint(data->free_cnt); break; // converting from uint32_t;
            case MP_QSTR_free_size: dest[0] = mp_obj_new_int_from_uint(data->free_size); break; // converting from uint32_t;
            case MP_QSTR_free_biggest_size: dest[0] = mp_obj_new_int_from_uint(data->free_biggest_size); break; // converting from uint32_t;
            case MP_QSTR_used_cnt: dest[0] = mp_obj_new_int_from_uint(data->used_cnt); break; // converting from uint32_t;
            case MP_QSTR_used_pct: dest[0] = mp_obj_new_int_from_uint(data->used_pct); break; // converting from uint8_t;
            case MP_QSTR_frag_pct: dest[0] = mp_obj_new_int_from_uint(data->frag_pct); break; // converting from uint8_t;
            default: field_not_found(MP_QSTR_lv_mem_monitor_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_total_size: data->total_size = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_free_cnt: data->free_cnt = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_free_size: data->free_size = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_free_biggest_size: data->free_biggest_size = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_used_cnt: data->used_cnt = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_used_pct: data->used_pct = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_frag_pct: data->frag_pct = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                default: field_not_found(MP_QSTR_lv_mem_monitor_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_mem_monitor_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_mem_monitor_t");
}

STATIC const mp_rom_map_elem_t mp_lv_mem_monitor_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_mem_monitor_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_mem_monitor_t_locals_dict, mp_lv_mem_monitor_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_mem_monitor_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_mem_monitor_t,
    .print = mp_lv_mem_monitor_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_mem_monitor_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_mem_monitor_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_mem_monitor_t_type()
{
    return &mp_lv_mem_monitor_t_type;
}
    

/*
 * lvgl extension definition for:
 * void lv_mem_monitor(lv_mem_monitor_t *mon_p)
 */
 
STATIC mp_obj_t mp_lv_mem_monitor(size_t n_args, const mp_obj_t *args)
{
    lv_mem_monitor_t *mon_p = mp_to_ptr(args[0]);
    lv_mem_monitor(mon_p);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mem_monitor_obj, 1, 1, mp_lv_mem_monitor);

 

/*
 * lvgl extension definition for:
 * uint32_t lv_mem_get_size(const void *data)
 */
 
STATIC mp_obj_t mp_lv_mem_get_size(size_t n_args, const mp_obj_t *args)
{
    const void *data = mp_to_ptr(args[0]);
    uint32_t res = lv_mem_get_size(data);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_mem_get_size_obj, 1, 1, mp_lv_mem_get_size);

 

/*
 * lvgl extension definition for:
 * void lv_ll_init(lv_ll_t *ll_p, uint32_t node_size)
 */
 
STATIC mp_obj_t mp_lv_ll_init(size_t n_args, const mp_obj_t *args)
{
    lv_ll_t *ll_p = mp_write_ptr_lv_ll_t(args[0]);
    uint32_t node_size = (uint32_t)mp_obj_get_int(args[1]);
    lv_ll_init(ll_p, node_size);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_init_obj, 2, 2, mp_lv_ll_init);

 

/*
 * lvgl extension definition for:
 * void *lv_ll_ins_head(lv_ll_t *ll_p)
 */
 
STATIC mp_obj_t mp_lv_ll_ins_head(size_t n_args, const mp_obj_t *args)
{
    lv_ll_t *ll_p = mp_write_ptr_lv_ll_t(args[0]);
    void * res = lv_ll_ins_head(ll_p);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_ins_head_obj, 1, 1, mp_lv_ll_ins_head);

 

/*
 * lvgl extension definition for:
 * void *lv_ll_ins_prev(lv_ll_t *ll_p, void *n_act)
 */
 
STATIC mp_obj_t mp_lv_ll_ins_prev(size_t n_args, const mp_obj_t *args)
{
    lv_ll_t *ll_p = mp_write_ptr_lv_ll_t(args[0]);
    void *n_act = mp_to_ptr(args[1]);
    void * res = lv_ll_ins_prev(ll_p, n_act);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_ins_prev_obj, 2, 2, mp_lv_ll_ins_prev);

 

/*
 * lvgl extension definition for:
 * void *lv_ll_ins_tail(lv_ll_t *ll_p)
 */
 
STATIC mp_obj_t mp_lv_ll_ins_tail(size_t n_args, const mp_obj_t *args)
{
    lv_ll_t *ll_p = mp_write_ptr_lv_ll_t(args[0]);
    void * res = lv_ll_ins_tail(ll_p);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_ins_tail_obj, 1, 1, mp_lv_ll_ins_tail);

 

/*
 * lvgl extension definition for:
 * void lv_ll_rem(lv_ll_t *ll_p, void *node_p)
 */
 
STATIC mp_obj_t mp_lv_ll_rem(size_t n_args, const mp_obj_t *args)
{
    lv_ll_t *ll_p = mp_write_ptr_lv_ll_t(args[0]);
    void *node_p = mp_to_ptr(args[1]);
    lv_ll_rem(ll_p, node_p);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_rem_obj, 2, 2, mp_lv_ll_rem);

 

/*
 * lvgl extension definition for:
 * void lv_ll_clear(lv_ll_t *ll_p)
 */
 
STATIC mp_obj_t mp_lv_ll_clear(size_t n_args, const mp_obj_t *args)
{
    lv_ll_t *ll_p = mp_write_ptr_lv_ll_t(args[0]);
    lv_ll_clear(ll_p);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_clear_obj, 1, 1, mp_lv_ll_clear);

 

/*
 * lvgl extension definition for:
 * void lv_ll_chg_list(lv_ll_t *ll_ori_p, lv_ll_t *ll_new_p, void *node, bool head)
 */
 
STATIC mp_obj_t mp_lv_ll_chg_list(size_t n_args, const mp_obj_t *args)
{
    lv_ll_t *ll_ori_p = mp_write_ptr_lv_ll_t(args[0]);
    lv_ll_t *ll_new_p = mp_write_ptr_lv_ll_t(args[1]);
    void *node = mp_to_ptr(args[2]);
    bool head = mp_obj_is_true(args[3]);
    lv_ll_chg_list(ll_ori_p, ll_new_p, node, head);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_chg_list_obj, 4, 4, mp_lv_ll_chg_list);

 

/*
 * lvgl extension definition for:
 * void *lv_ll_get_head(const lv_ll_t *ll_p)
 */
 
STATIC mp_obj_t mp_lv_ll_get_head(size_t n_args, const mp_obj_t *args)
{
    const lv_ll_t *ll_p = mp_write_ptr_lv_ll_t(args[0]);
    void * res = lv_ll_get_head(ll_p);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_get_head_obj, 1, 1, mp_lv_ll_get_head);

 

/*
 * lvgl extension definition for:
 * void *lv_ll_get_tail(const lv_ll_t *ll_p)
 */
 
STATIC mp_obj_t mp_lv_ll_get_tail(size_t n_args, const mp_obj_t *args)
{
    const lv_ll_t *ll_p = mp_write_ptr_lv_ll_t(args[0]);
    void * res = lv_ll_get_tail(ll_p);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_get_tail_obj, 1, 1, mp_lv_ll_get_tail);

 

/*
 * lvgl extension definition for:
 * void *lv_ll_get_next(const lv_ll_t *ll_p, const void *n_act)
 */
 
STATIC mp_obj_t mp_lv_ll_get_next(size_t n_args, const mp_obj_t *args)
{
    const lv_ll_t *ll_p = mp_write_ptr_lv_ll_t(args[0]);
    const void *n_act = mp_to_ptr(args[1]);
    void * res = lv_ll_get_next(ll_p, n_act);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_get_next_obj, 2, 2, mp_lv_ll_get_next);

 

/*
 * lvgl extension definition for:
 * void *lv_ll_get_prev(const lv_ll_t *ll_p, const void *n_act)
 */
 
STATIC mp_obj_t mp_lv_ll_get_prev(size_t n_args, const mp_obj_t *args)
{
    const lv_ll_t *ll_p = mp_write_ptr_lv_ll_t(args[0]);
    const void *n_act = mp_to_ptr(args[1]);
    void * res = lv_ll_get_prev(ll_p, n_act);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_get_prev_obj, 2, 2, mp_lv_ll_get_prev);

 

/*
 * lvgl extension definition for:
 * void lv_ll_move_before(lv_ll_t *ll_p, void *n_act, void *n_after)
 */
 
STATIC mp_obj_t mp_lv_ll_move_before(size_t n_args, const mp_obj_t *args)
{
    lv_ll_t *ll_p = mp_write_ptr_lv_ll_t(args[0]);
    void *n_act = mp_to_ptr(args[1]);
    void *n_after = mp_to_ptr(args[2]);
    lv_ll_move_before(ll_p, n_act, n_after);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_move_before_obj, 3, 3, mp_lv_ll_move_before);

 

/*
 * lvgl extension definition for:
 * bool lv_ll_is_empty(lv_ll_t *ll_p)
 */
 
STATIC mp_obj_t mp_lv_ll_is_empty(size_t n_args, const mp_obj_t *args)
{
    lv_ll_t *ll_p = mp_write_ptr_lv_ll_t(args[0]);
    bool res = lv_ll_is_empty(ll_p);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_ll_is_empty_obj, 1, 1, mp_lv_ll_is_empty);

 

/*
 * lvgl extension definition for:
 * void lv_task_init(void)
 */
 
STATIC mp_obj_t mp_lv_task_init(size_t n_args, const mp_obj_t *args)
{
    
    lv_task_init();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_task_init_obj, 0, 0, mp_lv_task_init);

 

/*
 * lvgl extension definition for:
 * void lv_task_handler(void)
 */
 
STATIC mp_obj_t mp_lv_task_handler(size_t n_args, const mp_obj_t *args)
{
    
    lv_task_handler();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_task_handler_obj, 0, 0, mp_lv_task_handler);

 

/*
 * Function NOT generated:
 * Callback argument 'void (*task)(lv_task_t *)' cannot be the first argument! We assume the first argument contains the user_data
 * lv_task_t *lv_task_create(void (*task)(lv_task_t *), uint32_t period, lv_task_prio_t prio, void *user_data)
 */
    

/*
 * lvgl extension definition for:
 * void lv_task_del(lv_task_t *lv_task_p)
 */
 
STATIC mp_obj_t mp_lv_task_del(size_t n_args, const mp_obj_t *args)
{
    lv_task_t *lv_task_p = mp_to_ptr(args[0]);
    lv_task_del(lv_task_p);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_task_del_obj, 1, 1, mp_lv_task_del);

 

/*
 * lvgl extension definition for:
 * void lv_task_set_prio(lv_task_t *lv_task_p, lv_task_prio_t prio)
 */
 
STATIC mp_obj_t mp_lv_task_set_prio(size_t n_args, const mp_obj_t *args)
{
    lv_task_t *lv_task_p = mp_to_ptr(args[0]);
    lv_task_prio_t prio = (uint8_t)mp_obj_get_int(args[1]);
    lv_task_set_prio(lv_task_p, prio);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_task_set_prio_obj, 2, 2, mp_lv_task_set_prio);

 

/*
 * lvgl extension definition for:
 * void lv_task_set_period(lv_task_t *lv_task_p, uint32_t period)
 */
 
STATIC mp_obj_t mp_lv_task_set_period(size_t n_args, const mp_obj_t *args)
{
    lv_task_t *lv_task_p = mp_to_ptr(args[0]);
    uint32_t period = (uint32_t)mp_obj_get_int(args[1]);
    lv_task_set_period(lv_task_p, period);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_task_set_period_obj, 2, 2, mp_lv_task_set_period);

 

/*
 * lvgl extension definition for:
 * void lv_task_ready(lv_task_t *lv_task_p)
 */
 
STATIC mp_obj_t mp_lv_task_ready(size_t n_args, const mp_obj_t *args)
{
    lv_task_t *lv_task_p = mp_to_ptr(args[0]);
    lv_task_ready(lv_task_p);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_task_ready_obj, 1, 1, mp_lv_task_ready);

 

/*
 * lvgl extension definition for:
 * void lv_task_once(lv_task_t *lv_task_p)
 */
 
STATIC mp_obj_t mp_lv_task_once(size_t n_args, const mp_obj_t *args)
{
    lv_task_t *lv_task_p = mp_to_ptr(args[0]);
    lv_task_once(lv_task_p);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_task_once_obj, 1, 1, mp_lv_task_once);

 

/*
 * lvgl extension definition for:
 * void lv_task_reset(lv_task_t *lv_task_p)
 */
 
STATIC mp_obj_t mp_lv_task_reset(size_t n_args, const mp_obj_t *args)
{
    lv_task_t *lv_task_p = mp_to_ptr(args[0]);
    lv_task_reset(lv_task_p);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_task_reset_obj, 1, 1, mp_lv_task_reset);

 

/*
 * lvgl extension definition for:
 * void lv_task_enable(bool en)
 */
 
STATIC mp_obj_t mp_lv_task_enable(size_t n_args, const mp_obj_t *args)
{
    bool en = mp_obj_is_true(args[0]);
    lv_task_enable(en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_task_enable_obj, 1, 1, mp_lv_task_enable);

 

/*
 * lvgl extension definition for:
 * uint8_t lv_task_get_idle(void)
 */
 
STATIC mp_obj_t mp_lv_task_get_idle(size_t n_args, const mp_obj_t *args)
{
    
    uint8_t res = lv_task_get_idle();
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_task_get_idle_obj, 0, 0, mp_lv_task_get_idle);

 

/*
 * lvgl extension definition for:
 * int16_t lv_trigo_sin(int16_t angle)
 */
 
STATIC mp_obj_t mp_lv_trigo_sin(size_t n_args, const mp_obj_t *args)
{
    int16_t angle = (int16_t)mp_obj_get_int(args[0]);
    int16_t res = lv_trigo_sin(angle);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_trigo_sin_obj, 1, 1, mp_lv_trigo_sin);

 

/*
 * lvgl extension definition for:
 * int32_t lv_bezier3(uint32_t t, int32_t u0, int32_t u1, int32_t u2, int32_t u3)
 */
 
STATIC mp_obj_t mp_lv_bezier3(size_t n_args, const mp_obj_t *args)
{
    uint32_t t = (uint32_t)mp_obj_get_int(args[0]);
    int32_t u0 = (int32_t)mp_obj_get_int(args[1]);
    int32_t u1 = (int32_t)mp_obj_get_int(args[2]);
    int32_t u2 = (int32_t)mp_obj_get_int(args[3]);
    int32_t u3 = (int32_t)mp_obj_get_int(args[4]);
    int32_t res = lv_bezier3(t, u0, u1, u2, u3);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_bezier3_obj, 5, 5, mp_lv_bezier3);

 

/*
 * lvgl extension definition for:
 * lv_color_t lv_color_hsv_to_rgb(uint16_t h, uint8_t s, uint8_t v)
 */
 
STATIC mp_obj_t mp_lv_color_hsv_to_rgb(size_t n_args, const mp_obj_t *args)
{
    uint16_t h = (uint16_t)mp_obj_get_int(args[0]);
    uint8_t s = (uint8_t)mp_obj_get_int(args[1]);
    uint8_t v = (uint8_t)mp_obj_get_int(args[2]);
    lv_color_t res = lv_color_hsv_to_rgb(h, s, v);
    return mp_read_lv_color32_t(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_color_hsv_to_rgb_obj, 3, 3, mp_lv_color_hsv_to_rgb);

 

/*
 * Struct lv_color_hsv_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_color_hsv_t_type();

STATIC inline lv_color_hsv_t* mp_write_ptr_lv_color_hsv_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_color_hsv_t_type()));
    return (lv_color_hsv_t*)self->data;
}

#define mp_write_lv_color_hsv_t(struct_obj) *mp_write_ptr_lv_color_hsv_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_color_hsv_t(lv_color_hsv_t *field)
{
    return lv_to_mp_struct(get_mp_lv_color_hsv_t_type(), field);
}

#define mp_read_lv_color_hsv_t(field) mp_read_ptr_lv_color_hsv_t(copy_buffer(&field, sizeof(lv_color_hsv_t)))
#define mp_read_byref_lv_color_hsv_t(field) mp_read_ptr_lv_color_hsv_t(&field)

STATIC void mp_lv_color_hsv_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_color_hsv_t *data = (lv_color_hsv_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_h: dest[0] = mp_obj_new_int_from_uint(data->h); break; // converting from uint16_t;
            case MP_QSTR_s: dest[0] = mp_obj_new_int_from_uint(data->s); break; // converting from uint8_t;
            case MP_QSTR_v: dest[0] = mp_obj_new_int_from_uint(data->v); break; // converting from uint8_t;
            default: field_not_found(MP_QSTR_lv_color_hsv_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_h: data->h = (uint16_t)mp_obj_get_int(dest[1]); break; // converting to uint16_t;
                case MP_QSTR_s: data->s = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_v: data->v = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                default: field_not_found(MP_QSTR_lv_color_hsv_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_color_hsv_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_color_hsv_t");
}

STATIC const mp_rom_map_elem_t mp_lv_color_hsv_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_color_hsv_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_color_hsv_t_locals_dict, mp_lv_color_hsv_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_color_hsv_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_color_hsv_t,
    .print = mp_lv_color_hsv_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_color_hsv_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_color_hsv_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_color_hsv_t_type()
{
    return &mp_lv_color_hsv_t_type;
}
    

/*
 * lvgl extension definition for:
 * lv_color_hsv_t lv_color_rgb_to_hsv(uint8_t r, uint8_t g, uint8_t b)
 */
 
STATIC mp_obj_t mp_lv_color_rgb_to_hsv(size_t n_args, const mp_obj_t *args)
{
    uint8_t r = (uint8_t)mp_obj_get_int(args[0]);
    uint8_t g = (uint8_t)mp_obj_get_int(args[1]);
    uint8_t b = (uint8_t)mp_obj_get_int(args[2]);
    lv_color_hsv_t res = lv_color_rgb_to_hsv(r, g, b);
    return mp_read_lv_color_hsv_t(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_color_rgb_to_hsv_obj, 3, 3, mp_lv_color_rgb_to_hsv);

 

/*
 * lvgl extension definition for:
 * void lv_area_set(lv_area_t *area_p, lv_coord_t x1, lv_coord_t y1, lv_coord_t x2, lv_coord_t y2)
 */
 
STATIC mp_obj_t mp_lv_area_set(size_t n_args, const mp_obj_t *args)
{
    lv_area_t *area_p = mp_to_ptr(args[0]);
    lv_coord_t x1 = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y1 = (int16_t)mp_obj_get_int(args[2]);
    lv_coord_t x2 = (int16_t)mp_obj_get_int(args[3]);
    lv_coord_t y2 = (int16_t)mp_obj_get_int(args[4]);
    lv_area_set(area_p, x1, y1, x2, y2);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_set_obj, 5, 5, mp_lv_area_set);

 

/*
 * lvgl extension definition for:
 * void lv_area_set_width(lv_area_t *area_p, lv_coord_t w)
 */
 
STATIC mp_obj_t mp_lv_area_set_width(size_t n_args, const mp_obj_t *args)
{
    lv_area_t *area_p = mp_to_ptr(args[0]);
    lv_coord_t w = (int16_t)mp_obj_get_int(args[1]);
    lv_area_set_width(area_p, w);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_set_width_obj, 2, 2, mp_lv_area_set_width);

 

/*
 * lvgl extension definition for:
 * void lv_area_set_height(lv_area_t *area_p, lv_coord_t h)
 */
 
STATIC mp_obj_t mp_lv_area_set_height(size_t n_args, const mp_obj_t *args)
{
    lv_area_t *area_p = mp_to_ptr(args[0]);
    lv_coord_t h = (int16_t)mp_obj_get_int(args[1]);
    lv_area_set_height(area_p, h);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_set_height_obj, 2, 2, mp_lv_area_set_height);

 

/*
 * lvgl extension definition for:
 * void lv_area_set_pos(lv_area_t *area_p, lv_coord_t x, lv_coord_t y)
 */
 
STATIC mp_obj_t mp_lv_area_set_pos(size_t n_args, const mp_obj_t *args)
{
    lv_area_t *area_p = mp_to_ptr(args[0]);
    lv_coord_t x = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[2]);
    lv_area_set_pos(area_p, x, y);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_set_pos_obj, 3, 3, mp_lv_area_set_pos);

 

/*
 * lvgl extension definition for:
 * uint32_t lv_area_get_size(const lv_area_t *area_p)
 */
 
STATIC mp_obj_t mp_lv_area_get_size(size_t n_args, const mp_obj_t *args)
{
    const lv_area_t *area_p = mp_to_ptr(args[0]);
    uint32_t res = lv_area_get_size(area_p);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_get_size_obj, 1, 1, mp_lv_area_get_size);

 

/*
 * lvgl extension definition for:
 * bool lv_area_intersect(lv_area_t *res_p, const lv_area_t *a1_p, const lv_area_t *a2_p)
 */
 
STATIC mp_obj_t mp_lv_area_intersect(size_t n_args, const mp_obj_t *args)
{
    lv_area_t *res_p = mp_to_ptr(args[0]);
    const lv_area_t *a1_p = mp_to_ptr(args[1]);
    const lv_area_t *a2_p = mp_to_ptr(args[2]);
    bool res = lv_area_intersect(res_p, a1_p, a2_p);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_intersect_obj, 3, 3, mp_lv_area_intersect);

 

/*
 * lvgl extension definition for:
 * void lv_area_join(lv_area_t *a_res_p, const lv_area_t *a1_p, const lv_area_t *a2_p)
 */
 
STATIC mp_obj_t mp_lv_area_join(size_t n_args, const mp_obj_t *args)
{
    lv_area_t *a_res_p = mp_to_ptr(args[0]);
    const lv_area_t *a1_p = mp_to_ptr(args[1]);
    const lv_area_t *a2_p = mp_to_ptr(args[2]);
    lv_area_join(a_res_p, a1_p, a2_p);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_join_obj, 3, 3, mp_lv_area_join);

 

/*
 * lvgl extension definition for:
 * bool lv_area_is_point_on(const lv_area_t *a_p, const lv_point_t *p_p)
 */
 
STATIC mp_obj_t mp_lv_area_is_point_on(size_t n_args, const mp_obj_t *args)
{
    const lv_area_t *a_p = mp_to_ptr(args[0]);
    const lv_point_t *p_p = mp_to_ptr(args[1]);
    bool res = lv_area_is_point_on(a_p, p_p);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_is_point_on_obj, 2, 2, mp_lv_area_is_point_on);

 

/*
 * lvgl extension definition for:
 * bool lv_area_is_on(const lv_area_t *a1_p, const lv_area_t *a2_p)
 */
 
STATIC mp_obj_t mp_lv_area_is_on(size_t n_args, const mp_obj_t *args)
{
    const lv_area_t *a1_p = mp_to_ptr(args[0]);
    const lv_area_t *a2_p = mp_to_ptr(args[1]);
    bool res = lv_area_is_on(a1_p, a2_p);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_is_on_obj, 2, 2, mp_lv_area_is_on);

 

/*
 * lvgl extension definition for:
 * bool lv_area_is_in(const lv_area_t *ain_p, const lv_area_t *aholder_p)
 */
 
STATIC mp_obj_t mp_lv_area_is_in(size_t n_args, const mp_obj_t *args)
{
    const lv_area_t *ain_p = mp_to_ptr(args[0]);
    const lv_area_t *aholder_p = mp_to_ptr(args[1]);
    bool res = lv_area_is_in(ain_p, aholder_p);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_area_is_in_obj, 2, 2, mp_lv_area_is_in);

 

/*
 * lvgl extension definition for:
 * void lv_disp_drv_init(lv_disp_drv_t *driver)
 */
 
STATIC mp_obj_t mp_lv_disp_drv_init(size_t n_args, const mp_obj_t *args)
{
    lv_disp_drv_t *driver = mp_write_ptr_lv_disp_drv_t(args[0]);
    lv_disp_drv_init(driver);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_drv_init_obj, 1, 1, mp_lv_disp_drv_init);

 

/*
 * lvgl extension definition for:
 * void lv_disp_buf_init(lv_disp_buf_t *disp_buf, void *buf1, void *buf2, uint32_t size_in_px_cnt)
 */
 
STATIC mp_obj_t mp_lv_disp_buf_init(size_t n_args, const mp_obj_t *args)
{
    lv_disp_buf_t *disp_buf = mp_to_ptr(args[0]);
    void *buf1 = mp_to_ptr(args[1]);
    void *buf2 = mp_to_ptr(args[2]);
    uint32_t size_in_px_cnt = (uint32_t)mp_obj_get_int(args[3]);
    lv_disp_buf_init(disp_buf, buf1, buf2, size_in_px_cnt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_buf_init_obj, 4, 4, mp_lv_disp_buf_init);

 

/*
 * lvgl extension definition for:
 * lv_disp_t *lv_disp_drv_register(lv_disp_drv_t *driver)
 */
 
STATIC mp_obj_t mp_lv_disp_drv_register(size_t n_args, const mp_obj_t *args)
{
    lv_disp_drv_t *driver = mp_write_ptr_lv_disp_drv_t(args[0]);
    lv_disp_t * res = lv_disp_drv_register(driver);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_drv_register_obj, 1, 1, mp_lv_disp_drv_register);

 

/*
 * lvgl extension definition for:
 * void lv_disp_drv_update(lv_disp_t *disp, lv_disp_drv_t *new_drv)
 */
 
STATIC mp_obj_t mp_lv_disp_drv_update(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_disp_drv_t *new_drv = mp_write_ptr_lv_disp_drv_t(args[1]);
    lv_disp_drv_update(disp, new_drv);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_drv_update_obj, 2, 2, mp_lv_disp_drv_update);

 

/*
 * lvgl extension definition for:
 * void lv_disp_remove(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_remove(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_disp_remove(disp);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_remove_obj, 1, 1, mp_lv_disp_remove);

 

/*
 * lvgl extension definition for:
 * void lv_disp_set_default(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_set_default(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_disp_set_default(disp);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_set_default_obj, 1, 1, mp_lv_disp_set_default);

 

/*
 * lvgl extension definition for:
 * lv_disp_t *lv_disp_get_default(void)
 */
 
STATIC mp_obj_t mp_lv_disp_get_default(size_t n_args, const mp_obj_t *args)
{
    
    lv_disp_t * res = lv_disp_get_default();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_get_default_obj, 0, 0, mp_lv_disp_get_default);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_disp_get_hor_res(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_get_hor_res(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_coord_t res = lv_disp_get_hor_res(disp);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_get_hor_res_obj, 1, 1, mp_lv_disp_get_hor_res);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_disp_get_ver_res(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_get_ver_res(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_coord_t res = lv_disp_get_ver_res(disp);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_get_ver_res_obj, 1, 1, mp_lv_disp_get_ver_res);

 

/*
 * lvgl extension definition for:
 * bool lv_disp_get_antialiasing(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_get_antialiasing(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    bool res = lv_disp_get_antialiasing(disp);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_get_antialiasing_obj, 1, 1, mp_lv_disp_get_antialiasing);

 

/*
 * lvgl extension definition for:
 * void lv_disp_flush_ready(lv_disp_drv_t *disp_drv)
 */
 
STATIC mp_obj_t mp_lv_disp_flush_ready(size_t n_args, const mp_obj_t *args)
{
    lv_disp_drv_t *disp_drv = mp_write_ptr_lv_disp_drv_t(args[0]);
    lv_disp_flush_ready(disp_drv);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_flush_ready_obj, 1, 1, mp_lv_disp_flush_ready);

 

/*
 * lvgl extension definition for:
 * lv_disp_t *lv_disp_get_next(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_get_next(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_disp_t * res = lv_disp_get_next(disp);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_get_next_obj, 1, 1, mp_lv_disp_get_next);

 

/*
 * lvgl extension definition for:
 * lv_disp_buf_t *lv_disp_get_buf(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_get_buf(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_disp_buf_t * res = lv_disp_get_buf(disp);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_get_buf_obj, 1, 1, mp_lv_disp_get_buf);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_disp_get_inv_buf_size(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_get_inv_buf_size(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    uint16_t res = lv_disp_get_inv_buf_size(disp);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_get_inv_buf_size_obj, 1, 1, mp_lv_disp_get_inv_buf_size);

 

/*
 * lvgl extension definition for:
 * void lv_disp_pop_from_inv_buf(lv_disp_t *disp, uint16_t num)
 */
 
STATIC mp_obj_t mp_lv_disp_pop_from_inv_buf(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    uint16_t num = (uint16_t)mp_obj_get_int(args[1]);
    lv_disp_pop_from_inv_buf(disp, num);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_pop_from_inv_buf_obj, 2, 2, mp_lv_disp_pop_from_inv_buf);

 

/*
 * lvgl extension definition for:
 * bool lv_disp_is_double_buf(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_is_double_buf(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    bool res = lv_disp_is_double_buf(disp);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_is_double_buf_obj, 1, 1, mp_lv_disp_is_double_buf);

 

/*
 * lvgl extension definition for:
 * bool lv_disp_is_true_double_buf(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_is_true_double_buf(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    bool res = lv_disp_is_true_double_buf(disp);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_is_true_double_buf_obj, 1, 1, mp_lv_disp_is_true_double_buf);

 
STATIC bool read_cb_callback(struct _lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
STATIC void feedback_cb_callback(struct _lv_indev_drv_t *, uint8_t);

/*
 * Struct lv_indev_drv_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_indev_drv_t_type();

STATIC inline lv_indev_drv_t* mp_write_ptr_lv_indev_drv_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_indev_drv_t_type()));
    return (lv_indev_drv_t*)self->data;
}

#define mp_write_lv_indev_drv_t(struct_obj) *mp_write_ptr_lv_indev_drv_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_indev_drv_t(lv_indev_drv_t *field)
{
    return lv_to_mp_struct(get_mp_lv_indev_drv_t_type(), field);
}

#define mp_read_lv_indev_drv_t(field) mp_read_ptr_lv_indev_drv_t(copy_buffer(&field, sizeof(lv_indev_drv_t)))
#define mp_read_byref_lv_indev_drv_t(field) mp_read_ptr_lv_indev_drv_t(&field)

STATIC void mp_lv_indev_drv_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_indev_drv_t *data = (lv_indev_drv_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_type: dest[0] = mp_obj_new_int_from_uint(data->type); break; // converting from lv_indev_type_t;
            case MP_QSTR_read_cb: dest[0] = ptr_to_mp((void*)data->read_cb); break; // converting from bool (*)(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
            case MP_QSTR_feedback_cb: dest[0] = ptr_to_mp((void*)data->feedback_cb); break; // converting from void (*)(lv_indev_drv_t *, uint8_t);
            case MP_QSTR_user_data: dest[0] = ptr_to_mp(data->user_data); break; // converting from lv_indev_drv_user_data_t;
            case MP_QSTR_disp: dest[0] = ptr_to_mp((void*)data->disp); break; // converting from lv_disp_t *;
            case MP_QSTR_read_task: dest[0] = ptr_to_mp((void*)data->read_task); break; // converting from lv_task_t *;
            case MP_QSTR_drag_limit: dest[0] = mp_obj_new_int_from_uint(data->drag_limit); break; // converting from uint8_t;
            case MP_QSTR_drag_throw: dest[0] = mp_obj_new_int_from_uint(data->drag_throw); break; // converting from uint8_t;
            case MP_QSTR_long_press_time: dest[0] = mp_obj_new_int_from_uint(data->long_press_time); break; // converting from uint16_t;
            case MP_QSTR_long_press_rep_time: dest[0] = mp_obj_new_int_from_uint(data->long_press_rep_time); break; // converting from uint16_t;
            default: field_not_found(MP_QSTR_lv_indev_drv_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_type: data->type = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to lv_indev_type_t;
                case MP_QSTR_read_cb: data->read_cb = (void*)mp_lv_callback(dest[1], read_cb_callback ,MP_QSTR_read_cb, &data->user_data); break; // converting to bool (*)(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
                case MP_QSTR_feedback_cb: data->feedback_cb = (void*)mp_lv_callback(dest[1], feedback_cb_callback ,MP_QSTR_feedback_cb, &data->user_data); break; // converting to void (*)(lv_indev_drv_t *, uint8_t);
                case MP_QSTR_user_data: data->user_data = mp_to_ptr(dest[1]); break; // converting to lv_indev_drv_user_data_t;
                case MP_QSTR_disp: data->disp = (void*)mp_to_ptr(dest[1]); break; // converting to lv_disp_t *;
                case MP_QSTR_read_task: data->read_task = (void*)mp_to_ptr(dest[1]); break; // converting to lv_task_t *;
                case MP_QSTR_drag_limit: data->drag_limit = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_drag_throw: data->drag_throw = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_long_press_time: data->long_press_time = (uint16_t)mp_obj_get_int(dest[1]); break; // converting to uint16_t;
                case MP_QSTR_long_press_rep_time: data->long_press_rep_time = (uint16_t)mp_obj_get_int(dest[1]); break; // converting to uint16_t;
                default: field_not_found(MP_QSTR_lv_indev_drv_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_indev_drv_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_indev_drv_t");
}

STATIC const mp_rom_map_elem_t mp_lv_indev_drv_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_indev_drv_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_indev_drv_t_locals_dict, mp_lv_indev_drv_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_indev_drv_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_indev_drv_t,
    .print = mp_lv_indev_drv_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_indev_drv_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_indev_drv_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_indev_drv_t_type()
{
    return &mp_lv_indev_drv_t_type;
}
    

/*
 * lvgl extension definition for:
 * void lv_indev_drv_init(lv_indev_drv_t *driver)
 */
 
STATIC mp_obj_t mp_lv_indev_drv_init(size_t n_args, const mp_obj_t *args)
{
    lv_indev_drv_t *driver = mp_to_ptr(args[0]);
    lv_indev_drv_init(driver);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_drv_init_obj, 1, 1, mp_lv_indev_drv_init);

 
typedef typeof( ((lv_indev_proc_t*)(0))->types ) lv_indev_proc_types_t;
typedef typeof( ((lv_indev_proc_types_t*)(0))->pointer ) lv_indev_proc_types_pointer_t;

/*
 * Struct lv_indev_proc_types_pointer_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_indev_proc_types_pointer_t_type();

STATIC inline lv_indev_proc_types_pointer_t* mp_write_ptr_lv_indev_proc_types_pointer_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_indev_proc_types_pointer_t_type()));
    return (lv_indev_proc_types_pointer_t*)self->data;
}

#define mp_write_lv_indev_proc_types_pointer_t(struct_obj) *mp_write_ptr_lv_indev_proc_types_pointer_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_indev_proc_types_pointer_t(lv_indev_proc_types_pointer_t *field)
{
    return lv_to_mp_struct(get_mp_lv_indev_proc_types_pointer_t_type(), field);
}

#define mp_read_lv_indev_proc_types_pointer_t(field) mp_read_ptr_lv_indev_proc_types_pointer_t(copy_buffer(&field, sizeof(lv_indev_proc_types_pointer_t)))
#define mp_read_byref_lv_indev_proc_types_pointer_t(field) mp_read_ptr_lv_indev_proc_types_pointer_t(&field)

STATIC void mp_lv_indev_proc_types_pointer_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_indev_proc_types_pointer_t *data = (lv_indev_proc_types_pointer_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_act_point: dest[0] = mp_read_byref_lv_point_t(data->act_point); break; // converting from lv_point_t;
            case MP_QSTR_last_point: dest[0] = mp_read_byref_lv_point_t(data->last_point); break; // converting from lv_point_t;
            case MP_QSTR_vect: dest[0] = mp_read_byref_lv_point_t(data->vect); break; // converting from lv_point_t;
            case MP_QSTR_drag_sum: dest[0] = mp_read_byref_lv_point_t(data->drag_sum); break; // converting from lv_point_t;
            case MP_QSTR_drag_throw_vect: dest[0] = mp_read_byref_lv_point_t(data->drag_throw_vect); break; // converting from lv_point_t;
            case MP_QSTR_act_obj: dest[0] = lv_to_mp((void*)data->act_obj); break; // converting from lv_obj_t *;
            case MP_QSTR_last_obj: dest[0] = lv_to_mp((void*)data->last_obj); break; // converting from lv_obj_t *;
            case MP_QSTR_last_pressed: dest[0] = lv_to_mp((void*)data->last_pressed); break; // converting from lv_obj_t *;
            case MP_QSTR_drag_limit_out: dest[0] = mp_obj_new_int_from_uint(data->drag_limit_out); break; // converting from uint8_t;
            case MP_QSTR_drag_in_prog: dest[0] = mp_obj_new_int_from_uint(data->drag_in_prog); break; // converting from uint8_t;
            default: field_not_found(MP_QSTR_lv_indev_proc_types_pointer_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_act_point: data->act_point = mp_write_lv_point_t(dest[1]); break; // converting to lv_point_t;
                case MP_QSTR_last_point: data->last_point = mp_write_lv_point_t(dest[1]); break; // converting to lv_point_t;
                case MP_QSTR_vect: data->vect = mp_write_lv_point_t(dest[1]); break; // converting to lv_point_t;
                case MP_QSTR_drag_sum: data->drag_sum = mp_write_lv_point_t(dest[1]); break; // converting to lv_point_t;
                case MP_QSTR_drag_throw_vect: data->drag_throw_vect = mp_write_lv_point_t(dest[1]); break; // converting to lv_point_t;
                case MP_QSTR_act_obj: data->act_obj = (void*)mp_to_lv(dest[1]); break; // converting to lv_obj_t *;
                case MP_QSTR_last_obj: data->last_obj = (void*)mp_to_lv(dest[1]); break; // converting to lv_obj_t *;
                case MP_QSTR_last_pressed: data->last_pressed = (void*)mp_to_lv(dest[1]); break; // converting to lv_obj_t *;
                case MP_QSTR_drag_limit_out: data->drag_limit_out = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_drag_in_prog: data->drag_in_prog = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                default: field_not_found(MP_QSTR_lv_indev_proc_types_pointer_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_indev_proc_types_pointer_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_indev_proc_types_pointer_t");
}

STATIC const mp_rom_map_elem_t mp_lv_indev_proc_types_pointer_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_indev_proc_types_pointer_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_indev_proc_types_pointer_t_locals_dict, mp_lv_indev_proc_types_pointer_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_indev_proc_types_pointer_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_indev_proc_types_pointer_t,
    .print = mp_lv_indev_proc_types_pointer_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_indev_proc_types_pointer_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_indev_proc_types_pointer_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_indev_proc_types_pointer_t_type()
{
    return &mp_lv_indev_proc_types_pointer_t_type;
}
    
typedef typeof( ((lv_indev_proc_types_t*)(0))->keypad ) lv_indev_proc_types_keypad_t;

/*
 * Struct lv_indev_proc_types_keypad_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_indev_proc_types_keypad_t_type();

STATIC inline lv_indev_proc_types_keypad_t* mp_write_ptr_lv_indev_proc_types_keypad_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_indev_proc_types_keypad_t_type()));
    return (lv_indev_proc_types_keypad_t*)self->data;
}

#define mp_write_lv_indev_proc_types_keypad_t(struct_obj) *mp_write_ptr_lv_indev_proc_types_keypad_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_indev_proc_types_keypad_t(lv_indev_proc_types_keypad_t *field)
{
    return lv_to_mp_struct(get_mp_lv_indev_proc_types_keypad_t_type(), field);
}

#define mp_read_lv_indev_proc_types_keypad_t(field) mp_read_ptr_lv_indev_proc_types_keypad_t(copy_buffer(&field, sizeof(lv_indev_proc_types_keypad_t)))
#define mp_read_byref_lv_indev_proc_types_keypad_t(field) mp_read_ptr_lv_indev_proc_types_keypad_t(&field)

STATIC void mp_lv_indev_proc_types_keypad_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_indev_proc_types_keypad_t *data = (lv_indev_proc_types_keypad_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_last_state: dest[0] = mp_obj_new_int_from_uint(data->last_state); break; // converting from lv_indev_state_t;
            case MP_QSTR_last_key: dest[0] = mp_obj_new_int_from_uint(data->last_key); break; // converting from uint32_t;
            default: field_not_found(MP_QSTR_lv_indev_proc_types_keypad_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_last_state: data->last_state = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to lv_indev_state_t;
                case MP_QSTR_last_key: data->last_key = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                default: field_not_found(MP_QSTR_lv_indev_proc_types_keypad_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_indev_proc_types_keypad_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_indev_proc_types_keypad_t");
}

STATIC const mp_rom_map_elem_t mp_lv_indev_proc_types_keypad_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_indev_proc_types_keypad_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_indev_proc_types_keypad_t_locals_dict, mp_lv_indev_proc_types_keypad_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_indev_proc_types_keypad_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_indev_proc_types_keypad_t,
    .print = mp_lv_indev_proc_types_keypad_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_indev_proc_types_keypad_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_indev_proc_types_keypad_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_indev_proc_types_keypad_t_type()
{
    return &mp_lv_indev_proc_types_keypad_t_type;
}
    

/*
 * Struct lv_indev_proc_types_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_indev_proc_types_t_type();

STATIC inline lv_indev_proc_types_t* mp_write_ptr_lv_indev_proc_types_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_indev_proc_types_t_type()));
    return (lv_indev_proc_types_t*)self->data;
}

#define mp_write_lv_indev_proc_types_t(struct_obj) *mp_write_ptr_lv_indev_proc_types_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_indev_proc_types_t(lv_indev_proc_types_t *field)
{
    return lv_to_mp_struct(get_mp_lv_indev_proc_types_t_type(), field);
}

#define mp_read_lv_indev_proc_types_t(field) mp_read_ptr_lv_indev_proc_types_t(copy_buffer(&field, sizeof(lv_indev_proc_types_t)))
#define mp_read_byref_lv_indev_proc_types_t(field) mp_read_ptr_lv_indev_proc_types_t(&field)

STATIC void mp_lv_indev_proc_types_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_indev_proc_types_t *data = (lv_indev_proc_types_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_pointer: dest[0] = mp_read_byref_lv_indev_proc_types_pointer_t(data->pointer); break; // converting from lv_indev_proc_types_pointer_t;
            case MP_QSTR_keypad: dest[0] = mp_read_byref_lv_indev_proc_types_keypad_t(data->keypad); break; // converting from lv_indev_proc_types_keypad_t;
            default: field_not_found(MP_QSTR_lv_indev_proc_types_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_pointer: data->pointer = mp_write_lv_indev_proc_types_pointer_t(dest[1]); break; // converting to lv_indev_proc_types_pointer_t;
                case MP_QSTR_keypad: data->keypad = mp_write_lv_indev_proc_types_keypad_t(dest[1]); break; // converting to lv_indev_proc_types_keypad_t;
                default: field_not_found(MP_QSTR_lv_indev_proc_types_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_indev_proc_types_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_indev_proc_types_t");
}

STATIC const mp_rom_map_elem_t mp_lv_indev_proc_types_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_indev_proc_types_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_indev_proc_types_t_locals_dict, mp_lv_indev_proc_types_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_indev_proc_types_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_indev_proc_types_t,
    .print = mp_lv_indev_proc_types_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_indev_proc_types_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_indev_proc_types_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_indev_proc_types_t_type()
{
    return &mp_lv_indev_proc_types_t_type;
}
    

/*
 * Struct lv_indev_proc_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_indev_proc_t_type();

STATIC inline lv_indev_proc_t* mp_write_ptr_lv_indev_proc_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_indev_proc_t_type()));
    return (lv_indev_proc_t*)self->data;
}

#define mp_write_lv_indev_proc_t(struct_obj) *mp_write_ptr_lv_indev_proc_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_indev_proc_t(lv_indev_proc_t *field)
{
    return lv_to_mp_struct(get_mp_lv_indev_proc_t_type(), field);
}

#define mp_read_lv_indev_proc_t(field) mp_read_ptr_lv_indev_proc_t(copy_buffer(&field, sizeof(lv_indev_proc_t)))
#define mp_read_byref_lv_indev_proc_t(field) mp_read_ptr_lv_indev_proc_t(&field)

STATIC void mp_lv_indev_proc_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_indev_proc_t *data = (lv_indev_proc_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_state: dest[0] = mp_obj_new_int_from_uint(data->state); break; // converting from lv_indev_state_t;
            case MP_QSTR_types: dest[0] = mp_read_byref_lv_indev_proc_types_t(data->types); break; // converting from lv_indev_proc_types_t;
            case MP_QSTR_pr_timestamp: dest[0] = mp_obj_new_int_from_uint(data->pr_timestamp); break; // converting from uint32_t;
            case MP_QSTR_longpr_rep_timestamp: dest[0] = mp_obj_new_int_from_uint(data->longpr_rep_timestamp); break; // converting from uint32_t;
            case MP_QSTR_long_pr_sent: dest[0] = mp_obj_new_int_from_uint(data->long_pr_sent); break; // converting from uint8_t;
            case MP_QSTR_reset_query: dest[0] = mp_obj_new_int_from_uint(data->reset_query); break; // converting from uint8_t;
            case MP_QSTR_disabled: dest[0] = mp_obj_new_int_from_uint(data->disabled); break; // converting from uint8_t;
            case MP_QSTR_wait_until_release: dest[0] = mp_obj_new_int_from_uint(data->wait_until_release); break; // converting from uint8_t;
            default: field_not_found(MP_QSTR_lv_indev_proc_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_state: data->state = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to lv_indev_state_t;
                case MP_QSTR_types: data->types = mp_write_lv_indev_proc_types_t(dest[1]); break; // converting to lv_indev_proc_types_t;
                case MP_QSTR_pr_timestamp: data->pr_timestamp = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_longpr_rep_timestamp: data->longpr_rep_timestamp = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_long_pr_sent: data->long_pr_sent = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_reset_query: data->reset_query = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_disabled: data->disabled = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_wait_until_release: data->wait_until_release = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                default: field_not_found(MP_QSTR_lv_indev_proc_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_indev_proc_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_indev_proc_t");
}

STATIC const mp_rom_map_elem_t mp_lv_indev_proc_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_indev_proc_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_indev_proc_t_locals_dict, mp_lv_indev_proc_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_indev_proc_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_indev_proc_t,
    .print = mp_lv_indev_proc_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_indev_proc_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_indev_proc_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_indev_proc_t_type()
{
    return &mp_lv_indev_proc_t_type;
}
    
STATIC void style_mod_cb_callback(struct _lv_group_t *, lv_style_t *);
STATIC void style_mod_edit_cb_callback(struct _lv_group_t *, lv_style_t *);
STATIC void focus_cb_callback(struct _lv_group_t *);

/*
 * Struct lv_group_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_group_t_type();

STATIC inline lv_group_t* mp_write_ptr_lv_group_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_group_t_type()));
    return (lv_group_t*)self->data;
}

#define mp_write_lv_group_t(struct_obj) *mp_write_ptr_lv_group_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_group_t(lv_group_t *field)
{
    return lv_to_mp_struct(get_mp_lv_group_t_type(), field);
}

#define mp_read_lv_group_t(field) mp_read_ptr_lv_group_t(copy_buffer(&field, sizeof(lv_group_t)))
#define mp_read_byref_lv_group_t(field) mp_read_ptr_lv_group_t(&field)

STATIC void mp_lv_group_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_group_t *data = (lv_group_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_obj_ll: dest[0] = mp_read_byref_lv_ll_t(data->obj_ll); break; // converting from lv_ll_t;
            case MP_QSTR_obj_focus: dest[0] = ptr_to_mp((void*)data->obj_focus); break; // converting from lv_obj_t **;
            case MP_QSTR_style_mod_cb: dest[0] = ptr_to_mp(data->style_mod_cb); break; // converting from lv_group_style_mod_cb_t;
            case MP_QSTR_style_mod_edit_cb: dest[0] = ptr_to_mp(data->style_mod_edit_cb); break; // converting from lv_group_style_mod_cb_t;
            case MP_QSTR_focus_cb: dest[0] = ptr_to_mp(data->focus_cb); break; // converting from lv_group_focus_cb_t;
            case MP_QSTR_style_tmp: dest[0] = mp_read_byref_lv_style_t(data->style_tmp); break; // converting from lv_style_t;
            case MP_QSTR_user_data: dest[0] = ptr_to_mp(data->user_data); break; // converting from lv_group_user_data_t;
            case MP_QSTR_frozen: dest[0] = mp_obj_new_int_from_uint(data->frozen); break; // converting from uint8_t;
            case MP_QSTR_editing: dest[0] = mp_obj_new_int_from_uint(data->editing); break; // converting from uint8_t;
            case MP_QSTR_click_focus: dest[0] = mp_obj_new_int_from_uint(data->click_focus); break; // converting from uint8_t;
            case MP_QSTR_refocus_policy: dest[0] = mp_obj_new_int_from_uint(data->refocus_policy); break; // converting from uint8_t;
            case MP_QSTR_wrap: dest[0] = mp_obj_new_int_from_uint(data->wrap); break; // converting from uint8_t;
            default: field_not_found(MP_QSTR_lv_group_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_obj_ll: data->obj_ll = mp_write_lv_ll_t(dest[1]); break; // converting to lv_ll_t;
                case MP_QSTR_obj_focus: data->obj_focus = (void*)mp_to_ptr(dest[1]); break; // converting to lv_obj_t **;
                case MP_QSTR_style_mod_cb: data->style_mod_cb = mp_lv_callback(dest[1], style_mod_cb_callback ,MP_QSTR_style_mod_cb, &data->user_data); break; // converting to lv_group_style_mod_cb_t;
                case MP_QSTR_style_mod_edit_cb: data->style_mod_edit_cb = mp_lv_callback(dest[1], style_mod_edit_cb_callback ,MP_QSTR_style_mod_edit_cb, &data->user_data); break; // converting to lv_group_style_mod_cb_t;
                case MP_QSTR_focus_cb: data->focus_cb = mp_lv_callback(dest[1], focus_cb_callback ,MP_QSTR_focus_cb, &data->user_data); break; // converting to lv_group_focus_cb_t;
                case MP_QSTR_style_tmp: data->style_tmp = mp_write_lv_style_t(dest[1]); break; // converting to lv_style_t;
                case MP_QSTR_user_data: data->user_data = mp_to_ptr(dest[1]); break; // converting to lv_group_user_data_t;
                case MP_QSTR_frozen: data->frozen = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_editing: data->editing = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_click_focus: data->click_focus = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_refocus_policy: data->refocus_policy = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_wrap: data->wrap = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                default: field_not_found(MP_QSTR_lv_group_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_group_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_group_t");
}

STATIC const mp_rom_map_elem_t mp_lv_group_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_group_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_group_t_locals_dict, mp_lv_group_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_group_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_group_t,
    .print = mp_lv_group_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_group_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_group_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_group_t_type()
{
    return &mp_lv_group_t_type;
}
    

/*
 * Struct lv_indev_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_indev_t_type();

STATIC inline lv_indev_t* mp_write_ptr_lv_indev_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_indev_t_type()));
    return (lv_indev_t*)self->data;
}

#define mp_write_lv_indev_t(struct_obj) *mp_write_ptr_lv_indev_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_indev_t(lv_indev_t *field)
{
    return lv_to_mp_struct(get_mp_lv_indev_t_type(), field);
}

#define mp_read_lv_indev_t(field) mp_read_ptr_lv_indev_t(copy_buffer(&field, sizeof(lv_indev_t)))
#define mp_read_byref_lv_indev_t(field) mp_read_ptr_lv_indev_t(&field)

STATIC void mp_lv_indev_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_indev_t *data = (lv_indev_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_driver: dest[0] = mp_read_byref_lv_indev_drv_t(data->driver); break; // converting from lv_indev_drv_t;
            case MP_QSTR_proc: dest[0] = mp_read_byref_lv_indev_proc_t(data->proc); break; // converting from lv_indev_proc_t;
            case MP_QSTR_cursor: dest[0] = lv_to_mp((void*)data->cursor); break; // converting from lv_obj_t *;
            case MP_QSTR_group: dest[0] = ptr_to_mp((void*)data->group); break; // converting from lv_group_t *;
            case MP_QSTR_btn_points: dest[0] = ptr_to_mp((void*)data->btn_points); break; // converting from lv_point_t *;
            default: field_not_found(MP_QSTR_lv_indev_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_driver: data->driver = mp_write_lv_indev_drv_t(dest[1]); break; // converting to lv_indev_drv_t;
                case MP_QSTR_proc: data->proc = mp_write_lv_indev_proc_t(dest[1]); break; // converting to lv_indev_proc_t;
                case MP_QSTR_cursor: data->cursor = (void*)mp_to_lv(dest[1]); break; // converting to lv_obj_t *;
                case MP_QSTR_group: data->group = (void*)mp_to_ptr(dest[1]); break; // converting to lv_group_t *;
                case MP_QSTR_btn_points: data->btn_points = (void*)mp_to_ptr(dest[1]); break; // converting to lv_point_t *;
                default: field_not_found(MP_QSTR_lv_indev_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_indev_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_indev_t");
}

STATIC const mp_rom_map_elem_t mp_lv_indev_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_indev_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_indev_t_locals_dict, mp_lv_indev_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_indev_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_indev_t,
    .print = mp_lv_indev_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_indev_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_indev_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_indev_t_type()
{
    return &mp_lv_indev_t_type;
}
    

/*
 * lvgl extension definition for:
 * lv_indev_t *lv_indev_drv_register(lv_indev_drv_t *driver)
 */
 
STATIC mp_obj_t mp_lv_indev_drv_register(size_t n_args, const mp_obj_t *args)
{
    lv_indev_drv_t *driver = mp_to_ptr(args[0]);
    lv_indev_t * res = lv_indev_drv_register(driver);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_drv_register_obj, 1, 1, mp_lv_indev_drv_register);

 

/*
 * lvgl extension definition for:
 * void lv_indev_drv_update(lv_indev_t *indev, lv_indev_drv_t *new_drv)
 */
 
STATIC mp_obj_t mp_lv_indev_drv_update(size_t n_args, const mp_obj_t *args)
{
    lv_indev_t *indev = mp_to_ptr(args[0]);
    lv_indev_drv_t *new_drv = mp_to_ptr(args[1]);
    lv_indev_drv_update(indev, new_drv);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_drv_update_obj, 2, 2, mp_lv_indev_drv_update);

 

/*
 * lvgl extension definition for:
 * lv_indev_t *lv_indev_get_next(lv_indev_t *indev)
 */
 
STATIC mp_obj_t mp_lv_indev_get_next(size_t n_args, const mp_obj_t *args)
{
    lv_indev_t *indev = mp_to_ptr(args[0]);
    lv_indev_t * res = lv_indev_get_next(indev);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_get_next_obj, 1, 1, mp_lv_indev_get_next);

 

/*
 * Struct lv_indev_data_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_indev_data_t_type();

STATIC inline lv_indev_data_t* mp_write_ptr_lv_indev_data_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_indev_data_t_type()));
    return (lv_indev_data_t*)self->data;
}

#define mp_write_lv_indev_data_t(struct_obj) *mp_write_ptr_lv_indev_data_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_indev_data_t(lv_indev_data_t *field)
{
    return lv_to_mp_struct(get_mp_lv_indev_data_t_type(), field);
}

#define mp_read_lv_indev_data_t(field) mp_read_ptr_lv_indev_data_t(copy_buffer(&field, sizeof(lv_indev_data_t)))
#define mp_read_byref_lv_indev_data_t(field) mp_read_ptr_lv_indev_data_t(&field)

STATIC void mp_lv_indev_data_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_indev_data_t *data = (lv_indev_data_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_point: dest[0] = mp_read_byref_lv_point_t(data->point); break; // converting from lv_point_t;
            case MP_QSTR_key: dest[0] = mp_obj_new_int_from_uint(data->key); break; // converting from uint32_t;
            case MP_QSTR_btn_id: dest[0] = mp_obj_new_int_from_uint(data->btn_id); break; // converting from uint32_t;
            case MP_QSTR_enc_diff: dest[0] = mp_obj_new_int(data->enc_diff); break; // converting from int16_t;
            case MP_QSTR_state: dest[0] = mp_obj_new_int_from_uint(data->state); break; // converting from lv_indev_state_t;
            default: field_not_found(MP_QSTR_lv_indev_data_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_point: data->point = mp_write_lv_point_t(dest[1]); break; // converting to lv_point_t;
                case MP_QSTR_key: data->key = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_btn_id: data->btn_id = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                case MP_QSTR_enc_diff: data->enc_diff = (int16_t)mp_obj_get_int(dest[1]); break; // converting to int16_t;
                case MP_QSTR_state: data->state = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to lv_indev_state_t;
                default: field_not_found(MP_QSTR_lv_indev_data_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_indev_data_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_indev_data_t");
}

STATIC const mp_rom_map_elem_t mp_lv_indev_data_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_indev_data_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_indev_data_t_locals_dict, mp_lv_indev_data_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_indev_data_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_indev_data_t,
    .print = mp_lv_indev_data_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_indev_data_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_indev_data_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_indev_data_t_type()
{
    return &mp_lv_indev_data_t_type;
}
    

/*
 * lvgl extension definition for:
 * bool lv_indev_read(lv_indev_t *indev, lv_indev_data_t *data)
 */
 
STATIC mp_obj_t mp_lv_indev_read(size_t n_args, const mp_obj_t *args)
{
    lv_indev_t *indev = mp_to_ptr(args[0]);
    lv_indev_data_t *data = mp_to_ptr(args[1]);
    bool res = lv_indev_read(indev, data);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_read_obj, 2, 2, mp_lv_indev_read);

 

/*
 * lvgl extension definition for:
 * void lv_tick_inc(uint32_t tick_period)
 */
 
STATIC mp_obj_t mp_lv_tick_inc(size_t n_args, const mp_obj_t *args)
{
    uint32_t tick_period = (uint32_t)mp_obj_get_int(args[0]);
    lv_tick_inc(tick_period);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tick_inc_obj, 1, 1, mp_lv_tick_inc);

 

/*
 * lvgl extension definition for:
 * uint32_t lv_tick_get(void)
 */
 
STATIC mp_obj_t mp_lv_tick_get(size_t n_args, const mp_obj_t *args)
{
    
    uint32_t res = lv_tick_get();
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tick_get_obj, 0, 0, mp_lv_tick_get);

 

/*
 * lvgl extension definition for:
 * uint32_t lv_tick_elaps(uint32_t prev_tick)
 */
 
STATIC mp_obj_t mp_lv_tick_elaps(size_t n_args, const mp_obj_t *args)
{
    uint32_t prev_tick = (uint32_t)mp_obj_get_int(args[0]);
    uint32_t res = lv_tick_elaps(prev_tick);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_tick_elaps_obj, 1, 1, mp_lv_tick_elaps);

 

/*
 * lvgl extension definition for:
 * void lv_font_init(void)
 */
 
STATIC mp_obj_t mp_lv_font_init(size_t n_args, const mp_obj_t *args)
{
    
    lv_font_init();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_init_obj, 0, 0, mp_lv_font_init);

 

/*
 * lvgl extension definition for:
 * void lv_font_add(lv_font_t *child, lv_font_t *parent)
 */
 
STATIC mp_obj_t mp_lv_font_add(size_t n_args, const mp_obj_t *args)
{
    lv_font_t *child = mp_to_ptr(args[0]);
    lv_font_t *parent = mp_to_ptr(args[1]);
    lv_font_add(child, parent);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_add_obj, 2, 2, mp_lv_font_add);

 

/*
 * lvgl extension definition for:
 * void lv_font_remove(lv_font_t *child, lv_font_t *parent)
 */
 
STATIC mp_obj_t mp_lv_font_remove(size_t n_args, const mp_obj_t *args)
{
    lv_font_t *child = mp_to_ptr(args[0]);
    lv_font_t *parent = mp_to_ptr(args[1]);
    lv_font_remove(child, parent);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_remove_obj, 2, 2, mp_lv_font_remove);

 

/*
 * lvgl extension definition for:
 * bool lv_font_is_monospace(const lv_font_t *font_p, uint32_t letter)
 */
 
STATIC mp_obj_t mp_lv_font_is_monospace(size_t n_args, const mp_obj_t *args)
{
    const lv_font_t *font_p = mp_to_ptr(args[0]);
    uint32_t letter = (uint32_t)mp_obj_get_int(args[1]);
    bool res = lv_font_is_monospace(font_p, letter);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_is_monospace_obj, 2, 2, mp_lv_font_is_monospace);

 

/*
 * lvgl extension definition for:
 * const uint8_t *lv_font_get_bitmap(const lv_font_t *font_p, uint32_t letter)
 */
 
STATIC mp_obj_t mp_lv_font_get_bitmap(size_t n_args, const mp_obj_t *args)
{
    const lv_font_t *font_p = mp_to_ptr(args[0]);
    uint32_t letter = (uint32_t)mp_obj_get_int(args[1]);
    const uint8_t * res = lv_font_get_bitmap(font_p, letter);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_get_bitmap_obj, 2, 2, mp_lv_font_get_bitmap);

 

/*
 * lvgl extension definition for:
 * uint8_t lv_font_get_width(const lv_font_t *font_p, uint32_t letter)
 */
 
STATIC mp_obj_t mp_lv_font_get_width(size_t n_args, const mp_obj_t *args)
{
    const lv_font_t *font_p = mp_to_ptr(args[0]);
    uint32_t letter = (uint32_t)mp_obj_get_int(args[1]);
    uint8_t res = lv_font_get_width(font_p, letter);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_get_width_obj, 2, 2, mp_lv_font_get_width);

 

/*
 * lvgl extension definition for:
 * uint8_t lv_font_get_real_width(const lv_font_t *font_p, uint32_t letter)
 */
 
STATIC mp_obj_t mp_lv_font_get_real_width(size_t n_args, const mp_obj_t *args)
{
    const lv_font_t *font_p = mp_to_ptr(args[0]);
    uint32_t letter = (uint32_t)mp_obj_get_int(args[1]);
    uint8_t res = lv_font_get_real_width(font_p, letter);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_get_real_width_obj, 2, 2, mp_lv_font_get_real_width);

 

/*
 * lvgl extension definition for:
 * uint8_t lv_font_get_bpp(const lv_font_t *font, uint32_t letter)
 */
 
STATIC mp_obj_t mp_lv_font_get_bpp(size_t n_args, const mp_obj_t *args)
{
    const lv_font_t *font = mp_to_ptr(args[0]);
    uint32_t letter = (uint32_t)mp_obj_get_int(args[1]);
    uint8_t res = lv_font_get_bpp(font, letter);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_get_bpp_obj, 2, 2, mp_lv_font_get_bpp);

 

/*
 * lvgl extension definition for:
 * const uint8_t *lv_font_get_bitmap_continuous(const lv_font_t *font, uint32_t unicode_letter)
 */
 
STATIC mp_obj_t mp_lv_font_get_bitmap_continuous(size_t n_args, const mp_obj_t *args)
{
    const lv_font_t *font = mp_to_ptr(args[0]);
    uint32_t unicode_letter = (uint32_t)mp_obj_get_int(args[1]);
    const uint8_t * res = lv_font_get_bitmap_continuous(font, unicode_letter);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_get_bitmap_continuous_obj, 2, 2, mp_lv_font_get_bitmap_continuous);

 

/*
 * lvgl extension definition for:
 * const uint8_t *lv_font_get_bitmap_sparse(const lv_font_t *font, uint32_t unicode_letter)
 */
 
STATIC mp_obj_t mp_lv_font_get_bitmap_sparse(size_t n_args, const mp_obj_t *args)
{
    const lv_font_t *font = mp_to_ptr(args[0]);
    uint32_t unicode_letter = (uint32_t)mp_obj_get_int(args[1]);
    const uint8_t * res = lv_font_get_bitmap_sparse(font, unicode_letter);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_get_bitmap_sparse_obj, 2, 2, mp_lv_font_get_bitmap_sparse);

 

/*
 * lvgl extension definition for:
 * int16_t lv_font_get_width_continuous(const lv_font_t *font, uint32_t unicode_letter)
 */
 
STATIC mp_obj_t mp_lv_font_get_width_continuous(size_t n_args, const mp_obj_t *args)
{
    const lv_font_t *font = mp_to_ptr(args[0]);
    uint32_t unicode_letter = (uint32_t)mp_obj_get_int(args[1]);
    int16_t res = lv_font_get_width_continuous(font, unicode_letter);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_get_width_continuous_obj, 2, 2, mp_lv_font_get_width_continuous);

 

/*
 * lvgl extension definition for:
 * int16_t lv_font_get_width_sparse(const lv_font_t *font, uint32_t unicode_letter)
 */
 
STATIC mp_obj_t mp_lv_font_get_width_sparse(size_t n_args, const mp_obj_t *args)
{
    const lv_font_t *font = mp_to_ptr(args[0]);
    uint32_t unicode_letter = (uint32_t)mp_obj_get_int(args[1]);
    int16_t res = lv_font_get_width_sparse(font, unicode_letter);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_get_width_sparse_obj, 2, 2, mp_lv_font_get_width_sparse);

 

/*
 * lvgl extension definition for:
 * void lv_font_builtin_init(void)
 */
 
STATIC mp_obj_t mp_lv_font_builtin_init(size_t n_args, const mp_obj_t *args)
{
    
    lv_font_builtin_init();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_font_builtin_init_obj, 0, 0, mp_lv_font_builtin_init);

 

/*
 * lvgl extension definition for:
 * void lv_anim_init(void)
 */
 
STATIC mp_obj_t mp_lv_anim_init(size_t n_args, const mp_obj_t *args)
{
    
    lv_anim_init();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_anim_init_obj, 0, 0, mp_lv_anim_init);

 
STATIC void exec_cb_callback(void *, lv_anim_value_t);
STATIC lv_anim_value_t path_cb_callback(const struct _lv_anim_t *);
STATIC void ready_cb_callback(struct _lv_anim_t *);

/*
 * Struct lv_anim_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_anim_t_type();

STATIC inline lv_anim_t* mp_write_ptr_lv_anim_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_anim_t_type()));
    return (lv_anim_t*)self->data;
}

#define mp_write_lv_anim_t(struct_obj) *mp_write_ptr_lv_anim_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_anim_t(lv_anim_t *field)
{
    return lv_to_mp_struct(get_mp_lv_anim_t_type(), field);
}

#define mp_read_lv_anim_t(field) mp_read_ptr_lv_anim_t(copy_buffer(&field, sizeof(lv_anim_t)))
#define mp_read_byref_lv_anim_t(field) mp_read_ptr_lv_anim_t(&field)

STATIC void mp_lv_anim_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_anim_t *data = (lv_anim_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_var: dest[0] = ptr_to_mp((void*)data->var); break; // converting from void *;
            case MP_QSTR_exec_cb: dest[0] = ptr_to_mp(data->exec_cb); break; // converting from lv_anim_exec_cb_t;
            case MP_QSTR_path_cb: dest[0] = ptr_to_mp(data->path_cb); break; // converting from lv_anim_path_cb_t;
            case MP_QSTR_ready_cb: dest[0] = ptr_to_mp(data->ready_cb); break; // converting from lv_anim_ready_cb_t;
            case MP_QSTR_start: dest[0] = mp_obj_new_int(data->start); break; // converting from int32_t;
            case MP_QSTR_end: dest[0] = mp_obj_new_int(data->end); break; // converting from int32_t;
            case MP_QSTR_time: dest[0] = mp_obj_new_int_from_uint(data->time); break; // converting from uint16_t;
            case MP_QSTR_act_time: dest[0] = mp_obj_new_int(data->act_time); break; // converting from int16_t;
            case MP_QSTR_playback_pause: dest[0] = mp_obj_new_int_from_uint(data->playback_pause); break; // converting from uint16_t;
            case MP_QSTR_repeat_pause: dest[0] = mp_obj_new_int_from_uint(data->repeat_pause); break; // converting from uint16_t;
            case MP_QSTR_user_data: dest[0] = ptr_to_mp(data->user_data); break; // converting from lv_anim_user_data_t;
            case MP_QSTR_playback: dest[0] = mp_obj_new_int_from_uint(data->playback); break; // converting from uint8_t;
            case MP_QSTR_repeat: dest[0] = mp_obj_new_int_from_uint(data->repeat); break; // converting from uint8_t;
            case MP_QSTR_playback_now: dest[0] = mp_obj_new_int_from_uint(data->playback_now); break; // converting from uint8_t;
            case MP_QSTR_has_run: dest[0] = mp_obj_new_int_from_uint(data->has_run); break; // converting from uint32_t;
            default: field_not_found(MP_QSTR_lv_anim_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_var: data->var = (void*)mp_to_ptr(dest[1]); break; // converting to void *;
                case MP_QSTR_exec_cb: data->exec_cb = mp_lv_callback(dest[1], NULL ,MP_QSTR_exec_cb, NULL); break; // converting to lv_anim_exec_cb_t;
                case MP_QSTR_path_cb: data->path_cb = mp_lv_callback(dest[1], path_cb_callback ,MP_QSTR_path_cb, &data->user_data); break; // converting to lv_anim_path_cb_t;
                case MP_QSTR_ready_cb: data->ready_cb = mp_lv_callback(dest[1], ready_cb_callback ,MP_QSTR_ready_cb, &data->user_data); break; // converting to lv_anim_ready_cb_t;
                case MP_QSTR_start: data->start = (int32_t)mp_obj_get_int(dest[1]); break; // converting to int32_t;
                case MP_QSTR_end: data->end = (int32_t)mp_obj_get_int(dest[1]); break; // converting to int32_t;
                case MP_QSTR_time: data->time = (uint16_t)mp_obj_get_int(dest[1]); break; // converting to uint16_t;
                case MP_QSTR_act_time: data->act_time = (int16_t)mp_obj_get_int(dest[1]); break; // converting to int16_t;
                case MP_QSTR_playback_pause: data->playback_pause = (uint16_t)mp_obj_get_int(dest[1]); break; // converting to uint16_t;
                case MP_QSTR_repeat_pause: data->repeat_pause = (uint16_t)mp_obj_get_int(dest[1]); break; // converting to uint16_t;
                case MP_QSTR_user_data: data->user_data = mp_to_ptr(dest[1]); break; // converting to lv_anim_user_data_t;
                case MP_QSTR_playback: data->playback = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_repeat: data->repeat = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_playback_now: data->playback_now = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_has_run: data->has_run = (uint32_t)mp_obj_get_int(dest[1]); break; // converting to uint32_t;
                default: field_not_found(MP_QSTR_lv_anim_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_anim_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_anim_t");
}

STATIC const mp_rom_map_elem_t mp_lv_anim_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_anim_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_anim_t_locals_dict, mp_lv_anim_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_anim_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_anim_t,
    .print = mp_lv_anim_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_anim_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_anim_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_anim_t_type()
{
    return &mp_lv_anim_t_type;
}
    

/*
 * lvgl extension definition for:
 * void lv_anim_create(lv_anim_t *anim_p)
 */
 
STATIC mp_obj_t mp_lv_anim_create(size_t n_args, const mp_obj_t *args)
{
    lv_anim_t *anim_p = mp_to_ptr(args[0]);
    lv_anim_create(anim_p);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_anim_create_obj, 1, 1, mp_lv_anim_create);

 

/*
 * Function NOT generated:
 * Callback: user_data NOT FOUND! void lv_anim_exec_cb_t(void *, lv_anim_value_t)
 * bool lv_anim_del(void *var, lv_anim_exec_cb_t fp)
 */
    

/*
 * lvgl extension definition for:
 * uint16_t lv_anim_count_running(void)
 */
 
STATIC mp_obj_t mp_lv_anim_count_running(size_t n_args, const mp_obj_t *args)
{
    
    uint16_t res = lv_anim_count_running();
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_anim_count_running_obj, 0, 0, mp_lv_anim_count_running);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_anim_speed_to_time(uint16_t speed, lv_anim_value_t start, lv_anim_value_t end)
 */
 
STATIC mp_obj_t mp_lv_anim_speed_to_time(size_t n_args, const mp_obj_t *args)
{
    uint16_t speed = (uint16_t)mp_obj_get_int(args[0]);
    lv_anim_value_t start = (int16_t)mp_obj_get_int(args[1]);
    lv_anim_value_t end = (int16_t)mp_obj_get_int(args[2]);
    uint16_t res = lv_anim_speed_to_time(speed, start, end);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_anim_speed_to_time_obj, 3, 3, mp_lv_anim_speed_to_time);

 

/*
 * lvgl extension definition for:
 * lv_anim_value_t lv_anim_path_linear(const lv_anim_t *a)
 */
 
STATIC mp_obj_t mp_lv_anim_path_linear(size_t n_args, const mp_obj_t *args)
{
    const lv_anim_t *a = mp_to_ptr(args[0]);
    lv_anim_value_t res = lv_anim_path_linear(a);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_anim_path_linear_obj, 1, 1, mp_lv_anim_path_linear);

 

/*
 * lvgl extension definition for:
 * lv_anim_value_t lv_anim_path_ease_in(const lv_anim_t *a)
 */
 
STATIC mp_obj_t mp_lv_anim_path_ease_in(size_t n_args, const mp_obj_t *args)
{
    const lv_anim_t *a = mp_to_ptr(args[0]);
    lv_anim_value_t res = lv_anim_path_ease_in(a);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_anim_path_ease_in_obj, 1, 1, mp_lv_anim_path_ease_in);

 

/*
 * lvgl extension definition for:
 * lv_anim_value_t lv_anim_path_ease_out(const lv_anim_t *a)
 */
 
STATIC mp_obj_t mp_lv_anim_path_ease_out(size_t n_args, const mp_obj_t *args)
{
    const lv_anim_t *a = mp_to_ptr(args[0]);
    lv_anim_value_t res = lv_anim_path_ease_out(a);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_anim_path_ease_out_obj, 1, 1, mp_lv_anim_path_ease_out);

 

/*
 * lvgl extension definition for:
 * lv_anim_value_t lv_anim_path_ease_in_out(const lv_anim_t *a)
 */
 
STATIC mp_obj_t mp_lv_anim_path_ease_in_out(size_t n_args, const mp_obj_t *args)
{
    const lv_anim_t *a = mp_to_ptr(args[0]);
    lv_anim_value_t res = lv_anim_path_ease_in_out(a);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_anim_path_ease_in_out_obj, 1, 1, mp_lv_anim_path_ease_in_out);

 

/*
 * lvgl extension definition for:
 * lv_anim_value_t lv_anim_path_overshoot(const lv_anim_t *a)
 */
 
STATIC mp_obj_t mp_lv_anim_path_overshoot(size_t n_args, const mp_obj_t *args)
{
    const lv_anim_t *a = mp_to_ptr(args[0]);
    lv_anim_value_t res = lv_anim_path_overshoot(a);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_anim_path_overshoot_obj, 1, 1, mp_lv_anim_path_overshoot);

 

/*
 * lvgl extension definition for:
 * lv_anim_value_t lv_anim_path_bounce(const lv_anim_t *a)
 */
 
STATIC mp_obj_t mp_lv_anim_path_bounce(size_t n_args, const mp_obj_t *args)
{
    const lv_anim_t *a = mp_to_ptr(args[0]);
    lv_anim_value_t res = lv_anim_path_bounce(a);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_anim_path_bounce_obj, 1, 1, mp_lv_anim_path_bounce);

 

/*
 * lvgl extension definition for:
 * lv_anim_value_t lv_anim_path_step(const lv_anim_t *a)
 */
 
STATIC mp_obj_t mp_lv_anim_path_step(size_t n_args, const mp_obj_t *args)
{
    const lv_anim_t *a = mp_to_ptr(args[0]);
    lv_anim_value_t res = lv_anim_path_step(a);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_anim_path_step_obj, 1, 1, mp_lv_anim_path_step);

 

/*
 * lvgl extension definition for:
 * void lv_style_init(void)
 */
 
STATIC mp_obj_t mp_lv_style_init(size_t n_args, const mp_obj_t *args)
{
    
    lv_style_init();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_style_init_obj, 0, 0, mp_lv_style_init);

 

/*
 * lvgl extension definition for:
 * void lv_style_copy(lv_style_t *dest, const lv_style_t *src)
 */
 
STATIC mp_obj_t mp_lv_style_copy(size_t n_args, const mp_obj_t *args)
{
    lv_style_t *dest = mp_to_ptr(args[0]);
    const lv_style_t *src = mp_to_ptr(args[1]);
    lv_style_copy(dest, src);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_style_copy_obj, 2, 2, mp_lv_style_copy);

 

/*
 * lvgl extension definition for:
 * void lv_style_mix(const lv_style_t *start, const lv_style_t *end, lv_style_t *res, uint16_t ratio)
 */
 
STATIC mp_obj_t mp_lv_style_mix(size_t n_args, const mp_obj_t *args)
{
    const lv_style_t *start = mp_to_ptr(args[0]);
    const lv_style_t *end = mp_to_ptr(args[1]);
    lv_style_t *res = mp_to_ptr(args[2]);
    uint16_t ratio = (uint16_t)mp_obj_get_int(args[3]);
    lv_style_mix(start, end, res, ratio);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_style_mix_obj, 4, 4, mp_lv_style_mix);

 
STATIC void ready_cb_callback(struct _lv_anim_t *);

/*
 * Struct lv_style_anim_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_style_anim_t_type();

STATIC inline lv_style_anim_t* mp_write_ptr_lv_style_anim_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_style_anim_t_type()));
    return (lv_style_anim_t*)self->data;
}

#define mp_write_lv_style_anim_t(struct_obj) *mp_write_ptr_lv_style_anim_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_style_anim_t(lv_style_anim_t *field)
{
    return lv_to_mp_struct(get_mp_lv_style_anim_t_type(), field);
}

#define mp_read_lv_style_anim_t(field) mp_read_ptr_lv_style_anim_t(copy_buffer(&field, sizeof(lv_style_anim_t)))
#define mp_read_byref_lv_style_anim_t(field) mp_read_ptr_lv_style_anim_t(&field)

STATIC void mp_lv_style_anim_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_style_anim_t *data = (lv_style_anim_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_style_start: dest[0] = ptr_to_mp((void*)data->style_start); break; // converting from lv_style_t *;
            case MP_QSTR_style_end: dest[0] = ptr_to_mp((void*)data->style_end); break; // converting from lv_style_t *;
            case MP_QSTR_style_anim: dest[0] = ptr_to_mp((void*)data->style_anim); break; // converting from lv_style_t *;
            case MP_QSTR_ready_cb: dest[0] = ptr_to_mp(data->ready_cb); break; // converting from lv_anim_ready_cb_t;
            case MP_QSTR_time: dest[0] = mp_obj_new_int(data->time); break; // converting from int16_t;
            case MP_QSTR_act_time: dest[0] = mp_obj_new_int(data->act_time); break; // converting from int16_t;
            case MP_QSTR_playback_pause: dest[0] = mp_obj_new_int_from_uint(data->playback_pause); break; // converting from uint16_t;
            case MP_QSTR_repeat_pause: dest[0] = mp_obj_new_int_from_uint(data->repeat_pause); break; // converting from uint16_t;
            case MP_QSTR_user_data: dest[0] = ptr_to_mp(data->user_data); break; // converting from lv_anim_user_data_t;
            case MP_QSTR_playback: dest[0] = mp_obj_new_int_from_uint(data->playback); break; // converting from uint8_t;
            case MP_QSTR_repeat: dest[0] = mp_obj_new_int_from_uint(data->repeat); break; // converting from uint8_t;
            default: field_not_found(MP_QSTR_lv_style_anim_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_style_start: data->style_start = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_style_end: data->style_end = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_style_anim: data->style_anim = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_ready_cb: data->ready_cb = mp_lv_callback(dest[1], NULL ,MP_QSTR_ready_cb, NULL); break; // converting to lv_anim_ready_cb_t;
                case MP_QSTR_time: data->time = (int16_t)mp_obj_get_int(dest[1]); break; // converting to int16_t;
                case MP_QSTR_act_time: data->act_time = (int16_t)mp_obj_get_int(dest[1]); break; // converting to int16_t;
                case MP_QSTR_playback_pause: data->playback_pause = (uint16_t)mp_obj_get_int(dest[1]); break; // converting to uint16_t;
                case MP_QSTR_repeat_pause: data->repeat_pause = (uint16_t)mp_obj_get_int(dest[1]); break; // converting to uint16_t;
                case MP_QSTR_user_data: data->user_data = mp_to_ptr(dest[1]); break; // converting to lv_anim_user_data_t;
                case MP_QSTR_playback: data->playback = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                case MP_QSTR_repeat: data->repeat = (uint8_t)mp_obj_get_int(dest[1]); break; // converting to uint8_t;
                default: field_not_found(MP_QSTR_lv_style_anim_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_style_anim_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_style_anim_t");
}

STATIC const mp_rom_map_elem_t mp_lv_style_anim_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_style_anim_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_style_anim_t_locals_dict, mp_lv_style_anim_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_style_anim_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_style_anim_t,
    .print = mp_lv_style_anim_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_style_anim_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_style_anim_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_style_anim_t_type()
{
    return &mp_lv_style_anim_t_type;
}
    

/*
 * lvgl extension definition for:
 * void *lv_style_anim_create(lv_style_anim_t *anim)
 */
 
STATIC mp_obj_t mp_lv_style_anim_create(size_t n_args, const mp_obj_t *args)
{
    lv_style_anim_t *anim = mp_to_ptr(args[0]);
    void * res = lv_style_anim_create(anim);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_style_anim_create_obj, 1, 1, mp_lv_style_anim_create);

 

/*
 * lvgl extension definition for:
 * void lv_init(void)
 */
 
STATIC mp_obj_t mp_lv_init(size_t n_args, const mp_obj_t *args)
{
    
    lv_init();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_init_obj, 0, 0, mp_lv_init);

 

/*
 * lvgl extension definition for:
 * lv_res_t lv_event_send(lv_obj_t *obj, lv_event_t event, const void *data)
 */
 
STATIC mp_obj_t mp_lv_event_send(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_event_t event = (uint8_t)mp_obj_get_int(args[1]);
    const void *data = mp_to_ptr(args[2]);
    lv_res_t res = lv_event_send(obj, event, data);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_event_send_obj, 3, 3, mp_lv_event_send);

 

/*
 * Function NOT generated:
 * Callback argument 'lv_event_cb_t event_cb' cannot be the first argument! We assume the first argument contains the user_data
 * lv_res_t lv_event_send_func(lv_event_cb_t event_cb, lv_obj_t *obj, lv_event_t event, const void *data)
 */
    

/*
 * lvgl extension definition for:
 * const void *lv_event_get_data(void)
 */
 
STATIC mp_obj_t mp_lv_event_get_data(size_t n_args, const mp_obj_t *args)
{
    
    const void * res = lv_event_get_data();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_event_get_data_obj, 0, 0, mp_lv_event_get_data);

 

/*
 * lvgl extension definition for:
 * void lv_signal_send(lv_obj_t *obj, lv_signal_t signal, void *param)
 */
 
STATIC mp_obj_t mp_lv_signal_send(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_signal_t signal = (uint8_t)mp_obj_get_int(args[1]);
    void *param = mp_to_ptr(args[2]);
    lv_signal_send(obj, signal, param);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_signal_send_obj, 3, 3, mp_lv_signal_send);

 

/*
 * lvgl extension definition for:
 * void lv_group_init(void)
 */
 
STATIC mp_obj_t mp_lv_group_init(size_t n_args, const mp_obj_t *args)
{
    
    lv_group_init();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_init_obj, 0, 0, mp_lv_group_init);

 

/*
 * lvgl extension definition for:
 * lv_group_t *lv_group_create(void)
 */
 
STATIC mp_obj_t mp_lv_group_create(size_t n_args, const mp_obj_t *args)
{
    
    lv_group_t * res = lv_group_create();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_create_obj, 0, 0, mp_lv_group_create);

 

/*
 * lvgl extension definition for:
 * void lv_group_del(lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_group_del(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    lv_group_del(group);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_del_obj, 1, 1, mp_lv_group_del);

 

/*
 * lvgl extension definition for:
 * void lv_group_add_obj(lv_group_t *group, lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_group_add_obj(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    lv_obj_t *obj = mp_to_lv(args[1]);
    lv_group_add_obj(group, obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_add_obj_obj, 2, 2, mp_lv_group_add_obj);

 

/*
 * lvgl extension definition for:
 * void lv_group_remove_obj(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_group_remove_obj(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_group_remove_obj(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_remove_obj_obj, 1, 1, mp_lv_group_remove_obj);

 

/*
 * lvgl extension definition for:
 * void lv_group_focus_obj(lv_obj_t *obj)
 */
 
STATIC mp_obj_t mp_lv_group_focus_obj(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *obj = mp_to_lv(args[0]);
    lv_group_focus_obj(obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_focus_obj_obj, 1, 1, mp_lv_group_focus_obj);

 

/*
 * lvgl extension definition for:
 * void lv_group_focus_next(lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_group_focus_next(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    lv_group_focus_next(group);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_focus_next_obj, 1, 1, mp_lv_group_focus_next);

 

/*
 * lvgl extension definition for:
 * void lv_group_focus_prev(lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_group_focus_prev(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    lv_group_focus_prev(group);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_focus_prev_obj, 1, 1, mp_lv_group_focus_prev);

 

/*
 * lvgl extension definition for:
 * void lv_group_focus_freeze(lv_group_t *group, bool en)
 */
 
STATIC mp_obj_t mp_lv_group_focus_freeze(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_group_focus_freeze(group, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_focus_freeze_obj, 2, 2, mp_lv_group_focus_freeze);

 

/*
 * lvgl extension definition for:
 * lv_res_t lv_group_send_data(lv_group_t *group, uint32_t c)
 */
 
STATIC mp_obj_t mp_lv_group_send_data(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    uint32_t c = (uint32_t)mp_obj_get_int(args[1]);
    lv_res_t res = lv_group_send_data(group, c);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_send_data_obj, 2, 2, mp_lv_group_send_data);

 

/*
 * Callback function style_mod_cb
 * void lv_group_style_mod_cb_t(struct _lv_group_t *, lv_style_t *)
 */

STATIC void style_mod_cb_callback(lv_group_t * arg0, lv_style_t * arg1)
{
    mp_obj_t args[2];
    args[0] = ptr_to_mp((void*)arg0);
    args[1] = ptr_to_mp((void*)arg1);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_style_mod_cb)) , 2, 0, args);
    return;
}


/*
 * lvgl extension definition for:
 * void lv_group_set_style_mod_cb(lv_group_t *group, lv_group_style_mod_cb_t style_mod_cb)
 */
 
STATIC mp_obj_t mp_lv_group_set_style_mod_cb(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    lv_group_style_mod_cb_t style_mod_cb = mp_lv_callback(args[1], &style_mod_cb_callback, MP_QSTR_style_mod_cb, &group->user_data);
    lv_group_set_style_mod_cb(group, style_mod_cb);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_set_style_mod_cb_obj, 2, 2, mp_lv_group_set_style_mod_cb);

 

/*
 * Callback function style_mod_edit_cb
 * void lv_group_style_mod_cb_t(struct _lv_group_t *, lv_style_t *)
 */

STATIC void style_mod_edit_cb_callback(lv_group_t * arg0, lv_style_t * arg1)
{
    mp_obj_t args[2];
    args[0] = ptr_to_mp((void*)arg0);
    args[1] = ptr_to_mp((void*)arg1);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_style_mod_edit_cb)) , 2, 0, args);
    return;
}


/*
 * lvgl extension definition for:
 * void lv_group_set_style_mod_edit_cb(lv_group_t *group, lv_group_style_mod_cb_t style_mod_edit_cb)
 */
 
STATIC mp_obj_t mp_lv_group_set_style_mod_edit_cb(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    lv_group_style_mod_cb_t style_mod_edit_cb = mp_lv_callback(args[1], &style_mod_edit_cb_callback, MP_QSTR_style_mod_edit_cb, &group->user_data);
    lv_group_set_style_mod_edit_cb(group, style_mod_edit_cb);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_set_style_mod_edit_cb_obj, 2, 2, mp_lv_group_set_style_mod_edit_cb);

 

/*
 * Callback function focus_cb
 * void lv_group_focus_cb_t(struct _lv_group_t *)
 */

STATIC void focus_cb_callback(lv_group_t * arg0)
{
    mp_obj_t args[1];
    args[0] = ptr_to_mp((void*)arg0);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_focus_cb)) , 1, 0, args);
    return;
}


/*
 * lvgl extension definition for:
 * void lv_group_set_focus_cb(lv_group_t *group, lv_group_focus_cb_t focus_cb)
 */
 
STATIC mp_obj_t mp_lv_group_set_focus_cb(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    lv_group_focus_cb_t focus_cb = mp_lv_callback(args[1], &focus_cb_callback, MP_QSTR_focus_cb, &group->user_data);
    lv_group_set_focus_cb(group, focus_cb);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_set_focus_cb_obj, 2, 2, mp_lv_group_set_focus_cb);

 

/*
 * lvgl extension definition for:
 * void lv_group_set_refocus_policy(lv_group_t *group, lv_group_refocus_policy_t policy)
 */
 
STATIC mp_obj_t mp_lv_group_set_refocus_policy(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    lv_group_refocus_policy_t policy = (uint8_t)mp_obj_get_int(args[1]);
    lv_group_set_refocus_policy(group, policy);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_set_refocus_policy_obj, 2, 2, mp_lv_group_set_refocus_policy);

 

/*
 * lvgl extension definition for:
 * void lv_group_set_editing(lv_group_t *group, bool edit)
 */
 
STATIC mp_obj_t mp_lv_group_set_editing(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    bool edit = mp_obj_is_true(args[1]);
    lv_group_set_editing(group, edit);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_set_editing_obj, 2, 2, mp_lv_group_set_editing);

 

/*
 * lvgl extension definition for:
 * void lv_group_set_click_focus(lv_group_t *group, bool en)
 */
 
STATIC mp_obj_t mp_lv_group_set_click_focus(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_group_set_click_focus(group, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_set_click_focus_obj, 2, 2, mp_lv_group_set_click_focus);

 

/*
 * lvgl extension definition for:
 * void lv_group_set_wrap(lv_group_t *group, bool en)
 */
 
STATIC mp_obj_t mp_lv_group_set_wrap(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_group_set_wrap(group, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_set_wrap_obj, 2, 2, mp_lv_group_set_wrap);

 

/*
 * lvgl extension definition for:
 * lv_style_t *lv_group_mod_style(lv_group_t *group, const lv_style_t *style)
 */
 
STATIC mp_obj_t mp_lv_group_mod_style(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    const lv_style_t *style = mp_to_ptr(args[1]);
    lv_style_t * res = lv_group_mod_style(group, style);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_mod_style_obj, 2, 2, mp_lv_group_mod_style);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_group_get_focused(const lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_group_get_focused(size_t n_args, const mp_obj_t *args)
{
    const lv_group_t *group = mp_to_ptr(args[0]);
    lv_obj_t * res = lv_group_get_focused(group);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_get_focused_obj, 1, 1, mp_lv_group_get_focused);

 

/*
 * lvgl extension definition for:
 * lv_group_user_data_t *lv_group_get_user_data(lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_group_get_user_data(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    lv_group_user_data_t * res = lv_group_get_user_data(group);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_get_user_data_obj, 1, 1, mp_lv_group_get_user_data);

 

/*
 * lvgl extension definition for:
 * lv_group_style_mod_cb_t lv_group_get_style_mod_cb(const lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_group_get_style_mod_cb(size_t n_args, const mp_obj_t *args)
{
    const lv_group_t *group = mp_to_ptr(args[0]);
    lv_group_style_mod_cb_t res = lv_group_get_style_mod_cb(group);
    return ptr_to_mp(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_get_style_mod_cb_obj, 1, 1, mp_lv_group_get_style_mod_cb);

 

/*
 * lvgl extension definition for:
 * lv_group_style_mod_cb_t lv_group_get_style_mod_edit_cb(const lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_group_get_style_mod_edit_cb(size_t n_args, const mp_obj_t *args)
{
    const lv_group_t *group = mp_to_ptr(args[0]);
    lv_group_style_mod_cb_t res = lv_group_get_style_mod_edit_cb(group);
    return ptr_to_mp(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_get_style_mod_edit_cb_obj, 1, 1, mp_lv_group_get_style_mod_edit_cb);

 

/*
 * lvgl extension definition for:
 * lv_group_focus_cb_t lv_group_get_focus_cb(const lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_group_get_focus_cb(size_t n_args, const mp_obj_t *args)
{
    const lv_group_t *group = mp_to_ptr(args[0]);
    lv_group_focus_cb_t res = lv_group_get_focus_cb(group);
    return ptr_to_mp(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_get_focus_cb_obj, 1, 1, mp_lv_group_get_focus_cb);

 

/*
 * lvgl extension definition for:
 * bool lv_group_get_editing(const lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_group_get_editing(size_t n_args, const mp_obj_t *args)
{
    const lv_group_t *group = mp_to_ptr(args[0]);
    bool res = lv_group_get_editing(group);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_get_editing_obj, 1, 1, mp_lv_group_get_editing);

 

/*
 * lvgl extension definition for:
 * bool lv_group_get_click_focus(const lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_group_get_click_focus(size_t n_args, const mp_obj_t *args)
{
    const lv_group_t *group = mp_to_ptr(args[0]);
    bool res = lv_group_get_click_focus(group);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_get_click_focus_obj, 1, 1, mp_lv_group_get_click_focus);

 

/*
 * lvgl extension definition for:
 * bool lv_group_get_wrap(lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_group_get_wrap(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    bool res = lv_group_get_wrap(group);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_get_wrap_obj, 1, 1, mp_lv_group_get_wrap);

 

/*
 * lvgl extension definition for:
 * void lv_group_report_style_mod(lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_group_report_style_mod(size_t n_args, const mp_obj_t *args)
{
    lv_group_t *group = mp_to_ptr(args[0]);
    lv_group_report_style_mod(group);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_group_report_style_mod_obj, 1, 1, mp_lv_group_report_style_mod);

 

/*
 * lvgl extension definition for:
 * void lv_refr_init(void)
 */
 
STATIC mp_obj_t mp_lv_refr_init(size_t n_args, const mp_obj_t *args)
{
    
    lv_refr_init();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_refr_init_obj, 0, 0, mp_lv_refr_init);

 

/*
 * lvgl extension definition for:
 * void lv_refr_now(void)
 */
 
STATIC mp_obj_t mp_lv_refr_now(size_t n_args, const mp_obj_t *args)
{
    
    lv_refr_now();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_refr_now_obj, 0, 0, mp_lv_refr_now);

 

/*
 * lvgl extension definition for:
 * void lv_inv_area(lv_disp_t *disp, const lv_area_t *area_p)
 */
 
STATIC mp_obj_t mp_lv_inv_area(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    const lv_area_t *area_p = mp_to_ptr(args[1]);
    lv_inv_area(disp, area_p);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_inv_area_obj, 2, 2, mp_lv_inv_area);

 

/*
 * lvgl extension definition for:
 * lv_disp_t *lv_refr_get_disp_refreshing(void)
 */
 
STATIC mp_obj_t mp_lv_refr_get_disp_refreshing(size_t n_args, const mp_obj_t *args)
{
    
    lv_disp_t * res = lv_refr_get_disp_refreshing();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_refr_get_disp_refreshing_obj, 0, 0, mp_lv_refr_get_disp_refreshing);

 

/*
 * lvgl extension definition for:
 * void lv_disp_refr_task(lv_task_t *task)
 */
 
STATIC mp_obj_t mp_lv_disp_refr_task(size_t n_args, const mp_obj_t *args)
{
    lv_task_t *task = mp_to_ptr(args[0]);
    lv_disp_refr_task(task);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_refr_task_obj, 1, 1, mp_lv_disp_refr_task);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_disp_get_scr_act(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_get_scr_act(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_obj_t * res = lv_disp_get_scr_act(disp);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_get_scr_act_obj, 1, 1, mp_lv_disp_get_scr_act);

 

/*
 * lvgl extension definition for:
 * void lv_disp_set_scr_act(lv_obj_t *scr)
 */
 
STATIC mp_obj_t mp_lv_disp_set_scr_act(size_t n_args, const mp_obj_t *args)
{
    lv_obj_t *scr = mp_to_lv(args[0]);
    lv_disp_set_scr_act(scr);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_set_scr_act_obj, 1, 1, mp_lv_disp_set_scr_act);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_disp_get_layer_top(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_get_layer_top(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_obj_t * res = lv_disp_get_layer_top(disp);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_get_layer_top_obj, 1, 1, mp_lv_disp_get_layer_top);

 

/*
 * lvgl extension definition for:
 * lv_obj_t *lv_disp_get_layer_sys(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_get_layer_sys(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_obj_t * res = lv_disp_get_layer_sys(disp);
    return lv_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_get_layer_sys_obj, 1, 1, mp_lv_disp_get_layer_sys);

 

/*
 * lvgl extension definition for:
 * void lv_disp_assign_screen(lv_disp_t *disp, lv_obj_t *scr)
 */
 
STATIC mp_obj_t mp_lv_disp_assign_screen(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_obj_t *scr = mp_to_lv(args[1]);
    lv_disp_assign_screen(disp, scr);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_assign_screen_obj, 2, 2, mp_lv_disp_assign_screen);

 

/*
 * lvgl extension definition for:
 * lv_task_t *lv_disp_get_refr_task(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_get_refr_task(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_task_t * res = lv_disp_get_refr_task(disp);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_get_refr_task_obj, 1, 1, mp_lv_disp_get_refr_task);

 

/*
 * lvgl extension definition for:
 * uint32_t lv_disp_get_inactive_time(const lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_get_inactive_time(size_t n_args, const mp_obj_t *args)
{
    const lv_disp_t *disp = mp_to_ptr(args[0]);
    uint32_t res = lv_disp_get_inactive_time(disp);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_get_inactive_time_obj, 1, 1, mp_lv_disp_get_inactive_time);

 

/*
 * lvgl extension definition for:
 * void lv_disp_trig_activity(lv_disp_t *disp)
 */
 
STATIC mp_obj_t mp_lv_disp_trig_activity(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *disp = mp_to_ptr(args[0]);
    lv_disp_trig_activity(disp);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_disp_trig_activity_obj, 1, 1, mp_lv_disp_trig_activity);

 
typedef typeof( ((lv_theme_t*)(0))->style ) lv_theme_style_t;
typedef typeof( ((lv_theme_style_t*)(0))->btn ) lv_theme_style_btn_t;

/*
 * Struct lv_theme_style_btn_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_btn_t_type();

STATIC inline lv_theme_style_btn_t* mp_write_ptr_lv_theme_style_btn_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_btn_t_type()));
    return (lv_theme_style_btn_t*)self->data;
}

#define mp_write_lv_theme_style_btn_t(struct_obj) *mp_write_ptr_lv_theme_style_btn_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_btn_t(lv_theme_style_btn_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_btn_t_type(), field);
}

#define mp_read_lv_theme_style_btn_t(field) mp_read_ptr_lv_theme_style_btn_t(copy_buffer(&field, sizeof(lv_theme_style_btn_t)))
#define mp_read_byref_lv_theme_style_btn_t(field) mp_read_ptr_lv_theme_style_btn_t(&field)

STATIC void mp_lv_theme_style_btn_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_btn_t *data = (lv_theme_style_btn_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_rel: dest[0] = ptr_to_mp((void*)data->rel); break; // converting from lv_style_t *;
            case MP_QSTR_pr: dest[0] = ptr_to_mp((void*)data->pr); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_rel: dest[0] = ptr_to_mp((void*)data->tgl_rel); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_pr: dest[0] = ptr_to_mp((void*)data->tgl_pr); break; // converting from lv_style_t *;
            case MP_QSTR_ina: dest[0] = ptr_to_mp((void*)data->ina); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_btn_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_rel: data->rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_pr: data->pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_rel: data->tgl_rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_pr: data->tgl_pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_ina: data->ina = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_btn_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_btn_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_btn_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_btn_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_btn_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_btn_t_locals_dict, mp_lv_theme_style_btn_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_btn_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_btn_t,
    .print = mp_lv_theme_style_btn_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_btn_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_btn_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_btn_t_type()
{
    return &mp_lv_theme_style_btn_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->imgbtn ) lv_theme_style_imgbtn_t;

/*
 * Struct lv_theme_style_imgbtn_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_imgbtn_t_type();

STATIC inline lv_theme_style_imgbtn_t* mp_write_ptr_lv_theme_style_imgbtn_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_imgbtn_t_type()));
    return (lv_theme_style_imgbtn_t*)self->data;
}

#define mp_write_lv_theme_style_imgbtn_t(struct_obj) *mp_write_ptr_lv_theme_style_imgbtn_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_imgbtn_t(lv_theme_style_imgbtn_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_imgbtn_t_type(), field);
}

#define mp_read_lv_theme_style_imgbtn_t(field) mp_read_ptr_lv_theme_style_imgbtn_t(copy_buffer(&field, sizeof(lv_theme_style_imgbtn_t)))
#define mp_read_byref_lv_theme_style_imgbtn_t(field) mp_read_ptr_lv_theme_style_imgbtn_t(&field)

STATIC void mp_lv_theme_style_imgbtn_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_imgbtn_t *data = (lv_theme_style_imgbtn_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_rel: dest[0] = ptr_to_mp((void*)data->rel); break; // converting from lv_style_t *;
            case MP_QSTR_pr: dest[0] = ptr_to_mp((void*)data->pr); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_rel: dest[0] = ptr_to_mp((void*)data->tgl_rel); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_pr: dest[0] = ptr_to_mp((void*)data->tgl_pr); break; // converting from lv_style_t *;
            case MP_QSTR_ina: dest[0] = ptr_to_mp((void*)data->ina); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_imgbtn_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_rel: data->rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_pr: data->pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_rel: data->tgl_rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_pr: data->tgl_pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_ina: data->ina = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_imgbtn_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_imgbtn_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_imgbtn_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_imgbtn_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_imgbtn_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_imgbtn_t_locals_dict, mp_lv_theme_style_imgbtn_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_imgbtn_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_imgbtn_t,
    .print = mp_lv_theme_style_imgbtn_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_imgbtn_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_imgbtn_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_imgbtn_t_type()
{
    return &mp_lv_theme_style_imgbtn_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->label ) lv_theme_style_label_t;

/*
 * Struct lv_theme_style_label_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_label_t_type();

STATIC inline lv_theme_style_label_t* mp_write_ptr_lv_theme_style_label_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_label_t_type()));
    return (lv_theme_style_label_t*)self->data;
}

#define mp_write_lv_theme_style_label_t(struct_obj) *mp_write_ptr_lv_theme_style_label_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_label_t(lv_theme_style_label_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_label_t_type(), field);
}

#define mp_read_lv_theme_style_label_t(field) mp_read_ptr_lv_theme_style_label_t(copy_buffer(&field, sizeof(lv_theme_style_label_t)))
#define mp_read_byref_lv_theme_style_label_t(field) mp_read_ptr_lv_theme_style_label_t(&field)

STATIC void mp_lv_theme_style_label_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_label_t *data = (lv_theme_style_label_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_prim: dest[0] = ptr_to_mp((void*)data->prim); break; // converting from lv_style_t *;
            case MP_QSTR_sec: dest[0] = ptr_to_mp((void*)data->sec); break; // converting from lv_style_t *;
            case MP_QSTR_hint: dest[0] = ptr_to_mp((void*)data->hint); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_label_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_prim: data->prim = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_sec: data->sec = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_hint: data->hint = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_label_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_label_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_label_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_label_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_label_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_label_t_locals_dict, mp_lv_theme_style_label_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_label_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_label_t,
    .print = mp_lv_theme_style_label_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_label_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_label_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_label_t_type()
{
    return &mp_lv_theme_style_label_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->img ) lv_theme_style_img_t;

/*
 * Struct lv_theme_style_img_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_img_t_type();

STATIC inline lv_theme_style_img_t* mp_write_ptr_lv_theme_style_img_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_img_t_type()));
    return (lv_theme_style_img_t*)self->data;
}

#define mp_write_lv_theme_style_img_t(struct_obj) *mp_write_ptr_lv_theme_style_img_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_img_t(lv_theme_style_img_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_img_t_type(), field);
}

#define mp_read_lv_theme_style_img_t(field) mp_read_ptr_lv_theme_style_img_t(copy_buffer(&field, sizeof(lv_theme_style_img_t)))
#define mp_read_byref_lv_theme_style_img_t(field) mp_read_ptr_lv_theme_style_img_t(&field)

STATIC void mp_lv_theme_style_img_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_img_t *data = (lv_theme_style_img_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_light: dest[0] = ptr_to_mp((void*)data->light); break; // converting from lv_style_t *;
            case MP_QSTR_dark: dest[0] = ptr_to_mp((void*)data->dark); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_img_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_light: data->light = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_dark: data->dark = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_img_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_img_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_img_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_img_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_img_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_img_t_locals_dict, mp_lv_theme_style_img_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_img_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_img_t,
    .print = mp_lv_theme_style_img_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_img_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_img_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_img_t_type()
{
    return &mp_lv_theme_style_img_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->line ) lv_theme_style_line_t;

/*
 * Struct lv_theme_style_line_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_line_t_type();

STATIC inline lv_theme_style_line_t* mp_write_ptr_lv_theme_style_line_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_line_t_type()));
    return (lv_theme_style_line_t*)self->data;
}

#define mp_write_lv_theme_style_line_t(struct_obj) *mp_write_ptr_lv_theme_style_line_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_line_t(lv_theme_style_line_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_line_t_type(), field);
}

#define mp_read_lv_theme_style_line_t(field) mp_read_ptr_lv_theme_style_line_t(copy_buffer(&field, sizeof(lv_theme_style_line_t)))
#define mp_read_byref_lv_theme_style_line_t(field) mp_read_ptr_lv_theme_style_line_t(&field)

STATIC void mp_lv_theme_style_line_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_line_t *data = (lv_theme_style_line_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_decor: dest[0] = ptr_to_mp((void*)data->decor); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_line_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_decor: data->decor = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_line_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_line_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_line_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_line_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_line_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_line_t_locals_dict, mp_lv_theme_style_line_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_line_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_line_t,
    .print = mp_lv_theme_style_line_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_line_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_line_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_line_t_type()
{
    return &mp_lv_theme_style_line_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->bar ) lv_theme_style_bar_t;

/*
 * Struct lv_theme_style_bar_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_bar_t_type();

STATIC inline lv_theme_style_bar_t* mp_write_ptr_lv_theme_style_bar_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_bar_t_type()));
    return (lv_theme_style_bar_t*)self->data;
}

#define mp_write_lv_theme_style_bar_t(struct_obj) *mp_write_ptr_lv_theme_style_bar_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_bar_t(lv_theme_style_bar_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_bar_t_type(), field);
}

#define mp_read_lv_theme_style_bar_t(field) mp_read_ptr_lv_theme_style_bar_t(copy_buffer(&field, sizeof(lv_theme_style_bar_t)))
#define mp_read_byref_lv_theme_style_bar_t(field) mp_read_ptr_lv_theme_style_bar_t(&field)

STATIC void mp_lv_theme_style_bar_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_bar_t *data = (lv_theme_style_bar_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_indic: dest[0] = ptr_to_mp((void*)data->indic); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_bar_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_indic: data->indic = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_bar_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_bar_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_bar_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_bar_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_bar_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_bar_t_locals_dict, mp_lv_theme_style_bar_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_bar_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_bar_t,
    .print = mp_lv_theme_style_bar_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_bar_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_bar_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_bar_t_type()
{
    return &mp_lv_theme_style_bar_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->slider ) lv_theme_style_slider_t;

/*
 * Struct lv_theme_style_slider_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_slider_t_type();

STATIC inline lv_theme_style_slider_t* mp_write_ptr_lv_theme_style_slider_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_slider_t_type()));
    return (lv_theme_style_slider_t*)self->data;
}

#define mp_write_lv_theme_style_slider_t(struct_obj) *mp_write_ptr_lv_theme_style_slider_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_slider_t(lv_theme_style_slider_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_slider_t_type(), field);
}

#define mp_read_lv_theme_style_slider_t(field) mp_read_ptr_lv_theme_style_slider_t(copy_buffer(&field, sizeof(lv_theme_style_slider_t)))
#define mp_read_byref_lv_theme_style_slider_t(field) mp_read_ptr_lv_theme_style_slider_t(&field)

STATIC void mp_lv_theme_style_slider_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_slider_t *data = (lv_theme_style_slider_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_indic: dest[0] = ptr_to_mp((void*)data->indic); break; // converting from lv_style_t *;
            case MP_QSTR_knob: dest[0] = ptr_to_mp((void*)data->knob); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_slider_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_indic: data->indic = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_knob: data->knob = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_slider_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_slider_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_slider_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_slider_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_slider_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_slider_t_locals_dict, mp_lv_theme_style_slider_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_slider_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_slider_t,
    .print = mp_lv_theme_style_slider_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_slider_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_slider_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_slider_t_type()
{
    return &mp_lv_theme_style_slider_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->sw ) lv_theme_style_sw_t;

/*
 * Struct lv_theme_style_sw_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_sw_t_type();

STATIC inline lv_theme_style_sw_t* mp_write_ptr_lv_theme_style_sw_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_sw_t_type()));
    return (lv_theme_style_sw_t*)self->data;
}

#define mp_write_lv_theme_style_sw_t(struct_obj) *mp_write_ptr_lv_theme_style_sw_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_sw_t(lv_theme_style_sw_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_sw_t_type(), field);
}

#define mp_read_lv_theme_style_sw_t(field) mp_read_ptr_lv_theme_style_sw_t(copy_buffer(&field, sizeof(lv_theme_style_sw_t)))
#define mp_read_byref_lv_theme_style_sw_t(field) mp_read_ptr_lv_theme_style_sw_t(&field)

STATIC void mp_lv_theme_style_sw_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_sw_t *data = (lv_theme_style_sw_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_indic: dest[0] = ptr_to_mp((void*)data->indic); break; // converting from lv_style_t *;
            case MP_QSTR_knob_off: dest[0] = ptr_to_mp((void*)data->knob_off); break; // converting from lv_style_t *;
            case MP_QSTR_knob_on: dest[0] = ptr_to_mp((void*)data->knob_on); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_sw_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_indic: data->indic = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_knob_off: data->knob_off = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_knob_on: data->knob_on = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_sw_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_sw_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_sw_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_sw_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_sw_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_sw_t_locals_dict, mp_lv_theme_style_sw_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_sw_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_sw_t,
    .print = mp_lv_theme_style_sw_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_sw_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_sw_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_sw_t_type()
{
    return &mp_lv_theme_style_sw_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->calendar ) lv_theme_style_calendar_t;

/*
 * Struct lv_theme_style_calendar_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_calendar_t_type();

STATIC inline lv_theme_style_calendar_t* mp_write_ptr_lv_theme_style_calendar_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_calendar_t_type()));
    return (lv_theme_style_calendar_t*)self->data;
}

#define mp_write_lv_theme_style_calendar_t(struct_obj) *mp_write_ptr_lv_theme_style_calendar_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_calendar_t(lv_theme_style_calendar_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_calendar_t_type(), field);
}

#define mp_read_lv_theme_style_calendar_t(field) mp_read_ptr_lv_theme_style_calendar_t(copy_buffer(&field, sizeof(lv_theme_style_calendar_t)))
#define mp_read_byref_lv_theme_style_calendar_t(field) mp_read_ptr_lv_theme_style_calendar_t(&field)

STATIC void mp_lv_theme_style_calendar_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_calendar_t *data = (lv_theme_style_calendar_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_header: dest[0] = ptr_to_mp((void*)data->header); break; // converting from lv_style_t *;
            case MP_QSTR_header_pr: dest[0] = ptr_to_mp((void*)data->header_pr); break; // converting from lv_style_t *;
            case MP_QSTR_day_names: dest[0] = ptr_to_mp((void*)data->day_names); break; // converting from lv_style_t *;
            case MP_QSTR_highlighted_days: dest[0] = ptr_to_mp((void*)data->highlighted_days); break; // converting from lv_style_t *;
            case MP_QSTR_inactive_days: dest[0] = ptr_to_mp((void*)data->inactive_days); break; // converting from lv_style_t *;
            case MP_QSTR_week_box: dest[0] = ptr_to_mp((void*)data->week_box); break; // converting from lv_style_t *;
            case MP_QSTR_today_box: dest[0] = ptr_to_mp((void*)data->today_box); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_calendar_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_header: data->header = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_header_pr: data->header_pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_day_names: data->day_names = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_highlighted_days: data->highlighted_days = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_inactive_days: data->inactive_days = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_week_box: data->week_box = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_today_box: data->today_box = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_calendar_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_calendar_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_calendar_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_calendar_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_calendar_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_calendar_t_locals_dict, mp_lv_theme_style_calendar_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_calendar_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_calendar_t,
    .print = mp_lv_theme_style_calendar_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_calendar_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_calendar_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_calendar_t_type()
{
    return &mp_lv_theme_style_calendar_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->cb ) lv_theme_style_cb_t;
typedef typeof( ((lv_theme_style_cb_t*)(0))->box ) lv_theme_style_cb_box_t;

/*
 * Struct lv_theme_style_cb_box_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_cb_box_t_type();

STATIC inline lv_theme_style_cb_box_t* mp_write_ptr_lv_theme_style_cb_box_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_cb_box_t_type()));
    return (lv_theme_style_cb_box_t*)self->data;
}

#define mp_write_lv_theme_style_cb_box_t(struct_obj) *mp_write_ptr_lv_theme_style_cb_box_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_cb_box_t(lv_theme_style_cb_box_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_cb_box_t_type(), field);
}

#define mp_read_lv_theme_style_cb_box_t(field) mp_read_ptr_lv_theme_style_cb_box_t(copy_buffer(&field, sizeof(lv_theme_style_cb_box_t)))
#define mp_read_byref_lv_theme_style_cb_box_t(field) mp_read_ptr_lv_theme_style_cb_box_t(&field)

STATIC void mp_lv_theme_style_cb_box_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_cb_box_t *data = (lv_theme_style_cb_box_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_rel: dest[0] = ptr_to_mp((void*)data->rel); break; // converting from lv_style_t *;
            case MP_QSTR_pr: dest[0] = ptr_to_mp((void*)data->pr); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_rel: dest[0] = ptr_to_mp((void*)data->tgl_rel); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_pr: dest[0] = ptr_to_mp((void*)data->tgl_pr); break; // converting from lv_style_t *;
            case MP_QSTR_ina: dest[0] = ptr_to_mp((void*)data->ina); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_cb_box_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_rel: data->rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_pr: data->pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_rel: data->tgl_rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_pr: data->tgl_pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_ina: data->ina = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_cb_box_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_cb_box_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_cb_box_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_cb_box_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_cb_box_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_cb_box_t_locals_dict, mp_lv_theme_style_cb_box_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_cb_box_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_cb_box_t,
    .print = mp_lv_theme_style_cb_box_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_cb_box_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_cb_box_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_cb_box_t_type()
{
    return &mp_lv_theme_style_cb_box_t_type;
}
    

/*
 * Struct lv_theme_style_cb_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_cb_t_type();

STATIC inline lv_theme_style_cb_t* mp_write_ptr_lv_theme_style_cb_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_cb_t_type()));
    return (lv_theme_style_cb_t*)self->data;
}

#define mp_write_lv_theme_style_cb_t(struct_obj) *mp_write_ptr_lv_theme_style_cb_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_cb_t(lv_theme_style_cb_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_cb_t_type(), field);
}

#define mp_read_lv_theme_style_cb_t(field) mp_read_ptr_lv_theme_style_cb_t(copy_buffer(&field, sizeof(lv_theme_style_cb_t)))
#define mp_read_byref_lv_theme_style_cb_t(field) mp_read_ptr_lv_theme_style_cb_t(&field)

STATIC void mp_lv_theme_style_cb_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_cb_t *data = (lv_theme_style_cb_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_box: dest[0] = mp_read_byref_lv_theme_style_cb_box_t(data->box); break; // converting from lv_theme_style_cb_box_t;
            default: field_not_found(MP_QSTR_lv_theme_style_cb_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_box: data->box = mp_write_lv_theme_style_cb_box_t(dest[1]); break; // converting to lv_theme_style_cb_box_t;
                default: field_not_found(MP_QSTR_lv_theme_style_cb_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_cb_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_cb_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_cb_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_cb_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_cb_t_locals_dict, mp_lv_theme_style_cb_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_cb_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_cb_t,
    .print = mp_lv_theme_style_cb_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_cb_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_cb_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_cb_t_type()
{
    return &mp_lv_theme_style_cb_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->btnm ) lv_theme_style_btnm_t;
typedef typeof( ((lv_theme_style_btnm_t*)(0))->btn ) lv_theme_style_btnm_btn_t;

/*
 * Struct lv_theme_style_btnm_btn_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_btnm_btn_t_type();

STATIC inline lv_theme_style_btnm_btn_t* mp_write_ptr_lv_theme_style_btnm_btn_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_btnm_btn_t_type()));
    return (lv_theme_style_btnm_btn_t*)self->data;
}

#define mp_write_lv_theme_style_btnm_btn_t(struct_obj) *mp_write_ptr_lv_theme_style_btnm_btn_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_btnm_btn_t(lv_theme_style_btnm_btn_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_btnm_btn_t_type(), field);
}

#define mp_read_lv_theme_style_btnm_btn_t(field) mp_read_ptr_lv_theme_style_btnm_btn_t(copy_buffer(&field, sizeof(lv_theme_style_btnm_btn_t)))
#define mp_read_byref_lv_theme_style_btnm_btn_t(field) mp_read_ptr_lv_theme_style_btnm_btn_t(&field)

STATIC void mp_lv_theme_style_btnm_btn_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_btnm_btn_t *data = (lv_theme_style_btnm_btn_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_rel: dest[0] = ptr_to_mp((void*)data->rel); break; // converting from lv_style_t *;
            case MP_QSTR_pr: dest[0] = ptr_to_mp((void*)data->pr); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_rel: dest[0] = ptr_to_mp((void*)data->tgl_rel); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_pr: dest[0] = ptr_to_mp((void*)data->tgl_pr); break; // converting from lv_style_t *;
            case MP_QSTR_ina: dest[0] = ptr_to_mp((void*)data->ina); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_btnm_btn_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_rel: data->rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_pr: data->pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_rel: data->tgl_rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_pr: data->tgl_pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_ina: data->ina = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_btnm_btn_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_btnm_btn_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_btnm_btn_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_btnm_btn_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_btnm_btn_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_btnm_btn_t_locals_dict, mp_lv_theme_style_btnm_btn_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_btnm_btn_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_btnm_btn_t,
    .print = mp_lv_theme_style_btnm_btn_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_btnm_btn_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_btnm_btn_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_btnm_btn_t_type()
{
    return &mp_lv_theme_style_btnm_btn_t_type;
}
    

/*
 * Struct lv_theme_style_btnm_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_btnm_t_type();

STATIC inline lv_theme_style_btnm_t* mp_write_ptr_lv_theme_style_btnm_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_btnm_t_type()));
    return (lv_theme_style_btnm_t*)self->data;
}

#define mp_write_lv_theme_style_btnm_t(struct_obj) *mp_write_ptr_lv_theme_style_btnm_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_btnm_t(lv_theme_style_btnm_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_btnm_t_type(), field);
}

#define mp_read_lv_theme_style_btnm_t(field) mp_read_ptr_lv_theme_style_btnm_t(copy_buffer(&field, sizeof(lv_theme_style_btnm_t)))
#define mp_read_byref_lv_theme_style_btnm_t(field) mp_read_ptr_lv_theme_style_btnm_t(&field)

STATIC void mp_lv_theme_style_btnm_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_btnm_t *data = (lv_theme_style_btnm_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_btn: dest[0] = mp_read_byref_lv_theme_style_btnm_btn_t(data->btn); break; // converting from lv_theme_style_btnm_btn_t;
            default: field_not_found(MP_QSTR_lv_theme_style_btnm_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_btn: data->btn = mp_write_lv_theme_style_btnm_btn_t(dest[1]); break; // converting to lv_theme_style_btnm_btn_t;
                default: field_not_found(MP_QSTR_lv_theme_style_btnm_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_btnm_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_btnm_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_btnm_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_btnm_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_btnm_t_locals_dict, mp_lv_theme_style_btnm_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_btnm_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_btnm_t,
    .print = mp_lv_theme_style_btnm_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_btnm_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_btnm_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_btnm_t_type()
{
    return &mp_lv_theme_style_btnm_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->kb ) lv_theme_style_kb_t;
typedef typeof( ((lv_theme_style_kb_t*)(0))->btn ) lv_theme_style_kb_btn_t;

/*
 * Struct lv_theme_style_kb_btn_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_kb_btn_t_type();

STATIC inline lv_theme_style_kb_btn_t* mp_write_ptr_lv_theme_style_kb_btn_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_kb_btn_t_type()));
    return (lv_theme_style_kb_btn_t*)self->data;
}

#define mp_write_lv_theme_style_kb_btn_t(struct_obj) *mp_write_ptr_lv_theme_style_kb_btn_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_kb_btn_t(lv_theme_style_kb_btn_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_kb_btn_t_type(), field);
}

#define mp_read_lv_theme_style_kb_btn_t(field) mp_read_ptr_lv_theme_style_kb_btn_t(copy_buffer(&field, sizeof(lv_theme_style_kb_btn_t)))
#define mp_read_byref_lv_theme_style_kb_btn_t(field) mp_read_ptr_lv_theme_style_kb_btn_t(&field)

STATIC void mp_lv_theme_style_kb_btn_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_kb_btn_t *data = (lv_theme_style_kb_btn_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_rel: dest[0] = ptr_to_mp((void*)data->rel); break; // converting from lv_style_t *;
            case MP_QSTR_pr: dest[0] = ptr_to_mp((void*)data->pr); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_rel: dest[0] = ptr_to_mp((void*)data->tgl_rel); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_pr: dest[0] = ptr_to_mp((void*)data->tgl_pr); break; // converting from lv_style_t *;
            case MP_QSTR_ina: dest[0] = ptr_to_mp((void*)data->ina); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_kb_btn_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_rel: data->rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_pr: data->pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_rel: data->tgl_rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_pr: data->tgl_pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_ina: data->ina = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_kb_btn_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_kb_btn_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_kb_btn_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_kb_btn_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_kb_btn_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_kb_btn_t_locals_dict, mp_lv_theme_style_kb_btn_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_kb_btn_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_kb_btn_t,
    .print = mp_lv_theme_style_kb_btn_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_kb_btn_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_kb_btn_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_kb_btn_t_type()
{
    return &mp_lv_theme_style_kb_btn_t_type;
}
    

/*
 * Struct lv_theme_style_kb_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_kb_t_type();

STATIC inline lv_theme_style_kb_t* mp_write_ptr_lv_theme_style_kb_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_kb_t_type()));
    return (lv_theme_style_kb_t*)self->data;
}

#define mp_write_lv_theme_style_kb_t(struct_obj) *mp_write_ptr_lv_theme_style_kb_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_kb_t(lv_theme_style_kb_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_kb_t_type(), field);
}

#define mp_read_lv_theme_style_kb_t(field) mp_read_ptr_lv_theme_style_kb_t(copy_buffer(&field, sizeof(lv_theme_style_kb_t)))
#define mp_read_byref_lv_theme_style_kb_t(field) mp_read_ptr_lv_theme_style_kb_t(&field)

STATIC void mp_lv_theme_style_kb_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_kb_t *data = (lv_theme_style_kb_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_btn: dest[0] = mp_read_byref_lv_theme_style_kb_btn_t(data->btn); break; // converting from lv_theme_style_kb_btn_t;
            default: field_not_found(MP_QSTR_lv_theme_style_kb_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_btn: data->btn = mp_write_lv_theme_style_kb_btn_t(dest[1]); break; // converting to lv_theme_style_kb_btn_t;
                default: field_not_found(MP_QSTR_lv_theme_style_kb_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_kb_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_kb_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_kb_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_kb_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_kb_t_locals_dict, mp_lv_theme_style_kb_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_kb_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_kb_t,
    .print = mp_lv_theme_style_kb_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_kb_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_kb_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_kb_t_type()
{
    return &mp_lv_theme_style_kb_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->mbox ) lv_theme_style_mbox_t;
typedef typeof( ((lv_theme_style_mbox_t*)(0))->btn ) lv_theme_style_mbox_btn_t;

/*
 * Struct lv_theme_style_mbox_btn_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_mbox_btn_t_type();

STATIC inline lv_theme_style_mbox_btn_t* mp_write_ptr_lv_theme_style_mbox_btn_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_mbox_btn_t_type()));
    return (lv_theme_style_mbox_btn_t*)self->data;
}

#define mp_write_lv_theme_style_mbox_btn_t(struct_obj) *mp_write_ptr_lv_theme_style_mbox_btn_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_mbox_btn_t(lv_theme_style_mbox_btn_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_mbox_btn_t_type(), field);
}

#define mp_read_lv_theme_style_mbox_btn_t(field) mp_read_ptr_lv_theme_style_mbox_btn_t(copy_buffer(&field, sizeof(lv_theme_style_mbox_btn_t)))
#define mp_read_byref_lv_theme_style_mbox_btn_t(field) mp_read_ptr_lv_theme_style_mbox_btn_t(&field)

STATIC void mp_lv_theme_style_mbox_btn_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_mbox_btn_t *data = (lv_theme_style_mbox_btn_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_rel: dest[0] = ptr_to_mp((void*)data->rel); break; // converting from lv_style_t *;
            case MP_QSTR_pr: dest[0] = ptr_to_mp((void*)data->pr); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_mbox_btn_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_rel: data->rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_pr: data->pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_mbox_btn_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_mbox_btn_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_mbox_btn_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_mbox_btn_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_mbox_btn_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_mbox_btn_t_locals_dict, mp_lv_theme_style_mbox_btn_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_mbox_btn_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_mbox_btn_t,
    .print = mp_lv_theme_style_mbox_btn_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_mbox_btn_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_mbox_btn_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_mbox_btn_t_type()
{
    return &mp_lv_theme_style_mbox_btn_t_type;
}
    

/*
 * Struct lv_theme_style_mbox_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_mbox_t_type();

STATIC inline lv_theme_style_mbox_t* mp_write_ptr_lv_theme_style_mbox_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_mbox_t_type()));
    return (lv_theme_style_mbox_t*)self->data;
}

#define mp_write_lv_theme_style_mbox_t(struct_obj) *mp_write_ptr_lv_theme_style_mbox_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_mbox_t(lv_theme_style_mbox_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_mbox_t_type(), field);
}

#define mp_read_lv_theme_style_mbox_t(field) mp_read_ptr_lv_theme_style_mbox_t(copy_buffer(&field, sizeof(lv_theme_style_mbox_t)))
#define mp_read_byref_lv_theme_style_mbox_t(field) mp_read_ptr_lv_theme_style_mbox_t(&field)

STATIC void mp_lv_theme_style_mbox_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_mbox_t *data = (lv_theme_style_mbox_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_btn: dest[0] = mp_read_byref_lv_theme_style_mbox_btn_t(data->btn); break; // converting from lv_theme_style_mbox_btn_t;
            default: field_not_found(MP_QSTR_lv_theme_style_mbox_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_btn: data->btn = mp_write_lv_theme_style_mbox_btn_t(dest[1]); break; // converting to lv_theme_style_mbox_btn_t;
                default: field_not_found(MP_QSTR_lv_theme_style_mbox_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_mbox_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_mbox_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_mbox_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_mbox_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_mbox_t_locals_dict, mp_lv_theme_style_mbox_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_mbox_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_mbox_t,
    .print = mp_lv_theme_style_mbox_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_mbox_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_mbox_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_mbox_t_type()
{
    return &mp_lv_theme_style_mbox_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->page ) lv_theme_style_page_t;

/*
 * Struct lv_theme_style_page_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_page_t_type();

STATIC inline lv_theme_style_page_t* mp_write_ptr_lv_theme_style_page_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_page_t_type()));
    return (lv_theme_style_page_t*)self->data;
}

#define mp_write_lv_theme_style_page_t(struct_obj) *mp_write_ptr_lv_theme_style_page_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_page_t(lv_theme_style_page_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_page_t_type(), field);
}

#define mp_read_lv_theme_style_page_t(field) mp_read_ptr_lv_theme_style_page_t(copy_buffer(&field, sizeof(lv_theme_style_page_t)))
#define mp_read_byref_lv_theme_style_page_t(field) mp_read_ptr_lv_theme_style_page_t(&field)

STATIC void mp_lv_theme_style_page_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_page_t *data = (lv_theme_style_page_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_scrl: dest[0] = ptr_to_mp((void*)data->scrl); break; // converting from lv_style_t *;
            case MP_QSTR_sb: dest[0] = ptr_to_mp((void*)data->sb); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_page_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_scrl: data->scrl = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_sb: data->sb = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_page_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_page_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_page_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_page_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_page_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_page_t_locals_dict, mp_lv_theme_style_page_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_page_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_page_t,
    .print = mp_lv_theme_style_page_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_page_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_page_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_page_t_type()
{
    return &mp_lv_theme_style_page_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->ta ) lv_theme_style_ta_t;

/*
 * Struct lv_theme_style_ta_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_ta_t_type();

STATIC inline lv_theme_style_ta_t* mp_write_ptr_lv_theme_style_ta_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_ta_t_type()));
    return (lv_theme_style_ta_t*)self->data;
}

#define mp_write_lv_theme_style_ta_t(struct_obj) *mp_write_ptr_lv_theme_style_ta_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_ta_t(lv_theme_style_ta_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_ta_t_type(), field);
}

#define mp_read_lv_theme_style_ta_t(field) mp_read_ptr_lv_theme_style_ta_t(copy_buffer(&field, sizeof(lv_theme_style_ta_t)))
#define mp_read_byref_lv_theme_style_ta_t(field) mp_read_ptr_lv_theme_style_ta_t(&field)

STATIC void mp_lv_theme_style_ta_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_ta_t *data = (lv_theme_style_ta_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_area: dest[0] = ptr_to_mp((void*)data->area); break; // converting from lv_style_t *;
            case MP_QSTR_oneline: dest[0] = ptr_to_mp((void*)data->oneline); break; // converting from lv_style_t *;
            case MP_QSTR_cursor: dest[0] = ptr_to_mp((void*)data->cursor); break; // converting from lv_style_t *;
            case MP_QSTR_sb: dest[0] = ptr_to_mp((void*)data->sb); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_ta_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_area: data->area = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_oneline: data->oneline = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_cursor: data->cursor = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_sb: data->sb = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_ta_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_ta_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_ta_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_ta_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_ta_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_ta_t_locals_dict, mp_lv_theme_style_ta_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_ta_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_ta_t,
    .print = mp_lv_theme_style_ta_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_ta_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_ta_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_ta_t_type()
{
    return &mp_lv_theme_style_ta_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->spinbox ) lv_theme_style_spinbox_t;

/*
 * Struct lv_theme_style_spinbox_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_spinbox_t_type();

STATIC inline lv_theme_style_spinbox_t* mp_write_ptr_lv_theme_style_spinbox_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_spinbox_t_type()));
    return (lv_theme_style_spinbox_t*)self->data;
}

#define mp_write_lv_theme_style_spinbox_t(struct_obj) *mp_write_ptr_lv_theme_style_spinbox_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_spinbox_t(lv_theme_style_spinbox_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_spinbox_t_type(), field);
}

#define mp_read_lv_theme_style_spinbox_t(field) mp_read_ptr_lv_theme_style_spinbox_t(copy_buffer(&field, sizeof(lv_theme_style_spinbox_t)))
#define mp_read_byref_lv_theme_style_spinbox_t(field) mp_read_ptr_lv_theme_style_spinbox_t(&field)

STATIC void mp_lv_theme_style_spinbox_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_spinbox_t *data = (lv_theme_style_spinbox_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_cursor: dest[0] = ptr_to_mp((void*)data->cursor); break; // converting from lv_style_t *;
            case MP_QSTR_sb: dest[0] = ptr_to_mp((void*)data->sb); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_spinbox_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_cursor: data->cursor = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_sb: data->sb = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_spinbox_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_spinbox_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_spinbox_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_spinbox_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_spinbox_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_spinbox_t_locals_dict, mp_lv_theme_style_spinbox_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_spinbox_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_spinbox_t,
    .print = mp_lv_theme_style_spinbox_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_spinbox_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_spinbox_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_spinbox_t_type()
{
    return &mp_lv_theme_style_spinbox_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->list ) lv_theme_style_list_t;
typedef typeof( ((lv_theme_style_list_t*)(0))->btn ) lv_theme_style_list_btn_t;

/*
 * Struct lv_theme_style_list_btn_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_list_btn_t_type();

STATIC inline lv_theme_style_list_btn_t* mp_write_ptr_lv_theme_style_list_btn_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_list_btn_t_type()));
    return (lv_theme_style_list_btn_t*)self->data;
}

#define mp_write_lv_theme_style_list_btn_t(struct_obj) *mp_write_ptr_lv_theme_style_list_btn_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_list_btn_t(lv_theme_style_list_btn_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_list_btn_t_type(), field);
}

#define mp_read_lv_theme_style_list_btn_t(field) mp_read_ptr_lv_theme_style_list_btn_t(copy_buffer(&field, sizeof(lv_theme_style_list_btn_t)))
#define mp_read_byref_lv_theme_style_list_btn_t(field) mp_read_ptr_lv_theme_style_list_btn_t(&field)

STATIC void mp_lv_theme_style_list_btn_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_list_btn_t *data = (lv_theme_style_list_btn_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_rel: dest[0] = ptr_to_mp((void*)data->rel); break; // converting from lv_style_t *;
            case MP_QSTR_pr: dest[0] = ptr_to_mp((void*)data->pr); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_rel: dest[0] = ptr_to_mp((void*)data->tgl_rel); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_pr: dest[0] = ptr_to_mp((void*)data->tgl_pr); break; // converting from lv_style_t *;
            case MP_QSTR_ina: dest[0] = ptr_to_mp((void*)data->ina); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_list_btn_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_rel: data->rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_pr: data->pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_rel: data->tgl_rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_pr: data->tgl_pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_ina: data->ina = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_list_btn_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_list_btn_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_list_btn_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_list_btn_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_list_btn_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_list_btn_t_locals_dict, mp_lv_theme_style_list_btn_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_list_btn_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_list_btn_t,
    .print = mp_lv_theme_style_list_btn_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_list_btn_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_list_btn_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_list_btn_t_type()
{
    return &mp_lv_theme_style_list_btn_t_type;
}
    

/*
 * Struct lv_theme_style_list_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_list_t_type();

STATIC inline lv_theme_style_list_t* mp_write_ptr_lv_theme_style_list_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_list_t_type()));
    return (lv_theme_style_list_t*)self->data;
}

#define mp_write_lv_theme_style_list_t(struct_obj) *mp_write_ptr_lv_theme_style_list_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_list_t(lv_theme_style_list_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_list_t_type(), field);
}

#define mp_read_lv_theme_style_list_t(field) mp_read_ptr_lv_theme_style_list_t(copy_buffer(&field, sizeof(lv_theme_style_list_t)))
#define mp_read_byref_lv_theme_style_list_t(field) mp_read_ptr_lv_theme_style_list_t(&field)

STATIC void mp_lv_theme_style_list_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_list_t *data = (lv_theme_style_list_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_scrl: dest[0] = ptr_to_mp((void*)data->scrl); break; // converting from lv_style_t *;
            case MP_QSTR_sb: dest[0] = ptr_to_mp((void*)data->sb); break; // converting from lv_style_t *;
            case MP_QSTR_btn: dest[0] = mp_read_byref_lv_theme_style_list_btn_t(data->btn); break; // converting from lv_theme_style_list_btn_t;
            default: field_not_found(MP_QSTR_lv_theme_style_list_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_scrl: data->scrl = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_sb: data->sb = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_btn: data->btn = mp_write_lv_theme_style_list_btn_t(dest[1]); break; // converting to lv_theme_style_list_btn_t;
                default: field_not_found(MP_QSTR_lv_theme_style_list_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_list_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_list_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_list_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_list_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_list_t_locals_dict, mp_lv_theme_style_list_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_list_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_list_t,
    .print = mp_lv_theme_style_list_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_list_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_list_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_list_t_type()
{
    return &mp_lv_theme_style_list_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->ddlist ) lv_theme_style_ddlist_t;

/*
 * Struct lv_theme_style_ddlist_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_ddlist_t_type();

STATIC inline lv_theme_style_ddlist_t* mp_write_ptr_lv_theme_style_ddlist_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_ddlist_t_type()));
    return (lv_theme_style_ddlist_t*)self->data;
}

#define mp_write_lv_theme_style_ddlist_t(struct_obj) *mp_write_ptr_lv_theme_style_ddlist_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_ddlist_t(lv_theme_style_ddlist_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_ddlist_t_type(), field);
}

#define mp_read_lv_theme_style_ddlist_t(field) mp_read_ptr_lv_theme_style_ddlist_t(copy_buffer(&field, sizeof(lv_theme_style_ddlist_t)))
#define mp_read_byref_lv_theme_style_ddlist_t(field) mp_read_ptr_lv_theme_style_ddlist_t(&field)

STATIC void mp_lv_theme_style_ddlist_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_ddlist_t *data = (lv_theme_style_ddlist_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_sel: dest[0] = ptr_to_mp((void*)data->sel); break; // converting from lv_style_t *;
            case MP_QSTR_sb: dest[0] = ptr_to_mp((void*)data->sb); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_ddlist_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_sel: data->sel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_sb: data->sb = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_ddlist_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_ddlist_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_ddlist_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_ddlist_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_ddlist_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_ddlist_t_locals_dict, mp_lv_theme_style_ddlist_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_ddlist_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_ddlist_t,
    .print = mp_lv_theme_style_ddlist_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_ddlist_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_ddlist_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_ddlist_t_type()
{
    return &mp_lv_theme_style_ddlist_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->roller ) lv_theme_style_roller_t;

/*
 * Struct lv_theme_style_roller_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_roller_t_type();

STATIC inline lv_theme_style_roller_t* mp_write_ptr_lv_theme_style_roller_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_roller_t_type()));
    return (lv_theme_style_roller_t*)self->data;
}

#define mp_write_lv_theme_style_roller_t(struct_obj) *mp_write_ptr_lv_theme_style_roller_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_roller_t(lv_theme_style_roller_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_roller_t_type(), field);
}

#define mp_read_lv_theme_style_roller_t(field) mp_read_ptr_lv_theme_style_roller_t(copy_buffer(&field, sizeof(lv_theme_style_roller_t)))
#define mp_read_byref_lv_theme_style_roller_t(field) mp_read_ptr_lv_theme_style_roller_t(&field)

STATIC void mp_lv_theme_style_roller_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_roller_t *data = (lv_theme_style_roller_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_sel: dest[0] = ptr_to_mp((void*)data->sel); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_roller_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_sel: data->sel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_roller_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_roller_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_roller_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_roller_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_roller_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_roller_t_locals_dict, mp_lv_theme_style_roller_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_roller_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_roller_t,
    .print = mp_lv_theme_style_roller_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_roller_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_roller_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_roller_t_type()
{
    return &mp_lv_theme_style_roller_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->tabview ) lv_theme_style_tabview_t;
typedef typeof( ((lv_theme_style_tabview_t*)(0))->btn ) lv_theme_style_tabview_btn_t;

/*
 * Struct lv_theme_style_tabview_btn_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_tabview_btn_t_type();

STATIC inline lv_theme_style_tabview_btn_t* mp_write_ptr_lv_theme_style_tabview_btn_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_tabview_btn_t_type()));
    return (lv_theme_style_tabview_btn_t*)self->data;
}

#define mp_write_lv_theme_style_tabview_btn_t(struct_obj) *mp_write_ptr_lv_theme_style_tabview_btn_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_tabview_btn_t(lv_theme_style_tabview_btn_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_tabview_btn_t_type(), field);
}

#define mp_read_lv_theme_style_tabview_btn_t(field) mp_read_ptr_lv_theme_style_tabview_btn_t(copy_buffer(&field, sizeof(lv_theme_style_tabview_btn_t)))
#define mp_read_byref_lv_theme_style_tabview_btn_t(field) mp_read_ptr_lv_theme_style_tabview_btn_t(&field)

STATIC void mp_lv_theme_style_tabview_btn_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_tabview_btn_t *data = (lv_theme_style_tabview_btn_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_rel: dest[0] = ptr_to_mp((void*)data->rel); break; // converting from lv_style_t *;
            case MP_QSTR_pr: dest[0] = ptr_to_mp((void*)data->pr); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_rel: dest[0] = ptr_to_mp((void*)data->tgl_rel); break; // converting from lv_style_t *;
            case MP_QSTR_tgl_pr: dest[0] = ptr_to_mp((void*)data->tgl_pr); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_tabview_btn_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_rel: data->rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_pr: data->pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_rel: data->tgl_rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_tgl_pr: data->tgl_pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_tabview_btn_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_tabview_btn_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_tabview_btn_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_tabview_btn_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_tabview_btn_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_tabview_btn_t_locals_dict, mp_lv_theme_style_tabview_btn_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_tabview_btn_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_tabview_btn_t,
    .print = mp_lv_theme_style_tabview_btn_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_tabview_btn_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_tabview_btn_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_tabview_btn_t_type()
{
    return &mp_lv_theme_style_tabview_btn_t_type;
}
    

/*
 * Struct lv_theme_style_tabview_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_tabview_t_type();

STATIC inline lv_theme_style_tabview_t* mp_write_ptr_lv_theme_style_tabview_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_tabview_t_type()));
    return (lv_theme_style_tabview_t*)self->data;
}

#define mp_write_lv_theme_style_tabview_t(struct_obj) *mp_write_ptr_lv_theme_style_tabview_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_tabview_t(lv_theme_style_tabview_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_tabview_t_type(), field);
}

#define mp_read_lv_theme_style_tabview_t(field) mp_read_ptr_lv_theme_style_tabview_t(copy_buffer(&field, sizeof(lv_theme_style_tabview_t)))
#define mp_read_byref_lv_theme_style_tabview_t(field) mp_read_ptr_lv_theme_style_tabview_t(&field)

STATIC void mp_lv_theme_style_tabview_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_tabview_t *data = (lv_theme_style_tabview_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_indic: dest[0] = ptr_to_mp((void*)data->indic); break; // converting from lv_style_t *;
            case MP_QSTR_btn: dest[0] = mp_read_byref_lv_theme_style_tabview_btn_t(data->btn); break; // converting from lv_theme_style_tabview_btn_t;
            default: field_not_found(MP_QSTR_lv_theme_style_tabview_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_indic: data->indic = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_btn: data->btn = mp_write_lv_theme_style_tabview_btn_t(dest[1]); break; // converting to lv_theme_style_tabview_btn_t;
                default: field_not_found(MP_QSTR_lv_theme_style_tabview_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_tabview_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_tabview_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_tabview_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_tabview_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_tabview_t_locals_dict, mp_lv_theme_style_tabview_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_tabview_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_tabview_t,
    .print = mp_lv_theme_style_tabview_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_tabview_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_tabview_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_tabview_t_type()
{
    return &mp_lv_theme_style_tabview_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->tileview ) lv_theme_style_tileview_t;

/*
 * Struct lv_theme_style_tileview_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_tileview_t_type();

STATIC inline lv_theme_style_tileview_t* mp_write_ptr_lv_theme_style_tileview_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_tileview_t_type()));
    return (lv_theme_style_tileview_t*)self->data;
}

#define mp_write_lv_theme_style_tileview_t(struct_obj) *mp_write_ptr_lv_theme_style_tileview_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_tileview_t(lv_theme_style_tileview_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_tileview_t_type(), field);
}

#define mp_read_lv_theme_style_tileview_t(field) mp_read_ptr_lv_theme_style_tileview_t(copy_buffer(&field, sizeof(lv_theme_style_tileview_t)))
#define mp_read_byref_lv_theme_style_tileview_t(field) mp_read_ptr_lv_theme_style_tileview_t(&field)

STATIC void mp_lv_theme_style_tileview_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_tileview_t *data = (lv_theme_style_tileview_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_scrl: dest[0] = ptr_to_mp((void*)data->scrl); break; // converting from lv_style_t *;
            case MP_QSTR_sb: dest[0] = ptr_to_mp((void*)data->sb); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_tileview_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_scrl: data->scrl = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_sb: data->sb = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_tileview_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_tileview_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_tileview_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_tileview_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_tileview_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_tileview_t_locals_dict, mp_lv_theme_style_tileview_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_tileview_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_tileview_t,
    .print = mp_lv_theme_style_tileview_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_tileview_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_tileview_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_tileview_t_type()
{
    return &mp_lv_theme_style_tileview_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->table ) lv_theme_style_table_t;

/*
 * Struct lv_theme_style_table_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_table_t_type();

STATIC inline lv_theme_style_table_t* mp_write_ptr_lv_theme_style_table_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_table_t_type()));
    return (lv_theme_style_table_t*)self->data;
}

#define mp_write_lv_theme_style_table_t(struct_obj) *mp_write_ptr_lv_theme_style_table_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_table_t(lv_theme_style_table_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_table_t_type(), field);
}

#define mp_read_lv_theme_style_table_t(field) mp_read_ptr_lv_theme_style_table_t(copy_buffer(&field, sizeof(lv_theme_style_table_t)))
#define mp_read_byref_lv_theme_style_table_t(field) mp_read_ptr_lv_theme_style_table_t(&field)

STATIC void mp_lv_theme_style_table_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_table_t *data = (lv_theme_style_table_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_cell: dest[0] = ptr_to_mp((void*)data->cell); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_table_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_cell: data->cell = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_table_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_table_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_table_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_table_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_table_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_table_t_locals_dict, mp_lv_theme_style_table_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_table_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_table_t,
    .print = mp_lv_theme_style_table_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_table_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_table_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_table_t_type()
{
    return &mp_lv_theme_style_table_t_type;
}
    
typedef typeof( ((lv_theme_style_t*)(0))->win ) lv_theme_style_win_t;
typedef typeof( ((lv_theme_style_win_t*)(0))->content ) lv_theme_style_win_content_t;

/*
 * Struct lv_theme_style_win_content_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_win_content_t_type();

STATIC inline lv_theme_style_win_content_t* mp_write_ptr_lv_theme_style_win_content_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_win_content_t_type()));
    return (lv_theme_style_win_content_t*)self->data;
}

#define mp_write_lv_theme_style_win_content_t(struct_obj) *mp_write_ptr_lv_theme_style_win_content_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_win_content_t(lv_theme_style_win_content_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_win_content_t_type(), field);
}

#define mp_read_lv_theme_style_win_content_t(field) mp_read_ptr_lv_theme_style_win_content_t(copy_buffer(&field, sizeof(lv_theme_style_win_content_t)))
#define mp_read_byref_lv_theme_style_win_content_t(field) mp_read_ptr_lv_theme_style_win_content_t(&field)

STATIC void mp_lv_theme_style_win_content_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_win_content_t *data = (lv_theme_style_win_content_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_scrl: dest[0] = ptr_to_mp((void*)data->scrl); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_win_content_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_scrl: data->scrl = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_win_content_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_win_content_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_win_content_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_win_content_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_win_content_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_win_content_t_locals_dict, mp_lv_theme_style_win_content_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_win_content_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_win_content_t,
    .print = mp_lv_theme_style_win_content_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_win_content_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_win_content_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_win_content_t_type()
{
    return &mp_lv_theme_style_win_content_t_type;
}
    
typedef typeof( ((lv_theme_style_win_t*)(0))->btn ) lv_theme_style_win_btn_t;

/*
 * Struct lv_theme_style_win_btn_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_win_btn_t_type();

STATIC inline lv_theme_style_win_btn_t* mp_write_ptr_lv_theme_style_win_btn_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_win_btn_t_type()));
    return (lv_theme_style_win_btn_t*)self->data;
}

#define mp_write_lv_theme_style_win_btn_t(struct_obj) *mp_write_ptr_lv_theme_style_win_btn_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_win_btn_t(lv_theme_style_win_btn_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_win_btn_t_type(), field);
}

#define mp_read_lv_theme_style_win_btn_t(field) mp_read_ptr_lv_theme_style_win_btn_t(copy_buffer(&field, sizeof(lv_theme_style_win_btn_t)))
#define mp_read_byref_lv_theme_style_win_btn_t(field) mp_read_ptr_lv_theme_style_win_btn_t(&field)

STATIC void mp_lv_theme_style_win_btn_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_win_btn_t *data = (lv_theme_style_win_btn_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_rel: dest[0] = ptr_to_mp((void*)data->rel); break; // converting from lv_style_t *;
            case MP_QSTR_pr: dest[0] = ptr_to_mp((void*)data->pr); break; // converting from lv_style_t *;
            default: field_not_found(MP_QSTR_lv_theme_style_win_btn_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_rel: data->rel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_pr: data->pr = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                default: field_not_found(MP_QSTR_lv_theme_style_win_btn_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_win_btn_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_win_btn_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_win_btn_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_win_btn_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_win_btn_t_locals_dict, mp_lv_theme_style_win_btn_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_win_btn_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_win_btn_t,
    .print = mp_lv_theme_style_win_btn_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_win_btn_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_win_btn_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_win_btn_t_type()
{
    return &mp_lv_theme_style_win_btn_t_type;
}
    

/*
 * Struct lv_theme_style_win_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_win_t_type();

STATIC inline lv_theme_style_win_t* mp_write_ptr_lv_theme_style_win_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_win_t_type()));
    return (lv_theme_style_win_t*)self->data;
}

#define mp_write_lv_theme_style_win_t(struct_obj) *mp_write_ptr_lv_theme_style_win_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_win_t(lv_theme_style_win_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_win_t_type(), field);
}

#define mp_read_lv_theme_style_win_t(field) mp_read_ptr_lv_theme_style_win_t(copy_buffer(&field, sizeof(lv_theme_style_win_t)))
#define mp_read_byref_lv_theme_style_win_t(field) mp_read_ptr_lv_theme_style_win_t(&field)

STATIC void mp_lv_theme_style_win_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_win_t *data = (lv_theme_style_win_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_sb: dest[0] = ptr_to_mp((void*)data->sb); break; // converting from lv_style_t *;
            case MP_QSTR_header: dest[0] = ptr_to_mp((void*)data->header); break; // converting from lv_style_t *;
            case MP_QSTR_content: dest[0] = mp_read_byref_lv_theme_style_win_content_t(data->content); break; // converting from lv_theme_style_win_content_t;
            case MP_QSTR_btn: dest[0] = mp_read_byref_lv_theme_style_win_btn_t(data->btn); break; // converting from lv_theme_style_win_btn_t;
            default: field_not_found(MP_QSTR_lv_theme_style_win_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_sb: data->sb = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_header: data->header = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_content: data->content = mp_write_lv_theme_style_win_content_t(dest[1]); break; // converting to lv_theme_style_win_content_t;
                case MP_QSTR_btn: data->btn = mp_write_lv_theme_style_win_btn_t(dest[1]); break; // converting to lv_theme_style_win_btn_t;
                default: field_not_found(MP_QSTR_lv_theme_style_win_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_win_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_win_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_win_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_win_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_win_t_locals_dict, mp_lv_theme_style_win_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_win_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_win_t,
    .print = mp_lv_theme_style_win_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_win_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_win_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_win_t_type()
{
    return &mp_lv_theme_style_win_t_type;
}
    

/*
 * Struct lv_theme_style_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_t_type();

STATIC inline lv_theme_style_t* mp_write_ptr_lv_theme_style_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_style_t_type()));
    return (lv_theme_style_t*)self->data;
}

#define mp_write_lv_theme_style_t(struct_obj) *mp_write_ptr_lv_theme_style_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_style_t(lv_theme_style_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_style_t_type(), field);
}

#define mp_read_lv_theme_style_t(field) mp_read_ptr_lv_theme_style_t(copy_buffer(&field, sizeof(lv_theme_style_t)))
#define mp_read_byref_lv_theme_style_t(field) mp_read_ptr_lv_theme_style_t(&field)

STATIC void mp_lv_theme_style_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_style_t *data = (lv_theme_style_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_bg: dest[0] = ptr_to_mp((void*)data->bg); break; // converting from lv_style_t *;
            case MP_QSTR_panel: dest[0] = ptr_to_mp((void*)data->panel); break; // converting from lv_style_t *;
            case MP_QSTR_cont: dest[0] = ptr_to_mp((void*)data->cont); break; // converting from lv_style_t *;
            case MP_QSTR_btn: dest[0] = mp_read_byref_lv_theme_style_btn_t(data->btn); break; // converting from lv_theme_style_btn_t;
            case MP_QSTR_imgbtn: dest[0] = mp_read_byref_lv_theme_style_imgbtn_t(data->imgbtn); break; // converting from lv_theme_style_imgbtn_t;
            case MP_QSTR_label: dest[0] = mp_read_byref_lv_theme_style_label_t(data->label); break; // converting from lv_theme_style_label_t;
            case MP_QSTR_img: dest[0] = mp_read_byref_lv_theme_style_img_t(data->img); break; // converting from lv_theme_style_img_t;
            case MP_QSTR_line: dest[0] = mp_read_byref_lv_theme_style_line_t(data->line); break; // converting from lv_theme_style_line_t;
            case MP_QSTR_led: dest[0] = ptr_to_mp((void*)data->led); break; // converting from lv_style_t *;
            case MP_QSTR_bar: dest[0] = mp_read_byref_lv_theme_style_bar_t(data->bar); break; // converting from lv_theme_style_bar_t;
            case MP_QSTR_slider: dest[0] = mp_read_byref_lv_theme_style_slider_t(data->slider); break; // converting from lv_theme_style_slider_t;
            case MP_QSTR_lmeter: dest[0] = ptr_to_mp((void*)data->lmeter); break; // converting from lv_style_t *;
            case MP_QSTR_gauge: dest[0] = ptr_to_mp((void*)data->gauge); break; // converting from lv_style_t *;
            case MP_QSTR_arc: dest[0] = ptr_to_mp((void*)data->arc); break; // converting from lv_style_t *;
            case MP_QSTR_preload: dest[0] = ptr_to_mp((void*)data->preload); break; // converting from lv_style_t *;
            case MP_QSTR_sw: dest[0] = mp_read_byref_lv_theme_style_sw_t(data->sw); break; // converting from lv_theme_style_sw_t;
            case MP_QSTR_chart: dest[0] = ptr_to_mp((void*)data->chart); break; // converting from lv_style_t *;
            case MP_QSTR_calendar: dest[0] = mp_read_byref_lv_theme_style_calendar_t(data->calendar); break; // converting from lv_theme_style_calendar_t;
            case MP_QSTR_cb: dest[0] = mp_read_byref_lv_theme_style_cb_t(data->cb); break; // converting from lv_theme_style_cb_t;
            case MP_QSTR_btnm: dest[0] = mp_read_byref_lv_theme_style_btnm_t(data->btnm); break; // converting from lv_theme_style_btnm_t;
            case MP_QSTR_kb: dest[0] = mp_read_byref_lv_theme_style_kb_t(data->kb); break; // converting from lv_theme_style_kb_t;
            case MP_QSTR_mbox: dest[0] = mp_read_byref_lv_theme_style_mbox_t(data->mbox); break; // converting from lv_theme_style_mbox_t;
            case MP_QSTR_page: dest[0] = mp_read_byref_lv_theme_style_page_t(data->page); break; // converting from lv_theme_style_page_t;
            case MP_QSTR_ta: dest[0] = mp_read_byref_lv_theme_style_ta_t(data->ta); break; // converting from lv_theme_style_ta_t;
            case MP_QSTR_spinbox: dest[0] = mp_read_byref_lv_theme_style_spinbox_t(data->spinbox); break; // converting from lv_theme_style_spinbox_t;
            case MP_QSTR_list: dest[0] = mp_read_byref_lv_theme_style_list_t(data->list); break; // converting from lv_theme_style_list_t;
            case MP_QSTR_ddlist: dest[0] = mp_read_byref_lv_theme_style_ddlist_t(data->ddlist); break; // converting from lv_theme_style_ddlist_t;
            case MP_QSTR_roller: dest[0] = mp_read_byref_lv_theme_style_roller_t(data->roller); break; // converting from lv_theme_style_roller_t;
            case MP_QSTR_tabview: dest[0] = mp_read_byref_lv_theme_style_tabview_t(data->tabview); break; // converting from lv_theme_style_tabview_t;
            case MP_QSTR_tileview: dest[0] = mp_read_byref_lv_theme_style_tileview_t(data->tileview); break; // converting from lv_theme_style_tileview_t;
            case MP_QSTR_table: dest[0] = mp_read_byref_lv_theme_style_table_t(data->table); break; // converting from lv_theme_style_table_t;
            case MP_QSTR_win: dest[0] = mp_read_byref_lv_theme_style_win_t(data->win); break; // converting from lv_theme_style_win_t;
            default: field_not_found(MP_QSTR_lv_theme_style_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_bg: data->bg = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_panel: data->panel = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_cont: data->cont = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_btn: data->btn = mp_write_lv_theme_style_btn_t(dest[1]); break; // converting to lv_theme_style_btn_t;
                case MP_QSTR_imgbtn: data->imgbtn = mp_write_lv_theme_style_imgbtn_t(dest[1]); break; // converting to lv_theme_style_imgbtn_t;
                case MP_QSTR_label: data->label = mp_write_lv_theme_style_label_t(dest[1]); break; // converting to lv_theme_style_label_t;
                case MP_QSTR_img: data->img = mp_write_lv_theme_style_img_t(dest[1]); break; // converting to lv_theme_style_img_t;
                case MP_QSTR_line: data->line = mp_write_lv_theme_style_line_t(dest[1]); break; // converting to lv_theme_style_line_t;
                case MP_QSTR_led: data->led = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_bar: data->bar = mp_write_lv_theme_style_bar_t(dest[1]); break; // converting to lv_theme_style_bar_t;
                case MP_QSTR_slider: data->slider = mp_write_lv_theme_style_slider_t(dest[1]); break; // converting to lv_theme_style_slider_t;
                case MP_QSTR_lmeter: data->lmeter = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_gauge: data->gauge = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_arc: data->arc = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_preload: data->preload = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_sw: data->sw = mp_write_lv_theme_style_sw_t(dest[1]); break; // converting to lv_theme_style_sw_t;
                case MP_QSTR_chart: data->chart = (void*)mp_to_ptr(dest[1]); break; // converting to lv_style_t *;
                case MP_QSTR_calendar: data->calendar = mp_write_lv_theme_style_calendar_t(dest[1]); break; // converting to lv_theme_style_calendar_t;
                case MP_QSTR_cb: data->cb = mp_write_lv_theme_style_cb_t(dest[1]); break; // converting to lv_theme_style_cb_t;
                case MP_QSTR_btnm: data->btnm = mp_write_lv_theme_style_btnm_t(dest[1]); break; // converting to lv_theme_style_btnm_t;
                case MP_QSTR_kb: data->kb = mp_write_lv_theme_style_kb_t(dest[1]); break; // converting to lv_theme_style_kb_t;
                case MP_QSTR_mbox: data->mbox = mp_write_lv_theme_style_mbox_t(dest[1]); break; // converting to lv_theme_style_mbox_t;
                case MP_QSTR_page: data->page = mp_write_lv_theme_style_page_t(dest[1]); break; // converting to lv_theme_style_page_t;
                case MP_QSTR_ta: data->ta = mp_write_lv_theme_style_ta_t(dest[1]); break; // converting to lv_theme_style_ta_t;
                case MP_QSTR_spinbox: data->spinbox = mp_write_lv_theme_style_spinbox_t(dest[1]); break; // converting to lv_theme_style_spinbox_t;
                case MP_QSTR_list: data->list = mp_write_lv_theme_style_list_t(dest[1]); break; // converting to lv_theme_style_list_t;
                case MP_QSTR_ddlist: data->ddlist = mp_write_lv_theme_style_ddlist_t(dest[1]); break; // converting to lv_theme_style_ddlist_t;
                case MP_QSTR_roller: data->roller = mp_write_lv_theme_style_roller_t(dest[1]); break; // converting to lv_theme_style_roller_t;
                case MP_QSTR_tabview: data->tabview = mp_write_lv_theme_style_tabview_t(dest[1]); break; // converting to lv_theme_style_tabview_t;
                case MP_QSTR_tileview: data->tileview = mp_write_lv_theme_style_tileview_t(dest[1]); break; // converting to lv_theme_style_tileview_t;
                case MP_QSTR_table: data->table = mp_write_lv_theme_style_table_t(dest[1]); break; // converting to lv_theme_style_table_t;
                case MP_QSTR_win: data->win = mp_write_lv_theme_style_win_t(dest[1]); break; // converting to lv_theme_style_win_t;
                default: field_not_found(MP_QSTR_lv_theme_style_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_style_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_style_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_style_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_style_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_style_t_locals_dict, mp_lv_theme_style_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_style_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_style_t,
    .print = mp_lv_theme_style_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_style_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_style_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_style_t_type()
{
    return &mp_lv_theme_style_t_type;
}
    
typedef typeof( ((lv_theme_t*)(0))->group ) lv_theme_group_t;
STATIC void style_mod_cb_callback(struct _lv_group_t *, lv_style_t *);
STATIC void style_mod_edit_cb_callback(struct _lv_group_t *, lv_style_t *);

/*
 * Struct lv_theme_group_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_group_t_type();

STATIC inline lv_theme_group_t* mp_write_ptr_lv_theme_group_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_group_t_type()));
    return (lv_theme_group_t*)self->data;
}

#define mp_write_lv_theme_group_t(struct_obj) *mp_write_ptr_lv_theme_group_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_group_t(lv_theme_group_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_group_t_type(), field);
}

#define mp_read_lv_theme_group_t(field) mp_read_ptr_lv_theme_group_t(copy_buffer(&field, sizeof(lv_theme_group_t)))
#define mp_read_byref_lv_theme_group_t(field) mp_read_ptr_lv_theme_group_t(&field)

STATIC void mp_lv_theme_group_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_group_t *data = (lv_theme_group_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_style_mod_cb: dest[0] = ptr_to_mp(data->style_mod_cb); break; // converting from lv_group_style_mod_cb_t;
            case MP_QSTR_style_mod_edit_cb: dest[0] = ptr_to_mp(data->style_mod_edit_cb); break; // converting from lv_group_style_mod_cb_t;
            default: field_not_found(MP_QSTR_lv_theme_group_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_style_mod_cb: data->style_mod_cb = mp_lv_callback(dest[1], NULL ,MP_QSTR_style_mod_cb, NULL); break; // converting to lv_group_style_mod_cb_t;
                case MP_QSTR_style_mod_edit_cb: data->style_mod_edit_cb = mp_lv_callback(dest[1], NULL ,MP_QSTR_style_mod_edit_cb, NULL); break; // converting to lv_group_style_mod_cb_t;
                default: field_not_found(MP_QSTR_lv_theme_group_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_group_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_group_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_group_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_group_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_group_t_locals_dict, mp_lv_theme_group_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_group_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_group_t,
    .print = mp_lv_theme_group_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_group_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_group_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_group_t_type()
{
    return &mp_lv_theme_group_t_type;
}
    

/*
 * Struct lv_theme_t
 */

STATIC inline const mp_obj_type_t *get_mp_lv_theme_t_type();

STATIC inline lv_theme_t* mp_write_ptr_lv_theme_t(mp_obj_t self_in)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(cast(self_in, get_mp_lv_theme_t_type()));
    return (lv_theme_t*)self->data;
}

#define mp_write_lv_theme_t(struct_obj) *mp_write_ptr_lv_theme_t(struct_obj)

STATIC inline mp_obj_t mp_read_ptr_lv_theme_t(lv_theme_t *field)
{
    return lv_to_mp_struct(get_mp_lv_theme_t_type(), field);
}

#define mp_read_lv_theme_t(field) mp_read_ptr_lv_theme_t(copy_buffer(&field, sizeof(lv_theme_t)))
#define mp_read_byref_lv_theme_t(field) mp_read_ptr_lv_theme_t(&field)

STATIC void mp_lv_theme_t_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest)
{
    mp_lv_struct_t *self = MP_OBJ_TO_PTR(self_in);
    lv_theme_t *data = (lv_theme_t*)self->data;

    if (dest[0] == MP_OBJ_NULL) {
        // load attribute
        switch(attr)
        {
            case MP_QSTR_style: dest[0] = mp_read_byref_lv_theme_style_t(data->style); break; // converting from lv_theme_style_t;
            case MP_QSTR_group: dest[0] = mp_read_byref_lv_theme_group_t(data->group); break; // converting from lv_theme_group_t;
            default: field_not_found(MP_QSTR_lv_theme_t, attr);
        }
    } else {
        if (dest[1])
        {
            // store attribute
            switch(attr)
            {
                case MP_QSTR_style: data->style = mp_write_lv_theme_style_t(dest[1]); break; // converting to lv_theme_style_t;
                case MP_QSTR_group: data->group = mp_write_lv_theme_group_t(dest[1]); break; // converting to lv_theme_group_t;
                default: field_not_found(MP_QSTR_lv_theme_t, attr);
            }

            dest[0] = MP_OBJ_NULL; // indicate success
        }
    }
}

STATIC void mp_lv_theme_t_print(const mp_print_t *print,
    mp_obj_t self_in,
    mp_print_kind_t kind)
{
    mp_printf(print, "lvgl struct lv_theme_t");
}

STATIC const mp_rom_map_elem_t mp_lv_theme_t_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SIZE), MP_ROM_PTR(MP_ROM_INT(sizeof(lv_theme_t))) },
    { MP_ROM_QSTR(MP_QSTR_cast), MP_ROM_PTR(&mp_lv_cast_class_method) },
};

STATIC MP_DEFINE_CONST_DICT(mp_lv_theme_t_locals_dict, mp_lv_theme_t_locals_dict_table);

STATIC const mp_obj_type_t mp_lv_theme_t_type = {
    { &mp_type_type },
    .name = MP_QSTR_lv_theme_t,
    .print = mp_lv_theme_t_print,
    .make_new = make_new_lv_struct,
    .attr = mp_lv_theme_t_attr,
    .locals_dict = (mp_obj_dict_t*)&mp_lv_theme_t_locals_dict,
    .buffer_p = { .get_buffer = mp_blob_get_buffer }
};

STATIC inline const mp_obj_type_t *get_mp_lv_theme_t_type()
{
    return &mp_lv_theme_t_type;
}
    

/*
 * lvgl extension definition for:
 * void lv_theme_set_current(lv_theme_t *th)
 */
 
STATIC mp_obj_t mp_lv_theme_set_current(size_t n_args, const mp_obj_t *args)
{
    lv_theme_t *th = mp_to_ptr(args[0]);
    lv_theme_set_current(th);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_set_current_obj, 1, 1, mp_lv_theme_set_current);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_get_current(void)
 */
 
STATIC mp_obj_t mp_lv_theme_get_current(size_t n_args, const mp_obj_t *args)
{
    
    lv_theme_t * res = lv_theme_get_current();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_get_current_obj, 0, 0, mp_lv_theme_get_current);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_templ_init(uint16_t hue, lv_font_t *font)
 */
 
STATIC mp_obj_t mp_lv_theme_templ_init(size_t n_args, const mp_obj_t *args)
{
    uint16_t hue = (uint16_t)mp_obj_get_int(args[0]);
    lv_font_t *font = mp_to_ptr(args[1]);
    lv_theme_t * res = lv_theme_templ_init(hue, font);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_templ_init_obj, 2, 2, mp_lv_theme_templ_init);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_get_templ(void)
 */
 
STATIC mp_obj_t mp_lv_theme_get_templ(size_t n_args, const mp_obj_t *args)
{
    
    lv_theme_t * res = lv_theme_get_templ();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_get_templ_obj, 0, 0, mp_lv_theme_get_templ);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_default_init(uint16_t hue, lv_font_t *font)
 */
 
STATIC mp_obj_t mp_lv_theme_default_init(size_t n_args, const mp_obj_t *args)
{
    uint16_t hue = (uint16_t)mp_obj_get_int(args[0]);
    lv_font_t *font = mp_to_ptr(args[1]);
    lv_theme_t * res = lv_theme_default_init(hue, font);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_default_init_obj, 2, 2, mp_lv_theme_default_init);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_get_default(void)
 */
 
STATIC mp_obj_t mp_lv_theme_get_default(size_t n_args, const mp_obj_t *args)
{
    
    lv_theme_t * res = lv_theme_get_default();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_get_default_obj, 0, 0, mp_lv_theme_get_default);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_alien_init(uint16_t hue, lv_font_t *font)
 */
 
STATIC mp_obj_t mp_lv_theme_alien_init(size_t n_args, const mp_obj_t *args)
{
    uint16_t hue = (uint16_t)mp_obj_get_int(args[0]);
    lv_font_t *font = mp_to_ptr(args[1]);
    lv_theme_t * res = lv_theme_alien_init(hue, font);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_alien_init_obj, 2, 2, mp_lv_theme_alien_init);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_get_alien(void)
 */
 
STATIC mp_obj_t mp_lv_theme_get_alien(size_t n_args, const mp_obj_t *args)
{
    
    lv_theme_t * res = lv_theme_get_alien();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_get_alien_obj, 0, 0, mp_lv_theme_get_alien);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_night_init(uint16_t hue, lv_font_t *font)
 */
 
STATIC mp_obj_t mp_lv_theme_night_init(size_t n_args, const mp_obj_t *args)
{
    uint16_t hue = (uint16_t)mp_obj_get_int(args[0]);
    lv_font_t *font = mp_to_ptr(args[1]);
    lv_theme_t * res = lv_theme_night_init(hue, font);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_night_init_obj, 2, 2, mp_lv_theme_night_init);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_get_night(void)
 */
 
STATIC mp_obj_t mp_lv_theme_get_night(size_t n_args, const mp_obj_t *args)
{
    
    lv_theme_t * res = lv_theme_get_night();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_get_night_obj, 0, 0, mp_lv_theme_get_night);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_zen_init(uint16_t hue, lv_font_t *font)
 */
 
STATIC mp_obj_t mp_lv_theme_zen_init(size_t n_args, const mp_obj_t *args)
{
    uint16_t hue = (uint16_t)mp_obj_get_int(args[0]);
    lv_font_t *font = mp_to_ptr(args[1]);
    lv_theme_t * res = lv_theme_zen_init(hue, font);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_zen_init_obj, 2, 2, mp_lv_theme_zen_init);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_get_zen(void)
 */
 
STATIC mp_obj_t mp_lv_theme_get_zen(size_t n_args, const mp_obj_t *args)
{
    
    lv_theme_t * res = lv_theme_get_zen();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_get_zen_obj, 0, 0, mp_lv_theme_get_zen);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_mono_init(uint16_t hue, lv_font_t *font)
 */
 
STATIC mp_obj_t mp_lv_theme_mono_init(size_t n_args, const mp_obj_t *args)
{
    uint16_t hue = (uint16_t)mp_obj_get_int(args[0]);
    lv_font_t *font = mp_to_ptr(args[1]);
    lv_theme_t * res = lv_theme_mono_init(hue, font);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_mono_init_obj, 2, 2, mp_lv_theme_mono_init);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_get_mono(void)
 */
 
STATIC mp_obj_t mp_lv_theme_get_mono(size_t n_args, const mp_obj_t *args)
{
    
    lv_theme_t * res = lv_theme_get_mono();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_get_mono_obj, 0, 0, mp_lv_theme_get_mono);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_nemo_init(uint16_t hue, lv_font_t *font)
 */
 
STATIC mp_obj_t mp_lv_theme_nemo_init(size_t n_args, const mp_obj_t *args)
{
    uint16_t hue = (uint16_t)mp_obj_get_int(args[0]);
    lv_font_t *font = mp_to_ptr(args[1]);
    lv_theme_t * res = lv_theme_nemo_init(hue, font);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_nemo_init_obj, 2, 2, mp_lv_theme_nemo_init);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_get_nemo(void)
 */
 
STATIC mp_obj_t mp_lv_theme_get_nemo(size_t n_args, const mp_obj_t *args)
{
    
    lv_theme_t * res = lv_theme_get_nemo();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_get_nemo_obj, 0, 0, mp_lv_theme_get_nemo);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_material_init(uint16_t hue, lv_font_t *font)
 */
 
STATIC mp_obj_t mp_lv_theme_material_init(size_t n_args, const mp_obj_t *args)
{
    uint16_t hue = (uint16_t)mp_obj_get_int(args[0]);
    lv_font_t *font = mp_to_ptr(args[1]);
    lv_theme_t * res = lv_theme_material_init(hue, font);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_material_init_obj, 2, 2, mp_lv_theme_material_init);

 

/*
 * lvgl extension definition for:
 * lv_theme_t *lv_theme_get_material(void)
 */
 
STATIC mp_obj_t mp_lv_theme_get_material(size_t n_args, const mp_obj_t *args)
{
    
    lv_theme_t * res = lv_theme_get_material();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_theme_get_material_obj, 0, 0, mp_lv_theme_get_material);

 

/*
 * lvgl extension definition for:
 * void lv_indev_init(void)
 */
 
STATIC mp_obj_t mp_lv_indev_init(size_t n_args, const mp_obj_t *args)
{
    
    lv_indev_init();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_init_obj, 0, 0, mp_lv_indev_init);

 

/*
 * lvgl extension definition for:
 * void lv_indev_read_task(lv_task_t *task)
 */
 
STATIC mp_obj_t mp_lv_indev_read_task(size_t n_args, const mp_obj_t *args)
{
    lv_task_t *task = mp_to_ptr(args[0]);
    lv_indev_read_task(task);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_read_task_obj, 1, 1, mp_lv_indev_read_task);

 

/*
 * lvgl extension definition for:
 * lv_indev_t *lv_indev_get_act(void)
 */
 
STATIC mp_obj_t mp_lv_indev_get_act(size_t n_args, const mp_obj_t *args)
{
    
    lv_indev_t * res = lv_indev_get_act();
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_get_act_obj, 0, 0, mp_lv_indev_get_act);

 

/*
 * lvgl extension definition for:
 * lv_indev_type_t lv_indev_get_type(const lv_indev_t *indev)
 */
 
STATIC mp_obj_t mp_lv_indev_get_type(size_t n_args, const mp_obj_t *args)
{
    const lv_indev_t *indev = mp_to_ptr(args[0]);
    lv_indev_type_t res = lv_indev_get_type(indev);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_get_type_obj, 1, 1, mp_lv_indev_get_type);

 

/*
 * lvgl extension definition for:
 * void lv_indev_reset(lv_indev_t *indev)
 */
 
STATIC mp_obj_t mp_lv_indev_reset(size_t n_args, const mp_obj_t *args)
{
    lv_indev_t *indev = mp_to_ptr(args[0]);
    lv_indev_reset(indev);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_reset_obj, 1, 1, mp_lv_indev_reset);

 

/*
 * lvgl extension definition for:
 * void lv_indev_reset_long_press(lv_indev_t *indev)
 */
 
STATIC mp_obj_t mp_lv_indev_reset_long_press(size_t n_args, const mp_obj_t *args)
{
    lv_indev_t *indev = mp_to_ptr(args[0]);
    lv_indev_reset_long_press(indev);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_reset_long_press_obj, 1, 1, mp_lv_indev_reset_long_press);

 

/*
 * lvgl extension definition for:
 * void lv_indev_enable(lv_indev_t *indev, bool en)
 */
 
STATIC mp_obj_t mp_lv_indev_enable(size_t n_args, const mp_obj_t *args)
{
    lv_indev_t *indev = mp_to_ptr(args[0]);
    bool en = mp_obj_is_true(args[1]);
    lv_indev_enable(indev, en);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_enable_obj, 2, 2, mp_lv_indev_enable);

 

/*
 * lvgl extension definition for:
 * void lv_indev_set_cursor(lv_indev_t *indev, lv_obj_t *cur_obj)
 */
 
STATIC mp_obj_t mp_lv_indev_set_cursor(size_t n_args, const mp_obj_t *args)
{
    lv_indev_t *indev = mp_to_ptr(args[0]);
    lv_obj_t *cur_obj = mp_to_lv(args[1]);
    lv_indev_set_cursor(indev, cur_obj);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_set_cursor_obj, 2, 2, mp_lv_indev_set_cursor);

 

/*
 * lvgl extension definition for:
 * void lv_indev_set_group(lv_indev_t *indev, lv_group_t *group)
 */
 
STATIC mp_obj_t mp_lv_indev_set_group(size_t n_args, const mp_obj_t *args)
{
    lv_indev_t *indev = mp_to_ptr(args[0]);
    lv_group_t *group = mp_to_ptr(args[1]);
    lv_indev_set_group(indev, group);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_set_group_obj, 2, 2, mp_lv_indev_set_group);

 

/*
 * lvgl extension definition for:
 * void lv_indev_set_button_points(lv_indev_t *indev, const lv_point_t *points)
 */
 
STATIC mp_obj_t mp_lv_indev_set_button_points(size_t n_args, const mp_obj_t *args)
{
    lv_indev_t *indev = mp_to_ptr(args[0]);
    const lv_point_t *points = mp_to_ptr(args[1]);
    lv_indev_set_button_points(indev, points);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_set_button_points_obj, 2, 2, mp_lv_indev_set_button_points);

 

/*
 * lvgl extension definition for:
 * void lv_indev_get_point(const lv_indev_t *indev, lv_point_t *point)
 */
 
STATIC mp_obj_t mp_lv_indev_get_point(size_t n_args, const mp_obj_t *args)
{
    const lv_indev_t *indev = mp_to_ptr(args[0]);
    lv_point_t *point = mp_to_ptr(args[1]);
    lv_indev_get_point(indev, point);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_get_point_obj, 2, 2, mp_lv_indev_get_point);

 

/*
 * lvgl extension definition for:
 * uint32_t lv_indev_get_key(const lv_indev_t *indev)
 */
 
STATIC mp_obj_t mp_lv_indev_get_key(size_t n_args, const mp_obj_t *args)
{
    const lv_indev_t *indev = mp_to_ptr(args[0]);
    uint32_t res = lv_indev_get_key(indev);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_get_key_obj, 1, 1, mp_lv_indev_get_key);

 

/*
 * lvgl extension definition for:
 * bool lv_indev_is_dragging(const lv_indev_t *indev)
 */
 
STATIC mp_obj_t mp_lv_indev_is_dragging(size_t n_args, const mp_obj_t *args)
{
    const lv_indev_t *indev = mp_to_ptr(args[0]);
    bool res = lv_indev_is_dragging(indev);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_is_dragging_obj, 1, 1, mp_lv_indev_is_dragging);

 

/*
 * lvgl extension definition for:
 * void lv_indev_get_vect(const lv_indev_t *indev, lv_point_t *point)
 */
 
STATIC mp_obj_t mp_lv_indev_get_vect(size_t n_args, const mp_obj_t *args)
{
    const lv_indev_t *indev = mp_to_ptr(args[0]);
    lv_point_t *point = mp_to_ptr(args[1]);
    lv_indev_get_vect(indev, point);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_get_vect_obj, 2, 2, mp_lv_indev_get_vect);

 

/*
 * lvgl extension definition for:
 * void lv_indev_wait_release(lv_indev_t *indev)
 */
 
STATIC mp_obj_t mp_lv_indev_wait_release(size_t n_args, const mp_obj_t *args)
{
    lv_indev_t *indev = mp_to_ptr(args[0]);
    lv_indev_wait_release(indev);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_wait_release_obj, 1, 1, mp_lv_indev_wait_release);

 

/*
 * lvgl extension definition for:
 * lv_task_t *lv_indev_get_read_task(lv_disp_t *indev)
 */
 
STATIC mp_obj_t mp_lv_indev_get_read_task(size_t n_args, const mp_obj_t *args)
{
    lv_disp_t *indev = mp_to_ptr(args[0]);
    lv_task_t * res = lv_indev_get_read_task(indev);
    return ptr_to_mp((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_indev_get_read_task_obj, 1, 1, mp_lv_indev_get_read_task);

 

/*
 * lvgl extension definition for:
 * void lv_txt_get_size(lv_point_t *size_res, const char *text, const lv_font_t *font, lv_coord_t letter_space, lv_coord_t line_space, lv_coord_t max_width, lv_txt_flag_t flag)
 */
 
STATIC mp_obj_t mp_lv_txt_get_size(size_t n_args, const mp_obj_t *args)
{
    lv_point_t *size_res = mp_to_ptr(args[0]);
    const char *text = (char*)mp_obj_str_get_str(args[1]);
    const lv_font_t *font = mp_to_ptr(args[2]);
    lv_coord_t letter_space = (int16_t)mp_obj_get_int(args[3]);
    lv_coord_t line_space = (int16_t)mp_obj_get_int(args[4]);
    lv_coord_t max_width = (int16_t)mp_obj_get_int(args[5]);
    lv_txt_flag_t flag = (uint8_t)mp_obj_get_int(args[6]);
    lv_txt_get_size(size_res, text, font, letter_space, line_space, max_width, flag);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_txt_get_size_obj, 7, 7, mp_lv_txt_get_size);

 

/*
 * lvgl extension definition for:
 * uint16_t lv_txt_get_next_line(const char *txt, const lv_font_t *font, lv_coord_t letter_space, lv_coord_t max_width, lv_txt_flag_t flag)
 */
 
STATIC mp_obj_t mp_lv_txt_get_next_line(size_t n_args, const mp_obj_t *args)
{
    const char *txt = (char*)mp_obj_str_get_str(args[0]);
    const lv_font_t *font = mp_to_ptr(args[1]);
    lv_coord_t letter_space = (int16_t)mp_obj_get_int(args[2]);
    lv_coord_t max_width = (int16_t)mp_obj_get_int(args[3]);
    lv_txt_flag_t flag = (uint8_t)mp_obj_get_int(args[4]);
    uint16_t res = lv_txt_get_next_line(txt, font, letter_space, max_width, flag);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_txt_get_next_line_obj, 5, 5, mp_lv_txt_get_next_line);

 

/*
 * lvgl extension definition for:
 * lv_coord_t lv_txt_get_width(const char *txt, uint16_t length, const lv_font_t *font, lv_coord_t letter_space, lv_txt_flag_t flag)
 */
 
STATIC mp_obj_t mp_lv_txt_get_width(size_t n_args, const mp_obj_t *args)
{
    const char *txt = (char*)mp_obj_str_get_str(args[0]);
    uint16_t length = (uint16_t)mp_obj_get_int(args[1]);
    const lv_font_t *font = mp_to_ptr(args[2]);
    lv_coord_t letter_space = (int16_t)mp_obj_get_int(args[3]);
    lv_txt_flag_t flag = (uint8_t)mp_obj_get_int(args[4]);
    lv_coord_t res = lv_txt_get_width(txt, length, font, letter_space, flag);
    return mp_obj_new_int(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_txt_get_width_obj, 5, 5, mp_lv_txt_get_width);

 

/*
 * lvgl extension definition for:
 * bool lv_txt_is_cmd(lv_txt_cmd_state_t *state, uint32_t c)
 */
 
STATIC mp_obj_t mp_lv_txt_is_cmd(size_t n_args, const mp_obj_t *args)
{
    lv_txt_cmd_state_t *state = mp_to_ptr(args[0]);
    uint32_t c = (uint32_t)mp_obj_get_int(args[1]);
    bool res = lv_txt_is_cmd(state, c);
    return convert_to_bool(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_txt_is_cmd_obj, 2, 2, mp_lv_txt_is_cmd);

 

/*
 * lvgl extension definition for:
 * void lv_txt_ins(char *txt_buf, uint32_t pos, const char *ins_txt)
 */
 
STATIC mp_obj_t mp_lv_txt_ins(size_t n_args, const mp_obj_t *args)
{
    char *txt_buf = (char*)mp_obj_str_get_str(args[0]);
    uint32_t pos = (uint32_t)mp_obj_get_int(args[1]);
    const char *ins_txt = (char*)mp_obj_str_get_str(args[2]);
    lv_txt_ins(txt_buf, pos, ins_txt);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_txt_ins_obj, 3, 3, mp_lv_txt_ins);

 

/*
 * lvgl extension definition for:
 * void lv_txt_cut(char *txt, uint32_t pos, uint32_t len)
 */
 
STATIC mp_obj_t mp_lv_txt_cut(size_t n_args, const mp_obj_t *args)
{
    char *txt = (char*)mp_obj_str_get_str(args[0]);
    uint32_t pos = (uint32_t)mp_obj_get_int(args[1]);
    uint32_t len = (uint32_t)mp_obj_get_int(args[2]);
    lv_txt_cut(txt, pos, len);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_txt_cut_obj, 3, 3, mp_lv_txt_cut);

 

/*
 * lvgl extension definition for:
 * lv_opa_t lv_draw_aa_get_opa(lv_coord_t seg, lv_coord_t px_id, lv_opa_t base_opa)
 */
 
STATIC mp_obj_t mp_lv_draw_aa_get_opa(size_t n_args, const mp_obj_t *args)
{
    lv_coord_t seg = (int16_t)mp_obj_get_int(args[0]);
    lv_coord_t px_id = (int16_t)mp_obj_get_int(args[1]);
    lv_opa_t base_opa = (uint8_t)mp_obj_get_int(args[2]);
    lv_opa_t res = lv_draw_aa_get_opa(seg, px_id, base_opa);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_draw_aa_get_opa_obj, 3, 3, mp_lv_draw_aa_get_opa);

 

/*
 * lvgl extension definition for:
 * void lv_draw_aa_ver_seg(lv_coord_t x, lv_coord_t y, lv_coord_t length, const lv_area_t *mask, lv_color_t color, lv_opa_t opa)
 */
 
STATIC mp_obj_t mp_lv_draw_aa_ver_seg(size_t n_args, const mp_obj_t *args)
{
    lv_coord_t x = (int16_t)mp_obj_get_int(args[0]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t length = (int16_t)mp_obj_get_int(args[2]);
    const lv_area_t *mask = mp_to_ptr(args[3]);
    lv_color_t color = mp_write_lv_color32_t(args[4]);
    lv_opa_t opa = (uint8_t)mp_obj_get_int(args[5]);
    lv_draw_aa_ver_seg(x, y, length, mask, color, opa);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_draw_aa_ver_seg_obj, 6, 6, mp_lv_draw_aa_ver_seg);

 

/*
 * lvgl extension definition for:
 * void lv_draw_aa_hor_seg(lv_coord_t x, lv_coord_t y, lv_coord_t length, const lv_area_t *mask, lv_color_t color, lv_opa_t opa)
 */
 
STATIC mp_obj_t mp_lv_draw_aa_hor_seg(size_t n_args, const mp_obj_t *args)
{
    lv_coord_t x = (int16_t)mp_obj_get_int(args[0]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[1]);
    lv_coord_t length = (int16_t)mp_obj_get_int(args[2]);
    const lv_area_t *mask = mp_to_ptr(args[3]);
    lv_color_t color = mp_write_lv_color32_t(args[4]);
    lv_opa_t opa = (uint8_t)mp_obj_get_int(args[5]);
    lv_draw_aa_hor_seg(x, y, length, mask, color, opa);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_draw_aa_hor_seg_obj, 6, 6, mp_lv_draw_aa_hor_seg);

 

/*
 * lvgl extension definition for:
 * void lv_draw_px(lv_coord_t x, lv_coord_t y, const lv_area_t *mask_p, lv_color_t color, lv_opa_t opa)
 */
 
STATIC mp_obj_t mp_lv_draw_px(size_t n_args, const mp_obj_t *args)
{
    lv_coord_t x = (int16_t)mp_obj_get_int(args[0]);
    lv_coord_t y = (int16_t)mp_obj_get_int(args[1]);
    const lv_area_t *mask_p = mp_to_ptr(args[2]);
    lv_color_t color = mp_write_lv_color32_t(args[3]);
    lv_opa_t opa = (uint8_t)mp_obj_get_int(args[4]);
    lv_draw_px(x, y, mask_p, color, opa);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_draw_px_obj, 5, 5, mp_lv_draw_px);

 

/*
 * lvgl extension definition for:
 * void lv_draw_fill(const lv_area_t *cords_p, const lv_area_t *mask_p, lv_color_t color, lv_opa_t opa)
 */
 
STATIC mp_obj_t mp_lv_draw_fill(size_t n_args, const mp_obj_t *args)
{
    const lv_area_t *cords_p = mp_to_ptr(args[0]);
    const lv_area_t *mask_p = mp_to_ptr(args[1]);
    lv_color_t color = mp_write_lv_color32_t(args[2]);
    lv_opa_t opa = (uint8_t)mp_obj_get_int(args[3]);
    lv_draw_fill(cords_p, mask_p, color, opa);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_draw_fill_obj, 4, 4, mp_lv_draw_fill);

 

/*
 * lvgl extension definition for:
 * void lv_draw_letter(const lv_point_t *pos_p, const lv_area_t *mask_p, const lv_font_t *font_p, uint32_t letter, lv_color_t color, lv_opa_t opa)
 */
 
STATIC mp_obj_t mp_lv_draw_letter(size_t n_args, const mp_obj_t *args)
{
    const lv_point_t *pos_p = mp_to_ptr(args[0]);
    const lv_area_t *mask_p = mp_to_ptr(args[1]);
    const lv_font_t *font_p = mp_to_ptr(args[2]);
    uint32_t letter = (uint32_t)mp_obj_get_int(args[3]);
    lv_color_t color = mp_write_lv_color32_t(args[4]);
    lv_opa_t opa = (uint8_t)mp_obj_get_int(args[5]);
    lv_draw_letter(pos_p, mask_p, font_p, letter, color, opa);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_draw_letter_obj, 6, 6, mp_lv_draw_letter);

 

/*
 * lvgl extension definition for:
 * void lv_draw_map(const lv_area_t *cords_p, const lv_area_t *mask_p, const uint8_t *map_p, lv_opa_t opa, bool chroma_key, bool alpha_byte, lv_color_t recolor, lv_opa_t recolor_opa)
 */
 
STATIC mp_obj_t mp_lv_draw_map(size_t n_args, const mp_obj_t *args)
{
    const lv_area_t *cords_p = mp_to_ptr(args[0]);
    const lv_area_t *mask_p = mp_to_ptr(args[1]);
    const uint8_t *map_p = mp_to_ptr(args[2]);
    lv_opa_t opa = (uint8_t)mp_obj_get_int(args[3]);
    bool chroma_key = mp_obj_is_true(args[4]);
    bool alpha_byte = mp_obj_is_true(args[5]);
    lv_color_t recolor = mp_write_lv_color32_t(args[6]);
    lv_opa_t recolor_opa = (uint8_t)mp_obj_get_int(args[7]);
    lv_draw_map(cords_p, mask_p, map_p, opa, chroma_key, alpha_byte, recolor, recolor_opa);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_draw_map_obj, 8, 8, mp_lv_draw_map);

 

/*
 * lvgl extension definition for:
 * void lv_draw_rect(const lv_area_t *coords, const lv_area_t *mask, const lv_style_t *style, lv_opa_t opa_scale)
 */
 
STATIC mp_obj_t mp_lv_draw_rect(size_t n_args, const mp_obj_t *args)
{
    const lv_area_t *coords = mp_to_ptr(args[0]);
    const lv_area_t *mask = mp_to_ptr(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_opa_t opa_scale = (uint8_t)mp_obj_get_int(args[3]);
    lv_draw_rect(coords, mask, style, opa_scale);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_draw_rect_obj, 4, 4, mp_lv_draw_rect);

 

/*
 * lvgl extension definition for:
 * void lv_draw_label(const lv_area_t *coords, const lv_area_t *mask, const lv_style_t *style, lv_opa_t opa_scale, const char *txt, lv_txt_flag_t flag, lv_point_t *offset, uint16_t sel_start, uint16_t sel_end)
 */
 
STATIC mp_obj_t mp_lv_draw_label(size_t n_args, const mp_obj_t *args)
{
    const lv_area_t *coords = mp_to_ptr(args[0]);
    const lv_area_t *mask = mp_to_ptr(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_opa_t opa_scale = (uint8_t)mp_obj_get_int(args[3]);
    const char *txt = (char*)mp_obj_str_get_str(args[4]);
    lv_txt_flag_t flag = (uint8_t)mp_obj_get_int(args[5]);
    lv_point_t *offset = mp_to_ptr(args[6]);
    uint16_t sel_start = (uint16_t)mp_obj_get_int(args[7]);
    uint16_t sel_end = (uint16_t)mp_obj_get_int(args[8]);
    lv_draw_label(coords, mask, style, opa_scale, txt, flag, offset, sel_start, sel_end);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_draw_label_obj, 9, 9, mp_lv_draw_label);

 

/*
 * lvgl extension definition for:
 * void lv_draw_line(const lv_point_t *point1, const lv_point_t *point2, const lv_area_t *mask, const lv_style_t *style, lv_opa_t opa_scale)
 */
 
STATIC mp_obj_t mp_lv_draw_line(size_t n_args, const mp_obj_t *args)
{
    const lv_point_t *point1 = mp_to_ptr(args[0]);
    const lv_point_t *point2 = mp_to_ptr(args[1]);
    const lv_area_t *mask = mp_to_ptr(args[2]);
    const lv_style_t *style = mp_to_ptr(args[3]);
    lv_opa_t opa_scale = (uint8_t)mp_obj_get_int(args[4]);
    lv_draw_line(point1, point2, mask, style, opa_scale);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_draw_line_obj, 5, 5, mp_lv_draw_line);

 

/*
 * lvgl extension definition for:
 * void lv_draw_triangle(const lv_point_t *points, const lv_area_t *mask, const lv_style_t *style, lv_opa_t opa_scale)
 */
 
STATIC mp_obj_t mp_lv_draw_triangle(size_t n_args, const mp_obj_t *args)
{
    const lv_point_t *points = mp_to_ptr(args[0]);
    const lv_area_t *mask = mp_to_ptr(args[1]);
    const lv_style_t *style = mp_to_ptr(args[2]);
    lv_opa_t opa_scale = (uint8_t)mp_obj_get_int(args[3]);
    lv_draw_triangle(points, mask, style, opa_scale);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_draw_triangle_obj, 4, 4, mp_lv_draw_triangle);

 

/*
 * lvgl extension definition for:
 * void lv_draw_img(const lv_area_t *coords, const lv_area_t *mask, const void *src, const lv_style_t *style, lv_opa_t opa_scale)
 */
 
STATIC mp_obj_t mp_lv_draw_img(size_t n_args, const mp_obj_t *args)
{
    const lv_area_t *coords = mp_to_ptr(args[0]);
    const lv_area_t *mask = mp_to_ptr(args[1]);
    const void *src = mp_to_ptr(args[2]);
    const lv_style_t *style = mp_to_ptr(args[3]);
    lv_opa_t opa_scale = (uint8_t)mp_obj_get_int(args[4]);
    lv_draw_img(coords, mask, src, style, opa_scale);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_draw_img_obj, 5, 5, mp_lv_draw_img);

 

/*
 * lvgl extension definition for:
 * void lv_fs_init(void)
 */
 
STATIC mp_obj_t mp_lv_fs_init(size_t n_args, const mp_obj_t *args)
{
    
    lv_fs_init();
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_fs_init_obj, 0, 0, mp_lv_fs_init);

 

/*
 * Function NOT generated:
 * Missing conversion to char when generating struct lv_fs_drv_t.letter
 * void lv_fs_add_drv(lv_fs_drv_t *drv_p)
 */
    

/*
 * Function NOT generated:
 * Missing conversion to char
 * bool lv_fs_is_ready(char letter)
 */
    

/*
 * Function NOT generated:
 * Missing conversion to char when generating struct lv_fs_drv_t.letter
 * lv_fs_res_t lv_fs_open(lv_fs_file_t *file_p, const char *path, lv_fs_mode_t mode)
 */
    

/*
 * Function NOT generated:
 * Missing conversion to char when generating struct lv_fs_drv_t.letter
 * lv_fs_res_t lv_fs_close(lv_fs_file_t *file_p)
 */
    

/*
 * lvgl extension definition for:
 * lv_fs_res_t lv_fs_remove(const char *path)
 */
 
STATIC mp_obj_t mp_lv_fs_remove(size_t n_args, const mp_obj_t *args)
{
    const char *path = (char*)mp_obj_str_get_str(args[0]);
    lv_fs_res_t res = lv_fs_remove(path);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_fs_remove_obj, 1, 1, mp_lv_fs_remove);

 

/*
 * Function NOT generated:
 * Missing conversion to char when generating struct lv_fs_drv_t.letter
 * lv_fs_res_t lv_fs_read(lv_fs_file_t *file_p, void *buf, uint32_t btr, uint32_t *br)
 */
    

/*
 * Function NOT generated:
 * Missing conversion to char when generating struct lv_fs_drv_t.letter
 * lv_fs_res_t lv_fs_write(lv_fs_file_t *file_p, const void *buf, uint32_t btw, uint32_t *bw)
 */
    

/*
 * Function NOT generated:
 * Missing conversion to char when generating struct lv_fs_drv_t.letter
 * lv_fs_res_t lv_fs_seek(lv_fs_file_t *file_p, uint32_t pos)
 */
    

/*
 * Function NOT generated:
 * Missing conversion to char when generating struct lv_fs_drv_t.letter
 * lv_fs_res_t lv_fs_tell(lv_fs_file_t *file_p, uint32_t *pos)
 */
    

/*
 * Function NOT generated:
 * Missing conversion to char when generating struct lv_fs_drv_t.letter
 * lv_fs_res_t lv_fs_trunc(lv_fs_file_t *file_p)
 */
    

/*
 * Function NOT generated:
 * Missing conversion to char when generating struct lv_fs_drv_t.letter
 * lv_fs_res_t lv_fs_size(lv_fs_file_t *file_p, uint32_t *size)
 */
    

/*
 * lvgl extension definition for:
 * lv_fs_res_t lv_fs_rename(const char *oldname, const char *newname)
 */
 
STATIC mp_obj_t mp_lv_fs_rename(size_t n_args, const mp_obj_t *args)
{
    const char *oldname = (char*)mp_obj_str_get_str(args[0]);
    const char *newname = (char*)mp_obj_str_get_str(args[1]);
    lv_fs_res_t res = lv_fs_rename(oldname, newname);
    return mp_obj_new_int_from_uint(res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_fs_rename_obj, 2, 2, mp_lv_fs_rename);

 

/*
 * Function NOT generated:
 * Missing conversion to char when generating struct lv_fs_drv_t.letter
 * lv_fs_res_t lv_fs_dir_open(lv_fs_dir_t *rddir_p, const char *path)
 */
    

/*
 * Function NOT generated:
 * Missing conversion to char when generating struct lv_fs_drv_t.letter
 * lv_fs_res_t lv_fs_dir_read(lv_fs_dir_t *rddir_p, char *fn)
 */
    

/*
 * Function NOT generated:
 * Missing conversion to char when generating struct lv_fs_drv_t.letter
 * lv_fs_res_t lv_fs_dir_close(lv_fs_dir_t *rddir_p)
 */
    

/*
 * Function NOT generated:
 * Missing conversion to char
 * lv_fs_res_t lv_fs_free_space(char letter, uint32_t *total_p, uint32_t *free_p)
 */
    

/*
 * lvgl extension definition for:
 * char *lv_fs_get_letters(char *buf)
 */
 
STATIC mp_obj_t mp_lv_fs_get_letters(size_t n_args, const mp_obj_t *args)
{
    char *buf = (char*)mp_obj_str_get_str(args[0]);
    char * res = lv_fs_get_letters(buf);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_fs_get_letters_obj, 1, 1, mp_lv_fs_get_letters);

 

/*
 * lvgl extension definition for:
 * const char *lv_fs_get_ext(const char *fn)
 */
 
STATIC mp_obj_t mp_lv_fs_get_ext(size_t n_args, const mp_obj_t *args)
{
    const char *fn = (char*)mp_obj_str_get_str(args[0]);
    const char * res = lv_fs_get_ext(fn);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_fs_get_ext_obj, 1, 1, mp_lv_fs_get_ext);

 

/*
 * lvgl extension definition for:
 * char *lv_fs_up(char *path)
 */
 
STATIC mp_obj_t mp_lv_fs_up(size_t n_args, const mp_obj_t *args)
{
    char *path = (char*)mp_obj_str_get_str(args[0]);
    char * res = lv_fs_up(path);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_fs_up_obj, 1, 1, mp_lv_fs_up);

 

/*
 * lvgl extension definition for:
 * const char *lv_fs_get_last(const char *path)
 */
 
STATIC mp_obj_t mp_lv_fs_get_last(size_t n_args, const mp_obj_t *args)
{
    const char *path = (char*)mp_obj_str_get_str(args[0]);
    const char * res = lv_fs_get_last(path);
    return convert_to_str((void*)res);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mp_lv_fs_get_last_obj, 1, 1, mp_lv_fs_get_last);

 

/*
 * lvgl lv_font_dejavu_10 global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_dejavu_10 = {
    { &mp_lv_font_t_type },
    &lv_font_dejavu_10
};
    

/*
 * lvgl lv_font_dejavu_10_latin_sup global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_dejavu_10_latin_sup = {
    { &mp_lv_font_t_type },
    &lv_font_dejavu_10_latin_sup
};
    

/*
 * lvgl lv_font_dejavu_10_cyrillic global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_dejavu_10_cyrillic = {
    { &mp_lv_font_t_type },
    &lv_font_dejavu_10_cyrillic
};
    

/*
 * lvgl lv_font_symbol_10 global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_symbol_10 = {
    { &mp_lv_font_t_type },
    &lv_font_symbol_10
};
    

/*
 * lvgl lv_font_dejavu_20 global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_dejavu_20 = {
    { &mp_lv_font_t_type },
    &lv_font_dejavu_20
};
    

/*
 * lvgl lv_font_dejavu_20_latin_sup global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_dejavu_20_latin_sup = {
    { &mp_lv_font_t_type },
    &lv_font_dejavu_20_latin_sup
};
    

/*
 * lvgl lv_font_dejavu_20_cyrillic global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_dejavu_20_cyrillic = {
    { &mp_lv_font_t_type },
    &lv_font_dejavu_20_cyrillic
};
    

/*
 * lvgl lv_font_symbol_20 global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_symbol_20 = {
    { &mp_lv_font_t_type },
    &lv_font_symbol_20
};
    

/*
 * lvgl lv_font_dejavu_30 global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_dejavu_30 = {
    { &mp_lv_font_t_type },
    &lv_font_dejavu_30
};
    

/*
 * lvgl lv_font_dejavu_30_latin_sup global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_dejavu_30_latin_sup = {
    { &mp_lv_font_t_type },
    &lv_font_dejavu_30_latin_sup
};
    

/*
 * lvgl lv_font_dejavu_30_cyrillic global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_dejavu_30_cyrillic = {
    { &mp_lv_font_t_type },
    &lv_font_dejavu_30_cyrillic
};
    

/*
 * lvgl lv_font_symbol_30 global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_symbol_30 = {
    { &mp_lv_font_t_type },
    &lv_font_symbol_30
};
    

/*
 * lvgl lv_font_dejavu_40 global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_dejavu_40 = {
    { &mp_lv_font_t_type },
    &lv_font_dejavu_40
};
    

/*
 * lvgl lv_font_dejavu_40_latin_sup global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_dejavu_40_latin_sup = {
    { &mp_lv_font_t_type },
    &lv_font_dejavu_40_latin_sup
};
    

/*
 * lvgl lv_font_dejavu_40_cyrillic global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_dejavu_40_cyrillic = {
    { &mp_lv_font_t_type },
    &lv_font_dejavu_40_cyrillic
};
    

/*
 * lvgl lv_font_symbol_40 global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_symbol_40 = {
    { &mp_lv_font_t_type },
    &lv_font_symbol_40
};
    

/*
 * lvgl lv_font_monospace_8 global definitions
 */

STATIC const mp_lv_struct_t mp_lv_font_monospace_8 = {
    { &mp_lv_font_t_type },
    &lv_font_monospace_8
};
    

/*
 * lvgl lv_style_scr global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_scr = {
    { &mp_lv_style_t_type },
    &lv_style_scr
};
    

/*
 * lvgl lv_style_transp global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_transp = {
    { &mp_lv_style_t_type },
    &lv_style_transp
};
    

/*
 * lvgl lv_style_transp_fit global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_transp_fit = {
    { &mp_lv_style_t_type },
    &lv_style_transp_fit
};
    

/*
 * lvgl lv_style_transp_tight global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_transp_tight = {
    { &mp_lv_style_t_type },
    &lv_style_transp_tight
};
    

/*
 * lvgl lv_style_plain global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_plain = {
    { &mp_lv_style_t_type },
    &lv_style_plain
};
    

/*
 * lvgl lv_style_plain_color global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_plain_color = {
    { &mp_lv_style_t_type },
    &lv_style_plain_color
};
    

/*
 * lvgl lv_style_pretty global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_pretty = {
    { &mp_lv_style_t_type },
    &lv_style_pretty
};
    

/*
 * lvgl lv_style_pretty_color global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_pretty_color = {
    { &mp_lv_style_t_type },
    &lv_style_pretty_color
};
    

/*
 * lvgl lv_style_btn_rel global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_btn_rel = {
    { &mp_lv_style_t_type },
    &lv_style_btn_rel
};
    

/*
 * lvgl lv_style_btn_pr global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_btn_pr = {
    { &mp_lv_style_t_type },
    &lv_style_btn_pr
};
    

/*
 * lvgl lv_style_btn_tgl_rel global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_btn_tgl_rel = {
    { &mp_lv_style_t_type },
    &lv_style_btn_tgl_rel
};
    

/*
 * lvgl lv_style_btn_tgl_pr global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_btn_tgl_pr = {
    { &mp_lv_style_t_type },
    &lv_style_btn_tgl_pr
};
    

/*
 * lvgl lv_style_btn_ina global definitions
 */

STATIC const mp_lv_struct_t mp_lv_style_btn_ina = {
    { &mp_lv_style_t_type },
    &lv_style_btn_ina
};
    

/*
 * Function NOT generated:
 * Callback: user_data NOT FOUND! const uint8_t *get_bitmap(const struct _lv_font_struct *, uint32_t)
 * const uint8_t *get_bitmap(const struct _lv_font_struct *, uint32_t)
 */
    

/*
 * Function NOT generated:
 * Callback: user_data NOT FOUND! int16_t get_width(const struct _lv_font_struct *, uint32_t)
 * int16_t get_width(const struct _lv_font_struct *, uint32_t)
 */
    

/*
 * Callback function flush_cb
 * void flush_cb(struct _disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
 */

STATIC void flush_cb_callback(lv_disp_drv_t * arg0, const lv_area_t * arg1, lv_color_t * arg2)
{
    mp_obj_t args[3];
    args[0] = mp_read_ptr_lv_disp_drv_t((void*)arg0);
    args[1] = ptr_to_mp((void*)arg1);
    args[2] = mp_read_ptr_lv_color32_t((void*)arg2);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_flush_cb)) , 3, 0, args);
    return;
}


/*
 * Callback function rounder_cb
 * void rounder_cb(struct _disp_drv_t *disp_drv, lv_area_t *area)
 */

STATIC void rounder_cb_callback(lv_disp_drv_t * arg0, lv_area_t * arg1)
{
    mp_obj_t args[2];
    args[0] = mp_read_ptr_lv_disp_drv_t((void*)arg0);
    args[1] = ptr_to_mp((void*)arg1);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_rounder_cb)) , 2, 0, args);
    return;
}


/*
 * Callback function set_px_cb
 * void set_px_cb(struct _disp_drv_t *disp_drv, uint8_t *buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa)
 */

STATIC void set_px_cb_callback(lv_disp_drv_t * arg0, uint8_t * arg1, lv_coord_t arg2, lv_coord_t arg3, lv_coord_t arg4, lv_color_t arg5, lv_opa_t arg6)
{
    mp_obj_t args[7];
    args[0] = mp_read_ptr_lv_disp_drv_t((void*)arg0);
    args[1] = ptr_to_mp((void*)arg1);
    args[2] = mp_obj_new_int(arg2);
    args[3] = mp_obj_new_int(arg3);
    args[4] = mp_obj_new_int(arg4);
    args[5] = mp_read_lv_color32_t(arg5);
    args[6] = mp_obj_new_int_from_uint(arg6);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_set_px_cb)) , 7, 0, args);
    return;
}


/*
 * Callback function monitor_cb
 * void monitor_cb(struct _disp_drv_t *disp_drv, uint32_t time, uint32_t px)
 */

STATIC void monitor_cb_callback(lv_disp_drv_t * arg0, uint32_t arg1, uint32_t arg2)
{
    mp_obj_t args[3];
    args[0] = mp_read_ptr_lv_disp_drv_t((void*)arg0);
    args[1] = mp_obj_new_int_from_uint(arg1);
    args[2] = mp_obj_new_int_from_uint(arg2);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_monitor_cb)) , 3, 0, args);
    return;
}


/*
 * Callback function mem_blend_cb
 * void mem_blend_cb(struct _disp_drv_t *disp_drv, lv_color_t *dest, const lv_color_t *src, uint32_t length, lv_opa_t opa)
 */

STATIC void mem_blend_cb_callback(lv_disp_drv_t * arg0, lv_color_t * arg1, const lv_color_t * arg2, uint32_t arg3, lv_opa_t arg4)
{
    mp_obj_t args[5];
    args[0] = mp_read_ptr_lv_disp_drv_t((void*)arg0);
    args[1] = mp_read_ptr_lv_color32_t((void*)arg1);
    args[2] = mp_read_ptr_lv_color32_t((void*)arg2);
    args[3] = mp_obj_new_int_from_uint(arg3);
    args[4] = mp_obj_new_int_from_uint(arg4);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_mem_blend_cb)) , 5, 0, args);
    return;
}


/*
 * Callback function mem_fill_cb
 * void mem_fill_cb(struct _disp_drv_t *disp_drv, lv_color_t *dest_buf, const lv_area_t *dest_area, const lv_area_t *fill_area, lv_color_t color)
 */

STATIC void mem_fill_cb_callback(lv_disp_drv_t * arg0, lv_color_t * arg1, const lv_area_t * arg2, const lv_area_t * arg3, lv_color_t arg4)
{
    mp_obj_t args[5];
    args[0] = mp_read_ptr_lv_disp_drv_t((void*)arg0);
    args[1] = mp_read_ptr_lv_color32_t((void*)arg1);
    args[2] = ptr_to_mp((void*)arg2);
    args[3] = ptr_to_mp((void*)arg3);
    args[4] = mp_read_lv_color32_t(arg4);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_mem_fill_cb)) , 5, 0, args);
    return;
}


/*
 * Callback function task_cb
 * void task_cb(struct _lv_task_t *)
 */

STATIC void task_cb_callback(lv_task_t * arg0)
{
    mp_obj_t args[1];
    args[0] = ptr_to_mp((void*)arg0);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_task_cb)) , 1, 0, args);
    return;
}


/*
 * Callback function read_cb
 * bool read_cb(struct _lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
 */

STATIC bool read_cb_callback(lv_indev_drv_t * arg0, lv_indev_data_t * arg1)
{
    mp_obj_t args[2];
    args[0] = ptr_to_mp((void*)arg0);
    args[1] = ptr_to_mp((void*)arg1);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_obj_t callback_result = mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_read_cb)) , 2, 0, args);
    return mp_obj_is_true(callback_result);
}


/*
 * Callback function feedback_cb
 * void feedback_cb(struct _lv_indev_drv_t *, uint8_t)
 */

STATIC void feedback_cb_callback(lv_indev_drv_t * arg0, uint8_t arg1)
{
    mp_obj_t args[2];
    args[0] = ptr_to_mp((void*)arg0);
    args[1] = mp_obj_new_int_from_uint(arg1);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_feedback_cb)) , 2, 0, args);
    return;
}


/*
 * Function NOT generated:
 * Callback: user_data NOT FOUND! void lv_anim_exec_cb_t(void *, lv_anim_value_t)
 * void lv_anim_exec_cb_t(void *, lv_anim_value_t)
 */
    

/*
 * Callback function path_cb
 * lv_anim_value_t lv_anim_path_cb_t(const struct _lv_anim_t *)
 */

STATIC lv_anim_value_t path_cb_callback(const lv_anim_t * arg0)
{
    mp_obj_t args[1];
    args[0] = ptr_to_mp((void*)arg0);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_obj_t callback_result = mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_path_cb)) , 1, 0, args);
    return (int16_t)mp_obj_get_int(callback_result);
}


/*
 * Callback function ready_cb
 * void lv_anim_ready_cb_t(struct _lv_anim_t *)
 */

STATIC void ready_cb_callback(lv_anim_t * arg0)
{
    mp_obj_t args[1];
    args[0] = ptr_to_mp((void*)arg0);
    mp_obj_t callbacks = get_callback_dict_from_user_data(arg0->user_data);
    mp_call_function_n_kw(mp_obj_dict_get(callbacks, MP_OBJ_NEW_QSTR(MP_QSTR_ready_cb)) , 1, 0, args);
    return;
}



/*
 * lvgl module definitions
 */

STATIC const mp_rom_map_elem_t lvgl_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_lvgl) },
    { MP_ROM_QSTR(MP_QSTR_obj), MP_ROM_PTR(&mp_obj_type) },
    { MP_ROM_QSTR(MP_QSTR_cont), MP_ROM_PTR(&mp_cont_type) },
    { MP_ROM_QSTR(MP_QSTR_btn), MP_ROM_PTR(&mp_btn_type) },
    { MP_ROM_QSTR(MP_QSTR_imgbtn), MP_ROM_PTR(&mp_imgbtn_type) },
    { MP_ROM_QSTR(MP_QSTR_label), MP_ROM_PTR(&mp_label_type) },
    { MP_ROM_QSTR(MP_QSTR_img), MP_ROM_PTR(&mp_img_type) },
    { MP_ROM_QSTR(MP_QSTR_line), MP_ROM_PTR(&mp_line_type) },
    { MP_ROM_QSTR(MP_QSTR_page), MP_ROM_PTR(&mp_page_type) },
    { MP_ROM_QSTR(MP_QSTR_list), MP_ROM_PTR(&mp_list_type) },
    { MP_ROM_QSTR(MP_QSTR_chart), MP_ROM_PTR(&mp_chart_type) },
    { MP_ROM_QSTR(MP_QSTR_table), MP_ROM_PTR(&mp_table_type) },
    { MP_ROM_QSTR(MP_QSTR_cb), MP_ROM_PTR(&mp_cb_type) },
    { MP_ROM_QSTR(MP_QSTR_bar), MP_ROM_PTR(&mp_bar_type) },
    { MP_ROM_QSTR(MP_QSTR_slider), MP_ROM_PTR(&mp_slider_type) },
    { MP_ROM_QSTR(MP_QSTR_led), MP_ROM_PTR(&mp_led_type) },
    { MP_ROM_QSTR(MP_QSTR_btnm), MP_ROM_PTR(&mp_btnm_type) },
    { MP_ROM_QSTR(MP_QSTR_kb), MP_ROM_PTR(&mp_kb_type) },
    { MP_ROM_QSTR(MP_QSTR_ddlist), MP_ROM_PTR(&mp_ddlist_type) },
    { MP_ROM_QSTR(MP_QSTR_roller), MP_ROM_PTR(&mp_roller_type) },
    { MP_ROM_QSTR(MP_QSTR_ta), MP_ROM_PTR(&mp_ta_type) },
    { MP_ROM_QSTR(MP_QSTR_canvas), MP_ROM_PTR(&mp_canvas_type) },
    { MP_ROM_QSTR(MP_QSTR_win), MP_ROM_PTR(&mp_win_type) },
    { MP_ROM_QSTR(MP_QSTR_tabview), MP_ROM_PTR(&mp_tabview_type) },
    { MP_ROM_QSTR(MP_QSTR_tileview), MP_ROM_PTR(&mp_tileview_type) },
    { MP_ROM_QSTR(MP_QSTR_mbox), MP_ROM_PTR(&mp_mbox_type) },
    { MP_ROM_QSTR(MP_QSTR_lmeter), MP_ROM_PTR(&mp_lmeter_type) },
    { MP_ROM_QSTR(MP_QSTR_gauge), MP_ROM_PTR(&mp_gauge_type) },
    { MP_ROM_QSTR(MP_QSTR_sw), MP_ROM_PTR(&mp_sw_type) },
    { MP_ROM_QSTR(MP_QSTR_arc), MP_ROM_PTR(&mp_arc_type) },
    { MP_ROM_QSTR(MP_QSTR_preload), MP_ROM_PTR(&mp_preload_type) },
    { MP_ROM_QSTR(MP_QSTR_calendar), MP_ROM_PTR(&mp_calendar_type) },
    { MP_ROM_QSTR(MP_QSTR_spinbox), MP_ROM_PTR(&mp_spinbox_type) },
    { MP_ROM_QSTR(MP_QSTR_color_to1), MP_ROM_PTR(&mp_lv_color_to1_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_to8), MP_ROM_PTR(&mp_lv_color_to8_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_to16), MP_ROM_PTR(&mp_lv_color_to16_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_to32), MP_ROM_PTR(&mp_lv_color_to32_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_mix), MP_ROM_PTR(&mp_lv_color_mix_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_brightness), MP_ROM_PTR(&mp_lv_color_brightness_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_make), MP_ROM_PTR(&mp_lv_color_make_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_hex), MP_ROM_PTR(&mp_lv_color_hex_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_hex3), MP_ROM_PTR(&mp_lv_color_hex3_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_copy), MP_ROM_PTR(&mp_lv_area_copy_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_get_width), MP_ROM_PTR(&mp_lv_area_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_get_height), MP_ROM_PTR(&mp_lv_area_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_get_height), MP_ROM_PTR(&mp_lv_font_get_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_scr_act), MP_ROM_PTR(&mp_lv_scr_act_obj) },
    { MP_ROM_QSTR(MP_QSTR_layer_top), MP_ROM_PTR(&mp_lv_layer_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_layer_sys), MP_ROM_PTR(&mp_lv_layer_sys_obj) },
    { MP_ROM_QSTR(MP_QSTR_scr_load), MP_ROM_PTR(&mp_lv_scr_load_obj) },
    { MP_ROM_QSTR(MP_QSTR_log_add), MP_ROM_PTR(&mp_lv_log_add_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem_init), MP_ROM_PTR(&mp_lv_mem_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem_alloc), MP_ROM_PTR(&mp_lv_mem_alloc_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem_free), MP_ROM_PTR(&mp_lv_mem_free_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem_realloc), MP_ROM_PTR(&mp_lv_mem_realloc_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem_defrag), MP_ROM_PTR(&mp_lv_mem_defrag_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem_monitor), MP_ROM_PTR(&mp_lv_mem_monitor_obj) },
    { MP_ROM_QSTR(MP_QSTR_mem_get_size), MP_ROM_PTR(&mp_lv_mem_get_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_init), MP_ROM_PTR(&mp_lv_ll_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_ins_head), MP_ROM_PTR(&mp_lv_ll_ins_head_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_ins_prev), MP_ROM_PTR(&mp_lv_ll_ins_prev_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_ins_tail), MP_ROM_PTR(&mp_lv_ll_ins_tail_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_rem), MP_ROM_PTR(&mp_lv_ll_rem_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_clear), MP_ROM_PTR(&mp_lv_ll_clear_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_chg_list), MP_ROM_PTR(&mp_lv_ll_chg_list_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_get_head), MP_ROM_PTR(&mp_lv_ll_get_head_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_get_tail), MP_ROM_PTR(&mp_lv_ll_get_tail_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_get_next), MP_ROM_PTR(&mp_lv_ll_get_next_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_get_prev), MP_ROM_PTR(&mp_lv_ll_get_prev_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_move_before), MP_ROM_PTR(&mp_lv_ll_move_before_obj) },
    { MP_ROM_QSTR(MP_QSTR_ll_is_empty), MP_ROM_PTR(&mp_lv_ll_is_empty_obj) },
    { MP_ROM_QSTR(MP_QSTR_task_init), MP_ROM_PTR(&mp_lv_task_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_task_handler), MP_ROM_PTR(&mp_lv_task_handler_obj) },
    { MP_ROM_QSTR(MP_QSTR_task_del), MP_ROM_PTR(&mp_lv_task_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_task_set_prio), MP_ROM_PTR(&mp_lv_task_set_prio_obj) },
    { MP_ROM_QSTR(MP_QSTR_task_set_period), MP_ROM_PTR(&mp_lv_task_set_period_obj) },
    { MP_ROM_QSTR(MP_QSTR_task_ready), MP_ROM_PTR(&mp_lv_task_ready_obj) },
    { MP_ROM_QSTR(MP_QSTR_task_once), MP_ROM_PTR(&mp_lv_task_once_obj) },
    { MP_ROM_QSTR(MP_QSTR_task_reset), MP_ROM_PTR(&mp_lv_task_reset_obj) },
    { MP_ROM_QSTR(MP_QSTR_task_enable), MP_ROM_PTR(&mp_lv_task_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_task_get_idle), MP_ROM_PTR(&mp_lv_task_get_idle_obj) },
    { MP_ROM_QSTR(MP_QSTR_trigo_sin), MP_ROM_PTR(&mp_lv_trigo_sin_obj) },
    { MP_ROM_QSTR(MP_QSTR_bezier3), MP_ROM_PTR(&mp_lv_bezier3_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_hsv_to_rgb), MP_ROM_PTR(&mp_lv_color_hsv_to_rgb_obj) },
    { MP_ROM_QSTR(MP_QSTR_color_rgb_to_hsv), MP_ROM_PTR(&mp_lv_color_rgb_to_hsv_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_set), MP_ROM_PTR(&mp_lv_area_set_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_set_width), MP_ROM_PTR(&mp_lv_area_set_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_set_height), MP_ROM_PTR(&mp_lv_area_set_height_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_set_pos), MP_ROM_PTR(&mp_lv_area_set_pos_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_get_size), MP_ROM_PTR(&mp_lv_area_get_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_intersect), MP_ROM_PTR(&mp_lv_area_intersect_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_join), MP_ROM_PTR(&mp_lv_area_join_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_is_point_on), MP_ROM_PTR(&mp_lv_area_is_point_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_is_on), MP_ROM_PTR(&mp_lv_area_is_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_area_is_in), MP_ROM_PTR(&mp_lv_area_is_in_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_drv_init), MP_ROM_PTR(&mp_lv_disp_drv_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_buf_init), MP_ROM_PTR(&mp_lv_disp_buf_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_drv_register), MP_ROM_PTR(&mp_lv_disp_drv_register_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_drv_update), MP_ROM_PTR(&mp_lv_disp_drv_update_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_remove), MP_ROM_PTR(&mp_lv_disp_remove_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_set_default), MP_ROM_PTR(&mp_lv_disp_set_default_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_get_default), MP_ROM_PTR(&mp_lv_disp_get_default_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_get_hor_res), MP_ROM_PTR(&mp_lv_disp_get_hor_res_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_get_ver_res), MP_ROM_PTR(&mp_lv_disp_get_ver_res_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_get_antialiasing), MP_ROM_PTR(&mp_lv_disp_get_antialiasing_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_flush_ready), MP_ROM_PTR(&mp_lv_disp_flush_ready_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_get_next), MP_ROM_PTR(&mp_lv_disp_get_next_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_get_buf), MP_ROM_PTR(&mp_lv_disp_get_buf_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_get_inv_buf_size), MP_ROM_PTR(&mp_lv_disp_get_inv_buf_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_pop_from_inv_buf), MP_ROM_PTR(&mp_lv_disp_pop_from_inv_buf_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_is_double_buf), MP_ROM_PTR(&mp_lv_disp_is_double_buf_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_is_true_double_buf), MP_ROM_PTR(&mp_lv_disp_is_true_double_buf_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_drv_init), MP_ROM_PTR(&mp_lv_indev_drv_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_drv_register), MP_ROM_PTR(&mp_lv_indev_drv_register_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_drv_update), MP_ROM_PTR(&mp_lv_indev_drv_update_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_get_next), MP_ROM_PTR(&mp_lv_indev_get_next_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_read), MP_ROM_PTR(&mp_lv_indev_read_obj) },
    { MP_ROM_QSTR(MP_QSTR_tick_inc), MP_ROM_PTR(&mp_lv_tick_inc_obj) },
    { MP_ROM_QSTR(MP_QSTR_tick_get), MP_ROM_PTR(&mp_lv_tick_get_obj) },
    { MP_ROM_QSTR(MP_QSTR_tick_elaps), MP_ROM_PTR(&mp_lv_tick_elaps_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_init), MP_ROM_PTR(&mp_lv_font_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_add), MP_ROM_PTR(&mp_lv_font_add_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_remove), MP_ROM_PTR(&mp_lv_font_remove_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_is_monospace), MP_ROM_PTR(&mp_lv_font_is_monospace_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_get_bitmap), MP_ROM_PTR(&mp_lv_font_get_bitmap_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_get_width), MP_ROM_PTR(&mp_lv_font_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_get_real_width), MP_ROM_PTR(&mp_lv_font_get_real_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_get_bpp), MP_ROM_PTR(&mp_lv_font_get_bpp_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_get_bitmap_continuous), MP_ROM_PTR(&mp_lv_font_get_bitmap_continuous_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_get_bitmap_sparse), MP_ROM_PTR(&mp_lv_font_get_bitmap_sparse_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_get_width_continuous), MP_ROM_PTR(&mp_lv_font_get_width_continuous_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_get_width_sparse), MP_ROM_PTR(&mp_lv_font_get_width_sparse_obj) },
    { MP_ROM_QSTR(MP_QSTR_font_builtin_init), MP_ROM_PTR(&mp_lv_font_builtin_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_anim_init), MP_ROM_PTR(&mp_lv_anim_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_anim_create), MP_ROM_PTR(&mp_lv_anim_create_obj) },
    { MP_ROM_QSTR(MP_QSTR_anim_count_running), MP_ROM_PTR(&mp_lv_anim_count_running_obj) },
    { MP_ROM_QSTR(MP_QSTR_anim_speed_to_time), MP_ROM_PTR(&mp_lv_anim_speed_to_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_anim_path_linear), MP_ROM_PTR(&mp_lv_anim_path_linear_obj) },
    { MP_ROM_QSTR(MP_QSTR_anim_path_ease_in), MP_ROM_PTR(&mp_lv_anim_path_ease_in_obj) },
    { MP_ROM_QSTR(MP_QSTR_anim_path_ease_out), MP_ROM_PTR(&mp_lv_anim_path_ease_out_obj) },
    { MP_ROM_QSTR(MP_QSTR_anim_path_ease_in_out), MP_ROM_PTR(&mp_lv_anim_path_ease_in_out_obj) },
    { MP_ROM_QSTR(MP_QSTR_anim_path_overshoot), MP_ROM_PTR(&mp_lv_anim_path_overshoot_obj) },
    { MP_ROM_QSTR(MP_QSTR_anim_path_bounce), MP_ROM_PTR(&mp_lv_anim_path_bounce_obj) },
    { MP_ROM_QSTR(MP_QSTR_anim_path_step), MP_ROM_PTR(&mp_lv_anim_path_step_obj) },
    { MP_ROM_QSTR(MP_QSTR_style_init), MP_ROM_PTR(&mp_lv_style_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_style_copy), MP_ROM_PTR(&mp_lv_style_copy_obj) },
    { MP_ROM_QSTR(MP_QSTR_style_mix), MP_ROM_PTR(&mp_lv_style_mix_obj) },
    { MP_ROM_QSTR(MP_QSTR_style_anim_create), MP_ROM_PTR(&mp_lv_style_anim_create_obj) },
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_lv_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_event_send), MP_ROM_PTR(&mp_lv_event_send_obj) },
    { MP_ROM_QSTR(MP_QSTR_event_get_data), MP_ROM_PTR(&mp_lv_event_get_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_signal_send), MP_ROM_PTR(&mp_lv_signal_send_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_init), MP_ROM_PTR(&mp_lv_group_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_create), MP_ROM_PTR(&mp_lv_group_create_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_del), MP_ROM_PTR(&mp_lv_group_del_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_add_obj), MP_ROM_PTR(&mp_lv_group_add_obj_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_remove_obj), MP_ROM_PTR(&mp_lv_group_remove_obj_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_focus_obj), MP_ROM_PTR(&mp_lv_group_focus_obj_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_focus_next), MP_ROM_PTR(&mp_lv_group_focus_next_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_focus_prev), MP_ROM_PTR(&mp_lv_group_focus_prev_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_focus_freeze), MP_ROM_PTR(&mp_lv_group_focus_freeze_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_send_data), MP_ROM_PTR(&mp_lv_group_send_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_set_style_mod_cb), MP_ROM_PTR(&mp_lv_group_set_style_mod_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_set_style_mod_edit_cb), MP_ROM_PTR(&mp_lv_group_set_style_mod_edit_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_set_focus_cb), MP_ROM_PTR(&mp_lv_group_set_focus_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_set_refocus_policy), MP_ROM_PTR(&mp_lv_group_set_refocus_policy_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_set_editing), MP_ROM_PTR(&mp_lv_group_set_editing_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_set_click_focus), MP_ROM_PTR(&mp_lv_group_set_click_focus_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_set_wrap), MP_ROM_PTR(&mp_lv_group_set_wrap_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_mod_style), MP_ROM_PTR(&mp_lv_group_mod_style_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_get_focused), MP_ROM_PTR(&mp_lv_group_get_focused_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_get_user_data), MP_ROM_PTR(&mp_lv_group_get_user_data_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_get_style_mod_cb), MP_ROM_PTR(&mp_lv_group_get_style_mod_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_get_style_mod_edit_cb), MP_ROM_PTR(&mp_lv_group_get_style_mod_edit_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_get_focus_cb), MP_ROM_PTR(&mp_lv_group_get_focus_cb_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_get_editing), MP_ROM_PTR(&mp_lv_group_get_editing_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_get_click_focus), MP_ROM_PTR(&mp_lv_group_get_click_focus_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_get_wrap), MP_ROM_PTR(&mp_lv_group_get_wrap_obj) },
    { MP_ROM_QSTR(MP_QSTR_group_report_style_mod), MP_ROM_PTR(&mp_lv_group_report_style_mod_obj) },
    { MP_ROM_QSTR(MP_QSTR_refr_init), MP_ROM_PTR(&mp_lv_refr_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_refr_now), MP_ROM_PTR(&mp_lv_refr_now_obj) },
    { MP_ROM_QSTR(MP_QSTR_inv_area), MP_ROM_PTR(&mp_lv_inv_area_obj) },
    { MP_ROM_QSTR(MP_QSTR_refr_get_disp_refreshing), MP_ROM_PTR(&mp_lv_refr_get_disp_refreshing_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_refr_task), MP_ROM_PTR(&mp_lv_disp_refr_task_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_get_scr_act), MP_ROM_PTR(&mp_lv_disp_get_scr_act_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_set_scr_act), MP_ROM_PTR(&mp_lv_disp_set_scr_act_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_get_layer_top), MP_ROM_PTR(&mp_lv_disp_get_layer_top_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_get_layer_sys), MP_ROM_PTR(&mp_lv_disp_get_layer_sys_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_assign_screen), MP_ROM_PTR(&mp_lv_disp_assign_screen_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_get_refr_task), MP_ROM_PTR(&mp_lv_disp_get_refr_task_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_get_inactive_time), MP_ROM_PTR(&mp_lv_disp_get_inactive_time_obj) },
    { MP_ROM_QSTR(MP_QSTR_disp_trig_activity), MP_ROM_PTR(&mp_lv_disp_trig_activity_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_set_current), MP_ROM_PTR(&mp_lv_theme_set_current_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_get_current), MP_ROM_PTR(&mp_lv_theme_get_current_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_templ_init), MP_ROM_PTR(&mp_lv_theme_templ_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_get_templ), MP_ROM_PTR(&mp_lv_theme_get_templ_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_default_init), MP_ROM_PTR(&mp_lv_theme_default_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_get_default), MP_ROM_PTR(&mp_lv_theme_get_default_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_alien_init), MP_ROM_PTR(&mp_lv_theme_alien_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_get_alien), MP_ROM_PTR(&mp_lv_theme_get_alien_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_night_init), MP_ROM_PTR(&mp_lv_theme_night_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_get_night), MP_ROM_PTR(&mp_lv_theme_get_night_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_zen_init), MP_ROM_PTR(&mp_lv_theme_zen_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_get_zen), MP_ROM_PTR(&mp_lv_theme_get_zen_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_mono_init), MP_ROM_PTR(&mp_lv_theme_mono_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_get_mono), MP_ROM_PTR(&mp_lv_theme_get_mono_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_nemo_init), MP_ROM_PTR(&mp_lv_theme_nemo_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_get_nemo), MP_ROM_PTR(&mp_lv_theme_get_nemo_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_material_init), MP_ROM_PTR(&mp_lv_theme_material_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_theme_get_material), MP_ROM_PTR(&mp_lv_theme_get_material_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_init), MP_ROM_PTR(&mp_lv_indev_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_read_task), MP_ROM_PTR(&mp_lv_indev_read_task_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_get_act), MP_ROM_PTR(&mp_lv_indev_get_act_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_get_type), MP_ROM_PTR(&mp_lv_indev_get_type_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_reset), MP_ROM_PTR(&mp_lv_indev_reset_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_reset_long_press), MP_ROM_PTR(&mp_lv_indev_reset_long_press_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_enable), MP_ROM_PTR(&mp_lv_indev_enable_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_set_cursor), MP_ROM_PTR(&mp_lv_indev_set_cursor_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_set_group), MP_ROM_PTR(&mp_lv_indev_set_group_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_set_button_points), MP_ROM_PTR(&mp_lv_indev_set_button_points_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_get_point), MP_ROM_PTR(&mp_lv_indev_get_point_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_get_key), MP_ROM_PTR(&mp_lv_indev_get_key_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_is_dragging), MP_ROM_PTR(&mp_lv_indev_is_dragging_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_get_vect), MP_ROM_PTR(&mp_lv_indev_get_vect_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_wait_release), MP_ROM_PTR(&mp_lv_indev_wait_release_obj) },
    { MP_ROM_QSTR(MP_QSTR_indev_get_read_task), MP_ROM_PTR(&mp_lv_indev_get_read_task_obj) },
    { MP_ROM_QSTR(MP_QSTR_txt_get_size), MP_ROM_PTR(&mp_lv_txt_get_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_txt_get_next_line), MP_ROM_PTR(&mp_lv_txt_get_next_line_obj) },
    { MP_ROM_QSTR(MP_QSTR_txt_get_width), MP_ROM_PTR(&mp_lv_txt_get_width_obj) },
    { MP_ROM_QSTR(MP_QSTR_txt_is_cmd), MP_ROM_PTR(&mp_lv_txt_is_cmd_obj) },
    { MP_ROM_QSTR(MP_QSTR_txt_ins), MP_ROM_PTR(&mp_lv_txt_ins_obj) },
    { MP_ROM_QSTR(MP_QSTR_txt_cut), MP_ROM_PTR(&mp_lv_txt_cut_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_aa_get_opa), MP_ROM_PTR(&mp_lv_draw_aa_get_opa_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_aa_ver_seg), MP_ROM_PTR(&mp_lv_draw_aa_ver_seg_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_aa_hor_seg), MP_ROM_PTR(&mp_lv_draw_aa_hor_seg_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_px), MP_ROM_PTR(&mp_lv_draw_px_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_fill), MP_ROM_PTR(&mp_lv_draw_fill_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_letter), MP_ROM_PTR(&mp_lv_draw_letter_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_map), MP_ROM_PTR(&mp_lv_draw_map_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_rect), MP_ROM_PTR(&mp_lv_draw_rect_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_label), MP_ROM_PTR(&mp_lv_draw_label_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_line), MP_ROM_PTR(&mp_lv_draw_line_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_triangle), MP_ROM_PTR(&mp_lv_draw_triangle_obj) },
    { MP_ROM_QSTR(MP_QSTR_draw_img), MP_ROM_PTR(&mp_lv_draw_img_obj) },
    { MP_ROM_QSTR(MP_QSTR_fs_init), MP_ROM_PTR(&mp_lv_fs_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_fs_remove), MP_ROM_PTR(&mp_lv_fs_remove_obj) },
    { MP_ROM_QSTR(MP_QSTR_fs_rename), MP_ROM_PTR(&mp_lv_fs_rename_obj) },
    { MP_ROM_QSTR(MP_QSTR_fs_get_letters), MP_ROM_PTR(&mp_lv_fs_get_letters_obj) },
    { MP_ROM_QSTR(MP_QSTR_fs_get_ext), MP_ROM_PTR(&mp_lv_fs_get_ext_obj) },
    { MP_ROM_QSTR(MP_QSTR_fs_up), MP_ROM_PTR(&mp_lv_fs_up_obj) },
    { MP_ROM_QSTR(MP_QSTR_fs_get_last), MP_ROM_PTR(&mp_lv_fs_get_last_obj) },
    { MP_ROM_QSTR(MP_QSTR_TASK_PRIO), MP_ROM_PTR(&mp_LV_TASK_PRIO_type) },
    { MP_ROM_QSTR(MP_QSTR_OPA), MP_ROM_PTR(&mp_LV_OPA_type) },
    { MP_ROM_QSTR(MP_QSTR_INDEV_TYPE), MP_ROM_PTR(&mp_LV_INDEV_TYPE_type) },
    { MP_ROM_QSTR(MP_QSTR_INDEV_STATE), MP_ROM_PTR(&mp_LV_INDEV_STATE_type) },
    { MP_ROM_QSTR(MP_QSTR_BORDER), MP_ROM_PTR(&mp_LV_BORDER_type) },
    { MP_ROM_QSTR(MP_QSTR_SHADOW), MP_ROM_PTR(&mp_LV_SHADOW_type) },
    { MP_ROM_QSTR(MP_QSTR_DESIGN), MP_ROM_PTR(&mp_LV_DESIGN_type) },
    { MP_ROM_QSTR(MP_QSTR_RES), MP_ROM_PTR(&mp_LV_RES_type) },
    { MP_ROM_QSTR(MP_QSTR_EVENT), MP_ROM_PTR(&mp_LV_EVENT_type) },
    { MP_ROM_QSTR(MP_QSTR_SIGNAL), MP_ROM_PTR(&mp_LV_SIGNAL_type) },
    { MP_ROM_QSTR(MP_QSTR_ALIGN), MP_ROM_PTR(&mp_LV_ALIGN_type) },
    { MP_ROM_QSTR(MP_QSTR_DRAG_DIR), MP_ROM_PTR(&mp_LV_DRAG_DIR_type) },
    { MP_ROM_QSTR(MP_QSTR_PROTECT), MP_ROM_PTR(&mp_LV_PROTECT_type) },
    { MP_ROM_QSTR(MP_QSTR_GROUP_REFOCUS_POLICY), MP_ROM_PTR(&mp_LV_GROUP_REFOCUS_POLICY_type) },
    { MP_ROM_QSTR(MP_QSTR_LAYOUT), MP_ROM_PTR(&mp_LV_LAYOUT_type) },
    { MP_ROM_QSTR(MP_QSTR_FIT), MP_ROM_PTR(&mp_LV_FIT_type) },
    { MP_ROM_QSTR(MP_QSTR_TXT_FLAG), MP_ROM_PTR(&mp_LV_TXT_FLAG_type) },
    { MP_ROM_QSTR(MP_QSTR_TXT_CMD_STATE), MP_ROM_PTR(&mp_LV_TXT_CMD_STATE_type) },
    { MP_ROM_QSTR(MP_QSTR_FS_RES), MP_ROM_PTR(&mp_LV_FS_RES_type) },
    { MP_ROM_QSTR(MP_QSTR_FS_MODE), MP_ROM_PTR(&mp_LV_FS_MODE_type) },
    { MP_ROM_QSTR(MP_QSTR_SB_MODE), MP_ROM_PTR(&mp_LV_SB_MODE_type) },
    { MP_ROM_QSTR(MP_QSTR_CURSOR), MP_ROM_PTR(&mp_LV_CURSOR_type) },
    { MP_ROM_QSTR(MP_QSTR_SYMBOL), MP_ROM_PTR(&mp_LV_SYMBOL_type) },
    { MP_ROM_QSTR(MP_QSTR_mem_monitor_t), MP_ROM_PTR(&mp_lv_mem_monitor_t_type) },
    { MP_ROM_QSTR(MP_QSTR_ll_t), MP_ROM_PTR(&mp_lv_ll_t_type) },
    { MP_ROM_QSTR(MP_QSTR_task_t), MP_ROM_PTR(&mp_lv_task_t_type) },
    { MP_ROM_QSTR(MP_QSTR_color32_t), MP_ROM_PTR(&mp_lv_color32_t_type) },
    { MP_ROM_QSTR(MP_QSTR_color_hsv_t), MP_ROM_PTR(&mp_lv_color_hsv_t_type) },
    { MP_ROM_QSTR(MP_QSTR_point_t), MP_ROM_PTR(&mp_lv_point_t_type) },
    { MP_ROM_QSTR(MP_QSTR_area_t), MP_ROM_PTR(&mp_lv_area_t_type) },
    { MP_ROM_QSTR(MP_QSTR_disp_buf_t), MP_ROM_PTR(&mp_lv_disp_buf_t_type) },
    { MP_ROM_QSTR(MP_QSTR_disp_drv_t), MP_ROM_PTR(&mp_lv_disp_drv_t_type) },
    { MP_ROM_QSTR(MP_QSTR_disp_t), MP_ROM_PTR(&mp_lv_disp_t_type) },
    { MP_ROM_QSTR(MP_QSTR_indev_data_t), MP_ROM_PTR(&mp_lv_indev_data_t_type) },
    { MP_ROM_QSTR(MP_QSTR_indev_drv_t), MP_ROM_PTR(&mp_lv_indev_drv_t_type) },
    { MP_ROM_QSTR(MP_QSTR_indev_proc_t), MP_ROM_PTR(&mp_lv_indev_proc_t_type) },
    { MP_ROM_QSTR(MP_QSTR_indev_t), MP_ROM_PTR(&mp_lv_indev_t_type) },
    { MP_ROM_QSTR(MP_QSTR_font_glyph_dsc_t), MP_ROM_PTR(&mp_lv_font_glyph_dsc_t_type) },
    { MP_ROM_QSTR(MP_QSTR_font_t), MP_ROM_PTR(&mp_lv_font_t_type) },
    { MP_ROM_QSTR(MP_QSTR_anim_t), MP_ROM_PTR(&mp_lv_anim_t_type) },
    { MP_ROM_QSTR(MP_QSTR_style_t), MP_ROM_PTR(&mp_lv_style_t_type) },
    { MP_ROM_QSTR(MP_QSTR_style_anim_t), MP_ROM_PTR(&mp_lv_style_anim_t_type) },
    { MP_ROM_QSTR(MP_QSTR_obj_type_t), MP_ROM_PTR(&mp_lv_obj_type_t_type) },
    { MP_ROM_QSTR(MP_QSTR_group_t), MP_ROM_PTR(&mp_lv_group_t_type) },
    { MP_ROM_QSTR(MP_QSTR_theme_t), MP_ROM_PTR(&mp_lv_theme_t_type) },
    { MP_ROM_QSTR(MP_QSTR_img_header_t), MP_ROM_PTR(&mp_lv_img_header_t_type) },
    { MP_ROM_QSTR(MP_QSTR_img_dsc_t), MP_ROM_PTR(&mp_lv_img_dsc_t_type) },
    { MP_ROM_QSTR(MP_QSTR_chart_series_t), MP_ROM_PTR(&mp_lv_chart_series_t_type) },
    { MP_ROM_QSTR(MP_QSTR_calendar_date_t), MP_ROM_PTR(&mp_lv_calendar_date_t_type) },
    { MP_ROM_QSTR(MP_QSTR_color_t), MP_ROM_PTR(&mp_lv_color32_t_type) },
    { MP_ROM_QSTR(MP_QSTR_font_dejavu_10), MP_ROM_PTR(&mp_lv_font_dejavu_10) },
    { MP_ROM_QSTR(MP_QSTR_font_dejavu_10_latin_sup), MP_ROM_PTR(&mp_lv_font_dejavu_10_latin_sup) },
    { MP_ROM_QSTR(MP_QSTR_font_dejavu_10_cyrillic), MP_ROM_PTR(&mp_lv_font_dejavu_10_cyrillic) },
    { MP_ROM_QSTR(MP_QSTR_font_symbol_10), MP_ROM_PTR(&mp_lv_font_symbol_10) },
    { MP_ROM_QSTR(MP_QSTR_font_dejavu_20), MP_ROM_PTR(&mp_lv_font_dejavu_20) },
    { MP_ROM_QSTR(MP_QSTR_font_dejavu_20_latin_sup), MP_ROM_PTR(&mp_lv_font_dejavu_20_latin_sup) },
    { MP_ROM_QSTR(MP_QSTR_font_dejavu_20_cyrillic), MP_ROM_PTR(&mp_lv_font_dejavu_20_cyrillic) },
    { MP_ROM_QSTR(MP_QSTR_font_symbol_20), MP_ROM_PTR(&mp_lv_font_symbol_20) },
    { MP_ROM_QSTR(MP_QSTR_font_dejavu_30), MP_ROM_PTR(&mp_lv_font_dejavu_30) },
    { MP_ROM_QSTR(MP_QSTR_font_dejavu_30_latin_sup), MP_ROM_PTR(&mp_lv_font_dejavu_30_latin_sup) },
    { MP_ROM_QSTR(MP_QSTR_font_dejavu_30_cyrillic), MP_ROM_PTR(&mp_lv_font_dejavu_30_cyrillic) },
    { MP_ROM_QSTR(MP_QSTR_font_symbol_30), MP_ROM_PTR(&mp_lv_font_symbol_30) },
    { MP_ROM_QSTR(MP_QSTR_font_dejavu_40), MP_ROM_PTR(&mp_lv_font_dejavu_40) },
    { MP_ROM_QSTR(MP_QSTR_font_dejavu_40_latin_sup), MP_ROM_PTR(&mp_lv_font_dejavu_40_latin_sup) },
    { MP_ROM_QSTR(MP_QSTR_font_dejavu_40_cyrillic), MP_ROM_PTR(&mp_lv_font_dejavu_40_cyrillic) },
    { MP_ROM_QSTR(MP_QSTR_font_symbol_40), MP_ROM_PTR(&mp_lv_font_symbol_40) },
    { MP_ROM_QSTR(MP_QSTR_font_monospace_8), MP_ROM_PTR(&mp_lv_font_monospace_8) },
    { MP_ROM_QSTR(MP_QSTR_style_scr), MP_ROM_PTR(&mp_lv_style_scr) },
    { MP_ROM_QSTR(MP_QSTR_style_transp), MP_ROM_PTR(&mp_lv_style_transp) },
    { MP_ROM_QSTR(MP_QSTR_style_transp_fit), MP_ROM_PTR(&mp_lv_style_transp_fit) },
    { MP_ROM_QSTR(MP_QSTR_style_transp_tight), MP_ROM_PTR(&mp_lv_style_transp_tight) },
    { MP_ROM_QSTR(MP_QSTR_style_plain), MP_ROM_PTR(&mp_lv_style_plain) },
    { MP_ROM_QSTR(MP_QSTR_style_plain_color), MP_ROM_PTR(&mp_lv_style_plain_color) },
    { MP_ROM_QSTR(MP_QSTR_style_pretty), MP_ROM_PTR(&mp_lv_style_pretty) },
    { MP_ROM_QSTR(MP_QSTR_style_pretty_color), MP_ROM_PTR(&mp_lv_style_pretty_color) },
    { MP_ROM_QSTR(MP_QSTR_style_btn_rel), MP_ROM_PTR(&mp_lv_style_btn_rel) },
    { MP_ROM_QSTR(MP_QSTR_style_btn_pr), MP_ROM_PTR(&mp_lv_style_btn_pr) },
    { MP_ROM_QSTR(MP_QSTR_style_btn_tgl_rel), MP_ROM_PTR(&mp_lv_style_btn_tgl_rel) },
    { MP_ROM_QSTR(MP_QSTR_style_btn_tgl_pr), MP_ROM_PTR(&mp_lv_style_btn_tgl_pr) },
    { MP_ROM_QSTR(MP_QSTR_style_btn_ina), MP_ROM_PTR(&mp_lv_style_btn_ina) }
};


STATIC MP_DEFINE_CONST_DICT (
    mp_module_lvgl_globals,
    lvgl_globals_table
);

const mp_obj_module_t mp_module_lvgl = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_lvgl_globals
};

