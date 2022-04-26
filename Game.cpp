#include "Game.h"
Game::Game(Simon_button **const game_buttons)	: game_buttons(game_buttons) {}

Game::~Game() {}

void Game::level_up_sound() const
{
	tone(SPEAKER_PIN, NOTE_C3);
	delay(250);
	tone(SPEAKER_PIN, NOTE_E3);
	delay(250);
	tone(SPEAKER_PIN, NOTE_G3);
	delay(500);
	noTone(SPEAKER_PIN);
}

void Game::game_over_sound() const
{
	tone(SPEAKER_PIN, NOTE_CS3);
	delay(400);
	tone(SPEAKER_PIN, NOTE_C3);
	delay(400);
	tone(SPEAKER_PIN, NOTE_B2);
	delay(400);
	tone(SPEAKER_PIN, NOTE_AS2);
	delay(400);
	noTone(SPEAKER_PIN);
}

void Game::Display() const
{
	for (int i = 0; i < 4; i++)
		game_buttons[i]->Display();
}

void Game::Display_sequence() const
{
	for (const auto b : sequence)
	{
		delay(250);
		b->Highlight_and_tone();
	}
}

void Game::Add_to_sequence()
{
	sequence.push_back(game_buttons[random(4)]);
}

bool Game::Compare_sequence_element(Simon_button *button, const int i) const
{
	if (button != sequence[i])
		return false;
	return true;
}

Simon_button *Game::Read_button() const
{
	while (1)
	{
		for (int i = 0; i < 4; i++)
			if (digitalRead(*game_buttons[i]->button_pin) == LOW)
				return game_buttons[i];
		delay(1);
	}
}

int Game::Play() const
{
	Display();
	int game_length = 1;
	while (1)
	{
		Add_to_sequence();
		Display_sequence();

		for (int i = 0; i < game_length; i++)
		{
			const auto button = Read_button();
			button->Highlight_and_tone();

			if (!Compare_sequence_element(button, i))
			{
				game_over_sound();
				return game_length - 1;
			}
		}

		level_up_sound();
		game_length++;
	}
}