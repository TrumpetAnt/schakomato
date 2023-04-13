#pragma once
#include "Piece.h"
#include "Square.h"
#include "DirectionIterators.h"
#include "SquareSearchIterator.h"

class Rook :
    public Piece
{
public:
    Rook(Color player) : Piece{ RookPiece, player } {};
    Rook* Copy() { return new Rook(GetPlayer()); };
    std::unique_ptr<std::vector<MoveCommand>> PossibleMoves(std::unique_ptr<Piece*[]> board, Square position);
};

