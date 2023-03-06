#include <iostream>
#include "StateManager.h"
#include "Renderer.h"

int main()
{
	auto state = std::make_shared<StateManager>("0pe21pe3");
	auto renderer = std::make_unique<Renderer>(Renderer(state));
	renderer->PrintStateToConsole();
	/*state->Move("e4");
	renderer->PrintStateToConsole();*/
}