#include "pid.h"
#include <math.h>
#include "board.h"
extern int32_t target_left_speed, target_right_speed;
extern int32_t ENA, ENB;
PID_Controller pid_left, pid_right;
// PID初始化
void PID_Init(PID_Controller *pid, float Kp, float Ki, float Kd, float min, float max) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    // 重置内部状态 
    pid->integral = 0.0f;
    pid->prev_error = 0.0f;
    // 输出限幅
    pid->output_min = min;
    pid->output_max = max;
    // 设置积分限幅(防止积分饱和)
    // 积分限幅 = 输出范围 / Ki 的 50%
    pid->integral_min = -fabsf(max / Ki) * 0.5f;
    pid->integral_max = fabsf(max / Ki) * 0.5f;
}
// 计算PID输出
float PID_Compute(PID_Controller *pid, float setpoint, float input) 
{
    // 计算时间间隔(秒)
    float dt = 0.02f; // 固定20ms控制周期
    pid->prev_error = setpoint - input;
    // 当前误差
    float error = setpoint - input;
    // 比例
    float proportional = pid->Kp * error;
    // 积分项
    pid->integral += error * dt;
    // 积分限幅
    if (pid->integral > pid->integral_max) {
        pid->integral = pid->integral_max;
    } else if (pid->integral < pid->integral_min) {
        pid->integral = pid->integral_min;
    }
    float integral = pid->Ki * pid->integral;
    // 微分
    float derivative = pid->Kd * (error - pid->prev_error) / dt;
    // 输出
    float output = proportional + integral + derivative;
    // 输出限幅
    if (output > pid->output_max) {
        output = pid->output_max;
    } else if (output < pid->output_min) {
        output = pid->output_min;
    }
    // 保存当前误差下次计算使用
    pid->prev_error = error;
    return output;
}

void pid_Control()
{
    float target_left = target_left_speed ;
    float target_right = target_right_speed ;
    
    float pwm_left = PID_Compute(&pid_left, target_left, ENA);
    float pwm_right = PID_Compute(&pid_right, target_right, ENB);

    tft180_show_float(0, 32,pwm_left, 6, 0);
    tft180_show_float(0, 48,pwm_right, 6, 0);
    DL_TimerG_setCaptureCompareValue(PWM_0_INST, (uint32_t)pwm_left, GPIO_PWM_0_C1_IDX);
    DL_TimerG_setCaptureCompareValue(PWM_0_INST, (uint32_t)pwm_right, GPIO_PWM_0_C0_IDX);
}