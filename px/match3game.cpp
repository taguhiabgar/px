#include <map>
#include <utility>
#include "match3game.h"


// configure game with given settings
void Match3Game::configure(
	Size boardSize, 
	int movesCount, 
	int obstaclesCount,
	const std::vector<Objective> objectives, 
	const std::vector<CellType>& possibleFigures) 
{
    boardSize_m = boardSize;
    movesCount_m = movesCount;
    objectives_m = objectives;
	obstaclesCount_m = obstaclesCount;
    possibleFigures_m = possibleFigures; 
}

void Match3Game::generateRandomBoard() {
	board.generateRandomly(possibleFigures_m, boardSize_m.height, boardSize_m.width, obstaclesCount_m);
}

void Match3Game::showBoard() const {
	std::cout << board;
}

void Match3Game::showRequirements() const {
	std::cout << "moves: " << movesCount_m << std::endl;

	for (auto& objective : objectives_m) {
		std::string color = Cell::to_string(objective.color);;
		std::cout << color << ": " << objective.count << std::endl;
	}

	std::cout << std::endl;
}

void printSwapHelp() {
	std::cout << "Enter 2 coordinates to swap: x1 y1 x2 y2" << std::endl;
}

std::pair<Coordinate, Coordinate> readUserInput() {
	Coordinate c1, c2;
	std::cin >> c1 >> c2;
	return {c1, c2};
}

// this function implements the main gameplay
void Match3Game::start() {
	generateRandomBoard();
	showBoard();
	showRequirements();
	std::map<CellType, int> removedItems = board.clearIteratively();

	std::cout << "moves count: " << movesCount_m << std::endl;

	while (movesCount_m >= 0) {
		printSwapHelp();
		readUserInput();
		removedItems = board.clearIteratively();
		--movesCount_m;
		showRequirements();
	}

	std::cin.get();
}

