#pragma once
#include <functional>
#include <stdexcept>
#include "Piece.h"

std::function<bool(Piece*)> inline FindPieceAux(PieceType type, int player, Square square) {
	std::function<bool(Piece*)> ret = [type, player, square](Piece* piece) {
		Square* sq = piece->GetPosition();
		auto file = sq->file;
		auto rank = sq->rank;
		delete sq;
		return piece->GetPieceType() == type &&
			file == square.file &&
			rank == square.rank &&
			piece->GetPlayer() == player;
	};
	return ret;
}

PieceType inline CharToPieceType(char c) {
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