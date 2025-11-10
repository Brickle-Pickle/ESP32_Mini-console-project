# How to upload a game
To upload a new game to the MiniConsole, follow these steps:

1. **Create Game Folder**: Create a new folder in the `MiniConsole\src\games\` directory. The folder name should be the same as the game name.
2. **Add Source Files**: Inside the new game folder, add the necessary source files for your game. At a minimum, you should have:
   - `yourGameName.cpp`: The main implementation file for your game.
   - `yourGameName.h`: The header file declaring functions and variables used in your game.
3. **Data Files**: If your game requires any data files (e.g., trivia questions, leaderboard scores), create a file named `purpose.xx` inside the game folder. This file should contain a brief description of the purpose of the data file.
Replace `xx` with the appropriate file extension for your data file (e.g., `sn` for snake leaderboard, `rt` for reaction time game).
4. **Add Game to `config.cpp`**: Open the `config.cpp` file in the `MiniConsole\src\os` directory. Change gameMenuOptions to include your game.
5. **Add Game to `gamesFunctions.cpp`**: Open the `gamesFunctions.cpp` file in the `MiniConsole\src\games` directory. In the function `gameMenuController`, add in the switch statement a case for your game in the same position as you added it to `config.cpp`. Also you should add the game .h file in the header as (in gamesFunctions.cpp)
    ```c++ 
        #include "src/games/yourGameName/yourGameName.h"
    ```
6. **Add Game to `yourGameName.h`**: Open the `yourGameName.h` file in the new game folder. This file must contain at least the following function prototype:
   - `void playYourGameName();`
   - Every else function used in your game.
7. **Add Game to `yourGameName.cpp`**: Open the `yourGameName.cpp` file in the new game folder. In the function `playYourGameName`, add the game logic.
8. **Upload the Firmware**: Open `MiniConsole.ino` in the Arduino IDE, select the appropriate board and port, then build and upload the firmware to the board.
9. **Test Your Game**: After uploading, test your game on the MiniConsole to ensure it functions as expected.
10. **Update Documentation**: Optionally, update the `README.md` file to include information about your new game, including controls, gameplay, and any special features.

By following these steps, you can easily add a new game to the MiniConsole and share it with others.