#include "Inventario.h"
#include "excepciones.h"
#include <cstdio>
#include <fstream>
#include <sstream>

//Constructor vacío, pone todo a 0
Inventario::Inventario() {
	this->items = {};
	this->valorTotal = 0;
}

//Coonstructor a partir de un fichero
Inventario::Inventario(string fichero) {
	string linea, aux, nombreItem;
	int cantidadItem;
	double valorItem;
	//Inicializamos a 0 el inventario
	this->items = {};
	this->valorTotal = 0;
	//Abrimos el fichero de inventario si no se puede lanzamos excepción
	ifstream Fichero(fichero);
	if (!Fichero) {
		this->items.clear();
		throw FileException("Error al abrir el fichero de inventario");
	}

	//Leemos línea a línea, cada línea es un item
	while (getline(Fichero, linea)) {
		stringstream tokenizer(linea);
		//Dividimos la línea por los tabuladores
		getline(tokenizer, aux, '\t');
		//El primer elemento de la linea es el nombre del item
		nombreItem = aux;
		//Comprobamos que no se añada 2 veces el mismo item al inventario
		if (this->searchItem(nombreItem) != -1) {
			this->items.clear();
			Fichero.close();
			throw FileException("Fichero con formato incorrecto: Item duplicado");
		}
		//El segundo elemento es el valor del item, tiene que ser un numero real
		getline(tokenizer, aux, '\t');
		try {
			valorItem = stod(aux);
		}
		catch (...) {
			this->items.clear();
			Fichero.close();
			throw FileException("Fichero con formato incorrecto: valor erroneo");
		}
		//El tercer elemento es la cantidad, tiene que ser un entero
		getline(tokenizer, aux, '\t');
		try {
			cantidadItem = stoi(aux);
		}
		catch (...) {
			this->items.clear();
			Fichero.close();
			throw FileException("Fichero con formato incorrecto: Cantidad erronea");
		}
		//Actualizamos el valor total sumando el valor del item leido
		this->valorTotal += valorItem*cantidadItem;
		//Añadimos el item a la lista de items
		this->items.push_back(Item(nombreItem, valorItem, cantidadItem));
	}
	Fichero.close();
}

//Destructor
Inventario::~Inventario() {
	this->items.clear();
}

//Getter del array de items
vector<Item> Inventario::getItems() {
	vector<Item> items;
	int i;
	//Creamos una copia del array para no devolver el mismo espacio de memoria
	for (i = 0; i < this->items.size(); i++) {
		items.push_back(Item(this->items[i].getNombre(), this->items[i].getValor(), this->items[i].getCantidad()));
	}
	return items;
}

//Getter del valor total del inventario
double Inventario::getValorTotal() {
	return this->valorTotal;
}

//Método que busca un item en el inventario, devuelve su índice en el array de items o -1 si no está en el inventario
int Inventario::searchItem(string nombre) {
	int i;
	for (i = 0; i < this->items.size(); i++) {
		if (this->items[i].getNombre() == nombre) {
			return i;
		}
	}
	return -1;
}

//Método que devuelve el valor de un item del inventario
double Inventario::getItemValue(string nombre) {
	int index;
	index = this->searchItem(nombre);
	//Si el item no está en el inventario lanzamos una excepción pues no tiene sentido este método
	if (index == -1) {
		throw LogicException("ERROR: el item no existe en el inventario");
	}
	return this->items[index].getValor();
}

//Setter del listado de items
void Inventario::setItems(vector<Item> items) {
	int i;
	double valor = 0;
	this->items = {};
	//Recorremos el listado de items y los añadimos 1 a 1 comprobando que no haya items duplicados
	for (i = 0; i < items.size(); i++) {
		if (this->searchItem(items[i].getNombre()) != -1) {
			throw LogicException("Vector de items incorrecto: Item duplicado");
		}
		this->items.push_back(Item(items[i].getNombre(), items[i].getValor(), items[i].getCantidad()));
		//Vamos actualizando el valor total con cada item añadido
		valor += items[i].getValor() * items[i].getCantidad();
	}
	this->valorTotal = valor;
}

//Método que añade un item nuevo al inventario, si el item esta duplicado lanza una excepción
void Inventario::addItem(string nombre, double valor) {
	if (this->searchItem(nombre) == -1) {
		this->items.push_back(Item(nombre, valor, 0));
	}
	else {
		throw LogicException("Item duplicado");
	}
}

//Método que quita un item del inventario, si el item no está en el inventario lanza una excepción
void Inventario::removeItem(string nombre) {
	int indice = this->searchItem(nombre);
	if (indice == -1) {
		throw LogicException("Item no existente");
	}
	else {
		//actualizamos también el valor total del inventario
		this->valorTotal -= this->items[indice].getValor() * this->items[indice].getCantidad();
		this->items.erase(this->items.begin() + indice);
	}
}

//Método que añade una cierta cantidad de un item, devuelve 1 si todo va bien y 0 si no existe el item
int Inventario::addItemQuantity(string nombre, int cantidad) {
	int indice = this->searchItem(nombre);
	if (indice == -1) {
		return 0;
	}
	else {
		this->valorTotal += this->items[indice].getValor() * cantidad;
		this->items[indice].setCantidad(this->items[indice].getCantidad() + cantidad);
	}
	return 1;
}

//Método que retira una cierta cantidad de un item, devuelve 1 si todo va bien y 0 si no hay suficientes de ese item en el inventario
int Inventario::removeItemQuantity(string nombre, int cantidad) {
	int indice = this->searchItem(nombre);
	if (indice == -1) {
		return 0;
	}
	else {
		if (this->items[indice].getCantidad() < cantidad) 
			return 0;
		this->valorTotal -= this->items[indice].getValor() * cantidad;
		this->items[indice].setCantidad(this->items[indice].getCantidad() - cantidad);
	}
	return 1;
}

//Método que imprime el inventario item a item en un fichero txt
void Inventario::printTxt(string fichero) {
	int i;
	//Eliminamos el fichero de inventario para crearlo de cero
	remove(fichero.c_str());
	ofstream Fichero(fichero);
	if (!Fichero) {
		throw FileException("Error al abrir el fichero de inventario");
	}
	for (i = 0; i < this->items.size(); i++) {
		//llamamos al método printTxt de Item para cada item del inventario
		Fichero << this->items[i].printTxt();
	}
	Fichero.close();
}

//Método que imprime el inventario por pantalla
void Inventario::printInventario() {
	int i;
	char valor[128];
	sprintf_s(valor, 128, "%.2f", this->valorTotal);
	//La primera linea contiene el número total de items y el valor del inventario
	cout << "Numero total de items: " << this->items.size() << "\t Valor total del inventario: " << valor << "$" << endl;
	//Después cada línea es un item
	for (i = 0; i < this->items.size(); i++) {
		cout << this->items[i].to_string() << endl;
	}
}