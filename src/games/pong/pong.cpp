#include "src/games/pong/pong.h"

// Dimensions of the game area
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// Symbols for the ball and paddles
#define BALL_CHAR (char)254
#define PADDLE_CHAR (char)219
#define CELL_SIZE 4

// Global variables
int ballX = SCREEN_WIDTH / 2;
int ballY = SCREEN_HEIGHT / 2;
int ballVelocityX = 1;
int ballVelocityY = 1;
int playerPaddleY = SCREEN_HEIGHT / 2 - 10;
int aiPaddleY = SCREEN_HEIGHT / 2 - 10;
int playerScore = 0;
int aiScore = 0;
int winner = 0; // 0: No winner, 1: Player, 2: AI
int aiDifficulty = -1; // 1: Easy, 2: Medium, 3: Hard

// Pong Difficulty Menu Options
MenuOption pongDifficultyOptions[3] = {
    {"Easy"},
    {"Medium"},
    {"Hard"}
};

// User input task handler
TaskHandle_t pongInputTaskHandle = NULL
void TaskPongUserInput(void *pvParameters);

void playPong() {
    resetPong();
    selectPongDifficulty();

    // Start user input task
    xTaskCreate(TaskPongUserInput, "PongUserInput", 2048, NULL, 1, &pongInputTaskHandle);

    while (winner == 0) {
        // Update score
        if (ballX <= 0) {
            aiScore++;
            resetPong();
        } else if (ballX >= SCREEN_WIDTH - 1) {
            playerScore++;
            resetBall();
        }
        
        // Check ball bounces
        if (ballY <= 0 || ballY >= SCREEN_HEIGHT / CELL_SIZE - 1) {
            ballVelocityY = -ballVelocityY; // Bounce off top/bottom
        }
        if ((ballX == 1 && ballY == playerPaddleY) || (ballX == SCREEN_WIDTH / CELL_SIZE - 2 && ballY == aiPaddleY)) {
            ballVelocityX = -ballVelocityX; // Bounce off paddles
        }

        // Move ball
        ballX += ballVelocityX;
        ballY += ballVelocityY;

        aiMove(ballY, ballX, aiPaddleY, aiDifficulty);

        // Update display
        updateDisplay(ballX, ballY, playerPaddleY, aiPaddleY, playerScore, aiScore);

        // Check for game over
        winner = (playerScore >= 5) ? 1 : (aiScore >= 5) ? 2 : 0;

        delay(200);
    }

    // Stop user input task
    if (pongInputTaskHandle != NULL) {
        vTaskDelete(pongInputTaskHandle);
        pongInputTaskHandle = NULL;
    }
}

void updateDisplay(int ballX, int ballY, int playerPaddleY, int aiPaddleY, int playerScore, int aiScore) {
    clearScreen();

    // Draw ball
    display.setCursor(ballX, ballY);
    display.write(BALL_CHAR);

    // Draw player paddle
    for (int i = 0; i < 4; i++) {
        display.setCursor(0, playerPaddleY + i);
        display.write(PADDLE_CHAR);
    }

    // Draw AI paddle
    for (int i = 0; i < 4; i++) {
        display.setCursor(SCREEN_WIDTH - 1, aiPaddleY + i);
        display.write(PADDLE_CHAR);
    }

    // Draw scores
    display.setCursor(SCREEN_WIDTH / 4, 0);
    display.print(String(playerScore));
    display.setCursor(3 * SCREEN_WIDTH / 4 - 20, 0);
    display.print(String(aiScore));

    display.display();
}

void aiMove(int ballY, int ballX, int aiPaddleY, int aiDifficulty) {
    int reactionThreshold;
    switch (aiDifficulty) {
        case 1: reactionThreshold = 4; break; // Easy
        case 2: reactionThreshold = 2; break; // Medium
        case 3: reactionThreshold = 1; break; // Hard
        default: reactionThreshold = 4; break;
    }

    if (ballX >= SCREEN_WIDTH / 2) { // Only move when ball is on AI side
        if (ballY < aiPaddleY && abs(ballY - aiPaddleY) > reactionThreshold) {
            aiPaddleY--;
        } else if (ballY > aiPaddleY + 3 && abs(ballY - (aiPaddleY + 3)) > reactionThreshold) {
            aiPaddleY++;
        }
    }
}

void TaskPongUserInput(void *pvParameters) {
    while (true) {
        if (digitalRead(UP) == LOW && playerPaddleY > 0) {
            playerPaddleY--;
        } else if (digitalRead(DOWN) == LOW && playerPaddleY < SCREEN_HEIGHT / CELL_SIZE - 4) {
            playerPaddleY++;
        }
        delay(200);
    }
}

void resetBall() {
    ballX = SCREEN_WIDTH / 2;
    ballY = SCREEN_HEIGHT / 2;
    ballVelocityX = (ballVelocityX > 0) ? -1 : 1; // Change direction
    ballVelocityY = (ballVelocityY > 0) ? 1 : -1; // Keep same vertical direction
}

void selectPongDifficulty() {
    while (aiDifficulty == -1) {
        clearScreen();
        int pongMenuSelectedOption = 0;

        if (digitalRead(UP) == LOW && pongMenuSelectedOption > 0) {
            pongMenuSelectedOption--;
            delay(200);
        } else if (digitalRead(DOWN) == LOW && pongMenuSelectedOption < 2) {
            pongMenuSelectedOption++;
            delay(200);
        } else if (digitalRead(RIGHT) == LOW) {
            aiDifficulty = (pongMenuSelectedOption + 1);
        }

        printMenu(pongDifficultyOptions, 3, "Select AI Difficulty", pongMenuSelectedOption);
        delay(200);
    }
}

void resetPong() {
    winner = 0;
    ballX = SCREEN_WIDTH / 2;
    ballY = SCREEN_HEIGHT / 2;
    ballVelocityX = 1;
    ballVelocityY = 1;
    playerPaddleY = SCREEN_HEIGHT / 2 - 10;
    aiPaddleY = SCREEN_HEIGHT / 2 - 10;
    playerScore = 0;
    aiScore = 0;
    aiDifficulty = -1;
}