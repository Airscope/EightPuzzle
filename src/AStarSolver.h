#pragma once

#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>

#include "Board.h"
#include "BaseSolver.h"


namespace solver {

class AStarSolver : public BaseSolver {
private:
	HeuristicType heuristic_type_;
	Comparator GetComparator() {
		return ([&](const Board & lhs, const Board & rhs) -> bool {
			return f_[lhs] > f_[rhs];
		});
	}
	int GetHeuristic(const Board& b) {
		switch (heuristic_type_) {
		case HeuristicType::kHamming:
			return b.Hamming();
		case HeuristicType::kManhattan:
			return b.Manhattan();
		default:
			return b.Hamming();
		}
	}
public:
	AStarSolver() : heuristic_type_(kHamming) {}
	virtual bool Solve(const Board& start) override;
	void SetHeuristicType(HeuristicType t) { heuristic_type_ = t; }
};

} // namespace solver

