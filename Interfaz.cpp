#include "Interfaz.h"
#include "excepciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <stdlib.h>

//Función que imprime por pantalla los distintos comandos que puede realizar el usuario
//Parámetro login: bool que es true si hay sesión abiarta y false si no
void opciones(bool login) {
	//Comandos si se ha hecho login con una empresa
	if (login) {
		cout << "<Opciones> para ver las acciones posibles" << endl;
		cout << "<Comprar> para comprar items" << endl;
		cout << "<Vender> para vender items" << endl;
		cout << "<AddEfectivo> para aniadir dinero a la cuenta de la empresa" << endl;
		cout << "<CambiarMargen> para cambiar el margen de ventas de la empresa" << endl;
		cout << "<Efectivo> para consultar el dinero en la cuenta de la empresa" << endl;
		cout << "<Margen> para consultar el margen de ventas de la empresa" << endl;
		cout << "<Inventario> para consultar el inventario" << endl;
		cout << "<Movimientos> para consultar las compras y ventas de la empresa" << endl;
		cout << "<Guardar> para guardar los datos de compras y ventas de esta sesion" << endl;
		cout << "<Logout> para cerrar sesion" << endl;
		cout << "<Salir> para salir del programa" << endl;
	}
	//Comandos si no se ha hecho login aún
	else {
		cout << "<Opciones> para ver las acciones posibles" << endl;
		cout << "<Login> para iniciar sesion en una empresa" << endl;
		cout << "<Salir> para salir del programa" << endl;
	}
}

//Función para registar una empresa que aún no está en el fichero de empresas "empresas.txt"
//Parámetro login: bool pasado por referencia que determona si hay o no sesión abierta
//Parámetro nombreEmpresa: nombre de la empresa a registrar
//Return: objeto Empresa con la empresa registrada
Empresa registrar(bool& login, string nombreEmpresa) {
	Empresa e;
	int flagEntrada = 1;
	string contrasenia, dineroInicial_s, margen_s;
	double dineroInicial, margen;

	//Pedimos la contraseña
	cout << "Establece la contrasenia: ";
	cin >> contrasenia;

	//Pedimos el dinero inciial de la empresa, que debe ser un número real
	cout << "Cual es el dinero incial? ";
	while (flagEntrada) {
		cin >> dineroInicial_s;
		try {
			dineroInicial = stod(dineroInicial_s);
			flagEntrada = 0;
		}
		catch (...) {
			cout << "Valor no valido, el dinero incial debe ser un numero real: ";
		}
	}
	
	flagEntrada = 1;

	//Pedimos el margen de ventas, que debe ser un número real
	cout << "Cual es el margen de ventas? (% que determina el precio de venta de los items, 100 supone que se vende a precio de compra)" << endl;
	while (flagEntrada) {
		cin >> margen_s;
		try {
			margen = stod(margen_s);
			flagEntrada = 0;
		}
		catch (...) {
			cout << "Valor no valido, el margen debe ser un numero real: ";
		}
	}
	
	//Imprimimos los datos de la nueva empresa en el fichero de empresas que se llama siempre "empresas.txt"
	ofstream Fichero("empresas.txt", ofstream::app);
	if (!Fichero) {
		login = false;
		throw FileException("Error al abrir el fichero empresas.txt");
	}
	Fichero << nombreEmpresa + "\t" + contrasenia + "\t" + dineroInicial_s + "\t" + margen_s << endl;
	Fichero.close();

	//Construimos el objeto Empresa con estos datos
	try {
		e = Empresa(nombreEmpresa, dineroInicial, margen);
	}
	catch (runtime_error& err) {
		login = false;
		throw runtime_error(err.what());
	}
	//Establecemos que se ha hecho login
	login = true;
	//Devolvemos la empresa
	return e;
}


//Función para hacer login
//Parámetro login: bool pasado por referencia que determona si hay o no sesión abierta
//Return: objeto Empresa con la empresa registrada
Empresa logIn(bool& login) {
	string linea, aux, nombreEmpresa, contrasenia, entrada;
	Empresa e;
	ifstream Fichero;
	int flagContrasenia = 3, flagEntrada = 1;
	double dinero, margen;
	//Pedimos el nombre de la empresa
	cout << "Introduce el nombre de la empresa: ";
	cin >> nombreEmpresa;
	//Comprobamos que el fichero de empresas "empresas.txt" existe y si no lo creamos
	Fichero = ifstream("empresas.txt");
	if (!Fichero.good()) {
		Fichero.close();
		ofstream FicheroAux("empresas.txt");
		FicheroAux.close();
		Fichero = ifstream("empresas.txt");
	}
	if (!Fichero) {
		cout << "Error al abrir el fichero empresas.txt. No se ha podido hacer login" << endl;
		login = false;
		return e;
	}
	//Leemos linea a linea el fichero, cada linea es una empresa registrada
	while (getline(Fichero, linea)) {
		stringstream tokenizer(linea);
		//Separamos la linea por los tabuladores
		//El primer elemento es el nombre de la empresa
		getline(tokenizer, aux, '\t');
		//Si no es la empresa introducida pasamos a la siguiente línea
		if (nombreEmpresa != aux) continue;
		//El segundo elemento es la contraseña
		getline(tokenizer, aux, '\t');
		while (flagContrasenia > 0) {
			//Pedimos la contraseña y comproabmos si coincide, usamos flagContrasenia para dar 3 intentos
			cout << "Introduce la contrasenia: ";
			cin >> contrasenia;
			if (contrasenia == aux) flagContrasenia = -1;
			else flagContrasenia--;
		}
		//Si fallan 3 veces no hacemos login
		if (flagContrasenia == 0) {
			Fichero.close();
			cout << "Demasiados intentos fallidos" << endl;
			login = false;
			return e;
		}
		//El tercer elemento es el dinero de la empresa, tiene que ser un número real
		getline(tokenizer, aux, '\t');
		try {
			dinero = stod(aux);
		}
		catch (...) {
			Fichero.close();
			cout << "Fichero empresa.txt con formato incorrecto. No se ha podido hacer login" << endl;
			login = false;
			return e;
		}
		//El cuarto elemento es el margen de ventas, tiene que ser un número real
		getline(tokenizer, aux, '\t');
		try {
			margen = stod(aux);
		}
		catch (...) {
			Fichero.close();
			cout << "Fichero empresa.txt con formato incorrecto. No se ha podido hacer login" << endl;
			login = false;
			return e;
		}
		//Inicializamos el objeto Empresa con los datos
		try {
			e = Empresa(nombreEmpresa, dinero, margen, nombreEmpresa + "_movimientos.txt", nombreEmpresa + "_inventario.txt");
		}
		catch (runtime_error& err) {
			cout << "No se ha podido hacer login, error al cargar la empresa. " << err.what() << endl;
			login = false;
			e = Empresa();
			return e;
		}
		Fichero.close();
		//Establecemos que se ha hecho login y devolvemos la empresa
		login = true;
		return e;
	}
	Fichero.close();
	//Si el nombre de la empresa no se encuentra en el fichero, la empresa no está registrada y ofecemos registrarla
	cout << "La empresa " + nombreEmpresa + " no esta registrada. Quieres registrarla? S/N: ";
	while (flagEntrada) {
		cin >> entrada;
		//Si quieren registrarla llamamos a la función registrar
		if (entrada == "S") {
			try {
				e = registrar(login, nombreEmpresa);
			}
			catch (runtime_error& err) {
				cout << "Error al registrar la empresa." << err.what() << endl;
				login = false;
				e = Empresa();
				return e;
			}
			catch (FileException& err) {
				cout << "Error al Abrir el fichero de empresas, no se pudo hacer el registro." << endl;
				login = false;
				e = Empresa();
				return e;
			}
			flagEntrada = 0;
		}
		//Si no, no hacemos login
		else if (entrada == "N") {
			cout << "No se ha hecho login";
			login = false;
			flagEntrada = 0;
		}
		else {
			cout << "Respuesta no reconocida, introduce solo S/N: ";
		}
	}
	return e;
}

//Función que guarda todos los datos de la empresa loggeada en los ficheros correspondientes
//Parámetro e: empresa con sesión abierta
void guardar(Empresa e) {
	int i;
	vector<string> datosAux = {};
	string linea, lineaEmpresa, aux, contrasenia;
	//Guardamos el margen y el dinero que pueden haber cambiado en el fichero "empresas.txt"
	ifstream Fichero("empresas.txt");
	if (!Fichero) {
		cout << "Error al abrir el fichero empresas.txt. No se han podido guardar los datos" << endl;
		return;
	}
	//leemos el fichero entero y guardamos los datos en un array auxiliar datosAux
	while (getline(Fichero, linea)) {
		stringstream tokenizer(linea);
		getline(tokenizer, aux, '\t');
		if (e.getNombre() != aux) {
			datosAux.push_back(linea);
			continue;
		}
		//Cuando leamos la línea correspondiente a la empresa loggeada modificamos los datos en datosAux
		getline(tokenizer, aux, '\t');
		contrasenia = aux;
		lineaEmpresa = e.getNombre() + "\t" + contrasenia + "\t" + to_string(e.getDinero()) + "\t" + to_string(e.getMargen());
		datosAux.push_back(lineaEmpresa);
	}
	Fichero.close();

	//Eliminamos el fichero y lo reescribimos de 0 con los datos de datosAux
	remove("empresas.txt");
	ofstream FicheroSalida("empresas.txt");
	if (!FicheroSalida) {
		cout << "Error al abrir el fichero empresas.txt. No se han podido guardar los datos" << endl;
		return;
	}
	for (i = 0; i < datosAux.size(); i++)
		FicheroSalida << datosAux[i] << endl;
	FicheroSalida.close();

	//Para guardar el inventario y los movimientos llamamos al método guardar de Empresa.
	//El fichero de movimientos es siempre "<nombreEmpresa>_movimientos.txt"
	//El fichero de inventario es siempre "<nombreEmpresa>_inventario.txt"
	try {
		e.guardar(e.getNombre() + "_movimientos.txt", e.getNombre() + "_inventario.txt");
	}
	catch (FileException& err) {
		throw FileException(err);
	}
	cout << "Datos guardados" << endl;
}

//Función para cerrar sesión de una empresa
//Parámetro e: empresa con sesión abierta pasada por referencia
//Return: bool 0 si se cierra la sesión, 1 si no se puede cerrar
bool logOut(Empresa& e) {
	int flagEntrada = 1, flagEntrada2 = 1;
	string entrada, errMsg;
	//Avisamos al usuario de que guarde antes de cerrar sesión
	cout << "Si no guarda el estado de la empresa antes de salir todos los cambios en el inventario y los movimientos realizados en esta sesion desde el ultimo guardado se perderan" << endl;
	cout << "Desea guardar el estado de la empresa antes de salir? S/N: ";
	while (flagEntrada) {
		cin >> entrada;
		//Si quieren guardar llamamos a la función guardar
		if (entrada == "S") {
			try {
				guardar(e);
			}
			//Si hay algún problema al guardar preguntamos si quieren salir de todos modos
			catch (FileException& err) {
				errMsg = err.what();
				cout << "Ha habido un error al guardar los datos: " + errMsg << endl;
				cout << "No se han podido guardar los datos, desea cerrar sesion de todos modos? S/N";
				while (flagEntrada2) {
					cin >> entrada;
					if (entrada == "S") 
						flagEntrada2 = 0;
					else if (entrada == "N") 
						return 1;
					else 
						cout << "Respuesta no reconocida, introduce solo S/N";
				}
			}
			flagEntrada = 0;
		}
		//Si no quieren guardar salimos directamente
		else if (entrada == "N") {
			cout << "No se han guardado los datos" << endl;
			flagEntrada = 0;
		}
		else
			cout << "Respuesta no reconocida, introduce solo S/N";
	}
	cout << "Cerrando sesion" << endl;
	//Vaciamos la empresa
	e = Empresa();
	return 0;
}

//Función para comprar items
//Parámetro e: empresa con sesión abierta pasada por referencia
void comprar(Empresa& e) {
	int flagEntrada1 = 1, flagEntrada2 = 1, ret, cantidad;
	double valor;
	string entrada, nombreItem, proveedor;
	//Pedimos el item y el proveedor al que quieren comprar
	cout << "Que item quieres comprar? ";
	cin >> nombreItem;
	cout << "Como se llama el proveedor? ";
	cin >> proveedor;
	//Pedimos la cantidad que quieren comprar, tiene que ser un entero
	while (flagEntrada1) {
		cout << "Que cantidad quieres comprar? ";
		cin >> entrada;
		try {
			cantidad = stoi(entrada);
			flagEntrada1 = 0;
		}
		catch (...) {
			cout << "El valor introducido debe ser un numero entero";
		}
	}
	flagEntrada1 = 1;
	
	//Realizamos la compra con comprarItem
	try {
		ret = e.comprarItem(nombreItem, cantidad, proveedor);
	}
	catch (LogicException& err) {
		cout << err.what();
		return;
	}
	//Compra exitosa
	if (ret == 1)
		cout << nombreItem + " comprado con exito" << endl;
	//No hay dinero
	else if (ret == 0)
		cout << "No hay suficiente dinero, aumenta los fondos o vende items antes de realizar esta compra";
	//Si el item no existe en el inventario preguntamos si lo quieren añadir
	else {
		cout << "El item no esta en el inventario. Quieres aniadirlo? S/N";
		while (flagEntrada1) {
			cin >> entrada;
			//Si lo quieren añadir preguntamos cuanto cuesta el item, tiene que ser un número real
			if (entrada == "S") {
				cout << "Cuanto vale el item?";
				while (flagEntrada2) {
					cin >> entrada;
					try {
						valor = stod(entrada);
						flagEntrada2 = 0;
					}
					catch (...) {
						cout << "El valor introducido debe ser un numero real";
					}
				}
				//Realizamos la compra con comprarItem
				try {
					ret = e.comprarItem(nombreItem, valor, cantidad, proveedor);
				}
				catch (LogicException& err) {
					cout << err.what();
					return;
				}
				//Compra exitosa
				if (ret == 1)
					cout << nombreItem + " comprado con exito" << endl;
				//No hay dinero
				else
					cout << "No hay suficiente dinero, aumenta los fondos o vende items antes de realizar esta compra";
				return;
			}
			//No quieren añadir el item
			else if (entrada == "N") {
				cout << "La compra no se ha realizado";
				flagEntrada1 = 0;
			}
			else {
				cout << "Respuesta no reconocida, introduce solo S/N";
			}
		}
	}
}

//Función para vender items
//Parámetro e: empresa con sesión abierta pasada por referencia
void vender(Empresa& e) {
	int cantidad, flagEntrada = 1;
	string nombreItem, entrada;
	//Preguntamos qué item quieren vender
	cout << "Que item quieres vender? ";
	cin >> nombreItem;
	//Preguntamos la cantidad que quieren vender, tiene que ser un entero
	while (flagEntrada) {
		cout << "Que cantidad quieres vender? ";
		cin >> entrada;
		try {
			cantidad = stoi(entrada);
			flagEntrada = 0;
		}
		catch (...) {
			cout << "El valor introducido debe ser un numero entero" << endl;
		}
	}
	//Realizamos la venta con venderItem
	if (e.venderItem(nombreItem, cantidad))
		//Venta exitosa
		cout << nombreItem + " vendido con exito" << endl;
	else
		//No hay bastantes items
		cout << "No hay suficientes items del tipo " + nombreItem + " debes comprar mas para poder vender esta cantidad";
}

//Función para añadir dinero a la empresa
//Parámetro e: empresa con sesión abierta pasada por referencia
void aniadirDinero(Empresa& e) {
	int flagEntrada = 1;
	double dinero;
	string entrada;
	while (flagEntrada) {
		//Preguntamos cuanto quieren añadir, tiene que ser un número real
		cout << "Cuanto dinero quieres aniadir? ";
		cin >> entrada;
		try {
			dinero = stod(entrada);
			flagEntrada = 0;
		}
		catch (...) {
			cout << "El valor introducido debe ser un numero real" << endl;
		}
	}
	//Añadimos el dinero con el setter de dinero
	e.setDinero(e.getDinero() + dinero);
	cout << "Dinero aniadido con exito" << endl;
}

//Función para cambiar el margen de ventas de la empresa
//Parámetro e: empresa con sesión abierta pasada por referencia
void cambiarMargen(Empresa &e) {
	int flagEntrada = 1;
	double margen;
	string entrada;
	while (flagEntrada) {
		//Preguntamos el nuevo margen, tiene que ser un número real
		cout << "Cual quieres que sea el nuevo margen? ";
		cin >> entrada;
		try {
			margen = stod(entrada);
			flagEntrada = 0;
		}
		catch (...) {
			cout << "El valor introducido debe ser un numero real" << endl;
		}
	}
	//Cambiamos el margen con el setter de margen
	e.setMargen(margen);
	cout << "Margen modificado con exito" << endl;
}

//Función principal de interfaz
void interfaz() {
	bool login = false;
	string entrada, errMsg;
	Empresa e;
	char dinero[128];
	//Imprimimos las opciones inicales del usuario
	opciones(login);
	//Hasta que se salga del programa con la opción <Salir>
	while (true) {
		//Leemos la entrada
		cin >> entrada;
		//Ponemos el terminal en blanco para que no se llene de texto
		system("cls");
		cout << entrada << endl;
		//LOGIN
		if (entrada == "Login" && login == true)
			cout << "La opcion <Login> solo esta disponible cuando no hay sesion iniciada" << endl;
		else if (entrada == "Login" && login == false) {
			//Hacemos llogin e imprimimos las opciones
			e = logIn(login);
			opciones(login);
		}
		//SALIR
		else if (entrada == "Salir" && login == true) {
			//Si estan logeados, se hace logout y se sale del programa
			login = logOut(e);
			cout << "Cerrando el programa" << endl;
			return;
		}
		else if (entrada == "Salir" && login == false) {
			//Si no estan logeados se sale directamente
			cout << "Cerrando el programa" << endl;
			return;
		}
		//COMPRAR
		else if (entrada == "Comprar" && login == true)
			//Llamamos a Comprar
			comprar(e);
		else if (entrada == "Comprar" && login == false)
			cout << "La opcion <Comprar> solo esta disponible cuando la sesion esta iniciada" << endl;
		//VENDER
		else if (entrada == "Vender" && login == true)
			//Llamamos a vender
			vender(e);
		else if (entrada == "Vender" && login == false)
			cout << "La opcion <Vender> solo esta disponible cuando la sesion esta iniciada" << endl;
		//AÑADIR DINERO
		else if (entrada == "AddEfectivo" && login == true)
			//Llamamos a aniadirDinero
			aniadirDinero(e);
		else if (entrada == "AddEfectivo" && login == false)
			cout << "La opcion <AddEfectivo> solo esta disponible cuando la sesion esta iniciada" << endl;
		//CAMBIAR MARGEN
		else if (entrada == "CambiarMargen" && login == true)
			//Llamamos a cambiarMargen
			cambiarMargen(e);
		else if (entrada == "CambiarMargen" && login == false)
			cout << "La opcion <CambiarMargen> solo esta disponible cuando la sesion esta iniciada" << endl;
		//CONSULTAR DINERO
		else if (entrada == "Efectivo" && login == true) {
			//Imprimimos el dinero de la empresa con 2 cifras decimales
			sprintf_s(dinero, 128, "%.2f", e.getDinero());
			cout << "Efectivo actual: " << dinero << "$" << endl;
		}
		else if (entrada == "Efectivo" && login == false)
			cout << "La opcion <Efectivo> solo esta disponible cuando la sesion esta iniciada" << endl;
		//CONSULTAR MARGEN
		else if (entrada == "Margen" && login == true)
			//Imprimimos el margen de ventas de la empresa
			cout << "Margen de ventas actual: " << e.getMargen() << endl;
		else if (entrada == "Margen" && login == false)
			cout << "La opcion <Margen> solo esta disponible cuando la sesion esta iniciada" << endl;
		else if (entrada == "Inventario" && login == true)
			e.consultarInventario();
		else if (entrada == "Inventario" && login == false)
			cout << "La opcion <Inventario> solo esta disponible cuando la sesion esta iniciada" << endl;
		//CONSULTAR MOVIMIENTOS
		else if (entrada == "Movimientos" && login == true)
			//Imprimimos los movimientos con el método consultarMovimientos de Empresa
			e.consultarMovimientos();
		else if (entrada == "Movimientos" && login == false)
			cout << "La opcion <Movimientos> solo esta disponible cuando la sesion esta iniciada" << endl;
		//GUARDAR
		else if (entrada == "Guardar" && login == true) {
			//Llamamos a guardar
			try {
				guardar(e);
			}
			catch (FileException& err) {
				errMsg = err.what();
				cout << "Ha habido un error al guardar los datos: " + errMsg << endl;
			}
		}
		else if (entrada == "Guardar" && login == false)
			cout << "La opcion <Guardar> solo esta disponible cuando la sesion esta iniciada" << endl;
		//CERRAR SESIÓN
		else if (entrada == "Logout" && login == true) {
			//Llamamos a logOut e imprimimos las opciones
			login = logOut(e);
			opciones(login);
		}
		else if (entrada == "Logout" && login == false)
			cout << "La opcion <Logout> solo esta disponible cuando la sesion esta iniciada" << endl;
		//OPCIONES
		else if (entrada == "Opciones")
			//Imprimimos las opciones
			opciones(login);
		//El comando introducido no existe
		else
			cout << "La instruccion seleccionada no existe" << endl;
	}
}