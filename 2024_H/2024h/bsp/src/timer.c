#include "board.h"
#include "tft180.h"
extern int32_t encoderA_cnt,encoderB_cnt;
int32_t ENA,ENB;
void timer_init(void)
{
    //定时器中断
	NVIC_ClearPendingIRQ(TIMER_TICK_INST_INT_IRQN);
	NVIC_EnableIRQ(TIMER_TICK_INST_INT_IRQN);
}

//电机编码器脉冲计数
void TIMER_TICK_INST_IRQHandler(void)
{
	//20ms归零中断触发
	if( DL_TimerA_getPendingInterrupt(TIMER_TICK_INST) == DL_TIMER_IIDX_ZERO )
	{
		//编码器更新
		encoder_update();
        ENA = encoderA_cnt;
        ENB = -encoderB_cnt;
		pid_Control();
		tft180_show_float(0, 0,ENA, 5, 2);
        tft180_show_float(0, 16,ENB, 5, 2);
	}
}