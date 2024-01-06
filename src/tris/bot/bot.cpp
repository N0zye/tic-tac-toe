#include "bot.h"

int findScore(BoardNode* root) {
    if (root == nullptr) {
        return 0;
    }

    std::queue<std::pair<BoardNode*, int>> q;
    q.push({ root,0 });
    int sum = 0;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        BoardNode* node = current.first;
        int depth = current.second;

        if (node->children.empty()) {
            // Leaf node
            switch (node->board.checkForWinner()) {
            case 0:
                sum += 1;
                break;
            case 1:// X win (O lost)
                if (depth == 1) {
                    return INT_MIN;
                }
                sum -= (8 - depth);
                break;
            case 2:// O wins
                if (depth == 0) {
                    return INT_MAX;
                }
                sum += (8 - depth);
                break;
            default:
                break;
            }
        }
        else {
            for (BoardNode* child : node->children) {
                q.push({ child, depth + 1 });
            }
        }
    }

    return sum;

}

std::pair<int, int> findBestMove(Board board) { // 0 is X and 1 is O
    std::map<std::pair<int, int>, int> possibleMovesScored;
    BoardTree* tree;
    std::vector<std::pair<int, int>> possibleMoves = board.calculateAllPossibleMoves();
    for (const auto& move : possibleMoves) {
        Board tempBoard = board;
        tempBoard.insertCoordinates(move.first, move.second);
        tree = new BoardTree(tempBoard);
        possibleMovesScored.emplace(move, findScore(tree->root));
        delete tree;
    }

    // Find the move with the highest score
    auto maxIterator = possibleMovesScored.begin();
    for (auto it = possibleMovesScored.begin(); it != possibleMovesScored.end(); ++it) {
        if (it->second > maxIterator->second) {
            maxIterator = it;
        }
    }

    return maxIterator->first;
}