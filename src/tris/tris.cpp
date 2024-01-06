#include "tris.h"

void mainLoop(bool botIsEnabled) { // bot plays always as O
    Board board;
    while (!WindowShouldClose()) {
        while (board.checkForWinner() == -1) {
            if (WindowShouldClose()) {
                return;
            }
            BeginDrawing();
            ClearBackground(BLACK);
            board.draw();
            EndDrawing();
            if (botIsEnabled && board.getTurn() == 1) {
                std::pair<int, int> move = findBestMove(board);
                board.insertCoordinates(move.first, move.second);
            }
            if (IsMouseButtonPressed(0)) {
                int posX = GetMouseX();
                int posY = GetMouseY();
                board.insertCoordinates(posY / (GetScreenWidth() / 3), posX / (GetScreenHeight() / 3));
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        board.draw();

        EndDrawing();
    }
}