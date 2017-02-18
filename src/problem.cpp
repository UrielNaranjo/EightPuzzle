#include "problem.h"
#include <iostream> 
#include <stdlib.h>
#include <utility>
#include <stack>

int N = 3;

node::node()
 : g(1000), h(1000), dist(1000), puzzle(""), parent(NULL)
{}

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
	return *this->parent;
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

std::string node::getPuzzle()const{
	return this->puzzle;
}

bool node::isGoal(){
    std::string goal = "123456780";
    if(this->puzzle == goal){
        return true;
    }
	return false;
}

void node::setPuzzle(const std::string &v){
    this->puzzle = v;
}

std::ostream &operator<<(std::ostream &os, const node &x){
	os << "g(n) = " << x.g << '\n';
	os << "h(n) = " << x.h << '\n';
	os << "Puzzle: \n";
	int size = N*N;
	for(auto i = 0; i < size; i++){
		os << x.puzzle.at(i);
		if((i+1)%3){
			os << " ";
		}
		else{
			os << "\n";
		}
	}
	return os;
}

void node::trace(){
	node curr = *this;
	node *minPath = &curr;
	std::stack<node> s;

	while(minPath->parent){
		s.push(*minPath);
		minPath = minPath->parent;
	}

	while(!(s.empty())){
		std::cout << s.top() << std::endl;
		s.pop();
	}
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
	if(this->puzzle == x.puzzle){
		return true;
	}
	return false;
}

int node::findBlank(){
	return this->puzzle.find('0');
}

bool node::shiftup(){
	int blank = this->findBlank();
	if(blank > (N-1)){
        int y = blank - N;
		std::swap(this->puzzle.at(blank), this->puzzle.at(y));
		return true;
	}
	return false;
}

bool node::shiftdown(){
	int blank = this->findBlank();
	if(blank < (N*2)){
        int y = blank + N;
		std::swap(this->puzzle.at(blank), this->puzzle.at(y));
		return true;
	}
	return false;
}

bool node::shiftleft(){
	int blank = this->findBlank();
	if( (blank % N) != 0){
        int y = blank - 1;
		std::swap(this->puzzle.at(blank), this->puzzle.at(y));
		return true;
	}
	return false;
} 

bool node::shiftright(){
	int blank = this->findBlank();
	if( ((blank-N+1) % N) != 0){
        int y = blank + 1;
		std::swap(this->puzzle.at(blank), this->puzzle.at(y));
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

	std::string goal = "123456780";

	for(auto i = 0; i < goal.size(); i++){
		if(this->puzzle.at(i) != goal.at(i)){
			ret++;
		}
	}
	
	return ret;
}

int getRow(int pos){
	int row = 0;
	int size = N*N;
	for(auto i = N; i <= size; i+=N){
		if( (pos >= (i-N) ) && (pos < i) ){
			row = (i / N) -1; 
			return row;
		}
	}
	return -1;
}

int getCol(int pos){
	for(auto i = 0; i < N; i++){
		if( ((pos-i) % N == 0) ){
			return i; 
		}
	}
	return -1;
}

// get distance to where value should be
// given the current location of the value
int getManDist(char value, int pos){ 
	int ret = 0;

	std::string goal = "123456780";
	int goalpos = goal.find(value);

	int	i = getRow(pos);
	int j = getCol(pos);
	int k = getRow(goalpos);
	int l = getCol(goalpos);
	ret = abs(i-k) + abs(j-l);	

	return ret;
}

int node::ManhattanDistance(){
	int ret = 0;
	int size = N*N;
	std::string goal = "123456780";
	char value = '0';
	for(auto i =0; i < size; i++){
		value = this->puzzle.at(i);
		if((value != '0') && (value != goal.at(i)) )
			ret += getManDist(value,i);	
	}
	return ret;
}

// check if the node is a repeated state
bool node::isInExplored(std::unordered_set<std::string> &v){
	if(v.find(this->getPuzzle()) == v.end()){
		return false;
	}
	return true;
}

void node::expand(std::unordered_set<std::string> &v, std::priority_queue<node, 
				std::vector<node>, std::greater<node> > &f,	int s){
	node temp = *this;
	int hn = 0;
	int gn = this->getGn() + 1; // one level deeper than current node

	if( (temp.shiftup()) && !(temp.isInExplored(v)) ){
		if(s == 1){
			hn = temp.UniformCostSearch();
		}
		else if(s == 2){
			hn = temp.MisplacedTile();
		}
		else if(s== 3){
			hn = temp.ManhattanDistance();
		}
		temp.setDist(gn, hn);
		temp.setParent(*this);
		f.push(temp);
	}

	temp = *this;
	if( (temp.shiftdown()) && !(temp.isInExplored(v)) ){
		if(s == 1){
			hn = temp.UniformCostSearch();
		}
		else if(s == 2){
			hn = temp.MisplacedTile();
		}
		else if(s == 3){
			hn = temp.ManhattanDistance();
		}
		temp.setDist(gn, hn);
		temp.setParent(*this);
		f.push(temp);
	}

	temp = *this;
	if( (temp.shiftleft()) && !(temp.isInExplored(v)) ){
		if(s == 1){
			hn = temp.UniformCostSearch();
		}
		else if(s == 2){
			hn = temp.MisplacedTile();
		}
		else if(s == 3){
			hn = temp.ManhattanDistance();
		}
		temp.setDist(gn, hn);
		temp.setParent(*this);
		f.push(temp);
	}
	
	temp =*this;
	if( (temp.shiftright()) && !(temp.isInExplored(v)) ){
		if(s == 1){
			hn = temp.UniformCostSearch();
		}
		else if(s == 2){
			hn = temp.MisplacedTile();
		}
		else if(s == 3){
			hn = temp.ManhattanDistance();
		}
		temp.setDist(gn, hn);
		temp.setParent(*this);
		f.push(temp);
	}
}
