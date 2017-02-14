#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>

class node{

	private:
		int g; // distance from initial node
		int h; // heuristic distance
		int dist; // g(n) + h(n)
		std::vector<std::vector<int> > puzzle; // current puzzle
		node *parent; // parent of current puzzle
	
	public:
		
		node();

		node getParent();		
		int getDist();
		int getGn();
		int getHn();
		void setDist(int, int);
		void setParent(node &);
		void setPuzzle(const std::vector<std::vector<int> > &);
		bool isGoal();
		std::pair<int,int> findBlank();

		const node & operator=( const node &);
		bool operator<(const node &) const;
		bool operator>(const node &) const;
		bool operator<=(const node &) const;
		bool operator>=(const node &) const;
		bool operator==(const node &) const;

		friend std::ostream &operator<<(std::ostream &os, const node &);

		node shiftup();
		node shiftdown();
		node shiftleft();
		node shiftright();

		int UniformCostSearch(); // heuristic function
		int MisplacedTile(); // heuristic function
		int ManhattanDistance(); // heuristic function
};

#endif
