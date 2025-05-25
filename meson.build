project(
  'hellostm32',
  [ 'c', 'cpp' ],
  default_options : [
    'c_std=c2x',
    'cpp_std=c++23',
    'buildtype=debug'
  ]
)

cc  = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')

# sysroot
sr = run_command(cc, ['--print-sysroot'], check: true)
sysroot = sr.stdout().strip()

arm_c_args = [
  '-DSTM32U545xx',
  '-Wall',
  '-Wextra',
  '-mcpu=cortex-m33',
  '-mfloat-abi=hard',   # FPU is hardware
  '-mfpu=fpv5-sp-d16',  # fp version 5, single precision, 16-double-precision-register
  '-mthumb',
  '-nostdlib',
  '--sysroot=' + sysroot
]

arm_cpp_args = [
  '-fno-rtti',
  '-fno-exceptions',
  '-fno-threadsafe-statics'
]

arm_link_args = [
  '-mcpu=cortex-m33',
  '-mthumb',
  '-mfloat-abi=hard',
  '-mfpu=fpv5-sp-d16',
]

subdir('lib')
subdir('lib/CMSIS')
subdir('lib/link')
subdir('lib/startup')
subdir('lib/stm32u5')  # bsp, hal, middlewares

firmware_elf = executable('firmware.elf',
  [
    'src/main.c',
    'src/syscalls.c',
    'src/sysmem.c',
    bsp_src,
    hal_src,
  ],
  include_directories: [
    include_directories('src'),
    startup_inc,
    bsp_inc,
    hal_inc,
  ],
  c_args: [
    '-fdata-sections',
    '-ffreestanding',
    '-ffunction-sections',
  ] + arm_c_args,
  cpp_args: arm_cpp_args,
  link_args: arm_link_args + [
    '--specs=nano.specs',
    '-Wl,--gc-sections',
    '-Wl,-Map=output.map',
    '-T', link_flash_path,
  ],
  link_depends: link_flash,
  dependencies: [
    startup,
    cmsis,
    # bsp,
    # hal
  ],
  install: false
)

custom_target('firmware.bin',
  input: firmware_elf,  # This makes it depend on the .elf build
  output: 'firmware.bin',
  command: ['arm-none-eabi-objcopy', '-O', 'binary', '@INPUT@', '@OUTPUT@'],
  build_by_default: true,
  install: false
)

