#include <iostream>
#include <string>
#include "tictactoe.h"
#include "GameTree.h"
using namespace std;

void TicTacToe::playGame(){
    //set difficulty
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
    //reset gameEnd variable
    gameEnd = false;
    while(!gameEnd){
        cout << "1. Input Move \n"
             << "2. Go Back A Move\n"
             << "3. Print Board\n"
             << "4. Calculate Optimal Move\n"
             << "5. Print all previous moves made\n"
             << "6. Print all possible moves\n"
             << "7. Change difficulty\n"
             << "8. Quit\n";
        int decision;
        cin >> decision;
        switch (decision) {
            case 1:
            {
                //first call for player
                int move1 = inputMove(true);
                //player wins
                if(move1 == 10){
                    cout << "You won!" << endl;
                    printBoard();
                    gameEnd = true;
                    return;
                }
                //move was invalid
                else if(move1 == -2){
                    break;
                }
                //tie game, game over
                else if(move1 == -1){
                    cout << "Tie game! Game over!" << endl;
                    printBoard();
                    gameEnd = true;
                    return;
                }

                //second call for computer
                int move2 = inputMove(false);
                //computer wins
                if(move2 == -10){
                    cout  << "You lost! Better luck next time!" << endl;
                    printBoard();
                    gameEnd = true;
                    return;
                }
                //tie game
                else if(move2 == -1){
                    cout << "Tie game! Game over!" << endl;
                    printBoard();
                    gameEnd = true;
                    return;
                }
                
                break;
            }
            
            case 2:
            {
                goBackMove();
                break;
            }
            case 3:
            {
                printBoard();
                break;
            }
            case 4:
            {
                string out = findBestMove(head, true);
                cout << "the ideal move for the player is column: " << ((int)out[1] - '0') + 1 << " row: " << ((int)out[0] - '0') + 1 << endl; 
                break;
            } 
            case 5:
            {
                printAllMovesMade();
                break;
            }                           
            case 6:
            {
                printPossibleMoves(head);
                break;
            }
            case 7:
            {
                changeDifficulty();                
                break;
            }
            case 8:
            {
                gameEnd = true;
                break;
            }            
        }   
    }

}
int TicTacToe::inputMove(bool isPlayer){
    //check if function is called for player or computer
    if(isPlayer){
        cout << "Enter column followed by row" << endl;
        int row, col;
        cin >> col >> row;
        row--;
        col--;        
        //player move
        //linked list is empty, beginning of game
        if(head == nullptr){
            head = new vertex;
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    head->space[i][j] = ' ';
                }
            }        
            head->parent = nullptr;
            head->space[row][col] = 'X';
            head->distance = 0;
        }
        //else if player inputted somewhere that is already occupied
        else if(head->space[row][col] != ' '){
            cout << "Inputted space already used!" << endl;
            return -2;
        }
        //else the player inputted a row or column outside of 1-3
        else if(row > 2 || col > 2 || col < 0 || row < 0){
            cout << "Inputted row or column not valid!" << endl;
            return -2;
        }
        //base case
        else{
            vertex *newHead = new vertex(head->space, head->distance+1, head);
            newHead->space[row][col] = 'X';
            head->child.push_back(newHead);
            head = newHead;
        }
    }
    else{
        //computer move
        vertex *input = new vertex (head->space, head->distance+1, head);
        //call findBestMove for computer
        string inString = findBestMove(head, false);

        int a = inString[0] - '0';
        int b = inString[1] - '0';
        input->space[a][b] = 'O';
        head->child.push_back(input);
        head = input;
    }
    //find if this move ended the game
    return isGameOver();
}
int TicTacToe::isGameOver(){
    //basically just a clone of evaluateMove()

    char board[3][3];
    //copy head node into board variable
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
    //checking for tie
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == ' '){
                return 0;
            }
        }
    }
    //returns -1 if the game is a tie
    return -1;
}
void TicTacToe::printBoard(){
    //check for empty board
    if(head == nullptr){
        cout << "Board empty!!" << endl;
        return;
    }
    //iterate through the 2d array
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
string TicTacToe::findBestMove(vertex* node, bool isPlayer){
    //check if findBestMove is called at the very beginning, LL is empty
    vertex *temp;
    if(node == nullptr && node == head){
        temp = myTree.search(myTree.getHead()->space);
    }
    //base case
    else{
        temp = myTree.search(node->space);
    }

    myTree.printVertex(temp);
    vertex *result = temp;
    int bestMove;
    int bestRow, bestCol, currentBest, depth;
    char move;
    //if the function is called for the player, set depth to 9 and set move = 'X'
    if(isPlayer){
        bestMove = -10000;
        move = 'X';
        depth = 9;
        for(int i = 0; i < temp->child.size(); i++){
            //put a ! in front of isPlayer to fix the un-ideal moves thing
            currentBest = myTree.miniMax(temp->child[i], depth, !isPlayer);
            if(currentBest > bestMove){
                result = temp->child[i];
                bestMove = currentBest;
            }    
        }
    //alternate way of doing the same thing
    //     for(int i = 0; i < 3; i++){
    //         for(int j = 0; j < 3; j++){
    //             if(node->space[i][j] == ' '){
    //                 temp->space[i][j] = move;
    //                 currentBest = myTree.miniMax(temp, depth, isPlayer);
    //                 temp->space[i][j] = ' ';
    //                 if(currentBest > bestMove){
    //                     bestCol = i;
    //                     bestRow = j;
    //                     bestMove = currentBest;
    //                 }
    //             }
    //         }
    //     }
    }
    //Otherwise the function was called for the computer, set move to 'O' and find difficulty
    else{
        bestMove = 10000;
        move = 'O';
        if(difficulty == "Easy")
            depth = 1;
        else if(difficulty == "Medium")
            depth = 3;
        else if (difficulty == "Hard")
            depth = 9;
        //depth represents how many levels down the tree the function will iterate
        for(int i = 0; i < temp->child.size(); i++){

            currentBest = myTree.miniMax(temp->child[i], depth, !isPlayer);
            if(currentBest < bestMove){
                result = temp->child[i];
                bestMove = currentBest;
            }    
        }
        // for(int i = 0; i < 3; i++){
        //     for(int j = 0; j < 3; j++){
        //         if(node->space[i][j] == ' '){
        //             temp->space[i][j] = move;
        //             currentBest = myTree.miniMax(temp, depth, !isPlayer);
        //             temp->space[i][j] = ' ';
        //             if(currentBest > bestMove){
        //                 bestCol = i;
        //                 bestRow = j;
        //                 bestMove = currentBest;
        //             }
        //         }
        //     }
        // }
    }
    //find where temp and result are different, this is the new move
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(temp->space[i][j] != result->space[i][j]){
                bestRow = j;
                bestCol = i;
            }
        }
    }
    string output = to_string(bestCol) + to_string(bestRow);
    return output;
}

void TicTacToe::printPossibleMoves(vertex *root){
    vertex *temp;
    //check if node is beginning of linked list
    if(root == nullptr && root == head){
        temp = myTree.search(myTree.getHead()->space);
    }
    //base case
    else{
        temp = myTree.search(root->space);
    }

    for (int i = 0; i < temp->child.size(); i++){
        myTree.printVertex(temp->child[i]);
    }
}

void TicTacToe::goBackMove(){
    //check if LL is empty
    if(head == nullptr){
        cout << "No moves have been made" << endl;
        return;
    }
    //go back two moves, once for the player's move, twice for the computer's move
    vertex *temp = head;
    head = head->parent;
    delete temp;
    temp->child.clear();
    temp = head;
    head = head->parent;
    delete temp;
    temp->child.clear();
}

void TicTacToe::resetGame(){
    //resets variables and deletes LL
    vertex *temp;
    while (head->parent != nullptr){
        temp = head;
        head = head->parent;
        delete temp;
        head->child.clear();
    }
    delete head;
    head = nullptr;
}
void TicTacToe::printAllMovesMade(){
    //check for empty LL
    if(head == nullptr){
        cout << "No moves have been made!" << endl;
        return;
    }
    //go to end of linked list
    vertex *temp = head;
    while(temp->parent != nullptr){
        temp = temp->parent;
    }
    //then iterate forwards
    while(temp != nullptr){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                cout << temp->space[i][j] << "";
                if(j%3 != 2){
                    cout << " | ";
                }
            }
            if(i%3 != 2){
                cout << endl << "--|---|--\n"; 
            }
        }
        cout << endl << endl;
        if(temp->child.size() != 0){
            temp = temp->child[0];
        }
        else{
            temp = nullptr;
        }
    }        
    
}
void TicTacToe::changeDifficulty(){
    //pretty much the same as what is in the playGame() function
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
        cout << "Difficulty not recognized" << endl;
        return;
    }    
}