#include "Queen.h"

std::unique_ptr<std::vector<MoveCommand>> Queen::PossibleMoves(std::unique_ptr<Piece*[]> board, Square position) {
	auto possibleMoves = new std::vector<MoveCommand>();

	for (int direction : DirectionalIterator()) {
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

	return std::make_unique<std::vector<MoveCommand>>(*possibleMoves);
}