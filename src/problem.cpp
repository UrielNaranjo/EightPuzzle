#include "Problem.h"

node::node()
 : dist(0), parent(NULL)
{}

const node & node::operator=(const node &r){
	this->dist = r.dist;
	this->parent = r.parent;
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

bool node::shiftup(){

	return true;
}

bool node::shiftdown(){

	return true;
}

bool node::shiftleft(){

	return true;
} 

bool node::shiftright(){

	return true;
} 

int node::UniformCostSearch(const node &curr){
	// h(n) = 0 for uniform cost search
	return 0;
}

int node::MisplacedTile(const node &curr){
	int ret = 0;
	int current = 0;
	std::vector<std::vector<int> > goal = 
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, -1}
	};
	for(auto i = 0; i < 3; i++){
		for(auto j = 0; j < 3; i++){
			current = curr.puzzle.at(i).at(j);
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
			ret+=j;
		}
	}
	else if(value == 3){
		if(i != 2){
			ret+=i;	
		}
		if(j != 0){
			ret+=j;
		}
	}
	else if(value == 4){
		if(i != 1){
			ret+=i;	
		}
		if(j != 0){
			ret+=j;
		}
	}
	else if(value == 5){
		if(i != 1){
			ret+=i;	
		}
		if(j != 1){
			ret+=j;
		}
	}
	else if(value == 6){
		if(i != 1){
			ret+=i;	
		}
		if(j != 2){
			ret+=j;
		}
	}
	else if(value == 7){
		if(i != 2){
			ret+=i;	
		}
		if(j != 0){
			ret+=j;
		}
	}
	else if(value == 8){
		if(i != 2){
			ret+=i;	
		}
		if(j != 1){
			ret+=j;
		}
	}
	return ret;
}

int node::ManhattanDistance(const node &curr){
	int ret = 0;
	for(auto i =0; i < 3; i++){
		for(auto j=0; j<3; j++){
			if(curr.puzzle.at(i).at(j) != -1){
				ret += getManDist(i, j, curr.puzzle.at(i).at(j));
			}
		}
	}
	return ret;
}
