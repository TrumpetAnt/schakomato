#include "pch.h"
#include <string>
#include <fstream>
#include <windows.h>
#include "StateManager.h"

namespace PawnTests {

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
		auto str = slurp("../../UnitTests/PawnMovementTest.txt");
		StateManager* state = new StateManager(str);

		// Assert
		EXPECT_ANY_THROW(state->Move("b4"));
	}

	TEST(PawnMovement, NoCapture_SingleMove_ThrowsException_MovingToOccupiedSquare) {
		// Arrange
		auto str = slurp("../../UnitTests/PawnMovementTest.txt");
		StateManager* state = new StateManager(str);

		// Assert
		EXPECT_ANY_THROW(state->Move("a4"));
	}

	TEST(PawnMovement, NoCapture_DoubleMove_ThrowsException_MovingOverSquare) {
		// Arrange
		auto str = slurp("../../UnitTests/PawnMovementTest.txt");
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

		board.reset();
	}

	TEST(PawnCapturing, Capture_SingleMove) {
		auto str = slurp("../../UnitTests/PawnCapturingTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		state->Move("xb3");

		// Assert
		auto board = state->GetStateCopy();

		AssertSquareNotNull(Square{ 'b', 3 }, &board);
		AssertSquareNull(Square{ 'a', 2 }, &board);

		EXPECT_EQ(White, board[SquareToInt(Square{ 'b', 3 })]->GetPlayer());
	}

	TEST(PawnCapturing, Capture_SingleMove_SecondOption) {
		auto str = slurp("../../UnitTests/PawnCapturingTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		state->Move("xc3");

		// Assert
		auto board = state->GetStateCopy();

		AssertSquareNotNull(Square{ 'c', 3 }, &board);
		AssertSquareNull(Square{ 'd', 2 }, &board);

		EXPECT_EQ(White, board[SquareToInt(Square{ 'c', 3 })]->GetPlayer());
	}

	TEST(PawnCapturing, Capture_MultipleCaptures) {
		auto str = slurp("../../UnitTests/PawnCapturingTest.txt");
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

	TEST(PawnCapturing, Capture_SingleMove_Disambiguation_WithPromotion) {
		auto str = slurp("../../UnitTests/PawnCapturingTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);
		
		// Act
		state->Move("xgf8Q");

		// Assert
		auto board = state->GetStateCopy();

		AssertSquareNotNull(Square{ 'f', 8 }, &board);
		AssertSquareNull(Square{ 'g', 7 }, &board);

		EXPECT_EQ(White, board[SquareToInt(Square{ 'f', 8 })]->GetPlayer());
		EXPECT_EQ(QueenPiece, board[SquareToInt(Square{ 'f', 8 })]->GetPieceType());
	}

	TEST(PawnCapturing, Capture_ThrowsException_NoTarget) {
		auto str = slurp("../../UnitTests/PawnCapturingTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("xe3"));
	}

	TEST(PawnCapturing, Capture_ThrowsException_NoSource) {
		auto str = slurp("../../UnitTests/PawnCapturingTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("xg5"));
	}

	TEST(PawnCapturing, Capture_ThrowsException_FriendlyPiece) {
		auto str = slurp("../../UnitTests/PawnCapturingTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("xd4"));
	}

	TEST(PawnCapturing, Capture_EnPassant) {
		auto str = slurp("../../UnitTests/PawnEnPassantTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		state->Move("b4");
		state->Move("xb3 e.p.");

		// Assert
		auto board = state->GetStateCopy();

		AssertSquareNotNull(Square{ 'b', 3 }, &board);
		AssertSquareNull(Square{ 'b', 4 }, &board);
		AssertSquareNull(Square{ 'a', 4 }, &board);

		EXPECT_EQ(Black, board[SquareToInt(Square{ 'b', 3 })]->GetPlayer());
	}

	TEST(PawnCapturing, Capture_EnPassant_ThrowsException_TooLate) {
		auto str = slurp("../../UnitTests/PawnEnPassantTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		state->Move("b4");

		state->Move("f6");
		state->Move("f3");

		// Assert
		EXPECT_ANY_THROW(state->Move("xb3 e.p."));
	}

	TEST(PawnUpgrade, UpgradeTo_Queen) {
		auto str = slurp("../../UnitTests/PawnUpgradeTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		state->Move("e8Q");

		//Assert
		auto board = state->GetStateCopy();

		EXPECT_EQ(QueenPiece, board[SquareToInt(Square{ 'e', 8 })]->GetPieceType());
		EXPECT_EQ(nullptr, board[SquareToInt(Square{ 'e', 7 })]);
	}

	TEST(PawnUpgrade, UpgradeTo_Rook) {
		auto str = slurp("../../UnitTests/PawnUpgradeTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		state->Move("e8R");

		//Assert
		auto board = state->GetStateCopy();

		EXPECT_EQ(RookPiece, board[SquareToInt(Square{ 'e', 8 })]->GetPieceType());
		EXPECT_EQ(nullptr, board[SquareToInt(Square{ 'e', 7 })]);
	}

	TEST(PawnUpgrade, UpgradeTo_Bishop) {
		auto str = slurp("../../UnitTests/PawnUpgradeTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		state->Move("e8B");

		//Assert
		auto board = state->GetStateCopy();

		auto p = board[SquareToInt(Square{ 'e', 8 })];
		auto t = board[SquareToInt(Square{ 'e', 8 })]->GetPieceType();

		EXPECT_EQ(BishopPiece, board[SquareToInt(Square{ 'e', 8 })]->GetPieceType());
		EXPECT_EQ(nullptr, board[SquareToInt(Square{ 'e', 7 })]);
	}

	TEST(PawnUpgrade, UpgradeTo_Knight) {
		auto str = slurp("../../UnitTests/PawnUpgradeTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		state->Move("e8N");

		//Assert
		auto board = state->GetStateCopy();

		EXPECT_EQ(KnightPiece, board[SquareToInt(Square{ 'e', 8 })]->GetPieceType());
		EXPECT_EQ(nullptr, board[SquareToInt(Square{ 'e', 7 })]);
	}

	TEST(PawnUpgrade, UpgradeTo_King_ThrowException) {
		auto str = slurp("../../UnitTests/PawnUpgradeTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("e8K"));
	}

	TEST(PawnUpgrade, NoTarget_ThrowException) {
		auto str = slurp("../../UnitTests/PawnUpgradeTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("a8Q"));
	}

	TEST(PawnUpgrade, OccupiedTarget_ThrowException) {
		auto str = slurp("../../UnitTests/PawnUpgradeTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("b8Q"));
	}

	TEST(PawnUpgrade, UpgradeTo_Queen_WithCapture) {
		auto str = slurp("../../UnitTests/PawnUpgradeTest.txt");
		EXPECT_NE(0, str.length());
		// Arrange
		StateManager* state = new StateManager(str);

		// Act
		state->Move("xf8Q");

		//Assert
		auto board = state->GetStateCopy();

		EXPECT_EQ(QueenPiece, board[SquareToInt(Square{ 'f', 8 })]->GetPieceType());
		EXPECT_EQ(White, board[SquareToInt(Square{ 'f', 8 })]->GetPlayer());
		EXPECT_EQ(nullptr, board[SquareToInt(Square{ 'e', 7 })]);
	}
}