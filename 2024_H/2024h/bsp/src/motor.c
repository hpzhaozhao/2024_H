#include "motor.h"
#include "board.h"
#include "tft180.h"
int32_t target_left_speed, target_right_speed;
void Motor_Stop(void)
{
    AIN1_OUT(1);
    AIN2_OUT(1);
    BIN1_OUT(1);
    BIN2_OUT(1);
}

void Car_Control(uint32_t left_speed, uint32_t right_speed, int error){
    if(left_speed > 0){
        AIN1_OUT(1);
        AIN2_OUT(0);
    }
    else {
        AIN1_OUT(0);
        AIN2_OUT(1);
    }
    if( right_speed > 0 ){
        BIN1_OUT(0);
        BIN2_OUT(1);
    }
    else{
        BIN1_OUT(1);
        BIN2_OUT(0);
    }
    target_left_speed = left_speed + error;
    target_right_speed = right_speed - error;
}
