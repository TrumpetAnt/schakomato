#pragma once
#include "PieceTypes.h"
#include "Square.h"

class Piece
{
public:
	Piece(PieceType type, int player, Square square) : type(type), player(player), square(square) {};
	void Move(Square square) {
		this->square = square;
	}
	Square GetPosition() { return square; };
	PieceType GetPieceType() { return type; };
	bool operator()(const Piece& a, const Piece& b) const {
		return a.square.file < b.square.file;
	}
private:
	PieceType type;
	int player;
	Square square;
};

