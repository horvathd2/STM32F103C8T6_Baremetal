/*
 * i2c.h
 *
 *  Created on: May 20, 2026
 *      Author: hdani
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "stm32f1xx.h"

typedef enum{
	I2C_OK,
	I2C_FAIL,
}i2c_err_t;

i2c_err_t i2c_transmit(uint32_t reg, const uint8_t *data, uint16_t size, uint32_t timeout);

#endif /* I2C_H_ */
