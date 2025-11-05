#include "utils.h"

void clearScreen() {
    display.clearDisplay();
    display.setCursor(0, 0);
}

void loadScene(String text){
    int percent = 0;

    // Load Scene Text
    while (percent < 128) {
        display.println(text);
        display.fillRect(0, 22, percent, 8, SSD1306_WHITE);
        display.drawRect(0, 22, 128, 8, SSD1306_WHITE);
        display.display();
        delay(20);
        clearScreen();
        percent++;
    }
}

void printMenu(MenuOption menuOptions[], int size, String title, int menuSelectedOption) {
    // Get Final Option Index
    int finalOp;
    finalOp = (menuSelectedOption == 0) ? 1 : (menuSelectedOption == size - 1) ? size - 2 : menuSelectedOption;
    int pointerIndex = (menuSelectedOption == 0) ? -1 : (menuSelectedOption == size - 1) ? 1 : 0;

    // Print Menu Options
    display.println(title);
    
    for (int i = -1; i <= 1; i++) {
        int idx = finalOp + i;
        if (idx < 0 || idx >= size) continue;
        String prefix = (i == pointerIndex) ? "   >  " : "      ";
        display.println(prefix + menuOptions[idx].text);
    }

    display.display();
}