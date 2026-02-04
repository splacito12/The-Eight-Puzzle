/*
    Name: Samantha Placito Melendrez
    SID: splac006
    Project: The Eight Puzzle
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

//here we will declare our states
struct gameState{
    vector<int> gameBoard;
    int g(n);   //our cost
    int h(n);   //our estimated distance from the goal 
    State* parent;  //will be used to show the solution steps
};

//declare our goal
vector<int> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 0};

/*
    Simple and short functions will go here
*/

//Here we will be creating comparing our priority queue for A* 
struct comparePQ{
    bool operator()(gameState x, gameState y){
        return (x.g(n) + x.h(n)) > (y.g(n) + y.h(n));
    }
}

//Our goal test function will go here. It will be a bool function
bool goalTest(const vector<int>& game){
    return game == goalState;
}

/*

    All of our search related functions will go here

*/

//Now, we will be printing ou our game board
void printGameBoard(const vector<int>& game){
    for(int i = 0; i < 9; i++){  
        if(i % 3 == 0){
            cout << " " << endl;
        }else{
            cout << game[i] << " ";
        }
    }

    cout << "~~~~~~~~~" << endl;
}

/*
    Our main function will go here. 
    - We will be asking the user to input the starting state of the puzzle
    - user has the option to choose from the three search algorithms that are provided
    - outputs the results with its steps
    -outputs the depth along with expanded nodes and max queue size
*/
int main(){}