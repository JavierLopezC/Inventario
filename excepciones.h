#ifndef EXCEPCIONES_HPP
#define EXCEPCIONES_HPP

#include <iostream>
using namespace std;

//Creamos una excepción para los errores de focrmato o apertura de los ficheros de empresa, inventario y movimientos
class FileException : public exception {
public:
	FileException(const char* message) : exception(message) {}
};

//Creamos un tipo de excepción para los errores en la lógica del programa
class LogicException : public exception {
public:
	LogicException(const char* message) : exception(message) {}
};

#endif //EXCEPCIONES_HPP