#include "ti/driverlib/dl_i2c.h"
#include "board.h"

#define CHANGE_THRESHOLD 3

u8 trun_flag = 0;
static int16_t err = 0;

void IIC_write_data(uint8_t addr,uint8_t data){
    uint8_t temp[2];
    temp[0] = addr;
    temp[1] = data;
    
    DL_I2C_fillControllerTXFIFO(I2C_eightways_INST, temp, 2);
    while (!(DL_I2C_getControllerStatus(I2C_eightways_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));
    DL_I2C_startControllerTransfer(I2C_eightways_INST, I2C_ADDR, DL_I2C_CONTROLLER_DIRECTION_TX, 2);
    while (DL_I2C_getControllerStatus(I2C_eightways_INST) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
    while (!(DL_I2C_getControllerStatus(I2C_eightways_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));
}

uint8_t I2C_read_data(uint8_t addr) {
    uint8_t data;
    DL_I2C_fillControllerTXFIFO(I2C_eightways_INST, &addr, 1);

	DL_I2C_disableInterrupt(I2C_eightways_INST, DL_I2C_INTERRUPT_CONTROLLER_TXFIFO_TRIGGER);
    while (!(DL_I2C_getControllerStatus(I2C_eightways_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));
    DL_I2C_startControllerTransfer(I2C_eightways_INST, I2C_ADDR, DL_I2C_CONTROLLER_DIRECTION_TX, 1);
    while (DL_I2C_getControllerStatus(I2C_eightways_INST) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
    while (!(DL_I2C_getControllerStatus(I2C_eightways_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));
 
    DL_I2C_startControllerTransfer(I2C_eightways_INST, I2C_ADDR, DL_I2C_CONTROLLER_DIRECTION_RX, 1);
    while (DL_I2C_getControllerStatus(I2C_eightways_INST) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
    while (!(DL_I2C_getControllerStatus(I2C_eightways_INST) & DL_I2C_CONTROLLER_STATUS_IDLE));
    data = DL_I2C_receiveControllerData(I2C_eightways_INST);
 
    return data;
}
void deal_data(u8 *x1,u8 *x2,u8 *x3,u8 *x4,u8 *x5,u8 *x6,u8 *x7,u8 *x8)
{
	u8 buf = 0xFF;
	buf = I2C_read_data(0x30);
	
	*x1 = (buf>>7)&0x01;
	*x2 = (buf>>6)&0x01;
	*x3 = (buf>>5)&0x01;
	*x4 = (buf>>4)&0x01;
	*x5 = (buf>>3)&0x01;
	*x6 = (buf>>2)&0x01;
	*x7 = (buf>>1)&0x01;
	*x8 = (buf>>0)&0x01;
}
void LineWalking(void)
{
	static u8 x1,x2,x3,x4,x5,x6,x7,x8;
 	deal_data(&x1,&x2,&x3,&x4,&x5,&x6,&x7,&x8);
	if(x1 == 0 && x2 == 0  && x3 == 0&& x4 == 0 && x5 == 0 && x6 == 1  && x7 == 1 && x8 == 1) // 0000 0111
	{
		err = -20;
       delay_ms(50);
	}

	else if(x1 == 0 && x2 == 0  && x3 == 0&& x4 == 0 && x5 ==1  && x6 == 1  && x7 == 1 && x8 == 1) // 0000 1111
	{
		err = -20;
       delay_ms(50);
	}

		else if(x1 == 0 && x2 == 0  && x3 == 0&& x4 == 1 && x5 == 1 && x6 == 1  && x7 == 1 && x8 == 1) // 00011111
	{
		err = -16;
       delay_ms(50);
	}
   else if(x1 == 1 && x2 == 1  && x3 == 1&& x4 == 0 && x5 == 0 && x6 == 0  && x7 == 0 && x8 == 0) // 1110 0000
	{
		err = 20;
       delay_ms(50);
	}
	    else if(x1 == 1 && x2 == 1  && x3 == 1&& x4 == 1 && x5 == 0 && x6 == 0  && x7 == 0 && x8 == 0) // 1111 0000
	{
		err = 20;
        delay_ms(50);
	}
		else if(x1 == 1 && x2 == 1  && x3 == 1&& x4 == 1 && x5 == 1 && x6 == 0  && x7 == 0 && x8 == 0) // 1111 1000
	{
		err = 16;
        delay_ms(50);
	}
	
	else if((x1 == 0 && x2 == 1 && x3 == 1) && (x6 == 0 || x7 == 0 || x8 == 0))
    {
        err = -20;  // 增加转向幅度
        delay_ms(50);  // 统一延迟时间
    }

	else if((x8 == 0 && x4 == 0 && x5 == 1)||(x8 == 0 && x7==0&& x1==0 &&x2==0&& x4 == 1 && x5 == 1)||((x8 == 0 && x7 == 1 && x6 == 1) && (x1 == 0 || x2 == 0 || x3 == 0)))
    {
        err = 20;  // 增加转向幅度
        delay_ms(50);  // 统一延迟时间
    }
    //走到交叉路
    else if(x1 == 0 &&  x2 == 0  && x7 == 0 && x8 == 0 ) //俩边都亮，直跑 
	{
		err = 0;
		if(trun_flag == 1)
		{
			trun_flag = 0;//走到圈了    Walking in circles.
		}
	}
    //直线与圆弧弯
	else if(x1 == 1 && x2 == 1  && x3 == 1&& x4 == 0 && x5 == 1 && x6 == 1  && x7 == 1 && x8 == 1) // 1110 1111
	{
		err = 0;
	}
	else if(x1 == 1 && x2 == 1  && x3 == 0&& x4 == 0 && x5 == 1 && x6 == 1  && x7 == 1 && x8 == 1) // 1100 1111
	{
		err = -4;
	}

	else if(x1 == 1 && x2 == 0  && x3 == 0&& x4 == 1 && x5 == 1 && x6 == 1  && x7 == 1 && x8 == 1) // 1001 1111
	{
		err = -4;
	}
   
		else if(x1 == 0 && x2 == 0  && x3 == 1&& x4 == 1 && x5 == 1 && x6 == 1  && x7 == 1 && x8 == 1) // 0011 1111
	{
		err = -10;  
	}
	else if(x1 == 0 && x2 == 1  && x3 == 1&& x4 == 1 && x5 == 1 && x6 == 1  && x7 == 1 && x8 == 1) // 0111 1111
	{
		err = -20; 
	}

	
	else if(x1 == 1 && x2 == 1  && x3 == 1&& x4 == 1 && x5 == 0 && x6 == 1  && x7 == 1 && x8 == 1) // 1111 0111
	{
		err = 0;
	} 
	else if(x1 == 1 && x2 == 1  && x3 == 1&& x4 == 1 && x5 == 0 && x6 == 0  && x7 == 1 && x8 == 1) // 1111 0011
	{
		err = 4;
	}

	else if(x1 == 1 && x2 == 1  && x3 == 1&& x4 == 1 && x5 == 1 && x6 == 0  && x7 == 0 && x8 == 1) // 1111 1001
	{
		err = 6;
	}
	

	else if(x1 == 1 && x2 == 1  && x3 == 1&& x4 == 1 && x5 == 1 && x6 == 1  && x7 == 0 && x8 == 0) // 1111 1100
	{
		err = 10; 
	}
	else if(x1 == 1 && x2 == 1  && x3 == 1&& x4 == 1 && x5 == 1 && x6 == 1  && x7 == 1 && x8 == 0) // 1111 1110
	{
		err = 20;
	}
	else if(x1 == 1 &&x2 == 1 &&x3 == 1 && x4 == 0 && x5 == 0 && x6 == 1 && x7 == 1&& x8 == 1) //直走 go straight
	{
		err = 0;
	}
    Car_Control(30,30,err);
}   
