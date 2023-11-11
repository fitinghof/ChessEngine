#include "positionClass.hpp"

int main() {
	Position pos;
	pos.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	pos.drawBoard();
	return 0;
}