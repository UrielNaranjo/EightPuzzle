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

// returns the string representing the nodes puzzle
std::string node::getPuzzle()const{
	return this->puzzle;
}

// returns true if current puzzle equals the goal state puzzle
bool node::isGoal(){

    std::string goal = "";
	int size = N*N;

	for(auto i = 1; i < size; i++){
		goal+= (i+'0');
	}

	goal += '0';
    if(this->puzzle == goal){
        return true;
    }
	return false;
}

// set nodes puzzle to node v
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

// outputs the solution trace from initial state to goal state
void node::trace(){
	node curr = *this;
	node *minPath = &curr;
	std::stack<node> s;

	// put nodes on stack to output them from intial state->goal state
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

// find where the blank is in the puzzle and return its index
int node::findBlank(){
	return this->puzzle.find('0');
}

// to shift up, subtract the current position by N to get new position
// and swap the values at the current position and the new position
// only if blank is not in the first row (blank > N-1)
bool node::shiftup(){
	int blank = this->findBlank();
	if(blank > (N-1)){
        int y = blank - N;
		std::swap(this->puzzle.at(blank), this->puzzle.at(y));
		return true;
	}
	return false;
}

// to shift down, add N to the current position to get new position
// and swap the values at the current position and the new position
// only if blank is not in the bottom row (blank < N*2)
bool node::shiftdown(){
	int blank = this->findBlank();
	if(blank < (N*2)){
        int y = blank + N;
		std::swap(this->puzzle.at(blank), this->puzzle.at(y));
		return true;
	}
	return false;
}

// to shift left, subtract the current position by 1 to get new position
// and swap the values at the current position and the new position
// only if blank is not in the first col (blank % N != 0)
bool node::shiftleft(){
	int blank = this->findBlank();
	if( (blank % N) != 0){
        int y = blank - 1;
		std::swap(this->puzzle.at(blank), this->puzzle.at(y));
		return true;
	}
	return false;
} 

// to shift right, add 1 to the current position to get new position
// and swap the values at the current position and the new position
// only if blank is not in the last col ( (blank-N+1) % N != 0)
bool node::shiftright(){
	int blank = this->findBlank();
	if( ((blank-N+1) % N) != 0){
        int y = blank + 1;
		std::swap(this->puzzle.at(blank), this->puzzle.at(y));
		return true;
	}
	return false;
} 

// h(n) = 0 for uniform cost search
int node::UniformCostSearch(){
	return 0;
}

// h(n) = # of tiles not in their correct position
// excludes the blank
int node::MisplacedTile(){
	int ret = 0;

	std::string goal = "";
	int size = N*N;

	// set goal state
	for(auto i = 1; i < size; i++){
		goal+= (i+'0');
	}
	goal += '0';

	for(auto i = 0; i < goal.size(); i++){
		if(this->puzzle.at(i) != goal.at(i)){
			ret++; // increment if the values at i are not equal
		}
	}
	
	return ret;
}

// Convert string position to the row position if
// the puzzle was represented by a 2d array instead of a string
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

// Convert string position to the col position if
// the puzzle was represeted by a 2d array instead of a string
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
int getManDistHelper(char value, int pos){ 
	int ret = 0;

	std::string goal = "";
	int size = N*N;

	// set goal state
	for(auto i = 1; i < size; i++){
		goal+= (i+'0');
	}
	goal += '0';

	// get values position in the string
	int goalpos = goal.find(value);

	// get 2D position of the values position in the current puzzle state
	int	i = getRow(pos);
	int j = getCol(pos);
	
	// get 2D position of the values position in the goal state
	int k = getRow(goalpos);
	int l = getCol(goalpos);

	// calculate manhattan distance of value
	ret = abs(i-k) + abs(j-l);	

	return ret;
}

// get the h(n) distance using the Manhattan Distance
int node::ManhattanDistance(){
	int ret = 0;
	int size = N*N;
	std::string goal = "";

	// set goal state
	for(auto i = 1; i < size; i++){
		goal+= (i+'0');
	}
	goal += '0';

	char value = '0'; // ignore blank
	for(auto i =0; i < size; i++){
		value = this->puzzle.at(i); // current value at i

		// if not blank and not equal to goal state value at i
		// find manhattan distance
		if((value != '0') && (value != goal.at(i)) )
			ret += getManDistHelper(value,i);	
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

	// if shift up is valid and node is not in the explored state
	// add it to the frontier
	if( (temp.shiftup()) && !(temp.isInExplored(v)) ){
		// get h(n) for corresponding heuristic
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
	// if shift down is valid and node is not in the explored state
	// add it to the frontier
	if( (temp.shiftdown()) && !(temp.isInExplored(v)) ){
		// get h(n) for corresponding heuristic
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
	// if shift left is valid and node is not in the explored state
	// add it to the frontier
	if( (temp.shiftleft()) && !(temp.isInExplored(v)) ){
		// get h(n) for corresponding heuristic
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
	// if shift right is valid and node is not in the explored state
	// add it to the frontier
	if( (temp.shiftright()) && !(temp.isInExplored(v)) ){
		// get h(n) for corresponding heuristic
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
