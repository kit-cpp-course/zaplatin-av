#pragma once

/*
 * Абстрактный класс, описывающий решение чего-либо
 */
class solver {
public:
	/*
	 * Проверка на наличие решения
	 */
	virtual bool solve() = 0;
};