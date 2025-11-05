// Imports
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ledFunctions.h"

// Data Structures
struct MenuOption {
    String text;
    int optionValue;
};

// Pins
#define LDR 2
#define LED 21
#define SDA 3
#define SCL 4

#define UP 8
#define DOWN 6
#define RIGHT 7
#define LEFT 5

// Oled Config
#define HEIGHT 32
#define WIDTH 128
Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, -1);

// Global Variables
int ldrValue = 0;
bool ledState = false;
int threshold = 2750;
int selectedOption = 0;

// Menu Options
MenuOption mainMenuOptions[] = {
    {"LED", 0},
    {"LIGHT", 1},
    {"GAMES", 2},
    {"EXIT", 3}
};

MenuOption ledMenuOptions[] = {
    {"LED ON", 1},
    {"LED OFF", 2},
    {"BLINK LED", 3},
};

MenuOption lightMenuOptions[] = {
    {"ACTUAL DAY STATE", 1},
    {"LIGHT INTENSITY", 2},
    {"EXIT", 3}
};

MenuOption gameMenuOptions[] = {
    {"TIC TAC TOE", 1},
    {"SNAKE", 2},
    {"EXIT", 3}
};



// Setup
void setup() {
    // Serial
    Serial.begin(115200);
    delay(1000);
    Serial.println("Started mini console");

    // Pin init
    pinMode(LDR, INPUT);
    pinMode(LED, OUTPUT);
    pinMode(UP, INPUT_PULLUP);
    pinMode(DOWN, INPUT_PULLUP);
    pinMode(RIGHT, INPUT_PULLUP);
    pinMode(LEFT, INPUT_PULLUP);

    // Oled init
    Wire.begin(SDA, SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("Screen init failed"));
        while (1);
    }

    // Display Init
    initDisplay();
}

void loop() {
    clearScreen();
    printMenu(mainMenuOptions, sizeof(mainMenuOptions)/sizeof(mainMenuOptions[0]), "MAIN MENU:");

    // Handle Main Menu Navigation
    if (digitalRead(UP) == LOW) {
        selectedOption--;
        if (selectedOption < 0) {
            selectedOption = 0;
        }
        delay(200);
    } else if (digitalRead(DOWN) == LOW) {
        selectedOption++;
        if (selectedOption >= sizeof(mainMenuOptions)/sizeof(mainMenuOptions[0])) {
            selectedOption = sizeof(mainMenuOptions)/sizeof(mainMenuOptions[0]) - 1;
        }
        delay(200);
    } else if (digitalRead(RIGHT) == LOW) {
        switch (selectedOption) {
            case 0: ledMenu(); break;
            /* case 1: lightMenu(); break;
            case 2: gameMenu(); break;
            case 3: exitProgram(); break; */
        }
    }
}

void initDisplay() {
    clearScreen();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    loadScene("Starting mini console");
}

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

void printMenu(MenuOption menuOptions[], int size, String title) {
    // Get Final Option Index
    int finalOp;
    finalOp = (selectedOption == 0) ? 1 : (selectedOption == size - 1) ? size - 2 : selectedOption;
    int pointerIndex = (selectedOption == 0) ? -1 : (selectedOption == size - 1) ? 1 : 0;

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