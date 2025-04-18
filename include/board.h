#pragma once
#include <vector>
#include<string>

enum class Square {
    NONE,
    XSQ,
    OSQ
};

// representation by 3x3 2d arr
class Board {
private:
    Square board[3][3];
    int filled;
    void dispBoard();

public:
    Board ();
    bool isEmpty (int x, int y); 
    bool isGameOver ();
    void move (Square player);
    std::vector<std::pair<int, int>> getAvailableMoves () const; 
    std::string getStateString () const;
};