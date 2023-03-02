#include "StateManager.h"

PieceType GetPieceType(std::string notation) {
	if (!isupper(notation[0])) {
		return Pawn;
	}
	return CharToPieceType(notation[0]);
}

StateManager::StateManager() {
	board = std::make_unique<Piece*[]>(64);
	board[SquareToInt(Square{ 'a',1 })] = new Piece(Rook, White);
	board[SquareToInt(Square{ 'b',1 })] = new Piece(Knight, White);
	board[SquareToInt(Square{ 'c',1 })] = new Piece(Bishop, White);
	board[SquareToInt(Square{ 'd',1 })] = new Piece(Queen, White);
	board[SquareToInt(Square{ 'e',1 })] = new Piece(King, White);
	board[SquareToInt(Square{ 'f',1 })] = new Piece(Bishop, White);
	board[SquareToInt(Square{ 'g',1 })] = new Piece(Knight, White);
	board[SquareToInt(Square{ 'h',1 })] = new Piece(Rook, White);
	board[SquareToInt(Square{ 'a',2 })] = new Piece(Pawn, White);
	board[SquareToInt(Square{ 'b',2 })] = new Piece(Pawn, White);
	board[SquareToInt(Square{ 'c',2 })] = new Piece(Pawn, White);
	board[SquareToInt(Square{ 'd',2 })] = new Piece(Pawn, White);
	board[SquareToInt(Square{ 'e',2 })] = new Piece(Pawn, White);
	board[SquareToInt(Square{ 'f',2 })] = new Piece(Pawn, White);
	board[SquareToInt(Square{ 'g',2 })] = new Piece(Pawn, White);
	board[SquareToInt(Square{ 'h',2 })] = new Piece(Pawn, White);

	board[SquareToInt(Square{ 'a',8 })] = new Piece(Rook, Black);
	board[SquareToInt(Square{ 'b',8 })] = new Piece(Knight, Black);
	board[SquareToInt(Square{ 'c',8 })] = new Piece(Bishop, Black);
	board[SquareToInt(Square{ 'd',8 })] = new Piece(Queen, Black);
	board[SquareToInt(Square{ 'e',8 })] = new Piece(King, Black);
	board[SquareToInt(Square{ 'f',8 })] = new Piece(Bishop, Black);
	board[SquareToInt(Square{ 'g',8 })] = new Piece(Knight, Black);
	board[SquareToInt(Square{ 'h',8 })] = new Piece(Rook, Black);
	board[SquareToInt(Square{ 'a',7 })] = new Piece(Pawn, Black);
	board[SquareToInt(Square{ 'b',7 })] = new Piece(Pawn, Black);
	board[SquareToInt(Square{ 'c',7 })] = new Piece(Pawn, Black);
	board[SquareToInt(Square{ 'd',7 })] = new Piece(Pawn, Black);
	board[SquareToInt(Square{ 'e',7 })] = new Piece(Pawn, Black);
	board[SquareToInt(Square{ 'f',7 })] = new Piece(Pawn, Black);
	board[SquareToInt(Square{ 'g',7 })] = new Piece(Pawn, Black);
	board[SquareToInt(Square{ 'h',7 })] = new Piece(Pawn, Black);

}

std::unique_ptr<Piece* []> StateManager::GetStateCopy() {
	auto result = std::make_unique<Piece* []>(64);
	for (int i = 0; i < 64; i++) {
		if (board[i] != nullptr) {
			result[i] = board[i]->Copy();
		}
	}
	return result;
}

int StateManager::FindPawnFromSourceSquare(Square target) {
	int rankModifier = this->currentPlayer == White ? -1 : 1;
	if (board[SquareToInt(Square{ target.file, target.rank + rankModifier })] != nullptr) {
		return SquareToInt(Square{ target.file, target.rank + rankModifier });
	}
	if (board[SquareToInt(Square{ target.file, target.rank + rankModifier * 2})] != nullptr) {
		return SquareToInt(Square{ target.file, target.rank + rankModifier * 2});
	}
	return -1;
}

int StateManager::FindPieceFromTarget(Square target, PieceType type) {
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
	Square target = Square{ notation[0], (notation[1] - '0') };
	int piecePosition = FindPieceFromTarget(target, type);
	if (piecePosition == -1) {
		throw new std::invalid_argument("Unable to execute move");
	}
	board[SquareToInt(target)] = board[piecePosition];
	board[piecePosition] = nullptr;
	currentPlayer = 1 - currentPlayer;
}