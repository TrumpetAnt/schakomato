#pragma once
#include <memory>
#include "PieceTypes.h"
#include "Square.h"


class Piece
{
public:
	Piece(PieceType type, int player, char file, int rank) : type(type), player(player) {
		square = std::make_unique<Square>(Square{ file, rank });
	};
	void Move(char file, int rank) {
		square.reset();
		square = std::make_unique<Square>(Square{file, rank});
	}
	Square* GetPosition() { return new Square{square->file, square->rank}; };
	PieceType GetPieceType() { return type; };
	int GetPlayer() { return player; }

	inline bool operator==(const Piece& a) {
		return this->square == a.square;
	}
	bool operator()(const Piece& a, const Piece& b) const {
		return a.square->file < b.square->file;
	}
private:
	PieceType type;
	int player;
	std::unique_ptr<Square> square;
};
