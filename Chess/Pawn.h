#pragma once
#include "Piece.h"
#include "Square.h"
#include "SquareSearchIterator.h"

class Pawn :
    public Piece
{
public:
    Pawn(Color player) : Piece{ PawnPiece, player } {};
    Pawn* Copy() { return new Pawn(GetPlayer()); };
    std::vector<MoveCommand> PossibleMoves(std::vector<Piece*> board, Square position);
private:
    bool CaptureIfPossible(Piece* capturingPieceB, Square probeCaptureRight, std::vector<MoveCommand> possibleMoves);
    MoveCommand CreateMoveCommand(Square target, bool capture, PieceType promotedTo = QueenPiece);
};

