#include <iostream> 
#include "Problem.h"
#include <queue>

using namespace std;

bool isInExplored(node &n, vector<node> &v){
	for(auto i =0; i < v.size(); i++){
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
	temp = temp.shiftup();
	if( !(temp == n) && !(isInExplored(temp, v)) ){
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
	temp = temp.shiftdown();
	if( !(temp == n) && !(isInExplored(temp, v)) ){
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
	temp = temp.shiftleft();
	if( !(temp == n) && !(isInExplored(temp, v)) ){
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
	temp = temp.shiftright();
	if( !(temp == n) && !(isInExplored(temp, v)) ){
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

	int search = 3;
	vector<node> explored;
	priority_queue<node, vector<node>, greater<node> > frontier;

	vector<vector<int> > p = 
	{
		{1,2,3},
		{4,8,-1},
		{7,6,5}
	};

	node root, goal;
	root.setPuzzle(p);
	int gn = 0;
	int hn = 0;
	if(search == 1){
		int hn = root.UniformCostSearch();
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

	node curr;
	bool isValid = false;
	while( !(frontier.empty()) ){

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

	return 0;
}
