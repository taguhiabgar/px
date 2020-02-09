#ifndef match3game_hpp
#define match3game_hpp

#include <vector>
#include "size.h"
#include "board.h"
#include "objective.h"

// this is the main class that receives all the user inputs and responds to them
class Match3Game {
public:
    
    // configure game with given settings
	void configure(
		Size boardSize,
		int movesCount,
		int obstaclesCount,
		const std::vector<Objective> objectives,
		const std::vector<CellType>& possibleFigures);
    
    void generateRandomBoard();
    
    void showBoard() const;

	void showRequirements() const;
    
    void start();

private:
    
    // game settings
    
    Size boardSize_m;
    
    int movesCount_m;

	int obstaclesCount_m;
  
    std::vector<Objective> objectives_m;
    
	std::vector<CellType> possibleFigures_m;

    // other members
    
    Board board;
    
};

#endif /* match3game_hpp */
