#include<iostream>
#include<time.h> 

using namespace std;

void registrar(struct persona *&cabeza);
void eliminar(struct persona *&cabeza);
void lista(struct persona *cabeza);
int random();
void elimronda(struct persona *&cabeza);

struct persona{
    char nombre[30];
    int id;
    struct persona *sig; 
};

int main(){

    struct persona *cabeza = NULL;

    int opc;

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
        case 1: cout<<"\n\n\tAgregar jugador"<<endl; registrar(cabeza); break;

        case 2: cout<<"\n\n\tEliminar jugador"<<endl; eliminar(cabeza); break;

        case 3: cout<<"\n\n\tJuego de la ronda"<<endl; 
         if(cabeza == NULL){                                  //si no hay jugadores registrados 
            cout<<"\nNo hay jugadores registrados"<<endl;
        } else {
            elimronda(cabeza);} break;

        case 4: cout<<"\n\n\tLista de jugadores"<<endl; lista(cabeza); break;

        case 5: cout<<"\nSaliendo, gracias por visitar..."<<endl;

        default: cout<<"\nOpcion invalida"<<endl;
    }

  }while(opc!=5);

    return 0;
}

void registrar(struct persona *&cabeza){

    struct persona *nuevo;                //se reserva un espacio en memoria para el nuevo nodo
    nuevo = new(struct persona);

    cout<<"\nIngrese su nombre: "; cin. ignore(); cin.getline(nuevo->nombre, 30);
    cout<<"Ingrese su id: "; cin>>nuevo->id;

    struct persona *temp = cabeza;  

    if(cabeza == NULL){     //si la lista está vacia
        cabeza = nuevo;          //nuevo se convierte en el primer nodo de la lista 
        cabeza->sig = cabeza;    //su siguiente es el mismo, es una lista circular 
    } else {
    
    while(temp->sig != cabeza){          //se recorre la lista 
        temp = temp->sig; 
    }

    temp->sig = nuevo;       //se agrega el nuevo nodo al final de la lista
    nuevo->sig = cabeza;   //y se conecta con la cabeza
    }

    cout<<"\nRegistro exitoso"<<endl; 
}

void eliminar(struct persona *&cabeza){

    int idB;

    cout<<"\nDigite el id de la persona a eliminar: "; cin>>idB; 
    
    struct persona *temp = cabeza;
    struct persona *ant = NULL;  //puntero al nodo anterior 

    while(temp->id != idB){
       ant = temp;              //se recorre la lista hasta que se encuentre el id
       temp = temp->sig;
    }

    if(ant == NULL){        //si ant no ha tomado algun valor, el nodo es la cabeza
     cabeza = temp->sig;   //la cabeza seria el sgte nodo
    } else {

    struct persona *elim = temp;  //se almacena la direccion del nodo a eliminar
    ant->sig = elim->sig;  //se conecta el nodo anterior con el siguiente

    delete temp;  //se elimina el nodo
    }
   
    cout<<"\nEliminación exitosa"<<endl;
}

void lista(struct persona *cabeza){

    if(cabeza == NULL){
        cout<<"\nNo hay jugadores registrados"<<endl;  //si no hay jugadores registrados 
        return;
    }

    struct persona *temp = cabeza;

    do{
      cout<<"\nNombre: "<<temp->nombre<<endl;
      cout<<"Id: "<<temp->id<<endl;                //imprime los nodos de la lista
      temp = temp->sig;
        }while(temp != cabeza);

}

int random(){

    int num;          //time(NULL) proporciona un valor diferente cada segundo
    srand(time(NULL));  //srand establece la semilla del generador aleatorio
    num = rand() % 6 + 1;  // dado entre 1 y 6

    return num;  //retorna el valor arrojado por el dado
}

void elimronda(struct persona *&cabeza){
    
    int posc = 1;
    int num = random();
  

    struct persona *temp = cabeza;
    struct persona *ant = NULL;

    if(cabeza->sig == cabeza){
        cout<<"\nEl jugador "<<cabeza->nombre<<" ha sido el ganador"<<endl;
    } else {

    random();

    while(posc != num){      //recorre la lista hasta el numero lanzado por el dado
        ant = temp; 
        temp = temp->sig;
        posc++;
    }

    if(posc == 1){                 
        cabeza = temp->sig;    //se elimina el primer nodo
    } else {

    struct persona *elim = temp;  //almaceno en elim el nodo a eliminar
    ant->sig = elim->sig;   //conecto el anterior a nodo al nodo siguiente
    cabeza = elim->sig;  //ahora la nueva cabeza es el siguiente al nodo eliminado
    delete elim;
 }

    cout<<"\nJugador en la posicion "<<num<<" eliminado"<<endl;

  }
}