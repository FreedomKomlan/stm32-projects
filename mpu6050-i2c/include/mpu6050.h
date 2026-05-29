#ifndef MPU6050_H
#define MPU6050_H
#include <stdint.h>

#define MPU6050_ADDR 0x68 // Adresse I2C du MPU6050
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

#define REG_CONFIG_GYRO 0x1B
#define REG_CONFIG_ACCEL 0x1C
#define REG_ACCEL_XOUT_H 0x3B
#define REG_USR_CTRL 0x6A
// #define REG_DATA 0x3B

void mpu6050_init(void);
void mpu6050_read_accel(int16_t* ax, int16_t* ay, int16_t* az);
void mpu6050_read_gyro(int16_t* gx, int16_t* gy, int16_t* gz);

#endif // MPU6050_H