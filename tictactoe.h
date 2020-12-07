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
        void printPossibleMoves(vertex *node);
        void printAllMovesMade();
        void changeDifficulty();
    protected:
    private:
        vertex *head; //first data structure - linked list that holds all moves made
                      //sort of a hybrid linked list, because the head moves forward and is
                      //the current state of the board
        std::string difficulty;
        bool gameEnd;
        GameTree myTree; //second data structure - graph like structure that holds every possible tictactoe
                         //playthrough possibility

};

#endif // TICTACTOE_H

