#ifndef LED_FUNCTIONS_H
#define LED_FUNCTIONS_H

#include <Arduino.h>

// LED Menu Options
struct MenuOption {
    String text;
    int optionValue;
};

// Extern declarations
extern MenuOption ledMenuOptions[];
extern void clearScreen();
extern void printMenu(MenuOption menuOptions[], int numOptions, String title);

// LED Menu Functions
void turnLedOn(bool &ledState, int ledPin);
void turnLedOff(bool &ledState, int ledPin);
void blinkLed(bool &ledState, int ledPin);
void ledMenuController(int selectedOption, bool &ledState, int ledPin);
void ledMenu(int &ledState, int ledPin);

#endif