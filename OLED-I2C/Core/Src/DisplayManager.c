/*
 * Autor: Adam Szajgin | s319821 | Politechnika Warszawska | Wydzial Elektroniki i Technik Informacyjnych
 *
 * Jest to plik .c dla biblioteki DisplayManager.
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

#include <DisplayManager.h> // Dołączenie pliku nagłówkowego dla biblioteki DisplayManager.
#include "SSD1306.h" // Dołączenie pliku nagłówkowego dla biblioteki SSD1306.
#include <stdint.h> // Dołączenie pliku nagłówkowego dla typów danych całkowitych o ustalonej szerokości.

#define ARRAY_SIZE 5 // Definicja rozmiaru tablicy.

// Funkcja do wyświetlania podstawowych parametrów systemowych na ekranie OLED.
// Parametry:
// - short positioningState: stan pozycjonowania,
// - short receivingState: stan odbierania,
// - double size_x: szerokość znaku,
// - double size_y: wysokość znaku.
void displayParameters(short positioningState, short receivingState, double size_x, double size_y){

    double char_size_x = 2 * size_x; // Obliczenie rozmiaru znaku w osi X.
    double char_size_y = 2 * size_y; // Obliczenie rozmiaru znaku w osi Y.

    // Wyświetlanie parametrów na ekranie OLED.
    GFX_draw_string(0, 54,"Positioning state: ",WHITE, BLACK, size_x, size_y);
    GFX_draw_char(59, 34, positioningState, WHITE, BLACK, char_size_x, char_size_y);
    GFX_draw_string(0, 27,"-------------------",WHITE, BLACK, size_x, size_y);
    GFX_draw_string(0, 20,"Connection status: ",WHITE, BLACK, size_x, size_y);
    GFX_draw_char(59, 1, receivingState, WHITE, BLACK, char_size_x, char_size_y);

    SSD1306_display_repaint(); // Odświeżenie wyświetlacza OLED.

}

// Funkcja do wyświetlania stanu na ekranie OLED.
// Parametry:
// - int stateMemory[]: tablica stanów.
// Zwraca: stan wyświetlany na ekranie.
char displayState(int stateMemory[]){

    char positioningState; // Zmienna przechowująca stan pozycjonowania.

    enum State { // Definicja enuma do przechowywania stanów.
        STATE_1 = '1',
        STATE_2 = '2',
        STATE_3 = '3'
    };

    // Sprawdzenie stanu i przypisanie odpowiedniego znaku dla wyświetlenia na ekranie OLED.
    if (stateMemory[0] == 1 && stateMemory[1] == 0){
        positioningState = STATE_2; // Ustawienie stanu 2.
    }
    else {
        positioningState = STATE_1; // Ustawienie stanu 1.
    }

    return positioningState; // Zwrócenie stanu wyświetlanego na ekranie.
}

// Funkcja do przełączania stanu pozycjonowania.
// Parametry:
// - int stateMemory[2]: tablica przechowująca stany.
void togglePositioningState(int stateMemory[2]) {

    if (stateMemory[0] == 0) {
        stateMemory[0] = 1; // Ustawienie stanu 1.
    } else if (stateMemory[1] == 0) {
        stateMemory[1] = 1; // Ustawienie stanu 2.
    } else {
        stateMemory[0] = 0; // Powrót do stanu 0.
        stateMemory[1] = 0; // Powrót do stanu 0.
    }
}
