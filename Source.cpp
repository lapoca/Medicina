#include <iostream>
#include <wchar.h>
#include <locale.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
using namespace std;
class Menu
{
private:
	char Nombre[30];
	char NombreMed[30];
	char Horario[20];

public:
	void Menuprincipal();
	void setDatos();
	void clearDatos();
	void listarDatos();
	void mostrarInfo();

};
static void error()
{
	cout << "Error al abrir el archivo" << endl;
}
void Menu::Menuprincipal()
{
	setlocale(LC_CTYPE, "spanish");
	int opc{};
	do
	{
		fflush(stdin);
		system("cls");
		cout << "\t\t\t***Menú principal***\t\t\t\n" << endl;
		cout << "1. Ingresar datos" << endl;
		cout << "2. Borrar Datos" << endl;
		cout << "3. Listar Datos" << endl;
		cout << "4. Mostrar detalles" << endl;
		cout << "5. Salir" << endl;
		cout << "Ingrese una opcion: ";
		cin >> opc;
		switch (opc)
		{
		case 1:
			setDatos();
			break;
		case 2:
			clearDatos();
			break;
		case 3:
			listarDatos();
			break;
		case 4:
			mostrarInfo();
			break;
		case 5:
			cout << "Saliendo..." << endl;
			break;
		default:
			do
			{
				cout << "Opcion no valida" << endl;
				cout << "Ingrese una opción valida" << endl;
				cin >> opc;
				system("pause");
				break;
			} while (opc <= 0 || opc > 5);
		}
	} while (opc != 5);
}
void Menu::setDatos()
{
	setlocale(LC_CTYPE, "spanish");
	//Declaración de variables
	ofstream escritura;
	ifstream verificador;
	char auxcode[30];
	bool encontrado = false;
	verificador.open("Medicinas.txt", ios::in);
	escritura.open("Medicinas.txt", ios::app);
	if (escritura.is_open() && verificador.is_open())
	{
		system("cls");
		cout << "\t\t\t***Ingreso de datos***\t\t\t\n" << endl;
		fflush(stdin);
		cout << "Ingrese el nombre del paciente: ";
		cin.getline(auxcode, 30) >> auxcode;
		if (strcmp(auxcode, "") == 0) {
			do
			{
				cout << "\nEl campo no puede estar vacio, inténtalo de nuevo: " << endl;
				cin.getline(auxcode, 30) >> auxcode;
			} while (strcmp(auxcode, "") == 0);
		}
		system("cls");
		strcpy_s(Nombre, auxcode);
		cout << "\t\t\t***Ingreso de datos***\t\t\t\n" << endl;
		cout << "Ingrese el nombre del paciente: ";
		cout << Nombre << endl;
		cout << "\n";
		fflush(stdin);
		cout << "Ingrese el nombre del medicamento: ";
		cin.getline(NombreMed, 30) >> NombreMed;
		cout << "\n";
		fflush(stdin);
		cout << "Ingrese el horario para tomar el medicamento: ";
		cin.getline(Horario, 20) >> Horario;
		cout << "\n";
		escritura << Nombre << "\n" << NombreMed << "\n" << Horario << endl;
		cout << "Datos guardados" << endl;
	}
	else
	{
		error();
	}
	escritura.close();
	verificador.close();
	system("pause");
}
void Menu::clearDatos() {
	setlocale(LC_CTYPE, "spanish");
	ifstream lectura;
	ofstream auxiliar;
	bool encontrado = false;
	char auxcode[30];
	char opc[5];
	lectura.open("Medicinas.txt", ios::in);
	auxiliar.open("auxiliar.txt", ios::out);
	system("cls");
	cout << "\t\t\t***Borrar datos***\t\t\t\n" << endl;
	if (lectura.is_open() && auxiliar.is_open()) {
		fflush(stdin);
		cout << "Ingrese el nombre del paciente: (Con espacios y Mayúsculas) ";
		cin.getline(auxcode, 30) >> auxcode;
		lectura >> Nombre;
		while (!lectura.eof()) {
			lectura >> NombreMed >> Horario;
			if (strcmp(auxcode, Nombre) == 0) {
				encontrado = true;
				cout << "\nRegistro encontrado" << endl;
				cout << "Nombre del paciente: " << Nombre << endl;
				cout << "Nombre del medicamento: " << NombreMed << endl;
				cout << "Horario para tomar el medicamento: " << Horario << endl;
				cout << "\n";
				cout << "¿Desea borrar el registro de " << Nombre << "? (S/N): ";
				cin.getline(opc, 5) >> opc;
				if (strcmp(opc, "s") == 0 || strcmp(opc, "S") == 0 || strcmp(opc, "si") == 0 || strcmp(opc, "Si") == 0 || strcmp(opc, "SI") == 0 || strcmp(opc, "sI") == 0) {
					cout << "Registro borrado correctamente" << endl;
				}
				else {
					cout << "\nRegistro conservado" << endl;
					auxiliar << Nombre << "\n" << NombreMed << "\n" << Horario << endl;
				}
			}
			else {
				auxiliar << Nombre << "\n" << NombreMed << "\n" << Horario << endl;
			}
			lectura >> Nombre;
		}
		if (encontrado == false) {
			cout << "No se encontraron registros" << auxcode << endl;
		}
	}
	else {
		error();
	}
	lectura.close();
	auxiliar.close();
	remove("Medicinas.txt");
	rename("auxiliar.txt", "Medicinas.txt");
	system("pause");
}
void Menu::listarDatos() {
	int i = 0;
	setlocale(LC_CTYPE, "spanish");
	ifstream lectura;
	lectura.open("Medicinas.txt", ios::in);
	if (lectura.is_open()) {
		system("cls");
		cout << "\t\t\t***Listado de datos***\t\t\t\n" << endl;
		lectura >> Nombre;
		while (!lectura.eof()) {
			i++;
			lectura >> NombreMed >> Horario;
			cout << "Nombre del paciente: " << Nombre << endl;
			cout << "Nombre del medicamento: " << NombreMed << endl;
			cout << "Horario para tomar el medicamento: " << Horario << endl;
			cout << "\n";
			lectura >> Nombre;
		}
		if (i == 1) {
			cout << "Solo hay un registro de medicina" << endl;
		}
		else {
			cout << "Hay " << i << " registros de medicina" << endl;
		}
	}
	else {
		error();
	}
	lectura.close();
	system("pause");
}
void Menu::mostrarInfo() {
	setlocale(LC_CTYPE, "spanish");
	char auxcode[30];
	ifstream mostrar;
	bool encontrado = false;
	mostrar.open("Medicinas.txt", ios::in);
	if (mostrar.is_open()) {
		system("cls");
		fflush(stdin);
		cout << "\t\t\t***Mostrar detalles***\t\t\t\n" << endl;
		cout << "Ingrese el nombre del paciente: ";
		cin.getline(auxcode, 30) >> auxcode;
		mostrar >> Nombre;
		while (!mostrar.eof()) {
			mostrar >> NombreMed >> Horario;
			if (strcmp(auxcode, Nombre) == 0) {
				encontrado = true;
				cout << "Nombre del paciente: " << Nombre << endl;
				cout << "Nombre del medicamento: " << NombreMed << endl;
				cout << "Horario para tomar el medicamento: " << Horario << endl;
				cout << "\n";
			}
			mostrar >> Nombre;
		}
		if (encontrado == false) {
			cout << "No se encontraron registros con el nombre de " << auxcode << endl;
		}
	}
	else {
		error();
	}
	mostrar.close();
	system("pause");
}
void comprobarArchivo()
{
	setlocale(LC_CTYPE, "spanish");
	ifstream archivo;
	archivo.open("Medicinas.txt", ios::in);
	if (!archivo.is_open())
	{
		cout << "¡No se pudo abrir el archivo de registros o aún no se ha registrado ningun cliente!";
		cout << "\n\n";
		cout << "Para crear el archivo de registros selecciona la opcion de dar de alta un cliente.";
		cout << "\n";
		system("pause");
		system("cls");
	}
}
int main()
{
	system("color 0f");
	Menu inicio{};
	comprobarArchivo();
	inicio.Menuprincipal();
	return 0;
}
