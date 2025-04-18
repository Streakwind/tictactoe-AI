#pragma once
#include "board.h"
#include <unordered_map>
#include <random>

class QLearningAgent {
private:
    std::unordered_map<std::string, std::vector<double>> qTable;
    double learningRate;
    double discountFactor;
    double explorationRate;

    // rng
    std::random_device rd;
    std::mt19937 gen{rd()};

    // (0,0) → 0    (0,1) → 1    (0,2) → 2
    // (1,0) → 3    (1,1) → 4    (1,2) → 5 
    // (2,0) → 6    (2,1) → 7    (2,2) → 8
    int actionToIndex (const std::pair<int, int>& move) const { return move.first * 3 + move.second; }
    // 0 → (0,0)    1 → (0,1)    2 → (0,2)
    // 3 → (1,0)    4 → (1,1)    5 → (1,2) 
    // 6 → (2,0)    7 → (2,1)    8 → (2,2)
    std::pair<int, int> indexToAction (int index) const { return {index / 3, index % 3}; }

public:
    // lr -> learning rate (alpha)
    // df -> discount factor (gamma)
    // er -> exploration rate (epsilon)
    QLearningAgent (double lr = 0.1, double df = 0.9, double er = 0.3);
    
    std::pair<int, int> chooseMove (const Board& board);
    void learn (const Board& prevBoard, 
               const std::pair<int, int>& move,
               const Board& newBoard,
               double reward);
    
    void savePolicy (const std::string& filepath);
    void loadPolicy (const std::string& filepath);

    void setLearningRate (double lr) { learningRate = lr; }
    void setExplorationRate (double er) { explorationRate = er; }
    double getLearningRate () const { return learningRate; }
    double getExplorationRate () const { return explorationRate; }
};