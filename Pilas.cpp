#include<iostream>
using namespace std;

struct nodo {
    int info;
    struct nodo *sig;
};

void insertar(nodo *&raiz);
void imprimir(nodo *&raiz);
void extraer(nodo *&raiz);
int cantidad(nodo *&raiz);
void liberar(nodo *&raiz);
void insertarN(nodo *&raiz);
void extraerN(nodo *&raiz);

int main(){

    int opc, opc2;
    struct nodo *raiz = NULL;

    do{
    cout<<"\n\tMENÚ PILAS"<<endl;
    cout<<"\n1. Insertar nodo"<<endl;
    cout<<"2. Imprimir pila"<<endl;
    cout<<"3. Extraer"<<endl;
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
         }else if(opc2 == 2){
            insertarN(raiz);
         } else {
            cout<<"\nOpcion no disponible"<<endl;
         }break;

        case 2: cout<<"\n\tImprimir pila"<<endl;
        if(raiz == NULL){
            cout<<"\nLa pila está vacia"<<endl;
        } else {
            imprimir(raiz);
        } break;

        case 3: cout<<"\n\tExtraer nodo"<<endl;
        if(raiz == NULL){
            cout<<"\nLa pila está vacia"<<endl;
        } else {

        cout<<"\n1. Extraer de la ultima posicion"<<endl;
        cout<<"2. Extraer de la poscision N"<<endl;
        cout<<"\nElija una opcion: "; cin>>opc2;
        if(opc2 == 1){
            extraer(raiz);
         }else if(opc2 == 2){
            extraerN(raiz);
         } else {
            cout<<"\nOpcion no disponible"<<endl;
         } break;

        case 4: cout<<"\n\tCantidad de nodos\n"<<endl; 
        if(raiz == NULL){
            cout<<"La pila está vacia"<<endl;
        } else {
                cout<<cantidad(raiz)<<endl;
            }
        } break; 

        case 5: cout<<"\n\tLiberar pila"<<endl; 
        if (raiz == NULL) {
            cout<<"La pila ya está vacía."<<endl;
        } else {
            liberar(raiz); 
        } break;

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

    struct nodo *aux = NULL;

    cout<<"\nInformacion de nodos: \n\n";
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
    
    int informacion = raiz->info;
    struct nodo *elim = raiz;
    raiz = raiz->sig;
    delete elim;
    
    cout<<"\nDato extraido: "<<informacion<<endl;
}

int cantidad(nodo *&raiz){
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

 return count;         

}

void liberar(nodo *&raiz){
   
    struct nodo *reco = raiz;
    struct nodo *bor;

    while (reco != NULL) {
        bor = reco;
        reco = reco->sig;
        delete bor;  
    }
    raiz = NULL;
    cout<<"Pila liberada." <<endl;
}

void insertarN(nodo *&raiz){

    int posc;
    cout<<"\nIngrese la posicion donde desea ingresar el nodo: "; cin>>posc;

    if(posc == (cantidad(raiz) + 1)){
        insertar(raiz);                         //ultima posicion
        return;
    }

    if(posc != 1 && posc > cantidad(raiz) || posc <= 0){
        cout<<"\nPosicion no disponible"<<endl;
        return;
    }

    struct nodo *aux = NULL;

    if(posc == 1){                          //1 posicion
        if(raiz == NULL){
            insertar(raiz);
            return;
       
        } else {

            while(raiz != NULL){
            struct nodo *temp = raiz;
            raiz = raiz->sig;
            temp->sig = aux;
            aux = temp;
           }
   
    }
      } else {                //posicion x

        while(posc -1 != cantidad(raiz)){
            struct nodo *temp = raiz;
            raiz = raiz->sig;
            temp->sig = aux;
            aux = temp; 
        }

    }
    
    insertar(raiz);

    while(aux != NULL){
     struct nodo *temp = aux;
     aux = aux->sig;
     temp->sig = raiz;
     raiz = temp;
   
}
}

void extraerN(nodo *&raiz){
   
    int posc;
    cout<<"\nIngrese la posicion donde desea extraer el nodo: "; cin>>posc;

    if(posc > cantidad(raiz) || posc <= 0){
        cout<<"\nPosicion no disponible"<<endl;
        return;
    }

    if(posc == cantidad(raiz)){      //ultima posicion
        extraer(raiz);
        return;
    }

    struct nodo *aux = NULL;

    if(posc == 1){          //1 posicion
        
        while(cantidad(raiz) != 1){
            struct nodo *temp = raiz;
            raiz = raiz->sig;
            temp->sig = aux;
            aux = temp;
        }

    } else {         //posicion x

        while(posc != cantidad(raiz)){
            struct nodo *temp = raiz;
            raiz = raiz->sig;
            temp->sig = aux;
            aux = temp;
        }
    
    }
        extraer(raiz);

        while(aux != NULL){
            struct nodo *temp = aux;
            aux = aux->sig;
            temp->sig = raiz;
            raiz = temp;
        }

    }
   
