#include <iostream> 
#include "Problem.h"
#include <queue>

using namespace std;

int main(int argc, char **argv){

	vector<node> explored;
	priority_queue<node, vector<node>, greater<node> > frontier;
	vector<vector<int> > p = 
	{
		{1,2,3},
		{4,8,-1},
		{7,6,5}
	};

	node root;
	root.setPuzzle(p);

	frontier.push(root);
	// int gn = 1; // initial g(n) distance
	root.setDist(root.ManhattanDistance());
	cout << root << endl;
	root.setDist(root.MisplacedTile());
	cout << root << endl;
	/*while( !(frontier.empty()) ){
			
	}*/
	return 0;
}
