#include "Knight.h"


std::vector<MoveCommand> Knight::PossibleMoves(std::vector<Piece*> board, Square position) {
	auto possibleMoves = std::vector<MoveCommand>();

	Square targetSquares[8] = {
		Square{(char)((int)position.file + 1), position.rank + 2},
		Square{(char)((int)position.file + 2), position.rank + 1},
		Square{(char)((int)position.file - 1), position.rank + 2},
		Square{(char)((int)position.file - 2), position.rank + 1},
		Square{(char)((int)position.file + 1), position.rank - 2},
		Square{(char)((int)position.file + 2), position.rank - 1},
		Square{(char)((int)position.file - 1), position.rank - 2},
		Square{(char)((int)position.file - 2), position.rank - 1},
	};

	for (int i = 0; i < 8; i++) {
		Square* sq = &targetSquares[i];
		
		if (!SquareInBoard(sq)) {
			continue;
		}
		int squareInt = SquareToInt(targetSquares[i]);
		Piece* p = board[squareInt];
		if (p != nullptr &&
			p->GetPlayer() == GetPlayer()) {
			continue;
		}
		MoveCommand command = { Square{'\0', 0}, targetSquares[i], BishopPiece };
		possibleMoves.push_back(command);
	}
	return std::vector<MoveCommand>(possibleMoves);
}

