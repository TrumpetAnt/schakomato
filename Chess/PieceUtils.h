#pragma once
#include <functional>
#include <stdexcept>
#include "Piece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

inline int SquareToInt(Square square) {
	return (square.file - 'a') + (square.rank - 1) * 8;
}

inline Square IntToSquare(int square) {
	return Square{ (char)(square % 8 + 'a'), square / 8 + 1 };
}

inline PieceType CharToPieceType(char c) {
	switch (c) {
	case 'B':
		return BishopPiece;
	case 'K':
		return KingPiece;
	case 'Q':
		return QueenPiece;
	case 'R':
		return RookPiece;
	case 'N':
		return KnightPiece;
	}
	throw std::invalid_argument("Character not a piecetype");
}

inline char PieceTypeToChar(PieceType type) {
	switch (type) {
	case KingPiece:
		return 'K';
	case QueenPiece:
		return 'Q';
	case RookPiece:
		return 'R';
	case BishopPiece:
		return 'B';
	case KnightPiece:
		return 'N';
	case PawnPiece:
		return 'i';
	default:
		throw std::invalid_argument("Unhandeled switch case");
	}
}

inline Piece* CreateNewPiece(PieceType type, Color player) {
	switch (type) {
	case KingPiece:
		return new King(player);
	case QueenPiece:
		return new Queen(player);
	case RookPiece:
		return new Rook(player);
	case BishopPiece:
		return new Bishop(player);
	case KnightPiece:
		return new Knight(player);
	case PawnPiece:
		return new Pawn(player);
	default:
		throw std::invalid_argument("Unhandeled switch case");
	}
}