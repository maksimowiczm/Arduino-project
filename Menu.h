#pragma once
#include "headers.h"
#include "Menu_element.h"
#include "Simon_button.h"

class Menu
{
	const Adafruit_ILI9341 *const tft;

	// Domyślne piny przycisków do sterowania w menu
	const int *const button_pins = new const int[4]{BUTTON_PIN0, BUTTON_PIN1, BUTTON_PIN2, BUTTON_PIN3};

	// Elementy menu
	const Menu_element **const main_menu_elements = new const Menu_element *[4]
	{ new const Menu_element("Start", ILI9341_YELLOW, tft), new const Menu_element("Kolory", 0x04BF, tft),
		  new const Menu_element("Klawisze", ILI9341_GREEN, tft), new const Menu_element("Autorzy", ILI9341_RED, tft) };
	Menu_element *exit_menu_element = new Menu_element("Wyjdz", ILI9341_RED, tft);

	// Piny przycisków używanych do sterowania w grze
	int **const custom_button_pins = new int *[4]
	{ new int(BUTTON_PIN0), new int(BUTTON_PIN1), new int(BUTTON_PIN2), new int(BUTTON_PIN3) };

	// Kolory elementów do gry
	int **const custom_button_colors = new int *[4]
	{ new int(BUTTON_COLOR0), new int(BUTTON_COLOR1), new int(BUTTON_COLOR2), new int(BUTTON_COLOR3) };

	// Kolory podświetlenia elementów do gry
	int **const custom_button_highlights = new int *[4]
	{ new int(BUTTON_HIGHLIGHT0), new int(BUTTON_HIGHLIGHT1), new int(BUTTON_HIGHLIGHT2), new int(BUTTON_HIGHLIGHT3) };

	// Elementy gry
	Simon_button **const game_buttons = new Simon_button *[4]
	{ new Simon_button(120, 100, 40, custom_button_colors[0], custom_button_highlights[0], tft, custom_button_pins[0], BUTTON_TONE0),
	  new Simon_button(60, 170, 40, custom_button_colors[1], custom_button_highlights[1], tft, custom_button_pins[1], BUTTON_TONE1),
	  new Simon_button(180, 170, 40, custom_button_colors[2], custom_button_highlights[2], tft, custom_button_pins[2], BUTTON_TONE2),
	  new Simon_button(120, 240, 40, custom_button_colors[3], custom_button_highlights[3], tft, custom_button_pins[3], BUTTON_TONE3) };

	// Wyświetlanie napisu na ekranie
	void display_string(const int x, const int y, const int size, const int color, const String str) const;
	void display_string(const int size, const int color, const String str) const;
	void display_string(const String str) const;

	// Menu wyboru koloru 16 bitowego. Zwraca kolor 16 bitowy
	int pick_color(const int button_number, int **const b_colors, const bool highlight) const;

public:
	Menu(const Adafruit_ILI9341 *const tft);
	~Menu();

	void Display_klawisze(); // Menu edycji sterowania

	void Display_kolory(); // Menu edycji kolorów elementów gry

	void Display_autorzy() const;

	void Display_menu() const; // Menu główne

	void Start_game() const;

	void Display_game_over(const int score) const;

	int Read_button() const; // Zwraca indeks naciśniętego przycisku z button_pins
};