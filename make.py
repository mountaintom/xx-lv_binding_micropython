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


class Partition:

    def __init__(self, file_path):
        self.file_path = file_path
        self.csv_data = self.read_csv()
        last_partition = self.csv_data[-1]

        self.total_space = last_partition[-2] + last_partition[-3]

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
            f.write('\n'.join(otp))
            f.write('\n')

    def read_csv(self):
        with open(self.file_path, 'r') as f:
            csv_data = f.read()

        csv_data = [
            line.strip()
            for line in csv_data.split('\n')
            if line.strip() and not line.startswith('#')
        ]

        def convert_to_int(elem):
            if elem.startswith('0'):
                elem = int(elem, 16)
            return elem

        for i, line in enumerate(csv_data):
            line = [convert_to_int(item.strip()) for item in line.split(',')]
            csv_data[i] = line

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
            'USER_C_MODULES=../../../micropython.cmake'
        ] + extra_args

        compile_cmd = [
            'make',
            '-C',
            f'ports/{target}',
            'USER_C_MODULES=../../../micropython.cmake'
        ] + extra_args

        submodules_cmd = []

elif target.lower() == 'esp32':
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
        if 'partition is too small ' not in output:
            sys.exit(ret_code)

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

        spawn(clean_cmd)
        ret_code, output = spawn(compile_cmd)

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
