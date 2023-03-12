#include "Piece.h"

void Piece::PromoteTo(PieceType promotion) {
	if (type != Pawn) {
		throw new std::invalid_argument("Only pawns can be promoted");
	}
	if (promotion == King || promotion == Pawn) {
		throw new std::invalid_argument("Cannot promote to King or Pawn");
	}
	type = promotion;
}