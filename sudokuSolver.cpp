#include "sudokuSolver.h"
#include "stdafx.h"

size_t solving = 0;

sudokuSolver::sudokuSolver(size_t *matrix, size_t size): size(size) {
	grid = new size_t[size*size];
	for (size_t i = 0; i < size*size; i++) {
		grid[i] = matrix[i];
	}
};

sudokuSolver::~sudokuSolver() {
	delete[] grid;
}

bool sudokuSolver::solve() {
	placeNumber(0);
	if (solving == 1) {
		solving = 0;
		return true;
	}
	solving = 0;
	return false;
}

void sudokuSolver::placeNumber(size_t position) {
	if (position == size*size) {
		solving++;
		return;
	}
	if (grid[position] > 0) {
		placeNumber(position + 1);
		return ;
	}
	for (size_t i = 1; i <= size; i++) {
		if (checkValidity(i, position % size, position / size)) {
			grid[position] = i;
			placeNumber(position + 1);
			grid[position] = 0;
		}
	}
}

bool sudokuSolver::checkValidity(size_t val, size_t x, size_t y) {
	size_t sideSquare = (size_t)sqrt(size);
	for (size_t i = 0; i < size; i++) {
		if (grid[y * size + i] == val || grid[i * size + x] == val)
			return false;
	}
	size_t startX = (x / sideSquare) * sideSquare;
	size_t startY = (y / sideSquare) * sideSquare;
	for (size_t i = startY; i < startY + sideSquare; i++) {
		for (size_t j = startX; j < startX + sideSquare; j++) {
			if (grid[i * size + j] == val)
				return false;
		}
	}
	return true;
}

void sudokuSolver::changeNumb(size_t x,size_t item) {
	grid[x] = item;
}