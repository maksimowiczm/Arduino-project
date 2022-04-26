#pragma once
#include "headers.h"

class Simon_button
{
private:
	const Adafruit_ILI9341 *const tft;
	const int x; // Współrzędna elementu na ekranie
	const int y;
	const int radius; // Promień koła
	int *const color; // Wskaźniki na kolory wyświetlania
	int *const highlight_color;
	const int note; // Dźwięk podświetlenia

public:
	int *const button_pin; // Wskaźnik na pin przycisku

	Simon_button(const int x, const int y, const int radius, int *const color, int *const highlight_color, const Adafruit_ILI9341 *const tft, int *const button_pin, const int note);

	void Display() const;
	void Highlight() const;
	void Highlight_and_tone() const;
};