#include <iostream>
#include <numeric>
#include <ctime>

#include "Board.h"
#include "AStarSolver.h"
#include "GreedySolver.h"
#include "IDSSolver.h"

int main() {
	using solver::BaseSolver;
	using solver::AStarSolver;
	using solver::GreedySolver;
	using solver::Board;
	using solver::IDSSolver;

	int count = 1000;
	AStarSolver astarsolver;
	GreedySolver greedysolver;
	IDSSolver idssolver;

	std::vector<clock_t> astar_times_hamming, astar_times_manhattan, greedy_times, ids_times;
	clock_t start_time, finish_time;
	while (count--) {
		auto start = new Board;
		std::cout << "Generate a solvable random 8-puzzle...\n";
		while (!start->Solvable()) {
			start->Randomize();
		}
		start->Print();

		std::cout << "AStar (Heuristic = Hamming) solving...\n";
		astarsolver.SetHeuristicType(BaseSolver::HeuristicType::kHamming);
		start_time = clock();
		astarsolver.Solve(*start);
		finish_time = clock();
		astar_times_hamming.push_back(finish_time - start_time);
		std::cout << "AStar (Heuristic = Hamming) time used: " 
                  << double(finish_time - start_time) / CLOCKS_PER_SEC 
                  << " seconds.\n";

		std::cout << "AStar (Heuristic = Manhattan) solving...\n";
		astarsolver.SetHeuristicType(BaseSolver::HeuristicType::kManhattan);
		start_time = clock();
		astarsolver.Solve(*start);
		finish_time = clock();
		astar_times_manhattan.push_back(finish_time - start_time);
		std::cout << "AStar (Heuristic = Manhattan) time used: "
                  << double(finish_time - start_time) / CLOCKS_PER_SEC 
                  << " seconds.\n";

		std::cout << "Greedy solving...\n";
		start_time = clock();
		greedysolver.Solve(*start);
		finish_time = clock();
		greedy_times.push_back(finish_time - start_time);
		std::cout << "Greedy time used: "
                  << double(finish_time - start_time) / CLOCKS_PER_SEC 
                  << " seconds.\n";

		std::cout << "IDS solving...\n";
		start_time = clock();
		idssolver.Solve(*start);
		finish_time = clock();
		ids_times.push_back(finish_time - start_time);
		std::cout << "IDS time used: "
                  << double(finish_time - start_time) / CLOCKS_PER_SEC 
                  << " seconds.\n\n";

		delete start;
	}

	std::cout << "AStar (Heuristic = Hamming) average solving time: " 
              << std::accumulate(astar_times_hamming.begin(), astar_times_hamming.end(), 0) /
                (double)astar_times_hamming.size() / CLOCKS_PER_SEC 
              << " seconds.\n";

	std::cout << "AStar (Heuristic = Manhattan) average solving time: " 
              << std::accumulate(astar_times_manhattan.begin(), astar_times_manhattan.end(), 0) / 
                (double)astar_times_manhattan.size() / CLOCKS_PER_SEC 
              << " seconds.\n";

	std::cout << "Greedy average solving time: " 
              << std::accumulate(greedy_times.begin(), greedy_times.end(), 0) / 
                (double)greedy_times.size() / CLOCKS_PER_SEC
              << " seconds.\n";

	std::cout << "IDS average solving time: " 
              << std::accumulate(ids_times.begin(), ids_times.end(), 0) / 
                (double)ids_times.size() / CLOCKS_PER_SEC
              << " seconds.\n";
	
	return 0;
}
