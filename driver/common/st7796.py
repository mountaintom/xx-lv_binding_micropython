
import time
from micropython import const

import lvgl as lv
import lcd_bus
import display_driver_framework


_SWRESET = const(0x01)
_SLPOUT = const(0x11)
_CSCON = const(0xF0)
_MADCTL = const(0x36)
_IPF = const(0x3A)
_INVTR = const(0xB4)
_DFC = const(0xB6)
_DOCA = const(0xE8)
_PWR2 = const(0xC1)
_PWR3 = const(0xC2)
_VCMPCTL = const(0xC5)
_PGC = const(0xE0)
_NGC = const(0xE1)
_DISPON = const(0x29)

STATE_HIGH = display_driver_framework.STATE_HIGH
STATE_LOW = display_driver_framework.STATE_LOW
STATE_PWM = display_driver_framework.STATE_PWM

PORTRAIT = display_driver_framework.PORTRAIT
LANDSCAPE = display_driver_framework.LANDSCAPE
REVERSE_PORTRAIT = display_driver_framework.REVERSE_PORTRAIT
REVERSE_LANDSCAPE = display_driver_framework.REVERSE_LANDSCAPE


class ST7796(display_driver_framework.DisplayDriver):

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

    display_name = 'ST7796'

    def __init__(
        self,
        data_bus,
        display_width,
        display_height,
        reset_pin=None,
        reset_state=STATE_HIGH,
        power_pin=None,
        power_on_state=STATE_HIGH,
        backlight_pin=None,
        backlight_on_state=STATE_HIGH,
        offset_x=0,
        offset_y=0,
    ):
        super().__init__(
            data_bus=data_bus,
            display_width=display_width,
            display_height=display_height,
            reset_pin=reset_pin,
            reset_state=reset_state,
            power_pin=power_pin,
            power_on_state=power_on_state,
            backlight_pin=backlight_pin,
            backlight_on_state=backlight_on_state,
            offset_x=offset_x,
            offset_y=offset_y,
            color_format=lv.COLOR_FORMAT.NATIVE_REVERSE
        )

    def init(self):
        param_buf = bytearray(14)
        param_mv = memoryview(param_buf)

        self.set_params(_SWRESET)

        time.sleep_ms(120)

        self.set_params(_SLPOUT)

        time.sleep_ms(120)

        param_buf[0] = 0xC3
        self.set_params(_CSCON, param_mv[:1])

        param_buf[0] = 0x96
        self.set_params(_CSCON, param_mv[:1])

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

        if lv.color_t.__SIZE__ == 4:  # NOQA
            pixel_format = 0x07  # 262K-Colors
        elif lv.color_t.__SIZE__ == 2:  # NOQA
            pixel_format = 0x05  # 65K-Colors  55??
        else:
            raise RuntimeError(
                'ST7796 micropython driver '
                'requires defining LV_COLOR_DEPTH=32 or LV_COLOR_DEPTH=16'
            )

        param_buf[0] = pixel_format
        self.set_params(_IPF, param_mv[:1])

        param_buf[0] = 0x01
        self.set_params(_INVTR, param_mv[:1])

        param_buf[0] = 0x80
        param_buf[1] = 0x02
        param_buf[2] = 0x3B
        self.set_params(_DFC, param_mv[:3])

        param_buf[:8] = bytearray([
            0x40, 0x8A, 0x00, 0x00, 0x29, 0x19, 0xA5, 0x33
        ])
        self._data_bus.tx_param(_DOCA, param_mv[:8])

        param_buf[0] = 0x06
        self.set_params(_PWR2, param_mv[:1])

        param_buf[0] = 0xA7
        self.set_params(_PWR3, param_mv[:1])

        param_buf[0] = 0x18
        self.set_params(_VCMPCTL, param_mv[:1])

        time.sleep_ms(120)

        param_buf[:14] = bytearray([
            0xF0, 0x09, 0x0b, 0x06, 0x04, 0x15, 0x2F,
            0x54, 0x42, 0x3C, 0x17, 0x14, 0x18, 0x1B
        ])
        self.set_params(_PGC, param_mv[:14])

        param_buf[:14] = bytearray([
            0xE0, 0x09, 0x0B, 0x06, 0x04, 0x03, 0x2B,
            0x43, 0x42, 0x3B, 0x16, 0x14, 0x17, 0x1B
        ])
        self.set_params(_NGC, param_mv[:14])

        time.sleep_ms(120)

        param_buf[0] = 0x3C
        self.set_params(_CSCON, param_mv[:1])

        param_buf[0] = 0x69
        self.set_params(_CSCON, param_mv[:1])

        time.sleep_ms(120)

        self.set_params(_DISPON)

        time.sleep_ms(120)

        display_driver_framework.DisplayDriver.init(self)
