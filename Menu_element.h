#include "headers.h"

class Menu_element
{
private:
    const Adafruit_ILI9341 *const tft;
    const char *const text;
    const int color;

public:
    Menu_element(const char *const text, const int color, const Adafruit_ILI9341 *const tft);
    ~Menu_element();

    void Display(const int x, const int y, const int size) const; // Wyświetla element menu na ekranie
};