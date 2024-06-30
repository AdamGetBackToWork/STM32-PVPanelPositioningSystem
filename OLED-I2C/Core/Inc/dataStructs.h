/*
 * Autor: Adam Szajgin | s319821 | Politechnika Warszawska | Wydzial Elektroniki i Technik Informacyjnych
 *
 * Opis:
 * Ten plik nagłówkowy zawiera definicje struktur używanych w systemie do
 * przechowywania danych z czujników oraz kątów ustawienia serwomechanizmów.
 * Struktury te są kluczowe dla operacji związanych z przetwarzaniem danych
 * z czujników i kontrolą położenia serwomechanizmów.
 *
 * Zawartość:
 * - SensorData: Struktura do przechowywania wyników pomiarów z czterech kanałów ADC.
 * - ServoAngles: Struktura do przechowywania bieżących kątów ustawienia serwomechanizmów.
 */

#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#include <stdint.h> // Dołączenie nagłówka dla typów całkowitych o ustalonej szerokości (np. uint16_t).

// Struktura przechowująca wyniki pomiarów z czujników (cztery kanały ADC).
typedef struct {
    uint16_t adcResults[4]; // Tablica wyników ADC (cztery kanały).
} SensorData;

// Struktura przechowująca kąty ustawienia serwomechanizmów.
typedef struct {
    int horizontalAngle; // Kąt poziomy serwomechanizmu.
    int verticalAngle;   // Kąt pionowy serwomechanizmu.
} ServoAngles;

#endif // DATA_STRUCTS_H
