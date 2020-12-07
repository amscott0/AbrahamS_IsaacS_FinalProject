#ifndef GAMETREE_H
#define GAMETREE_H

#include<vector>
#include<iostream>

struct vertex{
    char space[3][3]; //game board 
    vertex *parent = nullptr;
    bool visited;
    int distance;
    std::vector<vertex*> child;
    vertex(){};
    vertex(char ar[3][3], int d, vertex *p)
    {
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                space[i][j] = ar[i][j];
            }
        }
        distance = d;
        parent = p;
    }
};

class GameTree
{
    public:
        GameTree();
        void printVertex(vertex* root);
        int miniMax(vertex *node, int depth, bool isMaxiMove); //most important function, finds the ideal move to make
        vertex *search(char a[3][3]); 
        vertex *getHead();
    protected:
    private:
        vertex* head;
        void popSpaces(vertex *root);
        void DFSLabel(std::string person, int ID);
        vertex *searchHelper(char a[3][3], vertex* root);
        void createGameTree(vertex *root);
        bool tieGame(vertex *node);
        int evaluateMove(char board[3][3]); //assigns a heuristic value to a game board state, integral to miniMax working
};

#endif // GAMETREE_H