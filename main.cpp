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
        cout << "\n--- Menú Principal ---\n";
        cout << "1. Gestion de Clientes\n";
        cout << "2. Finanzas\n";
        cout << "3. Gestion de Riesgos\n";
        cout << "4. Recursos Humanos\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin>>opcionGeneral;
        switch (opcionGeneral)
        {
        case 1:
            cout<<endl<<"-------///Modulo de Gestion de Clientes///-------"<<endl;
            gestionClientes();
            break;
        case 2:
        cout<<endl<<"-------///Modulo del area de Finanzas///-------"<<endl;
            gestionFinanzas();
            break;
        case 3:
        cout<<endl<<"-------///Modulo de Gestion de Candidatos///-------"<<endl;
            gestionCandidatos();
            break;
        case 4:
        cout<<endl<<"-------///Modulo de Gestion de Riesgos///-------"<<endl;
            gestionRiesgos();
            break;
        default:
            break;
        }
    } while (opcionGeneral!=5);
    
    return 0;
}