# HelloSTM32

Learning how to use STM32 MCUs by setting up a build environment with CMake
and Meson, downloading the ARM compiler, exploring the STM32CubeIDE directory
structure, and modifying it to suit personal needs and style.

## Development

### CMake

The CMake build automatically downloads the ARM GNU toolchain into `.tools/` on
first configure if it is not already present. No manual toolchain setup needed.

Configure:

```sh
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi-toolchain.cmake
```

Build:

```sh
ninja -C build
```

To target a different MCU (default is `STM32U545xx`):

```sh
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi-toolchain.cmake \
      -DTARGET_MCU=STM32H503xx
```

Supported MCUs are defined in `cmake/MCU.cmake`. Add an `elseif` block there
to support a new device.

**Optional**: Symlink `compile_commands.json` to the root directory for
`clangd`/`ccls`.

**Linux**

```sh
ln -sfn ./build/compile_commands.json .
```

**Windows (requires admin)**

```ps1
New-Item -ItemType SymbolicLink -Path "compile_commands.json" -Target "./build/compile_commands.json"
```

### Meson

Use `meson` to configure your build directory and `ninja` to compile:

```sh
meson setup build --cross-file toolchain/cross.ini
ninja -C build
```

The Meson build requires the ARM toolchain to be on `PATH`. See the
platform-specific sections below for how to set that up.

### Linux

Download arm toolchains for Linux.

```sh
mkdir -p .tools && cd .tools
wget "https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz"
tar -xf arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz
mv ./arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi/* .
rm arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi
```

Set environment in the current shell environment.

```sh
export PATH="$(pwd)/.tools/bin:$PATH"
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
`powershell`.

```ps1
$env:PATH = "$(pwd)/.tools/bin;$env:PATH"
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

You can flash your firmware onto the target MCU using various tools. Choose the
one that matches your hardware/debug adapter.

### stlink

Download [stlink](https://github.com/stlink-org/stlink).

```sh
st-flash write build/firmware.bin 0x8000000
```

**Windows**

If you're downloading through the github release page make sure to copy the
`stlink` directory under `Program Files (x86)` in the zip file to the real
`Program Files (x86)`.

And you'll also need to download [libusb](https://libusb.info/) and put the
`dll` either in the same path as `stlink` binaries or expose it in the system
path environment.

### OpenOCD

```sh
openocd -f interface/stlink.cfg -f target/stm32u5x.cfg \
        -c "program build/firmware.elf verify reset exit"
```

## Debugging

### OpenOCD

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
(gdb) b main
(gdb) c
```

### Segger J-Link

```sh
JLinkGDBServer -device STM32U545RET6 -if SWD -speed 4000
```

```sh
arm-none-eabi-gdb -ex "target remote localhost:3333" -ex "load" -ex "monitor reset init" -ex "b main" -ex "c" build/firmware.elf
```

Follow the same step as the `openocd`.

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

**Tutorials**

  - [GPIO Usage using HAL](https://embeddedexplorer.com/stm32-gpio-tutorial/)

## Hardware

  - [NUCLEO-U545RE-Q](https://www.st.com/en/evaluation-tools/nucleo-u545re-q.html)
    - [UM3062 STM32U3/U5 Nucleo-64 board (MB1841)](https://www.st.com/en/evaluation-tools/nucleo-u545re-q.html#documentation)

**AArch32 bare-metal target (arm-none-eabi)**
