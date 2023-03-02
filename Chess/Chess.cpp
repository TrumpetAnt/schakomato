#include <iostream>
#include "StateManager.h"
#include "Renderer.h"

int main()
{
	auto state = std::make_shared<StateManager>();
	auto renderer = std::make_unique<Renderer>(Renderer(state));
	renderer->PrintStateToConsole();
	state->Move("e4");
	renderer->PrintStateToConsole();
}