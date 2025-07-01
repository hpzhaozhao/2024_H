/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerA_backupConfig gPWM_0Backup;
DL_TimerA_backupConfig gTIMER_TICKBackup;
DL_SPI_backupConfig gTFT_SPIBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_PWM_0_init();
    SYSCFG_DL_TIMER_TICK_init();
    SYSCFG_DL_I2C_eightways_init();
    SYSCFG_DL_TFT_SPI_init();
    SYSCFG_DL_SYSTICK_init();
    SYSCFG_DL_SYSCTL_CLK_init();
    /* Ensure backup structures have no valid state */
	gPWM_0Backup.backupRdy 	= false;
	gTIMER_TICKBackup.backupRdy 	= false;
	gTFT_SPIBackup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(PWM_0_INST, &gPWM_0Backup);
	retStatus &= DL_TimerA_saveConfiguration(TIMER_TICK_INST, &gTIMER_TICKBackup);
	retStatus &= DL_SPI_saveConfiguration(TFT_SPI_INST, &gTFT_SPIBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(PWM_0_INST, &gPWM_0Backup, false);
	retStatus &= DL_TimerA_restoreConfiguration(TIMER_TICK_INST, &gTIMER_TICKBackup, false);
	retStatus &= DL_SPI_restoreConfiguration(TFT_SPI_INST, &gTFT_SPIBackup);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerA_reset(PWM_0_INST);
    DL_TimerA_reset(TIMER_TICK_INST);
    DL_I2C_reset(I2C_eightways_INST);
    DL_SPI_reset(TFT_SPI_INST);


    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerA_enablePower(PWM_0_INST);
    DL_TimerA_enablePower(TIMER_TICK_INST);
    DL_I2C_enablePower(I2C_eightways_INST);
    DL_SPI_enablePower(TFT_SPI_INST);

    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXIN_IOMUX);
    DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXOUT_IOMUX);

    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_0_C0_IOMUX,GPIO_PWM_0_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_0_C0_PORT, GPIO_PWM_0_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_0_C1_IOMUX,GPIO_PWM_0_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_0_C1_PORT, GPIO_PWM_0_C1_PIN);

    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_eightways_IOMUX_SDA,
        GPIO_I2C_eightways_IOMUX_SDA_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_eightways_IOMUX_SCL,
        GPIO_I2C_eightways_IOMUX_SCL_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_enableHiZ(GPIO_I2C_eightways_IOMUX_SDA);
    DL_GPIO_enableHiZ(GPIO_I2C_eightways_IOMUX_SCL);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_TFT_SPI_IOMUX_SCLK, GPIO_TFT_SPI_IOMUX_SCLK_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_TFT_SPI_IOMUX_PICO, GPIO_TFT_SPI_IOMUX_PICO_FUNC);

    DL_GPIO_initDigitalOutputFeatures(LED_PIN_22_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);

    DL_GPIO_initDigitalOutputFeatures(BEE_PIN_23_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);

    DL_GPIO_initDigitalOutput(TB6612_AIN1_IOMUX);

    DL_GPIO_initDigitalOutput(TB6612_AIN2_IOMUX);

    DL_GPIO_initDigitalOutput(TB6612_BIN1_IOMUX);

    DL_GPIO_initDigitalOutput(TB6612_BIN2_IOMUX);

    DL_GPIO_initDigitalInputFeatures(L_ENCODER_LENA_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(L_ENCODER_LENB_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(TFT_RES_IOMUX);

    DL_GPIO_initDigitalOutput(TFT_DC_IOMUX);

    DL_GPIO_initDigitalOutput(TFT_CS_IOMUX);

    DL_GPIO_initDigitalOutput(TFT_BLK_IOMUX);

    DL_GPIO_initDigitalOutput(IIC_Software_SCL_IOMUX);

    DL_GPIO_initDigitalOutput(IIC_Software_SDA_IOMUX);

    DL_GPIO_initDigitalInputFeatures(R_ENCODER_RENA_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(R_ENCODER_RENB_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(KEY_K1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(KEY_K2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(KEY_K3_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(KEY_K4_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_clearPins(GPIOA, IIC_Software_SCL_PIN |
		IIC_Software_SDA_PIN);
    DL_GPIO_setPins(GPIOA, TB6612_AIN1_PIN |
		TB6612_AIN2_PIN |
		TB6612_BIN1_PIN |
		TB6612_BIN2_PIN);
    DL_GPIO_enableOutput(GPIOA, TB6612_AIN1_PIN |
		TB6612_AIN2_PIN |
		TB6612_BIN1_PIN |
		TB6612_BIN2_PIN |
		IIC_Software_SCL_PIN |
		IIC_Software_SDA_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOA, DL_GPIO_PIN_8_EDGE_RISE |
		DL_GPIO_PIN_9_EDGE_RISE);
    DL_GPIO_setUpperPinsPolarity(GPIOA, DL_GPIO_PIN_24_EDGE_RISE |
		DL_GPIO_PIN_26_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOA, R_ENCODER_RENA_PIN |
		R_ENCODER_RENB_PIN);
    DL_GPIO_enableInterrupt(GPIOA, R_ENCODER_RENA_PIN |
		R_ENCODER_RENB_PIN);
    DL_GPIO_clearPins(GPIOB, LED_PIN_22_PIN |
		BEE_PIN_23_PIN |
		TFT_RES_PIN |
		TFT_DC_PIN |
		TFT_CS_PIN |
		TFT_BLK_PIN);
    DL_GPIO_enableOutput(GPIOB, LED_PIN_22_PIN |
		BEE_PIN_23_PIN |
		TFT_RES_PIN |
		TFT_DC_PIN |
		TFT_CS_PIN |
		TFT_BLK_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOB, DL_GPIO_PIN_0_EDGE_RISE |
		DL_GPIO_PIN_1_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOB, L_ENCODER_LENA_PIN |
		L_ENCODER_LENB_PIN);
    DL_GPIO_enableInterrupt(GPIOB, L_ENCODER_LENA_PIN |
		L_ENCODER_LENB_PIN);

}


static const DL_SYSCTL_SYSPLLConfig gSYSPLLConfig = {
    .inputFreq              = DL_SYSCTL_SYSPLL_INPUT_FREQ_32_48_MHZ,
	.rDivClk2x              = 1,
	.rDivClk1               = 0,
	.rDivClk0               = 0,
	.enableCLK2x            = DL_SYSCTL_SYSPLL_CLK2X_ENABLE,
	.enableCLK1             = DL_SYSCTL_SYSPLL_CLK1_DISABLE,
	.enableCLK0             = DL_SYSCTL_SYSPLL_CLK0_DISABLE,
	.sysPLLMCLK             = DL_SYSCTL_SYSPLL_MCLK_CLK2X,
	.sysPLLRef              = DL_SYSCTL_SYSPLL_REF_HFCLK,
	.qDiv                   = 1,
	.pDiv                   = DL_SYSCTL_SYSPLL_PDIV_1
};
SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);
    DL_SYSCTL_setFlashWaitState(DL_SYSCTL_FLASH_WAIT_STATE_2);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_setHFCLKSourceHFXTParams(DL_SYSCTL_HFXT_RANGE_32_48_MHZ,20, true);
    DL_SYSCTL_configSYSPLL((DL_SYSCTL_SYSPLLConfig *) &gSYSPLLConfig);
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_2);
    DL_SYSCTL_setMCLKSource(SYSOSC, HSCLK, DL_SYSCTL_HSCLK_SOURCE_SYSPLL);
    /* INT_GROUP1 Priority */
    NVIC_SetPriority(GPIOA_INT_IRQn, 0);

}
SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_CLK_init(void) {
    while ((DL_SYSCTL_getClockStatus() & (DL_SYSCTL_CLK_STATUS_SYSPLL_GOOD
		 | DL_SYSCTL_CLK_STATUS_HFCLK_GOOD
		 | DL_SYSCTL_CLK_STATUS_HSCLK_GOOD
		 | DL_SYSCTL_CLK_STATUS_LFOSC_GOOD))
	       != (DL_SYSCTL_CLK_STATUS_SYSPLL_GOOD
		 | DL_SYSCTL_CLK_STATUS_HFCLK_GOOD
		 | DL_SYSCTL_CLK_STATUS_HSCLK_GOOD
		 | DL_SYSCTL_CLK_STATUS_LFOSC_GOOD))
	{
		/* Ensure that clocks are in default POR configuration before initialization.
		* Additionally once LFXT is enabled, the internal LFOSC is disabled, and cannot
		* be re-enabled other than by executing a BOOTRST. */
		;
	}
}



/*
 * Timer clock configuration to be sourced by  / 8 (10000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   10000000 Hz = 10000000 Hz / (8 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gPWM_0ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 0U
};

static const DL_TimerA_PWMConfig gPWM_0Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 1000,
    .isTimerWithFourCC = false,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_0_init(void) {

    DL_TimerA_setClockConfig(
        PWM_0_INST, (DL_TimerA_ClockConfig *) &gPWM_0ClockConfig);

    DL_TimerA_initPWMMode(
        PWM_0_INST, (DL_TimerA_PWMConfig *) &gPWM_0Config);

    // Set Counter control to the smallest CC index being used
    DL_TimerA_setCounterControl(PWM_0_INST,DL_TIMER_CZC_CCCTL0_ZCOND,DL_TIMER_CAC_CCCTL0_ACOND,DL_TIMER_CLC_CCCTL0_LCOND);

    DL_TimerA_setCaptureCompareOutCtl(PWM_0_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_ENABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(PWM_0_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_0_INDEX);
    DL_TimerA_setCaptureCompareValue(PWM_0_INST, 1000, DL_TIMER_CC_0_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(PWM_0_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_ENABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_1_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(PWM_0_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_1_INDEX);
    DL_TimerA_setCaptureCompareValue(PWM_0_INST, 1000, DL_TIMER_CC_1_INDEX);

    DL_TimerA_enableClock(PWM_0_INST);


    
    DL_TimerA_setCCPDirection(PWM_0_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (10000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   1000000 Hz = 10000000 Hz / (8 * (9 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_TICKClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 9U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_TICK_INST_LOAD_VALUE = (20ms * 1000000 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_TICKTimerConfig = {
    .period     = TIMER_TICK_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_TICK_init(void) {

    DL_TimerA_setClockConfig(TIMER_TICK_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_TICKClockConfig);

    DL_TimerA_initTimerMode(TIMER_TICK_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_TICKTimerConfig);
    DL_TimerA_enableInterrupt(TIMER_TICK_INST , DL_TIMERA_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(TIMER_TICK_INST_INT_IRQN, 3);
    DL_TimerA_enableClock(TIMER_TICK_INST);





}


static const DL_I2C_ClockConfig gI2C_eightwaysClockConfig = {
    .clockSel = DL_I2C_CLOCK_BUSCLK,
    .divideRatio = DL_I2C_CLOCK_DIVIDE_1,
};

SYSCONFIG_WEAK void SYSCFG_DL_I2C_eightways_init(void) {

    DL_I2C_setClockConfig(I2C_eightways_INST,
        (DL_I2C_ClockConfig *) &gI2C_eightwaysClockConfig);
    DL_I2C_setAnalogGlitchFilterPulseWidth(I2C_eightways_INST,
        DL_I2C_ANALOG_GLITCH_FILTER_WIDTH_50NS);
    DL_I2C_enableAnalogGlitchFilter(I2C_eightways_INST);

    /* Configure Controller Mode */
    DL_I2C_resetControllerTransfer(I2C_eightways_INST);
    /* Set frequency to 400000 Hz*/
    DL_I2C_setTimerPeriod(I2C_eightways_INST, 9);
    DL_I2C_setControllerTXFIFOThreshold(I2C_eightways_INST, DL_I2C_TX_FIFO_LEVEL_EMPTY);
    DL_I2C_setControllerRXFIFOThreshold(I2C_eightways_INST, DL_I2C_RX_FIFO_LEVEL_BYTES_1);
    DL_I2C_enableControllerClockStretching(I2C_eightways_INST);


    /* Enable module */
    DL_I2C_enableController(I2C_eightways_INST);


}

static const DL_SPI_Config gTFT_SPI_config = {
    .mode        = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO3_POL0_PHA0,
    .parity      = DL_SPI_PARITY_NONE,
    .dataSize    = DL_SPI_DATA_SIZE_8,
    .bitOrder    = DL_SPI_BIT_ORDER_MSB_FIRST,
};

static const DL_SPI_ClockConfig gTFT_SPI_clockConfig = {
    .clockSel    = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1
};

SYSCONFIG_WEAK void SYSCFG_DL_TFT_SPI_init(void) {
    DL_SPI_setClockConfig(TFT_SPI_INST, (DL_SPI_ClockConfig *) &gTFT_SPI_clockConfig);

    DL_SPI_init(TFT_SPI_INST, (DL_SPI_Config *) &gTFT_SPI_config);

    /* Configure Controller mode */
    /*
     * Set the bit rate clock divider to generate the serial output clock
     *     outputBitRate = (spiInputClock) / ((1 + SCR) * 2)
     *     8000000 = (80000000)/((1 + 4) * 2)
     */
    DL_SPI_setBitRateSerialClockDivider(TFT_SPI_INST, 4);
    /* Set RX and TX FIFO threshold levels */
    DL_SPI_setFIFOThreshold(TFT_SPI_INST, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Enable module */
    DL_SPI_enable(TFT_SPI_INST);
}

SYSCONFIG_WEAK void SYSCFG_DL_SYSTICK_init(void)
{
    /* Initialize the period to 1.00 μs */
    DL_SYSTICK_init(80);
    /* Enable the SysTick and start counting */
    DL_SYSTICK_enable();
}

