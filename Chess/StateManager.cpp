#include "StateManager.h"

PieceType GetPieceType(std::string notation, bool capture) {
	int i = capture ? 1 : 0;
	if (!isupper(notation[i])) {
		return Pawn;
	}
	return CharToPieceType(notation[i]);
}

StateManager::StateManager() {
	board = std::make_unique<Piece* []>(64);
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

StateManager::StateManager(std::string boardString) {
	board = std::make_unique<Piece* []>(64);
	auto pieceString = boardString.substr(0, 4);
	while (pieceString.length() == 4) {
		board[SquareToInt(Square{ pieceString[2], pieceString[3] - '0' })] =
			new Piece(GetPieceType(pieceString.substr(1, 1), false), pieceString[0] - '0' == 0 ? White : Black);

		boardString = boardString.substr(4);
		pieceString = boardString.substr(0, 4);
	}
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

int StateManager::FindPawnFromSourceSquare(Square target, bool capture) {
	int rankModifier = currentPlayer == White ? -1 : 1;
	if (!capture) {
		auto pieceAtTarget = board[SquareToInt(Square{ target.file, target.rank + rankModifier })];
		if (pieceAtTarget != nullptr && pieceAtTarget->GetPlayer() == currentPlayer) {
			return SquareToInt(Square{ target.file, target.rank + rankModifier });
		}
		auto secondPiece = board[SquareToInt(Square{ target.file, target.rank + rankModifier * 2 })];
		if (target.rank == (currentPlayer == White ? 4 : 5) &&
			secondPiece != nullptr &&
			pieceAtTarget == nullptr) {
			return SquareToInt(Square{ target.file, target.rank + rankModifier * 2 });
		}
	}
	else {
		if (disambiguationSource.file != '\0') {
			disambiguationSource.rank = target.rank + rankModifier;
			auto capturingPiece = board[SquareToInt(disambiguationSource)];
			if (capturingPiece != nullptr && capturingPiece->GetPlayer() == currentPlayer) {
				return SquareToInt(disambiguationSource);
			}
		}
		auto capturingPieceA = board[SquareToInt(Square{ (char)(target.file - 1), target.rank + rankModifier })];
		auto capturingPieceB = board[SquareToInt(Square{ (char)(target.file + 1), target.rank + rankModifier })];
		if (capturingPieceA != nullptr && capturingPieceA->GetPlayer() == currentPlayer &&
			capturingPieceB != nullptr && capturingPieceB->GetPlayer() == currentPlayer) {
			throw new NotImplementedException();
		}
		if (capturingPieceA != nullptr && capturingPieceA->GetPlayer() == currentPlayer) {
			return SquareToInt(Square{ (char)(target.file - 1), target.rank + rankModifier });
		}
		if (capturingPieceB != nullptr && capturingPieceB->GetPlayer() == currentPlayer) {
			return SquareToInt(Square{ (char)(target.file + 1), target.rank + rankModifier });
		}
	}

	return -1;
}

int StateManager::FindKnightFromSourceSquare(Square target) {
	int targetInt = SquareToInt(target);
	Square sourceSquares[8] = {
		Square{(char)((int)target.file + 1), target.rank + 2},
		Square{(char)((int)target.file + 2), target.rank + 1},
		Square{(char)((int)target.file - 1), target.rank + 2},
		Square{(char)((int)target.file - 2), target.rank + 1},
		Square{(char)((int)target.file + 1), target.rank - 2},
		Square{(char)((int)target.file + 2), target.rank - 1},
		Square{(char)((int)target.file - 1), target.rank - 2},
		Square{(char)((int)target.file - 2), target.rank - 1},
	};
	int sourceSquare = -1;
	
	for (int i = 0; i < 8; i++) {
		Square* sq = &sourceSquares[i];
		if ((disambiguationSource.file != '\0' && sq->file != disambiguationSource.file) ||
			(disambiguationSource.rank != -1 && sq->rank != disambiguationSource.rank)) {
			continue;
		}
		if ((sq->file - 'a') < 0 ||
			(sq->file - 'a') > 7 ||
			sq->rank < 1 ||
			sq->rank > 8) {
			continue;
		} 
		int squareInt = SquareToInt(sourceSquares[i]);
		Piece* p = board[squareInt];
		if (p == nullptr ||
			p->GetPieceType() != Knight ||
			p->GetPlayer() != currentPlayer) {
			continue;
		}
		if (sourceSquare != -1) {
			throw std::invalid_argument("Unexpected ambiguous move");
		}
		sourceSquare = squareInt;
	}
	return sourceSquare;
}

int StateManager::FindPieceFromTarget(Square target, PieceType type, bool capture) {
	switch (type) {
	case Pawn:
		return FindPawnFromSourceSquare(target, capture);
	case Knight:
		return FindKnightFromSourceSquare(target);
	default:
		throw new NotImplementedException();
	}
}

void StateManager::ValidateMoveToTarget(Square target, bool capture, bool enPassant) {
	auto pieceAtTarget = board[SquareToInt(target)];
	if (pieceAtTarget != nullptr) {
		if (pieceAtTarget->GetPlayer() != currentPlayer && !capture) {
			throw std::invalid_argument("A capturing move is required to capture a piece.");
		}
		if (pieceAtTarget->GetPlayer() == this->currentPlayer) {
			throw std::invalid_argument("Square is occupied by same player piece");
		}
	}
	else if (capture && !enPassant) {
		throw std::invalid_argument("No piece at target of capturing move");
	}
	else if (enPassant && enPassantCapturablePawn == -1) {
		throw std::invalid_argument("No legal en passant move.");
	}
}

void StateManager::Move(std::string notation)
{
	disambiguationSource = Square{ '\0', -1 };
	// TODO: Add regex input validation
	// TODO: Implement Disambiguating moves
	// TODO: Draw offer
	// TODO: Castling 
	// TODO: Check 
	// TODO: Checkmate 
	// TODO: End of game 
	bool capture = notation.find('x') != std::string::npos;
	bool enPassant = notation.length() > 4 && notation.compare(notation.length() - 4, 4, "e.p.") == 0;
	PieceType type = GetPieceType(notation, capture);
	if (type != Pawn) {
		notation = notation.substr(1);
	}
	if (capture) {
		notation = notation.substr(1);
	}
	if (isalpha(notation[0]) && isalpha(notation[1])) {
		disambiguationSource.file = notation[0];
		notation = notation.substr(1);
	}
	if (notation.length() > 2 && isdigit(notation[1]) && isdigit(notation[2])) {
		disambiguationSource.rank = notation[1];
		char c = notation[0];
		notation = notation.substr(1);
		notation[0] = c;
	}

	Square target = Square{ notation[0], (notation[1] - '0') };

	ValidateMoveToTarget(target, capture, enPassant);

	int piecePosition = FindPieceFromTarget(target, type, capture);
	if (piecePosition == -1) {
		throw new std::invalid_argument("Unable to execute move");
	}
	if (type == Pawn && target.rank == 8) {
		if (notation.length() < 3) {
			throw new std::invalid_argument("Pawn promotion expected, input too short");
		}
		board[piecePosition]->PromoteTo(CharToPieceType(notation[2]));
	}
	int enPassantTarget = enPassantCapturablePawn;
	enPassantCapturablePawn = board[piecePosition]->GetPieceType() == Pawn && abs(IntToSquare(piecePosition).rank - target.rank) == 2
		? SquareToInt(target)
		: -1;

	if (capture && !enPassant) {
		delete board[SquareToInt(target)];
	}
	board[SquareToInt(target)] = board[piecePosition];
	board[piecePosition] = nullptr;
	if (enPassant) {
		delete board[enPassantTarget];
		board[enPassantTarget] = nullptr;
	}
	currentPlayer = 1 - currentPlayer;
}