
#ifndef __BOARD_H__
#define __BOARD_H__

#include "ti_msp_dl_config.h"
#include "motor.h"
#include "eight_ways.h"
#include "jy61p.h"
#include "timer.h"
#include "encoder.h"
#include "tft180.h"
#include "task.h"
#include "stdio.h"
#include "math.h"
#include "pid.h"

#ifndef u8
#define u8 uint8_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

#ifndef u64
#define u64 uint64_t
#endif
void all_init(void);
/* 延时函数 */
void delay_us(int __us);
void delay_ms(int __ms);

void delay_1us(int __us);
void delay_1ms(int __ms);

#endif
