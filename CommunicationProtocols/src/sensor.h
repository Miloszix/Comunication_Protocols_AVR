#include <avr/io.h>
#include "I2C.h"
#include "UART.h"

// Type definitions for various sensor data types
typedef int32_t BME280_S32_t;
typedef int64_t BME280_S64_t;
typedef uint32_t BME280_U32_t;

// BME280 I2C address
#define BME280_ADDR 0x76

// Calibration data for the BME280 sensor
uint16_t dig_T1;
int16_t dig_T2, dig_T3;
uint16_t dig_P1;
int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
uint8_t dig_H1, dig_H3;
int16_t dig_H2, dig_H4, dig_H5, dig_H6;

// Variables to store the sensor readings
double temp;
double press;
double hum;

// Create instances for I2C and UART communication
mm::I2C i2c;
mm::UART uart;

/**
 * @brief Writes a value to a register on the BME280 sensor.
 * @param reg Register address to write to.
 * @param value Value to write to the register.
 */
void writeRegister(uint8_t reg, uint8_t value)
{
  i2c.write_register(BME280_ADDR, reg, value);
}

/**
 * @brief Reads a value from a register on the BME280 sensor.
 * @param reg Register address to read from.
 * @return Value read from the register.
 */
uint8_t readRegister(uint8_t reg)
{
  return i2c.read_register(BME280_ADDR, reg);
}

/**
 * @brief Reads a block of data from a specified register on the BME280 sensor.
 * @param reg Starting register address to read from.
 * @param len Number of bytes to read.
 * @param data Pointer to the array to store the read data.
 */
void readBlock(uint8_t reg, uint8_t len, uint8_t *data)
{
  i2c.read_block(BME280_ADDR, reg, data, len);
}

/**
 * @brief Reads the calibration data from the BME280 sensor.
 */
void readCalibrationData()
{
  // Read temperature calibration data
  dig_T1 = (readRegister(0x89) << 8) | readRegister(0x88);
  dig_T2 = (readRegister(0x8B) << 8) | readRegister(0x8A);
  dig_T3 = (readRegister(0x8D) << 8) | readRegister(0x8C);

  // Read pressure calibration data
  dig_P1 = (readRegister(0x8F) << 8) | readRegister(0x8E);
  dig_P2 = (readRegister(0x91) << 8) | readRegister(0x90);
  dig_P3 = (readRegister(0x93) << 8) | readRegister(0x92);
  dig_P4 = (readRegister(0x95) << 8) | readRegister(0x94);
  dig_P5 = (readRegister(0x97) << 8) | readRegister(0x96);
  dig_P6 = (readRegister(0x99) << 8) | readRegister(0x98);
  dig_P7 = (readRegister(0x9B) << 8) | readRegister(0x9A);
  dig_P8 = (readRegister(0x9D) << 8) | readRegister(0x9C);
  dig_P9 = (readRegister(0x9F) << 8) | readRegister(0x9E);

  // Read humidity calibration data
  dig_H1 = readRegister(0xA1);
  dig_H2 = (readRegister(0xE2) << 8) | readRegister(0xE1);
  dig_H3 = readRegister(0xE3);
  dig_H4 = (readRegister(0xE4) << 4) | (readRegister(0xE5) & 0x0F);
  dig_H5 = (readRegister(0xE6) << 4) | (readRegister(0xE5) >> 4);
  dig_H6 = (int8_t)readRegister(0xE7);
}

/**
 * @brief Initializes the BME280 sensor and checks if it is detected.
 */
void initBME280()
{
  uint8_t id = readRegister(0xD0);  // Read the device ID
  if (id == 0x60)  // Check if the sensor is BME280
  {
    uart.transmitString("BME280 detected!");  // Notify via UART if BME280 is detected
  }

  // Configure the sensor
  writeRegister(0xF2, 0b101);  // Set humidity oversampling
  _delay_ms(10);
  writeRegister(0xF4, 0b01101101);  // Set pressure and temperature oversampling, mode to normal
  _delay_ms(10);
  writeRegister(0xF5, 0b10101100);  // Configure the sensor's standby time and filter
  _delay_ms(10);

  readCalibrationData();  // Read the calibration data
}

// Global variable to store fine temperature value for compensation
BME280_S32_t t_fine;

/**
 * @brief Compensates the raw temperature data from the sensor.
 * @param adc_T Raw temperature data from the sensor.
 * @return Compensated temperature value in integer format (0.01 degrees Celsius).
 */
BME280_S32_t BME280_compensate_T_int32(BME280_S32_t adc_T)
{
  BME280_S32_t var1, var2, T;

  // Temperature compensation algorithm
  var1 = ((((adc_T >> 3) - ((BME280_S32_t)dig_T1 << 1))) * ((BME280_S32_t)dig_T2)) >> 11;
  var2 = (((((adc_T >> 4) - ((BME280_S32_t)dig_T1)) * ((adc_T >> 4) - ((BME280_S32_t)dig_T1))) >> 12) *
          ((BME280_S32_t)dig_T3)) >>
         14;
  t_fine = var1 + var2;  // Fine temperature value for compensation
  T = (t_fine * 5 + 128) >> 8;  // Final compensated temperature value
  return T;
}

/**
 * @brief Compensates the raw pressure data from the sensor.
 * @param adc_P Raw pressure data from the sensor.
 * @return Compensated pressure value in Pa.
 */
BME280_U32_t BME280_compensate_P_int64(BME280_S32_t adc_P)
{
  BME280_S64_t var1, var2, p;

  // Pressure compensation algorithm
  var1 = ((BME280_S64_t)t_fine) - 128000;
  var2 = var1 * var1 * (BME280_S64_t)dig_P6;
  var2 = var2 + ((var1 * (BME280_S64_t)dig_P5) << 17);
  var2 = var2 + (((BME280_S64_t)dig_P4) << 35);
  var1 = ((var1 * var1 * (BME280_S64_t)dig_P3) >> 8) + ((var1 * (BME280_S64_t)dig_P2) << 12);
  var1 = (((((BME280_S64_t)1) << 47) + var1)) * ((BME280_S64_t)dig_P1) >> 33;
  
  if (var1 == 0)
  {
    return 0;  // Avoid division by zero error
  }

  p = 1048576 - adc_P;
  p = (((p << 31) - var2) * 3125) / var1;
  var1 = (((BME280_S64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
  var2 = (((BME280_S64_t)dig_P8) * p) >> 19;
  p = ((p + var1 + var2) >> 8) + (((BME280_S64_t)dig_P7) << 4);
  return (BME280_U32_t)p;
}

/**
 * @brief Compensates the raw humidity data from the sensor.
 * @param adc_H Raw humidity data from the sensor.
 * @return Compensated humidity value in percentage.
 */
BME280_U32_t BME280_compensate_H_int32(BME280_S32_t adc_H)
{
  BME280_S32_t v_x1_u32r;

  // Humidity compensation algorithm
  v_x1_u32r = (t_fine - ((BME280_S32_t)76800));
  v_x1_u32r = (((((adc_H << 14) - (((BME280_S32_t)dig_H4) << 20) - (((BME280_S32_t)dig_H5) * v_x1_u32r)) +
                 ((BME280_S32_t)16384)) >> 15) *
               (((((((v_x1_u32r * ((BME280_S32_t)dig_H6)) >> 10) * (((v_x1_u32r *
                                                                      ((BME280_S32_t)dig_H3)) >> 11) +
                                                                    ((BME280_S32_t)32768))) >> 10) +
                  ((BME280_S32_t)2097152)) *
                     ((BME280_S32_t)dig_H2) +
                 8192) >> 14));

  // Apply the limits to the humidity value
  v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((BME280_S32_t)dig_H1)) >> 4));
  v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
  v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
  return (BME280_U32_t)(v_x1_u32r >> 12);
}

/**
 * @brief Reads raw sensor data (temperature, pressure, humidity) from the BME280 sensor.
 */
void readRawData()
{
  uint8_t data[8];

  // Start a measurement
  writeRegister(0xF4, 0b01101101);
  _delay_ms(500);

  // Read the sensor data
  for (uint8_t i = 0; i < 8; i++)
  {
    data[i] = readRegister(0xF7 + i);
    _delay_ms(10);
  }

  // Combine the raw data values
  uint32_t press_raw = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
  uint32_t temp_raw = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4);
  uint16_t hum_raw = (data[6] << 8) | data[7];

  // Compensate the raw values and store the result
  temp = BME280_compensate_T_int32(temp_raw) / 100.0;
  press = BME280_compensate_P_int64(press_raw) / 256.0 / 100.0;
  hum = BME280_compensate_H_int32(hum_raw) / 1024.0;

  // Send the raw data via UART for debugging
  uart.transmitString("Raw data: ");
  for (uint8_t i = 0; i < 8; i++)
  {
    char buffer[20];
    sprintf(buffer, "Testowa: %.d \n", data[i]);
    uart.transmitString(buffer);
    uart.transmitString(" ");
  }
}

/**
 * @brief Returns the current temperature reading.
 * @return Temperature in degrees Celsius.
 */
double getTemp()
{
  return temp;
}

/**
 * @brief Returns the current humidity reading.
 * @return Humidity as a percentage.
 */
double getHum()
{
  return hum;
}

/**
 * @brief Returns the current pressure reading.
 * @return Pressure in hPa.
 */
double getPress()
{
  return press;
}
