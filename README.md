# HelloSTM32

Learning how to use STM32 MCUs by setting up a build environment with Meson,
downloading the ARM compiler, exploring the STM32CubeIDE directory structure,
and modifying it to suit personal needs and style.

## Development

Guide to setting up development tools: follow your operating-system–specific
instructions first, then proceed with the Meson guide.

### meson

Use `meson` to configure your build directory and `ninja` to compile:

```sh
meson setup build --cross-file toolchain/cross.ini
```

```sh
ninja -C build
```


### Linux

Download arm toolchains for Linux.

```sh
mkdir -p .tools && cd .tools
wget "https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz"
tar arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz
```

Set environment in the current shell environment.

```sh
export PATH="$(pwd)/.tools/bin:$PATH"
```

**Optional**: Symlink `compile_commands.json` to root directory for
`clangd`/`ccls`.

```sh
ln -sfn ./build/compile_commands.json .
```

### Windows

Download arm toolchains for Windows.

```ps1
mkdir .tools; cd .tools
Invoke-WebRequest `
  -Uri "https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-mingw-w64-x86_64-arm-none-eabi.zip" `
  -OutFile "arm-gnu-toolchain-14.2.rel1-mingw-w64-x86_64-arm-none-eabi.zip"
unzip arm-gnu-toolchain-14.2.rel1-mingw-w64-x86_64-arm-none-eabi.zip
```

Set environment in the current shell environment. The example below uses
powershell.

```ps1
$env:PATH = "$(pwd)/.tools/bin;$env:PATH"
```

**Optional**: Symlink `compile_commands.json` to root directory for
`clangd`/`ccls` for windows. Requires **admin**.

```ps1
New-Item -ItemType SymbolicLink -Path "compile_commands.json" -Target "./build/compile_commands.json"
```

### Docker Container

**Linux**:

```sh
docker build --build-arg USER_ID=$(id -u) --build-arg GROUP_ID=$(id -g) -t hellostm32 .
```

**Windows**:

```sh
docker build -t hellostm32 .
```

Run container:

```sh
docker run -it --rm -v "$(pwd):/app" hellostm32
```

## Flashing

Only notes for now.

You can flash your firmware onto the target MCU using various tools—choose the
one that matches your hardware/debug adapter.

### Using `st-flash`

```sh
st-flash write build/firmware.bin 0x8000000
```

## Debugging

Only notes for now.

### Using OpenOCD

```sh
openocd -f interface/stlink.cfg -f target/stm32u5x.cfg
```

```sh
arm-none-eabi-gdb build/firmware.elf
```

`gdb`

```sh
(gdb) target remote localhost:3333
(gdb) load
(gdb) monitor reset init
(gdb) continue
```

### Segger J-Link

```sh
JLinkGDBServer -device STM32F407VG -if SWD -speed 4000
```

```sh
arm-none-eabi-gdb build/firmware.elf
```

## Resources

You'll need an account if you want to download anything from ST.

  - [Arm GNU Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)

  - [STM32CubeMX](https://www.st.com/en/development-tools/stm32-configurators-and-code-generators.html)
  - [STM32CubeIDE](https://www.st.com/en/development-tools/stm32-ides.html)

  - [STM32U545](https://www.st.com/en/microcontrollers-microprocessors/stm32u535-545.html)
    - [STM32CubeU5](https://github.com/STMicroelectronics/STM32CubeU5)
    - [stm32u5xx-hal-driver](https://github.com/STMicroelectronics/stm32u5xx-hal-driver)
  - [STM32H503](https://www.st.com/en/microcontrollers-microprocessors/stm32h503.html)
    - [STM32CubeH5](https://github.com/STMicroelectronics/STM32CubeH5)
    - [stm32h5xx-hal-driver](https://github.com/STMicroelectronics/stm32h5xx-hal-driver)

  - [OpenOCD - (Open On-Chip-Debugger)](https://openocd.org/)

  - [JTAG](https://en.wikipedia.org/wiki/JTAG)
  - [SWD](https://en.wikipedia.org/wiki/JTAG#Similar_interface_standards)

## Hardware

  - [NUCLEO-U545RE-Q](https://www.st.com/en/evaluation-tools/nucleo-u545re-q.html)

**AArch32 bare-metal target (arm-none-eabi)**

