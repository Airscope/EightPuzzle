#pragma once
#include "BaseSolver.h"
#include "Board.h"

namespace solver {

class GreedySolver : public BaseSolver {
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
	GreedySolver() : heuristic_type_(kHamming) {}
	void SetHeuristicType(HeuristicType t) { heuristic_type_ = t; }
	virtual bool Solve(const Board& first) override;
};

} // namespace solver



