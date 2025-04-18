#include "../include/agent.h"
#include "../include/board.h"
#include <random>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>

QLearningAgent::QLearningAgent (double lr, double df, double er) {
    learningRate = lr;
    discountFactor = df;
    explorationRate = er;
    gen.seed(rd());
}

std::pair<int, int>  QLearningAgent::chooseMove (const Board& board) {
    const auto availableMoves = board.getAvailableMoves();

    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    std::uniform_int_distribution<size_t> moveDist(0, availableMoves.size() - 1);

    if (probDist(gen) < explorationRate) return availableMoves[moveDist(gen)];

    // find best q value move
    const std::string state = board.getStateString();
    auto qValues = qTable[state];
    auto bestMove = availableMoves[0];
    double bestQ = -1 * std::numeric_limits<double>::infinity();

    for (const auto& move : availableMoves) {
        const int i = actionToIndex(move);

        if (qValues[i] > bestQ) {
            bestQ = qValues[i];
            bestMove = move;
        }
    }

    return bestMove;
}

void QLearningAgent::learn (const Board& prevBoard, const std::pair<int, int>& move, const Board& newBoard, double reward) {
    const std::string prevState = prevBoard.getStateString();
    const std::string newState = newBoard.getStateString();
    const int i = actionToIndex(move);

    if (!qTable.count(prevState)) qTable[prevState] = std::vector<double>(9, 0.0);
    if (!qTable.count(newState)) qTable[newState] = std::vector<double>(9, 0.0);

    const double maxNextQ = *std::max_element(qTable[newState].begin(), qTable[newState].end());
    double& currentQ = qTable[prevState][i];

    currentQ += learningRate * (reward + discountFactor * maxNextQ - currentQ);
}

void QLearningAgent::savePolicy (const std::string &filepath) {
    std::ofstream outFile (filepath);

    for (const auto& [state, qValues] : qTable) {
        outFile << state;
        
        for (double q : qValues) {
            outFile << " " << q;
        }

        outFile << "\n";
    }
}

void QLearningAgent::loadPolicy (const std::string &filepath) {
    std::ifstream inFile (filepath);

    auto newQTable = qTable;
    std::string str;

    while (std::getline(inFile, str)) {
        std::istringstream iss(str);
        std::string state;
        iss >> state;

        std::vector<double> qValues(9);
        for (int i = 0; i < 9; i++) iss >> qValues[i];

        newQTable[state] = qValues;
    }

    std::swap(qTable, newQTable);
}