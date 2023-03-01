#pragma once
#include <vector>
#include <string>
#include "Piece.h"
#include "PieceTypes.h"
#include "PieceUtils.h"
#include "NotImplementedException.h"
#include "VectorUtils.h"

class StateManager
{
public:
	StateManager()
	{
		this->board = new std::vector<Piece*>;
		this->board->push_back(new Piece(Rook, 0, 'A', 0));
		this->board->push_back(new Piece(Knight, 0, 'B', 0));
		this->board->push_back(new Piece(Bishop, 0, 'C', 0));
		this->board->push_back(new Piece(Queen, 0, 'D', 0));
		this->board->push_back(new Piece(King, 0, 'E', 0));
		this->board->push_back(new Piece(Bishop, 0, 'F', 0));
		this->board->push_back(new Piece(Knight, 0, 'G', 0));
		this->board->push_back(new Piece(Rook, 0, 'H', 0));
		this->board->push_back(new Piece(Pawn, 0, 'A', 1));
		this->board->push_back(new Piece(Pawn, 0, 'B', 1));
		this->board->push_back(new Piece(Pawn, 0, 'C', 1));
		this->board->push_back(new Piece(Pawn, 0, 'D', 1));
		this->board->push_back(new Piece(Pawn, 0, 'E', 1));
		this->board->push_back(new Piece(Pawn, 0, 'F', 1));
		this->board->push_back(new Piece(Pawn, 0, 'G', 1));
		this->board->push_back(new Piece(Pawn, 0, 'H', 1));

		this->board->push_back(new Piece(Rook, 1, 'A', 7));
		this->board->push_back(new Piece(Knight, 1, 'B', 7));
		this->board->push_back(new Piece(Bishop, 1, 'C', 7));
		this->board->push_back(new Piece(Queen, 1, 'D', 7));
		this->board->push_back(new Piece(King, 1, 'E', 7));
		this->board->push_back(new Piece(Bishop, 1, 'F', 7));
		this->board->push_back(new Piece(Knight, 1, 'G', 7));
		this->board->push_back(new Piece(Rook, 1, 'H', 7));
		this->board->push_back(new Piece(Pawn, 1, 'A', 6));
		this->board->push_back(new Piece(Pawn, 1, 'B', 6));
		this->board->push_back(new Piece(Pawn, 1, 'C', 6));
		this->board->push_back(new Piece(Pawn, 1, 'D', 6));
		this->board->push_back(new Piece(Pawn, 1, 'E', 6));
		this->board->push_back(new Piece(Pawn, 1, 'F', 6));
		this->board->push_back(new Piece(Pawn, 1, 'G', 6));
		this->board->push_back(new Piece(Pawn, 1, 'H', 6));
	};

	std::vector<Piece*>* GetBoard() { return this->board; };
	void Move(std::string notation);
private:
	std::vector<Piece*>* board;
	int currentPlayer = 0;

	Piece* FindPieceFromTarget(Square target, PieceType type);
	Piece* FindPawnFromSourceSquare(Square target);
};

