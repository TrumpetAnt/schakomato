#pragma once
#include <functional>
#include <stdexcept>
#include "Piece.h"

std::function<bool(Piece*)> FindPieceAux(PieceType type, int player, Square square) {
	std::function<bool(Piece*)> ret = [type, player, square](Piece* piece) {
		Square sq = piece->GetPosition();
		return piece->GetPieceType() == type &&
			sq.file == square.file &&
			sq.rank == square.rank &&
			piece->GetPlayer() == player;
	};
	return ret;
}

PieceType CharToPieceType(char c) {
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