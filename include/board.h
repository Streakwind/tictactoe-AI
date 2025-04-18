#pragma once
#include <vector>
#include <string>

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
    bool isGameOver () const;
    bool isWinningMove (int x, int y, Square player) const;
    void move (int x, int y, Square player);
    
    std::vector<std::pair<int, int>> getAvailableMoves () const; 
    std::string getStateString () const;
    Square getSquare(int x, int y) const;
    Square getCurrentPlayer() const;  
};