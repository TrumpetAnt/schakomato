#pragma once
#include "Square.h"
#include "PieceTypes.h"

struct MoveCommand {
	Square disambiguation;
	Square target;
	PieceType type;
	bool capture;
	bool enPassant;
	bool promotion;
	PieceType promotedTo;
};