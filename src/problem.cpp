#include "Problem.h"
#include <iostream> 
#include <stdlib.h>
#include <utility>

node::node()
 : g(1000), h(1000), dist(1000), parent(NULL)
{
	puzzle.resize(3);
	for(auto i = 0; i < 3; i++){
		puzzle.at(i).resize(3);
	}
}

const node & node::operator=(const node &r){
	this->g = r.g;
	this->h = r.h;
	this->dist = r.dist;
	this->parent = r.parent;
	this->setPuzzle(r.puzzle);
	return *this;
}

void node::setParent(node &x){
	this->parent = &x;	
}

node node::getParent(){
	node temp = *parent;
	return temp;
}

void node::setDist(int gn, int hn){
	this->g = gn; 
	this->h = hn;
	this->dist = gn + hn;
}

int node::getGn(){
	return this->g;
}

int node::getHn(){
	return this->h;
}

int node::getDist(){
	return this->dist;
}

bool node::isGoal(){
	
	std::vector<std::vector<int> > goal = 
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, -1}
	};

	int current;
	for(auto i = 0; i < 3; i++){
		for(auto j = 0; j < 3; j++){
			current = this->puzzle.at(i).at(j);
			if( (current != goal.at(i).at(j) )  ){ 
				return false;
			}
		}
	}

	return true;
}

void node::setPuzzle(const std::vector<std::vector<int> > &v){
	for(auto i =0; i < 3; i++){
		for(auto j = 0; j < 3; j++){
			this->puzzle.at(i).at(j) = v.at(i).at(j);
		}
	}
}

std::ostream &operator<<(std::ostream &os, const node &x){
	os << "g(n) = " << x.g << '\n';
	os << "h(n) = " << x.h << '\n';
	os << "Puzzle: \n";
	for(auto i = 0; i < 3; i++){
		for(auto j = 0; j <3; j++){
			os << x.puzzle.at(i).at(j) << ((j != 3) ? " " : "");
		}
		os << '\n';
	}
	return os;
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
	for(auto i = 0; i < 3; i++){
		for(auto j = 0; j < 3; j++){
			if(this->puzzle.at(i).at(j) != x.puzzle.at(i).at(j)){
				return false;
			}
		}
	}
	return true;
}

std::pair<int,int> node::findBlank(){
	std::pair<int,int> ret(0,0);
	for(auto i = 0; i < 3; i++){
		for(auto j = 0; j < 3; j++){
			if(this->puzzle.at(i).at(j) == -1){
				ret.first = i;
				ret.second = j;
				return ret;
			}
		}
	}
	return ret;
}

bool node::shiftup(){
	std::pair<int,int> blank = this->findBlank();
	int i = blank.first;
	int j = blank.second;
	if(i != 0){
		std::swap(this->puzzle.at(i).at(j), this->puzzle.at(i-1).at(j));
		return true;
	}
	return false;
}

bool node::shiftdown(){
	std::pair<int,int> blank = this->findBlank();
	int i = blank.first;
	int j = blank.second;
	if(i != 2){
		std::swap(this->puzzle.at(i).at(j), this->puzzle.at(i+1).at(j));
		return true;
	}
	return false;
}

bool node::shiftleft(){
	std::pair<int,int> blank = this->findBlank();
	int i = blank.first;
	int j = blank.second;
	if(j != 0){
		std::swap(this->puzzle.at(i).at(j), this->puzzle.at(i).at(j-1));
		return true;
	}
	return false;
} 

bool node::shiftright(){
	std::pair<int,int> blank = this->findBlank();
	int i = blank.first;
	int j = blank.second;
	if(j != 2){
		std::swap(this->puzzle.at(i).at(j), this->puzzle.at(i).at(j+1));
		return true;
	}
	return false;
} 

int node::UniformCostSearch(){
	// h(n) = 0 for uniform cost search
	return 0;
}

int node::MisplacedTile(){
	int ret = 0;
	int current = 0;
	std::vector<std::vector<int> > goal = 
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, -1}
	};

	for(auto i = 0; i < 3; i++){
		for(auto j = 0; j < 3; j++){
			current = this->puzzle.at(i).at(j);
			if( (current != goal.at(i).at(j) ) && (current != -1) ){ 
				ret++;
			}
		}
	}
	return ret;
}

// get distance to where value should be
// given the current location of the value
int getManDist(int i, int j, int value){ 
	int ret = 0;
	if(value == 1){
		if(i != 0){
			ret+=i;	
		}
		if(j != 0){
			ret+=j;
		}
	}
	else if(value == 2){
		if(i != 0){
			ret+=i;	
		}
		if(j != 1){
			ret+= abs(j-1);
		}
	}
	else if(value == 3){
		if(i != 0){
			ret+=abs(i-2);	
		}
		if(j != 2){
			ret+=j;
		}
	}
	else if(value == 4){
		if(i != 1){
			ret+=abs(i-1);	
		}
		if(j != 0){
			ret+=j;
		}
	}
	else if(value == 5){
		if(i != 1){
			ret+=abs(i-1);	
		}
		if(j != 1){
			ret+=abs(j-1);
		}
	}
	else if(value == 6){
		if(i != 1){
			ret+=abs(i-1);	
		}
		if(j != 2){
			ret+=abs(j-2);
		}
	}
	else if(value == 7){
		if(i != 2){
			ret+=abs(i-2);	
		}
		if(j != 0){
			ret+=j;
		}
	}
	else if(value == 8){
		if(i != 2){
			ret+= abs(i-2);	
		}
		if(j != 1){
			ret+=abs(j-1);
		}
	}
	return ret;
}

int node::ManhattanDistance(){
	int ret = 0;
	for(auto i =0; i < 3; i++){
		for(auto j=0; j<3; j++){
			if(this->puzzle.at(i).at(j) != -1){
				ret += getManDist(i, j, this->puzzle.at(i).at(j));
			}
		}
	}
	return ret;
}
