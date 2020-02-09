#include "match.h"

std::vector<Coordinate> Match::coordinates() const {
    return coordinates_m;
}

Match::Match(Match::Type matchType, std::vector<Coordinate> coordinates) : type_m(matchType), coordinates_m(coordinates) {
	
}

Match::Type Match::type() const {
	return type_m;
}

CellType Match::generateBooster() const {
	switch (type()) {
	case Match::Type::longH:
		return CellType::vbomb;
	case Match::Type::longV:
		return CellType::hbomb;
	case Match::Type::square:
		return CellType::bomb;
	default:
		return CellType::empty;
	}
}
