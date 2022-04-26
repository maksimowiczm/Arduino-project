#pragma once
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "ArxContainer.h"
#include "pitches.h"

// Piny
#define TFT_DC 9
#define TFT_CS 10
#define SPEAKER_PIN 6
#define BUTTON_PIN0 2
#define BUTTON_PIN1 4
#define BUTTON_PIN2 7
#define BUTTON_PIN3 8

// Domyślne opcje gry
#define BUTTON_TONE0 NOTE_A3
#define BUTTON_TONE1 NOTE_B3
#define BUTTON_TONE2 NOTE_CS4
#define BUTTON_TONE3 NOTE_D4
#define BUTTON_COLOR0 0xAD40
#define BUTTON_COLOR1 0x014E
#define BUTTON_COLOR2 0x04A0
#define BUTTON_COLOR3 0xA000
#define BUTTON_HIGHLIGHT0 ILI9341_YELLOW
#define BUTTON_HIGHLIGHT1 0x04BF
#define BUTTON_HIGHLIGHT2 ILI9341_GREEN
#define BUTTON_HIGHLIGHT3 ILI9341_RED