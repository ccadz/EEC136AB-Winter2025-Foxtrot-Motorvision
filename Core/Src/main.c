/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <string.h>
#include "stdio.h"
#include "fonts.h"
#include "ssd1351.h"
#include "testimg.h"
#include "VL53Lx_api.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define is_interrupt 0
#define LIS3DH_I2C_ADDR 0x32
#define CTRL_REG1 0x20
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

int status;
VL53LX_Dev_t                   devleft;
VL53LX_DEV                     DevLeft = &devleft;
volatile int IntCountLeft;

VL53LX_Dev_t                   devright;
VL53LX_DEV                     DevRight = &devright;
volatile int IntCountRight;

uint8_t accel_data_buffer[6];
char uart_buffer[64];
uint8_t rxData;

static float accel_values[3]; // Array to store X, Y, Z values

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void SystemPower_Config(void);
static void MX_GPIO_Init(void);
static void MX_ICACHE_Init(void);
static void MX_I2C2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance==USART2)
  {
    if(rxData==79) // Ascii value of 'O' is 79
    {
    	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1);
    	snprintf(uart_buffer, sizeof(uart_buffer), "led on");
    	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buffer, strlen(uart_buffer), HAL_MAX_DELAY);
    }
    else if (rxData==88) // Ascii value of 'X' is 88
    {
    	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
    	snprintf(uart_buffer, sizeof(uart_buffer), "led off");
    	HAL_UART_Transmit(&huart2, (uint8_t *)uart_buffer, strlen(uart_buffer), HAL_MAX_DELAY);
    }
    HAL_UART_Receive_IT(&huart2,&rxData,1);
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//LEFT
	if (GPIO_Pin==GPIO_PIN_10)
	{
		IntCountLeft++;
	}
	//RIGHT
	if (GPIO_Pin==GPIO_PIN_9)
	{
		IntCountRight++;
	}
}

float* ReadAccelerometer(void) {

	//Read 6 bytes of data (X_L, X_H, Y_L, Y_H, Z_L, Z_H)
	if (HAL_I2C_Mem_Read(&hi2c2, LIS3DH_I2C_ADDR, OUT_X_L | 0x80, I2C_MEMADD_SIZE_8BIT, accel_data_buffer, 6, HAL_MAX_DELAY) == HAL_OK) {
		int16_t x = (int16_t)((accel_data_buffer[1] << 8) | accel_data_buffer[0]);
		int16_t y = (int16_t)((accel_data_buffer[3] << 8) | accel_data_buffer[2]);
		int16_t z = (int16_t)((accel_data_buffer[5] << 8) | accel_data_buffer[4]);

		//Convert raw values
		accel_values[0] = x * 2.0 * 9.81 / 32768.0;
		accel_values[1] = y * 2.0 * 9.81 / 32768.0;
		accel_values[2] = z * 2.0 * 9.81 / 32768.0;

		//Format and send the data to UART
		snprintf(uart_buffer, sizeof(uart_buffer), "X: %.2f m/s^2, Y: %.2f m/s^2, Z: %.2f m/s^2\r\n", accel_values[0], accel_values[1], accel_values[2]); // @suppress("Float formatting support")
		HAL_UART_Transmit(&huart2, (uint8_t *)uart_buffer, strlen(uart_buffer), HAL_MAX_DELAY);

	} else {
		accel_values[0] = accel_values[1] = accel_values[2] = 0.0; // Error3
		strcpy(uart_buffer, "I2C Read Error\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t *)uart_buffer, strlen(uart_buffer), HAL_MAX_DELAY);
	}
	return accel_values;
}

void DisplayOLED(void) {
    static bool screenIsRed = false;
    float* accel_values = ReadAccelerometer();

    if (accel_values[2] < -1.0) {
        if (!screenIsRed) {
            SSD1351_FillScreen(0xF800);  // fill red
            screenIsRed = true;
        }
    }
    else {
        if (screenIsRed) {
            SSD1351_FillScreen(0x0000);  // fill black
            screenIsRed = false;
        }
    }
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

	uint8_t byteData;
	uint16_t wordData;
	VL53LX_MultiRangingData_t MultiRangingData;
	VL53LX_MultiRangingData_t *pMultiRangingData = &MultiRangingData;
	uint8_t NewDataReady=0;
	int no_of_object_found=0;
	int j;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the System Power */
  SystemPower_Config();

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ICACHE_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  HAL_UART_Receive_IT(&huart2,&rxData,1);

  snprintf(uart_buffer, sizeof(uart_buffer), "BLUETOOTH LOG:\n");
  HAL_UART_Transmit(&huart2, (uint8_t *)uart_buffer, strlen(uart_buffer), HAL_MAX_DELAY);

  	// OLED Init
	SSD1351_Unselect();
	SSD1351_Init();

	// Set LEDs to High
	HAL_GPIO_WritePin(L_RED_GPIO_Port, L_RED_Pin, 1);
	HAL_GPIO_WritePin(L_YELLOW_GPIO_Port, L_YELLOW_Pin, 1);
	HAL_GPIO_WritePin(R_RED_GPIO_Port, R_RED_Pin, 1);
	HAL_GPIO_WritePin(R_YELLOW_GPIO_Port, R_YELLOW_Pin, 1);

	// Display Logo
	SSD1351_DrawImage(0, 0, 128, 128, (const uint16_t*)test_img_128x128);
	HAL_Delay(2500);
	SSD1351_FillScreen(0x0000);

	// Try to configure accelerometer
	uint8_t config[2] = {CTRL_REG1, 0x97};
	if (HAL_I2C_Master_Transmit(&hi2c2, LIS3DH_I2C_ADDR, config, 2, HAL_MAX_DELAY) != HAL_OK) {
		strcpy(uart_buffer, "Failed to configure accelerometer\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t *)uart_buffer, strlen(uart_buffer), HAL_MAX_DELAY);
	}

	printf("VL53L4CX Initialization\n");
	DevLeft->I2cHandle = &hi2c2;
	DevRight->I2cHandle = &hi2c2;

	// ALL LOW
	HAL_GPIO_WritePin(TOF_L_XSHUT_GPIO_Port, TOF_L_XSHUT_Pin, GPIO_PIN_RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(TOF_R_XSHUT_GPIO_Port, TOF_R_XSHUT_Pin, GPIO_PIN_RESET);
	HAL_Delay(5);
	// LEFT ToF HIGH
	HAL_GPIO_WritePin(TOF_L_XSHUT_GPIO_Port, TOF_L_XSHUT_Pin, GPIO_PIN_SET);
	HAL_Delay(5);

	DevLeft->I2cHandle = &hi2c2;
	DevLeft->I2cDevAddr = 0x52;
	status = VL53LX_SetDeviceAddress(DevLeft, 0X52);

	//ALL LOW
	HAL_GPIO_WritePin(TOF_L_XSHUT_GPIO_Port, TOF_L_XSHUT_Pin, GPIO_PIN_RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(TOF_R_XSHUT_GPIO_Port, TOF_R_XSHUT_Pin, GPIO_PIN_RESET);
	HAL_Delay(5);

	// RIGHT ToF HIGH
	HAL_GPIO_WritePin(TOF_R_XSHUT_GPIO_Port, TOF_R_XSHUT_Pin, GPIO_PIN_SET);
	HAL_Delay(5);

	DevRight->I2cHandle = &hi2c2;
	DevRight->I2cDevAddr = 0x53;
	status = VL53LX_SetDeviceAddress(DevRight, 0X53);

	HAL_GPIO_WritePin(TOF_L_XSHUT_GPIO_Port, TOF_L_XSHUT_Pin, GPIO_PIN_SET);
	HAL_Delay(5);

	// device ID must be 0XEBAA, those lines can be used to check if the I2C basic functions have been implemented correctly
	VL53LX_RdByte(DevLeft, 0x010F, &byteData);
	printf("VL53L4CX Model_ID: %02X\n\r", byteData);
	VL53LX_RdByte(DevLeft, 0x0110, &byteData);
	printf("VL53L4CX Module_Type: %02X\n\r", byteData);
	VL53LX_RdWord(DevLeft, 0x010F, &wordData);
	printf("VL53L4CX: %02X\n\r", wordData);
	printf("VL53L4CX Address: %02X\n\r", DevLeft->I2cDevAddr);

	// device ID must be 0XEBAA, those lines can be used to check if the I2C basic functions have been implemented correctly
	VL53LX_RdByte(DevRight, 0x010F, &byteData);
	printf("VL53L4CX Model_ID: %02X\n\r", byteData);
	VL53LX_RdByte(DevRight, 0x0110, &byteData);
	printf("VL53L4CX Module_Type: %02X\n\r", byteData);
	VL53LX_RdWord(DevRight, 0x010F, &wordData);
	printf("VL53L4CX: %02X\n\r", wordData);
	printf("VL53L4CX Address: %02X\n\r", DevRight->I2cDevAddr);

	printf("Ranging loop starts\n");
	status = VL53LX_WaitDeviceBooted(DevLeft);
	if(status){
		printf("VL53LX_WaitDeviceBooted DevLeft failed: error = %d \n", status);
		while(1);
	}
	status = VL53LX_WaitDeviceBooted(DevRight);
	if(status){
		printf("VL53LX_WaitDeviceBooted DevRight failed: error = %d \n", status);
		while(1);
	}
	status = VL53LX_DataInit(DevLeft);
	if(status){
		printf("VL53LX_DataInit DevLeft failed: error = %d \n", status);
		while(1);
	}
	status = VL53LX_DataInit(DevRight);
	if(status){
		printf("VL53LX_DataInit DevRight failed: error = %d \n", status);
		while(1);
	}
	status = VL53LX_StartMeasurement(DevLeft);
	if(status){
		printf("VL53LX_StartMeasurement DevLeft failed: error = %d \n", status);
		while(1);
	}
	status = VL53LX_StartMeasurement(DevRight);
	if(status){
		printf("VL53LX_StartMeasurement DevRight failed: error = %d \n", status);
		while(1);
	}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  DisplayOLED();
	  if(!is_interrupt){ // polling mode
			status = VL53LX_GetMeasurementDataReady(DevLeft, &NewDataReady);
			HAL_Delay(5);
			if((!status)&&(NewDataReady!=0)){
				status = VL53LX_GetMultiRangingData(DevLeft, pMultiRangingData);
				no_of_object_found=pMultiRangingData->NumberOfObjectsFound;
				for(j=0;j<=no_of_object_found;j++){
					if (pMultiRangingData->RangeData[j].RangeMilliMeter > 30 && pMultiRangingData->RangeData[j].RangeMilliMeter < 5900) {
						printf("LEFT %d = %5dmm\n", j + 1, pMultiRangingData->RangeData[j].RangeMilliMeter);// @suppress("Float formatting support")
						if (pMultiRangingData->RangeData[j].RangeMilliMeter < 2000) {
							HAL_GPIO_WritePin(L_RED_GPIO_Port, L_RED_Pin, 0);
							HAL_GPIO_WritePin(L_YELLOW_GPIO_Port, L_YELLOW_Pin, 1);
						} else if (pMultiRangingData->RangeData[j].RangeMilliMeter >= 2000 && pMultiRangingData->RangeData[j].RangeMilliMeter < 4000) {
							HAL_GPIO_WritePin(L_RED_GPIO_Port, L_RED_Pin, 1);
							HAL_GPIO_WritePin(L_YELLOW_GPIO_Port, L_YELLOW_Pin, 0);
						} else {
							HAL_GPIO_WritePin(L_RED_GPIO_Port, L_RED_Pin, 1);
							HAL_GPIO_WritePin(L_YELLOW_GPIO_Port, L_YELLOW_Pin, 1);
						}
//						snprintf(uart_buffer, sizeof(uart_buffer), "LEFT %d = %5dmm\n", j + 1, pMultiRangingData->RangeData[j].RangeMilliMeter);
//						HAL_UART_Transmit(&huart2, (uint8_t *)uart_buffer, strlen(uart_buffer), HAL_MAX_DELAY);
					}
				}
				if (status==0){
					status = VL53LX_ClearInterruptAndStartMeasurement(DevLeft);
				}
			}
			status = VL53LX_GetMeasurementDataReady(DevRight, &NewDataReady);
			HAL_Delay(5);
			if((!status)&&(NewDataReady!=0)){
				status = VL53LX_GetMultiRangingData(DevRight, pMultiRangingData);
				no_of_object_found=pMultiRangingData->NumberOfObjectsFound;
				for(j=0;j<=no_of_object_found;j++){
					if (pMultiRangingData->RangeData[j].RangeMilliMeter > 30 && pMultiRangingData->RangeData[j].RangeMilliMeter < 5900) {
						printf("RIGHT %d = %5dmm\n", j + 1, pMultiRangingData->RangeData[j].RangeMilliMeter);// @suppress("Float formatting support")
						if (pMultiRangingData->RangeData[j].RangeMilliMeter < 2000) {
							HAL_GPIO_WritePin(R_RED_GPIO_Port, R_RED_Pin, 0);
							HAL_GPIO_WritePin(R_YELLOW_GPIO_Port, R_YELLOW_Pin, 1);
						} else if (pMultiRangingData->RangeData[j].RangeMilliMeter >= 2000 && pMultiRangingData->RangeData[j].RangeMilliMeter < 4000) {
							HAL_GPIO_WritePin(R_RED_GPIO_Port, R_RED_Pin, 1);
							HAL_GPIO_WritePin(R_YELLOW_GPIO_Port, R_YELLOW_Pin, 0);
						} else {
							HAL_GPIO_WritePin(R_RED_GPIO_Port, R_RED_Pin, 1);
							HAL_GPIO_WritePin(R_YELLOW_GPIO_Port, R_YELLOW_Pin, 1);
						}
//						snprintf(uart_buffer, sizeof(uart_buffer), "RIGHT %d = %5dmm\n", j + 1, pMultiRangingData->RangeData[j].RangeMilliMeter);
//						HAL_UART_Transmit(&huart2, (uint8_t *)uart_buffer, strlen(uart_buffer), HAL_MAX_DELAY);
					}
				}
				if (status==0){
					status = VL53LX_ClearInterruptAndStartMeasurement(DevRight);
				}
			}
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_4;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Power Configuration
  * @retval None
  */
static void SystemPower_Config(void)
{
  HAL_PWREx_EnableVddIO2();

  /*
   * Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
   */
  HAL_PWREx_DisableUCPDDeadBattery();

  /*
   * Switch to SMPS regulator instead of LDO
   */
  if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK)
  {
    Error_Handler();
  }
/* USER CODE BEGIN PWR */
/* USER CODE END PWR */
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x00000E14;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
static void MX_ICACHE_Init(void)
{

  /* USER CODE BEGIN ICACHE_Init 0 */

  /* USER CODE END ICACHE_Init 0 */

  /* USER CODE BEGIN ICACHE_Init 1 */

  /* USER CODE END ICACHE_Init 1 */

  /** Enable instruction cache in 1-way (direct mapped cache)
  */
  if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ICACHE_Init 2 */

  /* USER CODE END ICACHE_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  SPI_AutonomousModeConfTypeDef HAL_SPI_AutonomousMode_Cfg_Struct = {0};

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES_TXONLY;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 0x7;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  hspi1.Init.ReadyMasterManagement = SPI_RDY_MASTER_MANAGEMENT_INTERNALLY;
  hspi1.Init.ReadyPolarity = SPI_RDY_POLARITY_HIGH;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerState = SPI_AUTO_MODE_DISABLE;
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerSelection = SPI_GRP1_GPDMA_CH0_TCF_TRG;
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerPolarity = SPI_TRIG_POLARITY_RISING;
  if (HAL_SPIEx_SetConfigAutonomousMode(&hspi1, &HAL_SPI_AutonomousMode_Cfg_Struct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, R_RED_Pin|LED_RED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TOF_R_XSHUT_GPIO_Port, TOF_R_XSHUT_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, RESET_Pin|CS_Pin|L_RED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TOF_L_XSHUT_GPIO_Port, TOF_L_XSHUT_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(L_YELLOW_GPIO_Port, L_YELLOW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(R_YELLOW_GPIO_Port, R_YELLOW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_BUTTON_Pin */
  GPIO_InitStruct.Pin = USER_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TOF_R_INT_Pin */
  GPIO_InitStruct.Pin = TOF_R_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TOF_R_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DC_Pin */
  GPIO_InitStruct.Pin = DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : R_RED_Pin LED_RED_Pin */
  GPIO_InitStruct.Pin = R_RED_Pin|LED_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : TOF_R_XSHUT_Pin */
  GPIO_InitStruct.Pin = TOF_R_XSHUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TOF_R_XSHUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RESET_Pin CS_Pin L_RED_Pin */
  GPIO_InitStruct.Pin = RESET_Pin|CS_Pin|L_RED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : TOF_L_INT_Pin */
  GPIO_InitStruct.Pin = TOF_L_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TOF_L_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TOF_L_XSHUT_Pin */
  GPIO_InitStruct.Pin = TOF_L_XSHUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TOF_L_XSHUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_GREEN_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : L_YELLOW_Pin */
  GPIO_InitStruct.Pin = L_YELLOW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(L_YELLOW_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : R_YELLOW_Pin */
  GPIO_InitStruct.Pin = R_YELLOW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(R_YELLOW_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_BLUE_Pin */
  GPIO_InitStruct.Pin = LED_BLUE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_BLUE_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM17 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM17) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
