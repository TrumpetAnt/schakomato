#include "Bishop.h"

std::unique_ptr<std::vector<MoveCommand>> Bishop::PossibleMoves(Piece** board, Square position) {
	auto possibleMoves = std::make_unique<std::vector<MoveCommand>>();

	for (int direction : DiagonalIterator()) {
		for (Square probe : SquareSearchIterator(position, direction)) {
			auto piece = board[SquareToInt(probe)];
			MoveCommand command = { Square{'\0', 0}, probe, BishopPiece };
			if (piece != nullptr) {
				if (piece->GetPlayer() == GetPlayer()) {
					break;
				}
				command.capture = true;
				possibleMoves->push_back(command);
			}
			possibleMoves->push_back(command);
		}
	}

	return possibleMoves;
}