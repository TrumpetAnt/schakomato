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
		this->board->push_back(new Piece(Rook, 0, 'a', 1));
		this->board->push_back(new Piece(Knight, 0, 'b', 1));
		this->board->push_back(new Piece(Bishop, 0, 'c', 1));
		this->board->push_back(new Piece(Queen, 0, 'd', 1));
		this->board->push_back(new Piece(King, 0, 'e', 1));
		this->board->push_back(new Piece(Bishop, 0, 'f', 1));
		this->board->push_back(new Piece(Knight, 0, 'g', 1));
		this->board->push_back(new Piece(Rook, 0, 'h', 1));
		this->board->push_back(new Piece(Pawn, 0, 'a', 2));
		this->board->push_back(new Piece(Pawn, 0, 'b', 2));
		this->board->push_back(new Piece(Pawn, 0, 'c', 2));
		this->board->push_back(new Piece(Pawn, 0, 'd', 2));
		this->board->push_back(new Piece(Pawn, 0, 'e', 2));
		this->board->push_back(new Piece(Pawn, 0, 'f', 2));
		this->board->push_back(new Piece(Pawn, 0, 'g', 2));
		this->board->push_back(new Piece(Pawn, 0, 'h', 2));

		this->board->push_back(new Piece(Rook, 1, 'a', 8));
		this->board->push_back(new Piece(Knight, 1, 'b', 8));
		this->board->push_back(new Piece(Bishop, 1, 'c', 8));
		this->board->push_back(new Piece(Queen, 1, 'd', 8));
		this->board->push_back(new Piece(King, 1, 'e', 8));
		this->board->push_back(new Piece(Bishop, 1, 'f', 8));
		this->board->push_back(new Piece(Knight, 1, 'g', 8));
		this->board->push_back(new Piece(Rook, 1, 'h', 8));
		this->board->push_back(new Piece(Pawn, 1, 'a', 7));
		this->board->push_back(new Piece(Pawn, 1, 'b', 7));
		this->board->push_back(new Piece(Pawn, 1, 'c', 7));
		this->board->push_back(new Piece(Pawn, 1, 'd', 7));
		this->board->push_back(new Piece(Pawn, 1, 'e', 7));
		this->board->push_back(new Piece(Pawn, 1, 'f', 7));
		this->board->push_back(new Piece(Pawn, 1, 'g', 7));
		this->board->push_back(new Piece(Pawn, 1, 'h', 7));
	};

	std::vector<Piece*>* GetBoard() { return this->board; };
	void Move(std::string notation);
private:
	std::vector<Piece*>* board;
	int currentPlayer = 0;

	Piece* FindPieceFromTarget(Square target, PieceType type);
	Piece* FindPawnFromSourceSquare(Square target);
};

