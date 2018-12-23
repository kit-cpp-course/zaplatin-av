#include "stdafx.h"
#include "sudoku.h"
#include "sudokuSolver.h"
#include "params.h"

using namespace std;

void main(size_t count, char ** arguments) {
	setlocale(0, "Russian");
	params parms(count, arguments);
	if (parms.checkValidity()) {
		size_t i = parms.getNumb();
		while (i) {
			sudoku s(parms.getSize());
			s.createNewField();
			s.printLevel(parms.Path());
			s.print(parms.Path());
			i--;
		}
	}
}

/*
 * Как указывать парамметры:
 * 1 парамметр - количество, 2 - размер, 3 - путь к файлу
 * Программа хорошо работает для судоку размером 4х4, 9х9.
 * Дальше генерация судоку происходит очень медленно!!!
 */
