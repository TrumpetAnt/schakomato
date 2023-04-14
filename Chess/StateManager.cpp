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
	whiteKingLocation = Square{ 'e',1 };

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
	blackKingLocation = Square{ 'e',8 };
}

StateManager::StateManager(std::string boardString) {
	board = std::make_unique<Piece* []>(64);
	auto pieceString = boardString.substr(0, 4);
	while (pieceString.length() == 4) {
		int position = SquareToInt(Square{ pieceString[2], pieceString[3] - '0' });
		auto piece = CreateNewPiece(GetPieceType(pieceString.substr(1, 1), false), pieceString[0] - '0' == 0 ? White : Black);
		board[position] = piece;
		
		if (piece->GetPieceType() == KingPiece) {
			if (piece->GetPlayer() == White) {
				this->whiteKingLocation = IntToSquare(position);
			}
			else {
				this->blackKingLocation = IntToSquare(position);
			}
		}

		boardString = boardString.substr(4);
		pieceString = boardString.substr(0, 4);
	}
}

StateManager::StateManager(const StateManager& other) {
	board = std::move(other.GetStateCopy());
	whiteKingLocation = other.whiteKingLocation;
	blackKingLocation = other.blackKingLocation;
	currentPlayer = other.currentPlayer;
}

StateManager::~StateManager() {
	for (int i = 0; i < 64; i++) {
		if (board[i] != nullptr) {
			delete board[i];
		}
	}
	board.reset();
}

bool StateManager::CheckStateForCheck(MoveCommand command, int piecePosition, int enPassantTarget) {
	auto stateClone = Clone();
	stateClone->ExecuteMove(command, piecePosition, enPassantTarget);
	
	MoveCommand testCommand;
	testCommand.enPassant = false;
	testCommand.capture = true;
	testCommand.target = stateClone->currentPlayer == White ? stateClone->blackKingLocation : stateClone->whiteKingLocation;
	testCommand.promotion = testCommand.target.rank == (stateClone->currentPlayer == White ? 8 : 1);
	testCommand.promotedTo = QueenPiece;
	testCommand.disambiguation = Square{ '\0',0 };
	if (testCommand.target == Square{ '\0',0 }) {
		delete stateClone;
		return false;
	}
	for (PieceType p : PieceTypeIterator()) {
		testCommand.type = p;
		std::vector<int>* pieces = stateClone->FindPieceFromTarget(testCommand);
		bool inCheck = pieces->size() > 0;
		pieces->clear();
		delete pieces;
		if (inCheck) {
			delete stateClone;
			return true;
		}
	}

	delete stateClone;

	return false;
}

std::unique_ptr<Piece* []> StateManager::GetStateCopy() const {
	auto result = std::make_unique<Piece* []>(64);
	for (int i = 0; i < 64; i++) {
		if (board[i] != nullptr) {
			result[i] = board[i]->Copy();
		}
	}
	return std::move(result);
}

StateManager* StateManager::Clone() const {
	auto cloneState = new StateManager();
	cloneState->board = std::move(GetStateCopy());
	cloneState->whiteKingLocation = whiteKingLocation;
	cloneState->blackKingLocation = blackKingLocation;
	cloneState->currentPlayer = currentPlayer;
	return cloneState;
}

std::vector<int>* StateManager::FindPawnFromSourceSquare(MoveCommand command) {
	std::vector<int>* res= new std::vector<int>();
	int rankModifier = currentPlayer == White ? -1 : 1;
	if (!command.capture) {
		auto pieceAtTarget = board[SquareToInt(Square{ command.target.file, command.target.rank + rankModifier })];
		if (pieceAtTarget != nullptr && pieceAtTarget->GetPlayer() == currentPlayer) {
			res->push_back( SquareToInt(Square{ command.target.file, command.target.rank + rankModifier }));
		}
		auto secondPiece = board[SquareToInt(Square{ command.target.file, command.target.rank + rankModifier * 2 })];
		if (command.target.rank == (currentPlayer == White ? 4 : 5) &&
			secondPiece != nullptr &&
			pieceAtTarget == nullptr) {
			res->push_back(SquareToInt(Square{ command.target.file, command.target.rank + rankModifier * 2 }));
		}
	}
	else {
		if (command.disambiguation.file != '\0') {
			command.disambiguation.rank = command.target.rank + rankModifier;
			auto capturingPiece = board[SquareToInt(command.disambiguation)];
			if (capturingPiece != nullptr && capturingPiece->GetPlayer() == currentPlayer) {
				res->push_back( SquareToInt(command.disambiguation));
			}
			return res;
		}
		auto capturingPieceA = board[SquareToInt(Square{ (char)(command.target.file - 1), command.target.rank + rankModifier })];
		auto capturingPieceB = board[SquareToInt(Square{ (char)(command.target.file + 1), command.target.rank + rankModifier })];
		if (capturingPieceA != nullptr && capturingPieceA->GetPlayer() == currentPlayer) {
			res->push_back( SquareToInt(Square{ (char)(command.target.file - 1), command.target.rank + rankModifier }));
		}
		if (capturingPieceB != nullptr && capturingPieceB->GetPlayer() == currentPlayer) {
			res->push_back(SquareToInt(Square{ (char)(command.target.file + 1), command.target.rank + rankModifier }));
		}
	}

	return res;
}

std::vector<int>* StateManager::FindKnightFromSourceSquare(MoveCommand command) {
	std::vector<int>* res = new std::vector<int>();
	Square sourceSquares[8] = {
		Square{(char)((int)command.target.file + 1), command.target.rank + 2},
		Square{(char)((int)command.target.file + 2), command.target.rank + 1},
		Square{(char)((int)command.target.file - 1), command.target.rank + 2},
		Square{(char)((int)command.target.file - 2), command.target.rank + 1},
		Square{(char)((int)command.target.file + 1), command.target.rank - 2},
		Square{(char)((int)command.target.file + 2), command.target.rank - 1},
		Square{(char)((int)command.target.file - 1), command.target.rank - 2},
		Square{(char)((int)command.target.file - 2), command.target.rank - 1},
	};

	for (int i = 0; i < 8; i++) {
		Square* sq = &sourceSquares[i];
		if ((command.disambiguation.file != '\0' && sq->file != command.disambiguation.file) ||
			(command.disambiguation.rank != 0 && sq->rank != command.disambiguation.rank)) {
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
		res->push_back( squareInt);
	}
	return res;
}

std::vector<int>* StateManager::FindKingPieceFromSourceSquare(MoveCommand command) {
	std::vector<int>* res = new std::vector<int>();
	for (int dir : DirectionalIterator()) {
		for (Square probe : SquareSearchIterator(Square{ command.target.file , command.target.rank }, dir, true)) {
			auto piece = board[SquareToInt(probe)];
			if (piece == nullptr) {
				continue;
			}
			if (piece->GetPieceType() == command.type && piece->GetPlayer() == currentPlayer) {
				res->push_back(SquareToInt(probe));
			}
			break;
		}
	}
	return res;
}

std::vector<int>* StateManager::FindPieceFromSourceSquare(MoveCommand command, DirectionalIterator* directionalIterator) {
	std::vector<int>* res = new std::vector<int>();
	for (int dir : *directionalIterator) {
		for (Square probe : SquareSearchIterator(Square{ command.target.file , command.target.rank }, command.disambiguation, dir)) {
			auto piece = board[SquareToInt(probe)];
			if (piece == nullptr) {
				continue;
			}
			if (piece->GetPieceType() == command.type && piece->GetPlayer() == currentPlayer) {
				res->push_back(SquareToInt(probe));
			}
			break;
		}
	}
	delete directionalIterator;
	return res;
}

std::vector<int>* StateManager::FindPieceFromTarget(MoveCommand command) {
	switch (command.type) {
	case PawnPiece:
		return FindPawnFromSourceSquare(command);
	case KnightPiece:
		return FindKnightFromSourceSquare(command);
	case BishopPiece:
		return FindPieceFromSourceSquare(command, new DiagonalIterator());
	case RookPiece:
		return FindPieceFromSourceSquare(command, new LevelIterator());
	case QueenPiece:
		return FindPieceFromSourceSquare(command, new DirectionalIterator());
	case KingPiece:
		return FindKingPieceFromSourceSquare(command);
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
	MoveCommand res = MoveCommand{ Square{ '\0' , 0 }, Square{ '\0' , 0 }, PawnPiece, false, false, false, PawnPiece };
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

	if (Completed()) {
		throw std::invalid_argument("Game over");
	}

	MoveCommand command = MoveFromInput(notation);
	BaseMoveValidation(command);

	std::vector<int>* possibleMoves = FindPieceFromTarget(command);
	while (possibleMoves->size() > 1 && ((*possibleMoves)[possibleMoves->size() - 2] == (*possibleMoves)[possibleMoves->size() - 1])) {
		possibleMoves->pop_back();
	}
	if (possibleMoves->size() != 1) {
		throw std::invalid_argument("Expected single possible move, got " + (possibleMoves->size() + '0'));
	}
	int piecePosition = possibleMoves->front();
	possibleMoves->clear();
	delete possibleMoves;
	if (command.promotion) {
		delete board[piecePosition];
		board[piecePosition] = CreateNewPiece(command.promotedTo, currentPlayer == 0 ? White : Black);
	}
	int enPassantTarget = enPassantCapturablePawn;
	enPassantCapturablePawn = board[piecePosition]->GetPieceType() == PawnPiece && abs(IntToSquare(piecePosition).rank - command.target.rank) == 2
		? SquareToInt(command.target)
		: -1;

	if (CheckStateForCheck(command, piecePosition, enPassantTarget)) {
		throw std::invalid_argument("Illegal move, cannot put king in check.");
	}
	ExecuteMove(command, piecePosition, enPassantTarget);

	if (CheckForMate()) {
		completed = true;
	}
}

void StateManager::ExecuteMove(MoveCommand command, int piecePosition, int enPassantTarget) {
	if (command.capture && !command.enPassant) {
		delete board[SquareToInt(command.target)];
	}
	board[SquareToInt(command.target)] = board[piecePosition];
	board[piecePosition] = nullptr;
	if (command.enPassant) {
		delete board[enPassantTarget];
		board[enPassantTarget] = nullptr;
	}
	if (command.type == KingPiece) {
		if (currentPlayer == White) {
			whiteKingLocation = command.target;
		}
		else {
			blackKingLocation = command.target;
		}
	}
	currentPlayer = 1 - currentPlayer;
}

std::unique_ptr<std::vector<Piece*>> StateManager::Pieces(Color player) {
	auto res = std::make_unique< std::vector<Piece*>>(std::vector<Piece*>());

	for (int position = 0; position < 64; position++) {
		auto piece = board[position];
		Square temp = IntToSquare(position);
		if (piece != nullptr && piece->GetPlayer() == player) {
			res->push_back(piece);
		}
	}

	return std::move(res);
}

bool StateManager::CheckForMate() {
	// TODO make it possible for draw
	int enPassantTarget = 0;
	for (int position = 0; position < 64; position++) {
		auto piece = board[position];
		if (piece != nullptr && piece->GetPlayer() == currentPlayer) {
			auto possibleMoves = piece->PossibleMoves(std::move(GetStateCopy()), IntToSquare(position));
			for (auto move : *possibleMoves) {
				if (piece->GetPieceType() == PawnPiece && move.enPassant) {
					int playerDirection = currentPlayer == White ? -1 : 1;
					enPassantTarget = SquareToInt(Square{ move.target.file, move.target.rank + playerDirection });
				}
				if (!CheckStateForCheck(move, position, enPassantTarget)) {
					return false;
				}
			}
			possibleMoves.reset();
		}
	}
	return true;
}
