// Abraham Scott, Isaac Scott
//Final Project

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include "GameTree.h"
class TicTacToe
{
    public:
        void playGame();
        void printBoard();
        void goBackMove();
        vertex *findBestMove(vertex *node, bool isPlayer);
        bool inputMove(bool isPlayer);

    protected:
    private:
        vertex *head;
        std::string difficulty;
        bool gameEnd;
        GameTree myTree;

};

#endif // TICTACTOE_H

