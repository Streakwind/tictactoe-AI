#include "../include/game.h"
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

bool Board::isGameOver() {
    // rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != Square::NONE && 
            board[i][0] == board[i][1] && 
            board[i][1] == board[i][2]) {
            Board::dispBoard();
            std::cout << ((board[i][0] == Square::XSQ) ? "X" : "O") << " won!\n";
            return true;
        }
    }
    
    // columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] != Square::NONE &&
            board[0][j] == board[1][j] &&
            board[1][j] == board[2][j]) {
            Board::dispBoard();
            std::cout << ((board[0][j] == Square::XSQ) ? "X" : "O") << " won!\n";
            return true;
        }
    }
    
    // diagonals
    if (board[0][0] != Square::NONE &&
        board[0][0] == board[1][1] && 
        board[1][1] == board[2][2]) {
        Board::dispBoard();
        std::cout << ((board[0][0] == Square::XSQ) ? "X" : "O") << " won!\n";
        return true;
    }
    
    if (board[0][2] != Square::NONE &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        Board::dispBoard();
        std::cout << ((board[0][2] == Square::XSQ) ? "X" : "O") << " won!\n";
        return true;
    }
    
    if (filled == 9) {
        Board::dispBoard();
        std::cout << "It's a tie!\n";
        return true;
    }

    return false;
}

void Board::move(Square player) {
    dispBoard();

    int x, y;
    while (true) {        
        std::cin >> x >> y;
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && isEmpty(x, y)) break;
    }

    board[x][y] = player;
    filled++;

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}