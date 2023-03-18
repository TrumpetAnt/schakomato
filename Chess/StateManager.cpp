#include "StateManager.h"

PieceType GetPieceType(std::string notation, bool capture) {
	int i = capture ? 1 : 0;
	if (!isupper(notation[i])) {
		return PawnPiece;
	}
	return CharToPieceType(notation[i]);
}

StateManager::StateManager() {
	board = std::make_unique<Piece* []>(64);
	board[SquareToInt(Square{ 'a',1 })] = new Rook(White);
	board[SquareToInt(Square{ 'b',1 })] = new Knight(White);
	board[SquareToInt(Square{ 'c',1 })] = new Bishop(White);
	board[SquareToInt(Square{ 'd',1 })] = new Queen(White);
	board[SquareToInt(Square{ 'e',1 })] = new King(White);
	board[SquareToInt(Square{ 'f',1 })] = new Bishop(White);
	board[SquareToInt(Square{ 'g',1 })] = new Knight(White);
	board[SquareToInt(Square{ 'h',1 })] = new Rook(White);
	board[SquareToInt(Square{ 'a',2 })] = new Pawn(White);
	board[SquareToInt(Square{ 'b',2 })] = new Pawn(White);
	board[SquareToInt(Square{ 'c',2 })] = new Pawn(White);
	board[SquareToInt(Square{ 'd',2 })] = new Pawn(White);
	board[SquareToInt(Square{ 'e',2 })] = new Pawn(White);
	board[SquareToInt(Square{ 'f',2 })] = new Pawn(White);
	board[SquareToInt(Square{ 'g',2 })] = new Pawn(White);
	board[SquareToInt(Square{ 'h',2 })] = new Pawn(White);

	board[SquareToInt(Square{ 'a',8 })] = new Rook(Black);
	board[SquareToInt(Square{ 'b',8 })] = new Knight(Black);
	board[SquareToInt(Square{ 'c',8 })] = new Bishop(Black);
	board[SquareToInt(Square{ 'd',8 })] = new Queen(Black);
	board[SquareToInt(Square{ 'e',8 })] = new King(Black);
	board[SquareToInt(Square{ 'f',8 })] = new Bishop(Black);
	board[SquareToInt(Square{ 'g',8 })] = new Knight(Black);
	board[SquareToInt(Square{ 'h',8 })] = new Rook(Black);
	board[SquareToInt(Square{ 'a',7 })] = new Pawn(Black);
	board[SquareToInt(Square{ 'b',7 })] = new Pawn(Black);
	board[SquareToInt(Square{ 'c',7 })] = new Pawn(Black);
	board[SquareToInt(Square{ 'd',7 })] = new Pawn(Black);
	board[SquareToInt(Square{ 'e',7 })] = new Pawn(Black);
	board[SquareToInt(Square{ 'f',7 })] = new Pawn(Black);
	board[SquareToInt(Square{ 'g',7 })] = new Pawn(Black);
	board[SquareToInt(Square{ 'h',7 })] = new Pawn(Black);
}

StateManager::StateManager(std::string boardString) {
	board = std::make_unique<Piece* []>(64);
	auto pieceString = boardString.substr(0, 4);
	while (pieceString.length() == 4) {
		board[SquareToInt(Square{ pieceString[2], pieceString[3] - '0' })] =
			CreateNewPiece(GetPieceType(pieceString.substr(1, 1), false), pieceString[0] - '0' == 0 ? White : Black);

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
			throw NotImplementedException();
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
			(disambiguationSource.rank != 0 && sq->rank != disambiguationSource.rank)) {
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
			p->GetPieceType() != KnightPiece ||
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

int StateManager::FindPieceFromSourceSquare(MoveCommand command, DirectionalIterator* directionalIterator) {
	int sourceSquare = -1;
	for (int dir : *directionalIterator) {
		for (Square probe : SquareSearchIterator(Square{ command.target.file , command.target.rank }, command.disambiguation, dir)) {
			auto piece = board[SquareToInt(probe)];
			if (piece == nullptr) {
				continue;
			}
			if (piece->GetPieceType() == command.type && piece->GetPlayer() == currentPlayer) {
				int potentialSource = SquareToInt(probe);
				if (sourceSquare != -1 && potentialSource != sourceSquare) {
					throw std::invalid_argument("Unexpected ambigous move");
				}
				sourceSquare = potentialSource;
			}
			break;
		}
	}
	delete directionalIterator;
	return sourceSquare;
}

int StateManager::FindPieceFromTarget(MoveCommand command) {
	switch (command.type) {
	case PawnPiece:
		return FindPawnFromSourceSquare(command.target, command.capture);
	case KnightPiece:
		return FindKnightFromSourceSquare(command.target);
	case BishopPiece:
		return FindPieceFromSourceSquare(command, new DiagonalIterator());
	case RookPiece:
		return FindPieceFromSourceSquare(command, new LevelIterator());
	case QueenPiece:
		return FindPieceFromSourceSquare(command, new DirectionalIterator());
	default:
		throw NotImplementedException();
	}
}

void StateManager::BaseMoveValidation(MoveCommand command) {
	auto pieceAtTarget = board[SquareToInt(command.target)];
	if (pieceAtTarget != nullptr) {
		if (pieceAtTarget->GetPlayer() != currentPlayer && !command.capture) {
			throw std::invalid_argument("A capturing move is required to capture a piece.");
		}
		if (pieceAtTarget->GetPlayer() == this->currentPlayer) {
			throw std::invalid_argument("Square is occupied by same player piece");
		}
	}
	else if (command.capture && !command.enPassant) {
		throw std::invalid_argument("No piece at target of capturing move");
	}
	else if (command.enPassant && enPassantCapturablePawn == -1) {
		throw std::invalid_argument("No legal en passant move.");
	}
}

MoveCommand StateManager::MoveFromInput(std::string notation) {
	if (notation.length() < 2) {
		throw std::invalid_argument("Move requires atleast target square");
	}
	MoveCommand res = MoveCommand{ Square{'\0',0},Square{'\0',0},PawnPiece,false,false,false,PawnPiece };
	if (notation[0] == 'x') {
		res.capture = true;
		notation = notation.substr(1);
	}
	PieceType type = GetPieceType(notation, false);
	if (type != PawnPiece) {
		res.type = type;
		notation = notation.substr(1);
	}
	else {
		const std::string enPassantSuffix = " e.p.";
		res.enPassant = notation.length() > enPassantSuffix.length() && notation.compare(notation.length() - enPassantSuffix.length(), enPassantSuffix.length(), enPassantSuffix) == 0;
		if (res.enPassant) {
			notation = notation.substr(0, notation.length() - enPassantSuffix.length());
		}
		else {
			PieceType promotion = GetPieceType(notation.substr(notation.length() - 1), false);
			if (promotion != PawnPiece) {
				if (promotion == KingPiece) {
					throw std::invalid_argument("Cannot promote Pawn to King");
				}
				res.promotedTo = promotion;
				res.promotion = true;
				notation = notation.substr(0, notation.length() - 1);
			}
		}
	}
	if (notation.length() > 2) {
		if (isdigit(notation[0])) {
			res.disambiguation.rank = notation[0] - '0';
			notation = notation.substr(1);
		}
		else {
			res.disambiguation.file = notation[0];
			notation = notation.substr(1);
			if (isdigit(notation[0])) {
				res.disambiguation.rank = notation[0] - '0';
				notation = notation.substr(1);
			}
		}
	}
	res.target = Square{ notation[0], notation[1] - '0' };

	return res;
}

void StateManager::Move(std::string notation)
{
	// TODO: Add regex input validation
	// TODO: Draw offer
	// TODO: Castling 
	// TODO: Check 
	// TODO: Checkmate 
	// TODO: End of game 

	MoveCommand command = MoveFromInput(notation);
	disambiguationSource = command.disambiguation;
	BaseMoveValidation(command);

	int piecePosition = FindPieceFromTarget(command);
	if (piecePosition == -1) {
		throw std::invalid_argument("Unable to execute move");
	}
	if (command.promotion) {
		delete board[piecePosition];
		board[piecePosition] = CreateNewPiece(command.promotedTo, currentPlayer == 0 ? White : Black);
	}
	int enPassantTarget = enPassantCapturablePawn;
	enPassantCapturablePawn = board[piecePosition]->GetPieceType() == PawnPiece && abs(IntToSquare(piecePosition).rank - command.target.rank) == 2
		? SquareToInt(command.target)
		: -1;

	if (command.capture && !command.enPassant) {
		delete board[SquareToInt(command.target)];
	}
	board[SquareToInt(command.target)] = board[piecePosition];
	board[piecePosition] = nullptr;
	if (command.enPassant) {
		delete board[enPassantTarget];
		board[enPassantTarget] = nullptr;
	}
	currentPlayer = 1 - currentPlayer;
}