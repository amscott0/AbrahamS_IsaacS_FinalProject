// Abraham Scott, Isaac Scott
//Final Project

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>


struct gameRound{
    char gameBoard[3][3];
    gameRound *next;
    gameRound *prev;
};

class TicTacToe
{
    public:
        void playGame();
        void printBoard();
        void goBackMove();
        gameRound findBestMove();
        bool inputMove();

    protected:
    private:
        //void miniMax(gameRound node, int depth, bool isMaxPlayer);
        int evaluateMove(char board[3][3]);
        gameRound *head;
        std::string difficulty;
        bool gameEnd;
};

#endif // TICTACTOE_H

