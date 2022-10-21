/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim10;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
int cnt;
int R_R_FLAG=0;
int At_Flag=0;
char Uart_Data[1024]; // 
char Rx_Flag; // extern
char Rx_Tab;
char Rx_Auto;
char Rx_Reset;
char reset[30]="\n\t******Reset STM******\n";
char message[25]="C - User - ERGUN :";
char message1[20]="Welcome";
char message2[20]="\nWrong Place\n";

char str[1024];
char BO[12]="BLUE ON";
char RO[12]="RED ON";
char OO[12]="ORANGE ON";
char c='\t';
char commands[200]=" \n****COMMANDS**** \n BLUE ON -> For Blue Red On \n RED ON -> For Red Led On \n ORANGE ON -> For Orange Led On \n Q -> For Reset \n Z -> For Get Back \n";
char str1[20];
char str2[20];
char newline[30] = "\n host command# : ";
char welcome[15]="welcome";
char WRONG[20] = "GETTING BACK\n";
int state=0;
char ON1[1]="1";
char ON2[1]="2";

int a;
char user[5]="ADMIN";
char root[5]="ROOT";
char ENTER[20]="\nENTER PASSWORD:";
int B,C;
char WR[20]="\nWRONG PASSWORD ";
char user_host[50]="\nC - USER  \n HOSTNAME: ADMIN";
char root_host[50]="\nC - USER  \n HOSTNAME: ROOT";
int TIM_FLAG=0;
int R_Flag;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM10_Init(void);
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
  MX_USART2_UART_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */
  __HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE); //IT codes
  __HAL_TIM_ENABLE_IT(&htim10, TIM_IT_UPDATE);
  HAL_TIM_Base_Start_IT(&htim10);
  HAL_UART_Transmit(&huart2, &message, strlen(message), 10);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if(Rx_Auto)
	  {
		  R_Flag=0;
		  Rx_Auto=0;
		  HAL_UART_Transmit(&huart2, commands, strlen(commands), 300);
	  }

	  if (Rx_Flag  )
	  {
		  Rx_Flag = 0;
		  strcpy(str2,Uart_Data);
		  switch(state)
		  {

		  case 0 :			// for user
			  R_R_FLAG=0;
			  R_Flag=0;
			  a=strncmp(str2,user,4);
			  if(a==0)
			  {
				  HAL_UART_Transmit(&huart2, &Uart_Data , strlen(Uart_Data), 10);
				  HAL_UART_Transmit(&huart2, ENTER, strlen(ENTER), 10);
				  state=1;	// PASSWORD
			  }
			  else if(strncmp(str2,root,4)==0)
			  {
				  HAL_UART_Transmit(&huart2, &Uart_Data , strlen(Uart_Data), 10);
				  HAL_UART_Transmit(&huart2, ENTER, strlen(ENTER), 10);
				  state=2;	// PASSWORD
			  }
			  else
			  {
				  HAL_UART_Transmit(&huart2, &Uart_Data , strlen(Uart_Data), 10);
				  state=5;  // wrong message
			  }
			  break;

		  case 1 :
			  R_R_FLAG=0;
			  R_Flag=0;
			  B=strncmp(Uart_Data,password,4);   // ADMIN password

			  if(B==0)
			  {
				 At_Flag=1;
				 HAL_UART_Transmit(&huart2, and0, strlen(and0), 10);
				 HAL_UART_Transmit(&huart2, and1, strlen(and1), 10);
				 HAL_UART_Transmit(&huart2, and2, strlen(and2), 10);
				 HAL_UART_Transmit(&huart2, and3, strlen(and3), 10);
				 HAL_UART_Transmit(&huart2, and4, strlen(and4), 10);
				 HAL_UART_Transmit(&huart2, and5, strlen(and5), 10);
				 HAL_UART_Transmit(&huart2, and6, strlen(and6), 10);
				 HAL_UART_Transmit(&huart2, user_host, strlen(user_host), 10);
				 state=3;
			  }
			  else
			  {
				  HAL_UART_Transmit(&huart2, WR, strlen(WR), 10); // WRONG PASSWORD
				  HAL_UART_Transmit(&huart2, ENTER, strlen(ENTER), 10);
				  state=1;
			  }
			  break;

		  case 2:                    //root Password
			  R_R_FLAG=0;
			  R_Flag=0;
			  C=strncmp(Uart_Data,password2,4);

			  if(C==0)
			  {
				  At_Flag=1;
				  HAL_UART_Transmit(&huart2, and0, strlen(and0), 10);
				  HAL_UART_Transmit(&huart2, and1, strlen(and1), 10);
				  HAL_UART_Transmit(&huart2, and2, strlen(and2), 10);
				  HAL_UART_Transmit(&huart2, and3, strlen(and3), 10);
				  HAL_UART_Transmit(&huart2, and4, strlen(and4), 10);
				  HAL_UART_Transmit(&huart2, and5, strlen(and5), 10);
				  HAL_UART_Transmit(&huart2, and6, strlen(and6), 10);
				  HAL_UART_Transmit(&huart2, root_host, strlen(root_host), 10);
				  state=3;
			  }

			  else
			  {
				  HAL_UART_Transmit(&huart2, WR, strlen(WR), 10);  // WRONG PASSWORD
				  HAL_UART_Transmit(&huart2, ENTER, strlen(ENTER), 10);
				  state=2;
			  }
			 break;

		  case 3:     // for process

			  R_Flag=0;
			  HAL_UART_Transmit(&huart2, &newline , strlen(newline), 10);
			  strcpy(str,Uart_Data);
			  memset(Uart_Data,0,sizeof(Uart_Data)); // 

			  if(R_R_FLAG==1)
			  {
				  HAL_UART_Transmit(&huart2, reset, strlen(reset),10);
				  state=0;

			  }

			  if  ( str[0]=='Q') // Reset PART
			  {
				  HAL_UART_Transmit(&huart2, &str , strlen(str), 10);
				  HAL_UART_Transmit(&huart2, reset, strlen(reset),10);
				  HAL_NVIC_SystemReset();
			  }

			  else if( str[0]=='Z') // GETTİNG BACK
			  {
				  HAL_UART_Transmit(&huart2, &str , strlen(str), 10);
				  state=4;
			  }

			  else if(str[0]!='\r'  )
			  {
				  HAL_UART_Transmit(&huart2, &str , strlen(str), 10);
				  if(strncmp(str,BO,7)==0) //blue
				  {
					  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,SET);
				  }
				  else if (strncmp(str,RO,4)==0) // red
				  {
					  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14,SET);
				  }
				  else if(strncmp(str,OO,9)==0)//orange
				  {
					  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, SET);
				  }
			 }
			  break;

		  case 4: 												// for getting back
			  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, RESET);
			  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, RESET);
			  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, RESET);

			  HAL_UART_Transmit(&huart2, &WRONG, strlen(WRONG), 10);

			  state=3;
			  break;

		  case 5:				// WRONG PLACE PART
			  if(Uart_Data[0] == '\r')
			  {

				  HAL_UART_Transmit(&huart2, &message, strlen(message), 10);
				  memset(Uart_Data,0,sizeof(Uart_Data));
				  state=0;

			  }
			  else
			  {
				  HAL_UART_Transmit(&huart2, &message2, strlen(message2), 10);
				  HAL_UART_Transmit(&huart2, &message, strlen(message), 10);
				  memset(Uart_Data,0,sizeof(Uart_Data));
				  state=0;
			  }
			  break;
		  } // switch ends
	  } // if ends

	  if (Rx_Tab && At_Flag)
	  {
		  R_Flag=0;
		  Rx_Tab=0;
		  HAL_UART_Transmit(&huart2, &newline , strlen(newline), 10);
		  strcpy(str,Uart_Data);
		  memset(Uart_Data,0,sizeof(Uart_Data)); 
		  char keywords[6][20] = {"RED ON","ORANGE ON","BLUE ON"};
		  HAL_UART_Transmit(&huart2, &str , strlen(str), 10);
		  if(str[0]!='\t')
		  {
			  for(int i = 0; i < 6; i++)		// FOR AUTOCOMPLETE
			  {
				  for(int j = 0; j < 5; j++)
				  {
					  if(strncmp(str, keywords[i],strlen(str)-1) == 0)
					  {
						  HAL_UART_Transmit(&huart2, &newline , strlen(newline), 10);

						  HAL_UART_Transmit(&huart2, keywords[i], strlen(keywords[i]), 200);
						  strcpy(str1,keywords[i]);

						  if(strncmp(str1,BO,7)==0) //blue
						  {
							  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,SET);
						  }
						  else if (strncmp(str1,RO,4)==0) // red
						  {
							  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14,SET);

						  }
						  else if(strncmp(str1,OO,9)==0)//orange
						  {
							  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, SET);
						  }

						  break;
					  }


					  else
					  {
						  memset(Uart_Data,0,sizeof(Uart_Data));

						  break;
					  }
				  }
			  }
		  }
	  }


  } // while end
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 16000;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 65000;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */

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
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_I2C_SPI_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_I2C_SPI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : I2S3_WS_Pin */
  GPIO_InitStruct.Pin = I2S3_WS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(I2S3_WS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI1_SCK_Pin SPI1_MISO_Pin SPI1_MOSI_Pin */
  GPIO_InitStruct.Pin = SPI1_SCK_Pin|SPI1_MISO_Pin|SPI1_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CLK_IN_Pin */
  GPIO_InitStruct.Pin = CLK_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                           Audio_RST_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : I2S3_MCK_Pin I2S3_SCK_Pin I2S3_SD_Pin */
  GPIO_InitStruct.Pin = I2S3_MCK_Pin|I2S3_SCK_Pin|I2S3_SD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_FS_Pin */
  GPIO_InitStruct.Pin = VBUS_FS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VBUS_FS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_FS_ID_Pin OTG_FS_DM_Pin OTG_FS_DP_Pin */
  GPIO_InitStruct.Pin = OTG_FS_ID_Pin|OTG_FS_DM_Pin|OTG_FS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Audio_SCL_Pin Audio_SDA_Pin */
  GPIO_InitStruct.Pin = Audio_SCL_Pin|Audio_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    R_Flag++;
    if(R_Flag>=4)
    {
    	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
    	R_R_FLAG=1;
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
