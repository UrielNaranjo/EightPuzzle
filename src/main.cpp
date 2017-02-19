#include <iostream> 
#include <unordered_set>
#include <queue>
#include "problem.h"

using namespace std;

int main(int argc, char **argv){

	int search = 1; // heuristic funtion to be used. Default is 1
	int def = 1; // 1 is default puzzle. 2 is custom puzzle
	int gn = 0; // g(n) for root node 
	int hn = 0; // h(n) varies depending on heuristic
	unsigned int maxnodes = 1; // initially we have one node in queue
	node root, goal; // initial node we get from input
	bool isValid = false; // set to true if we find a goal state
	unordered_set<string> explored; // explored set of nodes
	vector<int> tmprow(3);
	string p = ""; // initial puzzle state 
	char num;
	priority_queue<node, vector<node>, greater<node> > frontier; // frontier
	vector<node*> expanded;  // allocate nodes in memory to keep track of address

	// prompt user for initial puzzle and choice of algorithm
	cout << "Welcome to Uriel Naranjo's 8-puzzle solver." << endl << endl;
	cout << "Type '1' to use default puzzle, or '2' to enter your own puzzle." << endl;
	cin >> def;
	cout << endl;

	// custom initial state
	if(def == 2){
		cout << "Enter your puzzle, use '0' to represent the blank." << endl << endl;
		cout << "Enter the first row, use space or tabs between numbers." << endl;
		for(auto i = 0; i < 3; i++){
			cin >> num; 
			p+=num;
		}

		cout << "Enter the second row, use space or tabs between numbers." << endl;
		for(auto i = 0; i < 3; i++){
			cin >> num;
			p+=num;
		}

		cout << "Enter the third row, use space or tabs between numbers." << endl;
		for(auto i = 0; i < 3; i++){
			cin >> num;
			p+=num;
		}
	}
	// default puzzle
	else{
		p = "123480765";
	}

	cout << "\nEnter your choice of algorithm" << endl;
	cout << "\t1. Uniform Cost Search" << endl;
	cout << "\t2. A* with Misplaced Tile heuristic" << endl;
	cout << "\t3. A* with the Manhattan distance heurstic." << endl << endl;

	cin >> search;

	// initialize initial puzzle state 
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
		node *curr = new node(frontier.top()); // current node we are expanding
		expanded.push_back(curr);
		frontier.pop();

		// check if we have a goal state
		// if we do then we are done
		if(curr->isGoal()){
			goal = *expanded.at(expanded.size() - 1);
			isValid = true;
			break;
		}

		// add node to explored
		explored.insert(curr->getPuzzle());

		// expand the node using operations available
		expanded.at(expanded.size() -1)->expand(explored, frontier, search);
	}

	// if solution is not found, print intial puzzle and error message
	if(!isValid){
		cerr << "\nThe puzzle is not solvable with the given initial state:" << endl;
		cout << root << endl;
	}
	else{
		cout << "\nYou've reached the end goal!!" << endl;

		cout << "The following is the solution trace from initial state to goal state: \n\n";

		// print solution trace
		cout << root << endl;
		goal.trace();

		cout << endl << "To solve this problem the search algorithm expanded a total of ";
		cout << explored.size() << " nodes." << endl;
		cout << "The maximum number of nodes in the queue at any one time was ";
		cout << maxnodes << " nodes"<< endl;
		cout << "The depth of the goal node was " << goal.getGn() << "." << endl;
	}	

	// deallocate memory
	for(auto i = 0; i < expanded.size(); i++){
		delete expanded.at(i);
	}
	
	return 0;
}
