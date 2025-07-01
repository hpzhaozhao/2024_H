#ifndef PID_H
#define PID_H

#include <stdint.h>

// PID参数结构体
typedef struct {
    float Kp;           // 比例系数
    float Ki;           // 积分系数
    float Kd;           // 微分系数
    
    float integral;     // 积分累积值
    float prev_error;   // 上一次的误差值
    
    float output_min;   // PWM输出最小值(0)
    float output_max;   // PWM输出最大值(1000)
    
    float integral_min; // 积分限幅最小值
    float integral_max; // 积分限幅最大值
} PID_Controller;

void PID_Init(PID_Controller *pid, float Kp, float Ki, float Kd,  float min, float max);
float PID_Compute(PID_Controller *pid, float setpoint, float input);
void PID_Reset(PID_Controller *pid);

#endif // PID_H