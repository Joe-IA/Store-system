//Inclusi�n de librerias
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
//#include <locale.h>
#include <windows.h>
#include <fstream>
using namespace std;

struct Empleado{
	string Nombre, NombreUs,  FechaNac, Direccion, Contrasenha, tipoUs = "Empleado";
	char Sexo;
	
	void cambiarCon(string con){
		Contrasenha = con;
	}
};

struct Cliente{
	
	string Nombre, NombreUs,  FechaNac, Direccion, Contrasenha, tipoUs = "Cliente";
	char Sexo;
	vector<int> cart = vector<int>(12,0);//Se inicia un vector de 12 posiciones con 0's en cada una de ellas
	
	
	//Declaraci�n de metodos para no crear funciones que tengan como parametro la instancia cliente
	void cambiarCon(string con){
		Contrasenha = con;
	}
	
	void Info(){
		cout << "Nombre: " << Nombre << endl;
		cout << "FechaNac: " << FechaNac << endl;
		cout << "Sexo: " << Sexo << endl;
		cout << "Direcci�n: " << Direccion << endl;
		cout << "Tipo de usuario: " << tipoUs << endl;
	}
	
	void CambiarDir(){
		system("cls");
		string input;
		cout << "Ingrese su nueva direccion: ";
		fflush(stdin);
		getline(cin, input);
		Direccion = input;
		system("cls");
	}
	
	void CambiarUs(){
		system("cls");
		string input;
		cout << "Ingrese su nuevo nombre de usuario: ";
		fflush(stdin);
		getline(cin, input);
		NombreUs = input;
		system("cls");
	}
};


//Declaracion de funciones
int VerNombreE(string nombre, vector<Empleado> arr, bool &con);
bool VerConE(int ind, string con, vector<Empleado> arr);
bool verCon(string con);
string GenCon();
int VerNombreC(string nombre, vector<Cliente> arr, bool &con);
bool VerConC(int ind, string con, vector<Cliente> arr);
void nuevoMiembro(vector<Empleado>* empleado, vector<Cliente>* cliente);
void eliminarMiembro(vector<Empleado>* empleado, vector<Cliente>* cliente);
void InfoClientes(vector <Cliente> clientes);
string Newpass();
void carrito(int precios[], string productos[], vector<Cliente> clientes, int index,int ticket,int &descuento );
void comprar(vector<int> &db, int precios[], string productos[],vector<Cliente>* clientes, int index,int ticket,int &descuento) ;
void leerDBE(vector <Empleado> &empleados);
void leerDBC(vector <Cliente> &clientes);
void ImprimirDBE(vector<Empleado> empleados);
void ImprimirDBC(vector<Cliente> clientes);
void GuardTot(vector<int>Ventas,int precios[12],string productos[12],int descuento);

int main(){
	// Funciones para recibir e imprimir caracteres del espanhol
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	//setlocale(LC_ALL, "spanish");
	srand(unsigned(time(NULL)));
	
	
	char sel;
	int index, menu, cont,ticket,descuento=0;
	bool concorrect;
	string user, con, dir;
	
	//Iniclializacion de vectores
	
	vector<Cliente> clientes;
	vector<Empleado> empleados;
	vector<Cliente>* clientesPtr = &clientes;
	vector<Empleado>* empleadosPtr = &empleados;
	vector<int> Ventas(12, 0);
	string productos[12] = {"Mesa grande", "Mesa mediana", "Mesa peque�a", "Sill�n grande", "Sill�n mediano", "Sill�n chico", "Silla grande", "Silla mediana", "Silla chica", "Cama grande", "Cama mediana", "Cama peque�a"};
	int precios[12] = {        3000,           2400,              1600,         6750,              5740,            4300,        1500,              900,             790,          8900,       7000,             5600};

	//Inicializaci�n de usuario tipo cliente y empleado para la correcta inicializaci�n del programa
	Cliente cliente1;
	cliente1.Nombre = "Jose Armando Cerna"; cliente1.NombreUs = "JCerna29"; cliente1.FechaNac = "20 de abril de 2004"; cliente1.Sexo = 'H';
	cliente1.Direccion = "Calle Quinta Avenida 708"; cliente1.Contrasenha = "MiaOct17!"; 
	Empleado empleado1;
	empleado1.Nombre = "Jos� David Lam"; empleado1.NombreUs = "DavBJ"; empleado1.FechaNac = "5 de febrero de 2003"; empleado1.Sexo = 'H';
	empleado1.Direccion = "Av Aguascalientes 90"; empleado1.Contrasenha = "Guate_2003";
	clientes.push_back(cliente1);
	empleados.push_back(empleado1);

	
	while(true){//Inicio de sesi�n
		cont = 1;
		cout << "�Eres cliente o empleado? c/e: ";
		cin >> sel;
		fflush(stdin);
		if(sel != 'c' && sel!= 'e'){
			if(cin.fail()){
				cin.clear();
				fflush(stdin);
			}
			cout << "Opci�n inv�lida" << endl;
			Sleep(500); // Crea un apusa de 500 milisegundos (.5 segundos) antes de ejecutar la siguiente l�nea
			system("cls");
			continue;
		}
		Sleep(50);
		system("cls");
		cout << "Inicio de sesi�n" << endl << endl;
		cout << "Ingrese nombre de usuario: ";
		fflush(stdin);
		getline(cin, user);
		
		if(sel == 'e'){
			/*
			Verificaci�n de los datos de incio de sesi�n para usarios tipo empleado
			*/
			index = VerNombreE(user, empleados, concorrect);
			if(index >=0){
				do{
					cout << "Ingrese contrase�a: ";
					fflush(stdin);
					getline(cin, con);
					concorrect = VerConE(index, con, empleados);
					if(concorrect){
						system("cls");
						break;
					}
					cont ++;
				} while(cont <=3);
				if (cont > 3){//Generaci�n de nueva contrase�� despu�s de haber excedido el n�mero de intentos
					cout << "Ha excedido el n�mero de intentos..." << endl;
					cout << "Para restablecer su contrase�a ingrese su direcci�n: ";
					fflush(stdin);
					getline(cin, dir);
					if(empleados[index].Direccion == dir){
						empleados[index].cambiarCon(GenCon());
					}
					else{
						cout << "No concuerda la direcci�n con la registrada por el usuario " << empleados[index].NombreUs << endl;
						Sleep(1000);
						system("cls");
					}
				}
			}
		}
		//Verificaci�n de datos para inicio de sesi�n pero para usuario tipo cliente.
		else if(sel == 'c'){
			index = VerNombreC(user, clientes, concorrect);
			if(index >=0){
				do{
					cout << "Ingrese contrase�a: ";
					fflush(stdin);
					getline(cin, con);
					concorrect = VerConC(index, con, clientes);
					if(concorrect){
						ticket = 1+rand()%1700;
						system("cls");
						break;
					}
					cont ++;
				} while(cont <=3);
				if (cont > 3){
					cout << "Ha excedido el n�mero de intentos..." << endl;
					cout << "Para restablecer su contrase�a ingrese su direcci�n: ";
					fflush(stdin);
					getline(cin, dir);
					if(clientes[index].Direccion == dir){
						clientes[index].cambiarCon(GenCon());
					}
					else{
						cout << "No concuerda la direcci�n con la registrada por el usuario " << clientes[index].NombreUs << endl;
						Sleep(2500);
						system("cls");
					}
				}
			}
		}
		
		if(concorrect && sel == 'e'){//Menu empleado
			while(true){
				cout << "Usuario: " << empleados[index].Nombre << endl << endl;
				cout << "---Men�---" << endl;
				cout << "1. Dar de alta cliente/ empleado" << endl;
				cout << "2. Dar de baja cliente/empleado" << endl;
				cout << "3. Ver la lista de todos los clientes" << endl;
				cout << "4. Total de ventas realizadas y total de descuentos" << endl;
				cout  << "5. Cerrar sesi�n" << endl;
				cout << "6. Cargar base de datos clientes" << endl;
				cout << "7. Cargar base de datos empleados" << endl;
				cout << "8. Guardar base de datos clientes" << endl;
				cout << "9. Guardar base de datos empleados" << endl << endl;
				cout << endl << "Ingrese opci�n: ";
				cin >> menu;
				if(cin.fail()){
					cin.clear();
					fflush(stdin);
					cout << "Opci�n inv�lida" << endl;
					Sleep(500);
					system("cls");
				}
				if(menu == 5){
					system("cls");
					break;
				}
				switch(menu){//Se llama la funci�n correspondiente
					case 1:
						nuevoMiembro(empleadosPtr, clientesPtr);
						break;
					case 2:
						eliminarMiembro(empleadosPtr, clientesPtr);
						break;
					case 3:
						system("cls");
						InfoClientes(clientes);
						break;
					case 4:
						GuardTot(Ventas,precios,productos,descuento);
						Sleep(700);
						system("cls");
						break;
					case 6:
						leerDBC(clientes);
						Sleep(700);
						system("cls");
						break;
					case 7:
						leerDBE(empleados);
						Sleep(700);
						system("cls");
						break;
					case 8:
						ImprimirDBC(clientes);
						Sleep(700);
						system("cls");
						break;
					case 9:
						ImprimirDBE(empleados);
						Sleep(700);
						system("cls");
						break;
					default:
						cout << "Opci�n inv�lida" << endl;
						Sleep(500);
						system("cls");
				}
			}
		}
		
		if(concorrect && sel == 'c'){//Menu cliente
			while(true){
				cout << "Usuario: " << clientes[index].Nombre << endl << endl;
				cout << "---Men�---" << endl;
				cout << "1. Ver mis datos" << endl;
				cout << "2. Modificar direcci�n" << endl;
				cout << "3. Modificar nombre de usuario" << endl;
				cout << "4. Modificar contrase�a" << endl;
				cout << "5. Cerrar sesi�n" << endl;
				cout << "6. Comprar" << endl << endl;
				cout << "Ingresa la opci�n: ";
				cin >> menu;
				fflush(stdin);
				if(menu == 5){
					clientes[index].cart = vector<int>(12,0);//Al cerrar sesi�n se resetea el carrito de compras
					break;
				}
				switch(menu){
					case 1:{
						system("cls");
						clientes[index].Info();
						system("pause>0");//Se crea una pausa hasta que se oprima una tecla
						system("cls");
						break;
					}
					case 2:{
						clientes[index].CambiarDir();
						break;
					}
					case 3:{
						clientes[index].CambiarUs();
						break;
					}
					
					case 4:{
						clientes[index].cambiarCon(Newpass());
						break;
					}
					
					case 6:{
						system("cls");
						comprar(Ventas, precios, productos, clientesPtr, index, ticket,descuento);
						break;
					}
					default:
						cout << "Opci�n inv�lida" << endl;
						Sleep(500);
						system("cls");
				}
			}
		}
	
		Sleep(500);
		system("cls");	
	}
	return 0;
}

/*
	Itera a trav�s de un arreglo de tipo empleado buscando coincidencia 
	con el nombre de usuario ingresado, al encontrarlo regresa el �ndice 
	donde se encuntra la coincidencia, o -1 en caso contrario.
*/
int VerNombreE(string nombre, vector<Empleado> arr, bool &con){
	for(int  i = 0; i < arr.size(); i++){
		if (nombre == arr[i].NombreUs){
			return i;
		}
	}
	cout << "Usuario inv�lido" << endl;
	con = false;
	Sleep(700);
	system("cls");
	return -1;
}

/*
	Verifica la contrase�a en el �ndice que regresa la funci�n VerNombreE,
	en caso de coincidir regresa verdadero, o falso en caso contrario
*/
bool VerConE(int ind, string con, vector<Empleado> arr){
	if(con == arr[ind].Contrasenha ){
		return true;
	}
	cout << "Contrase�a incorrecta" <<endl;
	Sleep(700);
	return false;
}

/*
	Verifica si la contrase�a es v�lida referente a los siguientes par�metros:
	-Contenga una may�scula
	- Contenga una min�scula
	-Contenga un car�cter especial
	-Contenga un d�gito
	Si todas las condiciones se cumplen, la funci�n regresa true, en caso contrario false
	
*/
bool verCon(string con){
	bool esp[4] = {false, false, false, false};
	
	if(con.length() < 8 || con.length() > 14){
		return false;
	}
	for (int i = 0; i < con.length(); i++){
		if ((con[i] >= 33 && con[i] <= 47) || (con[i]>= 59 && con[i] <= 64)){
			esp[0] = true;
		}
		if(con[i] >= 48 && con[i] <= 57){
			esp[1] = true;
		}
		
		if(con[i] >= 65 && con[i] <= 90){
			esp[2] = true;
		}
		
		if(con[i] >= 97 && con[i] <= 122){
			esp[3] = true;
		}
	}
	
	if(esp[0] == true && esp[1] == true && esp[2] == true && esp[3] == true){
		return true;
	}
	
	return false;
	
}


/*
	Se genera una contrase�a de un longitud aleatoria entre 8 y 14.
	Se itera en un ciclo desde 0 hasta la longitud, generando n�meros aleatorios 
	que se castean a su correspondiente valos Ascii y se agregan a una string vac�o, verificando 
	que la constrase�� cumpla con los requisitos. En caso de no hacerlo se vac�a el string y se inicia de 
	nuevo con la iteraci�n.
*/
string GenCon(){
	string contrasenha;
	int cant;
	char car;
	cant = 8 + rand() % 7;
	do{
		contrasenha = "";
		for(int i = 0; i < cant; i++){
			car = 35 + rand() % 90;
			contrasenha.push_back(car);
			}
	}while(!verCon(contrasenha));
	cout << "Su nueva contrase�a es: " << contrasenha << endl;
	cout << "Presione cualquier tecla una vez que termine de copiar la nueva clave..." << endl;
	system("pause>0");
	system("cls");
	return contrasenha;
}
/*
	Tiene el mismo proposito que la funci�n VerNombreE, pero con el vector de cliente.
*/
int VerNombreC(string nombre, vector<Cliente> arr, bool &con){
	for (int i = 0; i < arr.size(); i++){
		if (nombre == arr[i].NombreUs){
			return i;
		}
	}
	cout << "Usuario inv�lido" << endl;
	con = false;
	Sleep(700);
	system("cls");
	return -1;
}
/*
	Tiene el mismo proposito que la funci�n VerConE, pero con el vector de cliente.
*/
bool VerConC(int ind, string con, vector<Cliente> arr){
	if(con == arr[ind].Contrasenha){
		return true;
	}
	
	cout << "Contrase�a incorrecta" << endl;
	return false;
}

/*
	Se crea una instancia de la estructura empleado o cliente seg�n sea el caso, se piden los datos mediante la consola y se guardan 
	como atributos de instancia. Posteriormente se agrega la instancia a su vector correspondiente. Sus parametros son punteros.
*/
void nuevoMiembro(vector<Empleado>* empleados, vector<Cliente>* clientes){
	/*string nombre, nombreUs, fechaNac, direccion, contrasenha;
	char sexo;
	*/
	char sel;
	cout << "Dar de alta:\n a. empleado\n b. cliente\nIngresar opci�n: ";
	cin >> sel;
	fflush(stdin);
	system("cls");
	switch(sel){
	case 'a':{
		Empleado empleado;
		cout << "Ingrese su nombre: ";
		fflush(stdin);
		getline(cin, empleado.Nombre);
		cout << "Ingrese nombre de usuario: ";
		cin >> empleado.NombreUs;
		cout << "Ingrese fecha de nacimiento: ";
		fflush(stdin);
		getline(cin, empleado.FechaNac);
		cout << "Ingrese sexo: ";
		cin >> empleado.Sexo;
		cout << "Ingrese su direcci�n: ";
		fflush(stdin);
		getline(cin, empleado.Direccion);
		do{
			cout << "Ingresa contrase�a: ";
			fflush(stdin);
			getline(cin, empleado.Contrasenha);
		 	if(!verCon(empleado.Contrasenha)){
		 	cout << "Contrase�a invalida. Int�ntelo de nuevo" << endl;
		 	}
		}while(!verCon(empleado.Contrasenha));	
		(*empleados).push_back(empleado);
		break;
		}
	case 'b':{
		Cliente cliente;
		cout << "Ingrese su nombre: ";
		fflush(stdin);
		getline(cin, cliente.Nombre);
		cout << "Ingrese nombre de usuario: ";
		cin >> cliente.NombreUs;
		cout << "Ingrese fecha de nacimiento: ";
		fflush(stdin);
		getline(cin, cliente.FechaNac);
		cout << "Ingrese sexo: ";
		cin >> cliente.Sexo;
		cout << "Ingrese su direcci�n: ";
		fflush(stdin);
		getline(cin, cliente.Direccion);
		do{
			cout << "Ingresa contrase�a: ";
			fflush(stdin);
			getline(cin, cliente.Contrasenha);
		 	if(!verCon(cliente.Contrasenha)){
		 	cout << "Contrase�a invalida. Int�ntelo de nuevo" << endl;
		 	}
		}while(!verCon(cliente.Contrasenha));
		//Cliente cliente = Cliente(nombre, nombreUs, fechaNac, sexo, direccion, contrasenha);
		(*clientes).push_back(cliente);
		break;
	}
	default:
	cout << "Opci�n inv�lida" << endl;
	}
	Sleep(300);
	system("cls");
}
/*
	`Por la consola se solicita el nombre del empleado o cliente a eliminar y se itera en su vector correspondiente, en caso de
	coincidir se elimina la instancia de la estructura creada. En caso de no haber coincidencia se imprime en consola "no 
	encontrado".
*/
void eliminarMiembro(vector<Empleado>* empleados, vector<Cliente>* clientes){
	char sel;
	string nombre;
	bool esta = false;
	system("cls");
	cout << "Dar de baja:\n a. empleado\n b. cliente\n Ingresar opci�n:";
	cin >> sel;
	fflush(stdin);
	switch(sel){
		case 'a':{
			cout << "Ingrese el nombre del empleado a eliminar: ";
			fflush(stdin);
			getline(cin, nombre);
			for(int i = 0; i < (*empleados).size(); i++){
				if(nombre == (*empleados)[i].Nombre){
					(*empleados).erase((*empleados).begin() + i);
					esta = true;
				}
			}
			if(!esta){
				cout << "Empleado no encontrado" << endl;
				Sleep(700);
			}
			break;
		}
		case 'b':{
			cout << "Ingrese el nombre del cliente a eliminar: ";
			fflush(stdin);
			getline(cin, nombre);
			for(int i = 0; i < (*clientes).size(); i++){
				if (nombre == (*clientes)[i].Nombre){
					(*clientes).erase((*clientes).begin() + i);
					esta = true;
				}
			}
			if(!esta){
				cout << "Cliente no encontrado" << endl;
				Sleep(700);
				system("cls");
			}
			break;
		}
		default:
			cout << "Opci�n inv�lida";
			Sleep(700);
	}
	system("cls");
}

/*
	Se itera por el vector clientes y se llama al metodo Info() de cada instancia en el vector para mostrar la informaci�n de la estructura (su atributos).
*/
void InfoClientes(vector <Cliente> clientes){
	for(int i = 0; i < clientes.size(); i++){
		clientes[i].Info();
		cout << "------------------------------------" << endl;
	}
	system("pause>0");
	system("cls");
}
/*
	Regresa la constrase�a ingresada por el usuario, una vez que haya cumplido con los requisitos de validaci�n de la funci�n VerCon ()
*/
string Newpass(){
		string con;
		do{
			cout << "Ingrese la nueva contrase�a: ";
			fflush(stdin);
			getline(cin, con);
			if(!verCon(con)){
				cout << "Contrase�a inv�lida" << endl << endl;
			}
		} while(!verCon(con));
		system("cls");
		return con;
}
/*
	Accede a un array de precios a uno de productos y al carrito de una instancia en un indice espec�fico del vector clientes. Itera a travez del vector del 
	carrito, verifiando que en sus posiciones haya numeros mayores que 0, si hay estos n�meros. Imprime el precio, el n�mbre y la cantidad de unidades compradas 
	las cuales se encuentran en diferentes vectores pero en la misma posici�n.
	
	Se actualiza el contador de descuentos 	sumando el valor anterior del contador m�s el .12 de la compra actual en cado de que el subtotal sea mayor
	a 5000.
*/

void carrito(int precios[], string productos[], vector<Cliente> clientes, int index, int ticket, int &descuento  ){
	if(clientes[index].Sexo == 'H' || clientes[index].Sexo == 'h'){
		cout << "Bienvenido a tu carrito ";
	}
	else if(clientes[index].Sexo == 'M' || clientes[index].Sexo == 'm'){
		cout << "Bienvenida a tu carrito ";
	}
	cout << clientes[index].Nombre << endl << endl;
	cout<<"Numero de ticket: "<< ticket<<endl<<endl;
	vector <int> cart = clientes[index].cart;
	int cont = 1, subtotal = 0;
	cout << "Art�culo\tPrecio Unitario\t\tCantidad\tTotal" << endl;
	for(int i = 0; i < cart.size(); i++){
		if(cart[i] != 0){
			cout << "Item " << cont << ":" << endl;
			cont++;
			cout << productos[i] <<"\t" <<"$" << precios[i] << "\t\t\t\t" << cart[i] << "\t" << "$" << precios[i] * clientes[index].cart[i] << endl;
			subtotal += precios[i] * clientes[index].cart[i];
		}
	}
	cout << endl << endl << "Subtotal $" << subtotal << endl;
	if(subtotal > 5000){
		cout << "Has ganado un descuento de 12%" << endl;
		descuento+=subtotal*.12;
		subtotal *= 0.88;
		
		cout << "El subtotal con el descuento quedar�a en $" << subtotal << endl; 
	}
	cout << "IVA: $" << subtotal * .16 << endl;
	cout << "Total: $" << subtotal * 1.16 << endl;
	cout << endl << endl << endl << "Presione cualquier tecla para continuar...";
	system("pause>0");
	
}

void comprar(vector<int> &db, int precios[], string productos[], vector<Cliente>* clientes, int index, int ticket,int &descuento){
	int menu, menu2, cant;
	while(true){
		/*
		Se imprime el catalogo ciclicamente hasta que el usuario introduzca "dejar de comprar"
		*/
		cout << "Cat�logo" << endl << endl;
		cout << "1. Mesas" << endl;
		cout << "2. Sillones" << endl;
		cout << "3. Sillas" << endl;
		cout << "4. Camas" << endl;
		cout << "5. Carrito" << endl;
		cout << "6. Dejar de comprar" << endl;
		cout << endl << "Ingresa opci�n: ";
		cin >> menu;
		if(cin.fail() || menu > 6){
			/* 
			En caso de que se agregue un tipo de dato distinto al  int, cin maracara error y entrara en este if. Se limpiara el buffer y se imprimira opci�n 
			incorrecta. Esto con el fin de que el programa no termine abruptamente.
			*/
			cin.clear();
			fflush(stdin);
			cout << "Opci�n inv�lida";
			menu = 6;
		}
		if(menu == 6){
			system("cls");
			break;
		}
		if(menu == 5){ //Se llama la func�on carrito
			system("cls");
			carrito(precios, productos, (*clientes), index, ticket,descuento);
			system("cls");
			continue;		
		}
		system("cls");
		switch(menu){
			/*
			Dependiendo del tipo de producto que se eligi� se despliega un sub-menu con los items contenidos en el arreglo productos. Si el producto son mesas
			se imprimen los primeras tres posiciones del arreglo productos. Si el producto con sillones, se imprime del indice 3 al 5. siel producto son sillas 
			se imprime del indice 6 al indice 8. Si son camas del 9 al 11. Posteriomente se imprime una cuarta opci�n sin importar el tipo 
			de producto.
			*/
			case 1:
				for(int i = 0; i < 3; i++){
					cout << i + 1 << ". " << productos[i] << "\t$" << precios[i] << endl;
				}
				break;
			case 2:
				for(int i = 3; i < 6; i++){
					cout << i - 2 << ". " << productos[i] << "\t$" << precios[i] << endl;
				}
				break;
			case 3:
				for(int i = 6; i < 9; i++){
					cout << i - 5 << ". " << productos[i] << "\t$" << precios[i] << endl; 
				}
				break;
			case 4:
				for(int i = 9; i < 12; i++){
					cout << i - 8 << ". " << productos[i] << "\t$" << precios[i] << endl;
				}
				break;
		}
				if(menu != 5 || menu <= 6 ){
					cout << "4. Men� anterior" << endl;
				}
				cout << endl << "Ingrese opci�n: ";
				cin >> menu2;
				if(cin.fail() || (menu2 < 1 || menu2 > 4)){
					cin.clear();
					fflush(stdin);
					cout << "Opci�n inv�lida";
					system("cls");
				} 
				if(menu2 == 4){ //Se va a la siguiente iteraci�n del menu
					system("cls");
					continue;
				}
				//Dependiendo delmproducto general que se escogi�, la opci�n del sub-menu sumara o restara cierto n�mero para acoplarse a las posiciones de
				//los arreglos
				if(menu == 1){ 
					menu2 -= 1;
				}
				if(menu == 2){
					menu2+= 2;
				}
				if(menu == 3){
					menu2 += 5;
				}
				if(menu == 4){
					menu2+=8;
				}
				cout << "Producto elegido: " << productos[menu2] << endl;//Se imprime el producto que se eligi�
				cout << "Cantidad: "; //Se pide la cantidad y se guarda en una variable
				cin >> cant;
				(*clientes)[index].cart[menu2] += cant;//Se agrega el producto al carrito en la posici�n correspondiente
				db[menu2] += cant;//Se actualiza el contador del producto espec�fico en el arreglo de ventas general.
				cout << "El total por " << cant << " " << productos[menu2];
				if(cant > 1){
				cout <<"s";
				}
				cout << " ser�a un total de $" << cant * precios[menu2] << endl;
				Sleep(3000);
				system("cls");
		}
	}
	/*
	Se carga una base de datos de un archivo con extensi�n.txt y separado cada valor por una tabulaci�n.
	*/
void leerDBE(vector <Empleado> &empleados){
	fstream archivo;
	string text, aux; //Se crea una variable para guardar cada una de las lineas y una para guardar un dato espec�fico.
	bool is = false;
	int linea = 1; //Se crea esta variable para verificar que no se lean los encabezados.
	archivo.open("DatabaseE.txt", ios::in);//Se abre un archivo en modo lectura 
	if(archivo.is_open()){
		while(getline(archivo, text)){//Se lee el texto hasta que se termine el nmero de lineas
			if(linea > 1){
				int cont = 0;
				Empleado empleado;
				is = false;
				for(int i = 0; i < text.length(); i++){ //Se hace comprobaci�n de los encabezados
					if(text[i] == 9 || i == text.length() - 1){ //Se verifica que el caracter leido no sea un tabulador.
					/*
					Este for se utiliza para saber si el dato leido no existe ya en la base de datos, en caso de ser as�, se va a la siguiente l�nea
					y vac�a la variable auxiliar.
					*/
						for (int i = 0; i < empleados.size(); i++){
							if(cont == 0 && aux == empleados[i].Nombre){
								is = true;
							}
						}
						if(is){
							aux.clear();
							break;
						}
						/*
						Se verifica en que columna estamos para asignar ese valor a un atributo espec�fico a la instancia del tipo empleado que se creo
						*/
						if(cont == 0){
							empleado.Nombre = aux;
							cont++;
						}
						else if(cont == 1){
							empleado.NombreUs = aux;
							cont++;
						}
						else if(cont == 2){
							empleado.Direccion = aux;
							cont++;
						}
						else if(cont == 3){
							empleado.Contrasenha = aux;
							cont++;
						}
						else if(cont == 4){
							empleado.FechaNac = aux;
							cont++;
						}
						else if(cont == 5){
							empleado.Sexo = aux[0];
							cont++;
						}
						aux.clear();
						continue;
					}
					aux.push_back(text[i]);//En caso de no ser tabulador se agregara el dato a la variable auxiliar
				}
				if(!is){//Si no existe un empleado con esos datos, se garegara a la base de datos.
					empleados.push_back(empleado);
				}		
			}
			linea++;
		}
		cout << "Lectura exitosa" << endl;
		archivo.close();
	}
	else{
		cout << "Archivo no se abri�" << endl;
	}
}
/*
	Hace lo mismo que la funci�n anterior pero con el tipo de dato cliente y su vector correspondiente
*/
void leerDBC(vector <Cliente> &clientes){
	fstream archivo;
	string text, aux;
	bool is = false;
	int linea = 1;
	archivo.open("DatabaseC.txt", ios::in);
	if(archivo.is_open()){
		while(getline(archivo, text)){
			if(linea > 1){
				int cont = 0;
				Cliente cliente;
				is = false;
				for(int i = 0; i < text.length(); i++){
					if(text[i] == 9 || i == text.length() - 1){
						for (int i = 0; i < clientes.size(); i++){
							if(cont == 0 && aux == clientes[i].Nombre){
								is = true;
							}
						}
						if(is){
							aux.clear();
							break;
						}
						if(cont == 0){
							cliente.Nombre = aux;
							cont++;
						}
						else if(cont == 1){
							cliente.NombreUs = aux;
							cont++;
						}
						else if(cont == 2){
							cliente.Direccion = aux;
							cont++;
						}
						else if(cont == 3){
							cliente.Contrasenha = aux;
							cont++;
						}
						else if(cont == 4){
							cliente.FechaNac = aux;
							cont++;
						}
						else if(cont == 5){
							cliente.Sexo = aux[0];
							cont++;
						}
						aux.clear();
						continue;
					}
					aux.push_back(text[i]);
				}
				if(!is){
					clientes.push_back(cliente);
				}		
			}
			linea++;
		}
		cout << "Lectura exitosa" << endl;
		archivo.close();
	}
	else{
		cout << "Archivo no se abri�" << endl;
	}
}
/*
	Se itera a travez del vector empleado y se imprime de forma tabulada cada uno de sus atributos, mandando esta informaci�n a un archivo de texto
	.txt
*/
void ImprimirDBE(vector<Empleado> empleados){
	fstream archivo;
	archivo.open("DatabaseE.txt", ios::out);
	/*
	Se abre un archivo en modo escritura.
	*/
	if(archivo.is_open()){//Se hace una comprobaci�n de que el archivo se haya abierto correctamente
		archivo << "Nombre\tNombreUs\tDireccion\tContrase�a\tFechaNac\tSexo" << endl; //Encabezado de datos
		for(int i = 0; i < empleados.size(); i++){
			archivo << empleados[i].Nombre << "\t" << empleados[i].NombreUs << "\t" << empleados[i].Direccion << "\t";
			archivo << empleados[i].Contrasenha << "\t"<< empleados[i].FechaNac << "\t" << empleados[i].Sexo << "\t";
			archivo << endl;     
		}
		cout << "Impresi�n exitosa";
		archivo.close(); //Se cierra el archivo.
	}
	else{
		cout << "Error de impresi�n" << endl;
	}
}
// 	Hace lo mismo que la funci�n anterior pero con el tipo de dato cliente y su vector correspondiente
void ImprimirDBC(vector<Cliente> clientes){
	fstream archivo;
	archivo.open("DatabaseC.txt", ios::out);
	if(archivo.is_open()){
		archivo << "Nombre\tNombreUs\tDireccion\tContrase�a\tFechaNac\tSexo" << endl;
		for(int i = 0; i < clientes.size(); i++){
			archivo << clientes[i].Nombre << "\t" << clientes[i].NombreUs << "\t" << clientes[i].Direccion << "\t";
			archivo << clientes[i].Contrasenha << "\t"<< clientes[i].FechaNac << "\t" << clientes[i].Sexo << "\t";
			archivo << endl;     
		}
		cout << "Impresi�n exitosa";
		archivo.close();
	}
	
	else{
		cout << "Error de impresi�n" << endl;
	}
}
/*
	Se imprimen  los datos de los vectores ventas, productos y precios de forma tabulada con sus cantidades correspondientes.
*/
void GuardTot(vector<int>Ventas,int precios[12],string productos[12],int descuento){
	fstream Total;
	Total.open("DatabaseT.txt",ios::out);
	if(Total.is_open()){ 
		Total<<"Tipo de producto\tUnidades vendidas\tPrecio por unidad\tTotal"<<endl;
		for(int i = 0; i < 12; i++){
			Total << productos[i] << "\t\t\t" << Ventas[i] << "\t\t\t" << precios[i]<< "\t\t"<< Ventas[i]*precios[i];
			Total << endl;
		}
		Total<<"El total de descuento asciende a : $"<< descuento;
		cout << "Impresi�n exitosa";
		Total.close();
	}
	else{
		cout << "Error de impresi�n" << endl;
	}
		
}




