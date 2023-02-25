#include "StateManager.h"

void StateManager::Move(std::string notation)
{
	Piece* piece = FindPieceFromMove(notation);
}

PieceType GetPieceType(std::string notation) {
	if (!isupper(notation[0])) {
		return Pawn;
	}
	return CharToPieceType(notation[0]);
}

Piece* StateManager::FindPawnFromSourceSquare(Square target) {
	int rankModifier = this->currentPlayer == 0 ? 1 : -1;
	Piece* x = Find(this->board, FindPieceAux(Pawn, this->currentPlayer, Square{ target.file, target.rank + rankModifier }));
	return x != nullptr ? x : Find(this->board, FindPieceAux(Pawn, this->currentPlayer, Square{ target.file, target.rank + rankModifier * 2 }));
}

Piece* StateManager::FindPieceFromTarget(Square target, PieceType type) {
	switch (type) {
	case Pawn:
		return FindPawnFromSourceSquare(target);
	default:
		throw new NotImplementedException();
	}
}

Piece* StateManager::FindPieceFromMove(std::string notation) {
	// TODO: Add regex input validation
	// TODO: Captures 
	// TODO: Implement Disambiguating moves
	// TODO: Pawn promotion
	// TODO: Draw offer
	// TODO: Castling 
	// TODO: Check 
	// TODO: Checkmate 
	// TODO: End of game 
	bool capture = notation.find('x');
	PieceType type = GetPieceType(notation);
	if (type != Pawn) {
		notation = notation.substr(1);
	}
	if (capture) {
		notation = notation.substr(1);
	}
	Square target = Square{ notation[0], notation[1] };

	return FindPieceFromTarget(target, type);
}
