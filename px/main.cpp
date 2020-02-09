#include <iostream>
#include <windows.h>
#include <time.h>
#include "match3game.h"

void testConsoleColors();

int main(int argc, const char * argv[]) {
	srand(time(NULL)); // initialize random seed

	Match3Game game;
	game.configure(
		{ 7, 7 }, /* board size */
		15, /* moves count */
		3, /* obstacles count */
		{ { 3, CellType::violet }, { 5, CellType::blue }, { 8, CellType::red } }, /* objectives */
		{ CellType::violet, CellType::blue, CellType::red, CellType::green, CellType::orange } /* possible figures */
	);
	game.start();
}

void testConsoleColors() {
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < 20; ++i) {
		SetConsoleTextAttribute(hConsole, i);
		std::cout << i << ' ' << "o";
	}
}

//void test() {
//
//    std::vector<std::vector<int>> v = {
//        {1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 0, 1, 1, 0, 0},
//        {1, 1, 1, 0, 1, 1, 0, 0},
//        {1, 1, 1, 0, 1, 1, 1, 1},
//        {1, 1, 1, 0, 1, 0, 0, 0},
//        {1, 1, 1, 0, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1},
//        {0, 0, 0, 1, 1, 1, 1, 1},
//        {0, 0, 0, 1, 1, 1, 1, 1},
//    };
//
//    std::vector<std::vector<int>> vres = {
//        {2, 2, 2, 2, 1, 2, 2, 2},
//        {2, 2, 2, 2, 1, 1, 2, 2},
//        {1, 1, 1, 2, 1, 1, 2, 2},
//        {1, 1, 1, 2, 1, 1, 1, 1},
//        {1, 1, 1, 2, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1},
//        {1, 1, 1, 1, 1, 1, 1, 1},
//    };
//
//    const size_t rows = v.size();
//    const size_t cols = v[0].size();
//
//    const int remove = 0;
//
//    for(size_t j = 0; j < cols; ++j){
//        for (size_t i = rows - 1; i >= 0; --i) {
//            if (v[i][j] == remove){
//
//            }
//
//        }
//
//    }
//}
