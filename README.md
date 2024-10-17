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
