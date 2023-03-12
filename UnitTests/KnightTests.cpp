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
		state->Move("Nc3");
		state->Move("Nf6");

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

	TEST(KnightMovement, NoCapture_FriendlyPiece_ThrowException) {
		// Arrange
		StateManager* state = new StateManager();

		// Act
		EXPECT_ANY_THROW(state->Move("Nd2"));
	}

	TEST(KnightMovement, NoCapture_CornerMoves) {
		// Arrange
		StateManager* state = new StateManager();

		// Act
		state->Move("Na3");
		state->Move("Nh6");
		state->Move("Nb1");
		state->Move("Ng8");
		state->Move("Nh3");
		state->Move("Na6");
		state->Move("Ng1");
		state->Move("Nb8");

		// Assert
		auto board = state->GetStateCopy();
		Piece* result;

		result = board[SquareToInt(Square{ 'b', 1 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'g', 1 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'b', 8 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'g', 8 })];
		EXPECT_NE(nullptr, result);
	}

	TEST(KnightCapture, Captures) {
		// Arrange
		auto str = slurp("C:\\Source\\Chess\\UnitTests\\KnightMovementTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		state->Move("xNa3");

		// Assert
		auto board = state->GetStateCopy();
		Piece* result;

		result = board[SquareToInt(Square{ 'a', 3 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'b', 1 })];
		EXPECT_EQ(nullptr, result);
	}

	TEST(KnightCapture, CaptureDisambiguation) {
		// Arrange
		auto str = slurp("C:\\Source\\Chess\\UnitTests\\KnightMovementTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		state->Move("xNdc3");

		// Assert
		auto board = state->GetStateCopy();
		Piece* result;

		result = board[SquareToInt(Square{ 'b', 1 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'c', 3 })];
		EXPECT_NE(nullptr, result);

		result = board[SquareToInt(Square{ 'd', 1 })];
		EXPECT_EQ(nullptr, result);
	}

}