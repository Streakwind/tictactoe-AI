

#include <iostream>
#include "../include/board.h"
#include "../include/agent.h"

int main () {
    Board game;
    Square curPlayer = Square::XSQ;

    while (!game.isGameOver()) {
        game.move(curPlayer);
        curPlayer = (curPlayer == Square::XSQ) ? Square::OSQ : Square::XSQ;
    }

    return 0;
}