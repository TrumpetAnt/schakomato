#pragma once
#include <vector>
#include "Piece.h"
#include "PieceTypes.h"

class StateManager
{
public:
	StateManager()
	{
		this->board = new std::vector<Piece*>;
		this->board->push_back(new Piece(Rook, 0, Square{ 'A', 0 }));
		this->board->push_back(new Piece(Knight, 0, Square{ 'B', 0 }));
		this->board->push_back(new Piece(Bishop, 0, Square{ 'C', 0 }));
		this->board->push_back(new Piece(Queen, 0, Square{ 'D', 0 }));
		this->board->push_back(new Piece(King, 0, Square{ 'E', 0 }));
		this->board->push_back(new Piece(Bishop, 0, Square{'F', 0}));
		this->board->push_back(new Piece(Knight, 0, Square{ 'G', 0 }));
		this->board->push_back(new Piece(Rook, 0, Square{ 'H', 0 }));
		this->board->push_back(new Piece(Pawn, 0, Square{ 'A', 1 }));
		this->board->push_back(new Piece(Pawn, 0, Square{ 'B', 1 }));
		this->board->push_back(new Piece(Pawn, 0, Square{ 'C', 1 }));
		this->board->push_back(new Piece(Pawn, 0, Square{ 'D', 1 }));
		this->board->push_back(new Piece(Pawn, 0, Square{ 'E', 1 }));
		this->board->push_back(new Piece(Pawn, 0, Square{ 'F', 1 }));
		this->board->push_back(new Piece(Pawn, 0, Square{ 'G', 1 }));
		this->board->push_back(new Piece(Pawn, 0, Square{ 'H', 1 }));

		this->board->push_back(new Piece(Rook, 1, Square{ 'A', 7 }));
		this->board->push_back(new Piece(Knight, 1, Square{ 'B', 7 }));
		this->board->push_back(new Piece(Bishop, 1, Square{ 'C', 7 }));
		this->board->push_back(new Piece(Queen, 1, Square{ 'D', 7 }));
		this->board->push_back(new Piece(King, 1, Square{ 'E', 7 }));
		this->board->push_back(new Piece(Bishop, 1, Square{ 'F', 7 }));
		this->board->push_back(new Piece(Knight, 1, Square{ 'G', 7 }));
		this->board->push_back(new Piece(Rook, 1, Square{ 'H', 7 }));
		this->board->push_back(new Piece(Pawn, 1, Square{ 'A', 6 }));
		this->board->push_back(new Piece(Pawn, 1, Square{ 'B', 6 }));
		this->board->push_back(new Piece(Pawn, 1, Square{ 'C', 6 }));
		this->board->push_back(new Piece(Pawn, 1, Square{ 'D', 6 }));
		this->board->push_back(new Piece(Pawn, 1, Square{ 'E', 6 }));
		this->board->push_back(new Piece(Pawn, 1, Square{ 'F', 6 }));
		this->board->push_back(new Piece(Pawn, 1, Square{ 'G', 6 }));
		this->board->push_back(new Piece(Pawn, 1, Square{ 'H', 6 }));
	};

	std::vector<Piece*>* GetBoard() { return this->board; };
private:
	std::vector<Piece*>* board;
};

