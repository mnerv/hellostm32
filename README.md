# HelloSTM32

Learning how to use STM32 MCUs by setting up a build environment with CMake,
downloading the ARM compiler, exploring the STM32CubeIDE directory structure,
and modifying it to suit personal needs and style.

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

CMake targets are provided for all common workflows:

```sh
cmake --build build --target flash   # build and flash firmware
cmake --build build --target debug   # start OpenOCD GDB server on :3333
cmake --build build --target gdb     # connect arm-none-eabi-gdb to :3333
```

`debug` and `gdb` are meant to run in separate terminals — start `debug`
first, then `gdb`.

Equivalent manual commands:

```sh
openocd -f interface/stlink.cfg -f target/stm32u5x.cfg
```

```sh
arm-none-eabi-gdb \
  -ex "target remote :3333" \
  -ex "load" \
  -ex "monitor reset init" \
  build/firmware.elf
```

### Zed

Zed's built-in debugger connects to OpenOCD via GDB. Requires a GDB build
with DAP support (GDB 14+) and multi-architecture support. Install
`gdb-multiarch` for your platform:

**Windows** — [MSYS2](https://www.msys2.org) UCRT64:

```sh
pacman -S mingw-w64-ucrt-x86_64-gdb-multiarch
```

**Linux**:

```sh
sudo apt install gdb-multiarch
```

**macOS**:

```sh
brew install gdb
```

Create `.zed/settings.json` with the path to the installed binary:

| Platform | Path                                     |
|----------|------------------------------------------|
| Windows  | `C:/msys64/ucrt64/bin/gdb-multiarch.exe` |
| Linux    | `/usr/bin/gdb-multiarch`                 |
| macOS    | `/opt/homebrew/bin/gdb`                  |

```json
{
  "dap": {
    "GDB": {
      "binary": "<path from table above>",
    },
  },
}
```

Create `.zed/debug.json`:

```json
[
  {
    "label": "Debug firmware (OpenOCD)",
    "adapter": "GDB",
    "request": "launch",
    "program": "$ZED_WORKTREE_ROOT/build/firmware.elf",
    "gdb_args": [
      "-ex",
      "target remote :3333",
      "-ex",
      "load",
      "-ex",
      "monitor reset init",
    ],
  },
]
```

Start OpenOCD first, then launch the debugger in Zed:

```sh
# Terminal — keep this running
cmake --build build --target debug
```

Then use **Run > Start Debugging** or the debug panel and select
**Debug firmware (OpenOCD)**.

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
