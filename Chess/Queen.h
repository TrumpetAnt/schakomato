#pragma once
#include "Piece.h"
#include "Square.h"
#include "DirectionIterators.h"
#include "SquareSearchIterator.h"

class Queen :
    public Piece
{
public:
    Queen(Color player) : Piece{ QueenPiece, player } {}
    Queen* Copy() { return new Queen(GetPlayer()); };
    std::unique_ptr<std::vector<MoveCommand>> PossibleMoves(Piece** board, Square position);
};

