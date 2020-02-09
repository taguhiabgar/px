#ifndef coordinate_hpp
#define coordinate_hpp

#include <iostream>

// simple struct to save a coordinate
struct Coordinate{
public:
	Coordinate();

	Coordinate(size_t x, size_t y);

	size_t row;
	size_t col;
};

std::istream& operator>>(std::istream& is, Coordinate& coordinate);

#endif /* coordinate_hpp */
