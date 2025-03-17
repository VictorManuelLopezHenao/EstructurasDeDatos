#include<iostream>
#include<time.h>

using namespace std;

void ingresar(struct persona *&cabeza);
void eliminar(struct persona *&cabeza);
void lista(struct persona *cabeza);
int random();
void elimronda(struct persona *&cabeza);


struct persona{
    char nombre[30];
    int id;
    struct persona *sig;
    struct persona *ant;
};

int main(){
   
    int opc;

    struct persona *cabeza = NULL;

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
        case 1: cout<<"\n\n\tAgregar jugador"<<endl; ingresar(cabeza); break;

        case 2: cout<<"\n\n\tEliminar jugador"<<endl;
         if(cabeza == NULL){                                  //si no hay jugadores registrados 
            cout<<"\nNo hay jugadores registrados"<<endl;
        } else {
          eliminar(cabeza);} break; 

        case 3:cout<<"\n\n\tJuego de la ronda"<<endl;
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

void ingresar(struct persona *&cabeza){

    struct persona *nuevo;
    nuevo = new(struct persona);

    cout<<"\nIngrese su nombre: "; cin.ignore(); cin.getline(nuevo->nombre, 30);
    cout<<"Ingrese su id: "; cin>>nuevo->id;

    struct persona *temp = cabeza;

    if(cabeza == NULL){
        cabeza = nuevo;
        cabeza->sig = cabeza;
        cabeza->ant = cabeza;
    } else {
       
        while(temp->sig != cabeza){
            temp = temp->sig;
        }

        temp->sig = nuevo;
        nuevo->sig = cabeza;
        nuevo->ant = temp;
    }

    cout<<"\nRegistro existoso"<<endl;
}

void eliminar(struct persona *&cabeza){

    int idB;
    struct persona *temp = cabeza;

    cout<<"\nIngrese el id del jugador a eliminar: "; cin>>idB;

    if(temp->sig == cabeza){
        if(temp->id == idB){
            
            cabeza = NULL;
            delete temp;
            cout<<"\nEliminacion exitosa"<<endl;
            return; 
            
        }

        cout<<"\nEl id ingresado no coincide con el de ningun jugador"<<endl;
        return;
    }

    do{
        if(temp->id == idB){
            if(temp == cabeza){
                
                struct persona *antelim = cabeza;

                while(antelim->sig != cabeza){
                    antelim = antelim->sig;
                }

                cabeza = temp->sig;
                antelim->sig = cabeza;
                cabeza->ant = antelim;


            } else {

               struct persona *anterior = temp->ant;
               anterior->sig = temp->sig;
               temp->sig->ant = anterior;

            }
               
            delete temp;
            cout<<"\nEliminacion exitosa"<<endl;
            return;

        }

        temp = temp->sig; 

    }while(temp != cabeza);
    
    cout<<"\nEl id ingresado no coincide con el de ningun jugador"<<endl;
}

void lista(struct persona *cabeza){

    struct persona *temp = cabeza;

    do{
        cout<<"\nNombre: "<<temp->nombre<<endl;
        cout<<"Id: "<<temp->id<<endl;

        temp = temp->sig;
          
    }while(temp!=cabeza);
}

int random(){

    int num;

    srand(time(NULL));
    num = rand() % 6 + 1;

    return num;
}

void elimronda(struct persona *&cabeza){

    int num = random();
    int opc;
    int posc = 1;

    struct persona *temp = cabeza;

    if(cabeza->sig == cabeza){
        cout<<"\nEl jugador "<<cabeza->nombre<<" ha sido el ganador"<<endl;
        return;
    }

    cout<<"\n¿En que direccion desea jugar esta ronda?"<<endl;
    cout<<"\n1. Derecha"<<endl;
    cout<<"2. Izquierda"<<endl;
    cout<<"\nElija una opcion: "; cin>>opc;

    if(opc == 1){
        while(posc != num){
            temp = temp->sig;
            posc++;
        }
       
        cabeza = temp->sig;
        cabeza->ant = temp->ant;
        temp->ant->sig = cabeza;
        delete temp;

        cout<<"\nEl dado lanzó el numero: "<<num<<endl;
        cout<<"\nJugador en la posicion "<<posc<<" eliminado"<<endl;
   
    } else {

        while(posc != num){
            temp = temp->ant;
            posc++;
        }

        cabeza = temp->ant;
        cabeza->sig = temp->ant;
        temp->sig->ant = cabeza;
        delete temp;

        cout<<"\nEl dado lanzó el numero: "<<num<<endl;
        cout<<"\nJugador en la posicion "<<posc<<" eliminado"<<endl;
    }
   
    if(cabeza->sig == cabeza){
      cout<<"\nEl jugador "<<cabeza->nombre<<" ha sido el ganador"<<endl;
    }
}