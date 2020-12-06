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
        difficulty = "Easy";
    }
    else if(choice == "Medium" || choice == "medium"){
        difficulty = "Medium";
    }
    else if(choice == "Hard" || choice == "hard"){
        difficulty = "Hard";
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
                //inputMove(isPlayer);
                //inputMove(!isPlayer);
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
int TicTacToe::inputMove(bool isPlayer){
    if(isPlayer){
        cout << "Enter row and column" << endl;
        int row, col;
        cin >> row >> col;        
        //player move
        if(head == nullptr){
            head = new vertex;
            head->parent = nullptr;
            head->space[row][col] = 'X';
            head->distance = 0;
        }
        else if(head->space[row][col] != ' '){
            cout << "Inputted space already used" << endl;
            return -1;
        }
        else{
            vertex *newHead = new vertex(head->space, head->distance+1, head);
            head->child.push_back(newHead);
            newHead->space[row][col] = 'X';
            head = newHead;
        }
    }
    else{
        //computer move
        vertex *input = findBestMove(head, false);

    }
    return isGameOver();
}
int TicTacToe::isGameOver(){
    //basically just a clone of evaluateMove()
    char board[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            board[i][j] = head->space[i][j];
        }
    }
    //Checking for row win
    for (int row = 0; row<3; row++) { 
        if (board[row][0]==board[row][1] && board[row][1]==board[row][2]) { 
            if (board[row][0]== 'X') 
                return 10; 
            else if (board[row][0]== 'O') 
                return -10; 
        } 
    } 
    // Checking for column win
    for (int col = 0; col<3; col++) { 
        if (board[0][col]==board[1][col] && board[1][col]==board[2][col]) { 
            if (board[0][col]== 'X') 
                return 10; 

            else if (board[0][col]== 'O') 
                return -10; 
        } 
    } 
    // Checking for diagonal win
    if (board[0][0]==board[1][1] && board[1][1]==board[2][2]) { 
        if (board[0][0]== 'X') 
            return 10; 
        else if (board[0][0]== 'O') 
            return -10; 
    } 
    if (board[0][2]==board[1][1] && board[1][1]==board[2][0]){ 
        if (board[0][2]== 'X') 
            return 10; 
        else if (board[0][2]== 'O') 
            return -10; 
    }
    return 0;
}
void TicTacToe::printBoard(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << head->space[i][j] << "";
            if(j%3 != 2){
                cout << " | ";
            }
        }
        if(i%3 != 2){
            cout << endl << "--|---|--\n"; 
        }
    }
    cout << endl;    
}
vertex *TicTacToe::findBestMove(vertex* node, bool isPlayer){
    vertex *temp = myTree.search(node->space);
    int bestMove = -100000;
    int bestRow, bestCol, currentBest, depth;
    char move;

    if(isPlayer){
        move = 'X';
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
    }    
    else{
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
    }
    node->space[bestCol][bestRow] = move;
    return node;
}
