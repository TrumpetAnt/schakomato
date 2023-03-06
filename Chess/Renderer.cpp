#include "Renderer.h"

std::string Repeat(int n, std::string s) {
	std::ostringstream os;
	for (int i = 0; i < n; i++)
		os << s;
	return os.str();
}

void Renderer::PrintStateToConsole() {
	auto output = StateToString();
	HANDLE  hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << output;
}

std::string Renderer::StateToString() {
	auto board = state->GetStateCopy();
	std::string res;
	res += "+---+---+---+---+---+---+---+---+\n";
	for (size_t i = 0; i < 8; i++) {
		res += "|";
		for (size_t j = 0; j < 8; j++) {
			char piece = board[(7 - i) * 8 + j] != nullptr ? PieceTypeToChar(board[(7 - i) * 8 + j]->GetPieceType()) : ' ';
			res += " ";
			res += piece;
			res += " |";
		}
		res += "\n+---+---+---+---+---+---+---+---+\n";
	}
	return res;
};