#include "Problem.h"

node::node()
 : dist(0), parent(NULL)
{}

const node & node::operator=(const node &r){
	for(auto i = 0; i < 3; i++){
		for(auto j = 0; i < 3; j++){
			this->puzzle.at(i).at(j) = r.puzzle.at(i).at(j);
		}
	}
	return *this;
}

void node::setParent(node &x){
	this->parent = &x;	
}

node node::getParent(){
	node temp = *parent;
	return temp;
}

void node::setDist(int &x){
	this->dist = x;
}

int node::getDist(){
	return this->dist;
}

bool node::operator<(const node &x) const{
	return (this->dist < x.dist);
}

bool node::operator>(const node &x) const{
	return this->dist > x.dist;
}

bool node::operator<=(const node &x) const{
	return (this->dist <= x.dist);
}

bool node::operator>=(const node &x) const{
	return this->dist >= x.dist;
} 

bool node::operator==(const node &x) const{
	return this->dist == x.dist;
}

EightPuzzle::EightPuzzle()
{
	goal.resize(3);
	for(auto i = 0; i < 3; i++){
		goal.at(i).resize(3);
	}
	goal.at(0).at(0) = 1;
	goal.at(0).at(1) = 2;
	goal.at(0).at(2) = 3;
	goal.at(1).at(0) = 4;
	goal.at(1).at(1) = 5;
	goal.at(1).at(2) = 6;
	goal.at(2).at(0) = 7;
	goal.at(2).at(1) = 8;
	goal.at(2).at(2) = -1;
}

EightPuzzle::EightPuzzle(node &v)
{
	goal.resize(3);

	for(auto i = 0; i < 3; i++){
		goal.at(i).resize(3);
	}

	goal.at(0).at(0) = 1;
	goal.at(0).at(1) = 2;
	goal.at(0).at(2) = 3;
	goal.at(1).at(0) = 4;
	goal.at(1).at(1) = 5;
	goal.at(1).at(2) = 6;
	goal.at(2).at(0) = 7;
	goal.at(2).at(1) = 8;
	goal.at(2).at(2) = -1;

	frontier.push(v);
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
	return true;
}

int EightPuzzle::UniformCostSearch(){

	return -1;
}

int EightPuzzle::MisplacedTile(){

	return -1;
}

int EightPuzzle::ManhattanDistance(){

	return -1;
}

void EightPuzzle::SearchAlgorithm(int x){
	int hn = 0;
	int gn = 0;
	hn = hn +gn; // test
}
