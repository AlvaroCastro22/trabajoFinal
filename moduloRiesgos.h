#ifndef moduloRiesgos

#define moduloRiesgos
#include <iostream>
#include <vector>
#include<fstream>
#include<sstream>
using namespace std;
struct Riesgo{

    int nivelRiesgo;
    string nombre;
    string descripcion;
};
void heapify(vector<Riesgo> &r,int pos){
    int padre = (pos-1)/2;
    if (pos==0)
    {
        
        return;
    }

    if (r[padre].nivelRiesgo<r[pos].nivelRiesgo)
    {
        swap(r[padre],r[pos]);
        heapify(r,padre);
        return;
    }

}
void heapifyDown(vector<Riesgo> &r,int pos){
    int largest = pos;
    int izq = 2*pos+1;
    int der = 2*pos+2;
    int size = r.size();
    if (izq<size && r[izq].nivelRiesgo>r[largest].nivelRiesgo )
    {
        largest = izq;
    }
    if(der<size && r[der].nivelRiesgo>r[largest].nivelRiesgo){
        largest = der;
    }

    if (largest!=pos)
    {
        swap(r[pos],r[largest]);
        heapifyDown(r,largest);
    }
    
    
}
void agregarRiesgo(vector<Riesgo> &r,int x,string nom,string desc){
    Riesgo item = {x,nom,desc};
    r.push_back(item);
    int posicion= r.size()-1;
    heapify(r,posicion);
}

void mostrarRiesgos(vector<Riesgo> r){
    int firstChild = 1;
    for (size_t i = 0; i < r.size(); i++)
    {
        if (i==0)
        {
            cout<<r[i].nivelRiesgo<<"-"<<r[i].nombre<<endl;

        }
        else
        {
            cout<<r[i].nivelRiesgo<<"-"<<r[i].nombre<<"  ";

        if (2*firstChild+1==i+1)
        {
            firstChild=i+1;
            cout<<endl;
        }
        }
        
        
        
        
    }
    
    

}
void eliminarRiesgoCSV(Riesgo riesgoABorrar){
    fstream lecturaF;
    string nombre = "riesgos.csv";
    string linea;
    vector<string> riesgosActuales;
    lecturaF.open(nombre,ios::in);
    if (lecturaF.fail())
    {
        cout<<"No se puede abrir el archivo"<<endl;
        return;
    }
    
    while (!lecturaF.eof())
    {
        vector<string> arr;
        string valor;
        bool entreComillas = false;
        getline(lecturaF,linea);
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

        if (arr[1]!=riesgoABorrar.nombre)
        {
            riesgosActuales.push_back(linea);
        }
        


    }
    lecturaF.close();


    ofstream archivo;
    archivo.open(nombre,ios::out);
    if (archivo.fail())
    {
        cout<<"No se puede abrir archivo";
        return;
    }

    for (size_t i = 0; i < riesgosActuales.size(); i++)
    {
        archivo<<riesgosActuales[i];
        if (i+1!=riesgosActuales.size())
        {
            archivo<<endl;
        }
        
        
    }
    
    
        
    
    archivo.close();
}
void eliminarMayor(vector<Riesgo> &r){
    eliminarRiesgoCSV(r[0]);
    swap(r[0],r[r.size() - 1]);
    r.pop_back();
    //cout<<r.size();
    heapifyDown(r,0);
}

Riesgo obtenerMayorRiesgo(vector<Riesgo> r){
    return r[0];
}

void cargarRiesgos(vector<Riesgo> &listaRiesgos){

    ifstream lecturaF;
    string linea;
    string palabra;
    string nombre = "riesgos.csv";
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
                int num = stoi(arr[0]);
                agregarRiesgo(listaRiesgos,num,arr[1],arr[2]);
    }
    
    lecturaF.close();
}



void añadirRiesgoCSV(vector<Riesgo> &listaRiesgos,Riesgo riesgo){
    ofstream archivo;
    string nombre = "riesgos.csv";
    archivo.open(nombre,ios::app);
    if (archivo.fail())
    {
        cout<<"No se puede abrir archivo";
    }else
    {
        archivo<<endl<<riesgo.nivelRiesgo<<","<<riesgo.nombre<<","<<riesgo.descripcion;
        agregarRiesgo(listaRiesgos,riesgo.nivelRiesgo,riesgo.nombre,riesgo.descripcion);
        
    }
    archivo.close();
    
}

int gestionRiesgos(){
    vector<Riesgo> riesgos;
    Riesgo riesgoNuevo;
    Riesgo riesgoActual;
    cargarRiesgos(riesgos);
    int opcionRiesgo;
    int opcionBorrarRiesgo;
    do
    {
        cout<<"Eliga una opcion:"<<endl;
        cout<<"1)Observar los riesgos"<<endl;
        cout<<"2)Añadir un riesgo"<<endl;
        cout<<"3)Atender el riesgo actual"<<endl;
        cout<<"4)Salir"<<endl;
        cin>>opcionRiesgo;
        switch (opcionRiesgo)
        {
        case 1:
            cout<<"---------Lista de Riesgos Financieros del Banco en forma jerarquica (nivel de riesgo-nombre)---------"<<endl;
            mostrarRiesgos(riesgos);
            break;
        case 2:
            cout<<"Ingrese el nivel de riesgo"<<endl;
            cin>>riesgoNuevo.nivelRiesgo;
            
            cin.ignore();
            cout<<"Ingrese el nombre del riesgo"<<endl;
            getline(cin,riesgoNuevo.nombre);
            cout<<"Agregue una pequeña descripcion del riesgo"<<endl;
            cin.ignore();
            
            getline(cin,riesgoNuevo.descripcion);
            añadirRiesgoCSV(riesgos,riesgoNuevo);
            break;
        case 3:
            riesgoActual = obtenerMayorRiesgo(riesgos);
            cout<<"Nivel de riesgo:"<<riesgoActual.nivelRiesgo<<endl;
            cout<<"Nombre del riesgo:"<<riesgoActual.nombre<<endl;
            cout<<"Descripcion del riesgo: "<<riesgoActual.descripcion<<endl;
            cout<<"El riesgo fue atendido? 1-Si No-cualquier otra tecla"<<endl;
            cin>>opcionBorrarRiesgo;
            if (opcionBorrarRiesgo==1)
            {
                cout<<"El riesgo ha sido atendido, eliminando de la lista..."<<endl;
            }else
            {
                cout<<"El riesgo se mantiene, se recomienda atenderlo con prisa"<<endl;
            }
            
            
            eliminarMayor(riesgos);
            break;
        default:
            cout<<"Escriba una opcion disponible..."<<endl;
            break;
        }
    } while (opcionRiesgo!=4);
    
    
    //añadirRiesgoCSV(riesgos,riesgoPrueba);
    //cout<<endl<<"Holaa"<<endl;
    
    //mostrarRiesgos(riesgos);
    return 0;

}


void saludar(){
    cout<<"XD"<<endl;
};

#endif