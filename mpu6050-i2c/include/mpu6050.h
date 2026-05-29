#ifndef MPU6050_H
#define MPU6050_H
#include <stdint.h>

#define MPU6050_ADDR_AD0 0x68 // Adresse I2C du MPU6050 (AD0 = 0)/  8 bits (0x68 << 1 = 0xD0 pour écriture, 0xD1 pour lecture)
#define MPU6050_ADDR_AD1 0x69 // Adresse I2C du MPU6050 (AD0 = 1)/  8 bits (0x69 << 1 = 0xD2 pour écriture, 0xD3 pour lecture)
#define MPU6050_PWR_MGMT_1 0x6B
#define WHO_AM_I_REG 0x75

#define FS_GYRO_250 0x00
#define FS_GYRO_500 0x08
#define FS_GYRO_1000 0x10
#define FS_GYRO_2000 0x18

#define FS_ACCEL_2G 0x00
#define FS_ACCEL_4G 0x08
#define FS_ACCEL_8G 0x10
#define FS_ACCEL_16G 0x18

// Filter frequency configuration values (example values, actual values depend on the desired cutoff frequency)
#define FILTER_FREQ_256HZ 0x00
#define FILTER_FREQ_188HZ 0x01  // Recommended for general use and Sample Rate value to be set to 1kHz (0)
#define FILTER_FREQ_98HZ 0x02
#define FILTER_FREQ_42HZ 0x03
#define FILTER_FREQ_20HZ 0x04
#define FILTER_FREQ_10HZ 0x05
#define FILTER_FREQ_5HZ 0x06

#define SMPLRT_DIV_1KHZ 0x00  // Sample Rate = Gyro Output Rate / (1 + SMPLRT_DIV) = 8kHz / (1 + 0) = 8kHz
#define SMPLRT_DIV_500HZ 0x01  // Sample Rate = 1kHz / (1 + 1) = 500Hz
#define SMPLRT_DIV_250HZ 0x03  // Sample Rate = 1kHz / (1 + 3) = 250Hz
#define SMPLRT_DIV_125HZ 0x07  // Sample Rate = 1kHz / (1 + 7) = 125Hz

// Register addresses for reading/writing data
#define REG_CONFIG_GYRO 0x1B
#define REG_CONFIG_ACCEL 0x1C
#define REG_FILTER_FREQ_CONFIG 0x1A
#define REG_SMPLRT_DIV 0x19
#define REG_ACCEL_XOUT_H 0x3B
#define REG_USR_CTRL 0x6A
// #define REG_DATA 0x3B


void mpu6050_init(void);
void mpu6050_test_connection(void);

// Get raw sensor data
void mpu6050_readRawAccel(int16_t* ax, int16_t* ay, int16_t* az);
void mpu6050_readRawGyro(int16_t* gx, int16_t* gy, int16_t* gz);
void mpu6050_readRawTemp(int16_t* temp);
void mpu6050_readAllRawData(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz, int16_t* temp);

// Compensation and conversion functions
void mpu6050_getAccel_g(int16_t ax, int16_t ay, int16_t az, float* ax_g, float* ay_g, float* az_g);
void mpu6050_getGyro_dps(int16_t gx, int16_t gy, int16_t gz, float* gx_dps, float* gy_dps, float* gz_dps);
float mpu6050_getTemp_C(int16_t temp);

void mpu6050_calibrate_gyro(void);
void mpu6050_calibrate_accel(void);

#endif // MPU6050_H