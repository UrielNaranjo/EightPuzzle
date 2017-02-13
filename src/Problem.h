#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <queue>

class node{

	protected:

		int dist; // g(n) + h(n)

		std::vector<std::vector<int> > puzzle; // current puzzle

		node *parent; // parent of current puzzle
	
	public:
		
		node();

		void setParent(node &);
		node getParent();		
		void setDist(int &);
		int getDist();
		const node & operator=( const node &);
		bool operator<(const node &) const;
		bool operator>(const node &) const;
		bool operator<=(const node &) const;
		bool operator>=(const node &) const;
		bool operator==(const node &) const;
};

class EightPuzzle: public node{

	private:

		std::priority_queue<node, std::vector<node>, std::greater<node> > frontier;

		std::vector<std::vector<int> > goal; // goal state

		std::vector<node> explored;

	public:

		EightPuzzle();

		EightPuzzle(node &v);

		bool shiftup();

		bool shiftdown();

		bool shiftleft();

		bool shiftright();

		int UniformCostSearch(); // heuristic function

		int MisplacedTile(); // heuristic function

		int ManhattanDistance(); // heuristic function

		void SearchAlgorithm(int x);

		bool isGoal() const; // check if we are at the goal state

		int getCost() const; // get g(n) in f(n) = g(n) + h(n)
};

#endif
