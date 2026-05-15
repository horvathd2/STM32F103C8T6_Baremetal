/*
 * mpu6050.h
 *
 *  Created on: Oct 27, 2025
 *      Author: hdani
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "main.h"

#define MPU6050_ADDR			0x68

#define MPU6050_ACCEL_REG		0x3B
#define MPU6050_GYRO_REG		0x43

#define MPU6050_PWR_REG1		0x6B
#define MPU6050_PWR_REG2		0x6C

#define MPU6050_INT_PIN_CFG		0x37
#define MPU6050_INT_EN			0x38

#define ACCEL_READ_BYTES		0x6
#define GYRO_READ_BYTES			0x6

/*----COM Interface Selecion----*/
#define MPU6050_USE_I2C			0	//Set to 1 for I2C
#define MPU6050_USE_SPI			1	//Set to 1 for SPI

#if (MPU6050_USE_I2C + MPU6050_USE_SPI) != 1
#error "Must select only one communication protocol (I2C or SPI)."
#endif

typedef enum{
	MPU_OK = 0,
	MPU_FAIL = 1,
}mpu_err_t;

typedef struct MPU6050_t MPU6050_t;

typedef struct{
	GPIO_TypeDef *gpio_port;
	uint32_t *gpio_pin;
}GPIO_mpu6050;

struct MPU6050_t{
	mpu_err_t (*read)(MPU6050_t *self, uint8_t reg, uint8_t *data, uint16_t len);
	mpu_err_t (*write)(MPU6050_t *self, uint8_t reg, const uint8_t *data, uint16_t len);
	void (*delay)(uint32_t ticks);

	I2C_HandleTypeDef *mpu6050_i2c;
	GPIO_mpu6050 *mpu6050_it;
	int16_t accel_val[3];
	int16_t gyro_val[3];
	uint8_t accel_buf[6];
	uint8_t gyro_buf[6];
	uint8_t i2c_tx;
	uint8_t i2c_addr;
};

mpu_err_t mpu6050_init(I2C_HandleTypeDef *mpu6050_i2c, uint8_t i2c_addr, GPIO_mpu6050 *mpu6050_it);
mpu_err_t mpu6050_read(MPU6050_t *mpu6050_dev, uint16_t MemAddress, uint8_t *pData, uint16_t Size, int16_t *val_buff);
mpu_err_t mpu6050_readall(MPU6050_t *mpu6050_dev);

#endif /* INC_MPU6050_H_ */
