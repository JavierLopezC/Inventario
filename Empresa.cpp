#include "Empresa.h"
#include "Excepciones.h"
#include <cstdio>
#include <time.h>
#include <fstream>
#include <sstream>

//Constructor vacío, pone todo a 0
Empresa::Empresa() {
	this->nombre = "";
	this->inventario = Inventario();
	this->dinero = 0;
	this->margen = 0;
	this->movimientos = {};
}

//Constructor de Empresa, carga los movimientos y el inventario desde ficheros
Empresa::Empresa(string nombre, double dinero, double margen, string fichMovimientos, string fichInventario) {
	string errMsg;
	//Inicializamos el nombre
	this->nombre = nombre;
	//Si hay fichero de inventario cargamos el inventario, si hay un error lanzamos una excepción
	if (fichInventario != "") {
		try {
			this->inventario = Inventario(fichInventario);
		}
		catch (const FileException& err) {
			this->inventario = Inventario();
			errMsg = err.what();
			throw runtime_error("Error al cargar el inventario: " + errMsg);
		}
	}
	//Si no inicializamos el inventario vacío
	else this->inventario = Inventario();
	//Inicializamos dinero, margen y el array de movimientos vacío
	this->dinero = dinero;
	this->margen = margen;
	this->movimientos = {};
	//Cargamos los movimientos desde fichero con el método cargarMovimientos, si hay un error lanzamos una excepción
	try {
		this->cargarMovimientos(fichMovimientos);
	}
	catch (const exception& err) {
		this->movimientos.clear();
		this->movimientos = {};
		errMsg = err.what();
		throw runtime_error("Error al cargar los movimientos: " + errMsg);
	}
}

//Destructor
Empresa::~Empresa() {
	this->movimientos.clear();
}

//Función que transforma una string con la fecha y hora de un movimiento a una fecha de tipo time_t
time_t parseDate(string date) {
	tm tm{};
	int dia, hora, min, sec, anio, wday, month;
	char dia_s[4], mes[4];
	string dia_ss, mes_s;
	char* aux = new char[date.length() + 1];

	//Copiamos la stringa  un char* para poder usar sscanf_s
	strcpy_s(aux, date.length() + 1, date.c_str());

	//Usamos sscanf_s para guardar los datos de la fecha en distintas variables, lanzamos una excepción si el formato de la fecha es incorrecto
	if (sscanf_s(aux, "%s %s %i %i:%i:%i %i", dia_s, 4, mes, 4, &dia, &hora, &min, &sec, &anio) != 7)
		throw FileException("Fichero de movimientos con formato incorrecto: fecha erronea");

	//Liberamos la memoria del char*
	delete[] aux;

	//Copiamos el char* que contiene el día a una string para poder compararlo cómodamente
	dia_ss.assign(dia_s, 3);
	//Guardamos el día en un int pues en la estructura tm se guarda como int
	if (dia_ss == "Mon") wday = 1;
	else if (dia_ss == "Tue") wday = 2;
	else if (dia_ss == "Wed") wday = 3;
	else if (dia_ss == "Thu") wday = 4;
	else if (dia_ss == "Fri") wday = 5;
	else if (dia_ss == "Sat") wday = 6;
	else if (dia_ss == "Sun") wday = 0;
	else throw FileException("Fichero de movimientos con formato incorrecto: fecha erronea");

	//Repetimos el proceso con el mes
	mes_s.assign(mes,3);
	if (mes_s == "Jan") month = 0;
	else if (mes_s == "Feb") month = 1;
	else if (mes_s == "Mar") month = 2;
	else if (mes_s == "Apr") month = 3;
	else if (mes_s == "May") month = 4;
	else if (mes_s == "Jun") month = 5;
	else if (mes_s == "Jul") month = 6;
	else if (mes_s == "Aug") month = 7;
	else if (mes_s == "Sep") month = 8;
	else if (mes_s == "Oct") month = 9;
	else if (mes_s == "Nov") month = 10;
	else if (mes_s == "Dec") month = 11;
	else throw FileException("Fichero de movimientos con formato incorrecto: fecha erronea");

	//Rellenamos la estructura tm
	tm.tm_wday = wday;
	tm.tm_mon = month;
	tm.tm_mday = dia;
	tm.tm_hour = hora;
	tm.tm_min = min;
	tm.tm_sec = sec;
	tm.tm_year = anio - 1900;
	tm.tm_isdst = 0;

	//Devolvemos el time_t de la estructura tm
	return mktime(&tm);
}

//Método que carga los movimientos de la empresa a partir de un fichero
void Empresa::cargarMovimientos(string fichero) {
	string linea, aux, nombreItem, tipo, proveedor;
	char* errMsg;
	int cantidad;
	double importe, beneficio = 0;
	time_t fecha;
	//Si no hay fichero inicializamos el array de movimientos vacío
	if (fichero == "") {
		this->movimientos = {};
		return;
	}
	//Abrimos el fichero
	ifstream Fichero(fichero);
	if (!Fichero) {
		throw FileException("Error al abrir el fichero de movimientos");
	}
	//Leemos línea a línea, cada línea es un movimiento
	while (getline(Fichero, linea)) {
		//Separamos la línea por los tabuladores
		stringstream tokenizer(linea);
		//El primer elemento es el tipo (si es compra o es venta) 
		getline(tokenizer, aux, '\t');
		tipo = aux;
		//El segundo elemento es el nombre del item comprado o vendido
		getline(tokenizer, aux, '\t');
		nombreItem = aux;
		//El tercer elemento es la cantidad comprada o vendida, debe ser un entero
		getline(tokenizer, aux, '\t');
		try {
			cantidad = stoi(aux);
		}
		catch (...) {
			Fichero.close();
			throw FileException("Fichero de movimientos con formato incorrecto: valor erroneo");
		}
		//El cuarto elemento es el importe de compra o venta, debe ser un número real
		getline(tokenizer, aux, '\t');
		try {
			importe = stod(aux);
		}
		catch (...) {
			Fichero.close();
			throw FileException("Fichero de movimientos con formato incorrecto: valor erroneo");
		}

		getline(tokenizer, aux, '\t');
		//Si es compra, el quinto elemento es el proveedor
		if (tipo == "Compra") {
			proveedor = aux;
		}
		//Si es venta, el quinto elemento es el beneficio que debe ser un número real
		else if (tipo == "Venta") {
			try {
				beneficio = stod(aux);
			}
			catch (...) {
				Fichero.close();
				throw FileException("Fichero de movimientos con formato incorrecto: beneficio erroneo");
			}
		}
		else {
			Fichero.close();
			throw FileException("Fichero de movimientos con formato incorrecto: Tipo erroneo");
		}
		//El sexto elemento es la fecha
		getline(tokenizer, aux, '\t');
		//Transformamos el string de fecha a time_t con parseDate y si hay algun problema lanzamos excepción
		try {
			fecha = parseDate(aux);
		}
		catch (const FileException& err) {
			Fichero.close();
			throw FileException(err);
		}
		//Añadimos la compra o venta al array de movimientos
		if (tipo == "Compra")
			this->movimientos.push_back(new Compra(nombreItem, cantidad, importe, proveedor, fecha));
		else if (tipo == "Venta") 
			this->movimientos.push_back(new Venta(nombreItem, cantidad, importe, beneficio, fecha));
	}
	Fichero.close();
}


//Getters y setters  de los atributos de la empresa
string Empresa::getNombre() {
	return this->nombre;
}

void Empresa::setNombre(string nombre) {
	this->nombre = nombre;
}

Inventario Empresa::getInventario() {
	return this->inventario;
}

void Empresa::setInventario(Inventario inventario) {
	//Copiamos el inventario para no emplear el mismo espacio de memoria que nos pasan
	this->inventario = Inventario();
	this->inventario.setItems(inventario.getItems());
}

double Empresa::getDinero() {
	return this->dinero;
}

void Empresa::setDinero(double dinero) {
	this->dinero = dinero;
}

double Empresa::getMargen() {
	return this->margen;
}

void Empresa::setMargen(double margen) {
	this->margen = margen;
}

vector<Movimiento*> Empresa::getMovimientos() {
	return this->movimientos;
}

void Empresa::setMovimientos(vector<Movimiento*> movimientos) {
	this->movimientos = movimientos;
}

//Método para comprar un item que ya está en el inventario, devuelve 1 si todo va bien , 0 si no hay bastante dinero o -1 si el item no esta en el inventario
int Empresa::comprarItem(string nombreItem, int cantidad, string proveedor) {
	double importe;
	time_t fecha;
	//Si no está en el inventario devolvemos -1
	if (this->inventario.searchItem(nombreItem) == -1) return -1;
	//Si no hay bastante dinro en la empresa devuelve 0
	importe = this->inventario.getItemValue(nombreItem) * cantidad;
	if (importe > this->dinero) return 0;
	//Añadimos la cantidad del item al inventario con el método addItemQuantity de Inventario
	if (this->inventario.addItemQuantity(nombreItem, cantidad)) {
		//Restamos el dinero a la empresa
		this->dinero -= importe;
		//Añadimos la compra al array de movimientos
		this->movimientos.push_back(new Compra(nombreItem, cantidad, importe, proveedor, time(&fecha)));
		return 1;
	}
	else throw LogicException("Algo ha ido mal al comprar el item");
}

//Método para comprar un item que no está en el inventario, devuelve 1 si se realiza la compra y 0 si no hay bastante dinero, si el item no se añade bien al inventario lanza una excepcion, pues es un error
int Empresa::comprarItem(string nombreItem, double valor, int cantidad, string proveedor) {
	time_t fecha;
	double importe = valor * cantidad;
	//Si no hay bastante dinero devuelve 0
	if (importe > this->dinero) return 0;
	//Añadimos el item al inventario con addItem
	this->inventario.addItem(nombreItem, valor);
	//Añadimos la cantidad del item al inventario con el método addItemQuantity de Inventario
	if (this->inventario.addItemQuantity(nombreItem, cantidad)) {
		//Restamos el dinero a la empresa
		this->dinero -= importe;
		//Añadimos la compra al array de movimientos
		this->movimientos.push_back(new Compra(nombreItem, cantidad, importe, proveedor, time(&fecha)));
		return 1;
	}
	else throw LogicException("ERROR: Ha habido un error al aniadir el item al inventario");

}

//Método para vender Items, devuelve 1 si todo va bien y 0 si no hay bastantes items en el inventario
int Empresa::venderItem(string nombreItem, int cantidad) {
	double importe;
	time_t fecha;
	//Quitamos los items del inventario con removeItemQuantity
	if (this->inventario.removeItemQuantity(nombreItem, cantidad)) {
		//Calculamos el importe de la venta
		importe = this->inventario.getItemValue(nombreItem) * cantidad * (this->margen / 100);
		//Sumamos el dinero a la empresa
		this->dinero += importe;
		//Añadimos la venta al array de movimientos
		this->movimientos.push_back(new Venta(nombreItem, cantidad, importe, importe-(this->inventario.getItemValue(nombreItem) * cantidad), time(&fecha)));
		return 1;
	}
	//Si no hay bastantes items devuelve 0
	return 0;
}

//Método que imprime por pantalla los movimientos de la empresa
void Empresa::consultarMovimientos() {
	int i;
	//Si no hay movimientos
	if (this->movimientos.size() == 0) {
		cout << "No hay movimientos";
		return;
	}
	//Si hay movimientos imprimimos el to_string de cada movimiento en una línea
	for (i = 0; i < this->movimientos.size(); i++) {
		cout << this->movimientos[i]->to_string();
	}
}

//Método que imprime por pantalla el inventario de la empresa llamando a printInventario
void Empresa::consultarInventario() {
	this->inventario.printInventario();
}

//Método que guarda el inventario y los movimientos en los ficheros correspondientes
void Empresa::guardar(string fichMovimientos, string fichInventario) {
	int i;
	//Imprimimos el inventario en su fichero
	try {
		this->inventario.printTxt(fichInventario);
	}
	catch (FileException& err) {
		throw FileException(err);
	}

	//Eliminamos el fichero de movimientos de la empresa para reescribirlo
	remove(fichMovimientos.c_str());
	ofstream Fichero(fichMovimientos);
	if (!Fichero) {
		throw FileException("Error al abrir el fichero de movimientos");
	}
	//Imprimimos en cada línea un movimiento
	for (i = 0; i < this->movimientos.size(); i++) {
		Fichero << this->movimientos[i]->printTxt();
	}
	Fichero.close();
}

