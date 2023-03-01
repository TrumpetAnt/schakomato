#include "pch.h"
#include <string>
#include <fstream>
#include "StateManager.h"

TEST(GameplayTest, PawnMovement_NoCapture) {
	// Arrange
	StateManager* state = new StateManager();

	// Act
	state->Move("e4");
	state->Move("d5");

	// Assert
	std::vector<Piece*>* pieces = state->GetBoard();
	Piece* result;

	result = Find(pieces, FindPieceAux(Pawn, 0, Square{ 'e', 4 }));
	EXPECT_NE(nullptr, result);

	result = Find(pieces, FindPieceAux(Pawn, 1, Square{ 'd', 5 }));
	EXPECT_NE(nullptr, result);

	result = Find(pieces, FindPieceAux(Pawn, 0, Square{ 'e', 2 }));
	EXPECT_EQ(nullptr, result);

	result = Find(pieces, FindPieceAux(Pawn, 1, Square{ 'd', 7 }));
	EXPECT_EQ(nullptr, result);
}
TEST(GameplayTest, PawnMovement_NoCapture_MultipleMoves) {
	// Arrange
	StateManager* state = new StateManager();

	// Act
	state->Move("e4");
	state->Move("d5");

	state->Move("e5");
	state->Move("d4");
	state->Move("e6");
	state->Move("d3");

	// Assert
	std::vector<Piece*>* pieces = state->GetBoard();
	Piece* result;

	result = Find(pieces, FindPieceAux(Pawn, 0, Square{ 'e', 6 }));
	EXPECT_NE(nullptr, result);

	result = Find(pieces, FindPieceAux(Pawn, 1, Square{ 'd', 3 }));
	EXPECT_NE(nullptr, result);

	result = Find(pieces, FindPieceAux(Pawn, 0, Square{ 'e', 2 }));
	EXPECT_EQ(nullptr, result);
	result = Find(pieces, FindPieceAux(Pawn, 0, Square{ 'e', 3 }));
	EXPECT_EQ(nullptr, result);
	result = Find(pieces, FindPieceAux(Pawn, 0, Square{ 'e', 4 }));
	EXPECT_EQ(nullptr, result);
	result = Find(pieces, FindPieceAux(Pawn, 0, Square{ 'e', 5 }));
	EXPECT_EQ(nullptr, result);

	result = Find(pieces, FindPieceAux(Pawn, 1, Square{ 'd', 7 }));
	EXPECT_EQ(nullptr, result);
	result = Find(pieces, FindPieceAux(Pawn, 1, Square{ 'd', 6 }));
	EXPECT_EQ(nullptr, result);
	result = Find(pieces, FindPieceAux(Pawn, 1, Square{ 'd', 5 }));
	EXPECT_EQ(nullptr, result);
	result = Find(pieces, FindPieceAux(Pawn, 1, Square{ 'd', 4 }));
	EXPECT_EQ(nullptr, result);
}