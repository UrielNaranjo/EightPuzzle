#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

extern int N; // NxN puzzle

class node{

	private:
		int g; // distance from initial node
		int h; // heuristic distance
		int dist; // g(n) + h(n)
		std::string puzzle; // puzzle of node
		node *parent; // parent of current puzzle
	
	public:
		
		node();

		node getParent();		
		int getDist();
		int getGn();
		int getHn();
		std::string getPuzzle() const;
		void setDist(int, int);
		void setParent(node &);
		void setPuzzle(const std::string &);
		bool isGoal();
		int findBlank(); // returns the position of the blank in the string
		void trace(); // prints the trace of the solution 

		// operator overloads for output and comparisons
		// comparisons only compare the nodes dist
		const node & operator=( const node &);
		bool operator<(const node &) const;
		bool operator>(const node &) const;
		bool operator<=(const node &) const;
		bool operator>=(const node &) const;
		bool operator==(const node &) const;

		friend std::ostream &operator<<(std::ostream &os, const node &);

		// state operators
		bool shiftup();
		bool shiftdown();
		bool shiftleft();
		bool shiftright();

		int UniformCostSearch(); // heuristic function
		int MisplacedTile(); // heuristic function
		int ManhattanDistance(); // heuristic function
		
		// checks if node is in the explored set
		bool isInExplored(std::unordered_set<std::string> &);

		// expand current node by applying all valid state operators
		void expand(std::unordered_set<std::string> &v, 
						std::priority_queue<node, std::vector<node>, 
									std::greater<node> > &f, int s);
};

#endif
