#ifndef MPU6050_H
#define MPU6050_H
#include "stm32f1xx_hal.h" // Include the appropriate HAL header for your STM32 series (e.g., stm32f1xx_hal.h, stm32f4xx_hal.h, etc.)
#include <stdint.h>

#define mpu6050_i2c hi2c1 // Replace with your actual I2C handle (e.g., hi2c1, hi2c2, etc.)
extern I2C_HandleTypeDef mpu6050_i2c; // Declare the I2C handle as an external variable to be defined in the source file

typedef enum {
    MPU6050_ADDR_AD0 = 0x68, // Adresse I2C du MPU6050 (AD0 = 0)/  8 bits (0x68 << 1 = 0xD0 pour écriture, 0xD1 pour lecture)
    MPU6050_ADDR_AD1 = 0x69, // Adresse I2C du MPU6050 (AD0 = 1)/  8 bits (0x69 << 1 = 0xD2 pour écriture, 0xD3 pour lecture)
} MPU6050_I2C_Address;

// Register addresses for reading/writing data
#define REG_WHO_AM_I 0x75
#define REG_PWR_MGMT_1 0x6B
#define REG_GYRO_CONFIG 0x1B
#define REG_ACCEL_CONFIG 0x1C
#define REG_FILTER_FREQ_CONFIG 0x1A
#define REG_SMPLRT_DIV 0x19
#define REG_ACCEL_XOUT_H 0x3B
#define REG_USR_CTRL 0x6A

#define ACCEL_SENSITIVITY_2G 16384.0 // LSB/g
#define ACCEL_SENSITIVITY_4G 8192.0  // LSB/g
#define ACCEL_SENSITIVITY_8G 4096.0  // LSB/g
#define ACCEL_SENSITIVITY_16G 2048.0  // LSB/g (16g range has lower sensitivity, so more LSB/g)

#define GYRO_SENSITIVITY_250DPS 131.0   // LSB/°/s
#define GYRO_SENSITIVITY_500DPS 65.5  // LSB/°/s
#define GYRO_SENSITIVITY_1000DPS 32.8 // LSB/°/s
#define GYRO_SENSITIVITY_2000DPS 16.4  // LSB/°/s

typedef enum {
    MPU6050_SLEEP_MODE = 1,
    MPU6050_WAKE_MODE = 0
} MPU6050_Mode;

typedef enum {
    ACCEL_FS_2G = 0,
    ACCEL_FS_4G = 1,
    ACCEL_FS_8G = 2,
    ACCEL_FS_16G = 3
} AccelFullScaleRange;

typedef enum {
    GYRO_FS_250DPS = 0,
    GYRO_FS_500DPS = 1,
    GYRO_FS_1000DPS = 2,
    GYRO_FS_2000DPS = 3
} GyroFullScaleRange;

typedef enum {
    FILTER_FREQ_256HZ = 0,
    FILTER_FREQ_188HZ = 1, // Recommended for general use and Sample Rate value to be set to 1kHz (0)
    FILTER_FREQ_98HZ = 2,
    FILTER_FREQ_42HZ = 3,
    FILTER_FREQ_20HZ = 4,
    FILTER_FREQ_10HZ = 5,
    FILTER_FREQ_5HZ = 6
} FilterFreqConfig;


typedef enum {
    SMPLRT_DIV_1KHZ = 0, // Sample Rate = Gyro Output Rate / (1 + SMPLRT_DIV) = 8kHz / (1 + 0) = 8kHz
    SMPLRT_DIV_500HZ = 1, // Sample Rate = 1kHz / (1 + 1) = 500Hz
    SMPLRT_DIV_250HZ = 3, // Sample Rate = 1kHz / (1 + 3) = 250Hz
    SMPLRT_DIV_125HZ = 7 // Sample Rate = 1kHz / (1 + 7) = 125Hz
} SampleRateDiv;

void mpu6050_init_default_config(MPU6050_Config *config);
uint8_t mpu6050_init(MPU6050_Config config);

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


// What if I change all the define into data members of a struct ?

typedef struct {
    MPU6050_I2C_Address device_address; // I2C address of the MPU6050 (e.g., 0x68 or 0x69)
    MPU6050_Mode pwr_mgmt_1;
    GyroFullScaleRange gyro_full_scale_range;
    AccelFullScaleRange accel_full_scale_range;
    FilterFreqConfig filter_freq_config;
    SampleRateDiv sample_rate_div;
} MPU6050_Config;

#endif // MPU6050_H