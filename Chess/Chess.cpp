#include <iostream>
#include "StateManager.h"
#include "Renderer.h"

using namespace std;

int main()
{
	auto state = make_shared<StateManager>();
	auto renderer = make_unique<Renderer>(Renderer(state));
	renderer->PrintStateToConsole();
	string s_in = "";
	while (true) {
		renderer->PrintStateToConsole();
		cout << (state->GetCurrentPlayer() == White ? "White " : "Black ") << "can make a move" << endl;
		cin >> s_in;
		if (s_in.compare("exit") == 0) {
			break;
		}
		try {
			state->Move(s_in);
		}
		catch (const std::exception& ex) {
			cout << "Illegal move: " << ex.what() << endl;
		}
	}
}