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
	Color GetPlayer() { return player; }
	virtual Piece* Copy() = 0;
	virtual int PossibleMoves(Piece** board, std::vector<Square>*movesVector) = 0;
private:
	PieceType type;
	Color player;
};
