#include "coordinate.h"

std::istream& operator>>(std::istream& is, Coordinate& coordinate) {
	is >> coordinate.row >> coordinate.col;
	return is;
}

Coordinate::Coordinate() : Coordinate(0, 0) {
	
}

Coordinate::Coordinate(size_t r, size_t c) : row(r), col(c) {
	
}
