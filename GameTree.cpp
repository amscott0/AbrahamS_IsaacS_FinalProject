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

int main(){
    return 0;
}