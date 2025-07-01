#ifndef _EIGHT_WAYS_H
#define _EIGHT_WAYS_H

#define I2C_ADDR 0x12
#include "board.h"
#define u8 uint8_t
float PID_IR_Calc(int16_t actual_value);
void IIC_write_data(uint8_t addr,uint8_t data);
uint8_t I2C_read_data(uint8_t addr);
void deal_data(u8 *x1,u8 *x2,u8 *x3,u8 *x4,u8 *x5,u8 *x6,u8 *x7,u8 *x8);
void LineWalking(void);

#endif