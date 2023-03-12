#pragma once
#include <vector>
#include <string>
#include "Piece.h"
#include "PieceTypes.h"
#include "PieceUtils.h"
#include "NotImplementedException.h"

class StateManager
{
public:
	StateManager();
	StateManager(std::string boardString);
	void Move(std::string notation);
	std::unique_ptr<Piece* []> GetStateCopy();
private:
	std::unique_ptr<Piece*[]> board;
	int currentPlayer = 0;

	int FindPieceFromTarget(Square target, PieceType type, bool capture);
	int FindPawnFromSourceSquare(Square target, bool capture);
	int FindKnightFromSourceSquare(Square target);
	void ValidateMoveToTarget(Square target, bool capture, bool enPassant);

	int enPassantCapturablePawn = -1;
	Square disambiguationSource;
};

