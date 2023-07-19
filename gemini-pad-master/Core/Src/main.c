/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "usbd_hid.h"
#include "stdlib.h"
#include "analog.h"
#include "rgb.h"
#include "keyboard.h"
#include "flash_address.h"
#include "MB85RC16.h"
#include "communication.h"
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

/* USER CODE BEGIN PV */
uint32_t count=0;
uint8_t cmd_buffer;
bool sendreport=true;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_ADC4_Init();
  MX_TIM7_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_USB_DEVICE_Init();
  MX_TIM17_Init();
  MX_TIM2_Init();
  MX_TIM6_Init();
  MX_TIM16_Init();
  MX_I2C2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */


  HAL_TIM_PWM_Start(&htim17,TIM_CHANNEL_1);
  RGB_Start();


  //Analog_Init();
  Analog_Recovery();
  RGB_Flash();
  RGB_TurnOff();
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim7);
  HAL_TIM_Encoder_Start_IT(&htim2,TIM_CHANNEL_1);
  HAL_TIM_Encoder_Start_IT(&htim3,TIM_CHANNEL_1);
  MX_USART1_UART_Init();
  Communication_Enable(&huart1,USART1_RX_Buffer,BUFFER_LENGTH);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	Analog_Scan();
	//adccount++;
    //RGB_Colors[0].R=ADC_Values[0]-2800;
    RGB_Set(RGB_Colors[0].r,RGB_Colors[0].g,RGB_Colors[0].b,0);
    RGB_Set(RGB_Colors[1].r,RGB_Colors[1].g,RGB_Colors[1].b,1);
    RGB_Set(RGB_Colors[2].r,RGB_Colors[2].g,RGB_Colors[2].b,2);
    RGB_Set(RGB_Colors[3].r,RGB_Colors[3].g,RGB_Colors[3].b,3);
    //HAL_Delay(1);
    switch (cmd_buffer)
    {
        case CMD_CALIBRATION_START:
            keyBoardHIDsub.KEYCODE1=0;
            keyBoardHIDsub.KEYCODE2=0;
            keyBoardHIDsub.KEYCODE3=0;
            keyBoardHIDsub.KEYCODE4=0;
            keyBoardHIDsub.KEYCODE5=0;
            keyBoardHIDsub.KEYCODE6=0;
            USBD_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&keyBoardHIDsub,sizeof(keyBoardHIDsub));
            cmd_buffer=CMD_NULL;
            HAL_TIM_Base_Stop_IT(&htim7);
            Analog_Init();
            HAL_TIM_Base_Start_IT(&htim7);
            break;
        case CMD_REPORT_START:
            sendreport=true;
            cmd_buffer=CMD_NULL;
            break;
        case CMD_REPORT_STOP:
            sendreport=false;
            cmd_buffer=CMD_NULL;
            break;
        default:
            break;
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_I2C2|RCC_PERIPHCLK_TIM8
                              |RCC_PERIPHCLK_ADC12|RCC_PERIPHCLK_ADC34;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  PeriphClkInit.Adc34ClockSelection = RCC_ADC34PLLCLK_DIV1;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_HSI;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  PeriphClkInit.Tim8ClockSelection = RCC_TIM8CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance==TIM7)
  {

    Keyboard_Scan();
    Analog_Average();
    Analog_Check();
    if(sendreport)
        Keyboard_SendReport();
    Communication_Pack();
    Communication_Transmit();
    /*
	RGB_Colors[0].r=(uint8_t)(255.0*Analog_Values[0]);
	RGB_Colors[1].b=(uint8_t)(255.0*Analog_Values[1]);
    RGB_Colors[2].g=(uint8_t)(255.0*Analog_Values[2]);
	RGB_Colors[3].r=(uint8_t)(255.0*Analog_Values[3]);
	RGB_Colors[3].g=(uint8_t)(255.0*Analog_Values[3]);
	*/
#define COLOR_INTERVAL(key,low,up) (uint8_t)(key<0?low:(key>1.0?up:key*up))
    RGB_Colors[0].r=COLOR_INTERVAL(advanced_keys[0].value,0,255.0);
    RGB_Colors[0].g=COLOR_INTERVAL(advanced_keys[0].value,0,34.0);
    RGB_Colors[0].b=COLOR_INTERVAL(advanced_keys[0].value,0,145.0);
    RGB_Colors[1].r=COLOR_INTERVAL(advanced_keys[1].value,0,255.0);
    RGB_Colors[1].g=COLOR_INTERVAL(advanced_keys[1].value,0,180.0);
    RGB_Colors[1].b=COLOR_INTERVAL(advanced_keys[1].value,0,0);
    RGB_Colors[2].r=COLOR_INTERVAL(advanced_keys[2].value,0,51.0);
    RGB_Colors[2].g=COLOR_INTERVAL(advanced_keys[2].value,0,80.0);
    RGB_Colors[2].b=COLOR_INTERVAL(advanced_keys[2].value,0,136.0);
    RGB_Colors[3].r=COLOR_INTERVAL(advanced_keys[3].value,0,255.0);
    RGB_Colors[3].g=COLOR_INTERVAL(advanced_keys[3].value,0,70.0);
    RGB_Colors[3].b=COLOR_INTERVAL(advanced_keys[3].value,0,145.0);
	//RGB_Colors[1].B=Keyboard_Keys[1]?0:128;
    /*
    RGB_Colors[0].g=Keyboard_Keys[0]?RGB_Colors[0].G?RGB_Colors[0].G-=1:0:128;
    RGB_Colors[1].b=Keyboard_Keys[1]?RGB_Colors[1].B?RGB_Colors[1].B-=1:0:128;
    RGB_Colors[2].g=Keyboard_Keys[2]?RGB_Colors[2].G?RGB_Colors[2].G-=1:0:128;
    RGB_Colors[3].r=Keyboard_Keys[3]?RGB_Colors[3].R?RGB_Colors[3].R-=1:0:128;
    RGB_Colors[3].g=Keyboard_Keys[3]?RGB_Colors[3].G?RGB_Colors[3].G-=1:0:128;
    */

	Analog_Clean();
  }

  if (htim->Instance==TIM6)
  {

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
