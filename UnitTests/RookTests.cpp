#include "pch.h"
#include <string>
#include <fstream>
#include <windows.h>
#include "StateManager.h"

namespace RookTests {
	std::string slurp(std::string filePath) {
		std::ifstream in;
		in.open(filePath);
		std::ostringstream sstr;
		sstr << in.rdbuf();
		return sstr.str();
	}

	TEST(RookMovement, NoCapture_BothPlayers) {
		// Arrange
		auto str = slurp("../../UnitTests/RookMovementTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		state->Move("Rh8");
		state->Move("Rh1");

		// Assert
		auto board = state->GetStateCopy();
		Piece* result;

		result = board[SquareToInt(Square{ 'h', 8 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'h', 1 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'a', 1 })];
		EXPECT_EQ(nullptr, result);

		result = board[SquareToInt(Square{ 'a', 8 })];
		EXPECT_EQ(nullptr, result);
	}

	TEST(RookMovement, NoCapture_FriendlyPiece_ThrowException) {
		// Arrange
		auto str = slurp("../../UnitTests/RookMovementTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("Rc2"));
	}

	TEST(RookMovement, NoCapture_MoveOverPiece_ThrowException) {
		// Arrange
		auto str = slurp("../../UnitTests/RookMovementTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("Rd3"));
	}

	TEST(RookCapture, Captures) {
		// Arrange
		auto str = slurp("../../UnitTests/RookCaptureTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		state->Move("xRb8");

		// Assert
		auto board = state->GetStateCopy();
		Piece* result;

		result = board[SquareToInt(Square{ 'b', 8 })];
		EXPECT_NE(nullptr, result);
		EXPECT_EQ(RookPiece, result->GetPieceType());
		EXPECT_EQ(White, result->GetPlayer());

		result = board[SquareToInt(Square{ 'h', 1 })];
		EXPECT_EQ(nullptr, result);
	}

	TEST(RookCapture, CaptureDisambiguation) {
		// Arrange
		auto str = slurp("../../UnitTests/RookCaptureTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		state->Move("xRe1c1");

		// Assert
		auto board = state->GetStateCopy();
		Piece* result;

		result = board[SquareToInt(Square{ 'a', 1 })];
		EXPECT_NE(nullptr, result);
		result = board[SquareToInt(Square{ 'c', 1 })];
		EXPECT_NE(nullptr, result);
		result = board[SquareToInt(Square{ 'c', 3 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'e', 1 })];
		EXPECT_EQ(nullptr, result);
	}

	TEST(RookCapture, CaptureDisambiguation_MissingSource_ThrowsException) {
		// Arrange
		auto str = slurp("../../UnitTests/RookMovementTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("Rcb1"));
	}
}