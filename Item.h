#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
using namespace std;

//Clase que representa cada uno de los items que se van a almacenar en el inventario
class Item {
private:
	string nombre; //Nombre del item
	double valor; //Valor del item en $
	int cantidad; //Cantidad de items que se tienen

public:
	//Constructores
	Item();
	Item(string nombre, double valor, int cantidad);
	//Destructor
	~Item();

	//Getters y setters
	string getNombre();
	void setNombre(string nombre);
	double getValor();
	void setValor(double valor);
	int getCantidad();
	void setCantidad(int cantidad);

	//Otros métodos
	string printTxt(); //Devuelve una string los datos del item en el formato adecuado para imprimir el item en fichero
	string to_string();	//Devuelve los datos del item en una string
};

#endif //ITEM_HPP
