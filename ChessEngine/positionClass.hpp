#ifndef POSITIONCLASS_HPP
#define POSITIONCLASS_HPP
#include <cstdint>
#include <iostream>
#include <bitset>
#include <cassert>
class Position {

	// 56 57 58 59 60 61 62 63
	// 48 49 50 51 52 53 54 55
	// 40 41 42 43 44 45 46 47
	// 32 33 34 35 36 37 38 39
	// 24 25 26 27 28 29 30 31
	// 16 17 18 19 20 21 22 23
	// 8  9  10 11 12 13 14 15
	// 0  1  2  3  4  5  6  7

private:
	uint64_t aOne = 0b1;
	enum pieces {
		PAWN = 0,
		ROOK = 1,
		KNIGHT = 2,
		BISHOP = 3,
		QUEEN = 4,
		KING = 5,
		WHITE = 6,
		BLACK = 7,
		PIECEAMOUNT = 6
	};
	uint64_t pieces[8]{ 0 };



	static const uint64_t LineMask1 = 0b11111111; //line, shift left by multiples of 8.
	static const uint64_t LineMask2 =     0b100000001000000010000000100000001000000010000000100000001; //standing line, shift left by multiples of 1.
	static const uint64_t diagonalMask1 = 0b1000000001000000001000000001000000001000000001000000001000000001; //diagonal line /, shift left by multiples of 1. func for shift amount = x % 8 - (x - x % 8)/8
	static const uint64_t diagonalMask2 = 0b100000010000001000000100000010000001000000100000010000001000000; //diagonal line \, shift left or right by multiples of 1. func for shift amount = (x - x % 8)/8 - x % 8
	static const uint64_t knightMask = 0b101000010001000000000001000100001010; //knight moves, shift left by x-18.
	static const uint64_t kingMoveMask;

	void getKnightMoves(int pos, uint64_t& color) {
		(knightMask << pos - 18) ^ color;


	}


public:
	void getPlayableMoves(uint64_t color) {
		for (int i = 0; i < 64; i++)
		{
			uint64_t moveMask = aOne << i;
			if (color & moveMask) {

			}
		}
	}

	void addPiece(int piece, uint64_t squareMap) {
		pieces[piece] |= squareMap;
	}

	void removePiece(int piece, uint64_t squareMap) {
		pieces[piece] |= squareMap;
		pieces[piece] ^= squareMap;
	}

	void play(int from, int to) {
		uint64_t fromMask = aOne << from;
		uint64_t toMask = aOne << to;

		for (int i = 0; i < PIECEAMOUNT; i++) {
			if (pieces[i] & fromMask) {
				removePiece(i, fromMask);
				addPiece(i, toMask);
				break;
			}
		}
		if (pieces[WHITE] & fromMask) {
			removePiece(WHITE, fromMask);
			addPiece(WHITE, toMask);
		}
		else {
			removePiece(BLACK, fromMask);
			addPiece(BLACK, toMask);
		}

	}

	void drawBoard() {
		static const char* pieceChars = "PRNBQK";
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				bool foundPiece = false;
				for (int k = 0; k < 6; k++) {
					if ((pieces[k] & aOne << (56 - i * 8 + j)) > 0) {
						foundPiece = true;
						if ((pieces[WHITE] & (aOne << (56 - i * 8 + j))) > 0)
						{
							std::cout << " " << pieceChars[k] << " ";
						}
						else std::cout << " " << char(pieceChars[k] + 32) << " ";
						break;
					}
				}
				if (!foundPiece) std::cout << " - ";
			}
			std::cout << std::endl;
		}
	}

	void loadFEN(std::string FEN) {
		int column = 0;
		int row = 7;
		for (char i : FEN) {
			switch (i) {
			case 'p':
			case 'P':
				addPiece(PAWN, aOne << (row * 8 + column));
				if (i < 'a') addPiece(WHITE, aOne << (row * 8 + column));
				else addPiece(BLACK, aOne << (row * 8 + column));
				column++;
				break;
			case 'r':
			case 'R':
				addPiece(ROOK, aOne << (row * 8 + column));
				if (i < 'a') addPiece(WHITE, aOne << (row * 8 + column));
				else addPiece(BLACK, aOne << (row * 8 + column));
				column++;
				break;
			case 'n':
			case 'N':
				addPiece(KNIGHT, aOne << (row * 8 + column));
				if (i < 'a') addPiece(WHITE, aOne << (row * 8 + column));
				else addPiece(BLACK, aOne << (row * 8 + column));
				column++;
				break;
			case 'b':
			case 'B':
				addPiece(BISHOP, aOne << (row * 8 + column));
				if (i < 'a') addPiece(WHITE, aOne << (row * 8 + column));
				else addPiece(BLACK, aOne << (row * 8 + column));
				column++;
				break;
			case 'q':
			case 'Q':
				addPiece(QUEEN, aOne << (row * 8 + column));
				if (i < 'a') addPiece(WHITE, aOne << (row * 8 + column));
				else addPiece(BLACK, aOne << (row * 8 + column));
				column++;
				break;
			case 'k':
			case 'K':
				addPiece(KING, aOne << (row * 8 + column));
				if (i < 'a') addPiece(WHITE, aOne << (row * 8 + column));
				else addPiece(BLACK, aOne << (row * 8 + column));
				column++;
				break;
			case '/':
				row--;
				column = 0;
				break;
			default:
				assert(i - '0' <= 8 - column && i - '0' >= 1, "Invalid FEN string");
				column += i - '0';
				break;
			}
		}
	}
};

#endif // !POSITIONCLASS_HPP
