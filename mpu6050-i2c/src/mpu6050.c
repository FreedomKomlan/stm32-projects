#include "mpu6050.h"

void mpu6050_init_default_config(MPU6050_Config *config) {
    config->device_address = MPU6050_ADDR_AD0; // Default I2C address (AD0 = 0)
    config->pwr_mgmt_1 = MPU6050_WAKE_MODE; // Wake up the MPU6050
    config->gyro_full_scale_range = GYRO_FS_250DPS;
    config->accel_full_scale_range = ACCEL_FS_2G;
    config->filter_freq_config = FILTER_FREQ_188HZ; // Recommended for general use and Sample Rate value to be set to 1kHz (0)
    config->sample_rate_div = SMPLRT_DIV_1KHZ; // Sample Rate = Gyro Output Rate / (1 + SMPLRT_DIV) = 8kHz / (1 + 0) = 8kHz
}

uint8_t mpu6050_init(MPU6050_Config config) {
    /* Initialization sequence for MPU6050
        * 0. Check the WHO_AM_I register to verify communication with the device (Optional but recommended)
        * 1. Wake up the MPU6050 by writing 0 to the PWR_MGMT_1 register
        * 2. Set the gyro full scale range (e.g., FS_GYRO_250)
        * 3. Set the accelerometer full scale range (e.g., FS_ACCEL_2G)
        * 4. Configure any additional settings as needed (e.g., sample rate, filters)
        * Note: The actual I2C write functions are not implemented here and should be defined separately.
    */

    uint8_t check;
    uint8_t data;

    HAL_I2C_Mem_Read(&mpu6050_i2c, config.device_address, REG_WHO_AM_I, 1, &check, 1, HAL_MAX_DELAY);
    if (check != 0x68) {
        return 1; // Device not found or communication error
    }
   
    HAL_I2C_Mem_Write(&mpu6050_i2c, config.device_address, REG_PWR_MGMT_1, 1, &config.pwr_mgmt_1, 1, HAL_MAX_DELAY);
    HAL_I2C_Mem_Write(&mpu6050_i2c, config.device_address, REG_GYRO_CONFIG, 1, &config.gyro_full_scale_range, 1, HAL_MAX_DELAY);
    HAL_I2C_Mem_Write(&mpu6050_i2c, config.device_address, REG_ACCEL_CONFIG, 1, &config.accel_full_scale_range, 1, HAL_MAX_DELAY);
    HAL_I2C_Mem_Write(&mpu6050_i2c, config.device_address, REG_FILTER_FREQ_CONFIG, 1, &config.filter_freq_config, 1, HAL_MAX_DELAY);
    HAL_I2C_Mem_Write(&mpu6050_i2c, config.device_address, REG_SMPLRT_DIV, 1, &config.sample_rate_div, 1, HAL_MAX_DELAY);
    return 0; // Success

}

