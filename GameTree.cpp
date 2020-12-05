#include "GameTree.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

int g = 0;

GameTree::GameTree(){
    //create the empty head of the graph
    head->distance = 0;
    head->visited = false;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            head->space[i][j] = ' ';
        }
    }
    //calls the createGameTree function
    createGameTree(head);
    cout << g << endl;
}

void GameTree::createGameTree(vertex* root){
    root->child.resize(0);

    for (int i = 0; i < (9 - root->distance); i++){
        vertex *n = new vertex(root->space, root->distance + 1, root);
        root->child.push_back(n);
        // g++;
    }
    g++;
    if(g < 100){
        printVertex(root);
        cout << endl;
    }
    popSpaces(root);
    // cout << "___\n";
    // for (int i = 0; i < root->child.size(); i++)
    // {
    //     printVertex(root->child[i]);
    // }
    // int h;
    // cin >> h;
    if(root->child.size() == 1){
        // g++;
        return;
    }

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
    cout << endl;
}

vertex *GameTree::search(char a[3][3]){
    bool found;
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
    if(!found){
        
    }
}

int main(){
    GameTree test;
    return 0;
}