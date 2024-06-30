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

#include <stdint.h> // Dołączenie nagłówka dla typów całkowitych o ustalonej szerokości (np. uint8_t, uint32_t).
#include <SolarPositioningAlgorithm.h> // Dołączenie nagłówka dla algorytmu pozycjonowania słonecznego.

// Funkcja zaokrąglająca wartość do najbliższej setki za pomocą operatora modulo.
uint16_t roundToHundred(uint16_t value) {
    uint16_t remainder = value % 100;
    if (remainder < 50) {
        return value - remainder; // Zaokrąglanie w dół
    } else {
        return value + (100 - remainder); // Zaokrąglanie w górę
    }
}
// Funkcja porównująca wartości z czterech czujników i ustawiająca odpowiedni kąt poziomy.
int compareAndSetHorizontalAngles(uint16_t A, uint16_t B, uint16_t C, uint16_t D) {
    int horizontalAngle = 0;

    A = roundToHundred(A);
    B = roundToHundred(B);
    C = roundToHundred(C);
    D = roundToHundred(D);

    // Porównanie wartości z czujników A, B, C i D w celu ustawienia kąta poziomego.
    if (A > B && C > D) {
        horizontalAngle = 100;
    } else if (A < B && C < D){
        horizontalAngle = -100;
    } else {
        horizontalAngle = 0;
    }

    return horizontalAngle; // Zwrócenie kąta poziomego.
}

// Funkcja porównująca wartości z czterech czujników i ustawiająca odpowiedni kąt pionowy.
int compareAndSetVerticalAngles(uint16_t A, uint16_t B, uint16_t C, uint16_t D) {
    int verticalAngle = 0;

    A = roundToHundred(A);
    B = roundToHundred(B);
    C = roundToHundred(C);
    D = roundToHundred(D);

    // Porównanie wartości z czujników A, B, C i D w celu ustawienia kąta pionowego.
    if (A > C && B > D) {
        verticalAngle = -100;
    } else if (A < C && B < D){
        verticalAngle = 100;
    } else {
        verticalAngle = 0;
    }

    return verticalAngle; // Zwrócenie kąta pionowego.
}

// Funkcja sprawdzająca i korygująca kąt poziomy, aby mieścił się w dopuszczalnym zakresie.
int checkHorizontalAngleBounds(int horizontalAngle){
    // Sprawdzenie, czy kąt poziomy przekracza dopuszczalne granice.
    if(horizontalAngle < 0){
        horizontalAngle = 0; // Korekta kąta na minimalną wartość.
    }
    if(horizontalAngle > 1800){
        horizontalAngle = 1800; // Korekta kąta na maksymalną wartość.
    }

    return horizontalAngle; // Zwrócenie skorygowanego kąta poziomego.
}

// Funkcja sprawdzająca i korygująca kąt pionowy, aby mieścił się w dopuszczalnym zakresie.
int checkVerticalAngleBounds(int verticalAngle){
    // Sprawdzenie, czy kąt pionowy przekracza dopuszczalne granice.
    if(verticalAngle < 500){
        verticalAngle = 500; // Korekta kąta na minimalną wartość.
    }
    if(verticalAngle > 1350){
        verticalAngle = 1350; // Korekta kąta na maksymalną wartość.
    }

    return verticalAngle; // Zwrócenie skorygowanego kąta pionowego.
}
