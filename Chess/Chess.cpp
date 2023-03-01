#include <iostream>
#include "StateManager.h"
#include "Renderer.h"

int main()
{
	StateManager state;
	Renderer renderer(state);
	std::string s = renderer.StateToString();
	state.Move("e4");
	renderer.StateToString();
	//std::cout << s << std::endl;
}