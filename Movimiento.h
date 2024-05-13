#ifndef MOVIMIENTO_HPP
#define MOVIMIENTO_HPP
#include "Item.h"

//Clase abstracta que incluye las compras y las ventas realizadas
class Movimiento {
	//Las subclases necesitan acceder a los atributos
	protected:
		string nombreItem; //Nombre del item comprado o vendido
		int cantidad; //Cantidad del item comprada o vendida
		double importe; //Importe de la compra o venta
		time_t fecha; //Fecha en la que se realiza el movimiento

	public:
		//Getters y setters de atributos comunes
		string getNombreItem();
		void setnombreItem(string nombreItem);
		int getCantidad();
		void setCantidad(int cantidad);
		double getImporte();
		void setImporte(double importe);
		time_t getFecha();
		void setFecha(time_t fecha);

		//Métodos virtuales implementados en las subclases
		virtual string printTxt() = 0;
		virtual string to_string() = 0;
};

//Sublclase de movimiento para las compras
class Compra : public Movimiento {
	private:
		//Contiene el proveedor de la compra
		string proveedor;
	public:
		//Constructores
		Compra(string nombreItem, int cantidad, double importe, string proveedor);
		Compra(string nombreItem, int cantidad, double importe, string proveedor, time_t fecha);
		//Destructor
		~Compra();
		//Getter y setter de proveedor
		string getProveedor();
		void setProveedor(string proveedor);
		//Métodos virtuales de movimiento implementados
		string printTxt();
		string to_string();
};

//Sublclase de movimiento para las ventas
class Venta : public Movimiento {
	private:
		//Contiene el beneficio obtenido con la venta
		double beneficio;
	public:
		//Constructores
		Venta(string nombreItem, int cantidad, double importe, double beneficio);
		Venta(string nombreItem, int cantidad, double importe, double beneficio, time_t fecha);
		//Destructor
		~Venta();
		//Getter y setter de beneficio
		double getBeneficio();
		void setBeneficio(double beneficio);
		//Métodos virtuales de movimiento implementados
		string printTxt();
		string to_string();
};

#endif //MOVIMIENTO_HPP