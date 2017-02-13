#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <queue>

class node{

	protected:
		int dist; // g(n) + h(n)
		std::vector<std::vector<int> > puzzle; // current puzzle
		std::vector<node> explored;
		node *parent; // parent of current puzzle
	
	public:
		
		node();

		node getParent();		
		int getDist();
		void setDist(int &);
		void setParent(node &);

		const node & operator=( const node &);
		bool operator<(const node &) const;
		bool operator>(const node &) const;
		bool operator<=(const node &) const;
		bool operator>=(const node &) const;
		bool operator==(const node &) const;

		bool shiftup();
		bool shiftdown();
		bool shiftleft();
		bool shiftright();

		int UniformCostSearch(const node &); // heuristic function
		int MisplacedTile(const node&); // heuristic function
		int ManhattanDistance(const node&); // heuristic function


};

#endif
