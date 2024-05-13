#ifndef EMPRESA_HPP
#define EMPRESA_HPP
#include "Inventario.h"
#include "Movimiento.h"

//Clase que representa el conjunto de datos de una empresa
class Empresa {
	private:
		string nombre; //Nombre de la empresa
		Inventario inventario; //Inventario de la empresa
		double dinero; //Dinero deisponible de la empresa
		double margen; //% de ganancia en ventas
		vector<Movimiento*> movimientos; //Array de compras y ventas realizadas por la empresa

	public:
		//Constructores
		Empresa();
		Empresa(string nombre, double dinero, double margen, string fichMovimientos = "", string fichInventario = "");
		//Destructor
		~Empresa();
		//Método que carga los movimientos de la empresa a partir de un fichero
		void cargarMovimientos(string fichMovimientos); 
		//Getters y setters
		string getNombre();
		void setNombre(string nombre);
		Inventario getInventario();
		void setInventario(Inventario inventario);
		double getDinero();
		void setDinero(double dinero);
		double getMargen();
		void setMargen(double margen);
		vector<Movimiento*> getMovimientos();
		void setMovimientos(vector<Movimiento*> movimientos);
		
		//Métodos para comprar items 
		int comprarItem(string nombreItem, int cantidad, string proveedor); //item que ya esta en el inventario
		int comprarItem(string nombreItem, double valor, int cantidad, string proveedor); // item que no esta en el inventario
		//Método para vender items del inventario
		int venderItem(string nombreItem, int cantidad);
		//Método que imprime los movimientos por pantalla
		void consultarMovimientos();
		//Método que imprime el inventario por pantalla
		void consultarInventario();
		//Método que guarda los datos de la empresa (incluyendo inventario y movimeintos) en los ficheros correspondientes
		void guardar(string fichMovimientos, string fichInventario);
};

#endif //EMPRESA_HPP