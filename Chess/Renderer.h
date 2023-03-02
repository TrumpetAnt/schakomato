#pragma once
#include "StateManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>
#include <windows.h>   // WinApi header

class Renderer
{
public:
	Renderer(std::shared_ptr<StateManager> state) : state(state) {};

	void PrintStateToConsole();
	std::string StateToString();

private:
	std::shared_ptr<StateManager> state;
};

