#include<iostream>
#include<cstring>
#include<time.h> 

using namespace std;

void registrar(struct persona *&cabeza, int &count);
void eliminar(struct persona *&cabeza, int &count);
void lista(struct persona *cabeza);
void random(int &num);
void elimronda(struct persona *&cabeza, int &count);

struct persona{
    char nombre[30];
    int id;
    struct persona *sig; 
};

int main(){

    struct persona *cabeza = NULL;

    int opc;
    int count = 0;

    cout<<"\n\tBienvenido al juego de la ronda"<<endl;

  do{

    cout<<"\nSeleccione una opcion"<<endl; 
    cout<<"\n1. Agregar jugador"<<endl;
    cout<<"2. Eliminar jugador"<<endl;
    cout<<"3. Jugar"<<endl;
    cout<<"4. Ver lista de jugadores"<<endl;
    cout<<"5. Salir"<<endl;
    cout<<"\nOpcion: "; cin>>opc;

    switch(opc){
        case 1: cout<<"\n\n\tAgregar jugador"<<endl; registrar(cabeza, count); break;

        case 2: cout<<"\n\n\tEliminar jugador"<<endl; eliminar(cabeza, count); break;

        case 3: cout<<"\n\n\tJuego de la ronda"<<endl; elimronda(cabeza, count); break;

        case 4: cout<<"\n\n\tLista de jugadores"<<endl; lista(cabeza); cout<<count; break;

        case 5: cout<<"\nSaliendo, gracias por visitar..."<<endl;

        default: cout<<"\nOpcion invalida"<<endl;
    }

  }while(opc!=5);

    return 0;
}

void registrar(struct persona *&cabeza, int &count){

    struct persona *nuevo;
    nuevo = new(struct persona);

    cout<<"\nIngrese su nombre: "; cin>>nuevo->nombre;
    cout<<"Ingrese su id: "; cin>>nuevo->id;

    struct persona *temp = cabeza;

    if(cabeza == NULL){
        cabeza = nuevo;
        cabeza->sig = cabeza;
    } else {
    
    while(temp->sig != cabeza){
        temp = temp->sig;
    }

    temp->sig = nuevo;
    nuevo->sig = cabeza;
    }

    cout<<"\nRegistro exitoso"<<endl;
    count++;  
}

void eliminar(struct persona *&cabeza, int &count){

    int idB;

    cout<<"Digite el id de la persona a eliminar: "; cin>>idB;
    
    struct persona *temp = cabeza;
    struct persona *ant = NULL;

    while(temp->id != idB){
       ant = temp;
       temp = temp->sig;
    }

    if(ant == NULL){
    cabeza = temp->sig;
    } else {

    struct persona *elim = temp;
    ant->sig = elim->sig;

    delete elim;
    }

    cout<<"\nEliminación exitosa"<<endl;
    count--;
}

void lista(struct persona *cabeza){

    if(cabeza == NULL){
        cout<<"\nNo hay jugadores registrados"<<endl;
        return;
    }

    struct persona *temp = cabeza;

    do{
    cout<<"\nNombre: "<<temp->nombre<<endl;
    cout<<"Id: "<<temp->id<<endl;
    
    
    temp = temp->sig;
    }while(temp != cabeza);
    
}

void random(int &num){

    srand(time(NULL));
    num = rand() % 7;

    cout<<"\nEl dado ha lanzado el numero: "<<num<<endl;

}

void elimronda(struct persona *&cabeza, int &count){
   int opc;
   

    int posc = 0;
    int num;

    struct persona *temp = cabeza;
    struct persona *ant = NULL;

    random(num);

    while(posc != num){
        ant = temp;
        temp = temp->sig;
        posc++;
    }

    if(ant == NULL){
        cabeza = temp->sig;
    } else {

    struct persona *elim = temp;
    ant->sig = elim->sig;
    cabeza = temp->sig;
    }

    cout<<"\nJugador en la posicion "<<num<<" eliminado"<<endl;
    delete temp;
    count--;


    if(count == 1){
        cout<<"\nEl jugador "<<cabeza->nombre<<" ha sido el ganador"<<endl;
    }

}