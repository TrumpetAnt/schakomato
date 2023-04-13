#include "Pawn.h"

inline bool AtInitialPosition(int rank, Color player) {
	return (player == White && rank == 2) || (player == Black && rank == 7);
}

inline bool AtPromotionRank(int rank, Color player) {
	return (player == White && rank == 8) || (player == Black && rank == 1);
}

MoveCommand Pawn::CreateMoveCommand(Square target, bool capture, PieceType promotedTo) {
	MoveCommand command = { Square{'\0', 0}, target, PawnPiece, capture };
	if (AtPromotionRank(target.rank, GetPlayer())) {
		command.promotion = true;
		command.promotedTo = promotedTo;
	}
	return command;
}

std::unique_ptr<std::vector<MoveCommand>> Pawn::PossibleMoves(std::unique_ptr<Piece*[]> board, Square position) {
	auto possibleMoves = new std::vector<MoveCommand>();

	int rankModifier = GetPlayer() == White ? 1 : -1;
	auto probe = Square{ position.file, position.rank + rankModifier };
	auto pieceAtTarget = board[SquareToInt(probe)];

	if (pieceAtTarget == nullptr) {
		possibleMoves->push_back(CreateMoveCommand(probe, false));
		if (possibleMoves->end()->promotion) {
			possibleMoves->push_back(CreateMoveCommand(probe, false, KnightPiece));
		}
	}
	probe = Square{ position.file, position.rank + rankModifier * 2};
	auto secondPiece = board[SquareToInt(probe)];
	if (pieceAtTarget == nullptr && secondPiece == nullptr && AtInitialPosition(position.rank, GetPlayer())) {
		possibleMoves->push_back(CreateMoveCommand(probe, false));
		if (possibleMoves->end()->promotion) {
			possibleMoves->push_back(CreateMoveCommand(probe, false, KnightPiece));
		}
	}
	auto probeCaptureLeft = Square{ (char)(position.file - 1), position.rank + rankModifier };
	auto probeCaptureRight = Square{ (char)(position.file + 1), position.rank + rankModifier };
	auto targetLeft = board[SquareToInt(probeCaptureLeft)];
	auto targetRight = board[SquareToInt(probeCaptureRight)];
	if (!CaptureIfPossible(targetLeft, probeCaptureLeft, possibleMoves)) {
		targetLeft = board[SquareToInt(Square{ probeCaptureLeft.file, probeCaptureLeft.rank + rankModifier })];
		if (CaptureIfPossible(targetLeft, probeCaptureLeft, possibleMoves)) {
			possibleMoves->end()->enPassant = true;
		}
	}
	if (!CaptureIfPossible(targetRight, probeCaptureRight, possibleMoves)) {
		targetRight = board[SquareToInt(Square{ probeCaptureRight.file, probeCaptureRight.rank + rankModifier })];
		if (CaptureIfPossible(targetRight, probeCaptureRight, possibleMoves)) {
			possibleMoves->end()->enPassant = true;
		}
	}
	return std::make_unique<std::vector<MoveCommand>>(*possibleMoves);
}

bool Pawn::CaptureIfPossible(Piece* targetPiece, const Square& target, std::vector<MoveCommand>* possibleMoves)
{
	if (targetPiece != nullptr && targetPiece->GetPlayer() != GetPlayer()) {
		possibleMoves->push_back(CreateMoveCommand(target, true));
		if (possibleMoves->end()->promotion) {
			possibleMoves->push_back(CreateMoveCommand(target, true, KnightPiece));
		}
		return true;
	}
	return false;
}
