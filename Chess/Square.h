#pragma once

struct Square {
	char file;
	int rank;
};

inline bool operator==(const Square& lhs, const Square& rhs) { return lhs.file == rhs.file && lhs.rank == rhs.rank; };
inline bool operator!=(const Square& lhs, const Square& rhs) { return lhs.file != rhs.file || lhs.rank != rhs.rank; };

inline int SquareToInt(Square square) {
	return (square.file - 'a') + (square.rank - 1) * 8;
}

inline Square IntToSquare(int square) {
	return Square{ (char)(square % 8 + 'a'), square / 8 + 1 };
}