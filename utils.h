#ifndef UTILS_H
#define UTILS_H

#include "config.h"

void clearScreen();
void loadScene(String scene);
void printMenu(MenuOption menuOptions[], int numOptions, String title, int menuSelectedOption);

#endif