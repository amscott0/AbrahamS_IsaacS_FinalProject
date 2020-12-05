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
    // cout << g << endl;
    printVertex(search(head->child[8]->child[7]->child[6]->child[5]->child[4]->child[3]->child[2]->child[0]->child[0]->space));
}

void GameTree::createGameTree(vertex* root){
    //clean vector
    root->child.resize(0);

    //create children of root
    for (int i = 0; i < (9 - root->distance); i++){
        vertex *n = new vertex(root->space, root->distance + 1, root);
        root->child.push_back(n);
        // g++;
    }
    // g++;
    // if(g < 100){
    //     printVertex(root);
    //     cout << endl;
    // }

    //make the children of root unique
    popSpaces(root);
    // cout << "___\n";
    // for (int i = 0; i < root->child.size(); i++)
    // {
    //     printVertex(root->child[i]);
    // }
    // int h;
    // cin >> h;

    //avoids needlessness
    if(root->child.size() == 1){
        // g++;
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

//prints a specific vertex
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

//searches for a specific vertex
//will likely be changed 
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

int main(){
    GameTree test;
    return 0;
}