//Abraham Scott, Isaac Scott
//Final Project

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "GameTree.h"
#include "tictactoe.h"
using namespace std;


// Main function run
int main()
{
    TicTacToe ttt;
    
	std::string dmenu = "======Main Menu=====\n"
					"1. Play Game\n"
					"2. Reset Game\n"
                    "3. Place Holder\n"
					"4. Quit";

    int choice;

    bool exit = false;
    
    cout << dmenu << endl;
    
    while(cin >> choice) {
        
        // flush the newlines and other characters
        cin.clear();
        cin.ignore();
        
        switch (choice) {
            case 1:
            {
                //call tictactoe playGame() function
                break;
            }
            
            case 2:
            {
                //ttt.resetGame()
                break;
            }
            case 3:
            {

                break;
            }
                
            case 4:
            {
                exit = true;
                break;
            }
        }
        
        if (exit) {
            break;
        }
        
        cout << dmenu << endl;
    }
	return 0;
}

