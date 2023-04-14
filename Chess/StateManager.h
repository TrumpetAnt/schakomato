#pragma once
#include <vector>
#include <string>
#include <utility>
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
	StateManager(const StateManager& other);
	~StateManager();

	void Move(std::string notation);
	std::unique_ptr<Piece*[]> GetStateCopy() const;
	Color GetCurrentPlayer() { return currentPlayer == 0 ? White : Black; };
	bool Completed() { return completed; }
	Color GetWinner() { if (!completed) { throw std::invalid_argument("Game not finished"); } return winner; }
	std::unique_ptr<std::vector<Piece*>> Pieces(Color player);
private:
	std::unique_ptr<Piece*[]> board;
	int currentPlayer = 0;
	Square whiteKingLocation = Square{'\0',0};
	Square blackKingLocation = Square{ '\0',0 };
	bool completed = false;
	Color winner = Black;

	bool CheckStateForCheck(MoveCommand command, int piecePosition, int enPassantTarget);
	std::vector<int>* FindPieceFromTarget(MoveCommand command);
	std::vector<int>* FindPawnFromSourceSquare(MoveCommand command);
	std::vector<int>* FindKnightFromSourceSquare(MoveCommand command);
	std::vector<int>* FindKingPieceFromSourceSquare(MoveCommand command);
	std::vector<int>* FindPieceFromSourceSquare(MoveCommand command, DirectionalIterator* directionalIterator);
	void BaseMoveValidation(MoveCommand command);
	StateManager* Clone() const;
	void ExecuteMove(MoveCommand command, int piecePosition, int enPassantTarget);
	bool CheckForMate();


	MoveCommand MoveFromInput(std::string notation);

	int enPassantCapturablePawn = -1;
};

