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
        return (x.g(n) + x.h(n)) > (y.g(n) + y.h(n)); //since we are doing PQ, we want the lowest value
    }
}

//Our goal test function will go here. It will be a bool function
bool goalTest(const vector<int>& game){
    return game == goalState;
}

/*

    All of our search related functions will go here

*/

//the A* misplaced tile heuristic function
int calculateMiplaced(const vector<int>& game){
    int misplacedTile = 0;
    for(int i = 0; i < 9; i++){
        //check whether the tile is in its position. Increment if not.
        if(game[i] != 0 && game[i] != goalState[i]){
            misplacedTile++;
        }
    }
    return misplacedTile;
}

//the A* manhattan didistance heuristic function
int calculateManhattan(const vector<int>& game){
    //since we are doing manhattan distance, we will need to calculate the distance
    int distSum = 0;
    for(int i = 0; i < 9; i++){
        //calculate the distance of the tiles that aren't in their position
        if(game[i] == 0){ 
            continue;
        }else{
            //calculate the goal row and column
            //remember, we have three rows and three columns
            int Row = (game[i] - 1) / 3;
            int Column = (game[i] - 1) % 3;

            //now, we need to calculate the current row and column
            int currRow = i / 3;
            int currColumn = i % 3;

            //calculate the absolute value of the two distanced
            distSum += abs(Row - currRow) + abs(Column - currColumn);
        }
    }

    return distSum;
}

//uniform cost search function
void UCS(const vector<int>& startState){
    //remember we use priority queue for uniform cost search
    //we need a function for the all of the nodes we visited
    priority_queue<gameState, vector<gameState>, comparePQ> priorityQueue;

}




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