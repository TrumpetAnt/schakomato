#pragma once
#include <memory>
#include <stdexcept>
#include <vector>
#include "PieceTypes.h"
#include "Square.h"
#include "Color.h"
#include "MoveCommand.h"


class Piece
{
public:
	Piece(PieceType type, Color player) : type(type), player(player) {};
	PieceType GetPieceType() { return type; };
	Color GetPlayer() { return player; }
	virtual Piece* Copy() = 0;
	virtual std::unique_ptr<std::vector<MoveCommand>> PossibleMoves(Piece** board, Square position) = 0;
private:
	PieceType type;
	Color player;
};
