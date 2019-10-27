#include "GreedySolver.h"

namespace solver {
	bool GreedySolver::Solve(const Board& start) {
		if (!start.Solvable()) {
			std::cerr << "Unsolvable Board." << std::endl;
			return false;
		}
		openset_.clear();
		camefrom_.clear();
		closeset_.clear();
		f_.clear();
		g_.clear();
		openset_.Initialize(GetComparator());
		openset_.Push(start);
		g_[start] = 0;
		f_[start] = GetHeuristic(start);
		while (!openset_.empty()) {
			Board current = openset_.Top();
			if (current.EqualsToGoal()) {
				ReconstructPath(current);
				return true;
			}
			openset_.Pop();
			auto neighbors = current.Neighbors();
			for (const auto& neighbor : neighbors) {
				if (g_.count(neighbor) == 0)
					g_[neighbor] = 9999999; // inf
				if (f_.count(neighbor) == 0)
					f_[neighbor] = 9999999; // inf
			}
			for (const auto& neighbor : neighbors) {
				f_[neighbor] = GetHeuristic(neighbor);
				if (closeset_.count(neighbor) == 0) {
					camefrom_[neighbor] = current;
					openset_.Push(std::move(neighbor));
				}
			}
			closeset_.insert(current);
		}
		return false;
	}

} // namespace solver
