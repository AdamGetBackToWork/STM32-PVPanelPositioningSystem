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


/*
 * -------------------------- METRYCZKA PROGRAMU -------------------------------
 *
 * Autor: Adam Szajgin | s319821 | Politechnika Warszawska | Wydzial Elektroniki i Technik Informacyjnych
 *
 * Nazwa: System pozycjonowania panela fotowoltaicznego z dwoma sposobami sterowania
 *
 * Opis:
 * - System pozycjonowania panela fotowoltaicznego jest programem wbudowanym napisanym w
 *   języku C dla mikrokontrolera STM32-L073RZT6.
 * - Program ten umożliwia sterowanie kątem położenia panela fotowoltaicznego w celu
 *   maksymalizacji pozyskiwanej energii ze światła słonecznego.
 * - Sterowanie odbywa się na podstawie odczytów z dzielników rezystancyjnych z
 *   fotorezystorami oraz sygnałów z telefonu zbieranych przez moduł Bluetooth HC-06.
 *
 *
 * Funkcjonalność:
 * 1. Algorytm Pozycjonowania Słonecznego:
 *    - Odczytuje wartości natężenia światła z czterech kanałów dzielników rezystancyjnych.
 *    - Na podstawie odczytanych wartości oblicza kąt położenia panela fotowoltaicznego w poziomie i pionie.
 *    - Zmienia kąt położenia panela w odpowiedzi na zmiany natężenia światła, tak aby maksymalizować
 *      pobieranie energii słonecznej.
 *    - Umożliwia nieblokujące opóźnienia dla zapewnienia odpowiedniego odstępu czasowego między operacjami.
 * 2. Sterowanie Ręczne:
 *    - Odbiera sygnały z telefonu przez interfejs Bluetooth HC-06.
 *    - Pozwala na manualne sterowanie kątem położenia panela fotowoltaicznego w poziomie i pionie na żądanie użytkownika.
 *    - Przekazuje otrzymane sygnały do odpowiednich funkcji sterujących.
 *
 *
 * Struktura:
 * - main.c: Główny plik programu, zawiera funkcję main() oraz konfiguracje mikrokontrolera.
 * - SolarPositioningAlgorithm.h/.c: Moduł implementujący algorytm pozycjonowania panela
 *   fotowoltaicznego na podstawie odczytów z dzielników rezystancyjnych.
 * - ManualSteering.h/.c: Moduł obsługujący sterowanie ręczne za pomocą sygnałów z telefonu przez Bluetooth.
 * - GFX.h: Moduł obsługujący wyświetlanie grafiki na ekranie OLED.
 * - DisplayManager.h/.c: Moduł zarządzający wyświetlaniem stanu i parametrów systemu na ekranie OLED.
 * - ADC.h: Konfiguracja i obsługa przetwornika analogowo-cyfrowego.
 * - DMA.h: Konfiguracja i obsługa kontrolera DMA.
 * - I2C.h: Konfiguracja i obsługa interfejsu I2C.
 * - TIM.h: Konfiguracja i obsługa liczników czasu.
 * - USART.h: Konfiguracja i obsługa interfejsu USART.
 * - GPIO.h: Konfiguracja i obsługa pinów GPIO.
 *
 * -------------------------- METRYCZKA PROGRAMU -------------------------------
 */



/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <dataStructs.h>
#include <systemStructs.h>
#include <SolarPositioningAlgorithm.h>
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "GFX.h"
#include "DisplayManager.h"
#include "ManualSteering.h"
#include "stdio.h"
#include "string.h"
#include "SolarAlgorithm.h"
#include "ServoManager.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

// Tablica przetrzmujaca dane zbierane z uzyciem DMA przez ADC z dzielnikow rezaystancyjnych z fotorezystorami
uint16_t AdcResultsArray[4];
// Struct do trzymania Adc Results
ADCResults adcResults;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// struct - otrzymywane przez HC-06 przesylana UART-em - pozniej dopasowywana do pozycji serw w biblitoece ManualSteering.c
SensorData sensorData;
// struct do trzymania katow serwomachnizmow
ServoAngles servoAngles;
// struct stan systemu - ktory algorytm pozycjonowania 1 - od swiatla, 2 - od bluetooth
SystemState systemState;

// zmienna do RX od HC-06 UART
uint8_t rxData;
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
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_I2C2_Init();
  MX_ADC_Init();
  /* USER CODE BEGIN 2 */

  // INICIALIZACJA ZASOBOW PERYFERYJNYCH
  	  // Inicjalizacja ekranu OLED
  	  SSD1306_init();
  	  // Inicjalizacja timerow pod wysylanie sygnalow PWM do serwomechanizmow
  	  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  	  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
  	  // Inicjalizacja UARTa pod odbieranie sygnalow z modulu bluetooth HC-06
  	  HAL_UART_Receive_IT(&huart1, &rxData,1);

  // INICJALIZACJA ZMIENNYCH
  	  // Stany odbierania sygnalow - dyktuje czy urzadzenie moze odbierac sygnaly
  	  // i wobec nich sie pozycjonowac (1) lub je ignotowac (0)
  	  systemState.receivingState = '0';
  	  // Stan pozycjonowania - alboo sterowanie swiatlem (1) albo sterownanie manualne - z telefonu
  	  systemState.positioningState = '1';
  	  // Zmienne katow pozycjonowania serwomechnizmow
  	  servoAngles.horizontalAngle = 900;
  	  servoAngles.verticalAngle = 924;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  // Start Timera do zbierania sygnalow z ADC
  HAL_TIM_Base_Start_IT(&htim2);
  // Start DMA pod zbieranie sygnalow z ADC
  //HAL_ADC_Start_DMA(&hadc, (uint32_t *)AdcResults, 4);
  HAL_ADC_Start_DMA(&hadc, (uint32_t *)AdcResultsArray, 4);
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
	  	 // Zmiana stanu urzadzenia po wcisnieciu przycisku
	  	 if (HAL_GPIO_ReadPin(USER_BUTTON2_GPIO_Port, USER_BUTTON2_Pin) != GPIO_PIN_RESET) {
	  	         togglePositioningState(systemState.stateMemory);
	  	 }
	  	 // Zmiana stanu urzadzenia
	  	 systemState.positioningState = displayState(systemState.stateMemory);
	  	 // Wyswietlenie stanu urzadzenia
	  	 displayParameters(systemState.positioningState, systemState.receivingState, 1, 1);

	     // Glowny switch case programu
	     switch (systemState.positioningState)
	     {
	         case '1':
	             // SolarAlgorithm - pozycjonowanie wobec swiatla
	        	 // zmiana stanu "odbierania" sygnalow z telefonu
	             systemState.receivingState = '0';

	        	 // przypisanie zczytanych z ADC wartosci do zmiennych okreslajacyh natezenie swiatla
	             adcResults.lux = (uint32_t)AdcResultsArray[0];
	             adcResults.lux1 = (uint32_t)AdcResultsArray[1];
	             adcResults.lux2 = (uint32_t)AdcResultsArray[2];
	             adcResults.lux3 = (uint32_t)AdcResultsArray[3];

	             // zwiekszenie lub zmniejszenie wartosci kata poziomego
	             servoAngles.horizontalAngle += compareAndSetHorizontalAngles(adcResults.lux, adcResults.lux1, adcResults.lux2, adcResults.lux3);
	             // sprawdzenie czy kat poziomy nie wykracza poza mechaniczny zakres
	             servoAngles.horizontalAngle = checkHorizontalAngleBounds(servoAngles.horizontalAngle);
	             // ustawienie serwomechanizmu na odpowiedni kat poziomy
	             setAngle(&htim3, TIM_CHANNEL_2 , servoAngles.horizontalAngle, 0);

	             // zwiekszenie lub zmniejszenie wartosci kata pionowego
	             servoAngles.verticalAngle += compareAndSetVerticalAngles(adcResults.lux, adcResults.lux1, adcResults.lux2, adcResults.lux3);
	             // sprawdzenie czy kat pionowy nie wykracza poza mechaniczny zakress
	             servoAngles.verticalAngle = checkVerticalAngleBounds(servoAngles.verticalAngle);
	             // ustawienie serwomechanizmu na odpowiedni kat pionowy
	             setAngle(&htim3, TIM_CHANNEL_4 , servoAngles.verticalAngle, 0);
	             break;

	         case '2':
	             // ManualSteering - pozycjonowanie wobec sygnalow z telefonu
	        	 // zmiana stanu "odbierania" sygnalow
	             systemState.receivingState = '1';
	             break;

	         default:
	        	 // Default by uniknac "niekontrolowanych" zmian stanu
	        	 // wywolanie funkcji przywracajacej stan poczatkowy - Agnles: 900; 900.
	        	 setDefault();
	        	 break;
	     }

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
    	ManualSteering(rxData);
        HAL_UART_Receive_IT(&huart1, &rxData, 1); // Enable interrupt receive again
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
