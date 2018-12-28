#pragma once
#include  "abstract_sudokuSolver.h"
/*
 * Класс, проверяющий наличие решения судоку
 */
class sudokuSolver: public solver{
	/*
	 * Одномерный массив, являющийся полем судоку
	 */
	size_t *grid;
	/*
	 * Размер судоку
	 */
	size_t size;
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
	 * Конструктор копирования.
	 *
	 * Создаёт судоку на основе уже существующего судоку.
	 *
	 * @param source судоку, на совнове которого следует создать
	 * новое судоку
	 */
	sudokuSolver(const sudokuSolver & source);
	/*
	 * Оператор присваивания.
	 *
	 * Присваивает судоку значения из другого судоку.
	 *
	 * @param that второй операнд. Судоку, из которого следует взять
	 * значения для текущего судоку.
	 * @returns ссылку на текущий экземпляр класса.
	 */
	sudokuSolver & operator = (const sudokuSolver & that);
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