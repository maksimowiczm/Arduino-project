#include "headers.h"
#include "Menu.h"

const Adafruit_ILI9341 *const tft = new Adafruit_ILI9341(TFT_CS, TFT_DC);
const Menu *const menu = new Menu(tft);

void setup()
{
    pinMode(BUTTON_PIN0, INPUT_PULLUP);
    pinMode(BUTTON_PIN1, INPUT_PULLUP);
    pinMode(BUTTON_PIN2, INPUT_PULLUP);
    pinMode(BUTTON_PIN3, INPUT_PULLUP);
    pinMode(SPEAKER_PIN, OUTPUT);

    randomSeed(analogRead(0));
    tft->begin();
}

void loop()
{
    menu->Display_menu();

    auto button = menu->Read_button();
    tft->fillScreen(ILI9341_BLACK);
    if (button == 0)
        menu->Start_game();
    else if (button == 1)
        menu->Display_kolory();
    else if (button == 2)
        menu->Display_klawisze();
    else if (button == 3)
        menu->Display_autorzy();
    tft->fillScreen(ILI9341_BLACK);
}