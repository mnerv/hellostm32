#include "stm32u5xx_hal.h"
#include "stm32u5xx_nucleo.h"
#include <stdio.h>

COM_InitTypeDef BspCOMInit;

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

    uint8_t i = 0;

    while (true) {
        printf("Hello, World! %d\r\n", i++);
        HAL_Delay(125);
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

