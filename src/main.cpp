#include <iostream> 
#include "Problem.h"
#include <unordered_set>
#include <queue>

using namespace std;

bool isInExplored(node &n, vector<node> &v){
	for(auto i = 0; i < v.size(); i++){
			if(n == v.at(i)){
				return true;
			}
	}
	return false;
}

void expand(node &n, vector<node> &v, priority_queue<node, vector<node>, greater<node> > &f,
				int s){
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
	int maxnodes = 1; // initially we have one node in queue
	node curr; // current node we are expanding
	node root, goal; // initial node we get from input
	bool isValid = false; // set to true if we find a goal state
	vector<node> explored; // explored set of nodes
	vector<vector<int> > p; // initial puzzle state 
	priority_queue<node, vector<node>, greater<node> > frontier;

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

	while( !(frontier.empty()) ){

		if(frontier.size() > maxnodes){
			maxnodes = frontier.size();
		}

		curr = frontier.top();
		frontier.pop();

		if(curr.isGoal()){
			goal = curr;
			isValid = true;
			break;
		}

		cout << "The best state to expand is: " << endl;
		cout << curr;
		cout << "Expanding this node..." << endl << endl;

		explored.push_back(curr);
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
