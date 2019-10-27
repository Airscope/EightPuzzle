#include "IDSSolver.h"

namespace solver {

bool IDSSolver::IDS(const Board& first) {
	for (size_t depth = 0; ; ++depth) {
		camefrom_.clear();
		closeset_.clear();
		ClearOpenSet();
		if (DLS(first, depth))
			return true;
	}
	return false;
}

// return found
bool IDSSolver::DLS(const Board& board, int depth) {
	if (depth == 0) {
		if (board.EqualsToGoal()) {
			ReconstructPath(board);
			return true;
		}
		else 
			return false;
	}

	ids_openset_.push({ board, 0 });
	bool found = false;
	while (!ids_openset_.empty()) {
		auto current = ids_openset_.top();
		if (current.second > depth) {
			ids_openset_.pop();
			continue;
		}
		else if (current.first.EqualsToGoal()) {
			ReconstructPath(current.first);
			found = true;
			break;
		}

		ids_openset_.pop();
		auto neighbors = current.first.Neighbors();
		for (const auto& neighbor : neighbors) {
			if (closeset_.count(neighbor) == 0) {
				ids_openset_.push({ neighbor, current.second + 1 });
				camefrom_[neighbor] = current.first;
			}
		}
		closeset_.insert(current.first);
	}
	return found;
}

} // namespace solver