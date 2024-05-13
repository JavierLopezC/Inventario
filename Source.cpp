#include "Empresa.h"
#include "Item.h"
#include "Movimiento.h"
#include "Inventario.h"
#include "Interfaz.h"
#include <iostream>
#include <cstdio>

int main() {
	//PRUEBAS ITEM
	//Item patata("patata", 20.1, 2);
	//cout << "hola nuevo" << endl;
	//cout << patata.getNombre() << endl;
	//patata.setNombre("patataBis");
	//cout << patata.getNombre() << endl;
	//cout << patata.getValor() << endl;
	//patata.setValor(22.4);
	//cout << patata.getValor() << endl;
	//cout << patata.getCantidad() << endl;
	//patata.setCantidad(4);
	//cout << patata.getCantidad() << endl;
	//cout << patata.printTxt() << endl;
	//cout << patata.to_string() << endl;



	////PRUEBAS INVENTARIO
	//Inventario a = Inventario();
	//a.addItem("patata", 20.4);
	//a.addItem("pescado", 50.4);
	//a.addItem("carne", 1.75);
	//try {
	//	a.addItem("patata", 20.4);
	//}
	//catch (runtime_error& err) {
	//	cout << err.what() << endl;
	//}
	//
	//a.printInventario();
	//a.printTxt("inventario.txt");
	//Inventario b("inventario.txt");
	//b.printInventario();
	//int i;
	//vector<Item> items = b.getItems();
	//for (i = 0; i < items.size(); i++) {
	//	cout << items[i].to_string() << endl;
	//}
	//Inventario c = Inventario();
	//c.setItems(items);
	// items.clear();
	//c.removeItem("patata");

	//try {
	//	c.removeItem("caldo");
	//}
	//catch (runtime_error& err) {
	//	cout << err.what() << endl;
	//}
	//
	//c.printInventario();

	//cout << endl << endl << endl << endl;

	//c.addItemQuantity("pescado", 2);
	//c.addItemQuantity("carne", 7);
	//if(!c.addItemQuantity("caldo", 4)){
	//	cout << "caldo no existe" << endl;
	//}
	//cout << "valorTotal: " + to_string(c.getValorTotal()) << endl;
	//c.printInventario();
	//cout << "valor carne: " + to_string(c.getItemValue("carne")) << endl;

	//c.removeItemQuantity("pescado", 1);
	//if (!c.removeItemQuantity("carne", 8)) {
	//	cout << "no hay bastantes carnes" << endl;
	//}
	//if (!c.removeItemQuantity("caldo", 8)) {
	//	cout << "caldo no existe" << endl;
	//}
	//c.printInventario();



	//PRUEBAS MOVIMIENTO
	//Movimiento compra(0, "patata", 1, 2.32), venta(1, "boniato", 3, 3.75);
	//cout << compra.printTxt();
	//cout << venta.printTxt();
	//cout << compra.to_string() << endl;
	//cout << venta.to_string() << endl;

	//tm tm1{}, tm2{};
	//tm1.tm_mon = 8;
	//tm1.tm_mday = 4;
	//tm1.tm_hour = 12;
	//tm1.tm_min = 55;
	//tm1.tm_sec = 41;
	//tm1.tm_year = 80;
	//tm1.tm_isdst = 0;

	//tm2.tm_mon = 8;
	//tm2.tm_mday = 4;
	//tm2.tm_hour = 12;
	//tm2.tm_min = 55;
	//tm2.tm_sec = 41;
	//tm2.tm_year = 160;
	//tm2.tm_isdst = 0;

	//Movimiento compra2(0, "patata", 1, 2.32, mktime(&tm1)), venta2(1, "boniato", 3, 3.75, mktime(&tm2));
	//cout << compra2.to_string() << endl;
	//cout << venta2.to_string() << endl;

	//cout << compra.compararFechas(compra2) << endl;
	//cout << venta.compararFechas(venta2) << endl;
	//cout << compra.compararFechas(venta) << endl;



	//PRUEBAS EMPRESA
	//Empresa e("empresa1", 10000, 120);
	//cout << e.getDinero() << endl;
	//e.consultarInventario();
	//if (e.comprarItem("patata", 7) == -1) cout << "bien" << endl;
	//cout << e.getDinero() << endl;
	//e.consultarInventario();
	//if (e.comprarItem("patata", 2.5, 7) == 1) cout << "bien" << endl;
	//cout << e.getDinero() << endl;
	//e.consultarInventario();
	//if (e.comprarItem("patata", 2) == 1) cout << "bien" << endl;
	//cout << e.getDinero() << endl;
	//e.consultarInventario();
	//if (e.comprarItem("patata", 10000) == 0) cout << "bien" << endl;
	//cout << e.getDinero() << endl;
	//e.consultarInventario();
	//if (e.comprarItem("boniato", 1) == -1) cout << "bien" << endl;
	//cout << e.getDinero() << endl;
	//e.consultarInventario();
	//if (e.comprarItem("boniato", 100.0, 1000) == 0) cout << "bien" << endl;
	//cout << e.getDinero() << endl;
	//e.consultarInventario();
	//if (e.comprarItem("boniato", 100.0, 3) == 1) cout << "bien" << endl;
	//cout << e.getDinero() << endl;
	//e.consultarInventario();
	//e.consultarMovimientos();
	//e.guardar("movimientos.txt", "inventarioEmpresa.txt");

	//Empresa e2("empresa2", 10000, 120, "movimientos.txt", "inventarioEmpresa.txt");
	//e2.consultarInventario();
	//e2.consultarMovimientos();
	


	//PRUEBAS INTERFAZ
	//comprar(e2, "fruta", 15);
	//verInventario(e2);
	//verMovimientos(e2);
	


	//PROGRAMA
	//El main solo llama a la función interfaz
	interfaz();
	return 0;
}