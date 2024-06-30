/*
 * Autor: Adam Szajgin | s319821 | Politechnika Warszawska | Wydzial Elektroniki i Technik Informacyjnych
 *
 * Ta jednofunkcyjna biblioteka służy do obsługi sterowania manualnego systemem
 * w drugiej opcji sterowania (drugiej po automatycznej).
 *
 * Pobiera ona informacje z przerwania UART-u i pozycjonuje system względem
 * wejścia z telefonu. Obsługa tego mechanizmu sterowania następuje przez UART,
 * przesyłając dane od modułu bluetooth HC-06. Z telefonu przez bluetooth przychodzi
 * zakodowana w ASCII litera, którą UART przekazuje do Nucleo.
 *
 * Ta litera jest właśnie w zmiennej rxData.
*/

// TO JEJ PLIK NAGŁÓWKOWY

#ifndef INC_MANUALSTEERING_H_
#define INC_MANUALSTEERING_H_

#include <stdint.h> // Dołączenie nagłówka dla typów całkowitych o ustalonej szerokości (np. uint8_t).

// Deklaracja funkcji obsługującej sterowanie manualne na podstawie danych otrzymanych przez UART.
// Parametry:
// - uint8_t rxData: dane otrzymane przez UART.
void ManualSteering(uint8_t rxData);

#endif /* INC_MANUALSTEERING_H_ */
