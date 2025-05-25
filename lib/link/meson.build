link_flash_name = 'STM32U545RETXQ_FLASH.ld'

link_flash = configure_file(
  input: link_flash_name,
  output: link_flash_name,
  copy: true
)

link_flash_path = join_paths(meson.source_root(), 'lib/link', link_flash_name)
