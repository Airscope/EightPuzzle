#include "Board.h"
#include <algorithm>

namespace solver {

void Board::Print() {
	std::cout << "-------\n";
	int tmp;
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			std::cout << "|";
			tmp = vec_[i * 3 + j];
			if (tmp) std::cout << tmp;
			else std::cout << " ";
		}
		std::cout << "|\n-------\n";
	}
}

bool Board::Solvable() const {
	int count = 0;
	for (size_t i = 0; i < vec_.size(); ++i) {
		for (size_t j = i + 1; j < vec_.size(); ++j) {
			if (vec_[i] != 0 && vec_[j] != 0 && vec_[i] > vec_[j])
				++count;
		}
	}
	return count % 2 == 0;
}

std::vector<Board> Board::Neighbors() const {
	std::vector<Board> ret;
	size_t emptypos = std::find(vec_.begin(), vec_.end(), 0) - vec_.begin();
	size_t row = emptypos / 3, col = emptypos % 3;
	if (row > 0)
		ret.push_back(Swap(3 * (row - 1) + col, emptypos));
	if (row < 2)
		ret.push_back(Swap(3 * (row + 1) + col, emptypos));
	if (col > 0)
		ret.push_back(Swap(3 * row + col - 1, emptypos));
	if (col < 2)
		ret.push_back(Swap(3 * row + col + 1, emptypos));
	return ret;
}

int Board::Hamming() const {
	int count = 0;
	for (size_t i = 0; i < vec_.size(); i++) {
		if (vec_[i] != i + 1 && vec_[i] != 0)
			++count;
	}
	return count;
}

int Board::Manhattan() const {
	int count = 0, ideal_row, ideal_col, real_row, real_col;
	for (size_t i = 0; i < vec_.size(); i++) {
		if (vec_[i] != 0) {
			ideal_row = (vec_[i] - 1) / 3;
			ideal_col = (vec_[i] - 1) % 3;
			real_row = i / 3;
			real_col = i % 3;
			count += abs(ideal_row - real_row) + abs(ideal_col - real_col);
		}
	}
	return count;
}

void Board::Randomize() {
	
	for (size_t i = 0; i < vec_.size(); i++) {
		vec_[i] = i;
	}
	for (size_t i = 0; i < vec_.size(); i++) {
		std::swap(vec_[i], vec_[rand() % vec_.size()]);
	}
}

} // namespace solve
