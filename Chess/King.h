#pragma once
#include "Piece.h"
#include "Square.h"
#include "SquareSearchIterator.h"

class King :
    public Piece
{
public:
    King(Color player) : Piece{ KingPiece, player } {};
    King* Copy() { return new King(GetPlayer()); };
    std::vector<MoveCommand> PossibleMoves(std::vector<Piece*> board, Square position);
};

