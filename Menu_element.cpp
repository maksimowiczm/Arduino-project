#include "Menu_element.h"

Menu_element::Menu_element(const char *const text, const int color, const Adafruit_ILI9341 *const tft) : text(text), color(color), tft(tft) {}

Menu_element::~Menu_element()
{
    delete[] text;
}

void Menu_element::Display(const int x, const int y, const int size) const
{
    tft->fillCircle(x + 10, y + 10, 10, color);
    tft->setCursor(x + 30, y);
    tft->setTextColor(color);
    tft->setTextSize(size);
    tft->println(text);
}