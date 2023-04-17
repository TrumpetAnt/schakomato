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
	std::vector<Piece*> GetStateCopy() const;
	Color GetCurrentPlayer() { return currentPlayer ; };
	bool Completed() { return completed; }
	Color GetWinner() { if (!completed) { throw std::invalid_argument("Game not finished"); } return winner; }
	std::vector<Piece*> Pieces(Color player);
private:
	std::vector<Piece*> board;
	Color currentPlayer = White;
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
	std::unique_ptr<StateManager> Clone() const;
	void ExecuteMove(MoveCommand command, int piecePosition, int enPassantTarget);
	bool CheckForMate();


	MoveCommand MoveFromInput(std::string notation);

	int enPassantCapturablePawn = -1;
};

