#pragma once
#include "Piece.h"
#include "DirectionIterators.h"
#include "SquareSearchIterator.h"
#include "Square.h"


class Bishop :
    public Piece
{
public:
    Bishop(Color player) : Piece{ BishopPiece, player } {};
    Bishop* Copy() { return new Bishop(GetPlayer()); };
    std::vector<MoveCommand> PossibleMoves(std::vector<Piece*> board, Square position);
};

