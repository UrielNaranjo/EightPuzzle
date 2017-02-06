#include "Problem.h"

EightPuzzle::EightPuzzle()
 : puzzle(9), goal(9) 
{
	for(auto i = 0; i < 8; i++){
		goal.at(i) = i+1;
	}
	goal.at(8) = -1; // this will be the space in the puzzle 
}

EightPuzzle::EightPuzzle(std::vector<int> &v)
 : puzzle(9), goal(9)
{
	puzzle = v;
	for(auto i = 0; i < 8; i++){
		goal.at(i) = i+1;
	}
	goal.at(8) = -1; // this will be the space in the puzzle 

}

bool EightPuzzle::shiftup(){

	return true;
}

bool EightPuzzle::shiftdown(){

	return true;
}

bool EightPuzzle::shiftleft(){

	return true;
} 

bool EightPuzzle::shiftright(){

	return true;
} 

bool EightPuzzle::isGoal() const{
	for(auto i = 0; i < 9; i++){
		if(this->puzzle.at(i) != this->goal.at(i)){
			return false;
		}
	}
	return true;
}

void EightPuzzle::UniformCostSearch(){

}

void EightPuzzle::MisplacedTile(){

}

void EightPuzzle::ManhattanDistance(){

}

void EightPuzzle::SearchAlgorithm(int x){
	if(x == 1){
		this->UniformCostSearch();
	}
	else if(x == 2){
		this->MisplacedTile();
	}
	else if(x == 3){
		this->ManhattanDistance();
	}
}
