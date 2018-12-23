#pragma once

/*
 * Класс, проверяющий наличие решения судоку
 */
class sudokuSolver{
	/*
	 * Одномерный массив, являющийся полем судоку
	 */
	size_t *grid;
	/*
	 * Размер судоку
	 */
	const size_t size;
	/*
	 * Функция, проверяющая, что число выбрано верно
	 *
	 * @param val - проверяемое значение
	 * @param x,y - координаты значения, для судоку, представленного в виде матрицы 
	 */
	bool checkValidity(size_t val, size_t x, size_t y);
	/*
	 * Определение позиции, для которой необходим подбор решения
	 * @param position - номер анализируемой позиции
	 */
	void placeNumber(size_t position);
public:
	/*
	 * Конструктор
	 *
	 * @param *matrix - одномерный массив судоку
	 * @param size - размер судоку
	 */
	sudokuSolver(size_t *matrix, size_t size);
	/*
	 * Деструктор
	 */
	~sudokuSolver();
	/*
	 * Функция, которая пытается решить судоку.
	 * Возвращает true, если есть решение
	 */
	bool solve();
	/*
	 * Заменяет выбранный элементы в судоку на указанный
	 *
	 * @param x - номер заменяемого элемента
	 * @param  item - заменяемое число
	 */
	void changeNumb(size_t x, size_t item);
};