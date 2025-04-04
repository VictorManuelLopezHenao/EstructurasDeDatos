#include<iostream>
using namespace std;

struct nodo {
    int info;
    struct nodo *sig;
};

void insertar(nodo *&raiz);
void imprimir(nodo *&raiz);
void extraer(nodo *&raiz);
void cantidad(nodo *&raiz);
void liberar(nodo *&raiz);
void extraerN(nodo *&raiz);
void insertarN(nodo *&raiz);

int main(){

    int opc, opc2;
    struct nodo *raiz = NULL;

    do{
    cout<<"\n\tMENÚ PILAS";
    cout<<"\n1. Insertar nodo"<<endl;
    cout<<"2. Imprimir pila"<<endl;
    cout<<"3. Extraer (Sale último nodo en llegar)"<<endl;
    cout<<"4. Cantidad"<<endl;
    cout<<"5. Liberar (Vaciar pila)"<<endl;
    cout<<"6. Salir"<<endl;
    
    cout<<"\nIngrese una opción: "; cin>>opc;

    switch(opc){
        case 1: cout<<"\n\tInsertar nodo"<<endl; 
        cout<<"\n1. Insertar en la ultima posicion"<<endl;
        cout<<"2. Insertar en la poscision N"<<endl;
        cout<<"\nElija una opcion: "; cin>>opc2;
        if(opc2 == 1){
            insertar(raiz);
         }else{
            insertarN(raiz);
         } break;

        case 2: cout<<"\n\tImprimir pila"<<endl; imprimir(raiz); break;

        case 3: cout<<"\n\tExtraer nodo"<<endl;
        cout<<"\n1. Extraer de la ultima posicion"<<endl;
        cout<<"2. Extraer de la poscision N"<<endl;
        cout<<"\nElija una opcion: "; cin>>opc2;
        if(opc2 == 1){
            extraer(raiz);
         }else{
            extraerN(raiz);
         } break;

        case 4: cout<<"\n\tCantidad de nodos"<<endl; cantidad(raiz); break; 

        case 5: cout<<"\n\tLiberar pila"<<endl; liberar(raiz); break;

        case 6: cout<<"\nHasta luego..."<<endl; break;

        default: cout<<"\nOpcion no valida"<<endl; break;
    }
}while(opc!=6);

    return 0;
}

void insertar(nodo *&raiz){

    struct nodo *nuevo = new(struct nodo);
    cout<<"\nIngrese un numero: "; cin>>nuevo->info;

    if(raiz == NULL){
        raiz = nuevo;
        nuevo->sig = NULL;
    } else {
        nuevo->sig = raiz;
        raiz = nuevo;
    }
}

void imprimir(nodo *&raiz){
    if(raiz == NULL){
        cout<<"\nLa pila está vacia"<<endl;
        return;
    }

    struct nodo *aux = NULL;

    cout<<"\nLista de nodos: \n\n";
    while(raiz != NULL){
        cout<<raiz->info<<endl;
        struct nodo *temp = raiz;
        raiz = raiz->sig;

        temp->sig = aux;
        aux = temp;
    }

    while(aux != NULL){
        struct nodo *temp = aux;
        aux = aux->sig;
        temp->sig = raiz;
        raiz = temp;
    }
}

void extraer(nodo *&raiz){
    if(raiz == NULL){
        cout<<"\nLa pila está vacia"<<endl;
        return;
    }

    int informacion = raiz->info;
    struct nodo *elim = raiz;
    raiz = raiz->sig;
    delete elim;
    
    cout<<"\nDato extraido: "<<informacion<<endl;
}

void cantidad(nodo *&raiz){
    if(raiz == NULL){
        cout<<"\nLa pila está vacia"<<endl;
        return;
    }

    int count = 0;
    struct nodo *aux = NULL;

    while(raiz != NULL){
        count++;
        struct nodo *temp = raiz;
        raiz = raiz->sig;
        temp->sig = aux;
        aux = temp;
    }

    while(aux != NULL){
        struct nodo *temp = aux;
        aux = aux->sig;
        temp->sig = raiz;
        raiz = temp;
    }

    cout<<count<<endl;             //manejar la funcion con int

}

void liberar(nodo *&raiz){
    if (raiz == NULL) {
        cout<<"La pila ya está vacía."<<endl;
        return;
    }

    struct nodo *reco = raiz;
    struct nodo *bor;

    if (raiz == NULL) {
        cout<<"La pila ya está vacía."<<endl;
        return;
    }

    while (reco != NULL) {
        bor = reco;
        reco = reco->sig;
        delete bor;  
    }
    raiz = NULL;
    cout<<"Pila liberada." <<endl;
}

void extraerN(nodo *&raiz){

}

void insertarN(nodo *&raiz){

}