/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32u5xx_hal.h"

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
#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define TOF_R_INT_Pin GPIO_PIN_9
#define TOF_R_INT_GPIO_Port GPIOF
#define DC_Pin GPIO_PIN_13
#define DC_GPIO_Port GPIOF
#define R_RED_Pin GPIO_PIN_0
#define R_RED_GPIO_Port GPIOG
#define TOF_R_XSHUT_Pin GPIO_PIN_1
#define TOF_R_XSHUT_GPIO_Port GPIOG
#define RESET_Pin GPIO_PIN_9
#define RESET_GPIO_Port GPIOE
#define CS_Pin GPIO_PIN_11
#define CS_GPIO_Port GPIOE
#define TOF_L_INT_Pin GPIO_PIN_10
#define TOF_L_INT_GPIO_Port GPIOB
#define TOF_L_XSHUT_Pin GPIO_PIN_11
#define TOF_L_XSHUT_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_2
#define LED_RED_GPIO_Port GPIOG
#define LED_GREEN_Pin GPIO_PIN_7
#define LED_GREEN_GPIO_Port GPIOC
#define L_YELLOW_Pin GPIO_PIN_8
#define L_YELLOW_GPIO_Port GPIOA
#define R_YELLOW_Pin GPIO_PIN_1
#define R_YELLOW_GPIO_Port GPIOD
#define LED_BLUE_Pin GPIO_PIN_7
#define LED_BLUE_GPIO_Port GPIOB
#define L_RED_Pin GPIO_PIN_0
#define L_RED_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
