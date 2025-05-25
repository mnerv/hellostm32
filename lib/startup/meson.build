startup_src = files(
  'startup_stm32u545retx.s',
  'system_stm32u5xx.c',
)

startup_lib = static_library('startup',
  startup_src,
  include_directories: [
    cmsis_inc,
    startup_inc,
    bsp_inc,
  ],
  c_args: arm_c_args,
  cpp_args: arm_cpp_args,
  link_args: arm_link_args
)

startup = declare_dependency(
  link_whole: startup_lib,
  include_directories: startup_inc
)
