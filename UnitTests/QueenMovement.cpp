#include "pch.h"
#include <string>
#include <fstream>
#include <windows.h>
#include "StateManager.h"

namespace QueenTests {
	std::string slurp(std::string filePath) {
		std::ifstream in;
		in.open(filePath);
		std::ostringstream sstr;
		sstr << in.rdbuf();
		return sstr.str();
	}

	TEST(QueenCapture, Captures) {
		// Arrange
		auto str = slurp("../../UnitTests/QueenCaptureTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		state->Move("xQf3");

		// Assert
		auto board = state->GetStateCopy();
		Piece* result;

		result = board[SquareToInt(Square{ 'f', 3 })];
		EXPECT_NE(nullptr, result);
		EXPECT_EQ(QueenPiece, result->GetPieceType());
		EXPECT_EQ(White, result->GetPlayer());

		result = board[SquareToInt(Square{ 'f', 5 })];
		EXPECT_EQ(nullptr, result);
	}

	TEST(QueenMovement, NoCaptures) {
		// Arrange
		auto str = slurp("../../UnitTests/QueenMovementTest.txt");
		EXPECT_TRUE(str.length() > 0);
		StateManager* state = new StateManager(str);

		// Act
		state->Move("Qe2");
		state->Move("Qg8");

		// Assert
		auto board = state->GetStateCopy();
		Piece* result;

		result = board[SquareToInt(Square{ 'g', 8 })];
		EXPECT_NE(nullptr, result);
		result = board[SquareToInt(Square{ 'e', 2 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'e', 3 })];
		EXPECT_EQ(nullptr, result);
		result = board[SquareToInt(Square{ 'f', 7 })];
		EXPECT_EQ(nullptr, result);
	}
}