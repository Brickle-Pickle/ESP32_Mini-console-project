#include "ledFunctions.h"
#include <Arduino.h>

// Internal Variable
TaskHandle_t blinkLedTaskHandle = NULL;

// Task Declaration
void TaskBlinkLed(void *pvParameters);

void ledMenu(int &ledState, int ledPin) {
    bool exit = false;
    int ledSelectedOption = 0;

    while (!exit) {
        clearScreen();
        printMenu(ledMenuOptions, sizeof(ledMenuOptions)/sizeof(ledMenuOptions[0]), "LED MENU:");

        if (digitalRead(UP) == LOW) {
            ledSelectedOption--;
            if (ledSelectedOption < 0)  ledSelectedOption = 0; 
            delay(200);
        } else if (digitalRead(DOWN) == LOW) {
            ledSelectedOption++;
            if (ledSelectedOption >= sizeof(ledMenuOptions)/sizeof(ledMenuOptions[0])) {
                ledSelectedOption = sizeof(ledMenuOptions)/sizeof(ledMenuOptions[0]) - 1;
            }
            delay(200);
        } else if (digitalRead(LEFT) == LOW) {
            exit = true;
            delay(200);
        } else if (digitalRead(RIGHT) == LOW) {
            ledMenuController(ledSelectedOption, ledState, ledPin);
            delay(200);
        }
    }
}

void ledMenuController(int selectedOption, bool &ledState, int ledPin) {
    switch (selectedOption) {
        case 0: turnLedOn(ledState, ledPin); break;
        case 1: turnLedOff(ledState, ledPin); break;
        case 2: blinkLed(ledState, ledPin); break;
    }
}

void turnLedOn(bool &ledState, int ledPin) {
    if (blinkLedTaskHandle != NULL) {
        vTaskDelete(blinkLedTaskHandle);
        blinkLedTaskHandle = NULL;
    }
    if (!ledState) digitalWrite(ledPin, HIGH);
    ledState = true;
}

void turnLedOff(bool &ledState, int ledPin) {
    if (blinkLedTaskHandle != NULL) {
        vTaskDelete(blinkLedTaskHandle);
        blinkLedTaskHandle = NULL;
    }
    if (ledState) digitalWrite(ledPin, LOW);
    ledState = false;
}

void blinkLed(bool &ledState, int ledPin) {
    if (blinkLedTaskHandle == NULL) {
       xTaskCreate(
            TaskBlinkLed,
            "BlinkLedTask",
            1000,
            (void*)&ledPin,
            1,
            &blinkLedTaskHandle
        );
    }
}

void TaskBlinkLed(void *pvParameters) {
    int ledPin = *((int*)pvParameters);
    while (true) {
        digitalWrite(ledPin, HIGH);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        digitalWrite(ledPin, LOW);
        vTaskDelay(1500 / portTICK_PERIOD_MS);
    }
}