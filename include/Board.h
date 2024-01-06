#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>

class Board {
private:
    std::string board[3][3];
    bool turn;  // 0 is X's turn and 1 is O's turn
    void initializeBoard();
    void drawTextIn(int x, int y,const std::string text);
    std::pair<std::pair<int, int>, std::pair<int, int>> getWinCoords();

public:
    Board();
    
    bool operator==(const Board& other);

    void draw();

    void insertCoordinates(int row, int col);

    int checkForWinner();

    bool getTurn();

    std::vector<std::pair<int, int>> calculateAllPossibleMoves();
};