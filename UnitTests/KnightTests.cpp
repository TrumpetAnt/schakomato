#include "pch.h"
#include <string>
#include <fstream>
#include <windows.h>
#include "StateManager.h"

namespace KnightTests {
	std::string slurp(std::string filePath) {
		std::ifstream in;
		in.open(filePath);
		std::ostringstream sstr;
		sstr << in.rdbuf();
		return sstr.str();
	}

	TEST(KnightMovement, NoCapture_BothPlayers) {
		// Arrange
		StateManager* state = new StateManager();

		// Act
		state->Move("Kc3");
		state->Move("Kf6");

		// Assert
		auto board = state->GetStateCopy();
		Piece* result;

		result = board[SquareToInt(Square{ 'c', 3 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'f', 6 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'b', 1 })];
		EXPECT_EQ(nullptr, result);

		result = board[SquareToInt(Square{ 'g', 8 })];
		EXPECT_EQ(nullptr, result);
	}

}