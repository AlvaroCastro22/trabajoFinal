#ifndef moduloCandidatos

#define moduloCandidatos
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include<fstream>
#include<sstream>
using namespace std;

struct Evaluacion {
    string criterio;
    int calificacion;
    Evaluacion* siguiente;
};

struct Candidato {
    int id;
    string nombre;
    string telefono;
    string correo;
    string dni;
    string estado;
    Evaluacion* evaluaciones;
    Candidato* siguiente;
};

struct Entrevista {
    int candidatoId;
    Entrevista* siguiente;
};




class SeleccionCandidatos {
    private:
        Candidato* cabeza;
        queue<Entrevista*> colaEntrevistas;
        stack<string> pilaProcesos;
        int contadorId;
    
    public:
        SeleccionCandidatos() : cabeza(nullptr), contadorId(1) {}
    void CargarCandidatos(){
        ifstream lecturaF;
        string linea;
        string palabra;
        string nombre = "candidatos.csv";
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
                    Candidato* nuevo = new Candidato;
                    nuevo->id = contadorId++;
                    nuevo->nombre = arr[0];
                    nuevo->dni = arr[1];
                    nuevo->telefono=arr[2];
                    nuevo->correo=arr[3];
                    nuevo->estado = "Proceso";
                    nuevo->evaluaciones = nullptr;
                    nuevo->siguiente = cabeza;
                    cabeza = nuevo;
        }
        
        lecturaF.close();
    }
    void RegistrarCandidato() {
        Candidato* nuevo = new Candidato;
        nuevo->id = contadorId++;
        cout << "Ingrese nombre del candidato: ";
        cin.ignore();
        getline(cin, nuevo->nombre);
        cout << "Ingrese el documento de identidad: ";
        getline(cin, nuevo->dni);
        cout << "Ingrese telefono del candidato: ";
        getline(cin, nuevo->telefono);
        cout << "Ingrese correo del candidato: ";
        getline(cin, nuevo->correo);
        nuevo->estado = "Proceso";
        nuevo->evaluaciones = nullptr;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cout << "Candidato registrado con ID: " << nuevo->id << "\n";
    }
    
        void BuscarCandidato(int id) {
            Candidato* actual = cabeza;
            while (actual) {
                if (actual->id == id) {
                    cout << "ID: " << actual->id << "\nNombre: " << actual->nombre
                         << "\nDocumento de Identidad: " << actual-> dni << "\nTelefono: " << actual->telefono << "\nCorreo: " << actual->correo
                         << "\nEstado: " << actual->estado << endl;
                    return;
                }
                actual = actual->siguiente;
            }
            cout << "Candidato no encontrado." << endl;
        }
    
        void TomarDecision(int id, string decision) {
            Candidato* actual = cabeza;
            while (actual) {
                if (actual->id == id) {
                    if (decision == "si") {
                        actual->estado = "En proceso";
                        Entrevista* nueva = new Entrevista;
                        nueva->candidatoId = id;
                        colaEntrevistas.push(nueva);
                        cout << "Candidato "<< actual->nombre<<" agregado a la cola de entrevistas." << endl;
                    } else {
                        actual->estado = "Rechazado";
                        cout << "Candidato "<< actual->nombre<<" rechazado del proceso de seleccion." << endl;
                    }
                    return;
                }
                actual = actual->siguiente;
            }
            cout << "Candidato no encontrado." << endl;
        }
        void SubirCandidatosCSV(){
            
            string nombre = "candidatos.csv";
            string linea;
            ofstream archivo;
            archivo.open(nombre,ios::out);
            if (archivo.fail())
            {
                cout<<"No se puede abrir archivo";
                return;
            }
        
            Candidato* actual = cabeza;
            while (actual) {
                archivo << actual->nombre<<","<<actual->dni<<","<<actual->telefono<<","<<actual->correo<< endl;
                actual = actual->siguiente;
            }
            
            archivo.close();
        }
        void EliminarCandidato(){
            Candidato* actual = cabeza;
            bool hayRechazados = false;
            while (actual)
            {
                if (actual->estado=="Rechazado")
                {
                   
                    cabeza = actual->siguiente; 
                    hayRechazados = true;   
                }
                Candidato *aux = actual->siguiente;
                
                if (aux!=nullptr)
                {
                    if (aux->estado=="Rechazado")
                    {
                        
                        actual->siguiente = aux->siguiente;
                        hayRechazados = true;
                        delete aux;
                    }
                    
                }
                
                
                actual = actual->siguiente;
            }
            if (hayRechazados)
            {
                cout<<endl<<"Candidatos rechazados eliminados de la base de datos"<<endl;
            }else
            {
                cout<<endl<<"No se encuentran candidatos rechazados"<<endl;
            }
            
            
            
        }
        void AgendarEntrevista() {
            if (!colaEntrevistas.empty()) {
                Entrevista* entrevista = colaEntrevistas.front();
                colaEntrevistas.pop();
                cout << "Entrevista agendada para candidato ID: " << entrevista->candidatoId << endl;
                delete entrevista;
            } else {
                cout << "No hay entrevistas pendientes." << endl;
            }
        }
    
        void FirmarContrato(int id) {
            Candidato* actual = cabeza;
            while (actual) {
                if (actual->id == id) {
                    actual->estado = "Contratado";
                    cout << "Candidato ID " << id << " ha sido contratado." << endl;
                    return;
                }
                actual = actual->siguiente;
            }
            cout << "Candidato no encontrado." << endl;
        }
    
        void MostrarCandidatos() {
            Candidato* actual = cabeza;
            while (actual) {
                cout << "ID: " << actual->id << " | Nombre: " << actual->nombre << " | DNI: " << actual->dni << " | Estado: " << actual->estado << endl;
                actual = actual->siguiente;
            }
        }
    };

    int gestionCandidatos(){

        SeleccionCandidatos seleccion;
    int opcion, id;
    string decision;
    seleccion.CargarCandidatos();
    do {
        cout << "\n1. Registrar candidato\n2. Buscar candidato\n3. Tomar decision\n4. Agendar entrevista\n5. Firmar contrato\n6. Mostrar candidatos\n7. Eliminar candidatos rechazados\n0. Salir\nIngrese opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                seleccion.RegistrarCandidato();
                seleccion.SubirCandidatosCSV();
                break;
            case 2:
                cout << "Ingrese ID del candidato: ";
                cin >> id;
                seleccion.BuscarCandidato(id);
                break;
            case 3:
                cout << "Ingrese ID del candidato: ";
                cin >> id;
                cout << "Ingrese decision (si/no): ";
                cin >> decision;
                seleccion.TomarDecision(id, decision);
                
                break;
            case 4:
                seleccion.AgendarEntrevista();
                break;
            case 5:
                cout << "Ingrese ID del candidato: ";
                cin >> id;
                seleccion.FirmarContrato(id);
                break;
            case 6:
                seleccion.MostrarCandidatos();
                break;
            case 7:
                seleccion.EliminarCandidato();
                seleccion.SubirCandidatosCSV();
                break;
        }
    } while (opcion != 0);
    return 0;
    }
#endif