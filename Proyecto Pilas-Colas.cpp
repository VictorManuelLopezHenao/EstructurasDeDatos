#include<iostream>
using namespace std;

struct datos{
    int id, tel, edad;
    char nombres[30], apellidos[30], fechaservicio[11], sexo[10];
    datos *sig;
};

void registrar(datos *&raiz1, datos *&fondo1, datos *&raiz2, datos *&fondo2, datos *&raiz3, datos *&fondo3);
void elimPersonaCola(datos *&raiz1, datos *&fondo1, datos *&raiz2, datos *&fondo2, datos *&raiz3, datos *&fondo3);

int main(){

    int opc;

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

            case 1: cout<<"\n\tRegistro"<<endl; registrar(raiz1, fondo1, raiz2, fondo2, raiz3, fondo3); break;

            case 2: cout<<"\n\tTurno siguiente"<<endl; break;

            case 3: cout<<"\n\tEliminar persona de la cola"<<endl; elimPersonaCola(raiz1, fondo1, raiz2, fondo2, raiz3, fondo3); break;

            case 4: cout<<"\n\tListado de personas atendidas"<<endl; break;

            case 5: cout<<"\nPrograma cerrado. Vuelve pronto..."<<endl; break;

            case 6: break;

            default: cout<<"\nOpcion no valida"<<endl; break;
        }

    }while(opc!=5);

    return 0;
}

void registrar(datos *&raiz1, datos *&fondo1, datos *&raiz2, datos *&fondo2, datos *&raiz3, datos *&fondo3){

    datos *nuevo = new(struct datos);

    cout<<"\nDigite la siguiente informacion: "<<endl;
    cout<<"\nNombres: "; cin.ignore(); cin.getline(nuevo->nombres, 30);
    cout<<"Apellidos: "; cin.getline(nuevo->apellidos, 30);
    cout<<"Sexo: "; cin.getline(nuevo->sexo, 11);
    cout<<"N° de identificacion: "; cin>>nuevo->id; 
    cout<<"N° de telefono: "; cin>>nuevo->tel;
    cout<<"Edad: "; cin>>nuevo->edad;
    
    nuevo->sig = NULL;

    if(nuevo->edad > 55){
        if(raiz1 == NULL){
            raiz1 = nuevo;
            fondo1 = nuevo;
        } else {
            fondo1->sig = nuevo;
            fondo1 = nuevo;
        }

    } else if (nuevo->edad <= 55 && nuevo->edad > 40) {
        if(raiz2 == NULL){
            raiz2 = nuevo;
            fondo2 = nuevo;
        } else {
            fondo2->sig = nuevo;
            fondo2 = nuevo;
        }

    } else if (nuevo->edad <= 40 && nuevo->edad > 0){
        if(raiz3 == NULL){
            raiz3 = nuevo;
            fondo3 = nuevo;
        } else {
            fondo3->sig = nuevo;
            fondo3 = nuevo;
        }

    } else {
        cout<<"\nEdad no valida"<<endl;
    }
   
    
}


void elimPersonaCola(datos *&raiz1, datos *&fondo1, datos *&raiz2, datos *&fondo2, datos *&raiz3, datos *&fondo3){

    int edadB, idB;
    cout<<"\nIngrese los siguientes datos de la persona a eliminar: "<<endl;
    cout<<"\nEdad: "; cin>>edadB;
    cout<<"Identificacion: "; cin>>idB;

    if(edadB > 55){

    }
    
    datos *auxR = NULL;
    datos *auxF = NULL;

   

    while(raiz != NULL){
        nodo *temp = raiz;
        raiz = raiz->sig;
        temp->sig = NULL;
        
        if(idB == raiz->){
            nodo *elim = temp;
            cout<<"\nInformacion del nodo eliminado: "<<elim->info<<endl;
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
    }

    raiz = auxR;
    fondo = auxF;

}