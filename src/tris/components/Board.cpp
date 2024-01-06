#include "Board.h"

Board::Board() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    turn = false; // starts always 'X'
    initializeBoard();
}

bool Board::operator==(const Board& other) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != other.board[i][j]) {
                return false; 
            }
        }
    }
    return true; 
}

void Board::initializeBoard() {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            board[row][col] = " ";
        }
    }
}

void Board::drawTextIn(int x, int y,const std::string text) {
    if (text == " ") {
        return;
    }
    float centerY = ((float)GetScreenWidth() / 6) * (x*2 +1);
    float centerX = ((float)GetScreenHeight() / 6) * (y*2 +1);
    if (text == "O") {
        DrawRing(Vector2{ centerX, centerY }, 55, 65, 0, 360, 200, RED);
    }
    else {
        DrawLineEx(Vector2{ (float)centerX - 65, (float)centerY + 65 }, Vector2{ (float)centerX + 65, (float)centerY - 65 }, 10, GREEN);
        DrawLineEx(Vector2{ (float)centerX + 65, (float)centerY + 65 }, Vector2{ (float)centerX - 65, (float)centerY - 65 }, 10, GREEN);
    }
}

std::pair<std::pair<int, int>, std::pair<int, int>> Board::getWinCoords() {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != " " && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return { {i, 0}, {i, 2} };
        }
    }

    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] != " " && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return { {0, i}, {2, i} };
        }
    }

    // Check diagonals
    if (board[0][0] != " " && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return { {0, 0}, {2, 2} };
    }

    if (board[0][2] != " " && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return { {0, 2}, {2, 0} };
    }

    return { {-1, -1}, {-1, -1} };
}

void Board::draw() {
    DrawLineEx(Vector2{ 0, (float)GetScreenHeight() / 3 }, Vector2{ (float)GetScreenWidth(), (float)GetScreenHeight() / 3 }, 8, WHITE);
    DrawLineEx(Vector2{ 0, (float)GetScreenHeight() / 3 * 2 }, Vector2{ (float)GetScreenWidth(), (float)GetScreenHeight() / 3 * 2 }, 8, WHITE);
    DrawLineEx(Vector2{ (float)GetScreenWidth() / 3, 0 }, Vector2{ (float)GetScreenWidth() / 3, (float)GetScreenHeight() }, 8, WHITE);
    DrawLineEx(Vector2{ (float)GetScreenWidth() / 3 * 2, 0 }, Vector2{ (float)GetScreenWidth() / 3 * 2, (float)GetScreenHeight() }, 8, WHITE);
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            drawTextIn(row, col, board[row][col]);
        }
    }
    if (checkForWinner() == 1 || checkForWinner() == 2) {
        float startY = ((float)GetScreenWidth() / 6) * (getWinCoords().first.first * 2 + 1);
        float startX = ((float)GetScreenHeight() / 6) * (getWinCoords().first.second * 2 + 1);
        float endY = ((float)GetScreenWidth() / 6) * (getWinCoords().second.first * 2 + 1);
        float endX = ((float)GetScreenHeight() / 6) * (getWinCoords().second.second * 2 + 1);
        DrawLineEx(Vector2{ startX, startY }, Vector2{ endX, endY }, 15, WHITE);
    }
}
void Board::insertCoordinates(int row, int col) {
    if (board[row][col] != " ") {
        return;
    }
    board[row][col] = turn ? "O" : "X";
    turn = !turn;
}

int Board::checkForWinner() {
    /*
    possible returns:
    -1: game hasn't finished
     0: draw
     1: X won
     2: O won
    */
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != " " && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return (board[i][0] == "X") ? 1 : 2;
        }
        if (board[0][i] != " " && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return (board[0][i] == "X") ? 1 : 2;
        }
    }

    if (board[0][0] != " " && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return (board[0][0] == "X") ? 1 : 2;
    }
    if (board[0][2] != " " && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return (board[0][2] == "X") ? 1 : 2;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == " ") {
                return -1;
            }
        }
    }

    return 0;
}

bool Board::getTurn() {
    return turn;
}

std::vector<std::pair<int, int>> Board::calculateAllPossibleMoves() {
    std::vector<std::pair<int, int>> possibleMoves;
    if (checkForWinner() == -1) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (board[row][col] == " ") {
                    possibleMoves.push_back(std::make_pair(row, col));
                }
            }
        }
    }
    return possibleMoves;
}