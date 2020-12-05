#include <iostream>
#include <string>
#include "tictactoe.h"
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