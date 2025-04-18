#include <iostream>
#include <chrono>
#include "../include/board.h"
#include "../include/agent.h"

#ifdef _WIN32
#include <windows.h>
#else
#include<cstdlib>
#endif

void clear () {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void train (QLearningAgent& ai, int episodes) {
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < episodes; i++) {
        Board game;
        Square curP = Square::XSQ;

        ai.setExplorationRate(0.3 * (1.0 - i / static_cast<double>(episodes)));

        while (!game.isGameOver()) {
            auto move = ai.chooseMove(game);
            Board prevState = game;

            game.move(move.first, move.second, curP);

            double reward = 0;
            if (game.isGameOver()) reward = game.isWinningMove(move.first, move.second, curP) ? 1.0 : (game.getAvailableMoves().empty() ? 0.5 : -1.0);

            ai.learn(prevState, move, game, reward);
            curP = (curP == Square::XSQ) ? Square::OSQ : Square::XSQ;
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << "Complete in " << (end-start).count() << "\n";
}

void play (QLearningAgent& ai) {
    Board game;
    Square player = Square::XSQ;
    Square aiPlayer = Square::OSQ;
    
    while (!game.isGameOver()) {
        clear();
        game.dispBoard();
        
        if (game.getCurrentPlayer() == player) {
            int x, y;
            std::cin >> x >> y;
            
            while (!game.move(x, y, player)) {
                std::cout << "invalid\n";
                std::cin >> x >> y;
            }
        } else {
            auto move = ai.chooseMove(game);
            game.move(move.first, move.second, aiPlayer);
        }
    }
    
    clear();
    game.dispBoard();

    if (game.isWinningMove(-1, -1, player)) std::cout << "you win\n";
    else if (game.isWinningMove(-1, -1, aiPlayer)) std::cout << "you lost\n";
    else std::cout << "draw\n";
}

int main () {
    QLearningAgent ai(0.1, 0.9, 0.3);

    train(ai, 10000);

    ai.savePolicy("ttt.policy");

    play(ai);

    return 0;
}