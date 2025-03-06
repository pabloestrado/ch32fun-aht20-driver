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

 #ifndef AHT20_H
 #define AHT20_H
 
 #define AHT20_ADDR          	0x38 // AHT default i2c address
 #define AHT20_CMD_CALIBRATE 	0xBE // Calibration command
 #define AHT20_CMD_TRIGGER 		0xAC // Trigger reading command
 #define AHT20_CMD_SOFTRESET 	0xBA // Soft reset command
 #define AHT20_STATUS_BUSY 		0x80 // Status bit for busy
 #define AHT20_STATUS_CALIBRATED 0x08 // Status bit for calibrated
 
 #define AHT20_OK				0x00 // No error
 #define AHT20_ERR_NOTFOUND 		0x01 // Error: sensor not responding on I2C bus		
 #define AHT20_ERR_CALIBRATION 	0x02 // Calibration error
 #define AHT20_ERR_MEASUREMENT 	0x03 // Measurement error
 
 typedef struct {
	 float temperature;
	 float humidity;
 } AHT20Data;
 
 uint8_t AHT20_read(AHT20Data *data);
 
 #endif // AHT20_H
