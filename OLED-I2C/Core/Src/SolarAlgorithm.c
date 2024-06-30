///*
// * TEN PLIK JEST OPCJA DO ALTERNATYWNEGO STEROWANIA SERWOMECHANIZMAMI W ODNIESIENIU DO POZIOMOW NATEZENIA SWIATLA
// *
// * ON NIE JEST OBECNIE W UZYCIU, PROSZE GO ZIGNOROWAC!!
// *
// */
//
//#include <SolarPositioningAlgorithm.h> // Dołączenie nagłówka dla algorytmu pozycjonowania słonecznego.
//#include "SolarAlgorithm.h"            // Dołączenie nagłówka dla algorytmu słonecznego (możliwe, że ten plik zawiera dodatkowe definicje lub funkcje związane z algorytmem).
//
//int solarPositioningAlgorithmHorizontal(int AdcResults[], int horizontalAngle){
//    // Deklaracja zmiennych lokalnych.
//    int temp1 = 0;             // Tymczasowa zmienna do przechowywania korekty kąta.
//    uint16_t lux = 0;          // Zmienna do przechowywania wartości ADC z pierwszego czujnika.
//    uint16_t lux1 = 0;         // Zmienna do przechowywania wartości ADC z drugiego czujnika.
//    uint16_t lux2 = 0;         // Zmienna do przechowywania wartości ADC z trzeciego czujnika.
//    uint16_t lux3 = 0;         // Zmienna do przechowywania wartości ADC z czwartego czujnika.
//
//    // Przypisanie wartości z tablicy wyników ADC do zmiennych.
//    lux = (uint16_t)AdcResults[0];
//    lux1 = (uint16_t)AdcResults[1];
//    lux2 = (uint16_t)AdcResults[2];
//    lux3 = (uint16_t)AdcResults[3];
//
//    // Porównanie wartości ADC i ustawienie kąta poziomego.
//    temp1 = compareAndSetHorizontalAngles(lux, lux1, lux2, lux3);
//
//    // Korekta kąta poziomego na podstawie wyniku porównania.
//    horizontalAngle += temp1;
//    horizontalAngle = checkHorizontalAngleBounds(horizontalAngle); // Sprawdzenie i korekta kąta, aby mieścił się w dopuszczalnym zakresie.
//
//    // Ustawienie nowego kąta poziomego za pomocą funkcji set_ang.
//    set_ang(&htim3, TIM_CHANNEL_2, horizontalAngle, 0);
//
//    // Opóźnienie nieblokujące.
//    //nonBlockingDelay(100);
//
//    return horizontalAngle; // Zwrócenie nowego kąta poziomego.
//}
//
//int solarPositioningAlgorithmVertical(int AdcResults[], int verticalAngle){
//    // Deklaracja zmiennych lokalnych.
//    int temp2 = 0;             // Tymczasowa zmienna do przechowywania korekty kąta.
//    uint16_t lux = 0;          // Zmienna do przechowywania wartości ADC z pierwszego czujnika.
//    uint16_t lux1 = 0;         // Zmienna do przechowywania wartości ADC z drugiego czujnika.
//    uint16_t lux2 = 0;         // Zmienna do przechowywania wartości ADC z trzeciego czujnika.
//    uint16_t lux3 = 0;         // Zmienna do przechowywania wartości ADC z czwartego czujnika.
//
//    // Przypisanie wartości z tablicy wyników ADC do zmiennych.
//    lux = (uint16_t)AdcResults[0];
//    lux1 = (uint16_t)AdcResults[1];
//    lux2 = (uint16_t)AdcResults[2];
//    lux3 = (uint16_t)AdcResults[3];
//
//    // Porównanie wartości ADC i ustawienie kąta pionowego.
//    temp2 = compareAndSetVerticalAngles(lux, lux1, lux2, lux3);
//
//    // Korekta kąta pionowego na podstawie wyniku porównania.
//    verticalAngle += temp2;
//    verticalAngle = checkVerticalAngleBounds(verticalAngle); // Sprawdzenie i korekta kąta, aby mieścił się w dopuszczalnym zakresie.
//
//    // Ustawienie nowego kąta pionowego za pomocą funkcji set_ang.
//    set_ang(&htim3, TIM_CHANNEL_4, verticalAngle, 0);
//
//    // Opóźnienie nieblokujące.
//    //nonBlockingDelay(100);
//
//    return verticalAngle; // Zwrócenie nowego kąta pionowego.
//}
