cmsis_inc = include_directories(
  'Device/ST/STM32U5xx/Include',
  'Include',
)

cmsis_src = files()

# cmsis_obj = static_library('cmsis',
#   cmsis_src,
#   c_args: arm_c_args,
#   cpp_args: arm_cpp_args,
#   include_directories: cmsis_inc,
#   install: false
# )

cmsis = declare_dependency(
  # link_with: cmsis_obj,
  include_directories: cmsis_inc
)
