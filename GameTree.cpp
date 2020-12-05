#include "GameTree.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

GameTree::GameTree(){
    head->distance = 0;
    head->visited = false;
    //vertices.push_back(head);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            head->space[i][j] = ' ';
        }
    }
    createGameTree(head);
}

void GameTree::createGameTree(vertex* root){
    for (int i = 0; i < (9 - root->distance); i++){
        vertex *n = new vertex(root->space, root->distance + 1, root);
        root->child.push_back(n);
    }
    popSpaces(root);
}

void GameTree::popSpaces(vertex* root){
    char thing;
    if(root->distance % 2 == 1){
        thing = 'X';
    } else {
        thing = 'O';
    }
    //for every child of root
    for (int i = 0; i < root->child.size(); i++){
        //for every slot of the child of root
        for (int j = i; j < 9; j++){
            //check to see if the child has a character in a certain space in the array
            if(root->child[i]->space[(int)floor(((double)j) / 3.0)][j%3] == ' '){
                root->child[i]->space[(int)floor(((double)j) / 3.0)][j%3] = thing;
                j = 10;
            }
        }
    }
}

void GameTree::printVertex(vertex* root){
    
}
int GameTree::miniMax(vertex *node, int depth, bool isMaxiMove){
    int moveScore;
    moveScore = evaluateMove(node->space);
    if(depth == 0 || node->child.size() == 0){
        return moveScore;
    }
    else if(moveScore == 10 || moveScore == -10){
        return moveScore;
    }
    else if(tieGame(node)){
        return 0;
    }
    if(isMaxiMove){
        int largestValue = -100000;
        for(int i = 0; i < node->child.size(); i++){
            largestValue = max(largestValue, miniMax(node->child[i], depth-1, !isMaxiMove));
        }
        return largestValue;
    }
    else{
        int smallestValue = 100000;
        for(int i = 0; i < node->child.size(); i++){
            miniMax(node->child[i], depth-1, !isMaxiMove);
            smallestValue = min(smallestValue, miniMax(node->child[i], depth-1, !isMaxiMove));
        }
        return smallestValue;
    }
}
bool GameTree::tieGame(vertex *node){
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
    for (int row = 0; row<3; row++) 
    { 
        if (board[row][0]==board[row][1] && board[row][1]==board[row][2]) 
        { 
            if (board[row][0]== 'X') 
                return 10; 
            else if (board[row][0]== 'O') 
                return -10; 
        } 
    } 
  
    // Checking for column win
    for (int col = 0; col<3; col++) 
    { 
        if (board[0][col]==board[1][col] && board[1][col]==board[2][col]) 
        { 
            if (board[0][col]== 'X') 
                return 10; 
  
            else if (board[0][col]== 'O') 
                return -10; 
        } 
    } 
  
    // Checking for diagonal win
    if (board[0][0]==board[1][1] && board[1][1]==board[2][2]) 
    { 
        if (board[0][0]== 'X') 
            return 10; 
        else if (board[0][0]== 'O') 
            return -10; 
    } 
  
    if (board[0][2]==board[1][1] && board[1][1]==board[2][0]) 
    { 
        if (board[0][2]== 'X') 
            return 10; 
        else if (board[0][2]== 'O') 
            return -10; 
    } 
  
    // If there is no winner, return 0
    return 0;     
}

int main(){
    return 0;
}