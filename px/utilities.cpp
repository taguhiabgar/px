#include <time.h>
#include "cell.h"
#include "utilities.h"

// generates random integer in range [0, max)
int random(int max) {
	
	return rand() % max;
}

Coordinate randomCoordinate(int rows, int cols) {
	size_t x = random(rows);
	size_t y = random(cols);
	return {x, y};
}

CellType randomCellType(const std::vector<CellType>& possibleChoices) {
	size_t index = random(possibleChoices.size());
	return possibleChoices[index];
}


