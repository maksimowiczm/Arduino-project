#include "headers.h"
#include "Simon_button.h"

class Game
{
private:
	arx::vector<Simon_button *> sequence;
	Simon_button **game_buttons;

	void level_up_sound() const;
	void game_over_sound() const;

public:
	Game(Simon_button **const game_buttons);
	~Game();

	void Display() const; // Wyświetla wszystkie elementy gry

	void Display_sequence() const; // Wyświetla sekwencję gry

	void Add_to_sequence(); // Dodaje losowy element do sekwencji gry

	bool Compare_sequence_element(Simon_button *button, const int i) const; // Porównuje podany przycisk do i-tego elementu w sekwencji

	Simon_button *Read_button() const; // Zwraca element dla naciśniętego przycisku

	int Play() const;
};