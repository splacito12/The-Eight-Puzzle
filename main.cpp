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
    int gN;   //our cost
    int hN;   //our estimated distance from the goal 
    gameState* parent;  //will be used to show the solution steps
};

//declare our goal
vector<int> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 0};

/*
    Simple and short functions will go here
*/

//Here we will be creating comparing our priority queue for A* 
struct comparePQ{
    bool operator()(gameState x, gameState y){
        return (x.gN + x.hN) > (y.gN + y.hN); //since we are doing PQ, we want the lowest value
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
int calculateMisplaced(const vector<int>& game){
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

            //calculate the absolute value of the distance bewteen the goal row and column and the current row  and column
            distSum += abs(Row - currRow) + abs(Column - currColumn);
        }
    }

    return distSum;
}

//node expansion function will go here
vector<gameState*> nodeExpansion(const gameState* currState){
    //expand nodes. This is done by moving tiles up, down, left, and right
        vector<gameState*> expandedNodes;

    //find the position od the blank(0) tile
    int blank = find(currState->gameBoard.begin(), currState->gameBoard.end(), 0) - currState->gameBoard.begin(); 
    int row = blank / 3;
    int column = blank %3;

    //check for all possible moves.
    if(row > 0){    //move up
        gameState* up = new gameState;
        up->gameBoard = currState->gameBoard;

        swap(up->gameBoard[blank], up->gameBoard[blank - 3]);   //swap blank tile with the tile above it

        up->gN = currState->gN + 1; //increment the cost
        up->parent = currState; 

        expandedNodes.push_back(up);
    }
                                                                                        
    if(row < 2){  //move down
        gameState* down = new gameState;
        down->gameBoard = currState->gameBoard;

        swap(down->gameBoard[blank], down->gameBoard[blank + 3]);  //swap blank tile with tile below it

        down->gN = currState->gN + 1; // increment the cost;
        down->parent = currState;

        expandedNodes.push_back(down);
    }
                                                                                                                                                    
    if(column > 0){    //move left
        gameState* left = new gameState;
        left->gameBoard = currState->gameBoard;

        swap(left->gameBoard[blank], left->gameBoard[blank - 1]); //swap blank tile with tile to the left

        left->gN = currState->gN + 1; //increment the cost
        left->parent = currState;

        expandedNodes.push_back(left);
    }
                                                                                                                                                                                                                
    if(column < 2){   //move right
        gameState* right = new gameState;
        right->gameBoard = currState->gameBoard;

        swap(right->gameBoard[blank], right->gameBoard[blank + 1]); //swap blank tile with tile to the right

        right->gN = currState->gN + 1; //increment the cost
        right->parent = currState;

        expandedNodes.push_back(right);
    }

    return expandedNodes;
}

                                                                                                                                                                                                                                                                            
//general search function will go here
/*                                                                                                                                                                                                                                                                         
This function will behave similarly to the one in the slides                                                                                                                                                                                                                                                                                
It will take in the starting state and user's choice to get to the goal state
using either misplace tile or mahnattan distance.
- we will be using priority queue
- calculate the depth
-calculate the max queue size
-calculate the number of nodes expanded

*/

void generalSearch(const vector<int>& startState, int searchChoice){

    priority_queue<gameState*, vector<gameState*>, comparePQ> priorityQueue;
    set<vector<int>> visited;   //keep track of the nodes that are being visited
    
    gameState* start = new gameState;   //create a new game state

    start->gameBoard = startState; 
    start->gN = 0;
                                                                                                                                                                                                                                                                                                                                
    //determine h(n) based off if the user's choice.
    if(searchChoice == 2){
        start->hN = calculateMisplaced(startState);
    }else if(searchChoice == 3){
        start->hN = calculateManhattan(startState);
    }else{
        start->hN = 0;  //this is for uniform cost search. 
    }

    
    //push the startint state into the priority queue
    priorityQueue.push(*start);
                               
    //now, we need to keep track of the depth, max queue size, and the number of nodes expanded
    int depth = 0;
    int maxQueue = 1;
    int expandedNodes = 0;
                          
    //begin the search
    while(!priorityQueue.empty()){
        //get the lowest value node
        gameState* currNode = priorityQueue.top();
        priorityQueue.pop();
        expandedNodes++;
                        
        //check if the current node is the goal state
        if(goalTest(currNode->gameBoard)){
            cout << "You have reached the goal state!" << endl;
            cout << "Depth: " << depth << endl;
            cout << "Max Queue Size: " << maxQueue << endl;
            cout << "Nodes Expanded: " << expandedNodes << endl;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
            
            return;                                                    
        }else{
            //if we didn't reach the goal state, expand the node even more
            vector<gameState*> expandedNodes = nodeExpansion(currNode);
        
        
        }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

// //node expansion function will go here
// vector<gameState> nodeExpansion(const gameState& currState){}



//Now, we will be printing ou our game board
void printGameBoard(const vector<int>& game){
    for(int i = 0; i < 9; i++){  
        if(i % 3 == 0){
            cout << endl;
        }else{
            cout << game[i] << " ";
        }
    }

    cout << "~~~~~~~~~" << endl;
}

//Function to print the optimal solution steps will go here
void printOptSolution(gameState* steps){
    //
}

/*
    Our main function will go here. 
    - We will be asking the user to input the starting state of the puzzle
    - user has the option to choose from the three search algorithms that are provided
*/
int main(){
    //variables go here
    //we will ask the user to input the starting state of the puzzle
    vector<int> startState(9);
    int searchChoice;

    //cout and cin go here
    cout << "Welcome to my 8 puzzle solver!" << endl;
    cout << "Before we proceed, please input the numbers you want to start with." << endl;
    cout << "For the blank tile, please use 0." << endl;
    
    for(int i = 0; i < 9; i++){
        cin >> startState[i];
    }

    //here we will print the puzzle the user has provided
    cout << "Your puzzle is: " << endl;
    printGameBoard(startState);

    //Ask the user what search algorithm they want to use
    cout << "Now, please choice was search algorithm you want to use to solve the puzzle." << endl;
    cout << " 1. Uniform Cost Search" << endl;
    cout << "2. A* with Misplaced Tile Heuristic" << endl;
    cout << "3. A* with Manhatta Distance Heuristic" << endl;
    cin >> searchChoice;

    //if the user chooses a number that isnt 1 - 3, ask them to choose again
    while(searchChoice < 1 || searchChoice > 3){
        cout << "Invalid choice. Please eneter the numbers 1, 2, or 3." << endl;
        cin >> searchChoice;
    }

    //now, depending on the user's choice, call the correct search function
    //we will be using a switch statement
    switch(searchChoice){
        case 1:
            generalSearch(startState, searchChoice);
            break;
        case 2:
            generalSearch(startState, searchChoice);
            break;
        case 3:
            generalSearch(startState, searchChoice);
            break;
    }

    return 0;
}