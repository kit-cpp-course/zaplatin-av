#pragma once

#include <string>

/*
 * Класс, предназначенный для обработки входных парамметров
 */
class params {
	/*
	 * Количество входных парамметров 
	 */
	size_t count;
	/*
	 * Массив парамметров
	 */
	char ** arguments;
	/*
	 * Функция, проверяющая наличие указанного файла
	 */
	bool isFileExist() const;
	/*
	 * Функция проверяет, что аргумент является целым неотрицательным числом
	 *
	 * @param numb - номер парамметра
	 */
	bool isValue(size_t numb) const;
	/*
	 * Функция проверят, что сторона судоку задана верно
	 */
	bool isGoodSize() const;
public:
	/*
	 * Конструктор
	 *
	 * @param count - количество аргументов
	 * @param arguments - массив аргументов
	 */
	params(size_t count, char ** arguments) :
		count(count), arguments(arguments) {};
	/*
	 * Конструктор копирования.
	 *
	 * Создаёт объект с параметрами на основе уже существующих параметров
	 *
	 * @param source параметры, на совнове которых следует создать
	 * новые параметры
	*/
	params(const params & source);
	/*
	 * Оператор присваивания.
	 *
	 * Присваивает объекту значения параметров.
	 *
	 * @param that второй операнд. Данные, из которых следует взять
	 * значения для текущих праметров
	 * @returns ссылку на текущий экземпляр класса.
	 */
	params & operator = (const params & that);
	/*
	 * Функция, проверяющая корректность введеных аргументов
	 */
	bool checkValidity();
	/*
	 * Функция, возвращает путь файла
	 */
	std::string Path() { return (std::string)arguments[3]; };
	/*
	 * Функция, возвращает количество необходимых судоку
	 */
	size_t getNumb() { return std::stoi(arguments[1]); };
	/*
	 * Функция, возвращает размер судоку
	 */
	size_t getSize() { return std::stoi(arguments[2]); }
};