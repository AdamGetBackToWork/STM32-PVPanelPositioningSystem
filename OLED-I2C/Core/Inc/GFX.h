/*
 Biblioteka do rysowania znaków na wyświetlaczu
 Jest ona tłumaczeniem na C biblioteki udostępnionej przez Adafruit
 Zawiera ona funkcje do rysowania jednego znaku - char, ciagu charow - stringa
 lub tez do narysowania kwadratu wypelnionego kolorem (czarnym lub bialym)

 Do kazdego rysunku, funkcje pobieraja pozycje jego, kolor, kolor tla oraz rozmiar czcionki
*/

#ifndef INC_GFX_H_
#define INC_GFX_H_

#include <stdint.h>
#include "SSD1306.h"

// Definicje szerokości i wysokości ekranu zgodnie z parametrami SSD1306
#define WIDTH SSD1306_WIDTH
#define HEIGHT SSD1306_HEIGHT

// wiecej opisow ponizszych funkcji w pliku GFX.c
void GFX_draw_char(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y);
void GFX_draw_string(int16_t x, int16_t y, unsigned char * c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y);
void GFX_draw_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

#endif /* INC_GFX_H_ */
