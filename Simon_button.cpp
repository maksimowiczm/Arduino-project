#include "Simon_button.h"

Simon_button::Simon_button(const int x, const int y, const int radius, int *const color, int *const highlight_color, const Adafruit_ILI9341 *const tft, int *const button_pin, const int note)
    : x(x), y(y), radius(radius), color(color), highlight_color(highlight_color), tft(tft), button_pin(button_pin), note(note) {}

void Simon_button::Display() const
{
    tft->fillCircle(x, y, radius, *color);
}

void Simon_button::Highlight() const
{
    tft->fillCircle(x, y, radius, *highlight_color);
}

void Simon_button::Highlight_and_tone() const
{
    Highlight();
    tone(SPEAKER_PIN, note);
    delay(500);
    Display();
    noTone(SPEAKER_PIN);
}