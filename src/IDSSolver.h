#pragma once
#include <stack>
#include "BaseSolver.h"
#include "Board.h"

namespace solver {

class IDSSolver : public BaseSolver {
public:
	virtual bool Solve(const Board& first) override { 
		if (!first.Solvable()) {
			std::cerr << "Unsolvable Board.\n";
			return false;
		}
		return IDS(first); 
	};

private:
	bool IDS(const Board& first);
	std::pair<bool, bool> DLS(const Board& board, int depth);
	std::stack<std::pair<Board, int>> ids_openset_;
	void ClearOpenSet() {
		while (!ids_openset_.empty()) {
			ids_openset_.pop();
		}
	}
};

} // namespace solver


