#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>

class EightPuzzle{

	private:

		std::vector<int> puzzle;

		std::vector<int> goal;

	public:

		EightPuzzle();

		EightPuzzle(std::vector<int> &v);

		bool shiftup();

		bool shiftdown();

		bool shiftleft();

		bool shiftright();

		void UniformCostSearch();

		void MisplacedTile();

		void ManhattanDistance();

		void SearchAlgorithm(int x);

		bool isGoal() const;
};

#endif
