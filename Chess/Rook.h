#pragma once
#include "Piece.h"
class Rook :
    public Piece
{
public:
    Rook(Color player) : Piece{ RookPiece, player } {};
    Rook* Copy() { return new Rook(GetPlayer()); };
    int PossibleMoves(Piece** board, std::vector<Square>* movesVector);
};

