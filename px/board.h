#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <vector>
#include "coordinate.h"
#include "cell.h"
#include "match.h"

class Board
{
public:
    
    Board();
    
    Board(int rows, int cols);
    
    void swapCells(Coordinate c1, Coordinate c2);
    
	// removes matches and drops cells down, iteratively until there are no matches to remove
	// shows board on each iteration
	std::map<CellType, int> clearIteratively();

	void generateRandomly(const std::vector<CellType>& possibleFigures, int rowsCount, int columnsCount, int obstaclesCount);

	const Cell& at(const Coordinate& c) const;

    // friend functions
    
    friend std::ostream& operator<<(std::ostream& os, const Board& board);
    
private:
    // methods
    
    bool validCoordinate(const Coordinate& c) const;
    
    std::vector<Match> detectMatches() const;
    
	std::map<CellType, int> removeMatches(const std::vector<Match>& matches);

	
    
    // members
    
    int rowNumber;
    
    int colNumber;

	std::vector<CellType> possibleFigures_m;
    
    std::vector<std::vector<Cell>> data;
};

std::ostream& operator<<(std::ostream& os, const Board& board);

#endif // BOARD_H
