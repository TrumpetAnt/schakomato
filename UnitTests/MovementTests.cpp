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

TEST(PawnCapturing, Capture_SingleMove) {
	auto str = slurp("C:\\Source\\Chess\\UnitTests\\PawnCapturingTest.txt");
	EXPECT_NE(0, str.length());
	// Arrange
	StateManager* state = new StateManager(str);

	// Act
	state->Move("xb3");

	// Assert
	auto board = state->GetStateCopy();
	Piece* result;

	AssertSquareNotNull(Square{ 'b', 3 }, &board);
	AssertSquareNull(Square{ 'a', 2 }, &board);

	EXPECT_EQ(White, board[SquareToInt(Square{ 'b', 3 })]->GetPlayer());
}

TEST(PawnCapturing, Capture_SingleMove_SecondOption) {
	auto str = slurp("C:\\Source\\Chess\\UnitTests\\PawnCapturingTest.txt");
	EXPECT_NE(0, str.length());
	// Arrange
	StateManager* state = new StateManager(str);

	// Act
	state->Move("xc3");

	// Assert
	auto board = state->GetStateCopy();
	Piece* result;

	AssertSquareNotNull(Square{ 'c', 3 }, &board);
	AssertSquareNull(Square{ 'd', 2 }, &board);

	EXPECT_EQ(White, board[SquareToInt(Square{ 'c', 3 })]->GetPlayer());
}

TEST(PawnCapturing, Capture_MultipleCaptures) {
	auto str = slurp("C:\\Source\\Chess\\UnitTests\\PawnCapturingTest.txt");
	EXPECT_NE(0, str.length());
	// Arrange
	StateManager* state = new StateManager(str);

	// Act
	state->Move("xb3");
	state->Move("xa6");
	state->Move("xc3");
	state->Move("xd4");

	// Assert
	auto board = state->GetStateCopy();
	Piece* result;

	AssertSquareNotNull(Square{ 'b', 3 }, &board);
	AssertSquareNotNull(Square{ 'a', 6 }, &board);
	AssertSquareNotNull(Square{ 'c', 3 }, &board);
	AssertSquareNotNull(Square{ 'd', 4 }, &board);
	AssertSquareNull(Square{ 'a', 2 }, &board);
	AssertSquareNull(Square{ 'b', 7 }, &board);
	AssertSquareNull(Square{ 'd',2 }, &board);
	AssertSquareNull(Square{ 'c', 5 }, &board);

	EXPECT_EQ(White, board[SquareToInt(Square{ 'b', 3 })]->GetPlayer());
	EXPECT_EQ(Black, board[SquareToInt(Square{ 'a', 6 })]->GetPlayer());
	EXPECT_EQ(White, board[SquareToInt(Square{ 'c', 3 })]->GetPlayer());
	EXPECT_EQ(Black, board[SquareToInt(Square{ 'd', 4 })]->GetPlayer());
}

TEST(PawnCapturing, Capture_ThrowsException_NoTarget) {
	auto str = slurp("C:\\Source\\Chess\\UnitTests\\PawnCapturingTest.txt");
	EXPECT_NE(0, str.length());
	// Arrange
	StateManager* state = new StateManager(str);

	// Act
	EXPECT_ANY_THROW(state->Move("xe3"));
}

TEST(PawnCapturing, Capture_ThrowsException_NoSource) {
	auto str = slurp("C:\\Source\\Chess\\UnitTests\\PawnCapturingTest.txt");
	EXPECT_NE(0, str.length());
	// Arrange
	StateManager* state = new StateManager(str);

	// Act
	EXPECT_ANY_THROW(state->Move("xg5"));
}

TEST(PawnCapturing, Capture_ThrowsException_FriendlyPiece) {
	auto str = slurp("C:\\Source\\Chess\\UnitTests\\PawnCapturingTest.txt");
	EXPECT_NE(0, str.length());
	// Arrange
	StateManager* state = new StateManager(str);

	// Act
	EXPECT_ANY_THROW(state->Move("xd4"));
}