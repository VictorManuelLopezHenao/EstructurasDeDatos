#include<iostream>
#include<time.h>  //para la func random

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

        case 2: cout<<"\n\n\tEliminar jugador"<<endl;
         if(cabeza == NULL){                                  //si no hay jugadores registrados 
            cout<<"\nNo hay jugadores registrados"<<endl;
        } else {
            eliminar(cabeza); }break;

        case 3: cout<<"\n\n\tJuego de la ronda"<<endl; 
         if(cabeza == NULL){                                  
            cout<<"\nNo hay jugadores registrados"<<endl;
        } else {
            elimronda(cabeza);} break;

        case 4: cout<<"\n\n\tLista de jugadores"<<endl;
        if(cabeza == NULL){                                  
            cout<<"\nNo hay jugadores registrados"<<endl;
        } else {
             lista(cabeza);} break;

        case 5: cout<<"\nSaliendo, gracias por visitar..."<<endl; break;

        default: cout<<"\nOpcion invalida"<<endl; break;
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
    struct persona *temp = cabeza;
    struct persona *ant = NULL;

    cout<<"\nDigite la id de la persona a eliminar: "; cin>>idB;

    if(temp->sig == cabeza){                                           //si hay un solo nodo en la lista
        if(temp->id == idB){                                    //y la id coincide

            cout<<"\nEliminacion exitosa"<<endl;
            delete temp;                                        //se borra el nodo
            cabeza = NULL;                                      //la lista pasa a ser vacia
            return;                                          //se retorna al menu
        }

        cout<<"\nIdentificacion no encontrada"<<endl;         
        return;
    }
 
    do{                                                 //si hay varios nodos en la lista
        if(temp->id == idB){                                    //y la id coincide
            if(temp == cabeza){                                     //y es el primer nodo de la lista
                
                struct persona *elim = temp;
                
                while(elim->sig != cabeza){                     //se busca el ultimo nodo de la lista
                    elim = elim->sig; }

                cabeza = cabeza->sig;                       //la cabeza será el nodo sgte
                elim->sig = cabeza;                        //se conecta el ultimo nodo con la nueva cabeza
                                                             
            } else {
                                                                 //si el nodo no es la cabeza de la lista
                ant->sig = temp->sig;                           //se conecta el nodo anterior con el sgte
                                              
            }
           
            cout<<"\nEliminacion exitosa"<<endl;
            delete temp;                                //se elimina el nodo
            return;                                    //se retorna al menu
          
        }
        
        ant = temp;                                    //si la id no coincide
        temp = temp->sig;                            //se avanza al sgte nodo
 
    }while(temp != cabeza);         //recorre la lista 
   
    cout<<"\nEl id ingresado no coincide con el de ningun jugador"<<endl;

}

void lista(struct persona *cabeza){

    struct persona *temp = cabeza;

    do{
      cout<<"\nNombre: "<<temp->nombre<<endl;
      cout<<"Id: "<<temp->id<<endl;                //imprime los nodos de la lista
      temp = temp->sig;
        }while(temp != cabeza);       //recorre la lista 

}

int random(){

    int num;          //time(NULL) proporciona un valor diferente cada segundo
    srand(time(NULL));  //srand establece la semilla del generador aleatorio
    num = rand() % 6 + 1;  // dado entre 1 y 6

    return num;  //retorna el valor arrojado por el dado
}

void elimronda(struct persona *&cabeza){
    
    int posc = 1;    
    int num = random();      //el valor de num, depende de lo que devuleva la func random

    struct persona *temp = cabeza;
    struct persona *ant = NULL;

    if(cabeza->sig == cabeza){                                                 //si solo hay un jugador 
        cout<<"\nEl jugador "<<cabeza->nombre<<" ha sido el ganador"<<endl;       //es el ganador 
        return;                                                                 //se retorna al menu
    } 

    while(posc != num){                  //se recorre la lista hasta encontrar el nodo en la posicion que arroja el dado
     ant = temp;
     temp = temp->sig;
     posc++;
    } 

    
       cabeza = temp->sig;     //la nueva cabeza es el sgte del nodo a eliminar
       ant->sig = cabeza;       //se conecta el nodo anterior al eliminado con la nueva cabeza
       delete temp;     //se elimina el nodo en la posicion arrojada por el dado

       cout<<"\nEl dado lanzó el numero: "<<num<<endl;
       cout<<"\nJugador en la posicion "<<posc<<" eliminado"<<endl;

       if(cabeza->sig == cabeza){                                                //si despues del jugar, queda 1 nodo, ese es el ganador
       cout<<"\nEl jugador "<<cabeza->nombre<<" ha sido el ganador"<<endl;
       }
}

       




    


    
