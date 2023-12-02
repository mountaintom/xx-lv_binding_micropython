import os
import sys
import subprocess

from argparse import ArgumentParser


SCRIPT_DIR = os.path.abspath(os.path.dirname(sys.argv[0]))
MPY_DIR = os.path.join(SCRIPT_DIR, 'micropython')

args = list(sys.argv[1:])
target = args.pop(0)

argParser = ArgumentParser()
argParser.add_argument(
    '-mpy_cross',
    dest='mpy_cross',
    help='compile mpy_cross',
    action='store_true'
)
argParser.add_argument(
    '-submodules',
    dest='submodules',
    help='build submodules',
    action='store_true'
)

argParser.add_argument(
    '-clean',
    dest='clean',
    help='clean the build',
    action='store_true'
)

argParser.add_argument(
    '-skip-partition-resize',
    dest='skip_partition_resize',
    help='clean the build',
    action='store_true'
)

args, extra_args = argParser.parse_known_args(args)

os.chdir(MPY_DIR)


def get_partition_file_name(otp):
    if 'Running cmake in directory ' in otp:
        build_path = otp.split('Running cmake in directory ', 1)[-1]
    else:
        build_path = otp.split('Running ninja in directory ', 1)[-1]

    build_path = build_path.split('\n', 1)[0]

    target_file = os.path.join(build_path, 'sdkconfig')

    with open(target_file, 'r') as f:
        file = f.read()

    for i, line in enumerate(file.split('\n')):
        if (
            line.startswith('CONFIG_PARTITION_TABLE_CUSTOM_FILENAME') or
            line.startswith('CONFIG_PARTITION_TABLE_FILENAME')
        ):
            return line.split('=', 1)[-1].replace('"', '')


PARTITION_HEADER = '''\
# Notes: the offset of the partition table itself is set in
# $IDF_PATH/components/partition_table/Kconfig.projbuild.
# Name,   Type, SubType, Offset,  Size, Flags
'''


class Partition:

    def __init__(self, file_path):
        self.file_path = file_path
        self._saved_data = None
        self.csv_data = self.read_csv()
        last_partition = self.csv_data[-1]

        self.total_space = last_partition[-2] + last_partition[-3]

    def revert_to_original(self):
        with open(self.file_path, 'w') as f:
            f.write(self._saved_data)

    def set_app_size(self, size):
        next_offset = 0
        app_size = 0

        for i, part in enumerate(self.csv_data):
            if next_offset == 0:
                next_offset = part[3]

            if part[3] != next_offset:
                part[3] = next_offset

            if part[1] == 'app':
                factor = ((part[4] + size) / 4096.0) + 1
                part[4] = int(int(factor) * 4096)
                app_size += part[4]
            elif app_size != 0:
                part[4] = self.total_space - next_offset

            next_offset += part[4]

        if next_offset > self.total_space:
            raise RuntimeError(
                f'Board does not have enough space, overflow of '
                f'{next_offset - self.total_space} bytes ({self.file_path})\n'
            )

    def save(self):
        otp = []

        def convert_to_hex(itm):
            if isinstance(itm, int):
                itm = hex(itm)
            return itm

        for line in self.csv_data:
            otp.append(','.join(convert_to_hex(item) for item in line))

        with open(self.file_path, 'w') as f:
            f.write(PARTITION_HEADER)
            f.write('\n'.join(otp))

    def read_csv(self):
        with open(self.file_path, 'r') as f:
            csv_data = f.read()

        self._saved_data = csv_data

        csv_data = [
            line.strip()
            for line in csv_data.split('\n')
            if line.strip() and not line.startswith('#')
        ]

        def convert_to_int(elem):
            if elem.startswith('0'):
                elem = int(elem, 16)
            return elem

        for j, line in enumerate(csv_data):
            line = [convert_to_int(item.strip()) for item in line.split(',')]
            csv_data[j] = line

        return csv_data


def spawn(cmd):

    print(' '.join(cmd))
    if sys.platform.startswith('win'):
        p = subprocess.Popen(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            stdin=subprocess.PIPE
        )
    else:
        cmd = ' '.join(cmd) + '\n'

        p = subprocess.Popen(
            'bash',
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            stdin=subprocess.PIPE,
            shell=True
        )

        p.stdin.write(cmd.encode('utf-8'))
        p.stdin.close()

    output_buffer = ''
    while p.poll() is None:
        char = p.stdout.read(1)
        while char != b'':
            sys.stdout.write(char.decode('utf-8'))
            sys.stdout.flush()
            output_buffer += char.decode('utf-8')
            char = p.stdout.read(1)

        char = p.stderr.read(1)
        while char != b'':
            sys.stderr.write(char.decode('utf-8'))
            sys.stderr.flush()
            output_buffer += char.decode('utf-8')
            char = p.stderr.read(1)

    if not p.stdout.closed:
        p.stdout.close()

    if not p.stderr.closed:
        p.stderr.close()

    sys.stdout.flush()
    sys.stderr.flush()

    return p.returncode, output_buffer


if target.lower() == 'unix':
    for i, arg in enumerate(extra_args):
        if arg.startswith('LV_CFLAGS'):
            LV_CFLAGS = arg.split('=', 1)[-1].replace('"', '')
            LV_CFLAGS += ' -DMICROPY_SDL=1'
            extra_args.pop(i)
            break
    else:
        LV_CFLAGS = '-DMICROPY_SDL=1'

    clean_cmd = [
        'make',
        '-C',
        'ports/unix',
        'clean',
        f'LV_CFLAGS="{LV_CFLAGS}"',
        f'USER_C_MODULES={SCRIPT_DIR}/make_build'
    ] + extra_args

    compile_cmd = [
        'make',
        '-C',
        'ports/unix',
        f'LV_CFLAGS="{LV_CFLAGS}"',
        f'USER_C_MODULES={SCRIPT_DIR}/make_build'
    ] + extra_args

    submodules_cmd = [
        'make',
        '-C',
        'ports/unix',
        'submodules',
        f'USER_C_MODULES={SCRIPT_DIR}/make_build'
    ] + extra_args

    mpy_cross_cmd = []

elif target.lower() == 'windows':
    if sys.platform.startswith('win'):
        try:
            import pyMSVC

            env = pyMSVC.setup_environment()
            print(env)
        except ImportError:
            pass

        mpy_cross_cmd = ['msbuild', 'mpy-cross/mpy-cross.vcxproj']
        clean_cmd = []
        compile_cmd = (
            [
                'msbuild',
                f'ports/{target}/micropython.vcxproj',
                f'USER_C_MODULES=={SCRIPT_DIR}/make_build'
            ] + extra_args
        )
        submodules_cmd = []
    else:
        mpy_cross_cmd = ['make', '-C', 'mpy-cross']
        clean_cmd = [
            'make',
            'clean',
            '-C',
            f'ports/{target}'
            f'USER_C_MODULES=={SCRIPT_DIR}/make_build'
        ] + extra_args

        compile_cmd = [
            'make',
            '-C',
            f'ports/{target}',
            f'USER_C_MODULES=={SCRIPT_DIR}/make_build'
        ] + extra_args

        submodules_cmd = []

elif target.lower() == 'esp32':
    esp_argParser = ArgumentParser()

    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_I2S',
        dest='MICROPY_PY_MACHINE_I2S',
        action='store',
        default=0,
        type=int,
        choices=[0, 1]
    )

    esp_argParser.add_argument(
        '-DMICROPY_ESPNOW',
        dest='MICROPY_ESPNOW',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_BLUETOOTH',
        dest='MICROPY_PY_BLUETOOTH',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS',
        dest='MICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS_WITH_INTERLOCK',
        dest='MICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS_WITH_INTERLOCK',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_BLUETOOTH_ENABLE_CENTRAL_MODE',
        dest='MICROPY_PY_BLUETOOTH_ENABLE_CENTRAL_MODE',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_BLUETOOTH_ENABLE_PAIRING_BONDING',
        dest='MICROPY_PY_BLUETOOTH_ENABLE_PAIRING_BONDING',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_BLUETOOTH_NIMBLE',
        dest='MICROPY_BLUETOOTH_NIMBLE',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_BLUETOOTH_NIMBLE_BINDINGS_ONLY',
        dest='MICROPY_BLUETOOTH_NIMBLE_BINDINGS_ONLY',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_HASHLIB_SHA1',
        dest='MICROPY_PY_HASHLIB_SHA1',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_HASHLIB_SHA256',
        dest='MICROPY_PY_HASHLIB_SHA256',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_CRYPTOLIB',
        dest='MICROPY_PY_CRYPTOLIB',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_OS_DUPTERM',
        dest='MICROPY_PY_OS_DUPTERM',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_OS_DUPTERM_NOTIFY',
        dest='MICROPY_PY_OS_DUPTERM_NOTIFY',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_OS_SYNC',
        dest='MICROPY_PY_OS_SYNC',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_OS_UNAME',
        dest='MICROPY_PY_OS_UNAME',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_OS_URANDOM',
        dest='MICROPY_PY_OS_URANDOM',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE',
        dest='MICROPY_PY_MACHINE',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_BITSTREAM',
        dest='MICROPY_PY_MACHINE_BITSTREAM',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_PULSE',
        dest='MICROPY_PY_MACHINE_PULSE',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_PWM',
        dest='MICROPY_PY_MACHINE_PWM',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_PWM_DUTY',
        dest='MICROPY_PY_MACHINE_PWM_DUTY',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_I2C',
        dest='MICROPY_PY_MACHINE_I2C',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_I2C_TRANSFER_WRITE1',
        dest='MICROPY_PY_MACHINE_I2C_TRANSFER_WRITE1',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_SOFTI2C',
        dest='MICROPY_PY_MACHINE_SOFTI2C',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_SPI',
        dest='MICROPY_PY_MACHINE_SPI',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_SPI_MSB',
        dest='MICROPY_PY_MACHINE_SPI_MSB',
        action='store',
        default=0,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_SPI_LSB',
        dest='MICROPY_PY_MACHINE_SPI_LSB',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_SOFTSPI',
        dest='MICROPY_PY_MACHINE_SOFTSPI',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_MACHINE_DAC',
        dest='MICROPY_PY_MACHINE_DAC',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_NETWORK',
        dest='MICROPY_PY_NETWORK',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_NETWORK_WLAN',
        dest='MICROPY_PY_NETWORK_WLAN',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_HW_ENABLE_SDCARD',
        dest='MICROPY_HW_ENABLE_SDCARD',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_SSL',
        dest='MICROPY_PY_SSL',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_SSL_MBEDTLS',
        dest='MICROPY_SSL_MBEDTLS',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_WEBSOCKET',
        dest='MICROPY_PY_WEBSOCKET',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_WEBREPL',
        dest='MICROPY_PY_WEBREPL',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_ONEWIRE',
        dest='MICROPY_PY_ONEWIRE',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_HW_ESP32S3_EXTENDED_IO',
        dest='MICROPY_HW_ESP32S3_EXTENDED_IO',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_HW_ENABLE_MDNS_QUERIES',
        dest='MICROPY_HW_ENABLE_MDNS_QUERIES',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_HW_ENABLE_MDNS_RESPONDER',
        dest='MICROPY_HW_ENABLE_MDNS_RESPONDER',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )
    esp_argParser.add_argument(
        '-DMICROPY_PY_NETWORK_LAN',
        dest='MICROPY_PY_NETWORK_LAN',
        action='store',
        default=1,
        type=int,
        choices=[0, 1]
    )

    esp_args, extra_args = esp_argParser.parse_known_args(extra_args)

    if esp_args.MICROPY_PY_MACHINE_SPI_MSB:
        esp_args.MICROPY_PY_MACHINE_SPI_LSB = 0
    if not esp_args.MICROPY_PY_MACHINE_SPI_LSB:
        esp_args.MICROPY_PY_MACHINE_SPI_MSB = 1

    replacements = (
        (
            f'#define MICROPY_PY_MACHINE_I2S              ({int(not esp_args.MICROPY_PY_MACHINE_I2S)})',
            f'#define MICROPY_PY_MACHINE_I2S              ({esp_args.MICROPY_PY_MACHINE_I2S})'
        ),
        (
            f'#define MICROPY_ESPNOW                      ({int(not esp_args.MICROPY_ESPNOW)})',
            f'#define MICROPY_ESPNOW                      ({esp_args.MICROPY_ESPNOW})'
        ),
        (
            f'#define MICROPY_PY_BLUETOOTH                ({int(not esp_args.MICROPY_PY_BLUETOOTH)})',
            f'#define MICROPY_PY_BLUETOOTH                ({esp_args.MICROPY_PY_BLUETOOTH})'
        ),
        (
            f'#define MICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS ({int(not esp_args.MICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS)})',
            f'#define MICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS ({esp_args.MICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS})'
        ),
        (
            f'#define MICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS_WITH_INTERLOCK ({int(not esp_args.MICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS_WITH_INTERLOCK)})',
            f'#define MICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS_WITH_INTERLOCK ({esp_args.MICROPY_PY_BLUETOOTH_USE_SYNC_EVENTS_WITH_INTERLOCK})'
        ),
        (
            f'#define MICROPY_PY_BLUETOOTH_ENABLE_CENTRAL_MODE ({int(not esp_args.MICROPY_PY_BLUETOOTH_ENABLE_CENTRAL_MODE)})',
            f'#define MICROPY_PY_BLUETOOTH_ENABLE_CENTRAL_MODE ({esp_args.MICROPY_PY_BLUETOOTH_ENABLE_CENTRAL_MODE})'
        ),
        (
            f'#define MICROPY_PY_BLUETOOTH_ENABLE_PAIRING_BONDING ({int(not esp_args.MICROPY_PY_BLUETOOTH_ENABLE_PAIRING_BONDING)})',
            f'#define MICROPY_PY_BLUETOOTH_ENABLE_PAIRING_BONDING ({esp_args.MICROPY_PY_BLUETOOTH_ENABLE_PAIRING_BONDING})'
        ),
        (
            f'#define MICROPY_BLUETOOTH_NIMBLE            ({int(not esp_args.MICROPY_BLUETOOTH_NIMBLE)})',
            f'#define MICROPY_BLUETOOTH_NIMBLE            ({esp_args.MICROPY_BLUETOOTH_NIMBLE})'
        ),
        (
            f'#define MICROPY_BLUETOOTH_NIMBLE_BINDINGS_ONLY ({int(not esp_args.MICROPY_BLUETOOTH_NIMBLE_BINDINGS_ONLY)})',
            f'#define MICROPY_BLUETOOTH_NIMBLE_BINDINGS_ONLY ({esp_args.MICROPY_BLUETOOTH_NIMBLE_BINDINGS_ONLY})'
        ),
        (
            f'#define MICROPY_PY_HASHLIB_SHA{int(not esp_args.MICROPY_PY_HASHLIB_SHA1)}             ({int(not esp_args.MICROPY_PY_HASHLIB_SHA1)})',
            f'#define MICROPY_PY_HASHLIB_SHA{esp_args.MICROPY_PY_HASHLIB_SHA1}             ({esp_args.MICROPY_PY_HASHLIB_SHA1})'
        ),
        (
            f'#define MICROPY_PY_HASHLIB_SHA256           ({int(not esp_args.MICROPY_PY_HASHLIB_SHA256)})',
            f'#define MICROPY_PY_HASHLIB_SHA256           ({esp_args.MICROPY_PY_HASHLIB_SHA256})'
        ),
        (
            f'#define MICROPY_PY_CRYPTOLIB                ({int(not esp_args.MICROPY_PY_CRYPTOLIB)})',
            f'#define MICROPY_PY_CRYPTOLIB                ({esp_args.MICROPY_PY_CRYPTOLIB})'
        ),
        (
            f'#define MICROPY_PY_OS_DUPTERM               ({int(not esp_args.MICROPY_PY_OS_DUPTERM)})',
            f'#define MICROPY_PY_OS_DUPTERM               ({esp_args.MICROPY_PY_OS_DUPTERM})'
        ),
        (
            f'#define MICROPY_PY_OS_DUPTERM_NOTIFY        ({int(not esp_args.MICROPY_PY_OS_DUPTERM_NOTIFY)})',
            f'#define MICROPY_PY_OS_DUPTERM_NOTIFY        ({esp_args.MICROPY_PY_OS_DUPTERM_NOTIFY})'
        ),
        (
            f'#define MICROPY_PY_OS_SYNC                  ({int(not esp_args.MICROPY_PY_OS_SYNC)})',
            f'#define MICROPY_PY_OS_SYNC                  ({esp_args.MICROPY_PY_OS_SYNC})'
        ),
        (
            f'#define MICROPY_PY_OS_UNAME                 ({int(not esp_args.MICROPY_PY_OS_UNAME)})',
            f'#define MICROPY_PY_OS_UNAME                 ({esp_args.MICROPY_PY_OS_UNAME})'
        ),
        (
            f'#define MICROPY_PY_OS_URANDOM               ({int(not esp_args.MICROPY_PY_OS_URANDOM)})',
            f'#define MICROPY_PY_OS_URANDOM               ({esp_args.MICROPY_PY_OS_URANDOM})'
        ),
        (
            f'#define MICROPY_PY_MACHINE                  ({int(not esp_args.MICROPY_PY_MACHINE)})',
            f'#define MICROPY_PY_MACHINE                  ({esp_args.MICROPY_PY_MACHINE})'
        ),
        (
            f'#define MICROPY_PY_MACHINE_BITSTREAM        ({int(not esp_args.MICROPY_PY_MACHINE_BITSTREAM)})',
            f'#define MICROPY_PY_MACHINE_BITSTREAM        ({esp_args.MICROPY_PY_MACHINE_BITSTREAM})'
        ),
        (
            f'#define MICROPY_PY_MACHINE_PULSE            ({int(not esp_args.MICROPY_PY_MACHINE_PULSE)})',
            f'#define MICROPY_PY_MACHINE_PULSE            ({esp_args.MICROPY_PY_MACHINE_PULSE})'
        ),
        (
            f'#define MICROPY_PY_MACHINE_PWM              ({int(not esp_args.MICROPY_PY_MACHINE_PWM)})',
            f'#define MICROPY_PY_MACHINE_PWM              ({esp_args.MICROPY_PY_MACHINE_PWM})'
        ),
        (
            f'#define MICROPY_PY_MACHINE_PWM_DUTY         ({int(not esp_args.MICROPY_PY_MACHINE_PWM_DUTY)})',
            f'#define MICROPY_PY_MACHINE_PWM_DUTY         ({esp_args.MICROPY_PY_MACHINE_PWM_DUTY})'
        ),
        (
            f'#define MICROPY_PY_MACHINE_I2C              ({int(not esp_args.MICROPY_PY_MACHINE_I2C)})',
            f'#define MICROPY_PY_MACHINE_I2C              ({esp_args.MICROPY_PY_MACHINE_I2C})'
        ),
        (
            f'#define MICROPY_PY_MACHINE_I2C_TRANSFER_WRITE1 ({int(not esp_args.MICROPY_PY_MACHINE_I2C_TRANSFER_WRITE1)})',
            f'#define MICROPY_PY_MACHINE_I2C_TRANSFER_WRITE1 ({esp_args.MICROPY_PY_MACHINE_I2C_TRANSFER_WRITE1})'
        ),
        (
            f'#define MICROPY_PY_MACHINE_SOFTI2C          ({int(not esp_args.MICROPY_PY_MACHINE_SOFTI2C)})',
            f'#define MICROPY_PY_MACHINE_SOFTI2C          ({esp_args.MICROPY_PY_MACHINE_SOFTI2C})'
        ),
        (
            f'#define MICROPY_PY_MACHINE_SPI              ({int(not esp_args.MICROPY_PY_MACHINE_SPI)})',
            f'#define MICROPY_PY_MACHINE_SPI              ({esp_args.MICROPY_PY_MACHINE_SPI})'
        ),
        (
            f'#define MICROPY_PY_MACHINE_SPI_MSB          ({int(not esp_args.MICROPY_PY_MACHINE_SPI_MSB)})',
            f'#define MICROPY_PY_MACHINE_SPI_MSB          ({esp_args.MICROPY_PY_MACHINE_SPI_MSB})'
        ),
        (
            f'#define MICROPY_PY_MACHINE_SPI_LSB          ({int(not esp_args.MICROPY_PY_MACHINE_SPI_LSB)})',
            f'#define MICROPY_PY_MACHINE_SPI_LSB          ({esp_args.MICROPY_PY_MACHINE_SPI_LSB})'
        ),
        (
            f'#define MICROPY_PY_MACHINE_SOFTSPI          ({int(not esp_args.MICROPY_PY_MACHINE_SOFTSPI)})',
            f'#define MICROPY_PY_MACHINE_SOFTSPI          ({esp_args.MICROPY_PY_MACHINE_SOFTSPI})'
        ),
        (
            f'#define MICROPY_PY_MACHINE_DAC              ({int(not esp_args.MICROPY_PY_MACHINE_DAC)})',
            f'#define MICROPY_PY_MACHINE_DAC              ({esp_args.MICROPY_PY_MACHINE_DAC})'
        ),
        (
            f'#define MICROPY_PY_NETWORK ({int(not esp_args.MICROPY_PY_NETWORK)})',
            f'#define MICROPY_PY_NETWORK ({esp_args.MICROPY_PY_NETWORK})'
        ),
        (
            f'#define MICROPY_PY_NETWORK_WLAN             ({int(not esp_args.MICROPY_PY_NETWORK_WLAN)})',
            f'#define MICROPY_PY_NETWORK_WLAN             ({esp_args.MICROPY_PY_NETWORK_WLAN})'
        ),
        (
            f'#define MICROPY_HW_ENABLE_SDCARD            ({int(not esp_args.MICROPY_HW_ENABLE_SDCARD)})',
            f'#define MICROPY_HW_ENABLE_SDCARD            ({esp_args.MICROPY_HW_ENABLE_SDCARD})'
        ),
        (
            f'#define MICROPY_PY_SSL                      ({int(not esp_args.MICROPY_PY_SSL)})',
            f'#define MICROPY_PY_SSL                      ({esp_args.MICROPY_PY_SSL})'
        ),
        (
            f'#define MICROPY_SSL_MBEDTLS                 ({int(not esp_args.MICROPY_SSL_MBEDTLS)})',
            f'#define MICROPY_SSL_MBEDTLS                 ({esp_args.MICROPY_SSL_MBEDTLS})'
        ),
        (
            f'#define MICROPY_PY_WEBSOCKET                ({int(not esp_args.MICROPY_PY_WEBSOCKET)})',
            f'#define MICROPY_PY_WEBSOCKET                ({esp_args.MICROPY_PY_WEBSOCKET})'
        ),
        (
            f'#define MICROPY_PY_WEBREPL                  ({int(not esp_args.MICROPY_PY_WEBREPL)})',
            f'#define MICROPY_PY_WEBREPL                  ({esp_args.MICROPY_PY_WEBREPL})'
        ),
        (
            f'#define MICROPY_PY_ONEWIRE                  ({int(not esp_args.MICROPY_PY_ONEWIRE)})',
            f'#define MICROPY_PY_ONEWIRE                  ({esp_args.MICROPY_PY_ONEWIRE})'
        ),
        (
            f'#define MICROPY_HW_ESP32S3_EXTENDED_IO      ({int(not esp_args.MICROPY_HW_ESP32S3_EXTENDED_IO)})',
            f'#define MICROPY_HW_ESP32S3_EXTENDED_IO      ({esp_args.MICROPY_HW_ESP32S3_EXTENDED_IO})'
        ),
        (
            f'#define MICROPY_HW_ENABLE_MDNS_QUERIES      ({int(not esp_args.MICROPY_HW_ENABLE_MDNS_QUERIES)})',
            f'#define MICROPY_HW_ENABLE_MDNS_QUERIES      ({esp_args.MICROPY_HW_ENABLE_MDNS_QUERIES})'
        ),
        (
            f'#define MICROPY_HW_ENABLE_MDNS_RESPONDER    ({int(not esp_args.MICROPY_HW_ENABLE_MDNS_RESPONDER)})',
            f'#define MICROPY_HW_ENABLE_MDNS_RESPONDER    ({esp_args.MICROPY_HW_ENABLE_MDNS_RESPONDER})'
        ),
        (
            f'#define MICROPY_PY_NETWORK_LAN              ({int(not esp_args.MICROPY_PY_NETWORK_LAN)})',
            f'#define MICROPY_PY_NETWORK_LAN              ({esp_args.MICROPY_PY_NETWORK_LAN})'
        ),
    )

    with open('ports/esp32/mpconfigport.h', 'r') as f:
        conf_data = f.read()

    for pattern, text in replacements:
        conf_data.replace(pattern, text)

    with open('ports/esp32/mpconfigport.h', 'w') as f:
        f.write(conf_data)

    mpy_cross_cmd = ['make', '-C', 'mpy-cross']
    clean_cmd = [
        'make',
        'clean',
        '-C',
        f'ports/{target}',
        'USER_C_MODULES=../../../../micropython.cmake'
    ] + extra_args

    compile_cmd = [
        'make',
        '-C',
        f'ports/{target}',
        'USER_C_MODULES=../../../../micropython.cmake'
    ] + extra_args
    submodules_cmd = [
        'make',
        'submodules',
        '-C',
        f'ports/{target}',
        'USER_C_MODULES=../../../../micropython.cmake'
    ] + extra_args

else:
    mpy_cross_cmd = ['make', '-C', 'mpy-cross']
    clean_cmd = [
        'make',
        'clean',
        '-C',
        f'ports/{target}',
        f'USER_C_MODULES=={SCRIPT_DIR}/make_build'
    ] + extra_args

    compile_cmd = [
        'make',
        '-C',
        f'ports/{target}',
        f'USER_C_MODULES=={SCRIPT_DIR}/make_build'
    ] + extra_args

    submodules_cmd = [
        'make',
        'submodules',
        '-C',
        f'ports/{target}',
        f'USER_C_MODULES=={SCRIPT_DIR}/make_build'
    ] + extra_args


def run_additional_commands():
    if args.mpy_cross and mpy_cross_cmd:
        return_code, _ = spawn(mpy_cross_cmd)
        if return_code != 0:
            sys.exit(return_code)

    if args.submodules and submodules_cmd:
        return_code, _ = spawn(submodules_cmd)
        if return_code != 0:
            sys.exit(return_code)

    if args.clean and clean_cmd:
        spawn(clean_cmd)


def run_esp32():

    if 'deploy' in compile_cmd:
        clean_cmd.remove('deploy')
        submodules_cmd.remove('deploy')

        if not args.skip_partition_resize:
            compile_cmd.remove('deploy')
            deploy = True
        else:
            deploy = False
    else:
        deploy = False

    new_data = [
        '',
        f"freeze('{SCRIPT_DIR}/driver/common', 'display_driver_framework.py')",
        f"freeze('{SCRIPT_DIR}/driver/common', 'fs_driver.py')",
        f"freeze('{SCRIPT_DIR}/utils', 'lv_utils.py')",
        ''
    ]
    manifest_path = os.path.join(
        MPY_DIR,
        'ports',
        'esp32',
        'boards',
        'manifest.py'
    )

    with open(manifest_path, 'r') as f:
        manifest = f.read().split('\n')

    if len(manifest) < 17:
        manifest.extend(new_data)
        with open(manifest_path, 'w') as f:
            f.write('\n'.join(manifest))

    esp32_common_path = os.path.join(
        'ports',
        'esp32',
        'esp32_common.cmake'
    )

    with open(esp32_common_path, 'r') as f:
        data = f.read()

    if 'esp_lcd' not in data:
        data1, data2 = data.split('esp_wifi\n', 1)
        data1 += 'esp_wifi\n'
        data1 += '    esp_lcd\n'
        data1 += data2
        with open(esp32_common_path, 'w') as f:
            f.write(data1)

    partition_file_names = {
        'partitions-32MiB.csv': 'ports/esp32/partitions-32MiB.csv',
        'partitions-32MiB-ota.csv': 'ports/esp32/partitions-32MiB-ota.csv',
        'partitions-16MiB-ota.csv': 'ports/esp32/partitions-16MiB-ota.csv',
        'partitions-16MiB.csv': 'ports/esp32/partitions-16MiB.csv',
        'partitions-8MiB.csv': 'ports/esp32/partitions-8MiB.csv',
        'partitions-4MiB-ota.csv': 'ports/esp32/partitions-4MiB-ota.csv',
        'partitions-2MiB.csv': 'ports/esp32/partitions-2MiB.csv',
        'partitions-4MiB.csv': 'ports/esp32/partitions-4MiB.csv',
        'partitions-app3M_fat9M_fact512k_16MiB.csv': (
            'ports/esp32/boards/ARDUINO_NANO_ESP32/partitions-'
            'app3M_fat9M_fact512k_16MiB.csv'
        )
    }

    ret_code, output = spawn(compile_cmd)
    if ret_code != 0:
        if (
            'partition is too small ' not in output or
            args.skip_partition_resize
        ):
            sys.exit(ret_code)

        sys.stdout.write('\n\033[31;1m***** Resizing Partition *****\033[0m\n')
        sys.stdout.flush()

        end = output.split('(overflow ', 1)[-1]
        overflow_amount = int(end.split(')', 1)[0], 16)

        partition_file_name = get_partition_file_name(output)

        if partition_file_name not in partition_file_names:
            raise RuntimeError(
                f'Unable to adjust partition size ({partition_file_name})'
            )

        partition = Partition(partition_file_names[partition_file_name])
        partition.set_app_size(overflow_amount)
        partition.save()

        sys.stdout.write('\n\033[31;1m***** Running build again *****\033[0m\n\n')
        sys.stdout.flush()

        if deploy:
            compile_cmd.append('deploy')

        ret_code, output = spawn(compile_cmd)

        # partition.revert_to_original()

        if ret_code != 0:
            sys.exit(ret_code)

    elif not args.skip_partition_resize:
        if 'Project build complete.' in output:

            sys.stdout.write('\n\033[31;1m***** Resizing Partition *****\033[0m\n')
            sys.stdout.flush()

            size_diff = output.rsplit('application')[1]
            size_diff = int(size_diff.split('(', 1)[-1].split('remaining')[0].strip())

            partition_file_name = get_partition_file_name(output)

            if partition_file_name not in partition_file_names:
                sys.stdout.write(
                    f'\n\033[31;1mUnable to adjust partition size ({partition_file_name})\033[0m\n\n'
                )
                sys.stdout.flush()
                sys.exit(0)

            partition = Partition(partition_file_names[partition_file_name])
            partition.set_app_size(-size_diff)
            partition.save()

            sys.stdout.write('\n\033[31;1m***** Running build again *****\033[0m\n\n')
            sys.stdout.flush()

            if deploy:
                compile_cmd.append('deploy')

            ret_code, output = spawn(compile_cmd)

            # partition.revert_to_original()

            if ret_code != 0:
                sys.exit(ret_code)

    if 'Running cmake in directory ' in output:
        build_path = output.split('Running cmake in directory ', 1)[-1]
    else:
        build_path = output.split('Running ninja in directory ', 1)[-1]

    build_path = build_path.split('\n', 1)[0]

    for arg in extra_args:
        if arg.startswith('BOARD='):
            print()
            print('COMPILED BINARIES')
            print(f'  BOOTLOADER:  {build_path}/bootloader/bootloader.bin')
            print(f'  FIRMWARE:    {build_path}/firmware.bin')
            print(f'  MICROPYTHON: {build_path}/micropython.bin')


def run_unix():
    new_data = [
        '',
        f"freeze('{SCRIPT_DIR}/driver/common', 'display_driver_framework.py')",
        f"freeze('{SCRIPT_DIR}/driver/linux', 'evdev.py')",
        f"freeze('{SCRIPT_DIR}/driver/linux', 'lv_timer.py')",
        f"freeze('{SCRIPT_DIR}/driver/linux', 'display_driver_utils.py')",
        f"freeze('{SCRIPT_DIR}/driver/linux', 'display_driver.py')",
        f"freeze('{SCRIPT_DIR}/driver/common', 'fs_driver.py')",
        f"freeze('{SCRIPT_DIR}/utils', 'lv_utils.py')",
        ''
    ]
    manifest_path = os.path.join(
        MPY_DIR,
        'ports',
        'unix',
        'variants',
        'manifest.py'
    )

    with open(manifest_path, 'r') as f:
        manifest = f.read().split('\n')

    if len(manifest) < 6:
        manifest.extend(new_data)
        with open(manifest_path, 'w') as f:
            f.write('\n'.join(manifest))

    ret_code, _ = spawn(compile_cmd)
    if ret_code != 0:
        sys.exit(ret_code)

    print()
    print(f'COMPILED BINARY: {SCRIPT_DIR}/micropython/ports/unix/build-standard/micropython')


def run_other():
    ret_code, _ = spawn(compile_cmd)
    if ret_code != 0:
        sys.exit(ret_code)


if __name__ == '__main__':
    run_additional_commands()

    if target.lower() == 'esp32':
        run_esp32()
    elif target.lower() == 'unix':
        run_unix()
    else:
        run_other()
