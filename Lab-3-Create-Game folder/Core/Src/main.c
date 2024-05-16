/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stdio.h"
#include "string.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define EEPROM_ADDR 0b10100000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;

UART_HandleTypeDef hlpuart1;
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_lpuart1_tx;
DMA_HandleTypeDef hdma_lpuart1_rx;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USER CODE BEGIN PV */

// For Send Questions to PuTTy "
uint8_t Hx[30] = "Quiz The Question !\n\r";
uint8_t Tx1[100] = "1). 1 + 1 = 2 ? (y/n)\n\r";
uint8_t Tx2[100] = "2). Microcon is EZ ! (y/n)\n\r";
uint8_t Tx3[100] = "3). Boss is handsome.(y/n)\n\r";
uint8_t Ax1[40] = "Your answer is ?:\n\r";
uint8_t GetAns[2];
uint8_t res1[30] = "You answered Yes.\r\n";
uint8_t res2[30] = "You answered No.\r\n";
uint8_t ToT[30] = "-*Scoreboard*-\n\r";
uint8_t ToT2[50] = "Top  Score : Boss : 100 points\n\r";
uint8_t S[50] = "Your Score : You  : 0 points\n\r";
uint8_t S1[50] = "Your Score : You  : 1 points\n\r";
uint8_t S2[50] = "Your Score : You  : 2 points\n\r";
uint8_t S3[50] = "Your Score : You  : 3 points\n\r";
uint8_t s1 = 0;
uint8_t s2 = 0;
uint8_t s3 = 0;
int mode = 0;

uint8_t TotalScore = 0;//Send to I2C

// I2C Part //
uint8_t WriteFlag = 0;
uint8_t ReadFlag = 0;
uint8_t ReadBack[1];

// Test Number //
int A = 8;
int B = 0;
int C = 0;
uint8_t D[1];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

// STM32 Part //
void Dummy();

// I2C Part //
void EEPROMWriteExample();
void EEPROMReadExample(uint8_t *Rdata, uint16_t len);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_LPUART1_UART_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(100);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // STM32 Part //
	  Dummy();
	  HAL_UART_Receive_DMA(&hlpuart1, GetAns, 2);
	if(A==8){
	  HAL_UART_Transmit(&hlpuart1,Hx, strlen(Hx), 4);
	  HAL_UART_Transmit(&hlpuart1,"-------------------------\n\r",strlen("-------------------------\n\r"), 8);
	  A=1;
	}
// Question 1 //
		if(A == 1){
			HAL_Delay(1000);
			HAL_UART_Transmit(&hlpuart1,Tx1, 100,10);
			HAL_UART_Transmit(&hlpuart1,Ax1, 40,10);
			A = 0;
			mode = 1;
		}
		if(mode == 1){
			if(GetAns[0] == 'y' && GetAns[1] == '\r' && mode == 1){
				HAL_UART_Transmit(&hlpuart1, res1, 30, 10);
				HAL_UART_Transmit(&hlpuart1,"*********\n\r",strlen("**********\n\r"), 8);
				s1 =+ 1;
				A = 2;
				GetAns[0]=0;
				GetAns[1]=0;
			}
			else if(GetAns[0] == 'n' && GetAns[1] == '\r' && mode == 1){
				HAL_UART_Transmit(&hlpuart1, res2, 30, 10);
				HAL_UART_Transmit(&hlpuart1,"*********\n\r",strlen("**********\n\r"), 8);
				A = 2;
				GetAns[0]=0;
				GetAns[1]=0;
			}
//			else if(GetAns[0] != 0 && GetAns[1] != 0){
//				char response[] = "Invalid Answer, Try Again.\r\n";
//				HAL_UART_Transmit(&huart1,response, strlen(response), 10);
//				A = 1;
//				mode = 0;
//				GetAns[0]=0;
//				GetAns[1]=0;
//			}
		}
// Question 2 //
		if(A == 2){
			HAL_Delay(500);
			HAL_UART_Transmit(&hlpuart1,Tx2, 100,10);
			HAL_UART_Transmit(&hlpuart1,Ax1, 40,10);
			A = 0;
			mode = 2;
		}
		if(mode == 2){
			if(GetAns[0] == 'y' && GetAns[1] == '\r' && mode == 2){
				HAL_UART_Transmit(&hlpuart1, res1, 30, 10);
				HAL_UART_Transmit(&hlpuart1,"*********\n\r",strlen("**********\n\r"), 8);
				A = 3;
				GetAns[0]=0;
				GetAns[1]=0;
			}
			else if(GetAns[0] == 'n' && GetAns[1] == '\r' && mode == 2){
				HAL_UART_Transmit(&hlpuart1, res2, 30, 10);
				HAL_UART_Transmit(&hlpuart1,"*********\n\r",strlen("**********\n\r"), 8);
				s2 =+ 1;
				A = 3;
				GetAns[0]=0;
				GetAns[1]=0;
			}
		}
// Question 3 //
		if(A == 3){
			HAL_Delay(500);
			HAL_UART_Transmit(&hlpuart1,Tx3, 100,10);
			HAL_UART_Transmit(&hlpuart1,Ax1, 40,10);
			A = 0;
			mode = 3;
		}
		if(mode == 3){
			if(GetAns[0] == 'y' && GetAns[1] == '\r' && mode == 3){
				HAL_UART_Transmit(&hlpuart1, res1, 30, 10);
				HAL_UART_Transmit(&hlpuart1,"*********\n\r",strlen("**********\n\r"), 8);
				s3 =+ 1;
				A = 4;
				GetAns[0]=0;
				GetAns[1]=0;
			}
			else if(GetAns[0] == 'n' && GetAns[1] == '\r' && mode == 3){
				HAL_UART_Transmit(&hlpuart1, res2, 30, 10);
				HAL_UART_Transmit(&hlpuart1,"*********\n\r",strlen("**********\n\r"), 8);
				A = 4;
				GetAns[0]=0;
				GetAns[1]=0;
			}
		}
//ScoreBoard //
		if(A == 4){
			HAL_Delay(500);
			HAL_UART_Transmit(&hlpuart1, ToT, 30, 10);
			HAL_UART_Transmit(&hlpuart1, ToT2, 50, 10);
			TotalScore = s1+s2+s3;
			A=5;
		}
// I2C part //
		if(A == 5){
			HAL_Delay(1000);
			WriteFlag = 1;
			C = 1;
			A=6;
		}
		if(A == 6){
			if(C == 1){
				ReadFlag = 1;
				C = 0;
			}
			A=7;
		}
		if(A == 7){
			strcpy(D,ReadBack);//compare
			if (D[0] == 0){
				B = 4;
				HAL_UART_Transmit(&hlpuart1, S, 50, 10);
			}
			else if(D[0] == 1){
				B = 1;
				HAL_UART_Transmit(&hlpuart1, S1, 50, 10);
			}
			else if(D[0] == 2){
				B = 2;
				HAL_UART_Transmit(&hlpuart1, S2, 50, 10);
			}
			else if(D[0] == 3){
				B = 3;
				HAL_UART_Transmit(&hlpuart1, S3, 50, 10);
			}
			HAL_UART_Transmit(&hlpuart1,"YOU ARE NOOB,LOSER UwU.\n\r", 50, 10);
			A=0;
		}
  EEPROMWriteExample();
  EEPROMReadExample(ReadBack, 1);
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x30A0A7FB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_9B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_EVEN;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

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
  huart1.Init.WordLength = UART_WORDLENGTH_9B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_EVEN;
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
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// I2C PART //
void EEPROMWriteExample() {
	if (WriteFlag && hi2c1.State == HAL_I2C_STATE_READY) {
	static uint8_t data[4];
	 data[0]=TotalScore;
	 data[1]=0x00;
	 data[2]=0x00;
	 data[3]=0x00;
		HAL_I2C_Mem_Write_IT(&hi2c1, EEPROM_ADDR, 0x2C, I2C_MEMADD_SIZE_16BIT,data, 1);
		WriteFlag = 0;
	}
}
void EEPROMReadExample(uint8_t *Rdata, uint16_t len) {
	if (ReadFlag && hi2c1.State == HAL_I2C_STATE_READY) {
		HAL_I2C_Mem_Read_IT(&hi2c1, EEPROM_ADDR, 0x2c, I2C_MEMADD_SIZE_16BIT,Rdata, len);
		ReadFlag = 0;
	}
}



// For LD2 Test //
void Dummy(){
	static uint32_t timestamp=0;
	if(HAL_GetTick()>=timestamp){
		timestamp = HAL_GetTick()+100;
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	}
}
/* USER CODE END 4 */

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
