#include "StateManager.h"


PieceType GetPieceType(std::string notation) {
	if (!isupper(notation[0])) {
		return Pawn;
	}
	return CharToPieceType(notation[0]);
}

Piece* StateManager::FindPawnFromSourceSquare(Square target) {
	int rankModifier = this->currentPlayer == 0 ? -1 : 1;
	Piece* x = Find(this->board, FindPieceAux(Pawn, this->currentPlayer, Square{ target.file, target.rank + rankModifier }));
	return x != nullptr ? x : Find(this->board, FindPieceAux(Pawn, this->currentPlayer, Square{ target.file, target.rank + rankModifier + rankModifier }));
}

Piece* StateManager::FindPieceFromTarget(Square target, PieceType type) {
	switch (type) {
	case Pawn:
		return FindPawnFromSourceSquare(target);
	default:
		throw new NotImplementedException();
	}
}

void StateManager::Move(std::string notation)
{
	// TODO: Add regex input validation
	// TODO: Captures 
	// TODO: Implement Disambiguating moves
	// TODO: Pawn promotion
	// TODO: Draw offer
	// TODO: Castling 
	// TODO: Check 
	// TODO: Checkmate 
	// TODO: End of game 
	auto x = notation.find('x');
	bool capture = x != std::string::npos;
	PieceType type = GetPieceType(notation);
	if (type != Pawn) {
		notation = notation.substr(1);
	}
	if (capture) {
		notation = notation.substr(1);
	}
	Square target = Square{ notation[0], (notation[1] - '0')};
	Piece* piece = FindPieceFromTarget(target, type);
	if (piece == nullptr) {
		throw new std::invalid_argument("Unable to execute move");
	}
	piece->Move(target.file, target.rank);
	currentPlayer = 1 - currentPlayer;
}