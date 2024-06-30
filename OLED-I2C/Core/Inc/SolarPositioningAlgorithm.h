/*
 * Autor: Adam Szajgin | s319821 | Politechnika Warszawska | Wydzial Elektroniki i Technik Informacyjnych
 *
 * Jest to biblioteka do ustawiania pozycji serwomechanizmow wzgledem pobieranych z ADC
 * wartosci natezenia swiatla.
 *
 * Dodatkowo zawiera funkcje wprowadzajaca opoznienie, jako alternatywe dla HAL_Delay()
 *
 * Kazdy z katow (horyzontalny i wertykalny) zawiera swoja funkcje go obslugujace,
 * Funkcje ziwekszajace konty lub zmniejszajace oraz pozniej sprawdzajace czy serwomechanizmy
 * nie wykraczaja poza zakres
 *
 */

#ifndef SOLARPOSITIONINGALGORITHM_H
#define SOLARPOSITIONINGALGORITHM_H

#include <stdint.h> // Dołączenie nagłówka dla typów całkowitych o ustalonej szerokości (np. uint8_t, uint32_t).

// Deklaracja funkcjio do zaokraglania wartosci do pelnych setek. pobniera wartosc i zwraca zaokraglona.
uint16_t roundToHundred(uint16_t value);

// Deklaracja funkcji, która porównuje wartości z czterech czujników i ustawia odpowiedni kąt poziomy.
// Parametry:
// - uint16_t A: wartość ADC z pierwszego czujnika.
// - uint16_t B: wartość ADC z drugiego czujnika.
// - uint16_t C: wartość ADC z trzeciego czujnika.
// - uint16_t D: wartość ADC z czwartego czujnika.
// Zwraca: różnicę kąta do ustawienia (korekta kąta poziomego).
int compareAndSetHorizontalAngles(uint16_t A, uint16_t B, uint16_t C, uint16_t D);

// Deklaracja funkcji, która porównuje wartości z czterech czujników i ustawia odpowiedni kąt pionowy.
// Parametry:
// - uint16_t A: wartość ADC z pierwszego czujnika.
// - uint16_t B: wartość ADC z drugiego czujnika.
// - uint16_t C: wartość ADC z trzeciego czujnika.
// - uint16_t D: wartość ADC z czwartego czujnika.
// Zwraca: różnicę kąta do ustawienia (korekta kąta pionowego).
int compareAndSetVerticalAngles(uint16_t A, uint16_t B, uint16_t C, uint16_t D);

// Deklaracja funkcji, która sprawdza i koryguje kąt poziomy, aby mieścił się w dopuszczalnym zakresie.
// Parametry:
// - int horizontalAngle: kąt poziomy do sprawdzenia i ewentualnej korekty.
// Zwraca: skorygowany kąt poziomy.
int checkHorizontalAngleBounds(int horizontalAngle);

// Deklaracja funkcji, która sprawdza i koryguje kąt pionowy, aby mieścił się w dopuszczalnym zakresie.
// Parametry:
// - int verticalAngle: kąt pionowy do sprawdzenia i ewentualnej korekty.
// Zwraca: skorygowany kąt pionowy.
int checkVerticalAngleBounds(int verticalAngle);

#endif // SOLARPOSITIONINGALGORITHM_H
