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
	Renderer(StateManager& state) : state(state) {};

	std::string StateToString() {

		HANDLE  hConsole;

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		std::map<int, std::vector<Piece*>> map;
		for (Piece* p : *this->state.GetBoard()) {
			auto pos = p->GetPosition();
			int rank = pos->rank;
			if (map.find(rank) == map.end()) {
				map[rank] = std::vector<Piece*>();
			}
			map[pos->rank].push_back(p);
			delete pos;
		}
		std::string res;
		std::string s;
		res += "+---+---+---+---+---+---+---+---+\n";
		for (int i = 0; i < 8; i++) {
			s = "|";
			if (map.find(i) != map.end()) {
				std::vector<Piece*> pieces = map[i];
				int j = 0;
				for (Piece* p : pieces) {
					auto pos = p->GetPosition();
					int file = this->FileToPosition(pos->file);
					delete pos;
					int numOfEmptyTiles = file - j - 1;
					if (numOfEmptyTiles > 0) {
						std::cout << this->repeat(numOfEmptyTiles, "   |");
						s += this->repeat(numOfEmptyTiles, "   |");
					}
					s += " ";
					s += this->PieceTypeToString(p->GetPieceType());
					s += " |";
					j = file;
				}
				if (j < 7) {
					s += this->repeat(7 - j, "   |");
				}
				s += "\n";
			}
			else {
				s += this->repeat(8, "   |");
				s += "\n";
			}
			res += s;
			res += "+---+---+---+---+---+---+---+---+\n";
		}
		std::cout << res;
		return res;
	};

private:
	int FileToPosition(char file) {
		switch (file) {
		case 'A':
			return 0;
		case 'B':
			return 1;
		case 'C':
			return 2;
		case 'D':
			return 3;
		case 'E':
			return 4;
		case 'F':
			return 5;
		case 'G':
			return 6;
		case 'H':
			return 7;
		default:
			throw std::invalid_argument("Invalid argument, argument is not a valid file: " + file);
		}
	}

	char PieceTypeToString(PieceType type) {
		switch (type) {
		case King:
			return 'K';
		case Queen:
			return 'Q';
		case Rook:
			return 'R';
		case Bishop:
			return 'B';
		case Knight:
			return 'N';
		case Pawn:
			return 'i';
		default:
			throw std::invalid_argument("Unhandeled switch case");
		}
	}

	std::string repeat(int n, std::string s) {
		std::ostringstream os;
		for (int i = 0; i < n; i++)
			os << s;
		return os.str();
	}

	StateManager& state;
};

