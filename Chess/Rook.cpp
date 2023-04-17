#include "Rook.h"


std::vector<MoveCommand> Rook::PossibleMoves(std::vector<Piece*> board, Square position) {
	auto possibleMoves = std::vector<MoveCommand>();

	for (int direction : LevelIterator()) {
		for (Square probe : SquareSearchIterator(position, direction)) {
			auto piece = board[SquareToInt(probe)];
			MoveCommand command = { Square{'\0', 0}, probe, BishopPiece };
			if (piece != nullptr) {
				if (piece->GetPlayer() == GetPlayer()) {
					break;
				}
				command.capture = true;
				possibleMoves.push_back(command);
			}
			possibleMoves.push_back(command);
		}
	}

	return std::vector<MoveCommand>(possibleMoves);
}