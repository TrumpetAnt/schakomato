#pragma once
#include "Piece.h"
class Queen :
    public Piece
{
public:
    Queen(Color player) : Piece{ QueenPiece, player } {}
    Queen* Copy() { return new Queen(GetPlayer()); };
    int PossibleMoves(Piece** board, std::vector<Square>* movesVector);
};

