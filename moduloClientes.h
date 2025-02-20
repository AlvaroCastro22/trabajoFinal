#ifndef moduloClientes

#define moduloClientes

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
using namespace std;

struct Cliente {
    int DNI;
    string nombres;
    string apellidos;
    string correo;
    string direccion;
    string telefono;
};

unordered_map<int, Cliente> tablaClientes; // Tabla hash para almacenar información

void guardarEnCSV() {
    ofstream archivo("datosClientes.csv");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    archivo << "DNI,Nombres,Apellidos,Correo,Direccion,Telefono\n";
    for (const auto& par : tablaClientes) {
        const Cliente& c = par.second;
        archivo << c.DNI << "," << c.nombres << "," << c.apellidos << "," 
                << c.correo << "," << c.direccion << "," << c.telefono << "\n";
    }

    archivo.close();
}

void cargarDesdeCSV() {
    ifstream archivo("datosClientes.csv");
    if (!archivo) return;

    string linea, token;
    getline(archivo, linea); // Saltar la cabecera

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Cliente c;
        getline(ss, token, ','); 
        c.DNI = stoi(token);
        getline(ss, c.nombres, ',');
        getline(ss, c.apellidos, ',');
        getline(ss, c.correo, ',');
        getline(ss, c.direccion, ',');
        getline(ss, c.telefono, ',');

        tablaClientes[c.DNI] = c;
    }

    archivo.close();
}

void registrarCliente() {
    Cliente nuevo;
    cout << "Ingrese el documento de identidad: ";
    cin >> nuevo.DNI;
    cin.ignore();

    cout << "Ingrese nombres: ";
    getline(cin, nuevo.nombres);
    cout << "Ingrese apellidos: ";
    getline(cin, nuevo.apellidos);
    cout << "Ingrese correo: ";
    getline(cin, nuevo.correo);
    cout << "Ingrese direccion: ";
    getline(cin, nuevo.direccion);
    cout << "Ingrese telefono: ";
    getline(cin, nuevo.telefono);

    tablaClientes[nuevo.DNI] = nuevo;
    guardarEnCSV();
    cout << "Cliente registrado con éxito.\n";
}

void buscarCliente() {
    int DNI;
    cout << "Ingrese el DNI a buscar: ";
    cin >> DNI;

    if (tablaClientes.find(DNI) != tablaClientes.end()) {
        cout << "El DNI del cliente fue encontrado: " << DNI << endl;
    } else {
        cout << "El DNI del cliente no ha sido encontrado." << endl;
    }
}

void mostrarCliente() {
    int DNI;
    cout << "Ingrese el DNI del cliente a mostrar: ";
    cin >> DNI;

    if (tablaClientes.find(DNI) != tablaClientes.end()) {
        Cliente c = tablaClientes[DNI];
        cout << "\nDNI: " << c.DNI
             << "\nNombres: " << c.nombres
             << "\nApellidos: " << c.apellidos
             << "\nCorreo: " << c.correo
             << "\nDireccion: " << c.direccion
             << "\nTelefono: " << c.telefono << endl;
    } else {
        cout << "Cliente no encontrado.\n";
    }
}

void actualizarCliente() {
    int DNI;
    cout << "Ingrese el DNI del cliente a actualizar: ";
    cin >> DNI;
    cin.ignore();

    if (tablaClientes.find(DNI) == tablaClientes.end()) {
        cout << "El cliente no existe." << endl;
        return;
    }

    Cliente& c = tablaClientes[DNI];
    string opcion;

    cout << "¿Actualizar nombres? (s/n): ";
    cin >> opcion;
    cin.ignore();
    if (opcion == "s" || opcion == "S") {
        cout << "Nuevo nombre: ";
        getline(cin, c.nombres);
    }

    cout << "¿Actualizar apellidos? (s/n): ";
    cin >> opcion;
    if (opcion == "s" || opcion == "S") {
        cout << "Nuevos apellidos: ";
        getline(cin, c.apellidos);
    }

    cout << "¿Actualizar correo? (s/n): ";
    cin >> opcion;
    if (opcion == "s" || opcion == "S") {
        cout << "Nuevo correo: ";
        getline(cin, c.correo);
    }

    cout << "¿Actualizar dirección? (s/n): ";
    cin >> opcion;
    if (opcion == "s" || opcion == "S") {
        cout << "Nueva dirección: ";
        getline(cin, c.direccion);
    }

    cout << "¿Actualizar teléfono? (s/n): ";
    cin >> opcion;
    if (opcion == "s" || opcion == "S") {
        cout << "Nuevo teléfono: ";
        getline(cin, c.telefono);
    }

    guardarEnCSV();
    cout << "Cliente actualizado correctamente.\n";
}

int gestionClientes(){
    cargarDesdeCSV();
    int opcion;
    
    do {
        cout << "\nMenu de Clientes:\n"
             << "1. Registrar cliente\n"
             << "2. Buscar cliente\n"
             << "3. Mostrar datos del cliente\n"
             << "4. Actualizar datos del cliente\n"
             << "0. Salir\n"
             << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarCliente();
                break;
            case 2:
                buscarCliente();
                break;
            case 3:
                mostrarCliente();
                break;
            case 4:
                actualizarCliente();
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}
#endif