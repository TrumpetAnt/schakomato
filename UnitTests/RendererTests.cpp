#include "pch.h"
#include <string>
#include <fstream>
#include "Renderer.h"

TEST(RenderTest, InitialBoard) {
	// Arrange
	auto state = std::make_shared<StateManager>(StateManager());
	auto renderer = std::make_unique<Renderer>(Renderer(state));

	// Act
	std::string output = renderer->StateToString();

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