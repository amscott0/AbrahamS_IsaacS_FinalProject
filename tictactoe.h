// Abraham Scott, Isaac Scott
//Final Project

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include "GameTree.h"
class TicTacToe
{
    public:
        TicTacToe(){
            head = nullptr;
        }
        void playGame();
        void resetGame();
        void printBoard();
        void goBackMove();
        vertex *findBestMove(vertex *node, bool isPlayer);
        int inputMove(bool isPlayer);
        int isGameOver();
        void printPossibleMoves(vertex *node);

    protected:
    private:
        vertex *head; //first data structure - linked list
        std::string difficulty;
        bool gameEnd;
        GameTree myTree; //second data structure - graph like structure

};

#endif // TICTACTOE_H

