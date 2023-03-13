#pragma once
#include "Piece.h"
class Pawn :
    public Piece
{
public:
    Pawn(Color player) : Piece{ PawnPiece, player } {};
    Pawn* Copy() { return new Pawn(GetPlayer()); };
    int PossibleMoves(Piece** board, std::vector<Square>* movesVector);
};

