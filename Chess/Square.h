#pragma once

struct Square {
	char file;
	int rank;
};

inline bool operator==(const Square& lhs, const Square& rhs) { return lhs.file == rhs.file && lhs.rank == rhs.rank; };
inline bool operator!=(const Square& lhs, const Square& rhs) { return lhs.file != rhs.file || lhs.rank != rhs.rank; };