#pragma once
#include "Piece.h"
class King :
    public Piece
{
public:
    King(Color player) : Piece{ KingPiece, player } {};
    King* Copy() { return new King(GetPlayer()); };
    int PossibleMoves(Piece** board, std::vector<Square>* movesVector);
};

