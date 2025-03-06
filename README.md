# AHT20 Driver for CH32V003 with ch32fun

This project demonstrates how to use the AHT20 temperature and humidity sensor with the CH32V003 microcontroller with [CH32fun framework](https://github.com/cnlohr/ch32fun/tree/master). The project includes initialization of the I2C bus, reading data from the AHT20 sensor, and printing the temperature and humidity values to the console.

## Features

- Temperature and humidity measurement using AHT20 sensor
- I2C communication with the AHT20 sensor
- Periodic data reading and console output

## Hardware Requirements

- CH32V003 microcontroller
- AHT20 temperature and humidity sensor module

## Wiring

- Connect PC1 to module SDA pin
- Connect PC2 to module SCL pin
- Connect VDD to power supply (3.3 to 5V)
- Connect GND to common ground

## Usage

 - Init I2C bus with `i2c_init()`
 - Declare variable of `AHT20Data` to store result
 - Run `AHT20_read()` to fetch sensor data

## Example Code

The main application code, including initialization, data reading, and console output.

```c
// filepath: /home/pavlo/Documents/PlatformIO/Projects/AHT20-driver/src/main.c
#include "ch32fun.h"
#include "aht20.h"

int main() {
    AHT20Data data;

    SystemInit();

    i2c_init();

    while (1)
    {   
        if(AHT20_read(&data) == AHT20_OK) {
            printf("Temperature: %d Humidity: %d\n", (int)data.temperature, (int)data.humidity);
        }
        else {
            printf("Error reading AHT20 sensor\n");
        }
        Delay_Ms(1000);
    }
}
```

## License

This project is licensed under the MIT License. 

## Acknowledgements

- [PlatformIO](https://platformio.org/)
- [CH32V003 SDK](https://github.com/wuxx/nanoCH32V003)