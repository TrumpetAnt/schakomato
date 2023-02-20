#include <iostream>
#include "StateManager.h"
#include "Renderer.h"

int main()
{
	StateManager state;
	Renderer renderer(state);
	std::string s = renderer.StateToString();
	//std::cout <<  << std::endl;
}