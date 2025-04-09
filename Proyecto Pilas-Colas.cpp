#include<iostream>
using namespace std;

struct datos{
    int id, tel, edad;
    char nombres[30], apellidos[30], fechaservicio[11], sexo[10];
    datos *sig;
};

void registrar(datos *&raiz, datos *&fondo, int edad);
void elimPersonaCola(datos *&raiz, datos *&fondo, int edad);

int main(){

    int opc;
    int edad;

    datos *raiz = NULL; datos *fondo = NULL;
    datos *raiz1 = NULL; datos *fondo1 = NULL; 
    datos *raiz2 = NULL; datos *fondo2 = NULL; 
    datos *raiz3 = NULL; datos *fondo3 = NULL; 

    do{
        cout<<"\n\tMenú principal"<<endl;
        cout<<"\n1. Registrar persona"<<endl;
        cout<<"2. Turno siguiente"<<endl;
        cout<<"3. Eliminar persona de la cola"<<endl;
        cout<<"4. Listado de personas atendidas"<<endl;
        cout<<"5. Salir"<<endl;
        cout<<"\nElija una opcion: "; cin>>opc;

        switch(opc){

            case 1: cout<<"\n\tRegistro"<<endl;

            cout<<"\nIngrese su edad: "; cin>>edad;
            
            if(edad > 55){
                raiz = raiz1;
                fondo = fondo1;

            } else if(edad <= 55 && edad > 40) {
                raiz = raiz2;
                fondo = fondo2;

            } else if(edad <= 40 && edad > 0){
                raiz = raiz3;
                fondo = fondo3;

            } else { 
                cout<<"\nEdad no valida"<<endl;
            }

            registrar(raiz, fondo, edad); break;

            case 2: cout<<"\n\tTurno siguiente"<<endl; break;

            case 3: cout<<"\n\tEliminar persona de la cola"<<endl; 
            
            cout<<"\nIngrese su edad: "; cin>>edad;
            
            if(edad > 55){
                raiz = raiz1;
                fondo = fondo1;

            } else if(edad <= 55 && edad > 40) {
                raiz = raiz2;
                fondo = fondo2;

            } else if(edad <= 40 && edad > 0){
                raiz = raiz3;
                fondo = fondo3;

            } else { 
                cout<<"\nEdad no valida"<<endl;
            }
            
            elimPersonaCola(raiz, fondo, edad); break;

            case 4: cout<<"\n\tListado de personas atendidas"<<endl; break;

            case 5: cout<<"\nPrograma cerrado. Vuelve pronto..."<<endl; break;

            case 6: break;

            default: cout<<"\nOpcion no valida"<<endl; break;
        }

    }while(opc!=5);

    return 0;
}

void registrar(datos *&raiz, datos *&fondo, int edad){

    datos *nuevo = new(struct datos);

    cout<<"\nDigite la siguiente informacion: "<<endl;
    cout<<"\nNombres: "; cin.ignore(); cin.getline(nuevo->nombres, 30);
    cout<<"Apellidos: "; cin.getline(nuevo->apellidos, 30);
    cout<<"Sexo: "; cin.getline(nuevo->sexo, 11);
    cout<<"N° de identificacion: "; cin>>nuevo->id; 
    cout<<"N° de telefono: "; cin>>nuevo->tel;
    nuevo->edad = edad;
    
    nuevo->sig = NULL;

        if(raiz == NULL){
            raiz = nuevo;
            fondo = nuevo;
        } else {
            fondo->sig = nuevo;
            fondo = nuevo;
        }

}


void elimPersonaCola(datos *&raiz, datos *&fondo, int edad){
   
    int idB;
    cout<<"\nIngrese la identificacion de la persona a eliminar: "<<endl;

    datos *auxR = NULL;
    datos *auxF = NULL;

    int count = 1;

    while(raiz != NULL){
        datos *temp = raiz;
        raiz = raiz->sig;
        temp->sig = NULL;
        
        if(idB == raiz->id){
            datos *elim = temp;
            delete elim;
        } else {
            if(auxR == NULL){
                auxR = temp;
                auxF = temp;
            } else {
                auxF->sig = temp;
                auxF = temp;
            }
        }
        count++;
    }

    raiz = auxR;
    fondo = auxF;
}