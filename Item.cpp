#include "Item.h"
#include <fstream>
#include <iostream>

//Constructor por defecto, pone todos los campos a cero
Item::Item() {
	this->nombre = "";
	this->valor = 0;
	this->cantidad = 0;
}

//Constructor
Item::Item(string nombre, double valor, int cantidad = 0) {
	this->nombre = nombre;
	this->valor = valor;
	this->cantidad = cantidad;
}

//Destructor
Item::~Item(){}

// Setters y getters
string Item::getNombre() {
	return nombre;
}

void Item::setNombre(string nombre) {
	this->nombre = nombre;
}

double Item::getValor() {
	return valor;
}

void Item::setValor(double valor) {
	this->valor = valor;
}

int Item::getCantidad() {
	return cantidad;
}

void Item::setCantidad(int cantidad) {
	this->cantidad = cantidad;
}


//Devuelve una string para imprimir en fichero txt con formato "<nombre> \t <valor> \t <cantidad>"
string Item::printTxt() {
	return this->nombre + "\t" + std::to_string(this->valor) + "\t" + std::to_string(this->cantidad) + "\n";
}

//Devuelve el item como una string con formato "Nombre del item: <nombre>, valor: <valor>$, cantidad: <cantidad>"
string Item::to_string() {
	char aux[128];
	sprintf_s(aux, 128, "%.2f", this->valor);
	return "Nombre del item: " + this->nombre + ", valor: " + aux + "$, cantidad: " + std::to_string(this->cantidad);
}



