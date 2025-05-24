project(
  'hellostm32',
  'c',
  default_options : [
    'c_std=c2x',
    'buildtype=debug'
  ]
)

arm_c_args = [
  '-DSTM32U545xx',
  '-Wall',
  '-Wextra',
  '-fdata-sections',
  '-ffreestanding',
  '-ffunction-sections',
  '-mcpu=cortex-m33',
  '-mfloat-abi=hard',   # FPU is hardware
  '-mfpu=fpv5-sp-d16',  # fp version 5, single precision, 16-double-precision-register
  '-mthumb',
  '-nostdlib',
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
  '--specs=nano.specs',
  '-Wl,--gc-sections',
  '-Wl,-Map=output.map',
]

std_periph_inc = include_directories(
  '.tools/arm-none-eabi/include',
  'lib/CMSIS/Device/ST/STM32U5xx/Include',
  'lib/CMSIS/Include',
  'lib/startup',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Inc',
)

std_periph_src = files(
  # Add HAL source files as needed:
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_adc.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_adc_ex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_cortex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dac.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dac_ex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma_ex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_exti.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_flash.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_flash_ex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_gpio.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_i2c.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_i2c_ex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pcd.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pcd_ex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pwr.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pwr_ex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc_ex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rtc.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rtc_ex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_spi.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_spi_ex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_tim.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_tim_ex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_uart.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_uart_ex.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_usart.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_ll_dma2d.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_ll_dma.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_ll_gpio.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_ll_rcc.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_ll_spi.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_ll_tim.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_ll_usb.c',
  'lib/stm32u5/Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_ll_utils.c',
  # CMSIS
  'lib/CMSIS/Device/ST/STM32U5xx/Source/Templates/system_stm32u5xx.c',
)

startup_file = files(
  'lib/startup/startup_stm32u545retx.s'
)

startup_obj = static_library('startup',
  startup_file,
  include_directories : std_periph_inc,
  install : false
)

firmware_elf = executable('firmware.elf',
  [
    'src/main.c',
    'src/syscalls.c',
    'src/sysmem.c',
  ] + std_periph_src,
  include_directories: std_periph_inc,
  c_args: arm_c_args,
  cpp_args: arm_cpp_args,
  link_args: arm_link_args + [
    '-T', join_paths(meson.source_root(), 'lib/link/STM32U545RETXQ_FLASH.ld')
  ],
  link_with: startup_obj,
  install: false
)

custom_target('firmware.bin',
  input: firmware_elf,  # This makes it depend on the .elf build
  output: 'firmware.bin',
  command: ['arm-none-eabi-objcopy', '-O', 'binary', '@INPUT@', '@OUTPUT@'],
  install: false
)

# firmware_ram_elf = executable('firmware_ram.elf',
#   [
#     'src/main.c',
#     'src/syscalls.c',
#     'src/sysmem.c',
#   ] + std_periph_src,
#   include_directories: std_periph_inc,
#   c_args: arm_c_args,
#   cpp_args: arm_cpp_args,
#   link_args: arm_link_args + [
#     '-T', join_paths(meson.source_root(), 'lib/link/STM32U545RETXQ_RAM.ld')
#   ],
#   link_with: startup_obj,
#   install: false
# )
#
# custom_target('firmware_ram.bin',
#   input: firmware_ram_elf,  # This makes it depend on the .elf build
#   output: 'firmware_ram.bin',
#   command: ['arm-none-eabi-objcopy', '-O', 'binary', '@INPUT@', '@OUTPUT@'],
#   install: false
# )
