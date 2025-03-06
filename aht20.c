/*
 * MIT License
 * 
 * Copyright (c) 2025 Pavlo Romaniuk
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * provided to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "ch32fun.h"
#include "aht20.h"
#include "i2c.h"

uint8_t AHT20_read(AHT20Data *data) {
    
    uint8_t buf[8] = {0};
    Delay_Ms(200);

    // Calibrate 
    buf[0] = AHT20_CMD_CALIBRATE;
    buf[1] = 0x08;
    buf[2] = 0x00;

    if(i2c_begin_transmisison(AHT20_ADDR, I2C_MODE_WRITE) != I2C_OK) {
        // Sensor not responding
        printf("AHT20 sensor or bus is not responding\n");
        i2c_end_transmisison(); //release I2C bus for others
        return AHT20_ERR_NOTFOUND;
    }
    i2c_transmit_data(buf, 3);
    i2c_end_transmisison();
    
    Delay_Ms(10); //Give int some time for calibration
    
    // Read calibration status and check calibrated bit 
    i2c_begin_transmisison(AHT20_ADDR, I2C_MODE_READ);
    i2c_receive_data(buf, 1);
    if(!(buf[0] & AHT20_STATUS_CALIBRATED)) {
        i2c_end_transmisison();
        printf("Calibration failed\n");
        return AHT20_ERR_CALIBRATION; 
    }
    i2c_end_transmisison();

    // Measurement request
    buf[0] = AHT20_CMD_TRIGGER;
    buf[1] = 0x33;
    buf[2] = 0x00; 
    i2c_begin_transmisison(0x38, I2C_MODE_WRITE);
    i2c_transmit_data(buf, 3);
    i2c_end_transmisison();

    Delay_Ms(100); 	// Minimal delay befor reading is 80ms according to the 
                    // AHT20 datasheet 100 ms is a good value

    // reading measurement results
    i2c_begin_transmisison(0x38, I2C_MODE_READ);
    // Receive all data from AHT20
    i2c_receive_data(buf, 7);
    if ((buf[0] & 0x80)) {
        i2c_end_transmisison();
        printf("Measurement error\n");
        return AHT20_ERR_MEASUREMENT; // Measurement failed
    }
    i2c_end_transmisison();
    
    // Reset
    i2c_begin_transmisison(0x38, AHT20_CMD_SOFTRESET);
    i2c_transmit_data(buf, 3);
    i2c_end_transmisison();

    // TODO: add CRC check

    // Combine 20-bit temperature value from result
    uint32_t raw_data;
    raw_data = (((uint32_t)buf[3]) << 16) |
                           (((uint32_t)buf[4]) << 8) |
                           (((uint32_t)buf[5]) << 0);
    
    raw_data = raw_data & 0x000FFFFF; // Keep ony 20 bits of data, zero the rest of them
    float temperature = (float)(raw_data) 
                                 / 1048576.0f * 200.0f
                                 - 50.0f;
    
    // Combine 20-bit humidity value
    raw_data = 0x00000000;
    raw_data = buf[1] << 12;
    raw_data |= buf[2] << 4;
    raw_data |= (buf[3] & 0xF0) >> 4;
    float humidity = ((float)raw_data / 1048576.0f) * 100.0f;

    data->temperature = temperature;
    data->humidity = humidity;
    return AHT20_OK;
}