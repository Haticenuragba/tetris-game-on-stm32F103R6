/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define _7B_Pin GPIO_PIN_0
#define _7B_GPIO_Port GPIOC
#define _7C_Pin GPIO_PIN_1
#define _7C_GPIO_Port GPIOC
#define _7D_Pin GPIO_PIN_2
#define _7D_GPIO_Port GPIOC
#define _7E_Pin GPIO_PIN_3
#define _7E_GPIO_Port GPIOC
#define _1A_Pin GPIO_PIN_1
#define _1A_GPIO_Port GPIOA
#define _1B_Pin GPIO_PIN_2
#define _1B_GPIO_Port GPIOA
#define _1C_Pin GPIO_PIN_3
#define _1C_GPIO_Port GPIOA
#define _1D_Pin GPIO_PIN_4
#define _1D_GPIO_Port GPIOA
#define _1E_Pin GPIO_PIN_5
#define _1E_GPIO_Port GPIOA
#define _2A_Pin GPIO_PIN_6
#define _2A_GPIO_Port GPIOA
#define _2B_Pin GPIO_PIN_7
#define _2B_GPIO_Port GPIOA
#define _8A_Pin GPIO_PIN_4
#define _8A_GPIO_Port GPIOC
#define _8B_Pin GPIO_PIN_5
#define _8B_GPIO_Port GPIOC
#define _4A_Pin GPIO_PIN_0
#define _4A_GPIO_Port GPIOB
#define _4B_Pin GPIO_PIN_1
#define _4B_GPIO_Port GPIOB
#define _4C_Pin GPIO_PIN_2
#define _4C_GPIO_Port GPIOB
#define _6A_Pin GPIO_PIN_10
#define _6A_GPIO_Port GPIOB
#define _6B_Pin GPIO_PIN_11
#define _6B_GPIO_Port GPIOB
#define _6C_Pin GPIO_PIN_12
#define _6C_GPIO_Port GPIOB
#define _6D_Pin GPIO_PIN_13
#define _6D_GPIO_Port GPIOB
#define _6E_Pin GPIO_PIN_14
#define _6E_GPIO_Port GPIOB
#define _7A_Pin GPIO_PIN_15
#define _7A_GPIO_Port GPIOB
#define _8C_Pin GPIO_PIN_6
#define _8C_GPIO_Port GPIOC
#define _8D_Pin GPIO_PIN_7
#define _8D_GPIO_Port GPIOC
#define _8E_Pin GPIO_PIN_8
#define _8E_GPIO_Port GPIOC
#define START_Pin GPIO_PIN_9
#define START_GPIO_Port GPIOC
#define START_EXTI_IRQn EXTI9_5_IRQn
#define _2C_Pin GPIO_PIN_8
#define _2C_GPIO_Port GPIOA
#define _2D_Pin GPIO_PIN_9
#define _2D_GPIO_Port GPIOA
#define _2E_Pin GPIO_PIN_10
#define _2E_GPIO_Port GPIOA
#define _3A_Pin GPIO_PIN_11
#define _3A_GPIO_Port GPIOA
#define _3B_Pin GPIO_PIN_12
#define _3B_GPIO_Port GPIOA
#define _3C_Pin GPIO_PIN_13
#define _3C_GPIO_Port GPIOA
#define _3D_Pin GPIO_PIN_14
#define _3D_GPIO_Port GPIOA
#define _3E_Pin GPIO_PIN_15
#define _3E_GPIO_Port GPIOA
#define LEFT_Pin GPIO_PIN_10
#define LEFT_GPIO_Port GPIOC
#define LEFT_EXTI_IRQn EXTI15_10_IRQn
#define R_GHT_Pin GPIO_PIN_11
#define R_GHT_GPIO_Port GPIOC
#define R_GHT_EXTI_IRQn EXTI15_10_IRQn
#define ROTATE_Pin GPIO_PIN_12
#define ROTATE_GPIO_Port GPIOC
#define ROTATE_EXTI_IRQn EXTI15_10_IRQn
#define _4D_Pin GPIO_PIN_3
#define _4D_GPIO_Port GPIOB
#define _4E_Pin GPIO_PIN_4
#define _4E_GPIO_Port GPIOB
#define _5A_Pin GPIO_PIN_5
#define _5A_GPIO_Port GPIOB
#define _5B_Pin GPIO_PIN_6
#define _5B_GPIO_Port GPIOB
#define _5C_Pin GPIO_PIN_7
#define _5C_GPIO_Port GPIOB
#define _5D_Pin GPIO_PIN_8
#define _5D_GPIO_Port GPIOB
#define _5E_Pin GPIO_PIN_9
#define _5E_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
