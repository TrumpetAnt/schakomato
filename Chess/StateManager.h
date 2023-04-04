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
#include "PieceTypeIterator.h"

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
	Square whiteKingLocation = Square{'\0',0};
	Square blackKingLocation = Square{ '\0',0 };

	bool CheckStateForCheck(MoveCommand command, int piecePosition, int enPassantTarget);
	std::vector<int>* FindPieceFromTarget(MoveCommand command);
	std::vector<int>* FindPawnFromSourceSquare(MoveCommand command);
	std::vector<int>* FindKnightFromSourceSquare(MoveCommand command);
	std::vector<int>* FindKingPieceFromSourceSquare(MoveCommand command);
	std::vector<int>* FindPieceFromSourceSquare(MoveCommand command, DirectionalIterator* directionalIterator);
	void BaseMoveValidation(MoveCommand command);
	std::unique_ptr<StateManager> Clone();
	void ExecuteMove(MoveCommand command, int piecePosition, int enPassantTarget);


	MoveCommand MoveFromInput(std::string notation);

	int enPassantCapturablePawn = -1;
};

