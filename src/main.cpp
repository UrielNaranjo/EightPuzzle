#include <iostream> 
#include "problem.h"
#include <unordered_set>
#include <queue>

using namespace std;

// check if the node is a repeated state
bool isInExplored(node &n, unordered_set<string> &v){
	if(v.find(n.getHash()) == v.end()){
		return false;
	}
	return true;
}

// expand nodes with legal operations and add them to the frontier
// if they are not a repeated state
void expand(node &n, unordered_set<string> &v, priority_queue<node, vector<node>, 
				greater<node> > &f,	int s){
	node temp = n;
	int hn = 0;
	int gn = n.getGn() + 1; // one level deeper than current node

	if( (temp.shiftup()) && !(isInExplored(temp, v)) ){
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
		temp.setParent(n);
		f.push(temp);
	}

	temp = n;
	if( (temp.shiftdown()) && !(isInExplored(temp, v)) ){
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
		temp.setParent(n);
		f.push(temp);
	}

	temp =n;
	if( (temp.shiftleft()) && !(isInExplored(temp, v)) ){
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
		temp.setParent(n);
		f.push(temp);
	}

	temp = n;
	if( (temp.shiftright()) && !(isInExplored(temp, v)) ){
		if(s == 1){
			hn = temp.UniformCostSearch();
		}
		else if(s== 2){
			hn = temp.MisplacedTile();
		}
		else if(s == 3){
			hn = temp.ManhattanDistance();
		}
		temp.setDist(gn, hn);
		temp.setParent(n);
		f.push(temp);
	}
}

int main(int argc, char **argv){

	int search = 1; // heuristic funtion to be used. Default is 1
	int gn = 0; // g(n) for root node 
	int hn = 0; // h(n) varies depending on heuristic
	unsigned int maxnodes = 1; // initially we have one node in queue
	node curr; // current node we are expanding
	node root, goal; // initial node we get from input
	bool isValid = false; // set to true if we find a goal state
	unordered_set<string> explored; // explored set of nodes
	vector<int> tmprow(3);
	vector<vector<int> > p; // initial puzzle state 
	priority_queue<node, vector<node>, greater<node> > frontier;

	// prompt user for initial puzzle and choice of algorithm
	cout << "Welcome to Uriel Naranjo's 8-puzzle solver." << endl << endl;
	cout << "Enter your puzzle, use '0' to represent the blank." << endl << endl;

	cout << "Enter the first row, use space or tabs between numbers." << endl;
	for(auto i = 0; i < 3; i++){
		cin >> tmprow.at(i); 
	}
	p.push_back(tmprow);

	cout << "Enter the second row, use space or tabs between numbers." << endl;
	for(auto i = 0; i < 3; i++){
		cin >> tmprow.at(i);
	}
	p.push_back(tmprow);

	cout << "Enter the third row, use space or tabs between numbers." << endl;
	for(auto i = 0; i < 3; i++){
		cin >> tmprow.at(i);
	}
	p.push_back(tmprow);

	cout << "\nEnter your choice of algorithm" << endl;
	cout << "\t1. Uniform Cost Search" << endl;
	cout << "\t2. A* with Misplaced Tile heuristic" << endl;
	cout << "\t3. A* with the Manhattan distance heurstic." << endl << endl;

	cin >> search;

	// initialize initial state
	root.setPuzzle(p);
	if(search == 1){
		hn = root.UniformCostSearch();
		root.setDist(gn,hn);
	}
	else if(search == 2){
		hn = root.MisplacedTile();
		root.setDist(gn, hn);
	}
	else if(search == 3){
		hn = root.ManhattanDistance();
		root.setDist(gn, hn);
	}

	frontier.push(root);

	// A* search algorithm
	while( !(frontier.empty()) ){

		// keep track of max nodes in frontier
		if(frontier.size() > maxnodes){
			maxnodes = frontier.size();
		}

		// get next node to expand
		curr = frontier.top();
		frontier.pop();

		// check if we have a goal state
		// if we do then we are done
		if(curr.isGoal()){
			goal = curr;
			isValid = true;
			break;
		}

		cout << "The best state to expand is: " << endl;
		cout << curr;
		cout << "Expanding this node..." << endl << endl;

		// add node to explored
		explored.insert(curr.getHash());

		// expand the node using operations available
		expand(curr, explored, frontier, search);
	}

	if(!isValid){
		cerr << "\nThe puzzle is not solvable with the given initial state." << endl;
	}
	else{
		cout << "\nYou've reached the end goal!!" << endl;
	}

	cout << endl << "To solve this problem the search algorithm expanded a total of ";
	cout << explored.size() << " nodes." << endl;
	cout << "The maximum number of nodes in the queue at any one time was ";
	cout << maxnodes << " nodes"<< endl;
	cout << "The depth of the goal node was " << goal.getGn() << "." << endl;

	return 0;
}
