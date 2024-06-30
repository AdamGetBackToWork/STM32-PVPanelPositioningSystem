/*
 * Autor: Adam Szajgin | s319821 | Politechnika Warszawska | Wydzial Elektroniki i Technik Informacyjnych
 *
 * Jest to jednofunkcyjna biblioteka zawierająca funkcję do ustawienia pozycji serwomechanizmu
 * pobiera ona wskaznik timera ktory obsluguje dany PWM, kanal tego timera, oraz kat obrotu i tryb
 *
 * Najpierw sprawdza ograniczenia katowe serwomechanizmow (sa one 0-180*)a nastepnie w zaleznosci
 * od wartosci trybu w ktorym dziala albo obraca serwo zgodnie z ruchem zegara albo nie
 *
 * ang - kąt obrotu wału serwomechanizmu
 * mode - tryb obrotu zgodnie/przeciwnie do wskazówek zegara
 */

#ifndef INC_SERVOMANAGER_H_
#define INC_SERVOMANAGER_H_

#include <stdint.h> // Dołączenie nagłówka dla typów całkowitych o ustalonej szerokości (np. uint8_t, uint16_t).
#include "tim.h"    // Dołączenie nagłówka dla obsługi timerów (TIM_HandleTypeDef).

// Definicje stałych dla zakresu kątów serwomechanizmu.
#define ANGLE_MIN 0     // Minimalny kąt serwomechanizmu (w setnych stopnia).
#define ANGLE_MAX 1800  // Maksymalny kąt serwomechanizmu (w setnych stopnia).

// Definicje stałych dla wartości PWM odpowiadających minimalnemu i maksymalnemu kątowi.
#define PWM_MIN 240     // Minimalna wartość PWM odpowiadająca minimalnemu kątowi.
#define PWM_MAX 1200    // Maksymalna wartość PWM odpowiadająca maksymalnemu kątowi.

// Obliczenie kroku PWM dla każdego stopnia (przeliczone na setne części stopnia).
// STEP określa zmianę wartości PWM na każdy stopień zmiany kąta.
#define STEP ((1000 * (PWM_MAX - PWM_MIN)) / (ANGLE_MAX - ANGLE_MIN))

// Deklaracja funkcji setAngle, która ustawia kąt serwomechanizmu.
// Parametry:
// - TIM_HandleTypeDef *tim: wskaźnik do struktury obsługującej timer.
// - uint8_t channNum: numer kanału timera.
// - uint16_t ang: kąt serwomechanizmu do ustawienia (w setnych stopnia).
// - uint8_t mode: tryb pracy (możliwe rozszerzenie funkcji).
void setAngle(TIM_HandleTypeDef *tim, uint8_t channNum, uint16_t ang, uint8_t mode);

// Deklaracja funkcji setDefault, która ustawia defaultowe ustawienia systemu
void setDefault();

#endif /* INC_SERVOMANAGER_H_ */
