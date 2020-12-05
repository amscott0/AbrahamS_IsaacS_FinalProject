#ifndef GAMETREE_H
#define GAMETREE_H

#include<vector>
#include<iostream>

struct vertex{
    char space[3][3];
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
        vertex *search(char a[3][3]);

    protected:
    private:
        vertex* head;
        void popSpaces(vertex *root);
        //I want to add all vertices to a vector
        //std::vector<vertex> vertices;
        void DFSLabel(std::string person, int ID);
        vertex *searchHelper(char a[3][3], vertex* root);
        void unvisit(vertex *root);
        void unvisitHelper(vertex *root);
        void createGameTree(vertex *root);
};

// class Graph
// {
//     public:
//         Graph();  
//         ~Graph(); 
//         void addEdge(std::string v1, std::string v2, int weight);
//         void addVertex(std::string name);
//         int isAdjacent(std::string v1, std::string v2);
//         void displayEdges();
//         void assignGroupID();
//         void infectAndTrace();
//         void infectAndSpread(double rate);
        
//     protected:
//     private:
//         std::vector<vertex> vertices;
//         vertex *findVertex(std::string name);
//         void DFSLabel(std::string person, int ID);
//         void unvisit();
// };

#endif // GAMETREE_H