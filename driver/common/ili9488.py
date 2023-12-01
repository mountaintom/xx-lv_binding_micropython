
from micropython import const
import lvgl as lv
import lcd_bus
import display_driver_framework


_INTRFC_MODE_CTL = const(0xB0)
_FRAME_RATE_NORMAL_CTL = const(0xB1)
_INVERSION_CTL = const(0xB4)
_FUNCTION_CTL = const(0xB6)
_ENTRY_MODE_CTL = const(0xB7)
_POWER_CTL_ONE = const(0xC0)
_POWER_CTL_TWO = const(0xC1)
_POWER_CTL_THREE = const(0xC5)
_POSITIVE_GAMMA_CTL = const(0xE0)
_NEGATIVE_GAMMA_CTL = const(0xE1)
_ADJUST_CTL_THREE = const(0xF7)
_COLOR_MODE_16BIT = const(0x55)
_COLOR_MODE_18BIT = const(0x66)
_INTERFACE_MODE_USE_SDO = const(0x00)
_INTERFACE_MODE_IGNORE_SDO = const(0x80)
_IMAGE_FUNCTION_DISABLE_24BIT_DATA = const(0x00)
_WRITE_MODE_BCTRL_DD_ON = const(0x28)
_FRAME_RATE_60HZ = const(0xA0)
_INIT_LENGTH_MASK = const(0x1F)
_MADCTL = const(0x36)
_COLMOD = const(0x3A)
_NOP = const(0x00)

STATE_HIGH = display_driver_framework.STATE_HIGH
STATE_LOW = display_driver_framework.STATE_LOW
STATE_PWM = display_driver_framework.STATE_PWM

PORTRAIT = display_driver_framework.PORTRAIT
LANDSCAPE = display_driver_framework.LANDSCAPE
REVERSE_PORTRAIT = display_driver_framework.REVERSE_PORTRAIT
REVERSE_LANDSCAPE = display_driver_framework.REVERSE_LANDSCAPE


class ILI9488(display_driver_framework.DisplayDriver):

    # The st7795 display controller has an internal framebuffer
    # arranged in 320 x 480
    # configuration. Physical displays with pixel sizes less than
    # 320 x 480 must supply a start_x and
    # start_y argument to indicate where the physical display begins
    # relative to the start of the
    # display controllers internal framebuffer.

    # this display driver supports RGB565 and also RGB666. RGB666 is going to
    # use twice as much memory as the RGB565. It is also going to slow down the
    # frame rate by 1/3, This is becasue of the extra byte of data that needs
    # to get sent. To use RGB666 the color depth MUST be set to 32.
    # so when compiling
    # make sure to have LV_COLOR_DEPTH=32 set in LVFLAGS when you call make.
    # For RGB565 you need to have LV_COLOR_DEPTH=16

    # the reason why we use a 32 bit color depth is because of how the data gets
    # written. The entire 8 bits for each byte gets sent. The controller simply
    # ignores the lowest 2 bits in the byte to make it a 6 bit color channel
    # We just have to tell lvgl that we want to use

    display_name = 'ILI9488'

    def init(self):
        param_buf = bytearray(15)
        param_mv = memoryview(param_buf)

        param_buf[:15] = bytearray([
            0x00, 0x03, 0x09, 0x08, 0x16,
            0x0A, 0x3F, 0x78, 0x4C, 0x09,
            0x0A, 0x08, 0x16, 0x1A, 0x0F
        ])

        self.set_params(_POSITIVE_GAMMA_CTL, param_mv[:15])

        param_buf[:15] = bytearray([
            0x00, 0x16, 0x19, 0x03, 0x0F,
            0x05, 0x32, 0x45, 0x46, 0x04,
            0x0E, 0x0D, 0x35, 0x37, 0x0F
        ])
        self.set_params(_NEGATIVE_GAMMA_CTL, param_mv[:15])

        param_buf[0] = 0x17
        param_buf[1] = 0x15

        self.set_params(_POWER_CTL_ONE, param_mv[:2])

        param_buf[0] = 0x41
        self.set_params(_POWER_CTL_TWO, param_mv[:1])

        param_buf[0] = 0x00
        param_buf[1] = 0x12
        param_buf[3] = 0x80
        self.set_params(_POWER_CTL_THREE, param_mv[:3])

        if isinstance(self._data_bus, lcd_bus.SPIBus):
            color_mode = display_driver_framework.COLOR_MODE_BGR
        else:
            color_mode = display_driver_framework.COLOR_MODE_RGB

        param_buf[0] = (
            self._madctl(
                color_mode, self._orientation,
                display_driver_framework._ORIENTATION_TABLE
            )
        )
        self.set_params(_MADCTL, param_mv[:1])

        if lv.color_t.__SIZE__ == 2:  # NOQA
            pixel_format = 0xAA
        elif lv.color_t.__SIZE__ in (3, 4):
            pixel_format = 0xEE
        else:
            raise RuntimeError(
                'ST7796 micropython driver '
                'requires defining LV_COLOR_DEPTH=32 or LV_COLOR_DEPTH=16'
            )

        param_buf[0] = pixel_format
        self.set_params(_COLMOD, param_mv[:1])

        param_buf[0] = _INTERFACE_MODE_USE_SDO
        self.set_params(_INTRFC_MODE_CTL, param_mv[:1])

        param_buf[0] = _FRAME_RATE_60HZ
        self.set_params(_FRAME_RATE_NORMAL_CTL, param_mv[:1])

        param_buf[0] = 0x02
        self.set_params(_INVERSION_CTL, param_mv[:1])

        param_buf[0] = 0x02
        param_buf[1] = 0x02
        param_buf[2] = 0x3B
        self.set_params(_FUNCTION_CTL, param_mv[:3])

        param_buf[0] = 0xC6
        self.set_params(_ENTRY_MODE_CTL, param_mv[:1])

        param_buf[:4] = bytearray([
            0xA9, 0x51, 0x2C, 0x02
        ])
        self._data_bus.tx_param(_ADJUST_CTL_THREE, param_mv[:4])

        self.set_params(_NOP)
