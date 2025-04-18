#include "../include/board.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

Board::Board () : filled(0) {
    for (int x = 0; x < 3; x++) {
        for (int y= 0; y < 3; y++) {
            Board::board[x][y] = Square::NONE;
        }
    }
}

void Board::dispBoard () {
    for (int i = 0; i < 3; i++) std::cout << " ___ ";
    std::cout << "\n";

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << (board[i][j] == Square::NONE ? "|   |" : 
                (board[i][j] == Square::XSQ ? "| X |" : "| O |"));
        }

        std::cout << "\n";

        for (int j = 0; j < 3; j++) {
            std::cout << " --- ";
        }

        std::cout << "\n";
    }

    std::cout << std::flush;
}

bool Board::isEmpty (int x, int y) {
    return Board::board[x][y] == Square::NONE;
}

bool Board::isGameOver () const {
    return (filled == 9) || isWinningMove(-1, -1, Square::XSQ) || isWinningMove(-1, -1, Square::OSQ);
}

bool Board::isWinningMove (int x, int y, Square player) const {
    if (x == -1 && y == -1) {
        for (x = 0; x < 3; x++) {
            for (y = 0; y < 3; y++) {
                if (checkWin(x, y, player)) return true;
            }
        }

        return false;
    }
    
    return checkWin(x, y, player);
}

bool Board::checkWin (int x, int y, Square player) const {
    if (board[x][y] != player) return false;
    
    // row
    if (board[x][0] == player && board[x][1] == player && board[x][2] == player) return true;
    
    // column
    if (board[0][y] == player && board[1][y] == player && board[2][y] == player) return true;
    
    // diagnol
    if (x == y && board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (x + y == 2 && board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;

    return false;
}

bool Board::move (int x, int y, Square player) {
    if (x < 0 || x > 2 || y < 0 || y > 2 || !isEmpty(x, y)) return false;

    board[x][y] = player;
    filled++;

    return true;
}

std::vector<std::pair<int, int>> Board::getAvailableMoves () const {
    std::vector<std::pair<int, int>> moves;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (board[x][y] == Square::NONE) {
                moves.push_back(std::make_pair(x, y));
            }
        }
    }

    return moves;
}

std::string Board::getStateString () const {
    std::string state;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            switch (board[i][j]) {
                case Square::XSQ: state += 'X'; break;
                case Square::OSQ: state += 'O'; break;
                case Square::NONE: state += ' '; break;
            }
        }
    }

    return state;
}

Square Board::getSquare(int x, int y) const { return board[x][y]; }

Square Board::getCurrentPlayer() const { return (filled % 2 == 0) ? Square::XSQ : Square::OSQ; }