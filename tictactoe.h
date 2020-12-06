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
        std::string findBestMove(vertex *node, bool isPlayer);
        int inputMove(bool isPlayer);
        int isGameOver();
        
    protected:
    private:
        vertex *head; //first data structure
        std::string difficulty;
        bool gameEnd;
        GameTree myTree; //second data structure

};

#endif // TICTACTOE_H

