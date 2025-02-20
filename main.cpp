#include <iostream>
#include "moduloRiesgos.h"
#include "moduloClientes.h"
#include "moduloCandidatos.h"
#include "moduloFinanzas.h"
using namespace std;

int main(){
    cout<<"Hola";
    int opcionGeneral;
    do
    {
        cout<<"Opciones:"<<endl;
        cout<<"1) Opcion 1"<<endl;
        cout<<"2) Opcion 2"<<endl;
        cout<<"3) Opcion 3"<<endl;
        cout<<"4) Opcion 4"<<endl;
        cin>>opcionGeneral;
        switch (opcionGeneral)
        {
        case 1:
            gestionClientes();
            break;
        case 2:
            gestionFinanzas();
            break;
        case 3:
            gestionCandidatos();
            break;
        case 4:
            gestionRiesgos();
            break;
        default:
            break;
        }
    } while (opcionGeneral!=5);
    
    return 0;
}