# HelloSTM32


## Docker Container

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
