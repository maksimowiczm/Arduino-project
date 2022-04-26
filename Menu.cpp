#include "Menu.h"
#include "Game.h"

Menu::Menu(const Adafruit_ILI9341 *const tft) : tft(tft) {}
Menu::~Menu()
{
	delete[] main_menu_elements;
	delete exit_menu_element;
	delete[] custom_button_pins;
	delete[] custom_button_colors;
	delete[] custom_button_highlights;
	delete[] game_buttons;
}

void Menu::display_string(const int x, const int y, const int size, const int color, const String str) const
{
	tft->setCursor(x, y);
	display_string(size, color, str);
}

void Menu::display_string(const int size, const int color, const String str) const
{
	tft->setTextColor(color);
	tft->setTextSize(size);
	display_string(str);
}

void Menu::display_string(const String str) const
{
	tft->println(str);
}

int Menu::pick_color(const int button_number, int **const b_colors, const bool highlight) const
{
	tft->fillScreen(ILI9341_BLACK);

	int button = 10, // aktualnie wciśnięty przycisk {0, 1, 2, 3}
		colors[3] = {(((31 << 11) & *b_colors[button_number]) >> 11) & 31, ((63 << 5) & *b_colors[button_number]) >> 5, *b_colors[button_number] & 31}, // 5 bit | 6 bit | 5 bit
		color = 0;									   // 0 - red, 1 - green, 2 - blue
	constexpr int color_range_limit[3] = {32, 64, 32}; // maksymalne wartości dla barw rgb 16bit

	const Menu_element **const elements = new const Menu_element *[4]
	{ new const Menu_element("+", BUTTON_HIGHLIGHT0, tft),
		  new const Menu_element("-", BUTTON_HIGHLIGHT3, tft),
		  new const Menu_element("Nastepny", BUTTON_HIGHLIGHT1, tft),
		  new const Menu_element("Zapisz", BUTTON_HIGHLIGHT2, tft) };

	while (button != 2)
	{
		display_string(0, 0, 2, ILI9341_WHITE, "Podaj kod\nkoloru\n" + String(highlight ? "podswietlenia\n" : ""));
		display_string(3, colors[0] << 11 | colors[1] << 5 | colors[2], "red   " + String(colors[0]) + (color == 0 ? "<" : "") + "\n");
		display_string("green " + String(colors[1]) + (color == 1 ? "<" : "") + "\n");
		display_string("blue  " + String(colors[2]) + (color == 2 ? "<" : "") + "\n");
		for (int i = 0; i < 4; i++)
			elements[i]->Display(10, 200 + 30 * i, 3);

		button = Read_button();
		if (button == 0) // +
			colors[color]++;

		else if (button == 1) // przechodzenie między barwami
			color = (color + 1) % 3;

		else if (button == 3) // -
			colors[color]--;

		if (colors[color] <= 0)
			colors[color] += color_range_limit[color];
		if (colors[color] >= color_range_limit[color])
			colors[color] = 0;
		tft->fillScreen(ILI9341_BLACK);
	}

	delete[] elements;
	return colors[0] << 11 | colors[1] << 5 | colors[2];
}

void Menu::Display_kolory()
{
	display_string(0, 0, 2, ILI9341_WHITE, "Wybierz element,\nktory chcesz\nedytowac");
	for (int i = 0; i < 4; i++)
		game_buttons[i]->Display();

	const auto button = Read_button();
	*custom_button_colors[button] = pick_color(button, custom_button_colors, false);
	*custom_button_highlights[button] = pick_color(button, custom_button_highlights, true);

	delay(250);
}

void Menu::Display_klawisze()
{
	display_string(0, 0, 2, ILI9341_WHITE, "Podaj przycisk dla\npodswietlonego\nelementu");
	for (int i = 0; i < 4; i++)
	{
		game_buttons[i]->Highlight();
		*custom_button_pins[i] = button_pins[Read_button()];
		game_buttons[i]->Display();
	}

	delay(250);
}

void Menu::Display_autorzy() const
{
	display_string(0, 0, 3, ILI9341_WHITE, "Autorzy:\n\nMateusz\nMaksimowicz\n\nKlaudia\nMieczkowska");
	exit_menu_element->Display(10, 250, 6);
	Read_button();
}

void Menu::Display_menu() const
{
	display_string(5, 0, 6, ILI9341_WHITE, "Simon");
	for (int i = 1; i <= 4; i++)
		main_menu_elements[i - 1]->Display(0, 40 + 50 * i, 4);
}

void Menu::Start_game() const
{
	Game *game = new Game(game_buttons);
	const int score = game->Play();
	Display_game_over(score);
	delete game;
}

void Menu::Display_game_over(int score) const
{
	tft->fillScreen(ILI9341_BLACK);
	display_string(0, 10, 2, ILI9341_WHITE, "Koniec gry wynik to\n");
	display_string(110, 120, 8, ILI9341_GREEN, String(score));
	exit_menu_element->Display(10, 250, 6);
	Read_button();
}

int Menu::Read_button() const
{
	while (true)
	{
		for (int i = 0; i < 4; i++)
			if (digitalRead(button_pins[i]) == LOW)
				return i;
		delay(10);
	}
}