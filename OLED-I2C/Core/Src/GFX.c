/*
 Biblioteka do rysowania znaków na wyświetlaczu
 Jest ona tłumaczeniem na C biblioteki udostępnionej przez Adafruit
 Zawiera ona funkcje do rysowania jednego znaku - char, ciagu charow - stringa
 lub tez do narysowania kwadratu wypelnionego kolorem (czarnym lub bialym)

 Do kazdego rysunku, funkcje pobieraja pozycje jego, kolor, kolor tla oraz rozmiar czcionki
*/

#include "GFX.h"
#include "font_ascii_5x7.h"

/**************************************************************************/
/*!
   @brief   Rysowanie pojedynczego znaku
    @param    x      Współrzędna x lewego dolnego rogu znaku
    @param    y      Współrzędna y lewego dolnego rogu znaku
    @param    c      8-bitowy indeks znaku w czcionce (prawdopodobnie ASCII)
    @param    color  16-bitowy kolor (5-6-5) do narysowania znaku
    @param    bg     16-bitowy kolor (5-6-5) tła znaku (jeśli taki sam jak kolor, brak tła)
    @param    size_x Powiększenie czcionki w osi X, 1 oznacza 'oryginalny' rozmiar
    @param    size_y Powiększenie czcionki w osi Y, 1 oznacza 'oryginalny' rozmiar
*/
/**************************************************************************/
void GFX_draw_char(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y)
{
	// Zmienne iteracyjne i od iterate
    int8_t i, j;
    uint8_t line;

    // Jeśli znak wykracza poza obszar wyświetlacza, funkcja nic nie robi
    if((x >= WIDTH) || (y >= HEIGHT) || ((x + 6 * size_x - 1) < 0) || ((y + 8 * size_y - 1) < 0))
    {
        return;
    }

    // Iteracja przez 5 kolumn bitmapy znaku
    for(i = 0; i < 5; i++)
    {
        line = (*(const unsigned char *)(&font[c * 5 + i])); // Pobranie kolumny bitmapy
        for(j = 7; j >= 0; j--, line >>= 1) // Iteracja przez 8 pikseli w kolumnie
        {
            if(line & 1) // Jeśli bit jest ustawiony, rysujemy piksel
            {
                if(size_x == 1 && size_y == 1)
                {
                    SSD1306_draw_pixel(x + i, y + j, color);
                }
                else
                {
                    GFX_draw_fill_rect(x + i * size_x, y + j * size_y, size_x, size_y, color);
                }
            }
            else if(bg != color) // Jeśli tło nie jest takie samo jak kolor, rysujemy tło
            {
                if(size_x == 1 && size_y == 1)
                {
                    SSD1306_draw_pixel(x + i, y + j, bg);
                }
                else
                {
                    GFX_draw_fill_rect(x + i * size_x, y + j * size_y, size_x, size_y, bg);
                }
            }
        }
    }

    // Jeśli tło nie jest takie samo jak kolor, rysujemy pionową linię w ostatniej kolumnie
    if(bg != color)
    {
        if(size_x == 1 && size_y == 1)
        {
            SSD1306_draw_fast_vline(x + 5, y, 8, bg);
        }
        else
        {
            GFX_draw_fill_rect(x + 5 * size_x, y, size_x, 8 * size_y, bg);
        }
    }
}

/**************************************************************************/
/*!
   @brief   Rysowanie ciągu znaków
    @param    x      Współrzędna x lewego dolnego rogu pierwszego znaku
    @param    y      Współrzędna y lewego dolnego rogu pierwszego znaku
    @param    c      Ciąg znaków (prawdopodobnie ASCII)
    @param    color  16-bitowy kolor (5-6-5) do narysowania znaków
    @param    bg     16-bitowy kolor (5-6-5) tła znaków (jeśli taki sam jak kolor, brak tła)
    @param    size_x Powiększenie czcionki w osi X, 1 oznacza 'oryginalny' rozmiar
    @param    size_y Powiększenie czcionki w osi Y, 1 oznacza 'oryginalny' rozmiar
*/
/**************************************************************************/
void GFX_draw_string(int16_t x, int16_t y, unsigned char * c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y)
{
    uint8_t offset = 0;
    // Iteracja przez każdy znak w ciągu znaków
    while(*c)
    {
        GFX_draw_char(x+offset, y, *c, color, bg, size_x, size_y); // Rysowanie pojedynczego znaku
        offset += (5 + 2) * size_x; // Przesunięcie do następnego znaku (5 pikseli na znak + 1 piksel odstępu)
        c++;
    }
}

/**************************************************************************/
/*!
   @brief    Wypełnienie prostokąta jednym kolorem. Można nadpisać w podklasach!
    @param    x      Współrzędna x lewego górnego rogu prostokąta
    @param    y      Współrzędna y lewego górnego rogu prostokąta
    @param    w      Szerokość prostokąta w pikselach
    @param    h      Wysokość prostokąta w pikselach
    @param    color  16-bitowy kolor (5-6-5) do wypełnienia prostokąta
*/
/**************************************************************************/
void GFX_draw_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    // Iteracja przez każdy piksel w szerokości prostokąta
    for(int16_t i = x; i < x + w; i++)
    {
        SSD1306_draw_fast_vline(i, y, h, color); // Rysowanie pionowej linii o wysokości 'h' i kolorze 'color'
    }
}
