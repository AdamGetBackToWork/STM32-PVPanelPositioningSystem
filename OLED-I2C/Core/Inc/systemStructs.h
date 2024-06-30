/*
 * Autor: Adam Szajgin | s319821 | Politechnika Warszawska | Wydzial Elektroniki i Technik Informacyjnych
 *
 * Opis:
 * Ten plik nagłówkowy zawiera definicje struktur używanych w systemie do
 * przechowywania wyników z ADC oraz stanu systemu. Struktury te są kluczowe
 * dla operacji związanych z pomiarem natężenia światła oraz kontrolą stanu
 * systemu.
 *
 * Zawartość:
 * - ADCResults: Struktura do przechowywania wyników pomiarów z czterech czujników ADC.
 * - SystemState: Struktura do przechowywania bieżącego stanu systemu, w tym stanów
 *   odbioru, pozycjonowania oraz kątów ustawienia.
 */

#ifndef SYSTEMSTRUCTS_H
#define SYSTEMSTRUCTS_H

#include <stdint.h> // Dołączenie nagłówka dla typów całkowitych o ustalonej szerokości (np. uint16_t).

// Struktura przechowująca wyniki z ADC (Analog-to-Digital Converter).
// TU WAZNE - lux, oznacza z laciny swiatlo - light, tez na zarowkach tak pisze!
typedef struct {
    volatile uint16_t lux;  // Wartość natężenia światła z głównego czujnika.
    volatile uint16_t lux1; // Wartość natężenia światła z pierwszego dodatkowego czujnika.
    volatile uint16_t lux2; // Wartość natężenia światła z drugiego dodatkowego czujnika.
    volatile uint16_t lux3; // Wartość natężenia światła z trzeciego dodatkowego czujnika.
} ADCResults;

// Struktura przechowująca stan systemu.
typedef struct {
    char receivingState;     // Stan odbioru danych.
    char positioningState;   // Stan pozycjonowania.
    int stateMemory[2];      // Pamięć stanów systemu (dwa elementy).
    int verticalAngle;       // Kąt pionowy systemu.
    int horizontalAngle;     // Kąt poziomy systemu.
} SystemState;

#endif // SYSTEMSTRUCTS_H
