#include "Movimiento.h"
#include <time.h>

//Getters y setters sencillos de los atributos comunes de Movimiento
string Movimiento::getNombreItem() {
	return this->nombreItem;
}

void Movimiento::setnombreItem(string nombreItem) {
	this->nombreItem = nombreItem;
}

int Movimiento::getCantidad() {
	return this->cantidad;
}

void Movimiento::setCantidad(int cantidad) {
	this->cantidad = cantidad;
}

double Movimiento::getImporte() {
	return this->importe;
}

void Movimiento::setImporte(double importe) {
	this->importe = importe;
}

time_t Movimiento::getFecha() {
	return this->fecha;
}

void Movimiento::setFecha(time_t fecha) {
	this->fecha = fecha;
}


//Subclase Compra

//Constructor sin fecha, establece como fecha y hora del movimiento la actual
Compra::Compra(string nombreItem, int cantidad, double importe, string proveedor) {
	time_t fecha;
	this->nombreItem = nombreItem;
	this->cantidad = cantidad;
	this->importe = importe;
	this->proveedor = proveedor;
	time(&fecha);
	this->fecha = fecha;
}

//Constructor con fecha
Compra::Compra(string nombreItem, int cantidad, double importe,  string proveedor, time_t fecha) {
	this->nombreItem = nombreItem;
	this->cantidad = cantidad;
	this->importe = importe;
	this->proveedor = proveedor;
	this->fecha = fecha;
}

//Destructor
Compra::~Compra() {}

//Getter de proveedor
string Compra::getProveedor() {
	return this->proveedor;
}

//Setter de proveedor
void Compra::setProveedor(string proveedor) {
	this->proveedor = proveedor;
}

//Método que devuelve una string con los datos de movimiento en el formato adecuado para imprimir en fichero "Compra \t <nombreItem> \t <cantidad> \t <importe> \t <proveedor> \t <fecha>"
string Compra::printTxt() {
	char fecha[26];
	ctime_s(fecha, sizeof fecha, &this->fecha);
	return "Compra\t" + this->nombreItem + "\t" + std::to_string(this->cantidad) + "\t" + std::to_string(this->importe) + "\t" + this->proveedor + "\t" + fecha ;
}

//Método que devuelve una string con los datos de movimiento en el formato adecuado para imprimir por pantalla "Compra de <Cantidad> <nombreItem> a <proveedor> por valor de <importe>$ en la fecha: <fecha>"
string Compra::to_string() {
	char fecha[26];
	ctime_s(fecha, sizeof fecha, &this->fecha);
	char aux[128];
	sprintf_s(aux, 128, "%.2f", this->importe);
	return "Compra de " + std::to_string(this->cantidad) + " " + this->nombreItem + " a " + this->proveedor + " por valor de " + aux + "$ en la fecha: " + fecha;
}


//Constructor sin fecha, establece como fecha y hora del movimiento la actual
Venta::Venta(string nombreItem, int cantidad, double importe, double beneficio) {
	time_t fecha;
	this->nombreItem = nombreItem;
	this->cantidad = cantidad;
	this->importe = importe;
	this->beneficio = beneficio;
	time(&fecha);
	this->fecha = fecha;
}

//Constructor con fecha
Venta::Venta(string nombreItem, int cantidad, double importe, double beneficio, time_t fecha) {
	this->nombreItem = nombreItem;
	this->cantidad = cantidad;
	this->importe = importe;
	this->beneficio = beneficio;
	this->fecha = fecha;
}

//Destructor
Venta::~Venta() {}

//Getter de beneficio
double Venta::getBeneficio() {
	return this->beneficio;
}

//Setter de beneficio
void Venta::setBeneficio(double beneficio) {
	this->beneficio = beneficio;
}

//Método que devuelve una string con los datos de movimiento en el formato adecuado para imprimir en fichero "Venta \t <nombreItem> \t <cantidad> \t <importe> \t <beneficio> \t <fecha>"
string Venta::printTxt() {
	char fecha[26];
	ctime_s(fecha, sizeof fecha, &this->fecha);
	return "Venta\t" + this->nombreItem + "\t" + std::to_string(this->cantidad) + "\t" + std::to_string(this->importe) + "\t" + std::to_string(this->beneficio) + "\t" + fecha ;
}


//Método que devuelve una string con los datos de movimiento en el formato adecuado para imprimir por pantalla "Venta de <Cantidad> <nombreItem> por valor de <importe>$ con un beneficio de <beneficio>$ en la fecha: <fecha>"
string Venta::to_string() {
	char fecha[26];
	ctime_s(fecha, sizeof fecha, &this->fecha);
	char valor[128], beneficio[128];
	sprintf_s(valor, 128, "%.2f", this->importe);
	sprintf_s(beneficio, 128, "%.2f", this->beneficio);
	return "Venta de " + std::to_string(this->cantidad) + " " + this->nombreItem + " por valor de " + valor + "$ con un beneficio de " + beneficio + "$ en la fecha: " + fecha;
}