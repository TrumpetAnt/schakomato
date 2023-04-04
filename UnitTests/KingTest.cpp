#include "pch.h"
#include <string>
#include <fstream>
#include <windows.h>
#include "StateManager.h"


namespace KingTest {


	std::string slurp(std::string filePath) {
		std::ifstream in;
		in.open(filePath);
		std::ostringstream sstr;
		sstr << in.rdbuf();
		return sstr.str();
	}

	TEST(KingRules, CannotPutKingInCheck_DirectMove) {
		// Arrange
		auto str = slurp("../../UnitTests/KingRulesTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("Ka1"));
	}

	TEST(KingRules, CannotPutKingInCheck_DirectMove_OpposingKing) {
		// Arrange
		auto str = slurp("../../UnitTests/KingRulesTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("Ka3"));
	}

	TEST(KingRules, CannotPutKingInCheck_IndirectMove) {
		// Arrange
		auto str = slurp("../../UnitTests/KingRulesTest.txt");
		StateManager* state = new StateManager(str);

		// Act
		EXPECT_ANY_THROW(state->Move("b4"));
	}

	TEST(KingRules, CannotPutKingInCheck_CaptureGuarded) {
		// Arrange
		auto str = slurp("../../UnitTests/KingRulesTest.txt");
		StateManager* state = new StateManager(str);

		state->Move("h5");

		// Act
		EXPECT_ANY_THROW(state->Move("Ka5"));
	}

	TEST(KingRules, Can_PutOpposingKingInCheck) {
		// Arrange
		auto str = slurp("../../UnitTests/KingRulesTest.txt");
		StateManager* state = new StateManager(str);

		state->Move("h5");

		// Act
		EXPECT_ANY_THROW(state->Move("Ka5"));
	}

	TEST(KingRules, CanEscapeCheck) {
		// Arrange
		auto str = slurp("../../UnitTests/KingRulesTest2.txt");
		StateManager* state = new StateManager(str);

		state->Move("Kc4");

		// Act
		auto board = state->GetStateCopy();

		// Assert
		EXPECT_EQ(nullptr, board[SquareToInt(Square{ 'c',3 })]);
		auto pos = SquareToInt(Square{ 'c',4 });
		EXPECT_NE(nullptr, board[pos]);
		EXPECT_EQ(KingPiece, board[pos]->GetPieceType());
	}

	TEST(KingRules, MustEscapeCheck_ThrowsException) {
		// Arrange
		auto str = slurp("../../UnitTests/KingRulesTest2.txt");
		StateManager* state = new StateManager(str);

		// Act & Assert
		EXPECT_ANY_THROW(state->Move("Kd3"));
	}
}