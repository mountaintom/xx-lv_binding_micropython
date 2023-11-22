import os
import sys
import subprocess

from argparse import ArgumentParser


SCRIPT_DIR = os.path.dirname(sys.argv[0])
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
    build_path = otp.split('Running cmake in directory ', 1)[-1]
    build_path = build_path.split('\n', 1)[0]

    target_file = os.path.join(build_path, 'sdkconfig')

    with open(target_file, 'r') as f:
        file = f.read()

    for i, line in enumerate(file.split('\n')):
        if (
            line.startswith('CONFIG_PARTITION_TABLE_CUSTOM_FILENAME') or
            line.startswith('CONFIG_PARTITION_TABLE_FILENAME')
        ):
            return line.split('=', 1)[-1]


class Partition:

    def __init__(self, file_path):
        self.file_path = file_path
        self.csv_data = self.read_csv()
        last_partition = self.csv_data[-1]

        self.total_space = last_partition[-2] + last_partition[-3]

    def set_app_size(self, size):
        next_offset = 0

        for i, part in enumerate(self.csv_data):
            if next_offset == 0:
                next_offset = part[3]

            if part[3] != next_offset:
                part[3] = next_offset

            if part[1] == 'app':
                factor = (part[4] + size) / 100.0 + 1
                part[4] = int(factor * 100)

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


if target == 'unix':
    mpy_cross_cmd = []
    clean_cmd = ['make', 'clean', '-C', 'ports/{target}'] + extra_args
    compile_cmd = ['make', '-C', 'ports/{target}'] + extra_args
    submodules_cmd = ['make', 'submodules', '-C', 'ports/{target}'] + extra_args
elif target == 'windows':
    if sys.platform.startswith('win'):
        try:
            import pyMSVC

            env = pyMSVC.setup_environment()
            print(env)
        except ImportError:
            pass

        mpy_cross_cmd = ['msbuild', 'mpy-cross/mpy-cross.vcxproj']
        clean_cmd = []
        compile_cmd = ['msbuild'] + extra_args + [
            os.path.join('ports', target, 'micropython.vcxproj')]
        submodules_cmd = []
    else:
        mpy_cross_cmd = ['make', '-C', 'mpy-cross']
        clean_cmd = ['make', 'clean', '-C', 'ports/{target}'] + extra_args
        compile_cmd = ['make', '-C', 'ports/{target}'] + extra_args
        submodules_cmd = []
else:
    mpy_cross_cmd = ['make', '-C', 'mpy-cross']
    clean_cmd = ['make', 'clean', '-C', 'ports/{target}'] + extra_args
    compile_cmd = ['make', '-C', 'ports/{target}'] + extra_args
    submodules_cmd = ['make', 'submodules', '-C', 'ports/{target}'] + extra_args


if target == 'esp32':
    clean_cmd.append('USER_C_MODULES=../../../micropython.cmake')
    compile_cmd.append('USER_C_MODULES=../../../micropython.cmake')
    submodules_cmd.append('USER_C_MODULES=../../../micropython.cmake')
else:
    if clean_cmd:
        clean_cmd.append('USER_C_MODULES=../../micropython.cmake')

    if submodules_cmd:
        submodules_cmd.append('USER_C_MODULES=../../micropython.cmake')

    compile_cmd.append('USER_C_MODULES=../../micropython.cmake')


def spawn(cmd):
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

    output_buffer = []
    while p.poll() is None:
        for line in iter(p.stdout.readline, b''):
            if line != b'':
                sys.stdout.write(line.decode('utf-8'))
                sys.stdout.flush()
                output_buffer.append(line.decode('utf-8'))

        for line in iter(p.stderr.readline, b''):
            if line != b'':
                sys.stderr.write(line.decode('utf-8'))
                sys.stderr.flush()
                output_buffer.append(line.decode('utf-8'))

    if not p.stdout.closed:
        p.stdout.close()

    if not p.stderr.closed:
        p.stderr.close()

    sys.stdout.flush()
    sys.stderr.flush()

    return p.returncode, output_buffer


if args.mpy_cross:
    return_code, _ = spawn(mpy_cross_cmd)
    if return_code != 0:
        sys.exit(return_code)

if args.submodules:
    return_code, _ = spawn(submodules_cmd)
    if return_code != 0:
        sys.exit(return_code)


if args.clean:
    spawn(clean_cmd)


if target.lower == 'esp32':

    'make.py esp32 mpy_cross submodules BOARD=ESP32_GENERIC_S3 MICROPY_BOARD_VARIANT=SPIRAM_OCTAL'
    'make.py esp32 BOARD=ESP32_GENERIC_S3 MICROPY_BOARD_VARIANT=SPIRAM_OCTAL'

    esp32_common_path = os.path.join(
        MPY_DIR,
        'ports',
        'esp32',
        'esp32_common.cmake'
    )

    with open(esp32_common_path, 'r') as f:
        data = f.read()

    if 'esp_lcd' not in data:
        data1, data2 = data.split('APPEND IDF_COMPONENTS', 1)
        data1 += 'APPEND IDF_COMPONENTS'
        data2, data3 = data2.split(')', 1)
        data1 += data2
        data1 += '    esp_lcd\n)'
        data1 += data3
        with open(esp32_common_path, 'w') as f:
            f.write(data1)

    partition_file_names = [
        'partitions-32MiB.csv',
        'partitions-32MiB-ota.csv',
        'partitions-16MiB-ota.csv',
        'partitions-16MiB.csv',
        'partitions-8MiB.csv',
        'partitions-4MiB-ota.csv',
        'partitions-2MiB.csv',
        'partitions-4MiB.csv',
    ]

    base_path = os.path.join(
        MPY_DIR,
        'ports',
        'esp32'
    )

    partition_file_names = {
        name: os.path.join(base_path, name) for name in partition_file_names
    }
    partition_file_names['partitions-app3M_fat9M_fact512k_16MiB.csv'] = (
        os.path.join(
            base_path,
            'boards',
            'ARDUINO_NANO_ESP32',
            'partitions-app3M_fat9M_fact512k_16MiB.csv'
        )
    )

    return_code, output = spawn(compile_cmd)
    if return_code != 0:
        output = ''.join(output)
        if 'partition is too small ' not in output:
            sys.exit(return_code)

        end = output.split(
            ' partition is too small for binary '
            'micropython.bin size (overflow ',
            1
        )[-1]
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
        return_code, _ = spawn(compile_cmd)
        if return_code != 0:
            sys.exit(return_code)

else:
    return_code, _ = spawn(compile_cmd)
    if return_code != 0:
        sys.exit(return_code)
