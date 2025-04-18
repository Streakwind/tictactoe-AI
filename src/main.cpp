#include <iostream>
#include <chrono>
#include <algorithm>
#include "../include/board.h"
#include "../include/agent.h"

#ifdef _WIN32
#include <windows.h>
#else
#include<cstdlib>
#endif

void train (QLearningAgent& ai, int episodes) {
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < episodes; i++) {
        Board game;
        Square curP = Square::XSQ;

        double decayRate = 0.9999;
        ai.setExplorationRate(std::max(0.01, ai.getExplorationRate() * decayRate));
        ai.setLearningRate(0.5 / (1.0 + i / static_cast<double>(episodes)));

        while (!game.isGameOver()) {
            auto move = ai.chooseMove(game);
            Board prevState = game;

            game.move(move.first, move.second, curP);

            double reward = 0;
            if (game.isGameOver()) {
                if (game.isWinningMove(move.first, move.second, curP)) reward = 1.0;
                else if (game.isWinningMove(move.first, move.second, (curP == Square::XSQ ? Square::OSQ : Square::XSQ))) reward = -1.0;
                else reward = 0.3;
            }
            
            ai.learn(prevState, move, game, reward);
            curP = (curP == Square::XSQ) ? Square::OSQ : Square::XSQ;
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << "Complete in " << std::chrono::duration_cast<std::chrono::seconds>(end-start).count() << "\n";
}

void play (QLearningAgent& ai) {
    Board game;
    Square player = Square::XSQ;
    Square aiPlayer = Square::OSQ;
    
    while (!game.isGameOver()) {
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
    
    game.dispBoard();

    if (game.isWinningMove(-1, -1, player)) std::cout << "you win\n";
    else if (game.isWinningMove(-1, -1, aiPlayer)) std::cout << "you lost\n";
    else std::cout << "draw\n";
}

int main () {
    QLearningAgent ai(0.1, 0.9, 0.3);

    // train(ai, 100000);
    // ai.savePolicy("ttt.policy");  

    ai.setExplorationRate(0.0);    
    ai.loadPolicy("ttt.policy");  

    play(ai);

    return 0;
}
