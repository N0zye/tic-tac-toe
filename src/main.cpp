#include "tris.h"

#define PLATFORM_WINDOWS

int WinMain() {
    
    InitWindow(600, 600, "Tic Tac Toe");

    mainLoop(true);

    CloseWindow();
    return 0;
}