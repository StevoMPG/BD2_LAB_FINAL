#include <iostream>
#include <mysql.h>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

char serverdb[] = "localhost";
char userdb[] = "root";
char passworddb[] = "adsl0496";
char database[] = "vehiculo";


void agregar() {

	MYSQL* connection;
	string vin;
	string marca;
	string modelo;
	string fecha_fab;
	string precio;
	string sql;
	const char* query;
	MYSQL_ROW rows;
	MYSQL_RES* r;
	int res;
	int result;
	connection = mysql_init(0);
	if (connection)
	{
		cout << "\nLa biblioteca MySQL se ha iniciado correctamente\n" << endl;
		system("cls");
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		if (connection)
		{
			cout << "Conexion exitosa a la base de datos!\n\n" << endl;
			cout << "Ingrese el vin del auto: ";
			cin >> vin;
			cout << "\n" << endl;
			sql = "SELECT * FROM auto WHERE vin = ('" + vin + "')";
			query = sql.c_str();
			res = mysql_query(connection, query);
		
			if (!res) {
				r = mysql_store_result(connection);
				if ((rows = mysql_fetch_row(r))) {

					cout << "| vin |        | Marca |        | Modelo |        | Fecha_fab |        | Precio |" << endl;
					cout <<   rows[0] << "               " << rows[1] << "            " << rows[2] << "           " << rows[3] << "           " << rows[4] << endl << endl;

					cout << "\nERROR!!! Ya existe un registro con ese vin, pruebe con otro valor!\n\n";
				}
				else
				{
					cout << "Ingrese marca del auto: ";
					cin >> marca;
					cout << "Ingrese el modelo del auto: ";
					cin >> modelo;
					cout << "Ingrese la fecha de fabricacion del auto: ";
					cin >> fecha_fab;
					cout << "Ingrese el precio del auto: ";
					cin >> precio;

					sql = "INSERT INTO auto(vin, marca, modelo, fecha_fab, precio) VALUES ('" + vin + "','" + marca + "', '" + modelo + "', '" + fecha_fab + "','" + precio + "')";
					query = sql.c_str();
					result = mysql_query(connection, query);

					if (result == 0)
					{
						cout << "\nRegistro guardado correctamente!\n" << endl;
					}
					else
					{
						cout << "\nERROR!!! No fue posible agregar el registro!\n" << mysql_error(connection) << endl;
					}
				}
			}
		}
		else
		{
			cout << "\nERROR!!! No fue posible conectarse a la base de datos: " << mysql_error(connection) << endl;
		}
	}
	else
	{
		cout << "\nERROR!!! No es posible iniciar la biblioteca de MySQL" << endl;
	}
}


void buscar() {

	MYSQL* connection;
	string sql;
	string vin;
	MYSQL_ROW rows;
	MYSQL_RES* r;
	int res;
	const char* query;
	connection = mysql_init(0);

	if (connection)
	{
		cout << "\nLa biblioteca MySQL se ha iniciado correctamente\n" << endl;
		system("cls");
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		if (connection)
		{
			cout << "Conexion exitosa a la base de datos!\n\n" << endl;
			cout << "Ingrese el vin del auto que deseas buscar: ";
			cin >> vin;
			cout << "\n" << endl;
			sql = "SELECT * FROM auto WHERE vin = ('" + vin + "')";
			query = sql.c_str();
			res = mysql_query(connection, query);

			if (!res) {
				r = mysql_store_result(connection);
				if ((rows = mysql_fetch_row(r))) {

					cout << "|vin |\t\t| Marca |\t| Modelo |\t| Fecha_fab |\t\t| Precio |" << endl;
					cout << rows[0] << "\t\t  " << rows[1] << "\t\t  " << rows[2] << "\t\t" << rows[3] << "\t\t  " << rows[4] << endl;

					cout << "\n\n\n";
				}
				else
				{
					cout << "\nERROR!!! No existe un registro con ese vin!\n" << endl;
				}
			}
		}
		else
		{
			cout << "\nERROR!!!No fue posible conectarse a la base de datos:  " << mysql_error(connection) << endl;
		}
	}
	else
	{
		cout << "\nERROR!!! No es posible iniciar la biblioteca de MySQL" << endl;
	}
}


void eliminar() {

	MYSQL* connection;
	string sql;
	string vin;
	MYSQL_ROW rows;
	MYSQL_RES* r;
	int res;
	const char* query;
	int result;
	connection = mysql_init(0);
	if (connection)
	{
		cout << "\nLa biblioteca MySQL se ha iniciado correctamente\n" << endl;
		system("cls");
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		if (connection)
		{
			cout << "Conexion exitosa a la base de datos!\n\n" << endl;
			cout << "Ingrese el vin del auto que deseas eliminar: ";
			cin >> vin;
			cout << "\n" << endl;
			sql = "SELECT * FROM auto WHERE vin = ('" + vin + "')";
			query = sql.c_str();
			res = mysql_query(connection, query);

			if (!res) {
				r = mysql_store_result(connection);
				if ((rows = mysql_fetch_row(r))) {

					cout << "|vin |\t\t| Marca |\t| Modelo |\t| Fecha_fab |\t\t| Precio |" << endl;
					cout << rows[0] << "\t\t  " << rows[1] << "\t\t  " << rows[2] << "\t\t" << rows[3] << "\t\t  " << rows[4] << endl;

					cout << "\n\n\n";

					char respuesta;
					cout << "Estas seguro que quieres eliminar este registro? [S/N]: ";
					cin >> respuesta;
					if ((respuesta == 's') || (respuesta == 'S'))
					{
						sql = "DELETE FROM auto WHERE vin = ('" + vin + "')";
						query = sql.c_str();
						result = mysql_query(connection, query);
						if (result == 0)
						{
							cout << "\nSe ha eliminado el registro de forma exitosa!\n" << endl;
							cout << endl;
						}
					}
					else
					{
						cout << "\nNo se ha querido eliminar el registro!\n" << endl;
					}
				}
				else
				{
					cout << "\nERROR!!! No existe un registro con ese vin!\n" << endl;
				}
			}
		}
		else
		{
			cout << "\nERROR!!! No fue posible conectarse a la base de datos: " << mysql_error(connection) << endl;
		}
	}
	else
	{
		cout << "\nERROR!!! No es posible iniciar la biblioteca de MySQL" << endl;
	}
}




void modificar() {

	MYSQL* connection;
	string vin;
	string marca;
	string modelo;
	string fecha_fab;
	string precio;
	string sql;
	int i, j, k, l;
	unsigned long* lon;
	MYSQL_ROW rows;
	MYSQL_RES* r;
	int res;
	const char* query;
	int result;
	connection = mysql_init(0);

	if (connection)
	{
		cout << "\nLa biblioteca MySQL se ha iniciado correctamente\n" << endl;
		system("cls");
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		if (connection)
		{
			cout << "Conexion exitosa a la base de datos!\n\n" << endl;
			cout << "Ingrese el vin del auto que deseas modificar sus datos: ";
			cin >> vin;
			cout << "\n" << endl;
			sql = "SELECT * FROM auto WHERE vin = ('" + vin + "')";
			query = sql.c_str();
			res = mysql_query(connection, query);

			if (!res) {
				r = mysql_store_result(connection);
				if ((rows = mysql_fetch_row(r))) {

					cout << "|vin |\t\t| Marca |\t| Modelo |\t| Fecha_fab |\t\t| Precio |" << endl;
					cout << rows[0] << "\t\t  " << rows[1] << "\t\t  " << rows[2] << "\t\t" << rows[3] << "\t\t  " << rows[4] << endl;

					cout << "\n\n\n";

					char respuesta;
					cout << "Estas seguro que quieres modificar este registro? [S/N]: ";
					cin >> respuesta;
					if ((respuesta == 's') || (respuesta == 'S'))
					{

						cout << "\nIngrese la nueva marca del auto: ";
						cin >> marca;
						cout << "\nIngrese el nuevo modelo del auto: ";
						cin >> modelo;
						cout << "\nIngrese la nueva fecha de fabricacion del auto (FORMATO AAAA-MM-DD): ";
						cin >> fecha_fab;
						cout << "\nIngrese el nuevo precio del auto (EN NUMERO): ";
						cin >> precio;
						MYSQL_ROW row;
						MYSQL_RES* data;
						sql = "UPDATE auto SET marca = ('" + marca + "'), modelo = ('" + modelo + "'), fecha_fab = ('" + fecha_fab + "'), precio = ('" + precio + "') WHERE vin = ('" + vin + "')";
						query = sql.c_str();
						result = mysql_query(connection, query);
						if (result == 0)
						{
							cout << "\nSe han modificado los datos de forma exitosa!\n" << endl;
							if ((data = mysql_store_result(connection))) {
								i = (int)mysql_num_rows(data);
								j = (int)mysql_num_fields(data);
								cout << endl << "" << endl;
								l = 1;
								for (l = 0; l < i; l++) {
									row = mysql_fetch_row(data);
									lon = mysql_fetch_lengths(data);
									cout << endl;
									for (k = 0; k < j; k++) {
									}
									cout << endl;
								}
							}
						}
						else
						{
							cout << "\nERROR!!! No se pudo realizar la modificacion" << mysql_error(connection) << endl;
						}
					}
					else
					{
						cout << "\nNo se ha querido modificar el registro!\n" << endl;
					}
				}
				else
				{
					cout << "\nERROR!!! No existe un registro con ese vin!\n" << endl;
				}
			}
		}
		else
		{
			cout << "\nERROR!!! No fue posible conectarse a la base de datos: " << mysql_error(connection) << endl;
		}
	}
	else
	{
		cout << "\nERROR!!! No es posible iniciar la biblioteca de MySQL" << endl;
	}
}


void mostrar() {
	MYSQL* connection;

	string sql;
	int i, j, k, l;
	unsigned long* lon;

	const char* query;
	int result;
	connection = mysql_init(0);
	if (connection)
	{
		cout << "\nLa biblioteca MySQL se ha iniciado correctamente\n" << endl;
		system("cls");
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		if (connection)
		{
			cout << "Conexion exitosa a la base de datos!\n\n" << endl;
			
			MYSQL_ROW row;
			MYSQL_RES* data;
			sql = "SELECT * FROM auto";
			query = sql.c_str();
			result = mysql_query(connection, query);
			if (result == 0)
			{
				cout << "Se han obtenido los datos de la tabla de forma exitosa:\n\n " << endl;
				cout << "|vin |\t\t| Marca |\t| Modelo |\t| Fecha_fab |\t\t| Precio |" << endl;
				if ((data = mysql_store_result(connection))) {
					i = (int)mysql_num_rows(data);
					j = (int)mysql_num_fields(data);
					cout << endl << "" << endl;
					l = 1;
					for (l = 0; l < i; l++) {
						row = mysql_fetch_row(data);
						lon = mysql_fetch_lengths(data);
						cout << endl;
						for (k = 0; k < j; k++) {
							cout << "" << ((row[k] == NULL) ? "NULL" : row[k]) << "\t\t";
						}
						cout << endl;
					}
				}
				else
				{
					cout << "\nERROR!!! No fue posible obtener los registros " << mysql_error(connection) << endl;
				}
			}
			else
			{
				cout << "\nERROR!!! No fue posible conectarse a la base de datos: " << mysql_error(connection) << endl;
			}
		}
		else
		{
			cout << "\nERROR!!! No es posible iniciar la biblioteca de MySQL" << endl;
		}
	}
}


int main() {

	int eleccion = 0;
	do {
		system("cls");

		cout << "***** STEVEN PEREIRA - BD2 - LAB03 *****\n" << endl;

		cout << "****************************************\n" << endl;
		cout << "*****              MENU            *****" << endl;
		cout << "***** 1 .- INGRESAR NUEVO AUTO     *****" << endl;
		cout << "***** 2 .- ELIMINAR DATOS AUTO     *****" << endl;
		cout << "***** 3 .- MODIFICAR DATOS AUTO    *****" << endl;
		cout << "***** 4 .- CONSULTAR DATOS AUTO    *****" << endl;
		cout << "***** 5 .- LISTAR DATOS AUTOS      *****" << endl;
		cout << "***** 6 .- SALIR                   *****\n" << endl;
		cout << "****************************************" << endl;

		cout << "\nELIJA UNA OPCION: ";
		cin >> eleccion;

		switch (eleccion) {
		case 1: agregar();
			system("pause");
			break;

		case 2: eliminar();
			system("pause");
			break;

		case 3: modificar();
			system("pause");
			break;

		case 4: buscar();
			system("pause");
			break;

		case 5: mostrar();
			system("pause");
			break;

		case 6:
			cout << "\nSaliendo de la aplicacion, gracias por utilizarla! Hasta la proxima...\n\n";
			system("pause");
			break;

		default:
			cout << "\nOpcion invalida, pruebe a elegir un valor correcto de los que se indican en pantalla!\n"; system("pause");
			break;
		}
	} while (eleccion != 6);
	system("cls");
	return 0;
}

