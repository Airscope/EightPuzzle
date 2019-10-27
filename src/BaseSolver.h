#pragma once

#include <algorithm>
#include <stack>
#include <vector>
#include <unordered_map>
#include <functional>
#include <unordered_set>

#include "Board.h"

namespace solver {

typedef	std::function<bool(const Board&, const Board&)> Comparator;

class OpenSet : public std::vector<Board> {
private:
	Comparator comparator_;
public:
	OpenSet() {};
	void Initialize(Comparator c) {
		comparator_ = c;
		std::make_heap(this->begin(), this->end(), comparator_);
	}
	void Push(const Board& b) {
		this->push_back(b);
		std::push_heap(this->begin(), this->end(), comparator_);
	}
	void Push(Board&& b) {
		this->push_back(std::move(b));
		std::push_heap(this->begin(), this->end(), comparator_);
	}
	void Pop() {
		std::pop_heap(this->begin(), this->end(), comparator_);
		this->pop_back();
	}
	Board Top() {
		return this->at(0);
	}
	bool Contains(const Board& b) {
		return !(std::find(this->begin(), this->end(), b) == this->end());
	}
};

class BaseSolver {
public:
	enum HeuristicType {
		kHamming,
		kManhattan
	};

protected:	
	OpenSet openset_;
	std::stack<Board> solution_;
	std::unordered_map<Board, int> f_;
	std::unordered_map<Board, int> g_;
	std::unordered_map<Board, Board> camefrom_;
	std::unordered_set<Board> closeset_;

	void ReconstructPath(const Board& current) {
		auto copy = current;
		solution_.push(copy);
		while (camefrom_.count(copy) != 0) {
			copy = camefrom_[copy];
			solution_.push(copy);
		}
	}

public:
	virtual bool Solve(const Board& start) = 0;
	virtual void PrintSolution() {
		auto tmp = solution_;
		while (!tmp.empty()) {
			tmp.top().Print();
			tmp.pop();
		}
	}
	std::stack<Board> GetSolution() const { return solution_; }
};

} // namespace solver


