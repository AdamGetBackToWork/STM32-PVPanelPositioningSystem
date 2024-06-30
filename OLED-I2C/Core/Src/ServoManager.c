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

#include <ServoManager.h> // Dołączenie nagłówka dla zarządzania serwomechanizmem.
#include "tim.h"          // Dołączenie nagłówka dla obsługi timerów.

void setAngle(TIM_HandleTypeDef *tim, uint8_t channNum, uint16_t ang, uint8_t mode)
{
    uint16_t setValue; // Zmienna przechowująca wartość PWM do ustawienia.

    // Sprawdzenie, czy podany kąt mieści się w zakresie.
    // Jeżeli nie, to ograniczenie wartości do maksymalnego lub minimalnego kąta.
    if (ang > ANGLE_MAX)
    {
        ang = ANGLE_MAX; // Ograniczenie kąta do wartości maksymalnej.
    }
    else if (ang < ANGLE_MIN)
    {
        ang = ANGLE_MIN; // Ograniczenie kąta do wartości minimalnej.
    }

    // Obliczenie wartości PWM na podstawie kąta i trybu obrotu.
    if (mode)
    {
        // Tryb zgodny ze wskazówkami zegara.
        // Przeliczenie kąta na wartość PWM przy użyciu wzoru: PWM_MIN + ((ang - ANGLE_MIN) * STEP) / 1000
    	setValue = PWM_MIN + ((ang - ANGLE_MIN) * STEP) / 1000;
    }
    else
    {
        // Tryb przeciwny do wskazówek zegara.
        // Przeliczenie kąta na wartość PWM przy użyciu wzoru: PWM_MAX - ((ang - ANGLE_MIN) * STEP) / 1000
    	setValue = PWM_MAX - ((ang - ANGLE_MIN) * STEP) / 1000;
    }

    // Ustawienie wartości PWM dla odpowiedniego kanału timera.
    __HAL_TIM_SET_COMPARE(tim, channNum, setValue);
}

// funjkcja setDefault, która ustawia defaultowe ustawienia systemu
void setDefault(){

    setAngle(&htim3, TIM_CHANNEL_2 , 900, 0);
    setAngle(&htim3, TIM_CHANNEL_4 , 900, 0);

}
