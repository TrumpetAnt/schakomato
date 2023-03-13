#include "pch.h"
#include <string>
#include <fstream>
#include <windows.h>
#include "StateManager.h"

namespace BishopTests {
	std::string slurp(std::string filePath) {
		std::ifstream in;
		in.open(filePath);
		std::ostringstream sstr;
		sstr << in.rdbuf();
		return sstr.str();
	}

	TEST(BishopMovement, NoCapture_BothPlayers) {
		// Arrange
		auto str = slurp("C:\\Source\\Chess\\UnitTests\\BishopMovementTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		state->Move("Bh8");
		state->Move("Bh1");

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

	TEST(BishopMovement, NoCapture_FriendlyPiece_ThrowException) {
		// Arrange
		auto str = slurp("C:\\Source\\Chess\\UnitTests\\BishopMovementTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("Bc2"));
	}

	TEST(BishopMovement, NoCapture_MoveOverPiece_ThrowException) {
		// Arrange
		auto str = slurp("C:\\Source\\Chess\\UnitTests\\BishopMovementTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("Bd3"));
	}

	TEST(BishopCapture, Captures) {
		// Arrange
		auto str = slurp("C:\\Source\\Chess\\UnitTests\\BishopCaptureTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		state->Move("xBa8");

		// Assert
		auto board = state->GetStateCopy();
		Piece* result;

		result = board[SquareToInt(Square{ 'a', 8 })];
		EXPECT_NE(nullptr, result);
		EXPECT_EQ(BishopPiece, result->GetPieceType());
		EXPECT_EQ(White, result->GetPlayer());

		result = board[SquareToInt(Square{ 'h', 1 })];
		EXPECT_EQ(nullptr, result);
	}

	TEST(BishopCapture, CaptureDisambiguation) {
		// Arrange
		auto str = slurp("C:\\Source\\Chess\\UnitTests\\BishopCaptureTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		state->Move("xBe1c3");

		// Assert
		auto board = state->GetStateCopy();
		Piece* result;

		result = board[SquareToInt(Square{ 'a', 1 })];
		EXPECT_NE(nullptr, result);
		result = board[SquareToInt(Square{ 'c', 3 })];
		EXPECT_NE(nullptr, result);
		result = board[SquareToInt(Square{ 'e', 5 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'e', 1 })];
		EXPECT_EQ(nullptr, result);
	}

	TEST(BishopCapture, CaptureDisambiguation_MissingSource_ThrowsException) {
		// Arrange
		auto str = slurp("C:\\Source\\Chess\\UnitTests\\BishopMovementTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("Bcb1"));
	}
}