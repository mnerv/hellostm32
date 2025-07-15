#include "stm32u5xx_hal.h"
#include "stm32u5xx_hal_gpio.h"
#include "stm32u5xx_hal_rcc.h"
#include "stm32u5xx_nucleo.h"

#include <stdio.h>

COM_InitTypeDef BspCOMInit;
TIM_HandleTypeDef htim2;

void Error_Handler(void);
void SystemClock_Config(void);
static void SystemPower_Config(void);
static void MX_ICACHE_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    SystemPower_Config();
    MX_ICACHE_Init();

    /* Initialize led */
    BSP_LED_Init(LED_GREEN);

    /* Initialize USER push-button, will be used to trigger an interrupt each time it's pressed.*/
    BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

    /* Initialize COM1 port (115200, 8 bits (7-bit data + 1 stop bit), no parity */
    BspCOMInit.BaudRate   = 115200;
    BspCOMInit.WordLength = COM_WORDLENGTH_8B;
    BspCOMInit.StopBits   = COM_STOPBITS_1;
    BspCOMInit.Parity     = COM_PARITY_NONE;
    BspCOMInit.HwFlowCtl  = COM_HWCONTROL_NONE;
    if (BSP_COM_Init(COM1, &BspCOMInit) != BSP_ERROR_NONE) {
        Error_Handler();
    }

    // Init GPIO
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_TIM2_CLK_ENABLE();

    // Init Hardware Timer 2 for PWM
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 32;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
        printf("Error initialising Hardware Timer Base: %s:%d\r\n", __FILE__, __LINE__);
        Error_Handler();
    }

    TIM_ClockConfigTypeDef clock_src_conf;
    clock_src_conf.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &clock_src_conf) != HAL_OK) {
        printf("Error configure clock source: %s:%d\r\n", __FILE__, __LINE__);
        Error_Handler();
    }

    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK) {
        printf("Error initialising PWM: %s:%d\r\n", __FILE__, __LINE__);
        Error_Handler();
    }

    TIM_MasterConfigTypeDef master_conf;
    master_conf.MasterOutputTrigger = TIM_TRGO_RESET;
    master_conf.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &master_conf) != HAL_OK) {
        printf("Error configuring master synchronization: %s:%d\r\n", __FILE__, __LINE__);
        Error_Handler();
    }

    TIM_OC_InitTypeDef conf_oc;
    conf_oc.OCMode = TIM_OCMODE_PWM1;
    conf_oc.Pulse = 0;
    conf_oc.OCPolarity = TIM_OCPOLARITY_HIGH;
    conf_oc.OCFastMode = TIM_OCFAST_DISABLE;

    if (HAL_TIM_PWM_ConfigChannel(&htim2, &conf_oc, TIM_CHANNEL_1) != HAL_OK) {
        printf("Error configuring PWM Channel 1: %s:%d\r\n", __FILE__, __LINE__);
        Error_Handler();
    }

    if (HAL_TIM_PWM_ConfigChannel(&htim2, &conf_oc, TIM_CHANNEL_2) != HAL_OK) {
        printf("Error configuring PWM Channel 2: %s:%d\r\n", __FILE__, __LINE__);
        Error_Handler();
    }

    GPIO_InitTypeDef gpio_init = {0};
    gpio_init.Pin       = GPIO_PIN_3;               // TIM2_CH2
    gpio_init.Mode      = GPIO_MODE_AF_PP;
    gpio_init.Pull      = GPIO_NOPULL;
    gpio_init.Speed     = GPIO_SPEED_FREQ_HIGH;
    gpio_init.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOB, &gpio_init);

    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);

    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 16);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 16);

    uint8_t i = 0;
    // uint8_t duty = 0;

    while (true) {
        printf("Hello, World! ah shit %d\r\n", i++);
        // __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, duty);
        // duty = (duty + 1) % 12;
        HAL_Delay(66);
    }
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE4) != HAL_OK) {
        Error_Handler();
    }

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.MSIState       = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_4;
    RCC_OscInitStruct.PLL.PLLState  = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK
                                | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1
                                | RCC_CLOCKTYPE_PCLK2
                                | RCC_CLOCKTYPE_PCLK3;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_MSI;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
        Error_Handler();
    }
}

static void SystemPower_Config(void) {
    if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_ICACHE_Init(void) {
    if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_ICACHE_Enable() != HAL_OK) {
        Error_Handler();
    }
}

void Error_Handler(void) {
    __disable_irq();
    while (true) { }
}

void HAL_MspInit(void) {
    __HAL_RCC_PWR_CLK_ENABLE();
}

void NMI_Handler(void) {
    while (1) { }
}

void HardFault_Handler(void) {
    while (1) { }
}

void MemManage_Handler(void) {
    while (true) { }
}

void BusFault_Handler(void) {
    while (true) { }
}

void UsageFault_Handler(void) {
    while (true) { }
}

void SVC_Handler(void) { }

void DebugMon_Handler(void) { }

void PendSV_Handler(void) { }

void SysTick_Handler(void) {
    HAL_IncTick();
}

void EXTI13_IRQHandler(void) {
    BSP_PB_IRQHandler(BUTTON_USER);
}

