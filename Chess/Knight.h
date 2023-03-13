#pragma once
#include "Piece.h"
class Knight :
    public Piece
{
public:
    Knight(Color player) : Piece{ KnightPiece, player } {};
    Knight* Copy() { return new Knight(GetPlayer()); };
    int PossibleMoves(Piece** board, std::vector<Square>* movesVector);
};

