#include<iostream>
#include<fstream>
using namespace std;

struct datos {
    int id, tel, edad;
    char nombres[30], apellidos[30], sexo[10];
    char fechaservicio[11];
    datos *sig;
};

void listado();
void consultarPorID();

int main(){

    int opc;

    do{
        cout<<"\n\tMenú principal"<<endl;
        cout<<"\n1. Listado de personas atentidas"<<endl;
        cout<<"2. Consultar persona atendida"<<endl;
        cout<<"3. Salir"<<endl;
        cout<<"\nElija una opcion: "; cin>>opc;

        switch(opc){

            case 1: cout<<"\n\tListado de personas atentidas"<<endl; 
            listado(); break;

            case 2:cout<<"\n\tConsultar persona atendida"<<endl;
            consultarPorID(); break;

            case 3: cout<<"\nPrograma cerrado. Vuelva pronto..."<<endl; break;

            default: cout<<"\nOpcion no valida"<<endl; break;
        }
    }while(opc!=3);

    return 0;
}


void listado() {
    ifstream archivo("PersonasAtendidas.bin", ios::binary);

    if (!archivo.is_open()) {
        cout << "\nError al intentar abrir el archivo." << endl;
        return;
    }

    datos persona;
    cout << "\nListado de personas atendidas:\n" << endl;

    while (archivo.read(reinterpret_cast<char*>(&persona), sizeof(persona))) {
        cout << "ID: " << persona.id << endl;
        cout << "Nombre: " << persona.nombres << " " << persona.apellidos << endl;
        cout << "Sexo: " << persona.sexo << endl;
        cout << "Teléfono: " << persona.tel << endl;
        cout << "Edad: " << persona.edad << endl;
        cout << "Fecha de Servicio: " << persona.fechaservicio << endl;
        cout << "-----------------------------------" << endl;
    }

    archivo.close();
}

void consultarPorID() {
    ifstream archivo("PersonasAtendidas.bin", ios::binary);

    if (!archivo.is_open()) {
        cout << "\nError al intentar abrir el archivo." << endl;
        return;
    }

    int idB;
    cout << "\nIngrese el ID de la persona a consultar: ";
    cin >> idB;

    datos persona;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&persona), sizeof(persona))) {
        if (persona.id == idB) {
            cout << "\nPersona encontrada:\n" << endl;
            cout << "ID: " << persona.id << endl;
            cout << "Nombre: " << persona.nombres << " " << persona.apellidos << endl;
            cout << "Sexo: " << persona.sexo << endl;
            cout << "Teléfono: " << persona.tel << endl;
            cout << "Edad: " << persona.edad << endl;
            cout << "Fecha de Servicio: " << persona.fechaservicio << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "\nNo se encontró una persona con el ID ingresado." << endl;
    }

    archivo.close();
}

