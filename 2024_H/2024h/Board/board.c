#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "board.h"
#include "ti/driverlib/m0p/dl_core.h"
PID_Controller pid_left, pid_right;
void all_init(void){
    SYSCFG_DL_init();
    jy61pInit();
    tft180_init();
    encoder_init();
    timer_init();
    PID_Init(&pid_left, 25.0f, 5.0f, 0, 0, 1000);
    PID_Init(&pid_right, 25.0f,5.0f, 0, 0, 1000);
}
void delay_us(int __us) { delay_cycles( (CPUCLK_FREQ / 1000 / 1000)*__us); }
void delay_ms(int __ms) { delay_cycles( (CPUCLK_FREQ / 1000)*__ms); }

void delay_1us(int __us) { delay_cycles( (CPUCLK_FREQ / 1000 / 1000)*__us); }
void delay_1ms(int __ms) { delay_cycles( (CPUCLK_FREQ / 1000)*__ms); }
