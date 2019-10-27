#pragma once

#include <random>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>


namespace solver {

class Board {

private:
	std::vector<int> vec_;


public:
	
	Board() : vec_(9, 0) {
		srand(static_cast<unsigned int>(time(nullptr)));
		Randomize();
	}
	explicit Board(std::vector<int> v) : vec_(v) {}

	inline bool operator==(const Board& other) const {
		return vec_ == other.vec_;
	}

	std::string ToString() const {
		std::ostringstream oss;
		for (size_t i = 0; i < vec_.size(); i++) {
			oss << vec_[i];
		}
		return oss.str();
	}

	bool EqualsToGoal() const {
		for (int i = 0; i < vec_.size()-1; i++) {
			if (vec_[i] != i + 1) return false;
		}
		return true;
	}

	int Hamming() const;
	int Manhattan() const;
	void Randomize();

	inline int Dist(const Board& neighbor) { return 1; }

	Board Swap(size_t pos1, size_t pos2) const {
		Board ret(*this);
		std::swap(ret.vec_[pos1], ret.vec_[pos2]);
		return ret;
	}

	void Print();

	bool Solvable() const;

	std::vector<Board> Neighbors() const;
};

} // namespace solver

namespace std {

template<>
struct hash<solver::Board> {
	std::size_t operator()(const solver::Board &key) const {
		return (hash<std::string>()(key.ToString()));
	}
};

}// namespace std
