#pragma once
#include <functional>
#include <stdexcept>
#include "Piece.h"

inline int SquareToInt(Square square) {
	return (square.file - 'a') + (square.rank - 1) * 8;
}

inline PieceType CharToPieceType(char c) {
	switch (c) {
	case 'B':
		return Bishop;
	case 'K':
		return King;
	case 'Q':
		return Queen;
	case 'R':
		return Rook;
	case 'N':
		return Knight;
	}
	throw new std::invalid_argument("Character not a piecetype");
}

inline char PieceTypeToChar(PieceType type) {
	switch (type) {
	case King:
		return 'K';
	case Queen:
		return 'Q';
	case Rook:
		return 'R';
	case Bishop:
		return 'B';
	case Knight:
		return 'N';
	case Pawn:
		return 'i';
	default:
		throw std::invalid_argument("Unhandeled switch case");
	}
}