#pragma once

#include <Board.h>

class BoardNode {
public:
    Board board;
    std::vector<BoardNode*> children;
    BoardNode(Board board) : board(board) {}
    ~BoardNode() {
        // Deallocate memory for child nodes
        for (BoardNode* child : children) {
            delete child;
        }
    }

};

class BoardTree {
public:
    BoardNode* root;

    BoardTree(Board currentBoard);
    ~BoardTree();
private:
    void initializeTree(Board currentBoard, BoardNode* localRoot);
};