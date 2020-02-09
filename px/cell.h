#ifndef cell_hpp
#define cell_hpp

#include <iostream>
#include <string>

// helper enum - type of cell
enum class CellType {
    empty,
    blue,
    green,
    orange,
    red,
    violet,
    bomb, // radial bomb
    hbomb, // horizontal bomb
    vbomb, // vertical bomb
	wall
};

class Cell//: public QPushButton
{
public:
    //Q_OBJECT

	// constructors

	Cell(CellType type);

	// methods

	bool isBooster() const;

	CellType type() const;

	// friend functions

	friend std::ostream& operator<<(std::ostream& os, const Cell& cell);

	// static functions

	static std::string to_string(CellType type);

private:

	CellType type_m;
};

bool operator==(const Cell& cell1, const Cell& cell2);

#endif /* cell_hpp */
