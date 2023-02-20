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
			int rank = p->GetPosition().rank;
			if (map.find(rank) == map.end()) {
				map[rank] = std::vector<Piece*>();
			}
			map[p->GetPosition().rank].push_back(p);
		}
		std::string res;
		std::string s;
		res += "+---+---+---+---+---+---+---+---+\n";
		std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;
		for (int i = 0; i < 8; i++) {
			s = "|";
			std::cout << "|";
			if (map.find(i) != map.end()) {
				std::vector<Piece*> pieces = map[i];
				int j = 0;
				for (Piece* p : pieces) {
					int file = this->FileToPosition(p->GetPosition().file);
					int numOfEmptyTiles = file - j - 1;
					if (numOfEmptyTiles > 0) {
						std::cout << this->repeat(numOfEmptyTiles, "   |");
						s += this->repeat(numOfEmptyTiles, "   |");
					}
					std::cout << " " << this->PieceTypeToString(p->GetPieceType()) << " |";
					s += " " + this->PieceTypeToString(p->GetPieceType());
					s += " |";
					j = file;
				}
				if (j < 7) {
					std::cout << this->repeat(7 - j, "   |");
				}
				std::cout << std::endl;
			}
			else {
				std::cout << this->repeat(8, "   |") << std::endl;
			}
			res += s;
			res += "+---+---+---+---+---+---+---+---+\n";
			std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;
		}

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

