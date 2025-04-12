#include<iostream>
#include<fstream>
using namespace std;

int main(){

    int opc;

    do{
        cout<<"\n\tMenú principal"<<endl;
        cout<<"\n1. Listado de personas atentidas"<<endl;
        cout<<"2. Consultar persona atendida"<<endl;
        cout<<"3. Salir"<<endl;
        cout<<"\nElija una opcion: "; cin>>opc;

        switch(opc){

            case 1: cout<<"\n\tListado de personas atentidas"<<endl; break;

            case 2:cout<<"\n\tConsultar persona atendida"<<endl;break;

            case 3: cout<<"\nPrograma cerrado. Vuelva pronto..."<<endl; break;

            default: cout<<"\nOpcion no valida"<<endl; break;
        }
    }while(opc!=3);

    return 0;
}

void listado(){

}