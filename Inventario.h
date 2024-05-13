#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include "Item.h"
#include <vector>

//Clase que representa el inventario de una empresa
class Inventario {
	private:
		vector<Item> items; //Array de items en el inventario
		double valorTotal; //Valor total de todos los items del inventario
	
	public:
		//Constructores
		Inventario();
		Inventario(string fichero);

		//Destructor
		~Inventario();

		//Getters y setters
		vector<Item> getItems();
		double getValorTotal();
		void setItems(vector<Item> items);

		//Otrso métodos
		int searchItem(string nombre); // Comprueba si el item esta en el inventario y devuelve su indice del array
		double getItemValue(string nombre); //Devuelve el valor del item
		void addItem(string nombre, double valor); //Añade un item nuevo al inventario
		void removeItem(string nombre); //Quita un item del inventario
		int addItemQuantity(string nombre, int cantidad); //Añade cierta cantidad de un item que ya está en el inventario
		int removeItemQuantity(string nombre, int cantidad); //Quita cierta cantidad de items del inventario sin sacarlos del array
		void printTxt(string fichero); //Imprime el Inventario en un fichero txt
		void printInventario(); //Método que imprime el inventario por pantalla
};

#endif //INVENTARIO_HPP