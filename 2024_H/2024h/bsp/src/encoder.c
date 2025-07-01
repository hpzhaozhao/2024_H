#include "board.h"

int32_t Get_Encoder_countA,encoderA_cnt,Get_Encoder_countB,encoderB_cnt;

//编码器初始化
void encoder_init(void)
{
	//编码器引脚外部中断
	NVIC_ClearPendingIRQ(L_ENCODER_INT_IRQN);
	NVIC_EnableIRQ(L_ENCODER_INT_IRQN);
    NVIC_ClearPendingIRQ(R_ENCODER_INT_IRQN);
	NVIC_EnableIRQ(R_ENCODER_INT_IRQN);
}

void encoder_update(void)
{
	encoderA_cnt = Get_Encoder_countA;
    encoderB_cnt = Get_Encoder_countB;
	Get_Encoder_countA = 0;
    Get_Encoder_countB = 0;//编码器计数值清零
}

//外部中断处理函数
void GROUP1_IRQHandler(void)
{
	uint32_t gpio_status_1,gpio_status_2;

	//获取中断信号情况
	gpio_status_1 = DL_GPIO_getEnabledInterruptStatus(L_ENCODER_PORT, L_ENCODER_LENA_PIN | L_ENCODER_LENB_PIN);
    gpio_status_2 = DL_GPIO_getEnabledInterruptStatus(R_ENCODER_PORT, R_ENCODER_RENA_PIN | R_ENCODER_RENB_PIN);
	//编码器A相上升沿触发
	if((gpio_status_1 & L_ENCODER_LENA_PIN) == L_ENCODER_LENA_PIN)
	{
		//如果在A相上升沿下，B相为低电平
		if(!DL_GPIO_readPins(L_ENCODER_PORT,L_ENCODER_LENB_PIN))
		{
			Get_Encoder_countA--;
		}
		else
		{
			Get_Encoder_countA++;
		}
	}//编码器B相上升沿触发
	else if((gpio_status_1 & L_ENCODER_LENB_PIN)==L_ENCODER_LENB_PIN)
	{
		//如果在B相上升沿下，A相为低电平
		if(!DL_GPIO_readPins(L_ENCODER_PORT,L_ENCODER_LENA_PIN))
		{
			Get_Encoder_countA++;
		}
		else
		{
			Get_Encoder_countA--;
		}
	}
    DL_GPIO_clearInterruptStatus(L_ENCODER_PORT,L_ENCODER_LENA_PIN|L_ENCODER_LENB_PIN);

    if((gpio_status_2 & R_ENCODER_RENA_PIN) == R_ENCODER_RENA_PIN)
	{
		//如果在A相上升沿下，B相为低电平
		if(!DL_GPIO_readPins(R_ENCODER_PORT,R_ENCODER_RENB_PIN))
		{
			Get_Encoder_countB--;
		}
		else
		{
			Get_Encoder_countB++;
		}
	}//编码器B相上升沿触发
	else if((gpio_status_2 & R_ENCODER_RENB_PIN)==R_ENCODER_RENB_PIN)
	{
		//如果在B相上升沿下，A相为低电平
		if(!DL_GPIO_readPins(R_ENCODER_PORT,R_ENCODER_RENA_PIN))
		{
			Get_Encoder_countB++;
		}
		else
		{
			Get_Encoder_countB--;
		}
	}
	//清除状态
	DL_GPIO_clearInterruptStatus(R_ENCODER_PORT,R_ENCODER_RENA_PIN|R_ENCODER_RENB_PIN);
}