#include <iostream>

using namespace std;
 
void agregarnodofinal(struct nodo *&primero);   //*&  trabaja con el puntero original
void opcinsert(struct nodo *&primero, int count);
void muestracontenido(struct nodo *primero, int count);    //*   trabaja con una copia del puntero
void agregarnodoposc(struct nodo *&primero, int count);
void opceliminar(struct nodo *&primero, int count);
void eliminarnodoposc(struct nodo *&primero, int count);

struct nodo{                 
   int id;
   char nombre[30];
   struct nodo *sig;
};


int main(){

    struct nodo *primero = NULL;  //este puntero lo utilizo para apuntar al primer nodo de la lista

    int opc;
    int count;

    do{
    cout<<"\n\tMenú de opciones "<<endl;
    cout<<"\n1. Insertar nodo"<<endl;
    cout<<"2. Eliminar nodo"<<endl;
    cout<<"3. Mostrar contenido de la lista"<<endl;
    cout<<"4. Salir"<<endl;
    cout<<"\nOpcion: "; cin>>opc;


    switch(opc){

        case 1: cout<<"\n\tInsertar nodo"<<endl; opcinsert(primero, count);  count++; break;

        case 2: cout<<"\n\tEliminar nodo"<<endl; opceliminar(primero, count); break;

        case 3: cout<<"\n\tContenido de la lista"<<endl; muestracontenido(primero, count); break;

        case 4: cout<<"\n¡Hasta pronto!..."<<endl; break;
        
        default: cout<<"\nOpción no valida"<<endl; break;

    }

    }while(opc!=4);

    return 0;
}

void opcinsert(struct nodo *&primero, int count){

    int opc;

    cout<<"\nSeleccione una opcion: "<<endl;
    cout<<"\n1. Insertar nodo al final de la lista"<<endl;
    cout<<"2. Insertar nodo despues de una posicion"<<endl;
    cout<<"3. Insertar nodo despues de una persona"<<endl;
    cout<<"4. Salir"<<endl;
    cout<<"\nOpcion: "; cin>>opc;

    switch(opc){
        
        case 1: cout<<"\n\tInsertar nodo al final de la lista"<<endl; agregarnodofinal(primero); return; break;

        case 2: cout<<"\n\tInsertar nodo despues de una posicion"<<endl; agregarnodoposc(primero, count); return; break;

        case 3: cout<<"\n\tInsertar nodo despues de una persona"<<endl;

        case 4: cout<<"\n¡Vuelve pronto!"<<endl;

        default: cout<<"\nOpción no valida"<<endl; break;

    }

}

void agregarnodofinal(struct nodo *&primero){
    struct nodo *nuevo;
    nuevo = new(struct nodo);    //asigna dinamicamente memoria para un nuevo nodo
                                     // y almacena la direccion de esta en el puntero nuevonodo
    cout<<"\nIngrese su id:  "; cin>>nuevo->id;
    cout<<"Ingrese su nombre: "; cin>>nuevo->nombre;
    cout<<"\nDatos registrados existosamente"<<endl<<endl;

    if(primero == NULL){          //si la lista está vacia, el nuevo nodo sera el primero de la lista
        nuevo->sig = NULL;        //el nuevo nodo apunta a NULL
        primero = nuevo;          // El nuevo nodo se convierte en el primer nodo de la lista
    } else {
        struct nodo *temp = primero;  //apunta al primer nodo de la lista
        
        while(temp->sig != NULL){     //se repite hasta que encuentre a NULL, es decir
            temp = temp->sig;         //la direccion a la que apunta el ultimo nodo
        }

        temp->sig = nuevo;            //ahora sig, cambia a NULL, por la direccion del nuevo nodo
        nuevo->sig = NULL;            //el nuevo nodo apunta a NULL
    }
}

void agregarnodoposc(struct nodo *&primero, int count){

    int posc;
    int count2 = 1;
    cout<<"\nCantidad de nodos registrados: "<<count;
    cout<<"\nIndique la posicion donde desea agregar el nodo: "; cin>>posc;

    if(posc <= count){
        struct nodo *nuevo;
        nuevo = new(struct nodo);

        cout<<"\nIngrese su id:  "; cin>>nuevo->id;
        cout<<"Ingrese su nombre: "; cin>>nuevo->nombre;
        cout<<"\nDatos registrados existosamente"<<endl<<endl;

        struct nodo *temp = primero;
        while(posc > count2){
            temp = temp->sig;
            count2++;
        }

        nuevo->sig = temp->sig;  //el nuevo nodo apunta al que apunta el nodo actual
        temp->sig = nuevo;  //el nodo actual apunta al nuevo nodo
    } else {
        cout<<"La posicion digitada es menor a la cantidad de nodos registrados"<<endl;
    }
}

void opceliminar(struct nodo *&primero, int count){

    int opc;

    cout<<"\nSeleccione una opcion: "<<endl;
    cout<<"\n1. Eliminar nodo de una posicion"<<endl;
    cout<<"2. Eliminar nodo despues de una persona"<<endl;
    cout<<"3. Salir"<<endl;
    cout<<"\nOpcion: "; cin>>opc;

    switch(opc){
        
        case 1: cout<<"\n\tEliminar nodo de una posicion"<<endl; eliminarnodoposc(primero, count); return; break;

        case 2: cout<<"\n\tEliminar nodo despues de una persona"<<endl;  return; break;

        case 3: cout<<"\n¡Vuelve pronto!"<<endl;

        default: cout<<"\nOpción no valida"<<endl; break;

    }

}

void eliminarnodoposc(struct nodo *&primero, int count){

    int posc;
    int count2 = 1;
    cout<<"\nCantidad de nodos registrados: "<<count;
    cout<<"\nIndique la posicion donde desea eliminar el nodo: "; cin>>posc;

    if(posc <= count){
        struct nodo *temp = primero;
       
        while(posc > count2){
            temp = temp->sig;
            count2++;
        }

        struct nodo *eliminado = temp->sig;
        temp->sig = eliminado->sig;

        count--;
        cout<<"\nNodo eliminado exitosamente"<<endl;
       

    } else {
        cout<<"La posicion digitada es menor a la cantidad de nodos registrados"<<endl;
    }
}

void muestracontenido(struct nodo *primero, int count){

    struct nodo *temp = primero;

    if(count == 0){
        cout<<"\nNo hay registros"<<endl;
    } else {

        cout<<"\nHay "<<count<<" registros"<<endl;

    while(temp != NULL){
        cout<<"\nCodigo: "<<temp->id<<endl;
        cout<<"Nombre: "<<temp->nombre<<endl;
        
        temp = temp->sig;
    }
}
}