#include "problem.h"
#include <iostream> 
#include <stdlib.h>
#include <utility>

node::node()
 : g(1000), h(1000), dist(1000), hashstr(""), parent(NULL)
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

std::string node::getHash()const{
	return this->hashstr;
}

bool node::isGoal(){
	
    std::string goal = "123456780";
    if(this->hashstr != goal){
        return false;
    }
	return true;
}

void node::setPuzzle(const std::vector<std::vector<int> > &v){
    std::string tmp = "";
	for(auto i =0; i < 3; i++){
		for(auto j = 0; j < 3; j++){
			this->puzzle.at(i).at(j) = v.at(i).at(j);
			tmp += v.at(i).at(j) + '0';
		}
	}
    this->hashstr = tmp;
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
	if(this->hashstr == x.hashstr){
		return true;
	}
	return false;
}

std::pair<int,int> node::findBlank(){
	std::pair<int,int> ret(0,0);
	for(auto i = 0; i < 3; i++){
		for(auto j = 0; j < 3; j++){
			if(this->puzzle.at(i).at(j) == 0){
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
        int x = i*3+j;
        int y = x - 3;
		std::swap(this->puzzle.at(i).at(j), this->puzzle.at(i-1).at(j));
		std::swap(this->hashstr.at(x), this->hashstr.at(y));
		return true;
	}
	return false;
}

bool node::shiftdown(){
	std::pair<int,int> blank = this->findBlank();
	int i = blank.first;
	int j = blank.second;
	if(i != 2){
        int x = i*3+j;
        int y = x + 3;
		std::swap(this->puzzle.at(i).at(j), this->puzzle.at(i+1).at(j));
		std::swap(this->hashstr.at(x), this->hashstr.at(y));
		return true;
	}
	return false;
}

bool node::shiftleft(){
	std::pair<int,int> blank = this->findBlank();
	int i = blank.first;
	int j = blank.second;
	if(j != 0){
        int x = i*3+j;
        int y = x - 1;
		std::swap(this->puzzle.at(i).at(j), this->puzzle.at(i).at(j-1));
		std::swap(this->hashstr.at(x), this->hashstr.at(y));
		return true;
	}
	return false;
} 

bool node::shiftright(){
	std::pair<int,int> blank = this->findBlank();
	int i = blank.first;
	int j = blank.second;
	if(j != 2){
        int x = i*3+j;
        int y = x + 1;
		std::swap(this->puzzle.at(i).at(j), this->puzzle.at(i).at(j+1));
		std::swap(this->hashstr.at(x), this->hashstr.at(y));
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
	int current = -1;
	std::vector<std::vector<int> > goal = 
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 0}
	};

	for(auto i = 0; i < 3; i++){
		for(auto j = 0; j < 3; j++){
			current = this->puzzle.at(i).at(j);
			if( (current != goal.at(i).at(j) ) && (current != 0) ){ 
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
			if(this->puzzle.at(i).at(j) != 0){
				ret += getManDist(i, j, this->puzzle.at(i).at(j));
			}
		}
	}
	return ret;
}
