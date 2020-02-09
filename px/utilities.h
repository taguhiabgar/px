#ifndef utilities_hpp
#define utilities_hpp

#include <vector>
#include "coordinate.h"

// generates random integer in range [0, max)
int random(int max);

Coordinate randomCoordinate(int rows, int cols);

CellType randomCellType(const std::vector<CellType>& possibleChoices);

#endif /* utilities_hpp*/
