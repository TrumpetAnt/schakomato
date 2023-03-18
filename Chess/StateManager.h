#pragma once
#include <vector>
#include <string>
#include "Piece.h"
#include "PieceTypes.h"
#include "PieceUtils.h"
#include "NotImplementedException.h"
#include "MoveCommand.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "DirectionIterators.h"
#include "SquareSearchIterator.h"

class StateManager
{
public:
	StateManager();
	StateManager(std::string boardString);
	void Move(std::string notation);
	std::unique_ptr<Piece* []> GetStateCopy();
	Color GetCurrentPlayer() { return currentPlayer == 0 ? White : Black; };
private:
	std::unique_ptr<Piece*[]> board;
	int currentPlayer = 0;

	int FindPieceFromTarget(MoveCommand command);
	int FindPawnFromSourceSquare(Square target, bool capture);
	int FindKnightFromSourceSquare(Square target);
	int FindBishopFromSourceSquare(MoveCommand command);
	int FindRookFromSourceSquare(MoveCommand command);
	void BaseMoveValidation(MoveCommand command);

	MoveCommand MoveFromInput(std::string notation);

	int enPassantCapturablePawn = -1;
	Square disambiguationSource;
};

