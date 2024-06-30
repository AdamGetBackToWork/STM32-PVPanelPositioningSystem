/*
 * Autor: Adam Szajgin | s319821 | Politechnika Warszawska | Wydzial Elektroniki i Technik Informacyjnych
 *
 * Jest to plik nagłówkowy dla biblioteki DisplayManager.
 * Ma on na celu przygotowanie pełnego zestawu funkcji do
 * łatwej obsługi wyświetlacza OLED firmy AdaFruit.
 *
 * W tej bibliotece dołączam biblioteki stworzone przez AdaFruit,
 * przeznaczone specjalnie dla wyświetlacza OLED o rozdzielczości 128x64 pikseli.
 *
 * Używane tutaj funkcje pochodzą głównie z dwóch bibliotek: jednej GFX i
 * drugiej SSD1306, z czego ta druga jest zawarta w GFX. Biblioteka GFX
 * zawiera wszystkie niezbędne funkcje "rysujące" - te, które
 * odpowiadają za adresowanie i aktywowanie niezbędnych pikseli.
 * Biblioteka SSD1306 jest do wszystkiego innego... inicjalizacji,
 * wyświetlania, wysyłania i innych.
*/


#ifndef _DisplayManager_H_
#define _DisplayManager_H_

#include "GFX.h" // Dołączenie nagłówka dla funkcji z biblioteki GFX.

// Deklaracja funkcji do wyświetlania parametrów na ekranie OLED.
// Parametry:
// - short positioningState: stan pozycjonowania,
// - short receivingState: stan odbierania,
// - double size_x: rozmiar w kierunku X,
// - double size_y: rozmiar w kierunku Y.
void displayParameters(short positioningState, short receivingState, double size_x, double size_y);

// Deklaracja funkcji do wyświetlania stanu na ekranie OLED.
// Parametry:
// - int stateMemory[]: tablica stanów.
// Zwraca: stan wyświetlany na ekranie.
char displayState(int stateMemory[]);

// Deklaracja funkcji do przełączania stanu pozycjonowania.
// Parametry:
// - int stateMemory[2]: tablica stanów.
void togglePositioningState(int stateMemory[2]);

#endif // __DisplayManager_H_
