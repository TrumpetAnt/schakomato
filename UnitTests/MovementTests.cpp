#include "pch.h"
#include <string>
#include <fstream>
#include <windows.h>
#include "StateManager.h"

std::string slurp(std::string filePath) {
	std::ifstream in;
	in.open(filePath);
	std::ostringstream sstr;
	sstr << in.rdbuf();
	return sstr.str();
}

TEST(PawnMovement, NoCapture_BothPlayers) {
	// Arrange
	StateManager* state = new StateManager();

	// Act
	state->Move("e4");
	state->Move("d5");

	// Assert
	auto board = state->GetStateCopy();
	Piece* result;

	result = board[SquareToInt(Square{ 'e', 4 })];
	EXPECT_NE(nullptr, result);

	result = board[SquareToInt(Square{ 'd', 5 })];
	EXPECT_NE(nullptr, result);

	result = board[SquareToInt(Square{ 'e', 2 })];
	EXPECT_EQ(nullptr, result);

	result = board[SquareToInt(Square{ 'd', 7 })];
	EXPECT_EQ(nullptr, result);
}

void AssertSquareNull(Square square, std::unique_ptr<Piece* []>* board) {
	auto result = (*board)[SquareToInt(square)];
	EXPECT_EQ(nullptr, result);
}

void AssertSquareNotNull(Square square, std::unique_ptr<Piece* []>* board) {
	auto result = (*board)[SquareToInt(square)];
	EXPECT_NE(nullptr, result);
}

TEST(PawnMovement, NoCapture_SingleMove) {
	// Arrange
	StateManager* state = new StateManager();

	// Act
	state->Move("e3");

	// Assert
	auto board = state->GetStateCopy();
	Piece* result;

	AssertSquareNotNull(Square{ 'e', 3 }, &board);
	AssertSquareNull(Square{ 'e', 2 }, &board);
}

TEST(PawnMovement, NoCapture_SingleMove_ThrowsException_MovingToCapture) {
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
	EXPECT_ANY_THROW(state->Move("e7"));
}

TEST(PawnMovement, NoCapture_SingleMove_ThrowsException_NoPieceFound) {
	// Arrange
	auto str = slurp("C:\\Source\\Chess\\UnitTests\\PawnMovementTest.txt");
	StateManager* state = new StateManager(str);

	// Assert
	EXPECT_ANY_THROW(state->Move("b4"));
}

TEST(PawnMovement, NoCapture_SingleMove_ThrowsException_MovingToOccupiedSquare) {
	// Arrange
	auto str = slurp("C:\\Source\\Chess\\UnitTests\\PawnMovementTest.txt");
	StateManager* state = new StateManager(str);

	// Assert
	EXPECT_ANY_THROW(state->Move("a4"));
}

TEST(PawnMovement, NoCapture_DoubleMove_ThrowsException_MovingOverSquare) {
	// Arrange
	auto str = slurp("C:\\Source\\Chess\\UnitTests\\PawnMovementTest.txt");
	EXPECT_NE(0, str.length());

	StateManager* state = new StateManager(str);

	// Assert
	EXPECT_ANY_THROW(state->Move("e4"));
}

TEST(PawnMovement, NoCapture_DoubleMove_ThrowsException_NonStartingSquare) {
	// Arrange
	StateManager* state = new StateManager();

	// Act
	state->Move("e3");
	state->Move("d5");

	// Assert
	EXPECT_ANY_THROW(state->Move("e5"));
}

TEST(PawnMovement, NoCapture_MultipleMoves) {
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
	auto board = state->GetStateCopy();
	Piece* result;

	result = board[SquareToInt(Square{ 'e', 6 })];
	EXPECT_NE(nullptr, result);

	result = board[SquareToInt(Square{ 'd', 3 })];
	EXPECT_NE(nullptr, result);

	result = board[SquareToInt(Square{ 'e', 2 })];
	EXPECT_EQ(nullptr, result);
	result = board[SquareToInt(Square{ 'e', 3 })];
	EXPECT_EQ(nullptr, result);
	result = board[SquareToInt(Square{ 'e', 4 })];
	EXPECT_EQ(nullptr, result);
	result = board[SquareToInt(Square{ 'e', 5 })];
	EXPECT_EQ(nullptr, result);

	result = board[SquareToInt(Square{ 'd', 7 })];
	EXPECT_EQ(nullptr, result);
	result = board[SquareToInt(Square{ 'd', 6 })];
	EXPECT_EQ(nullptr, result);
	result = board[SquareToInt(Square{ 'd', 5 })];
	EXPECT_EQ(nullptr, result);
	result = board[SquareToInt(Square{ 'd', 4 })];
	EXPECT_EQ(nullptr, result);
}