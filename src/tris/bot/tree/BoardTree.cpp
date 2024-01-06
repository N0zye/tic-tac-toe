#include "BoardTree.h"


BoardTree::BoardTree(Board currentBoard) {
    root = new BoardNode(currentBoard);
    initializeTree(currentBoard, root);
}
BoardTree::~BoardTree() {
    // Deallocate memory for the entire tree by deleting the root
    delete root;
}

void BoardTree::initializeTree(Board currentBoard, BoardNode* localRoot) {
    std::vector<std::pair<int, int>> possibleMoves = currentBoard.calculateAllPossibleMoves();
    possibleMoves.shrink_to_fit();
    for (int i = 0; i < possibleMoves.size(); i++) {
        Board tempBoard = currentBoard;
        tempBoard.insertCoordinates(possibleMoves.at(i).first, possibleMoves.at(i).second);
        localRoot->children.emplace_back(new BoardNode(tempBoard));
        initializeTree(tempBoard, localRoot->children.back());
    }
}