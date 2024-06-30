/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

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
#define USER_BUTTON2_Pin GPIO_PIN_5
#define USER_BUTTON2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
