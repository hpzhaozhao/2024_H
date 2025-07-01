/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMA1
#define PWM_0_INST_IRQHandler                                   TIMA1_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMA1_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                             10000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOA
#define GPIO_PWM_0_C0_PIN                                         DL_GPIO_PIN_17
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM39)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM39_PF_TIMA1_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOA
#define GPIO_PWM_0_C1_PIN                                         DL_GPIO_PIN_16
#define GPIO_PWM_0_C1_IOMUX                                      (IOMUX_PINCM38)
#define GPIO_PWM_0_C1_IOMUX_FUNC                     IOMUX_PINCM38_PF_TIMA1_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_TICK */
#define TIMER_TICK_INST                                                  (TIMA0)
#define TIMER_TICK_INST_IRQHandler                              TIMA0_IRQHandler
#define TIMER_TICK_INST_INT_IRQN                                (TIMA0_INT_IRQn)
#define TIMER_TICK_INST_LOAD_VALUE                                      (19999U)




/* Defines for I2C_eightways */
#define I2C_eightways_INST                                                  I2C1
#define I2C_eightways_INST_IRQHandler                            I2C1_IRQHandler
#define I2C_eightways_INST_INT_IRQN                                I2C1_INT_IRQn
#define I2C_eightways_BUS_SPEED_HZ                                        400000
#define GPIO_I2C_eightways_SDA_PORT                                        GPIOB
#define GPIO_I2C_eightways_SDA_PIN                                 DL_GPIO_PIN_3
#define GPIO_I2C_eightways_IOMUX_SDA                             (IOMUX_PINCM16)
#define GPIO_I2C_eightways_IOMUX_SDA_FUNC               IOMUX_PINCM16_PF_I2C1_SDA
#define GPIO_I2C_eightways_SCL_PORT                                        GPIOB
#define GPIO_I2C_eightways_SCL_PIN                                 DL_GPIO_PIN_2
#define GPIO_I2C_eightways_IOMUX_SCL                             (IOMUX_PINCM15)
#define GPIO_I2C_eightways_IOMUX_SCL_FUNC               IOMUX_PINCM15_PF_I2C1_SCL


/* Defines for TFT_SPI */
#define TFT_SPI_INST                                                       SPI1
#define TFT_SPI_INST_IRQHandler                                 SPI1_IRQHandler
#define TFT_SPI_INST_INT_IRQN                                     SPI1_INT_IRQn
#define GPIO_TFT_SPI_PICO_PORT                                            GPIOB
#define GPIO_TFT_SPI_PICO_PIN                                     DL_GPIO_PIN_8
#define GPIO_TFT_SPI_IOMUX_PICO                                 (IOMUX_PINCM25)
#define GPIO_TFT_SPI_IOMUX_PICO_FUNC                 IOMUX_PINCM25_PF_SPI1_PICO
/* GPIO configuration for TFT_SPI */
#define GPIO_TFT_SPI_SCLK_PORT                                            GPIOB
#define GPIO_TFT_SPI_SCLK_PIN                                     DL_GPIO_PIN_9
#define GPIO_TFT_SPI_IOMUX_SCLK                                 (IOMUX_PINCM26)
#define GPIO_TFT_SPI_IOMUX_SCLK_FUNC                 IOMUX_PINCM26_PF_SPI1_SCLK



/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOB)

/* Defines for PIN_22: GPIOB.22 with pinCMx 50 on package pin 21 */
#define LED_PIN_22_PIN                                          (DL_GPIO_PIN_22)
#define LED_PIN_22_IOMUX                                         (IOMUX_PINCM50)
/* Port definition for Pin Group BEE */
#define BEE_PORT                                                         (GPIOB)

/* Defines for PIN_23: GPIOB.23 with pinCMx 51 on package pin 22 */
#define BEE_PIN_23_PIN                                          (DL_GPIO_PIN_23)
#define BEE_PIN_23_IOMUX                                         (IOMUX_PINCM51)
/* Port definition for Pin Group TB6612 */
#define TB6612_PORT                                                      (GPIOA)

/* Defines for AIN1: GPIOA.14 with pinCMx 36 on package pin 7 */
#define TB6612_AIN1_PIN                                         (DL_GPIO_PIN_14)
#define TB6612_AIN1_IOMUX                                        (IOMUX_PINCM36)
/* Defines for AIN2: GPIOA.15 with pinCMx 37 on package pin 8 */
#define TB6612_AIN2_PIN                                         (DL_GPIO_PIN_15)
#define TB6612_AIN2_IOMUX                                        (IOMUX_PINCM37)
/* Defines for BIN1: GPIOA.12 with pinCMx 34 on package pin 5 */
#define TB6612_BIN1_PIN                                         (DL_GPIO_PIN_12)
#define TB6612_BIN1_IOMUX                                        (IOMUX_PINCM34)
/* Defines for BIN2: GPIOA.13 with pinCMx 35 on package pin 6 */
#define TB6612_BIN2_PIN                                         (DL_GPIO_PIN_13)
#define TB6612_BIN2_IOMUX                                        (IOMUX_PINCM35)
/* Port definition for Pin Group L_ENCODER */
#define L_ENCODER_PORT                                                   (GPIOB)

/* Defines for LENA: GPIOB.0 with pinCMx 12 on package pin 47 */
// pins affected by this interrupt request:["LENA","LENB"]
#define L_ENCODER_INT_IRQN                                      (GPIOB_INT_IRQn)
#define L_ENCODER_INT_IIDX                      (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define L_ENCODER_LENA_IIDX                                  (DL_GPIO_IIDX_DIO0)
#define L_ENCODER_LENA_PIN                                       (DL_GPIO_PIN_0)
#define L_ENCODER_LENA_IOMUX                                     (IOMUX_PINCM12)
/* Defines for LENB: GPIOB.1 with pinCMx 13 on package pin 48 */
#define L_ENCODER_LENB_IIDX                                  (DL_GPIO_IIDX_DIO1)
#define L_ENCODER_LENB_PIN                                       (DL_GPIO_PIN_1)
#define L_ENCODER_LENB_IOMUX                                     (IOMUX_PINCM13)
/* Port definition for Pin Group TFT */
#define TFT_PORT                                                         (GPIOB)

/* Defines for RES: GPIOB.10 with pinCMx 27 on package pin 62 */
#define TFT_RES_PIN                                             (DL_GPIO_PIN_10)
#define TFT_RES_IOMUX                                            (IOMUX_PINCM27)
/* Defines for DC: GPIOB.11 with pinCMx 28 on package pin 63 */
#define TFT_DC_PIN                                              (DL_GPIO_PIN_11)
#define TFT_DC_IOMUX                                             (IOMUX_PINCM28)
/* Defines for CS: GPIOB.14 with pinCMx 31 on package pin 2 */
#define TFT_CS_PIN                                              (DL_GPIO_PIN_14)
#define TFT_CS_IOMUX                                             (IOMUX_PINCM31)
/* Defines for BLK: GPIOB.26 with pinCMx 57 on package pin 28 */
#define TFT_BLK_PIN                                             (DL_GPIO_PIN_26)
#define TFT_BLK_IOMUX                                            (IOMUX_PINCM57)
/* Port definition for Pin Group IIC_Software */
#define IIC_Software_PORT                                                (GPIOA)

/* Defines for SCL: GPIOA.1 with pinCMx 2 on package pin 34 */
#define IIC_Software_SCL_PIN                                     (DL_GPIO_PIN_1)
#define IIC_Software_SCL_IOMUX                                    (IOMUX_PINCM2)
/* Defines for SDA: GPIOA.0 with pinCMx 1 on package pin 33 */
#define IIC_Software_SDA_PIN                                     (DL_GPIO_PIN_0)
#define IIC_Software_SDA_IOMUX                                    (IOMUX_PINCM1)
/* Port definition for Pin Group R_ENCODER */
#define R_ENCODER_PORT                                                   (GPIOA)

/* Defines for RENA: GPIOA.8 with pinCMx 19 on package pin 54 */
// pins affected by this interrupt request:["RENA","RENB"]
#define R_ENCODER_INT_IRQN                                      (GPIOA_INT_IRQn)
#define R_ENCODER_INT_IIDX                      (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define R_ENCODER_RENA_IIDX                                  (DL_GPIO_IIDX_DIO8)
#define R_ENCODER_RENA_PIN                                       (DL_GPIO_PIN_8)
#define R_ENCODER_RENA_IOMUX                                     (IOMUX_PINCM19)
/* Defines for RENB: GPIOA.9 with pinCMx 20 on package pin 55 */
#define R_ENCODER_RENB_IIDX                                  (DL_GPIO_IIDX_DIO9)
#define R_ENCODER_RENB_PIN                                       (DL_GPIO_PIN_9)
#define R_ENCODER_RENB_IOMUX                                     (IOMUX_PINCM20)
/* Port definition for Pin Group KEY */
#define KEY_PORT                                                         (GPIOA)

/* Defines for K1: GPIOA.24 with pinCMx 54 on package pin 25 */
#define KEY_K1_PIN                                              (DL_GPIO_PIN_24)
#define KEY_K1_IOMUX                                             (IOMUX_PINCM54)
/* Defines for K2: GPIOA.25 with pinCMx 55 on package pin 26 */
#define KEY_K2_PIN                                              (DL_GPIO_PIN_25)
#define KEY_K2_IOMUX                                             (IOMUX_PINCM55)
/* Defines for K3: GPIOA.26 with pinCMx 59 on package pin 30 */
#define KEY_K3_PIN                                              (DL_GPIO_PIN_26)
#define KEY_K3_IOMUX                                             (IOMUX_PINCM59)
/* Defines for K4: GPIOA.27 with pinCMx 60 on package pin 31 */
#define KEY_K4_PIN                                              (DL_GPIO_PIN_27)
#define KEY_K4_IOMUX                                             (IOMUX_PINCM60)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_SYSCTL_CLK_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_TIMER_TICK_init(void);
void SYSCFG_DL_I2C_eightways_init(void);
void SYSCFG_DL_TFT_SPI_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
