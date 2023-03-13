#pragma once
#include <memory>
#include <stdexcept>
#include <vector>
#include "PieceTypes.h"
#include "Square.h"
#include "Color.h"


class Piece
{
public:
	Piece(PieceType type, Color player) : type(type), player(player) {};
	PieceType GetPieceType() { return type; };
	void PromoteTo(PieceType promotion);
	Color GetPlayer() { return player; }
	Piece* Copy() { return new Piece(type, player); };
	virtual int PossibleMoves(Piece** board, std::vector<Square>*movesVector);
private:
	PieceType type;
	Color player;
};
