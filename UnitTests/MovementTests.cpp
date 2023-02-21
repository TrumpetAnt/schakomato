#include "pch.h"
#include <string>
#include <fstream>
#include "../Chess/StateManager.h"
#include "../Chess/VectorUtils.h"
#include "../Chess/Piece.h"

typedef bool (*ptr)(Piece*);
typedef ptr(*pm)();

int summation(int a, int b) {
	return a + b;
}

ptr FindAux(Piece* param) {
	return [param](Piece* p) { return p == param; };
}

TEST(GameplayTest, PawnMovement_NoCapture) {
	// Arrange
	StateManager& state = StateManager();

	// Act
	state.Move("d5");
	state.Move("e4");


	// Assert
	std::vector<Piece*>* pieces = state.GetBoard();


	Find(pieces, );


	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}