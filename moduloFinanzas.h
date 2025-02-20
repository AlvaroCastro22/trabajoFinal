#ifndef moduloFinanzas

#define moduloFinanzas
#include <iostream>
#include <vector>
#include<fstream>
#include<sstream>
struct Transaccion {
    int id;
    int clienteId;
    double monto;
    string tipo; // "Ingreso" o "Egreso"
};

struct Activo {
    int id;
    double valor;
};

struct Pasivo {
    int id;
    double valor;
};

vector<Transaccion> transacciones;
vector<Activo> activos;
vector<Pasivo> pasivos;

void cargarTransacciones(vector<Transaccion> &transacciones){

    ifstream lecturaF;
    string linea;
    string palabra;
    string nombre = "transacciones.csv";
    lecturaF.open(nombre,ios::in);
    if(lecturaF.fail()){
        cout<<"No se puede abrir el archivo";
        return;
        
    }
    while (!lecturaF.eof())
    {
        
           
        vector<string> arr;
        string valor;
        bool entreComillas = false;
        getline(lecturaF,linea);
        if (linea.empty())
        {
            continue;
        }
                for (size_t i = 0; i < linea.length(); i++)
                {
                    char c = linea[i];
                    if (c=='"')
                    {
                        entreComillas = !entreComillas;
                    }else if (c==',' && !entreComillas)
                    {
                        arr.push_back(valor);
                        valor="";
                    }else{
                        valor += c;
                    }
                    
                    
                }
                arr.push_back(valor);
                int id = stoi(arr[0]);
                int clienteId = stoi(arr[1]);
                double monto = stod(arr[2]);
                transacciones.push_back({id, clienteId, monto, arr[3]});
    }
    
    lecturaF.close();
}
void cargarActivos(vector<Activo> &activos){

    ifstream lecturaF;
    string linea;
    string palabra;
    string nombre = "activos.csv";
    lecturaF.open(nombre,ios::in);
    if(lecturaF.fail()){
        cout<<"No se puede abrir el archivo";
        return;
        
    }
    while (!lecturaF.eof())
    {
        
           
        vector<string> arr;
        string valor;
        bool entreComillas = false;
        getline(lecturaF,linea);
        if (linea.empty())
        {
            continue;
        }
                for (size_t i = 0; i < linea.length(); i++)
                {
                    char c = linea[i];
                    if (c=='"')
                    {
                        entreComillas = !entreComillas;
                    }else if (c==',' && !entreComillas)
                    {
                        arr.push_back(valor);
                        valor="";
                    }else{
                        valor += c;
                    }
                    
                    
                }
                arr.push_back(valor);
                int id = stoi(arr[0]);
                double valorMonto = stod(arr[1]);
                activos.push_back({id, valorMonto});
    }
    
    lecturaF.close();
}
void subirActivos(vector<Activo> &activos){
    string nombre = "activos.csv";
    ofstream archivo;
    archivo.open(nombre,ios::out);
    if (archivo.fail())
    {
        cout<<"No se puede abrir archivo";
        return;
    }

    for (size_t i = 0; i < activos.size(); i++)
    {
        archivo<<activos[i].id<<","<<activos[i].valor;
        if (i+1!=activos.size())
        {
            archivo<<endl;
        }
        
        
    }
    
    
        
    
    archivo.close();
}


void cargarPasivos(vector<Pasivo> &pasivos){

    ifstream lecturaF;
    string linea;
    string palabra;
    string nombre = "pasivos.csv";
    lecturaF.open(nombre,ios::in);
    if(lecturaF.fail()){
        cout<<"No se puede abrir el archivo";
        return;
        
    }
    while (!lecturaF.eof())
    {
        
           
        vector<string> arr;
        string valor;
        bool entreComillas = false;
        getline(lecturaF,linea);
        if (linea.empty())
        {
            continue;
        }
                for (size_t i = 0; i < linea.length(); i++)
                {
                    char c = linea[i];
                    if (c=='"')
                    {
                        entreComillas = !entreComillas;
                    }else if (c==',' && !entreComillas)
                    {
                        arr.push_back(valor);
                        valor="";
                    }else{
                        valor += c;
                    }
                    
                    
                }
                arr.push_back(valor);
                int id = stoi(arr[0]);
                double valorMonto = stod(arr[1]);
                pasivos.push_back({id, valorMonto});
    }
    
    lecturaF.close();
}
void subirPasivos(vector<Pasivo> &pasivos){
    string nombre = "pasivos.csv";
    ofstream archivo;
    archivo.open(nombre,ios::out);
    if (archivo.fail())
    {
        cout<<"No se puede abrir archivo";
        return;
    }

    for (size_t i = 0; i < pasivos.size(); i++)
    {
        archivo<<pasivos[i].id<<","<<pasivos[i].valor;
        if (i+1!=pasivos.size())
        {
            archivo<<endl;
        }
        
        
    }
    
    
        
    
    archivo.close();
}




void subirTransacciones(vector<Transaccion> &transacciones){
    string nombre = "transacciones.csv";
    ofstream archivo;
    archivo.open(nombre,ios::out);
    if (archivo.fail())
    {
        cout<<"No se puede abrir archivo";
        return;
    }

    for (size_t i = 0; i < transacciones.size(); i++)
    {
        archivo<<transacciones[i].id<<","<<transacciones[i].clienteId<<","<<transacciones[i].monto<<","<<transacciones[i].tipo;
        if (i+1!=transacciones.size())
        {
            archivo<<endl;
        }
        
        
    }
    
    
        
    
    archivo.close();
}
void registrarTransaccion() {
    int id, clienteId;
    double monto;
    string tipo;
    cout << "Ingrese ID de la transacción: "; cin >> id;
    cout << "Ingrese ID del cliente: "; cin >> clienteId;
    cout << "Ingrese monto: "; cin >> monto;
    cout << "Ingrese tipo (Ingreso/Egreso): "; cin >> tipo;
    transacciones.push_back({id, clienteId, monto, tipo});
}

void modificarActivos() {
    int opcion, id;
    double valor;
    cout << "Lista de Activos:" << endl;
    for (const auto& a : activos) {
        cout << "ID: " << a.id << " - Valor: " << a.valor << endl;
    }
    cout << "1. Agregar Activo" << endl;
    cout << "2. Eliminar Activo" << endl;
    cout << "Seleccione una opción: "; cin >> opcion;
    if (opcion == 1) {
        cout << "Ingrese ID del nuevo activo: " ; cin >> id;
        cout << "Ingrese valor: "; cin >> valor;
        activos.push_back({id, valor});
    } else if (opcion == 2) {
        cout << "Ingrese ID del activo a eliminar: "; cin >> id;
        for (auto it = activos.begin(); it != activos.end(); ++it) {
            if (it->id == id) {
                activos.erase(it);
                break;
            }
        }
    }
}

void modificarPasivos() {
    int opcion, id;
    double valor;
    cout << "Lista de Pasivos:" << endl;
    for (const auto& p : pasivos) {
        cout << "ID: " << p.id << " - Valor: " << p.valor << endl;
    }
    cout << "1. Agregar Pasivo" << endl;
    cout << "2. Eliminar Pasivo" << endl;
    cout << "Seleccione una opción: "; cin >> opcion;
    if (opcion == 1) {
        cout << "Ingrese ID del nuevo pasivo: "; cin >> id;
        cout << "Ingrese valor: "; cin >> valor;
        pasivos.push_back({id, valor});
    } else if (opcion == 2) {
        cout << "Ingrese ID del pasivo a eliminar: "; cin >> id;
        for (auto it = pasivos.begin(); it != pasivos.end(); ++it) {
            if (it->id == id) {
                pasivos.erase(it);
                break;
            }
        }
    }
}

void generarReporteFinanciero() {
    double totalActivos = 0, totalPasivos = 0;
    for (const auto& a : activos) totalActivos += a.valor;
    for (const auto& p : pasivos) totalPasivos += p.valor;
    
    cout << "\n--- Reporte Financiero ---\n";
    cout << "Activos Totales: " << totalActivos << endl;
    cout << "Pasivos Totales: " << totalPasivos << endl;
    cout << "Ganancia Neta: " << (totalActivos - totalPasivos) << endl;
    
    cout << "\n--- Informe de Transacciones ---\n";
    for (const auto& t : transacciones) {
        cout << "ID: " << t.id << " - Cliente ID: " << t.clienteId << " - Monto: " << t.monto << " - Tipo: " << t.tipo << endl;
    }
}


int gestionFinanzas(){
    cargarTransacciones(transacciones);
    cargarActivos(activos);
    cargarPasivos(pasivos);
    int opcion;
    do {
        cout << "\nMenú de Opciones:" << endl;
        cout << "1. Registrar Transacción" << endl;
        cout << "2. Modificar Activos" << endl;
        cout << "3. Modificar Pasivos" << endl;
        cout << "4. Generar Reporte Financiero" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarTransaccion();
                subirTransacciones(transacciones);
                break;
            case 2:
                modificarActivos();
                subirActivos(activos);
                break;
            case 3:
                modificarPasivos();
                subirPasivos(pasivos);
                break;
            case 4:
                generarReporteFinanciero();
                break;
            case 5:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 5);
    
    return 0;
}

#endif