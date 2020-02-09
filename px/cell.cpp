#include <iostream>
#include "cell.h"
#include <windows.h>

// friend functions

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char ch;
	switch (cell.type()) {
	    case CellType::empty:
			ch = '_';
	        break;
	    case CellType::blue:
			SetConsoleTextAttribute(hConsole, 9);
			ch = 'o';
	        break;
	    case CellType::green:
			SetConsoleTextAttribute(hConsole, 10);
			ch = 'o';
	        break;
	    case CellType::orange:
			SetConsoleTextAttribute(hConsole, 14);
			ch = 'o';
	        break;
	    case CellType::red:
			SetConsoleTextAttribute(hConsole, 12);
			ch = 'o';
	        break;
	    case CellType::violet:
			SetConsoleTextAttribute(hConsole, 13);
			ch = 'o';
	        break;
	    case CellType::bomb:
			ch = 'B';
	        break;
	    case CellType::hbomb:
			ch = 'H';
	        break;
		case CellType::vbomb:
			ch = 'V';
			break;
		case CellType::wall:
			SetConsoleTextAttribute(hConsole, 15);
			ch = '#';
			break;
//        default:
//            return;
	}
	os << ch;
	SetConsoleTextAttribute(hConsole, 7);
	return os;
}

// operator overloads

bool operator==(const Cell& cell1, const Cell& cell2){
    return cell1.type() == cell2.type();
}

// constructors

Cell::Cell(CellType cellType) : type_m(cellType)
{
//    QIcon icon;
//    switch (cellType) {
//        case Type::empty:
//            icon = QIcon(QString(":/Icons/tile_1"));
//            break;
//        case Type::blue:
//            icon = QIcon(QString(":/Icons/blue"));
//            break;
//        case Type::green:
//            icon = QIcon(QString(":/Icons/green"));
//            break;
//        case Type::orange:
//            icon = QIcon(QString(":/Icons/orange"));
//            break;
//        case Type::red:
//            icon = QIcon(QString(":/Icons/red"));
//            break;
//        case Type::violet:
//            icon = QIcon(QString(":/Icons/violet"));
//            break;
//        case Type::bomb:
//            icon = QIcon(QString(":/Icons/bomb"));
//            break;
//        case Type::hbomb:
//            icon = QIcon(QString(":/Icons/h_bomb"));
//            break;
//        case Type::vbomb:
//            icon = QIcon(QString(":/Icons/v_bomb"));
//            break;
////        default:
////            return;
//    }
//    setIcon(icon);
}

// member functions

bool Cell::isBooster() const {
	return type_m == CellType::bomb || type_m == CellType::hbomb || type_m == CellType::vbomb;
}

CellType Cell::type() const {
	return type_m;
}

// static functions

std::string Cell::to_string(CellType cellType) {
	switch (cellType) {
	case CellType::empty:
		return "empty";
	case CellType::blue:
		return "blue";
	case CellType::green:
		return "green";
	case CellType::orange:
		return "orange";
	case CellType::red:
		return "red";
	case CellType::violet:
		return "violet";
	case CellType::bomb:
		return "radial bomb";
	case CellType::hbomb:
		return "horizonal bomb";
	case CellType::vbomb:
		return "vertical bomb";
	case CellType::wall:
		return "wall";
	default:
		return "";
	}
}
