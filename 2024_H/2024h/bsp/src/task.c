#include "board.h"
#include "motor.h"
int task_flag = 0;//全局变量，标志位，按下按键后开始执行任务
int quanbai_flag = 35;
void all(void){
    while (1){
        if (DL_GPIO_readPins(KEY_PORT, KEY_K1_PIN) == 0){
            task_flag = 1;
        }
        if (DL_GPIO_readPins(KEY_PORT, KEY_K2_PIN) == 0){
            task_flag = 2;
        } 
        if (DL_GPIO_readPins(KEY_PORT, KEY_K3_PIN) == 0){
            task_flag = 3; // 停止任务
        }

        if (task_flag == 1){
            delay_ms(1000);
            task_1();
            task_flag = 0;
        }
        else if (task_flag == 2){
            delay_ms(1000);
            task_2();
            task_flag = 0;
        }
        else if (task_flag == 3){
            delay_ms(1000);
            task_3();
            task_flag = 0;
        }
        // else if (task_flag == 4){
        //     delay_ms(1000);
        //     task_4();
        //     task_flag = 0;
        // }


    }
}
//2024H第一道题
void task_1(void){
    u8 x1,x2,x3,x4,x5,x6,x7,x8;
    float yawz_init, yawz_now, err;
    // 1. 记录初始yaw角
    Gyro_Struct *angle = get_angle();
    yawz_init = angle->z;//读取初始yaw值
    while(1)
    {
        angle = get_angle();
        yawz_now = angle->z; // 实时读取yaw角
        // 计算偏航误差，并纠正输出
        err = yawz_now - yawz_init;
        if(err > 180) err -= 360;
        if(err < -180) err += 360;
        // err > 0 偏左，err < 0 偏右
        deal_data(&x1,&x2,&x3,&x4,&x5,&x6,&x7,&x8);//读取八路循迹
        Car_Control(30,30, err); // 用err作为控制输入
        if ((x4 == 0 && x5 == 0)||(x3 == 0 && x4 == 0)||(x5 == 0 && x6 == 0)){//0表示识别到黑线，灯亮，x1到8从左到右
            Motor_Stop();
            for(int i=0;i<3;i++)
            {
                DL_GPIO_clearPins(LED_PORT,LED_PIN_22_PIN);
                delay_ms(500);
                DL_GPIO_setPins(LED_PORT,LED_PIN_22_PIN);
                delay_ms(500);
                // DL_GPIO_clearPins(BEE_PORT,BEE_PIN_23_PIN);//蜂鸣器好像有点问题，先放
                // delay_ms(1000);
            }
            return;
        }
        delay_ms(10);
    }
}
void task_2(void){
    u8 x1,x2,x3,x4,x5,x6,x7,x8;
    float yawz_init1, yawz_init2, yawz_now, err;
    int state = 0; // 0:第一次空白直行 1:第一个半圆循迹 2:第二次空白直行 3:第二个半圆循迹 4:停车
    Gyro_Struct *angle = get_angle();
    yawz_init1 = angle->z; // 第一次空白区直行基准

    while(1){
        deal_data(&x1,&x2,&x3,&x4,&x5,&x6,&x7,&x8);
        angle = get_angle();
        yawz_now = angle->z;

        switch(state){
        case 0: // 第一次空白区直行
            err = yawz_now - yawz_init1;
            if(err > 180) err -= 360;
            if(err < -180) err += 360;
            Car_Control(30,30, err);
            // 检测到黑线，进入第一个半圆循迹
            if(x3==0 || x4==0 || x5==0 || x6==0){
                state = 1;
            }
            break;
        case 1: // 第一个半圆循迹
            if(x1==1 && x2==1 && x3==1 && x4==1 && x5==1 && x6==1 && x7==1 && x8==1){
                // 离开黑线，进入第二次空白区
                yawz_init2 = yawz_init1 + 180;
                if(yawz_init2 > 180) yawz_init2 -= 360;
                if(yawz_init2 < -180) yawz_init2 += 360;
                state = 2;
            }else{
                LineWalking();
            }
            break;
        case 2: // 第二次空白区直行
            err = yawz_now - yawz_init2;
            if(err > 180) err -= 360;
            if(err < -180) err += 360;
            Car_Control(30,30, err);
            // 检测到黑线，进入第二个半圆循迹
            if(x3==0 || x4==0 || x5==0 || x6==0){
                state = 3;
            }
            break;
        case 3: // 第二个半圆循迹
            if(x1==1 && x2==1 && x3==1 && x4==1 && x5==1 && x6==1 && x7==1 && x8==1){
                // 离开黑线，停车
                state = 4;
            }else{
                LineWalking();
            }
            break;
        case 4: // 停车
            Motor_Stop();
            for(int i=0;i<3;i++){
                DL_GPIO_clearPins(LED_PORT,LED_PIN_22_PIN);
                delay_ms(500);
                DL_GPIO_setPins(LED_PORT,LED_PIN_22_PIN);
                delay_ms(500);
            }
            return;
        }
        delay_ms(10);
    }
}
// void task_3(void){
//     u8 x1,x2,x3,x4,x5,x6,x7,x8;
//     float yawz_init, yawz_now, err;
//     float turn_angle = 36.78;
//     float yawz_left, yawz_right, yaw_1;
//     int state = 0; // 状态机
//     Gyro_Struct *angle = get_angle();
//     yawz_init = angle->z; // 起点yaw
//     yaw_1 = yawz_init + 180;
//     if(yaw_1 > 180) yaw_1 -= 360;
//     if(yaw_1 < -180) yaw_1 += 360;

//     while(1){
//         deal_data(&x1,&x2,&x3,&x4,&x5,&x6,&x7,&x8);
//         angle = get_angle();
//         yawz_now = angle->z;

//         switch(state){
//         case 0: // 左转arccos(0.8)度
//             yawz_left = yawz_init + turn_angle;
//             if(yawz_left > 180) yawz_left -= 360;
//             if(yawz_left < -180) yawz_left += 360;
//             err = yawz_now - yawz_left;
//             if(err > 180) err -= 360;
//             if(err < -180) err += 360;
//             if(fabs(err) > 2){
//                 Car_Control(10,10,-10); // 左转
//             }else{
//                 state = 1;
//             }
//             break;
//         case 1: // 第一次空白直行
//             err = yawz_now - yawz_left;
//             if(err > 180) err -= 360;
//             if(err < -180) err += 360;
//             Car_Control(30,30,err);
//             if((x1==0 && x2==0)||(x2==0 && x3==0) || ( x3==0 && x4==0) ||(x4==0 && x5==0)||( x5==0 && x6==0) || ( x6==0 && x7==0) ||( x7==0 && x8==0)  ){
//                 //delay_ms(500);
//                 //Motor_Stop();
//                 state = 3;
//             }
//             break;
//         case 2: // 半圆循迹前，先调整为初始yaw
//             err = yawz_now - yawz_init;
//             if(err > 180) err -= 360;
//             if(err < -180) err += 360;
//             if(fabs(err) > 2){
//                 Car_Control(10,10,10); // 调整到初始yaw
//             }else{
//                 state = 3;
//             }
//             break;
//         case 3: // 半圆循迹
//             if(x1==1 && x2==1 && x3==1 && x4==1 && x5==1 && x6==1 && x7==1 && x8==1){
//                 delay_ms(100);
//                 state = 5;
//             }else{
//                 LineWalking();
//             }
//             break;
//         case 4: // 半圆循迹后，先调整为yaw_1
//             err = yawz_now - yaw_1;
//             if(err > 180) err -= 360;
//             if(err < -180) err += 360;
//             if(fabs(err) > 2){
//                 Car_Control(10,10,10); // 调整到yaw_1
//             }else{
//                 state = 5;
//             }
//             break;
//         case 5: // 右转arccos(0.8)度
//             yawz_right = yawz_left + 2*(90 - turn_angle); // 左转+右转=180度
//             if(yawz_right > 180) yawz_right -= 360;
//             if(yawz_right < -180) yawz_right += 360;
//             err = yawz_now - yawz_right;
//             if(err > 180) err -= 360;
//             if(err < -180) err += 360;
//             if(fabs(err) > 2){
//                 Car_Control(10,10,10); // 右转
//             }else{
//                 state = 6;
//             }
//             break;
//         case 6: // 第二次空白直行
//             err = yawz_now - yawz_right;
//             if(err > 180) err -= 360;
//             if(err < -180) err += 360;
//             Car_Control(30, 30,err);
//             if((x1==0 && x2==0)||(x2==0 && x3==0) || ( x3==0 && x4==0) ||(x4==0 && x5==0)||( x5==0 && x6==0) || ( x6==0 && x7==0) ||( x7==0 && x8==0)){
                
//                 state = 8;
//             }
//             break;
//         case 7: // 第二次半圆循迹前，先调整为yaw_1
//             err = yawz_now - yaw_1;
//             if(err > 180) err -= 360;
//             if(err < -180) err += 360;
//             if(fabs(err) > 2){
//                 Car_Control(10,10,-10); // 调整到yaw_1
//             }else{
//                 state = 8;
//             }
//             break;
//         case 8: // 第二次半圆循迹
//             if(x1==1 && x2==1 && x3==1 && x4==1 && x5==1 && x6==1 && x7==1 && x8==1){
//                 delay_ms(100);
//                 state = 10;
//             }else{
//                 LineWalking();
//             }
//             break;
//         case 9: // 第二次半圆循迹后，先调整为初始yaw
//             err = yawz_now - yawz_init;
//             if(err > 180) err -= 360;
//             if(err < -180) err += 360;
//             if(fabs(err) > 2){
//                 Car_Control(10,10,-10); // 调整到初始yaw
//             }else{
//                 state = 10;
//             }
//             break;
//         case 10: // 停车
//             Motor_Stop();
//             for(int i=0;i<3;i++){
//                 DL_GPIO_clearPins(LED_PORT,LED_PIN_22_PIN);
//                 delay_ms(500);
//                 DL_GPIO_setPins(LED_PORT,LED_PIN_22_PIN);
//                 delay_ms(500);
//             }
//             return;
//         }
//         delay_ms(10);
//     }
// }


void task_3(void) {
    u8 x1,x2,x3,x4,x5,x6,x7,x8;
    float yawz_init, yawz_now, err;
    float turn_angle = 39;
    float yawz_left, yawz_right, yaw_1;
    int state = 0; // 状态机
    int loop_count = 0; // 循环计数器

    int quanbai_time;

    Gyro_Struct *angle = get_angle();
    
    // 记录初始角度（只在最开始记录一次）
    yawz_init = angle->z; // 起点yaw
    yaw_1 = yawz_init + 180;
    if(yaw_1 > 180) yaw_1 -= 360;
    if(yaw_1 < -180) yaw_1 += 360;

    while(1) {
        deal_data(&x1,&x2,&x3,&x4,&x5,&x6,&x7,&x8);
        angle = get_angle();
        yawz_now = angle->z;

        switch(state) {
        case 0: // 左转arccos(0.8)度
            // 每次重新计算左转目标角度（基于初始角度）
            yawz_left = yawz_init + turn_angle;
            if(yawz_left > 180) yawz_left -= 360;
            if(yawz_left < -180) yawz_left += 360;
            err = yawz_now - yawz_left;
            if(err > 180) err -= 360;
            if(err < -180) err += 360;
            if(fabs(err) >1) 
            {
                // 根据误差方向决定转向
                if(err > 0) 
                {
                    Car_Control(10,10,10); // 右转
                } 
                else if (err < 0) 
                {
                    Car_Control(10,10,-10); // 左转
                }
            }
            else 
            {
                state = 1;
            }
            break;
            
        case 1: // 第一次空白直行
            err = yawz_now - yawz_left;
            if(err > 180) err -= 360;
            if(err < -180) err += 360;
            Car_Control(30,30,err);
            if(x1==0||x2==0 || x3==0 ||x4==0 ||x5==0 ||x6==0|| x7==0 ||x8==0) {
                state = 2;
            }
            break;
            
        case 2: // 半圆循迹
           // LineWalking();
            if(x1==1 && x2==1 && x3==1 && x4==1 && x5==1 && x6==1 && x7==1 && x8==1) 
            {
                quanbai_time++;
                 
                if(quanbai_time>quanbai_flag){
                    quanbai_time=0;
                    state = 4;
                }              
            }
             else  { 
                 quanbai_time=0;
                LineWalking();
            }
            break;

         
        case 3: // 半圆循迹后，先调整为yaw_1
            err = yawz_now - yaw_1;
            if(err > 180) err -= 360;
            if(err < -180) err += 360;
            if(fabs(err) >1) 
            {
                // 根据误差方向决定转向
                if(err > 0) 
                {
                    Car_Control(10,10,10); // 右转
                } 
                else if (err < 0) 
                {
                    Car_Control(10,10,-10); // 左转
                }
            }
            else 
            {
                state = 4;
            }
            break;
            
        case 4: // 右转arccos(0.8)度
            // 每次重新计算右转目标角度（基于初始角度）
            yawz_right = yawz_left + (2*(90 - turn_angle)); // 计算右转目标
            if(yawz_right > 180) yawz_right -= 360;
            if(yawz_right < -180) yawz_right += 360;
            err = yawz_now - yawz_right;
            if(err > 180) err -= 360;
            if(err < -180) err += 360;
             if(fabs(err) >1) 
            {
                // 根据误差方向决定转向
                if(err > 0) 
                {
                    Car_Control(10,10,10); // 右转
                } 
                else if (err < 0) 
                {
                    Car_Control(10,10,-10); // 左转
                }
            }
            else 
            {
                state = 5;
            }
            break;
            
        case 5: // 第二次空白直行
            err = yawz_now - yawz_right;
            if(err > 180) err -= 360;
            if(err < -180) err += 360;
            Car_Control(30, 30,err);
            if(x1==0||x2==0 || x3==0 ||x4==0 ||x5==0 ||x6==0|| x7==0 ||x8==0) {
                state = 6;
            }
            break;
            
        case 6: // 第二次半圆循迹

         if(x1==1 && x2==1 && x3==1 && x4==1 && x5==1 && x6==1 && x7==1 && x8==1) 
            {
                quanbai_time++;  
                if(quanbai_time>quanbai_flag)
                {
                    quanbai_time=0;
                     loop_count++;
                     if(loop_count >= 4) {
                        state = 8;
                        } // 执行停止代码 
                else 
                {
                    state = 0; 
                }// 准备开始下一次循环
                }
            }
             else
            {  
                quanbai_time=0;
                LineWalking();
            }


            
            // if(x1==1 && x2==1 && x3==1 && x4==1 && x5==1 && x6==1 && x7==1 && x8==1) 
            // {
            //     quanbai_time++;                
            // } 
            // if(quanbai_time>32000)
            // {quanbai_time=0;
            //  loop_count++;
            //   if(loop_count >= 3) {state = 8; } // 执行停止代码 
            //   else {state = 7; }// 准备开始下一次循环
        
            // }
            
            // if(x1==1 && x2==1 && x3==1 && x4==1 && x5==1 && x6==1 && x7==1 && x8==1) {
            //     delay_ms(200);
            //     loop_count++;
                
            //     if(loop_count >= 3) {
            //         state = 8; // 执行停止代码
            //     } else {
            //         state = 7; // 准备开始下一次循环
            //     }
            // } else {
            //     LineWalking();
            // }
            break;
            
        case 7: // 重置到初始角度
            err = yawz_now - yawz_init;
            if(err > 180) err -= 360;
            if(err < -180) err += 360;
            if(fabs(err) >1) 
            {
                // 根据误差方向决定转向
                if(err > 0) 
                {
                    Car_Control(10,10,10); // 右转
                } 
                else if (err < 0) 
                {
                    Car_Control(10,10,-10); // 左转
                }
            }
            else 
            {
                state = 0; // 角度已重置，开始下一次循环
            }
            break;
            
        case 8: // 停车
            Motor_Stop();
            for(int i=0; i<3; i++) {
                DL_GPIO_clearPins(LED_PORT,LED_PIN_22_PIN);
                delay_ms(500);
                DL_GPIO_setPins(LED_PORT,LED_PIN_22_PIN);
                delay_ms(500);
            }
            return;
        }
        delay_ms(10);
    }}
    
    
