#pragma once
#include <iterator>
#include "Square.h"

inline void ProbeDiagonalSquare(int dir, Square* square) {
	square->file = (char)((int)square->file + 1 - 2 * (dir % 2));
	square->rank = square->rank + 1 - 2 * ((dir / 2) % 2);
}

inline void ProbeLevelSquare(int dir, Square* square) {
	square->file = (char)((int)square->file + dir % 2 * (dir - 2));
	square->rank = square->rank + (dir + 1) % 2 * (1 - dir);
}

inline void ProbeSquare(int dir, Square* square) {
	if (dir % 2 == 1) {
		ProbeDiagonalSquare((dir - 1) / 2, square);
	}
	else {
		ProbeLevelSquare(dir / 2, square);
	}
}

inline bool SquareInBoard(const Square* square) {
	auto file = square->file - 'a';
	return
		file >= 0 && file < 8 &&
		square->rank > 0 && square->rank < 9;
}

inline bool DirectionIsDiagonal(int dir) {
	return dir % 2 == 1;
}

class SquareSearchIterator {
public:
	class iterator : public std::iterator<
		std::input_iterator_tag,   // iterator_category
		Square,                      // value_type
		Square,                      // difference_type
		const Square*,               // pointer
		Square                       // reference
	> {
		Square square = Square{ '\0', 0 };
		int direction = -1;
		int count = -1;
		bool disambiguation = false;
	public:
		explicit iterator() {};
		explicit iterator(Square start, int direction, bool disambiguation) : square(start), direction(direction), disambiguation(disambiguation) {}
		iterator& operator++() { ProbeSquare(direction, &square); count++; return *this; }
		iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
		bool operator==(iterator other) const { return !SquareInBoard(&square) || (disambiguation && count == 1); }
		bool operator!=(iterator other) const { return !(*this == other); }
		reference operator*() const { return square; }
	};

	Square start;
	Square disambiguation;
	int direction;
	bool kingMove = false;
	SquareSearchIterator(Square start, int direction) : start(start), direction(direction), disambiguation(Square{ '\0', 0 }) {}
	SquareSearchIterator(Square start, int direction, bool kingMove) : start(start), direction(direction), disambiguation(Square{ '\0', 0 }), kingMove(kingMove) {}
	SquareSearchIterator(Square start, Square disambiguation, int direction) : start(start), direction(direction), disambiguation(disambiguation) {}

	iterator begin() {
		if (kingMove) {
			auto kingIter = iterator(start, direction, true);
			kingIter++;
			return kingIter;
		}
		else if (disambiguation.file != '\0' && disambiguation.rank != 0) {
			start = disambiguation;
			return iterator(start, direction, true);
		}
		else if (disambiguation != Square{ '\0', 0 }) {
			int diff = abs(disambiguation.file != '\0'
				? start.file - disambiguation.file
				: start.rank - disambiguation.rank);
			for (int i = 0; i < diff; i++) {
				ProbeSquare(direction, &disambiguation);
			}
			return iterator(start, direction, true);
		}
		auto res = iterator(start, direction, false);
		res++;
		return res;
	}
	iterator end() { return iterator(); }
};