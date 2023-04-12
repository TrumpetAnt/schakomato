#pragma once
#include "Piece.h"
#include "Square.h"
#include "SquareSearchIterator.h"

class Knight :
    public Piece
{
public:
    Knight(Color player) : Piece{ KnightPiece, player } {};
    Knight* Copy() { return new Knight(GetPlayer()); };
    std::unique_ptr<std::vector<MoveCommand>> PossibleMoves(Piece** board, Square position);
};

