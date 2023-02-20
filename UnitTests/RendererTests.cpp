#include "pch.h"
#include <string>
#include <fstream>
#include "../Chess/StateManager.h"
#include "../Chess/Renderer.h"

TEST(RenderTest, InitialBoard) {
	// Arrange
	StateManager& state = StateManager();
	Renderer& renderer = Renderer(state);

	// Act
	std::string output = renderer.StateToString();

	//Assert
	std::string s = "+---+---+---+---+---+---+---+---+\n\
| R | N | B | Q | K | B | N | R |\n\
+---+---+---+---+---+---+---+---+\n\
| i | i | i | i | i | i | i | i |\n\
+---+---+---+---+---+---+---+---+\n\
|   |   |   |   |   |   |   |   |\n\
+---+---+---+---+---+---+---+---+\n\
|   |   |   |   |   |   |   |   |\n\
+---+---+---+---+---+---+---+---+\n\
|   |   |   |   |   |   |   |   |\n\
+---+---+---+---+---+---+---+---+\n\
|   |   |   |   |   |   |   |   |\n\
+---+---+---+---+---+---+---+---+\n\
| i | i | i | i | i | i | i | i |\n\
+---+---+---+---+---+---+---+---+\n\
| R | N | B | Q | K | B | N | R |\n\
+---+---+---+---+---+---+---+---+\n";

	std::string expectedOutPut = s;

	EXPECT_EQ(output, expectedOutPut);
}