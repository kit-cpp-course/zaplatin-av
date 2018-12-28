#include "params.h"
#include <exception>
#include "stdafx.h"

params::params(const params & source) {
	count = source.count;
	arguments = new char*[count];
	for (size_t i = 0; i < count; i++) {
		arguments[i] = new char[sizeof(source.arguments[i])];
	}
	for (size_t i = 0; i < count; i++) {
		arguments[i] = source.arguments[i];
	}
}

params & params:: operator = (const params & that) {
	for (size_t i = 0; i < count; i++) {
		delete[] arguments[i];
	}
	delete[] arguments;
	count = that.count;
	arguments = new char*[count];
	for (size_t i = 0; i < count; i++) {
		arguments[i] = new char[sizeof(that.arguments[i])];
	}
	for (size_t i = 0; i < count; i++) {
		arguments[i] = that.arguments[i];
	}
	return *this;
}

bool params::isFileExist() const {
	std::fstream file(arguments[3]);
	return file.is_open();
}

bool params::isValue(size_t numb) const{
	try {
		size_t x= std::stoi(arguments[numb]);
		return true;
	}
	catch (...) {
		return false;
	}
}

bool params::isGoodSize() const {
	if (!isValue(2)) { return false; }
	size_t x = std::stoi(arguments[2]);
	return ((size_t)(sqrt(x))*(size_t)(sqrt(x)) == x);
}

bool params::checkValidity() {
	if (count != 4) {
		std::cout << "Неверное количество парамметров" << std::endl;
		return false;
	}
	if (!isValue(1)) {
		std::cout << "Неверно введено количество судоку" << std::endl;
		return false;
	}
	if (!isGoodSize()) {
		std::cout << "Неверно указан размер" << std::endl;
		return false;
	}
	if (!isFileExist()) {
		std::cout << "Заданный файл не существует" << std::endl;
		return false;
	}
	return true;
}

