#include "board.h"
#include "encoder.h"
#include "motor.h"
#include "task.h"
#include "tft180.h"
#include "ti_msp_dl_config.h"
#include "stdio.h"
#include "timer.h"
extern int32_t encoderA_cnt,encoderB_cnt;
int main(void)
{
    all_init();
    while (1)
    {
       all();
     // Car_Control(30,30,0);
    }
}