
#include "spi/spi_bus.h"
#include "i2c/i2c_bus.h"

#if (SOC_LCD_I80_SUPPORTED == 1)
#include "i80/i80_bus.h"
#endif /*(SOC_LCD_I80_SUPPORTED == 1)*/

#include "common/bus_common.h"

#if (SOC_LCD_RGB_SUPPORTED == 1)
#include "rgb/rgb_bus.h"
#endif /*(SOC_LCD_RGB_SUPPORTED == 1)*/

#include "esp_lcd_types.h"

#include "py/obj.h"

STATIC const mp_map_elem_t mp_module_lcd_bus_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__),           MP_OBJ_NEW_QSTR(MP_QSTR_lcd_bus)      },
#if (SOC_LCD_RGB_SUPPORTED == 1)
    { MP_ROM_QSTR(MP_QSTR_RGBBus),             (mp_obj_t)&mp_lcd_rgb_bus_type        },
#endif /*(SOC_LCD_RGB_SUPPORTED == 1)*/
    { MP_ROM_QSTR(MP_QSTR_SPIBus),             (mp_obj_t)&mp_lcd_spi_bus_type        },
    { MP_ROM_QSTR(MP_QSTR_I2CBus),             (mp_obj_t)&mp_lcd_i2c_bus_type        },
#if (SOC_LCD_I80_SUPPORTED == 1)
    { MP_ROM_QSTR(MP_QSTR_I80Bus),             (mp_obj_t)&mp_lcd_i80_bus_type        },
#endif /*(SOC_LCD_I80_SUPPORTED == 1)*/
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

