#include "GameTree.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

int g = 0;

GameTree::GameTree(){
    //create the empty head of the graph
    head = new vertex;
    head->distance = 0;
    head->visited = false;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            head->space[i][j] = ' ';
        }
    }
    //calls the createGameTree function
    createGameTree(head);
}

void GameTree::createGameTree(vertex* root){
    //clean vector
    root->child.clear();

    //create children of root
    for (int i = 0; i < (9 - root->distance); i++){
        vertex *n = new vertex(root->space, root->distance + 1, root);
        root->child.push_back(n);
    }

    //make the children of root unique
    popSpaces(root);

    //avoids needlessness
    if(root->child.size() == 1){
        return;
    }

    //calls this function again for recursion 
    for (int i = 0; i < root->child.size(); i++){
        createGameTree(root->child[i]);
    }
    
}

// populates the game board of root's children
void GameTree::popSpaces(vertex* root){
    //creating a checking device for ensures that one of the children is not the same as another
    char checker[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            checker[i][j] = root->space[i][j];
        }
    }
    //interchanges between Xs and Os for game
    char thing;
    if (root->distance % 2 == 0){
        thing = 'X';
    }else{
        thing = 'O';
    }

    //for every child of root
    for (int i = 0; i < root->child.size(); i++){
        //for every slot of the child of root
        for (int j = 0; j < 9; j++){
            //check to see if the child has an empty slot open in a certain space in the array
            //if so check to see if checker also has an empty slot;
            if (root->child[i]->space[(int)floor(((double)j) / 3.0)][j % 3] == ' ' && checker[(int)floor(((double)j) / 3.0)][j % 3] == ' '){
                root->child[i]->space[(int)floor(((double)j) / 3.0)][j % 3] = thing;
                checker[(int)floor(((double)j) / 3.0)][j % 3] = thing;
                break;
            }
        }
    }
}

//prints a specific vertex in a neat fashion
void GameTree::printVertex(vertex* root){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << root->space[i][j] << "";
            if(j%3 != 2){
                cout << " | ";
            }
        }
        if(i%3 != 2){
            cout << endl << "--|---|--\n"; 
        }
    }
    cout << endl << endl;
}

//searches for a specific vertex
vertex *GameTree::search(char a[3][3]){
    bool found;
    //compares given array and the head's array
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(head->space[i][j] == a[i][j]){
                found = true;
            }else{
                found = false;
                i = 10;
                j = 10;
            }
        }
    }
    //if it is not found, calls recursive function searchHelper on the head's children
    if(!found){
        for (int i = 0; i < head->child.size(); i++){
            vertex *temp = searchHelper(a, head->child[i]);
            if (temp != nullptr)
            {
                return temp;
            }
        }
        return nullptr;
    }
    else
    {
        return head;
    }
}

vertex *GameTree::searchHelper(char a[3][3], vertex* root){
    bool found;
    //compares given array and the root's array
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if(root->space[i][j] == a[i][j]){
                found = true;
            }else{
                found = false;
                i = 10;
                j = 10;
            }
        }
    }
    //if it was not found, calls searchHelper with root's children
    if(!found){
        for (int i = 0; i < root->child.size(); i++){
            vertex *temp = searchHelper(a, root->child[i]);
            if (temp != nullptr)
            {
                return temp;
            }
        }
        return nullptr;
    }
    else
    {
        return root;
    }
}
int GameTree::miniMax(vertex *node, int depth, bool isMaxiMove){
    int moveScore;
    //calls evaluateMove on the board to determine the heuristic value
    //in other words, it figures out if the current board is good for the player, good for the computer, or neither
    moveScore = evaluateMove(node->space);
    //miniMax is a recursive function, the following is one of the conditions to end it

    //depth is determined by the difficulty, when it gets to zero then no more children are checked
    //harder difficulty means more possibilities checked

    //if there are no more children then return the heuristic value
    //if the board is a victory for the player (moveScore == 10) or a victory for the computer (moveScore == -10),
    //then return the heuristic value
    if(depth == 0 || node->child.size() == 0 || moveScore == 10 || moveScore == -10){
        //this was supposed to fix the problem with the ai not going for the first available win
        if(isMaxiMove){
            //subtracted by the distance from the head of the tree in order to help the AI win quicker
            return moveScore - node->distance;
        }
        else{
            //added by the distance from the head of the tree in order to help the AI win quicker
            return moveScore + node->distance;
        }
    }
    else if(tieGame(node)){
        return 0;
    }
    //if isMaxiMove is true, then we want to find the largest heuristic value out of all of the current node's children
    if(isMaxiMove){
        int largestValue = -100000;
        for(int i = 0; i < node->child.size(); i++){
            largestValue = max(largestValue, miniMax(node->child[i], depth-1, !isMaxiMove));
        }
        return largestValue;
    }
    //else we want to find the smallest heuristic value out of all of the current node's children
    else{
        int smallestValue = 100000;
        for(int i = 0; i < node->child.size(); i++){
            smallestValue = min(smallestValue, miniMax(node->child[i], depth-1, !isMaxiMove));
        }
        return smallestValue;
    }
}
bool GameTree::tieGame(vertex *node){
    //simply finds if the game is a tie
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(node->space[i][j] == ' '){
                return false;
            }
        }
    }
    return true;
}
int GameTree::evaluateMove(char board[3][3]){
    // Checking for row win
    for (int row = 0; row<3; row++) { 
        if (board[row][0]==board[row][1] && board[row][1]==board[row][2]) { 
            //assign a value of 10 if X wins, because the player is the maximizer
            if (board[row][0]== 'X')
                return 10; 
            //vice versa, the computer is the minimizer
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
    if (board[0][2]==board[1][1] && board[1][1]==board[2][0]) { 
        if (board[0][2]== 'X') 
            return 10; 
        else if (board[0][2]== 'O') 
            return -10; 
    } 

    // If there is no winner, return 0
    return 0;     
}
vertex * GameTree::getHead(){
    return head;
}
