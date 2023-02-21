#include "pch.h"
#include <string>
#include <fstream>
#include "../Chess/StateManager.h"
#include "../Chess/VectorUtils.h"
#include "../Chess/Piece.h"
#include "../Chess/PieceUtils.h"

typedef bool (*ptr)(Piece*);
typedef ptr(*pm)();

int summation(int a, int b) {
	return a + b;
}


bool TestFunction(Piece* param) {
	return true;
}

bool TestForInt(int* x) {
	return true;
}

TEST(GameplayTest, PawnMovement_NoCapture) {
	// Arrange
	StateManager& state = StateManager();

	// Act
	state.Move("e4");
	state.Move("d5");


	// Assert
	std::vector<Piece*>* pieces = state.GetBoard();
	Piece* result;

	result = Find(pieces, FindPieceAux(Pawn, 0, Square{ 'E', 3 }));
	EXPECT_NE(nullptr, result);

	result = Find(pieces, FindPieceAux(Pawn, 1, Square{ 'D', 4 }));
	EXPECT_NE(nullptr, result);

	result = Find(pieces, FindPieceAux(Pawn, 0, Square{ 'E', 1 }));
	EXPECT_EQ(nullptr, result);

	result = Find(pieces, FindPieceAux(Pawn, 1, Square{ 'D', 6 }));
	EXPECT_EQ(nullptr, result);
}