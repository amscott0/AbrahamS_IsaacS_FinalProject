#include <iostream>
#include <string>
#include "tictactoe.h"
#include "GameTree.h"
using namespace std;

void TicTacToe::playGame(){
    cout << "Choose your difficulty:\n"
         << "Easy\n"
         << "Medium\n"
         << "Hard\n";
    string choice;
    cin >> choice;
    if(choice == "Easy" || choice == "easy"){
        difficulty == "Easy";
    }
    else if(choice == "Medium" || choice == "medium"){
        difficulty == "Medium";
    }
    else if(choice == "Hard" || choice == "hard"){
        difficulty == "Hard";
    }
    else{
        cout << "Difficulty not recognized, quitting" << endl;
        return;
    }
    while(!gameEnd){
        cout << "1. Input Move \n"
             << "2. Go Back A Move\n"
             << "3. Print Board\n"
             << "4. Calculate Optimal Move\n"
             << "5. Quit\n";
        int decision;
        switch (decision) {
            case 1:
            {
                //inputMove();
                break;
            }
            
            case 2:
            {
                //goBackMove();
                break;
            }
            case 3:
            {
                //printBoard();
                break;
            }
            case 4:
            {
                //findBestMove();
                break;
            }                
            case 5:
            {
                gameEnd = true;
                break;
            }
        }   
    }

}
void TicTacToe::printBoard(){

}
vertex *TicTacToe::findBestMove(vertex* node, bool isPlayer){
    GameTree myTree;
    vertex *temp; //= myTree.search(node->space);
    int bestMove = -100000;
    int bestRow, bestCol, currentBest, depth;
    char move;

    if(isPlayer)
        move = 'X';
    else
        move = 'O';

    if(difficulty == "Easy")
        depth = 1;
    else if(difficulty == "Medium")
        depth = 3;
    else if (difficulty == "Hard")
        depth = 9;
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(node->space[i][j] == ' '){
                temp->space[i][j] = move;
                currentBest = myTree.miniMax(temp, depth, !isPlayer);
                temp->space[i][j] = ' ';
                if(currentBest > bestMove){
                    bestCol = i;
                    bestRow = j;
                    bestMove = currentBest;
                }
            }
        }
    }
    temp->space[bestCol][bestRow] = move;
    return temp;
}