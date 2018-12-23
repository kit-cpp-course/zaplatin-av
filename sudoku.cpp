#include "stdafx.h"
#include "sudoku.h"
#include "sudokuSolver.h"


#define swap(a, b) (a ^= b ^= a ^= b)

//переменная, показывающая сколько раз изменяется поле
const size_t N = 20;

sudoku::sudoku(const size_t size):size(size), sideSquare((size_t)sqrt(size)), level(size*size) {
	matrix = new size_t*[size];
	matrix[0] = new size_t[size*size];

	for (size_t i = 1; i != size; i++) {
		matrix[i] = matrix[i - 1] + size;
	}

	
	for (size_t i = 0; i < size; i+=sideSquare) {
		fillArea(i, i + sideSquare);
	}
	// обеспечивают случайную генерацию судоку в дальнейшем
	Sleep(1000);
	srand(time(0)); 
	
}


sudoku::~sudoku() {
	
	delete[] matrix[0];
	delete[] matrix;
}

void sudoku::transposition() {
	for (size_t i = 0; i < size; i++) {
		for (size_t j = i+1; j < size; j++) {
			swap(matrix[i][j], matrix[j][i]);
		}
	}
}

void sudoku::swapRowsSmall() {
	int area = rand() % sideSquare,
		a = rand() % sideSquare + area * sideSquare,
		b = area * sideSquare + rand() % sideSquare;
	
	while(a == b) {
		b = area * sideSquare + rand() % sideSquare;
	}

	for (size_t i = 0; i < size; i++) {
		swap(matrix[a][i], matrix[b][i]);
	}
}

void sudoku::swapColumsSmall() {
	int area = rand() % sideSquare,
		a = rand() % sideSquare + area * sideSquare,
		b = area * sideSquare + rand() % sideSquare;
	
	while (a == b) {
		b = area * sideSquare + rand() % sideSquare;
	}

	for (size_t i = 0; i < size; i++) {
		swap(matrix[i][a], matrix[i][b]);
	}
}

void sudoku::swapRowsArea() {
	int areaA = rand() % sideSquare,
		areaB = (areaA + 1) % sideSquare * sideSquare;
	areaA *= sideSquare;

	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < sideSquare; j++) {
			swap(matrix[areaA + j][i], matrix[areaB + j][i]);
		}
	}
}

void sudoku::swapColumsArea() {
	int areaA = rand() % sideSquare,
		areaB = (areaA + 1) % sideSquare * sideSquare;
	areaA *= sideSquare;

	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < sideSquare; j++) {
			swap(matrix[i][areaA + j], matrix[i][areaB + j]);
		}
	}
}

void sudoku::createNewField() {
	for (size_t i = 0; i < N; i++) {
		switch (rand() % 5) {
		case 0:
			sudoku::transposition();
			break;
		case 1:
			sudoku::swapRowsSmall();
			break;
		case 2:
			sudoku::swapColumsSmall();
			break;
		case 3:
			sudoku::swapRowsArea();
			break;
		case 4:
			sudoku::swapColumsArea();
			break;
		defalt:
			break;
		}
	}
	deliteItems();
}

void sudoku::deliteItems() {	
	size_t	i = 0,
			j = 0,
			temp = 0,
			// Переменная отвечающая за легкость судоку
			minLevel = 0;

	switch (size) {
	case 4:
		minLevel = 8;
		break;
	case 9:
		minLevel = 33;
		break;
	case 16:
		minLevel = 121;
		break;
	case 25:
		minLevel = 335;
		break;
	default:
		minLevel = 0;
		break;
	}

	bool ** boolMatrix = new bool*[size];
	boolMatrix[0] = new bool[size*size];

	size_t ** copyMatrix = new size_t*[size];
	copyMatrix[0] = new size_t[size*size];

	for (size_t k = 1; k != size; k++) {
		boolMatrix[k] = boolMatrix[k - 1] + size;
		copyMatrix[k] = copyMatrix[k - 1] + size;
	}
	Start:
	for (size_t k = 0; k < size; k++) {
		for (size_t l = 0; l < size; l++) {
			boolMatrix[k][l] = 0;
			copyMatrix[k][l] = matrix[k][l];
		}
	}

	while (level) {
		sudokuSolver sud(*copyMatrix, size);
		i = rand() % size;
		j = rand() % size;
		if (!boolMatrix[i][j]) {
			boolMatrix[i][j] = 1;
			temp = matrix[i][j];
			sud.changeNumb(i*size + j, 0);
			if (sud.solve()) {
				level -= 1;
				copyMatrix[i][j] = 0;
			}
			else { break; }
		}
	}

	if (level > minLevel) {
		level = size*size;
		goto Start;
	}

	for (size_t k = 0; k < size; k++) {
		for (size_t l = 0; l < size; l++) {
			matrix[k][l] = copyMatrix[k][l];
		}
	}

	delete[] copyMatrix[0];
	delete[] copyMatrix;

	delete[] boolMatrix[0];
	delete[] boolMatrix;

}


void sudoku::print(const std::string path) {
	size_t count = (size + (sideSquare) * sideSquare + (sideSquare - 1));
	std::fstream file;
	file.open(path, std::ios::app);
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			file << matrix[i][j]<< ' ';
			if (matrix[i][j] / 10 != 0 && (j+1) % sideSquare !=0)
				file << ' ';
			if ((j + 1) % sideSquare == 0 && j + 1 != size) {
				file << '|';
			}
		}
		if ((i + 1) % sideSquare == 0 && i + 1 != size) {
			file << std::endl;
			for (size_t k = 0; k < count; k++) {
				file << '-';
			}
		}
		file << std::endl;
	}
	file << std::endl;
	while (count) {
		file << '*';
		count--;
	}
	file << std::endl;
	file.close();
}

void sudoku::printLevel(const std::string path) {
	std::fstream file;
	file.open(path, std::ios::app);
	file << "Сложность: "<<  level;
	file << std::endl << std::endl;
	file.close();
}


//Вспомогательные функции

void sudoku::fillArea(size_t border1, size_t border2) {
	int temp = 0,
		counter = border2 / (sideSquare);
	for (size_t i = border1; i < border2; i++) {
		temp = sideSquare * i % size + counter;
		for (size_t j = 0; j < size; j++) {
			if (temp == size + 1)
				temp = 1;
			matrix[i][j] = temp++;
		}
	}
}




