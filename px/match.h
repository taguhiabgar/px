#ifndef match_hpp
#define match_hpp

#include <vector>
#include "cell.h"
#include "coordinate.h"

class Match {
public:


    enum class Type {
        simple, // 3 cells matched - on row or column
		longH, // 3+ cells matched horizontally
		longV, // 3+ cells matched vertically
		square // 2 x 2 
    };
    
	Match(Match::Type matchType, std::vector<Coordinate> coordinates);

    std::vector<Coordinate> coordinates() const;
    
	Match::Type type() const;

	// generates booster depending on Match type
	CellType generateBooster() const;

private:
    Type type_m;
    
    std::vector<Coordinate> coordinates_m; // coordinates of matched cells
};

#endif /* match_hpp */
