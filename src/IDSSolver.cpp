#include "IDSSolver.h"

namespace solver {

bool IDSSolver::IDS(const Board& first) {
	for (size_t depth = 0; ; ++depth) {
		camefrom_.clear();
		closeset_.clear();
		ClearOpenSet();
		auto found_remaining = DLS(first, depth);
		if (found_remaining.first)
			return true;
		else if (!found_remaining.second)
			return false;
	}
	//return false;
}
std::pair<bool, bool> IDSSolver::DLS(const Board& board, int depth) {
	if (depth == 0) {
		if (board.EqualsToGoal()) {
			ReconstructPath(board);
			return {true, true};
		}
		else
			return {false, true};
	}
	else if (depth > 0) {
		bool any_remaining = false;
		auto neighbors = board.Neighbors();
		closeset_.insert(board);
		for (const auto& neighbor : neighbors) {
			if (closeset_.count(neighbor) != 0)
				continue;

			camefrom_[neighbor] = board;
			auto found_remaining = DLS(neighbor, depth - 1);
			if (found_remaining.first) {
				// ReconstructPath(board);
				return { true, true };
			}
			if (found_remaining.second)
				any_remaining = true;
		}
		closeset_.erase(board);
		return { false, any_remaining };
	}
}


} // namespace solver
