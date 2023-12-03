import micropython
import time
from machine import Pin, PWM
from micropython import const

import lvgl as lv
import lcd_bus


micropython.alloc_emergency_exception_buf(256)
# gc.threshold(0x10000) # leave enough room for SPI master TX DMA buffers

# Constants

COLOR_MODE_RGB = const(0x00)
COLOR_MODE_BGR = const(0x08)

_RASET = const(0x2B)
_CASET = const(0x2A)
_RAMWR = const(0x2C)
_MADCTL = const(0x36)

_MADCTL_MH = const(0x04)  # Refresh 0=Left to Right, 1=Right to Left
_MADCTL_ML = const(0x10)  # Refresh 0=Top to Bottom, 1=Bottom to Top
_MADCTL_MV = const(0x20)  # 0=Normal, 1=Row/column exchange
_MADCTL_MX = const(0x40)  # 0=Left to Right, 1=Right to Left
_MADCTL_MY = const(0x80)  # 0=Top to Bottom, 1=Bottom to Top

# MADCTL values for each of the orientation constants for non-st7789 displays.
_ORIENTATION_TABLE = (
    _MADCTL_MX,
    _MADCTL_MV,
    _MADCTL_MY,
    _MADCTL_MY | _MADCTL_MX | _MADCTL_MV
)

# Negative orientation constants indicate the MADCTL value will come from
# the ORIENTATION_TABLE, otherwise the rot value is used as the MADCTL value.
PORTRAIT = const(-1)
LANDSCAPE = const(-2)
REVERSE_PORTRAIT = const(-3)
REVERSE_LANDSCAPE = const(-4)

STATE_HIGH = 1
STATE_LOW = 0
STATE_PWM = -1


class DisplayDriver:

    display_name = 'DisplayDriver'

    # Default values of "power" and "backlight" are reversed logic! 0 means ON.
    # You can change this by setting backlight_on and power_on arguments.

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
        color_format=None
    ):

        if power_on_state not in (STATE_HIGH, STATE_LOW):
            raise RuntimeError(
                'power on state must be either STATE_HIGH or STATE_LOW'
            )

        if reset_state not in (STATE_HIGH, STATE_LOW):
            raise RuntimeError(
                'reset state must be either STATE_HIGH or STATE_LOW'
            )

        if backlight_on_state not in (STATE_HIGH, STATE_LOW, STATE_PWM):
            raise RuntimeError(
                'backlight on state must be either '
                'STATE_HIGH, STATE_LOW or STATE_PWM'
            )

        self.display_width = display_width
        self.display_height = display_height
        if reset_pin is None:
            self._reset_pin = None
        else:
            self._reset_pin = Pin(reset_pin, Pin.OUT)
            self._reset_pin.value(not reset_state)

        self._reset_state = reset_state

        if power_pin is None:
            self._power_pin = None
        else:
            self._power_pin = Pin(power_pin, Pin.OUT)
            self._power_pin.value(not power_on_state)

        self._power_on_state = power_on_state

        if backlight_pin is None:
            self._backlight_pin = None
        elif backlight_on_state == STATE_PWM:
            pin = Pin(backlight_pin, Pin.OUT)
            self._backlight_pin = PWM(pin, freq=20000000)
        else:
            self._backlight_pin = Pin(backlight_pin, Pin.OUT)
            self._backlight_pin.value(not backlight_on_state)

        self._backlight_on_state = backlight_on_state

        self._offset_x = offset_x
        self._offset_y = offset_y
        self._data_bus = data_bus

        self._param_buf = bytearray(4)
        self._param_mv = memoryview(self._param_buf)

        if not lv.is_initialized():
            lv.init()

        data_bus.init(display_width, display_height, lv.color_t.__SIZE__ * 8)

        self._frame_buffer_1 = data_bus.get_frame_buffer(1)
        self._frame_buffer_2 = data_bus.get_frame_buffer(2)
        frame_buffer_size = data_bus.get_frame_buffer_size()

        self._disp_drv = lv.display_create(self.display_width, self.display_height)
        self._disp_drv.set_flush_cb(self._flush_cb)

        if isinstance(data_bus, lcd_bus.RGBBus):
            self._disp_drv.set_draw_buffers(
                self._frame_buffer_1,
                self._frame_buffer_2,
                int(frame_buffer_size // lv.color_t.__SIZE__),
                lv.DISP_RENDER_MODE.FULL
            )
        else:
            self._disp_drv.set_draw_buffers(
                self._frame_buffer_1,
                self._frame_buffer_2,
                int(frame_buffer_size // lv.color_t.__SIZE__),
                lv.DISP_RENDER_MODE.PARTIAL
            )

        data_bus.register_callback(self._flush_ready_cb, self._disp_drv)

        if color_format:
            self._disp_drv.set_color_format(color_format)

        self._orientation = PORTRAIT
        self._initilized = False

    @property
    def orientation(self):
        return self._orientation

    @orientation.setter
    def orientation(self, value):
        if isinstance(self._data_bus, lcd_bus.SPIBus):
            color_mode = COLOR_MODE_BGR
        else:
            color_mode = COLOR_MODE_RGB

        self._orientation = value

        if self._initilized:
            self._param_buf[0] = (
                self._madctl(color_mode, value, _ORIENTATION_TABLE)
            )
            self._data_bus.tx_param(_MADCTL, self._param_mv[:1])

    def init(self):
        self._initilized = True

    def set_params(self, cmd, params=None):
        self._data_bus.tx_param(cmd, params)

    def get_params(self, cmd, params):
        self._data_bus.rx_param(cmd, params)

    @property
    def power(self):
        if self._power_pin is None:
            return -1

        state = self._power_pin.value()
        if self._power_on_state:
            return state

        return not state

    @power.setter
    def power(self, value):
        if self._power_pin is None:
            return

        if self._power_on_state:
            self._power_pin.value(value)
        else:
            self._power_pin.value(not value)

    def reset(self):
        if self._reset_pin is None:
            return

        self._reset_pin.value(self._reset_state)
        time.sleep_ms(120)
        self._reset_pin.value(not self._reset_state)

    @property
    def backlight(self):
        if self._backlight_pin is None:
            return -1

        if self._backlight_on_state == STATE_PWM:
            value = self._backlight_pin.duty_u16()  # NOQA
            return round(value / 65535 * 100.0)

        value = self._backlight_pin.value()

        if self._power_on_state:
            return value

        return not value

    @backlight.setter
    def backlight(self, value):
        if self._backlight_pin is None:
            return

        if self._backlight_on_state == STATE_PWM:
            self._backlight_pin.duty_u16(value / 100 * 65535)  # NOQA
        elif self._power_on_state:
            self._backlight_pin.value(int(bool(value)))
        else:
            self._backlight_pin.value(not int(bool(value)))

    def _flush_cb(self, disp_drv, area, color_p):
        # Column addresses
        x1 = area.x1 + self._offset_x
        x2 = area.x2 + self._offset_x

        self._param_buf[0] = (x1 >> 8) & 0xFF
        self._param_buf[1] = x1 & 0xFF
        self._param_buf[2] = (x2 >> 8) & 0xFF
        self._param_buf[3] = x2 & 0xFF

        self._data_bus.tx_param(_CASET, self._param_mv[:4])

        # Page addresses

        y1 = area.y1 + self._offset_y
        y2 = area.y2 + self._offset_y

        self._param_buf[0] = (y1 >> 8) & 0xFF
        self._param_buf[1] = y1 & 0xFF
        self._param_buf[2] = (y2 >> 8) & 0xFF
        self._param_buf[3] = y2 & 0xFF

        self._data_bus.tx_param(_RASET, self._param_mv[:4])

        # size = (x2 - x1 + 1) * (y2 - y1 + 1)
        # data_view = color_p.__dereference__(size * lv.color_t.__SIZE__)  # NOQA

        self._data_bus.tx_color(_RAMWR, color_p, x1, y1, x2, y2)

    def _flush_ready_cb(self, disp_drv):
        disp_drv.flush_ready()

    @staticmethod
    def _madctl(colormode, rotation, rotations):
        # if rotation is 0 or positive use the value as is.
        if rotation >= 0:
            return rotation | colormode

        # otherwise use abs(rotation)-1 as index to
        # retrieve value from rotations set

        index = abs(rotation) - 1
        if index > len(rotations):
            RuntimeError('Invalid display orientation value specified')

        return rotations[index] | colormode