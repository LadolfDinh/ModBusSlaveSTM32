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
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
  uint8_t low;
  uint8_t high;
} crc_result_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define slaveAdd 0x02
#define uartTimeOut 50
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
crc_result_t get_CRC16(const uint8_t* data, size_t length);
void Response_ReadHoldingRegister();
void Response_PresetMultipleRegister();
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart4;

/* USER CODE BEGIN PV */
uint16_t slaveRegister[0xFF];
uint8_t Tx_buffer[0xFF];
uint8_t Rx_buffer[0xFF];
uint8_t *Header;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_UART4_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart4, Header, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_2;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7|GPIO_PIN_10, GPIO_PIN_SET);

  /*Configure GPIO pin : PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PE7 PE10 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == UART4)
  {
     if (Header != slaveAdd) {                 // Checking address
       HAL_UART_Receive_IT(&huart4, Header, 1);
       return;
     }
    // got it

    HAL_UART_Receive(&huart4, Header, 1, uartTimeOut);      // receive function code
    switch (Header)
    {
    case 0x03:

      //Response_ReadHoldingRegister();
      HAL_UART_Transmit(&huart4, Tx_buffer, 7, uartTimeOut);
      break;
    case 0x10:

      Response_ReadHoldingRegister();
      break;
    default:
      break;
    }
    HAL_UART_Receive_IT(&huart4, Rx_buffer, 1);
  }
}
// Function 0x03 ///////////////////////////////////////////////////
void Response_ReadHoldingRegister()
{
  int cnn = 0;
  Tx_buffer[cnn++] = 2;
  Tx_buffer[cnn++] = 0x03;
  uint8_t temp[2] = {0x00, 0x00};
  HAL_UART_Receive(&huart4, temp, 2, uartTimeOut); // Get the rest of the modbus message
  uint16_t tempRegisterAddress = (temp[0] << 8) | temp[1];
  HAL_UART_Receive(&huart4, temp, 2, uartTimeOut);
  uint16_t tempNumberOfRegister = (temp[0] << 8) | temp[1];
  HAL_UART_Receive(&huart4, temp, 2, uartTimeOut);
  uint16_t tempcrc = (temp[0] << 8) | temp[1];
  Tx_buffer[cnn++] = tempNumberOfRegister * 2; // Byte count
  for (int i = tempRegisterAddress; i < (tempRegisterAddress + tempNumberOfRegister); i++)
  {
    Tx_buffer[cnn++] = (slaveRegister[i] >> 8) & 0xFF; // High byte
    Tx_buffer[cnn++] = slaveRegister[i] & 0xFF;       // Low byte
  }
  // Generate CRC
  crc_result_t crc_result = get_CRC16(Tx_buffer, cnn);
  Tx_buffer[cnn++] = crc_result.low;
  Tx_buffer[cnn++] = crc_result.high;
  // Send message
  HAL_UART_Transmit(&huart4, Tx_buffer, cnn, uartTimeOut);
}
// Function 0x10 ///////////////////////////////////////////////////
void Response_PresetMultipleRegister()
{
  int cnn = 0;
  // Get starting address and number of register
  HAL_UART_Receive(&huart4, Rx_buffer + 2, 5, uartTimeOut);
  uint16_t tempRegisterAddress = (Rx_buffer[2] << 8) | Rx_buffer[3];
  uint16_t tempNumberOfRegister = (Rx_buffer[4] << 8) | Rx_buffer[5];
  uint8_t tempNumberByte = Rx_buffer[6];
  // Get data
  HAL_UART_Receive(&huart4, Rx_buffer + 7, tempNumberByte, uartTimeOut);
  // Sign data to slave's register
  int dataCount = 7;
  for (int i = tempRegisterAddress; i < (tempRegisterAddress + tempNumberOfRegister); i++)
  {
      slaveRegister[i] = Rx_buffer[dataCount] << 8 | Rx_buffer[dataCount + 1];
      dataCount = dataCount + 2;
  }
  // Packing echo response message
  for (int i = 0; i < 6; i++)
  {
    Tx_buffer[i] = Rx_buffer[i];
    cnn = cnn + 1;
  }
  // Generate CRC
  crc_result_t crc_result = get_CRC16(Tx_buffer, cnn);
  Tx_buffer[cnn] = crc_result.low;
  cnn = cnn + 1;
  Tx_buffer[cnn] = crc_result.high;
  cnn = cnn + 1;
  // Send message
  HAL_UART_Transmit(&huart4, Tx_buffer, cnn, uartTimeOut);

}
// CRC generater //////////////////////////////////////////////////
crc_result_t get_CRC16(const uint8_t* data, size_t length)
{
  uint16_t crc = 0xFFFF;

  for (size_t pos = 0; pos < length; pos++)
  {
    crc ^= data[pos];

    for (int i = 8; i != 0; i--)
    {
      if ((crc & 0x0001) != 0)
      {
        crc >>= 1;
        crc ^= 0xA001;
      }
      else
      {
        crc >>= 1;
      }
    }
  }

  crc_result_t result;
  result.low = (uint8_t)(crc & 0xFF);
  result.high = (uint8_t)(crc >> 8);

  return result;
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
