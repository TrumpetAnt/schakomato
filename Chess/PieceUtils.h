#pragma once
#include <functional>
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