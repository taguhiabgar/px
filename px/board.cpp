#include <map>
#include <queue>
#include "cell.h"
#include "utilities.h"
#include "coordinate.h"
#include "board.h"

// BOARD - friend functions

std::ostream& operator<<(std::ostream& os, const Board& board) {
	if (board.data.empty()) {
		return os;
	}

	const size_t rows = board.data.size();
	const size_t columns = board.data[0].size();

	// column numbers
	std::cout << " | ";
	for (size_t i = 0; i < columns; ++i) {
		std::cout << i + 1 << ' ';
	}
	std::cout << std::endl << "-+";
	for (size_t i = 0; i < columns; ++i) {
		std::cout << " -";
	}
	std::cout << std::endl;

	// data 

	for (int i = 0; i < rows; ++i) {
		// row numbers
		std::cout << (i + 1) << "| ";
		for (int j = 0; j < columns; ++j) {
			std::cout << board.data[i][j] << ' ';
		}
		std::cout << std::endl;
	}

    return os;
}

// BOARD - constructors

Board::Board() : Board(0, 0) /*rowNumber(0), colNumber(0)*/ {
    
}

Board::Board(int rows, int cols) : rowNumber(rows), colNumber(cols) {
    
}

// BOARD - member methods

bool Board::validCoordinate(const Coordinate& c) const {
    const int x = c.row;
    const int y = c.col;
    return x >= 0 && y >= 0 && x < rowNumber && y < colNumber;
}

void Board::generateRandomly(const std::vector<CellType>& possibleFigures, int rowsCount, int columnsCount, int obstaclesCount) {
	possibleFigures_m = possibleFigures;
	
	// generate random board

	std::vector<std::vector<Cell>> randomBoard = std::vector<std::vector<Cell>>(
		rowsCount, 
		std::vector<Cell>(columnsCount, Cell(CellType::empty))
	);

	for (auto& row : randomBoard) {
		for (Cell& elem : row) {
			CellType randomType = randomCellType(possibleFigures);
			elem = Cell(randomType);
		}
	}
	
	// generate 3 random positions for 3 obstacles

	while (obstaclesCount) {
		Coordinate c = randomCoordinate(rowsCount, columnsCount);
		if (randomBoard[c.row][c.col].type() != CellType::wall) {
			randomBoard[c.row][c.col] = Cell(CellType::wall);
			--obstaclesCount;
		}
	}

	data = randomBoard;
}

// swap cells and clears board iteratively, until no new matches are deteced
// shows board on each iteration, so user can see all the progress
// if initial swap caused no cells to be removed, then cells are swapped back
void Board::swapCells(Coordinate c1, Coordinate c2) {
    if (!validCoordinate(c1) || !validCoordinate(c2)) {
        return;
    }
    
    std::swap(data[c1.row][c1.col], data[c2.row][c2.col]);
    
	std::map<CellType, int> removedItems = clearIteratively();

	if (removedItems.empty()) { // unsuccessful swap
		// swap back
		std::swap(data[c1.row][c1.col], data[c2.row][c2.col]);
	}
}


const Cell& Board::at(const Coordinate& c) const { 
	return data[c.row][c.col];
}

std::vector<Match> Board::detectMatches() const {
    std::vector<Match> matches;

	// detect horizontal matches

	for (size_t i = 0; i < data.size(); ++i) {
		for (size_t j = 0; j <= data[i].size() - 3; ++j) {
			Coordinate a = Coordinate(i, j);
			Coordinate b = Coordinate(i, j + 1);
			Coordinate c = Coordinate(i, j + 2);

			if (at(a) == at(b) && at(a) == at(c)) {
				// simple match deteced
				std::vector<Coordinate> coords = {a, b, c};

				// find if match is longer than 3
				size_t column = j + 3;
				while (column <= data[i].size() - 3) {
					Coordinate current = Coordinate(i, column);
					if (at(current) == at(a)) {
						coords.push_back(current);
						++column;
					} else {
						break;
					}
				}

				Match::Type matchType = coords.size() > 3 ? Match::Type::longH : Match::Type::simple;
				matches.push_back(Match(matchType, coords));
			}
		}
	}

	// detect vertical matches

	for (size_t i = 0; i <= data.size() - 3; ++i) {
		for (size_t j = 0; j < data[i].size(); ++j) {
			Coordinate a = Coordinate(i, j);
			Coordinate b = Coordinate(i + 1, j);
			Coordinate c = Coordinate(i + 2, j);

			if (at(a) == at(b) && at(a) == at(c)) {
				// simple match deteced
				std::vector<Coordinate> coords = { a, b, c };

				// find if match is longer than 3
				size_t row = i + 3;
				while (row <= data[i].size() - 3) {
					Coordinate current = Coordinate(row, j);
					if (at(current) == at(a)) {
						coords.push_back(current);
						++row;
					} else {
						break;
					}
				}

				Match::Type matchType = coords.size() > 3 ? Match::Type::longV : Match::Type::simple;
				matches.push_back(Match(matchType, coords));
			}
		}
	}

	// detect square matches

	for (size_t i = 0; i < data.size() - 1; ++i) {
		for (size_t j = 0; j < data[i].size() - 1; ++j) {
			Coordinate a = Coordinate(i, j);
			Coordinate b = Coordinate(i, j + 1); 
			Coordinate c = Coordinate(i + 1, j);
			Coordinate d = Coordinate(i + 1, j + 1);

			if (at(a) == at(b) && at(a) == at(c) && at(a) == at(d)) {
				// square match detected
				bool aa = true;

				std::cout << aa;
				matches.push_back(Match(Match::Type::square, { a, b, c, d }));
			}
		}
	}
    
    return matches;
}

// adds contents under the same keys 
// returns the "addition" of two maps
std::map<CellType, int> operator+(const std::map<CellType, int>& a, const std::map<CellType, int>& b) {
	std::map<CellType, int> result = a;

	for (const auto& elem : b) {
		const CellType& key = elem.first;
		auto search = result.find(key);
		if (search != result.end()) {
			// key found
			search->second += elem.second;
		} else {
			// key not found
			result.insert(elem);
		}
	}

	return result;
}

// removes matches and drops cells down, iteratively until there are no matches to remove
// shows board on each iteration
// returns true - matches have been detected and cleared iteratively
// returns false - no matches detected
std::map<CellType, int> Board::clearIteratively() {
	std::vector<Match> matches = detectMatches();
	std::map<CellType, int> removedItems;

	while (!matches.empty()) {
		// remove matches, drop cells down, generate new cells from top
		std::map<CellType, int> newRemovedItems = removeMatches(matches);

		// add contents of newRemovedItems to removedItems
		removedItems = removedItems + newRemovedItems;

		// show board
		std::cout << (*this) << std::endl;

		// check if new matches were generated 
		matches = detectMatches();
	}

	return removedItems;
}

// removes matches
// drops cells down
// generates new cells from top
// returns map of removed items and their count
std::map<CellType, int> Board::removeMatches(const std::vector<Match>& matches) {
    
	std::map<CellType, int> removedItems;

	if (data.empty()) {
		return removedItems;
	}

    // create empty cells in place of matched cells
    for(const Match& match : matches){

        std::vector<Coordinate> coords = match.coordinates();
        for(const Coordinate& coordinate : coords){
			Cell& cell = data[coordinate.row][coordinate.col];

			auto search = removedItems.find(cell.type());
			if (search != removedItems.end()) {
				// key found
				search->second += 1;
			} else {
				// key not found
				removedItems.insert(std::pair<CellType, int>(cell.type(), 1));
			}

            cell = Cell(CellType::empty);
        }

		CellType booster = match.generateBooster();

		if (booster != CellType::empty) { // booster cell should be generated
			// choose random position from coordinates of match and 
			// place the booster in that coordinate
			int index = random(match.coordinates().size());
			Coordinate coord = match.coordinates()[index];
			data[coord.row][coord.col] = Cell(booster);
		}
    }
    
    // drop cells down

	for (int j = 0; j < data[0].size(); ++j) {
		for (int i = data.size() - 1; i > 0; --i) {
			if (data[i][j].type() == CellType::empty) {
				for (int k = i; k > 0; --k) {
					data[k][j] = data[k - 1][j];
				}
				data[0][j] = Cell(CellType::empty);
				++i;
			}
		}
	}

    // generate random cells from top

	for (int j = 0; j < data[0].size(); ++j) {
		for (int i = 0; i < data.size() && data[i][j].type() == CellType::empty; ++i) {
			data[i][j] = randomCellType(possibleFigures_m);
		}
	}

	return removedItems;
}

