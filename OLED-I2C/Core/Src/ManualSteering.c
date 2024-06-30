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

// Dołączenie nagłówków plików nagłówkowych i pliku wykonującego ruchy serwomechanizmów.
#include "ManualSteering.h"
#include "ServoManager.h"

// Funkcja obsługująca sterowanie manualne na podstawie danych otrzymanych przez UART.
void ManualSteering(uint8_t rxData) {
    switch (rxData) {
        // STEROWANIE SERWEM NR. 1 - obracającym system "gora-dol"
        // Jego zakres jest nieograniczony mechanicznie, jedynie przez
        // kąt obrotu serwa - 180°, stąd zakres 0-1800
//        case 65: // Wartość ASCII litery 'A' to 65
//            setAngle(&htim3, TIM_CHANNEL_4, 0, 0); // Ustawienie kąta na 0°
//            break;
//        case 66: // Wartość ASCII litery 'B' to 66
//            setAngle(&htim3, TIM_CHANNEL_4, 450, 0); // Ustawienie kąta na 45°
//            break;
//        case 67: // Wartość ASCII litery 'C' to 67
//            setAngle(&htim3, TIM_CHANNEL_4, 900, 0); // Ustawienie kąta na 90°
//            break;
//        case 68: // Wartość ASCII litery 'D' to 68
//            setAngle(&htim3, TIM_CHANNEL_4, 1350, 0); // Ustawienie kąta na 135°
//            break;
//        case 69: // Wartość ASCII litery 'E' to 69
//            setAngle(&htim3, TIM_CHANNEL_4, 1800, 0); // Ustawienie kąta na 180°
//            break;

    case 65: // Wartość ASCII litery 'A' to 65
        setAngle(&htim3, TIM_CHANNEL_4, 500, 0); // Ustawienie kąta na 0°
        break;
    case 66: // Wartość ASCII litery 'B' to 66
        setAngle(&htim3, TIM_CHANNEL_4, 712, 0); // Ustawienie kąta na 45°
        break;
    case 67: // Wartość ASCII litery 'C' to 67
        setAngle(&htim3, TIM_CHANNEL_4, 924, 0); // Ustawienie kąta na 90°
        break;
    case 68: // Wartość ASCII litery 'D' to 68
        setAngle(&htim3, TIM_CHANNEL_4, 1136, 0); // Ustawienie kąta na 135°
        break;
    case 69: // Wartość ASCII litery 'E' to 69
        setAngle(&htim3, TIM_CHANNEL_4, 1350, 0); // Ustawienie kąta na 180°
        break;


        // STEROWANE SERWEM NR. 2 - obracającym system w poziomie
        // Tutaj oprócz ograniczeń kątu obrotu serwa, dochodzi ograniczenie
        // mechaniczne - obudowa systemu, dlatego zakres jest mniejszy niż 0-180°
        case 70: // Wartość ASCII litery 'F' to 70
            setAngle(&htim3, TIM_CHANNEL_2, 1800, 0); // Ustawienie kąta na 0°
            break;
        case 71: // Wartość ASCII litery 'G' to 71
            setAngle(&htim3, TIM_CHANNEL_2, 1350, 0); // Ustawienie kąta na 45°
            break;
        case 72: // Wartość ASCII litery 'H' to 72
            setAngle(&htim3, TIM_CHANNEL_2, 900, 0); // Ustawienie kąta na 90°
            break;
        case 73: // Wartość ASCII litery 'I' to 73
            setAngle(&htim3, TIM_CHANNEL_2, 450, 0); // Ustawienie kąta na 135°
            break;
        case 74: // Wartość ASCII litery 'J' to 74
            setAngle(&htim3, TIM_CHANNEL_2, 0, 0); // Ustawienie kąta na 180°
            break;

        default:
            // Nieznana komenda, można dodać obsługę błędów lub zignorować
            break;
    }
}
